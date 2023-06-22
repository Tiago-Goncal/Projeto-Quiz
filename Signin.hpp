/*
Este Ficheiro serve para:

 - lidar com a rececao de dados de utlizador no registo
 - Guardar estes dados num ficheiro de texto
 - ler os dados deste ficheiro na funçao login

  para testar a funcionalidade deve-se usar uma diretiva inlcude to main.cpp

  #include "Signin.hpp"

*/

#ifndef SIGNIN_HPP
#define SIGNIN_HPP

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

  //definiçao da estrutura "user

//declaraçoes
//void MenuUtilizador();
Utilizador Registo(Utilizador);
void Login();
void guardarDadosUtilizador(const Utilizador&);

/*
void MenuUtilizador()
{
  int escolha;
  Utilizador userMestre;

  while (escolha!=3)
  {
    cout << "\n----------------------------------------------";
    cout << "\nSelecione uma opçao:";
    cout << "\n1: Registo: ";
    cout << "\n2: Login: ";
    cout << "\n3: Sair ";
    cout << "\n----------------------------------------------";
    cin.ignore();
    }

    switch (escolha)
    {
    case 1:
      //Registo
      Registo(userMestre);
      break;
    case 2:
      //login
      break;
    case 3:
      //sair
      break;
    
    default:
      //erro
      break;
    }
 */   

   


//guardar dados no ficheiro
void guardarDadosUtilizador(const Utilizador& userMestre)
{
  ofstream file("Dados_utilizador.txt");//criar ficheiro
  if (file.is_open())//esta aberto? se sim, entao escrever.
  {
    file << "Nome: " << userMestre.nome << endl;
    file << "Email: " << userMestre.email << endl;
    file << "Password: " << userMestre.password << endl;
    file << endl;
    file.close();
    cout <<"\nDados guardados";
  }
  else
  {
    cerr << "Ficheiro falhou a abrir.";
  }
  
};

//registo: implementaçao
Utilizador Registo(Utilizador)
{
  Utilizador dadosUtilizador;

  cout << "\nRegisto: ";
  cout << "\nNome: ";
  getline(cin, dadosUtilizador.nome);
  cout << "\nEmail: ";
  getline(cin, dadosUtilizador.email);
  cout << "\nPassword: ";
  getline(cin, dadosUtilizador.password);

  if (dadosUtilizador.nome.length()== 0 || 
  dadosUtilizador.email.length()== 0 || dadosUtilizador.password.length()== 0)
  {
    cout << "\nCampo obrigatorios estao vazios. ";
    cout << "\nPrima qualquer tecla para continuar...";
    Registo(dadosUtilizador);
  }
  else if(dadosUtilizador.email.find('@') == string::npos && 
  dadosUtilizador.email.find('.com') == string::npos)
  {
    cout << "\nEmail Não valido.";
    cout << "\nPrima qualquer tecla para continuar...";
    Registo(dadosUtilizador);
  }
  else
  {
    guardarDadosUtilizador(dadosUtilizador);
  }

  return dadosUtilizador;
}



void Login()
{

}

#endif //SIGNIN