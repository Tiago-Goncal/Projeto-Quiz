
//Menus de entrada saida e erro
//funcoes menores


#ifndef EXTRAS_H
#define EXTRAS_H


#include <iostream>
#include <chrono>
#include <thread>




void boasVindas();
void error();
void vExit();
//void drawLoadingBar(); //barra de loading com timer de 10 segundos

void boasVindas()
{
    std::cout << "|=========================|" << std::endl;
    std::cout << "|====SEJA BEM-VINDO AO====|" << std::endl;
    std::cout << "|========QUIZ GAME========!" << std::endl;
    std::cout << "|=========================|" << std::endl;
    
    std::cout << "Prima qualquer tecla para continuar" << std::endl;
    std::cin.ignore();
}

void vExit()
{

    //system("CLS");
    std::cout << "==================================================" << std::endl;
    std::cout << "=                Até á próxima!!                 =" << std::endl;
    std::cout << "==================================================" << std::endl<< std::endl;
    
    std::cout << "Prima qualquer tecla para continuar" << std::endl;
    std::cin.ignore();


}

void error()
{

    //system("CLS");
    std::cout << "==================================================" << std::endl;
    std::cout << "=                     ERRO.                      =" << std::endl;
    std::cout << "==================================================" << std::endl<< std::endl;
    
    std::cout << "Prima qualquer tecla para continuar" << std::endl;
    std::cin.ignore();


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