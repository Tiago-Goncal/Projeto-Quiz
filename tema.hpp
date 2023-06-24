#ifndef TEMA_H
#define TEMA_H

#include <iostream>

using namespace std;


void tema()
{
    setlocale(LC_ALL,"");
    system("CLS");
    int tema = 0;
    
    cout << "\nEscolha o tema:" << endl;
    cout << "[1]:Cultura Geral" << endl;
    cout << "[2]:Historia" << endl;
    cout << "[3]:Desporto" << endl;
    cout << "[4]:Cinema" << endl;
    cout << ">>>>" << endl;
    cin >> tema;

    switch(tema){
        case 1:
        //Cultura Geral
            break;
        case 2:
        //Historia
            break;
        case 3:
        //Desporto
            break;
        case 4:
        //Cinema
            break;
        default:
        //Erro!
            break;


    }



}

#endif //TEMA_H