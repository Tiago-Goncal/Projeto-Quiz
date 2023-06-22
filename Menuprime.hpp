#ifndef MENUPRIME_H
#define MENUPRIME_H

#include <iostream>
#include <conio.h>

using namespace std;


void menu()
{
    system("CLS");
    int escolha = 0;
    int login;

    cout << "\nLogin status[0- 1]:" << endl;
    cin >> login;
    cin.ignore();


    Utilizador userMestre;

    while(escolha != 5){
    if (login == 0){

    cout << "\nSeleccione:" << endl;
    cout << "[1]:Iniciar jogo" << endl;
    cout << "[2]:Tabela de lideres" << endl;
    cout << "[3]:Eliminar utilizador" << endl;
    cout << "[4]:Sair" << endl << endl;
    cout << ">>>>";
    cin >> escolha;
    switch (escolha){
    case 1:
        system("CLS");
        //Iniciar jogo
        break;
    case 2:
        system("CLS");
        //Tabela de lideres
        break;
    case 3:
        system("CLS");
        //Eliminar utilizador
        break;
    case 4:
        system("CLS");
        exit();
        break;
    default:
        //error();
        //BRR! Erro
        break;}

    }else{

    cout << "\nSeleccione:" << endl;
    cout << "[1]:Iniciar sessão" << endl;
    cout << "[2]:Registar" << endl;
    cout << "[3]:Iniciar jogo" << endl;
    cout << "[4]:Tabela de lideres" << endl;
    cout << "[5]:Sair" << endl << endl;
    cout << ">>>>";

    switch (escolha){

    case 1:
        system("CLS");
        //Iniciar sessão
        break;
    case 2:
        system("CLS");
        Registo(userMestre);
        break;
    case 3:
        system("CLS");
        //Iniciar jogo
        break;
    case 4:
        system("CLS");
        //Tabela de lideres
        break;
    case 5:
        system("CLS");
        //exit();
        break;
    default:
        //error();
        //BRR! Erro
        break;
    }
    }
}
}


#endif // MENUPRIME_H