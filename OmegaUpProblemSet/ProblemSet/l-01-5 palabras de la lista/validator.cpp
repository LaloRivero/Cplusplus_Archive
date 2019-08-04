#include <bits/stdc++.h>

#define PRNWHERE 1

using namespace std;

string str;
vector<string> word;
set<string> wordlist;

void setscore(double score, int where)
{
	if( PRNWHERE )
		cout << score << " " << where;
	else
		cout << score;
	exit(0);
}

int main()
{
	// no input reading needed

	// try read output
	int countlines = 0;
	while( getline(cin, str) )
		word.push_back(str);
		
		
	// evaluate
	// valid words
	wordlist.insert("PROGRAMACION");
	wordlist.insert("COMPUTADORA");
	wordlist.insert("C/C++");
	wordlist.insert("DIVERSION");
	wordlist.insert("DRAGONBALL");
	wordlist.insert("OLIMPIADA");
	wordlist.insert("FORNITE");
	wordlist.insert("MUSICA");
	wordlist.insert("INFORMATICA");
	wordlist.insert("POKEMON");
	wordlist.insert("VIDEOS");
	wordlist.insert("GUANAJUATO");
	
	// 5 words
	if( word.size() != 5 )
		setscore(0.0, 0);
	// evaluate
	int countbad = 0;
	for( int i = 0; i < 5; i++ )
		if( wordlist.count(word[i]) == 0 )
			countbad++;
		else
			wordlist.erase(word[i]);
		
	// everything it's ok
	setscore(double(5 - countbad)/5.0, 0);
	return 0;
}
