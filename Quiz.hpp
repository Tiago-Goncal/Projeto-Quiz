#ifndef QUIZ_H
#define QUIZ_H

#include <iostream>

//declaraçoes
void quizSemUser();
Utilizador quizComUser(Utilizador& loggedUser);


//1:Cultura Geral|2:Historia|3:Desporto|4:Cinema
void quizSemUser()
{
    //ler ficheiro com as perguntas
    int escolha;
    cout << "\nBem-Vindo" << endl;
    cout << "\nSelecione um tema[1-4](ou selecione 5 para sair): " << endl;
    cout << "\n[1] Cultura Geral.";
    cout << "\n[2] Historia.";
    cout << "\n[3] Desporto.";
    cout << "\n[4] Cinema.";
    cout << ">>>>"

    switch (escolha)
    {
    case 1:
        cout << "Cultura Geral: " << endl;
        cout << "\nPrima qualquer tecla para continuar...";
        cin.ignore();
        break;
    case 2:
        cout << "Historia: " << endl;
        cout << "\nPrima qualquer tecla para continuar...";
        cin.ignore();
        break;
    case 3:
        cout << "Desporto: " << endl;
        cout << "\nPrima qualquer tecla para continuar...";
        cin.ignore();
        break;
    case 4:
        cout << "Cinema: " << endl;
        cout << "\nPrima qualquer tecla para continuar...";
        cin.ignore();
        break;
    case 5:
        menu();
        cin.clear();
        cin.ignore();
        break;
    default:
        quizSemUser();
        break;
    }
}



#endif //QUIZ_H