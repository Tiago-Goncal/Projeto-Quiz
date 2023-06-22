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

    while(escolha != 4){
    if (login == 0){

    cout << "\nSelecione:" << endl;
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
        vexit();
        break;
    default:
        //error();
        //BRR! Erro
        break;}

    }else if(login == 1){

    cout << "\nSelecione:" << endl;
    cout << "[1]:Iniciar sessão" << endl;
    cout << "[2]:Registar" << endl;
    cout << "[3]:Iniciar jogo" << endl;
    cout << "[4]:Sair" << endl;
    cout << "[5]:Tabela de lideres" << endl << endl;
    cout << ">>>>";
    cin >> escolha;
    switch (escolha){
    case 1:
        system("CLS");
        //Login();
        break;
    case 2:
        system("CLS");
        //Registo(userMestre);
        break;
    case 3:
        system("CLS");
        //Iniciar jogo
        break;
    case 4:
        system("CLS");
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
    }else{
        error();
    }
}
}


#endif // MENUPRIME_H