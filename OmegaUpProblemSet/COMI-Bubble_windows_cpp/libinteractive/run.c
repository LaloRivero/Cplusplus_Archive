/* Auto-generated by libinteractive. Do not edit. */
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PSAPI_VERSION 1
#include <windows.h>
#include <psapi.h>

#if defined(_WIN32)
#if !defined(PRIuS)
#define PRIuS "Iu"
#endif
#else
#if !defined(PRIuS)
#define PRIuS "zu"
#endif
#endif

#define NUM_PROCESSES 2
#define NUM_PIPES 2
#define LABEL_FORMAT "[%14s] "

#define print_error(fmt, ...) \
	_print_error(__LINE__, GetLastError(), fmt, ##__VA_ARGS__)

#define print_error_and_die(pause, fmt, ...)                     \
  do {                                                           \
    _print_error(__LINE__, GetLastError(), fmt, ##__VA_ARGS__);  \
    if (pause) {                                                 \
      fprintf(stderr,                                            \
        LABEL_FORMAT " Done. Press any key to exit...\n",        \
        "libinteractive");                                       \
      fgetc(stdin);                                              \
    }                                                            \
    exit(1);                                                     \
  } while (FALSE)

const char* interfaces[] = {
	"Main", "Bubble"
};

typedef struct {
	const char* out;
	const char* in;
} pipe_description;

pipe_description pipe_descriptions[NUM_PIPES] = {
	{ "\\\\.\\pipe\\libinteractive_Main_Bubble_out", "\\\\.\\pipe\\libinteractive_Bubble_Bubble_out" },
	{ "\\\\.\\pipe\\libinteractive_Bubble_Bubble_in", "\\\\.\\pipe\\libinteractive_Main_Bubble_in" },
};

char* const commands[] = {
	"\"libinteractive\\Main\\Main.exe\"",
	"\"libinteractive\\Bubble\\Bubble.exe\"",
};
char* const debug_commands[] = {
	"\"libinteractive\\Main\\Main.exe\"",
	"\"gdbserver.exe\" \"127.0.0.1:8042\" \"libinteractive\\Bubble\\Bubble_debug.exe\"",
};
int has_stdin[NUM_PROCESSES] = {
	1, 0
};

typedef struct {
	OVERLAPPED overlapped;
	HANDLE read_fd;
	HANDLE write_fd;
	const char* read_name;
	const char* write_name;
	BOOL connected;
	BOOL closed;
	BOOL pending;
	int pos;
	char buf[1024];
	int line;
	int main_stdout;
	const char* prefix;
} buffer;

typedef struct {
	PROCESS_INFORMATION pi;
	HANDLE out;
	HANDLE err;
} process;

buffer buffers[2 * NUM_PROCESSES + NUM_PIPES];
HANDLE events[2 * NUM_PROCESSES + NUM_PIPES];
process processes[NUM_PROCESSES];
HANDLE processes_and_pipes[NUM_PROCESSES + 1];

static void _print_error(size_t line_number, DWORD error, const char* fmt, ...)
	__attribute__((format (printf, 3, 4)));

static void _print_error(size_t line_number, DWORD error, const char* fmt, ...) {
	va_list arg;

	char buffer[1024];
	va_start(arg, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, arg);
	va_end(arg);

	char error_buffer[1024];
	FormatMessageA(
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		error,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		error_buffer,
		sizeof(error_buffer),
		NULL);

	fprintf(stderr, LABEL_FORMAT " (%s:%" PRIuS ") %s: %s\n",
		"ERROR", __FILE__, line_number, buffer, error_buffer);
	fflush(stderr);
}

// Ensure a buffer is fully written into the fd.
static void write_full(HANDLE fd, const char* buffer, DWORD bytes_read, BOOL pause) {
	BOOL success;
	DWORD bytes_written;
	while (bytes_read) {
		success = WriteFile(
			fd,
			buffer,
			bytes_read,
			&bytes_written,
			NULL
		);
		if (!success || bytes_written == 0) {
			print_error_and_die(pause, "WriteFile");
		}
		bytes_read -= bytes_written;
		buffer += bytes_written;
	}
}

// Once a buffer is read, send it out to its corresponding handle.
// Main's stdout will be highlighted in white instead of gray (unless
// redirected to a pipe or file). All other stdout/stderr will go to
// stderr and will have a nice label.
static void process_buffer(buffer* buf, BOOL pause) {
	if (buf->line) {
		char label[1024];
		_snprintf(label, sizeof(label), LABEL_FORMAT, buf->prefix);
		size_t label_len = strlen(label);
		const char* last = buf->buf;
		const char* end = buf->buf + buf->pos;
		int should_label = GetFileType(buf->write_fd) == FILE_TYPE_CHAR;
		int should_color = buf->main_stdout;
		CONSOLE_SCREEN_BUFFER_INFO color_info;
		if (should_color) {
			GetConsoleScreenBufferInfo(buf->write_fd, &color_info);
		}
		for (const char* pos = buf->buf; pos < end; pos++) {
			if (*pos == '\n') {
				if (should_label) {
					if (should_color) {
						SetConsoleTextAttribute(
							buf->write_fd,
							FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
						);
					}
					write_full(buf->write_fd, label, label_len, pause);
					if (should_color) {
						SetConsoleTextAttribute(
							buf->write_fd,
							color_info.wAttributes
						);
					}
				}
				write_full(buf->write_fd, last, pos - last + 1, pause);
				last = pos + 1;
			}
		}
		if (last == buf->buf) {
			// Nothing written, force flush
			if (should_label) {
				write_full(buf->write_fd, label, label_len, pause);
			}
			write_full(buf->write_fd, buf->buf, buf->pos, pause);
			write_full(buf->write_fd, "\r\n", 2, pause);
			buf->pos = 0;
		} else {
			buf->pos = end - last;
			memmove(buf->buf, last, buf->pos);
		}
	} else {
		write_full(buf->write_fd, buf->buf, buf->pos, pause);
		buf->pos = 0;
	}
}

// A wrapper for CreateProcess. Also redirects stdio.
void execute(size_t i, HANDLE input, BOOL debug, BOOL pause) {
	STARTUPINFOA si;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.hStdInput = has_stdin[i] ? input : INVALID_HANDLE_VALUE;
	si.hStdOutput = processes[i].out;
	si.hStdError = processes[i].err;
	si.dwFlags = STARTF_USESTDHANDLES;
	
	LPTSTR command_line = debug ? debug_commands[i] : commands[i];
	BOOL success = CreateProcessA(
		NULL,
		command_line,
		NULL,
		NULL,
		TRUE,
		0,
		NULL,
		NULL,
		&si,
		&processes[i].pi
	);
	if (!success) {
		print_error_and_die(pause, "CreateProcess %s", command_line);
	}

	// Release our copies of the children's ends of the pipes.
	CloseHandle(processes[i].out);
	CloseHandle(processes[i].err);
}

// Similar to mknod for a pipe.
static HANDLE create_pipe(const char* name, int read, BOOL pause) {
	HANDLE named_pipe = CreateNamedPipeA(
		name,
		read ?
			(PIPE_ACCESS_INBOUND | FILE_FLAG_OVERLAPPED) :
			PIPE_ACCESS_OUTBOUND,
		PIPE_TYPE_BYTE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		1024,
		1024,
		0,
		NULL
	);
	if (named_pipe == INVALID_HANDLE_VALUE) {
		print_error_and_die(pause, "CreateNamedPipe %s", name);
	}
	return named_pipe;
}

// This function should be similar to CreatePipe, but allowing one
// end (the reading end) of the pipe to have overlapped I/O.
static unsigned long long pipe_counter = 0;
static void create_pipe_pair(HANDLE* read, HANDLE* write, BOOL pause) {
	char pipe_name_buffer[1024];
	_snprintf(pipe_name_buffer, sizeof(pipe_name_buffer),
	          "\\\\.\\pipe\\libinteractive_anon_%I64u", pipe_counter++);
	SECURITY_ATTRIBUTES sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = TRUE;
	
	*read = CreateNamedPipeA(
		pipe_name_buffer,
		PIPE_ACCESS_INBOUND | FILE_FLAG_OVERLAPPED,
		PIPE_TYPE_BYTE | PIPE_WAIT,
		1,
		1024,
		1024,
		0,
		&sa
	);
	
	if (!*read || !SetHandleInformation(*read, HANDLE_FLAG_INHERIT, 0)) {
		print_error_and_die(pause, "CreateNamedPipe %s", pipe_name_buffer);
	}
	
	*write = CreateFileA(
		pipe_name_buffer,
		GENERIC_WRITE,
		0,
		&sa,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	
	if (!*write) {
		print_error_and_die(pause, "CreateFile %s", pipe_name_buffer);
	}
}

int run(HANDLE input, BOOL debug, BOOL pause) {
	long maxrss = 0;
	long long utime = 0;

	int retval = 0;
	memset(buffers, 0, sizeof(buffers));
	size_t num_buffers = 0;

	// Create stdout/stderr pipes.
	memset(buffers, 0, sizeof(buffers));	
	for (size_t i = 0; i < NUM_PROCESSES; i++) {
		create_pipe_pair(&buffers[num_buffers].read_fd, &processes[i].out, pause);
		BOOL success = DuplicateHandle(
			GetCurrentProcess(),
			i ?
				GetStdHandle(STD_ERROR_HANDLE) :
				GetStdHandle(STD_OUTPUT_HANDLE),
			GetCurrentProcess(),
			&buffers[num_buffers].write_fd,
			0,
			FALSE,
			DUPLICATE_SAME_ACCESS
		);
		buffers[num_buffers].read_name = interfaces[i];
		buffers[num_buffers].write_name = i ? "stderr" : "stdout";
		if (!success) {
			print_error_and_die(pause, "DuplicateHandle");
		}
		buffers[num_buffers].line = 1;
		buffers[num_buffers].main_stdout = i == 0;
		buffers[num_buffers].prefix = interfaces[i];
		events[num_buffers] = CreateEvent(
			NULL,
			TRUE,
			TRUE,
			NULL
		);
		buffers[num_buffers].overlapped.hEvent = events[num_buffers];
		num_buffers++;
		
		create_pipe_pair(&buffers[num_buffers].read_fd, &processes[i].err, pause);
		success = DuplicateHandle(
			GetCurrentProcess(),
			GetStdHandle(STD_ERROR_HANDLE),
			GetCurrentProcess(),
			&buffers[num_buffers].write_fd,
			0,
			FALSE,
			DUPLICATE_SAME_ACCESS
		);
		if (!success) {
			print_error_and_die(pause, "DuplicateHandle");
		}
		buffers[num_buffers].read_name = interfaces[i];
		buffers[num_buffers].write_name = "stderr";
		buffers[num_buffers].line = 1;
		buffers[num_buffers].prefix = interfaces[i];
		events[num_buffers] = CreateEvent(
			NULL,
			TRUE,
			TRUE,
			NULL
		);
		buffers[num_buffers].overlapped.hEvent = events[num_buffers];
		num_buffers++;
	}

	// Create RPC pipes.
	for (size_t i = 0; i < NUM_PIPES; i++) {
		HANDLE out = create_pipe(pipe_descriptions[i].out, 0, pause);
		HANDLE in = create_pipe(pipe_descriptions[i].in, 1, pause);
		events[num_buffers] = CreateEvent(
			NULL,
			TRUE,
			TRUE,
			NULL
		);
		buffers[num_buffers].overlapped.hEvent = events[num_buffers];
		buffers[num_buffers].read_name = pipe_descriptions[i].out;
		buffers[num_buffers].write_name = pipe_descriptions[i].in;
		buffers[num_buffers].read_fd = in;
		buffers[num_buffers].write_fd = out;
		if (ConnectNamedPipe(buffers[num_buffers].read_fd,
		                     &buffers[num_buffers].overlapped)) {
			print_error_and_die(pause, "ConnectNamedPipe");
		}
		switch (GetLastError()) {
			case ERROR_IO_PENDING:
				buffers[num_buffers].connected = FALSE;
				break;
			case ERROR_PIPE_CONNECTED:
				buffers[num_buffers].connected = TRUE;
				break;
			default:
				print_error_and_die(pause, "ConnectNamedPipe");
		}
		
		num_buffers++;
	}

	// Execute the children.
	for (size_t i = 0; i < NUM_PROCESSES; i++) {
		execute(i, input, debug, pause);

		// Once the child has started, add the child's handle to the table of live
		// processes and pipes.
		processes_and_pipes[i] = processes[i].pi.hProcess;
	}

	// Wait for the children to connect their ends of the pipes.
	size_t alive = num_buffers;
	for (size_t i = 2 * NUM_PROCESSES; i < num_buffers; i++) {
		if (buffers[i].connected) {
			// This should never happen in theory (because the ConnectNamedPipe()
			// function is called before the child process is started), but just for
			// correctness' sake.
			continue;
		}

		// Wait for one pipe. In the event that _any_ process dies before all pipes
		// are connected, we try to detect that here.
		// Since the pipe is added to the very end of the array, once one process
		// dies, any successive WaitForMultipleObjects() calls will also say that a
		// process died instead of the pipe being open.
		processes_and_pipes[NUM_PROCESSES] = buffers[i].overlapped.hEvent;
		DWORD woken = WaitForMultipleObjects(
			NUM_PROCESSES + 1,
			processes_and_pipes,
			FALSE,
			INFINITE
		) - WAIT_OBJECT_0;
		if (woken != NUM_PROCESSES) {
			// One of the processes died :/ Let's keep going to print out any error
			// messages.
			buffers[i].closed = TRUE;
			CloseHandle(buffers[i].read_fd);
			CloseHandle(buffers[i].write_fd);
			ResetEvent(buffers[i].overlapped.hEvent);
			alive--;
			continue;
		}

		DWORD _;
		BOOL success = GetOverlappedResult(
			buffers[i].read_fd,
			&buffers[i].overlapped,
			&_,
			TRUE
		);
		if (!success) {
			print_error("GetOverlappedResult");
			buffers[i].closed = TRUE;
			CloseHandle(buffers[i].read_fd);
			CloseHandle(buffers[i].write_fd);
			ResetEvent(buffers[i].overlapped.hEvent);
			alive--;
			continue;
		}
	}

	if (alive != num_buffers && debug) {
		// At least one process died while waiting for pipe connections.
		// In debug mode, this is most likely due to a bug in gdbserver 8.1.  Just
		// in case, print a helpful debugging message so that folks can decide what
		// to do about it.
		fprintf(stderr,
			LABEL_FORMAT "A process died while initializing.\n",
			"libinteractive");
		fprintf(stderr,
			LABEL_FORMAT "gdbserver.exe 8.1 has a bug that causes this to always fail.\n",
			"libinteractive");
		fprintf(stderr,
			LABEL_FORMAT "you can download a copy of gdbserver 8.0 "
			"from https://s3.amazonaws.com/omegaup-dist/gdbserver-8.0.zip\n",
			"libinteractive");
		fflush(stderr);
	}
	
	// Process I/O on all the pipes until they are all closed.
	while (alive) {
		int i = WaitForMultipleObjects(
			num_buffers,
			events,
			FALSE,
			INFINITE
		) - WAIT_OBJECT_0;
		
		if (i < 0 || i > (num_buffers - 1)) {
			print_error_and_die(pause, "WaitForMultipleObjects");
		}
		
		if (buffers[i].closed) {
			continue;
		}
		
		BOOL success;
		DWORD bytes_read;
		if (buffers[i].pending) {
			success = GetOverlappedResult(
				buffers[i].read_fd,
				&buffers[i].overlapped,
				&bytes_read,
				FALSE
			);
			buffers[i].pending = FALSE;
			if (!success && bytes_read <= 0) {
				buffers[i].closed = TRUE;
				CloseHandle(buffers[i].read_fd);
				CloseHandle(buffers[i].write_fd);
				ResetEvent(events[i]);
				alive--;
				continue;
			}
			buffers[i].pos += bytes_read;
			process_buffer(&buffers[i], pause);
		}
		
		while (1) {
			success = ReadFile(
				buffers[i].read_fd,
				buffers[i].buf + buffers[i].pos,
				sizeof(buffers[i].buf) - buffers[i].pos,
				&bytes_read,
				&buffers[i].overlapped
			);
			
			if (success && bytes_read > 0) {
				buffers[i].pending = FALSE;
				buffers[i].pos += bytes_read;
				process_buffer(&buffers[i], pause);
				continue;
			}
			
			DWORD last_error = GetLastError();
			if (!success && last_error == ERROR_IO_PENDING) {
				buffers[i].pending = TRUE;
				break;
			}
			
			buffers[i].closed = TRUE;
			CloseHandle(buffers[i].read_fd);
			CloseHandle(buffers[i].write_fd);
			ResetEvent(events[i]);
			alive--;
			break;
		}
	}

	// Close all processes and grab execution data.
	for (size_t i = 0; i < NUM_PROCESSES; i++) {
		WaitForSingleObject(processes[i].pi.hProcess, INFINITE);
		FILETIME creation, exit, kernel, user;
		GetProcessTimes(
			processes[i].pi.hProcess,
			&creation,
			&exit,
			&kernel,
			&user
		);
		ULARGE_INTEGER usertime;
		usertime.LowPart = user.dwLowDateTime;
		usertime.HighPart = user.dwHighDateTime;
		utime += usertime.QuadPart / 10;
		
		PROCESS_MEMORY_COUNTERS counters;
		ZeroMemory(&counters, sizeof(counters));
		counters.cb = sizeof(counters);
		GetProcessMemoryInfo(
			processes[i].pi.hProcess,
			&counters,
			sizeof(counters)
		);
		maxrss = max(maxrss, counters.PeakWorkingSetSize);
		DWORD exit_code = 1;
		GetExitCodeProcess(
			processes[i].pi.hProcess,
			&exit_code
		);
		retval = max(retval, exit_code);
			
		CloseHandle(processes[i].pi.hProcess);
		CloseHandle(processes[i].pi.hThread);
	}

	fprintf(stderr, "\nMemory: %7.3f MB\n", maxrss / 1048576.0f);
	fprintf(stderr, "Time:   %7.3f s\n", utime / 1e6);
	fflush(stderr);

	return retval;
}

int main(int argc, char* argv[]) {
	int retval = 0;
	BOOL debug = FALSE;
	BOOL pause = FALSE;
	BOOL from_stdin = TRUE;
	// Try to use the parameters as input filenames.
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--pause") == 0) {
			pause = TRUE;
			continue;
		}
		if (strcmp(argv[i], "--debug") == 0) {
			debug = TRUE;
			continue;
		}
		from_stdin = FALSE;
		SECURITY_ATTRIBUTES sa;
		ZeroMemory(&sa, sizeof(sa));
		sa.nLength = sizeof(sa);
		sa.bInheritHandle = TRUE;
		HANDLE input = CreateFile(
				argv[i],
				GENERIC_READ,
				FILE_SHARE_READ,
				&sa,
				OPEN_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
		if (input == INVALID_HANDLE_VALUE) {
			print_error("CreateFile %s", argv[i]);
			continue;
		}
		fprintf(stderr, "%s:\n", argv[i]);
		fflush(stderr);
		if (run(input, debug, pause) != 0) {
			retval = 1;
		}
		CloseHandle(input);
		fprintf(stderr, "\n");
	}
	// No parameters, use stdin.
	if (from_stdin) {
		retval = run(GetStdHandle(STD_INPUT_HANDLE), debug, pause);
	}
	if (pause) {
		fprintf(stderr,
			LABEL_FORMAT " Done. Press any key to exit...\n",
			"libinteractive");
		fgetc(stdin);
	}
	return retval;
}