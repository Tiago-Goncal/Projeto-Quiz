/*
Este Ficheiro serve para:

 - lidar com a rececao de dados de utlizador no registo
 - Guardar estes dados num ficheiro de texto
 - ler os dados deste ficheiro na funçao login
 - lidar com a eliminaçao de utilizadores

  para testar a funcionalidade deve-se usar uma diretiva include to main.cpp

  #include "Signin.hpp"

*/

#ifndef SIGNIN_HPP
#define SIGNIN_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>

using namespace std;

//declaraçoes
Utilizador Registo(Utilizador);
void Login();
void lerUtilizador(string& linha, Utilizador& userMestre);
void guardarDadosUtilizador(const Utilizador&);
void eliminarUtilizador(const string& nomeFicheiro, const int& idApagar);

//variaveis

vector<Utilizador> lista;
Utilizador dadosUtilizador;

//guardar dados no ficheiro
void guardarDadosUtilizador(const Utilizador& dadosUtilizador)
{
  ofstream file("Dados_utilizador.txt");//criar ficheiro
  if (file.is_open())//esta aberto? se sim, entao escrever.
  {
    file << "Nome: " << dadosUtilizador.nome << endl;
    file << "Email: " << dadosUtilizador.email << endl;
    file << "Password: " << dadosUtilizador.password << endl;
    file << "UltimaPontuaçao: " << dadosUtilizador.pontuacao << endl;
    file << "PontuaçaoMaxima: " << dadosUtilizador.highScore << endl;
    file << "NumerodeJogos: " << dadosUtilizador.nJogos << endl;
    file << "TotalPontos: " << dadosUtilizador.totalperguntas << endl;
    file << "ID: " << dadosUtilizador.id << endl;
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
void lerUtilizador(string& linha, Utilizador& dadosUtilizador)
{
  stringstream is(linha);
  string temp;
  int cont;

  while (getline(is, temp, ' '))
  {
    if (cont = 0)
    {
      dadosUtilizador.nome = temp;
    }
    else if (cont = 1)
    {
      dadosUtilizador.email = temp;
    }
    else if (cont = 2)
    {
      dadosUtilizador.password = temp;
    }
    else if (cont = 3)
    {
      dadosUtilizador.pontuacao = atoi(temp.c_str());
    }
    else if (cont = 4)
    {
      dadosUtilizador.highScore = atoi(temp.c_str());
    }
    else if (cont = 5)
    {
      dadosUtilizador.nJogos = atoi(temp.c_str());
    }
    else if (cont = 6)
    {
      dadosUtilizador.totalperguntas = atoi(temp.c_str());
    }
    else if (cont = 7)
    {
      dadosUtilizador.id = atoi(temp.c_str());
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
  //Utilizador dadosUtilizador;

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
    cin.ignore();
    Registo(dadosUtilizador);
  }
  else if(dadosUtilizador.email.find('@') == string::npos && 
  dadosUtilizador.email.find('.') == string::npos)
  {
    cout << "\nEmail Não valido.";
    cout << "\nPrima qualquer tecla para continuar...";
    cin.ignore();
    Registo(dadosUtilizador);
  }
  else
  {
    dadosUtilizador.id= dadosUtilizador.id+1;
    guardarDadosUtilizador(dadosUtilizador);
  }

  return dadosUtilizador;
}

void eliminarUtilizador(const string& nomeficheiro, const int& idApagar)
{
  ifstream ficheiro("Dados_utilizador.txt");
  if (!ficheiro) //o ficheiro falhou a abrir
  {
    cout << "Ficheiro nao encontrado." << endl;
    return;
  }
  //ler
  while (ficheiro >> dadosUtilizador.nome >> dadosUtilizador.email >> 
  dadosUtilizador.password >> dadosUtilizador.pontuacao >> dadosUtilizador.highScore >> 
  dadosUtilizador.nJogos >> dadosUtilizador.totalperguntas >> dadosUtilizador.id)
  {
    lista.push_back(dadosUtilizador);
  }
  ficheiro.close();

  //Criaçao de um ficheiro temporario para mainpulaçao segura
  ofstream tempfile("Tempfile.txt"); 
  if (!tempfile) //o ficheiro falhou a abrir
  {
    cout << "Ficheiro nao pode ser criado." << endl;
    return;
  }
  //percorrer o vetor e procurar o id selecionado
  int encontrado=0;//esta valor passa a ser1 se o id for encontrado

  for (size_t i = 0; i < lista.size(); i++)
  {
    if (lista[i].id == idApagar)
    {
       encontrado = 1;
       lista.erase(lista.begin()+ i);
       break;
    }
  }
  if (encontrado = 1)
  {
    for (size_t i = 0; i < lista.size(); i++)
    {
      lista[i].id = i + 1;
      //escrever no ficheiro temporario
      tempfile << "Nome: " << lista[i].nome << endl;
      tempfile << "Email: " << lista[i].email << endl;
      tempfile << "Password: " << lista[i].password << endl;
      tempfile << "UltimaPontuacao: " << lista[i].pontuacao << endl;
      tempfile << "PontuacaoMaxima: " << lista[i].highScore << endl;
      tempfile << "NumerodeJogos: " << lista[i].nJogos << endl;
      tempfile << "TotalPontos: " << lista[i].totalperguntas << endl;
      tempfile << "ID: " << lista[i].id << endl;
      tempfile << endl; 
    }
  }
  else
  {
    cout << "Utilizador com o ID " << idApagar << " não existe." << endl;
  }
  //fechar ficheiro temporario
  tempfile.close();

  //apagar o ficheiro antigo e renomear o temporario com os novos dados
  if (remove(nomeficheiro.c_str())!= 0)
  {
    cout << "Erro a apagar ficheiro" << endl;
    return;
  }
  if (rename("Tempfile.txt", nomeficheiro.c_str()) != 0) 
  {
    cout << "Erro a renomear ficheiro" << endl;
    return;
  }
  //confirmaçao
  cout << "Utilizador com o ID " << idApagar << " removido." << endl;
}
  



void Login()
{

  cout << "\nLogin: ";
  cout << endl;
  

}

#endif //SIGNIN