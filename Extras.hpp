/*
Menus de entrada saida e erro
*/

#ifndef EXTRAS_H
#define EXTRAS_H


#include <iostream>

using namespace std;


void boasVindas();
void error();
void vexit();

void boasVindas()
{

    cout << "|=========================|" << endl;
    cout << "|====SEJA BEM-VINDO AO====|" << endl;
    cout << "|========QUIZ GAME========!" << endl;
    cout << "|=========================|" << endl;
    
    cout << "Prima qualquer tecla para continuar" << endl;
    cin.ignore();


}

void vexit()
{

    //system("CLS");
    cout << "==================================================" << endl;
    cout << "=                Até á próxima!!                 =" << endl;
    cout << "==================================================" << endl<< endl;
    
    cout << "Prima qualquer tecla para continuar" << endl;
    cin.ignore();


}

void error()
{

    //system("CLS");
    cout << "==================================================" << endl;
    cout << "=                     ERRO.                      =" << endl;
    cout << "==================================================" << endl<< endl;
    
    cout << "Prima qualquer tecla para continuar" << endl;
    cin.ignore();


}



#endif// BOAS VINDAS_H