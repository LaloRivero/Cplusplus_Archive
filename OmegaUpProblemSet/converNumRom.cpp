#include <iostream>
using namespace std;
int num;
int uni, dece, cen, mil;

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>num;
    uni  = num%10;
    dece = num%100 - uni;
    cen  = num%1000 - dece - uni;
    mil  = num%10000 - cen - dece - uni;

    //Mostramos los millares
    if(mil == 1000){
        cout<<"M";
    }else if(mil == 2000){
        cout<<"MM";
    }else if(mil == 3000){
        cout<<"MMM";
    } 

///Mostramos las centenas
    if(cen==100){
        cout<<"C";
    }
    if(cen==200){
        cout<<"CC";
    }
    if(cen==300){
        cout<<"CCC";
    }
    if(cen==400){
        cout<<"CD";
    }
    if(cen==500){
        cout<<"D";
    }
    if(cen==600){
        cout<<"DC";
    }
    if(cen==700){
        cout<<"DCC";
    }
    if(cen==800){
        cout<<"DCCC";
    }
    if(cen==900){
        cout<<"CM";
    }

///Mostramos las decenas
    if(dece==10){
        cout<<"X";
    }
    if(dece==20){
        cout<<"XX";
    }
    if(dece==30){
        cout<<"XXX";
    }
    if(dece==40){
        cout<<"XL";
    }
    if(dece==50){
        cout<<"L";
    }
    if(dece==60){
        cout<<"LX";
    }
    if(dece==70){
        cout<<"LXX";
    }
    if(dece==80){
        cout<<"LXXX";
    }
    if(dece==90){
        cout<<"XC";
    }

///Mostramos las unidades
    if(uni==1){
        cout<<"I";
    }
    if(uni==2){
        cout<<"II";
    }
    if(uni==3){
        cout<<"III";
    }
    if(uni==4){
        cout<<"IV";
    }
    if(uni==5){
        cout<<"V";
    }
    if(uni==6){
        cout<<"VI";
    }
    if(uni==7){
        cout<<"VII";
    }
    if(uni==8){
        cout<<"VIII";
    }
    if(uni==9){
        cout<<"IX";
    } 
}