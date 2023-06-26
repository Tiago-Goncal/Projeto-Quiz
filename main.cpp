#include <iostream>
#include <string>
#include <locale.h>
#include <conio.h>
#include <vector>
#include <algorithm>

//ficheiros secundarios
#include "Estruturas.h"
#include "Signin.hpp"
#include "Extras.hpp"
#include "Quiz.hpp"
//#include "Menuprime.hpp"




using namespace std;

void menu();

Utilizador loggedUser;


int main()
{
    setlocale(LC_ALL, " ");
    boasVindas();
    menu();
    cout << "\nh";

    return 0;
}

void menu()
{
    system("CLS");
    int escolha = 0;
    int loginstatus;
    Utilizador userMestre;
  
  
    while(escolha != 4)
    {
    cout << "\nSelecione:" << endl;
    cout << "[1]:Iniciar sessão" << endl;
    cout << "[2]:Registar" << endl;
    cout << "[3]:Iniciar jogo" << endl;
    cout << "[4]:Sair" << endl;
    cout << "[5]:Tabela de lideres" << endl;
    cout << ">>>>" << endl;
    cin >> escolha;
    switch (escolha){
    case 1:
      {
        system("CLS");
        loggedUser = Login();
        break;
      }
    case 2:
      {
        system("CLS");
        Registo(userMestre);
        break;
      }
    case 3:
      {
        system("CLS");
        //Iniciar jogo
        if (loginstatus == 0)
        {
            quizSemUser();
        }
        else if (loginstatus == 1)
        {
            quizComUser(loggedUser);
        }
        break;
      }
    case 4:
      {
        //system("CLS");
        vexit();
        break;
      }
    case 5:
      {
        system("CLS");
        //Tabela de lideres
        break;
      }
    default:
      { 
        //error();
        //BRR! Erro
        break;
      }
    }
}

}

