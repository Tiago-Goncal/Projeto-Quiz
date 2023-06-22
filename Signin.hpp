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
#include <sstream>
#include <vector>

using namespace std;

  //definiçao da estrutura "user

//declaraçoes
//void MenuUtilizador();
Utilizador Registo(Utilizador);
void Login();
void guardarDadosUtilizador(const Utilizador&);

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
  
}

//esta funçao le o fichiro de texto linha a linha
void lerUtilizador(string& linha, Utilizador& userMestre)
{
  stringstream is(linha);
  string temp;
  int cont;

  while (getline(is, temp, ' '))
  {
    if (cont = 0)
    {
      userMestre.nome = temp;
    }
    else if (cont = 1)
    {
      userMestre.email = temp;
    }
    else if (cont = 2)
    {
      userMestre.password = temp;
    }
    else if (cont = 3)
    {
      userMestre.pontuacao = atoi(temp.c_str());
    }
    else if (cont = 4)
    {
      userMestre.highScore = atoi(temp.c_str());
    }
    else if (cont = 5)
    {
      userMestre.nJogos = atoi(temp.c_str());
    }
    else if (cont = 6)
    {
      userMestre.totalperguntas = atoi(temp.c_str());
    }

    ++cont;
  }
}
//ler o ficheiro com os dados de utilizador
void lerFicheiroUtilizador(string filename,vector<Utilizador>& lista)
{
  ifstream instream;
  instream.open("Dados_utilizador.txt");

  if (instream)//verifica se o ficheiro esta aberto
  {
    string line;
    while (getline(instream, line, '\n'))
    {
      Utilizador novoutilizador;

      lerUtilizador(line,novoutilizador);
      
      lista.push_back(novoutilizador);
    }
    
    instream.close();
    cout << "\n" << (to_string(lista.size())) + " Utilizadores registados. ";
  }

  else
  {
    cout << "\nFicheiro falhou a abrir";
  }
  

}

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
  dadosUtilizador.email.find('.') == string::npos)
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

  cout << "\nLogin: ";
  cout << endl;

}

#endif //SIGNIN