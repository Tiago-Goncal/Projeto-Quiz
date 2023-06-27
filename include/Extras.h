
//Menus de entrada saida e erro
//funcoes menores


#ifndef EXTRAS_H
#define EXTRAS_H


#include <iostream>
#include <chrono>
#include <thread>

using namespace std;


void boasVindas();
void error();
void vExit();
void drawLoadingBar(); //barra de loading com timer de 10 segundos

void boasVindas()
{

    cout << "|=========================|" << endl;
    cout << "|====SEJA BEM-VINDO AO====|" << endl;
    cout << "|========QUIZ GAME========!" << endl;
    cout << "|=========================|" << endl;
    
    cout << "Prima qualquer tecla para continuar" << endl;
    cin.ignore();


}

void vExit()
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
/*
void drawLoadingBar()
{
    const int barWidth = 70;
    std::cout << "Tempo: [";
    for (int i = 0; i <= barWidth; ++i)
    {
        std::cout << ".";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "]\n";
}
*/


#endif// BOAS VINDAS_H