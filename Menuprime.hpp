#ifndef MENUPRIME_H
#define MENUPRIME_H

#include <iostream>
#include <conio.h>

using namespace std;


void menu()
{
    setlocale(LC_ALL,"");
    system("CLS");
    int escolha = 0;
    int loginstatus = 1;
    Utilizador userMestre;
    /*
    esta variavel serve para capturar o valor da funçao login e deve ser usado para escolher qual o menu a usar
    (loged or nao logado)
    a minha recomedaçao e que os menus sejam separados em versoes, com  e sem login, possivelmente mover este bloco todo para main
    */
    
    

    //cout << "\nLogin status[0- 1]:" << endl;
    //cin >> loginstatus;
    //cin.ignore();



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
        system("CLS");
        Utilizador loggedUser = Login();
        break;
    case 2:
        system("CLS");
        Registo(userMestre);
        break;
    case 3:
        system("CLS");
        //Iniciar jogo
        if (loginstatus == 0)
        {
            quizSemUser();
        }
        else if (loginstatus == 1)
        {
            /* code */
        }
        else
        {

        }
        
        
        break;
    case 4:
        //system("CLS");
        vexit();
        break;
    case 5:
        system("CLS");
        //Tabela de lideres
        break;
    default:
        //error();
        //BRR! Erro
        break;
    }
}



}




#endif // MENUPRIME_H