/*
Este Ficheiro serve para:

 - lidar com a rececao de dados de utlizador no registo
 - Guardar estes dados num ficheiro de texto
 - ler os dados deste ficheiro na funçao login
 - lidar com a eliminaçao de utilizadores

  para testar a funcionalidade deve-se usar uma diretiva include to main.cpp

  #include "Signin.hpp"

*/


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>
#include "Signin.h"

using namespace std;

//declaraçoes


//variaveis

vector<Utilizador> lista;
Utilizador dadosUtilizador;
vector<Pergunta> quizquestions;

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
    return;
  }
  

}
//registo: implementaçao
Utilizador Registo(Utilizador)
{
  //Utilizador dadosUtilizador;
  string tempPass;

  cout << "\nRegisto: ";
  cout << "\nNome: ";
  getline(cin, dadosUtilizador.nome);
  cout << "\nEmail: ";
  getline(cin, dadosUtilizador.email);
  cout << "\nPalavrapasse: ";
  getline(cin, dadosUtilizador.password);
  cout << "\nConfirme a palavra passe: ";
  getline(cin, tempPass);
  if (tempPass != dadosUtilizador.password || tempPass.length()==0)
  {
    cout << "\nPalavra passe nao confirmada";
    tempPass.clear();
    Registo(dadosUtilizador);
  }
  else
  {
    cout << "\nPalavra passe Confirmada.";
  }
  

  if (dadosUtilizador.nome.length()== 0 || 
  dadosUtilizador.email.length()== 0 || dadosUtilizador.password.length()== 0)
  {
    cout << "\nCampos obrigatorios estao vazios. ";
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
  
//Login
//passos
//1:receber os dados od utilizador
//2:confirmar se estes sao validos
//3:carregar os ficheiro com os dados de utilizador
//4:comparar com o registo
Utilizador Login()
{
  Utilizador dadoslogin;

  system("CLS");
  cout << "\nLogin: ";
  cout << "\nNome: ";
  getline(cin, dadoslogin.nome);
  cout << "\nEmail: ";
  getline(cin, dadoslogin.email);
  cout << "\nPassword: ";
  getline(cin, dadoslogin.password);
  //campos vazios
  if (dadoslogin.nome.length()== 0 || dadoslogin.email.length()== 0 || dadoslogin.password.length()== 0)
  {
    cout << "\nCampos obrigatorios estão vazios" << endl;
    //limpar variavel
    dadoslogin.nome.clear();
    dadoslogin.email.clear();
    dadoslogin.password.clear();
    Login();
  }
  else
  {
    //ler e procurar se os valores introduzidos correspondem a um utilizador valido
    int encontrado = 0;
    lerFicheiroUtilizador("Dados_utilizadores.txt",lista);
    for (const Utilizador& temp : lista)
    {
      if (temp.nome == dadoslogin.nome && temp.email == dadoslogin.email && temp.password == dadoslogin.password)
      {
        //utilizador encontrado, reter a estrutura para uso futuro
        encontrado = 1;
        cout << "\nUtilizador encontrado. "<< endl;
        cout << "\nBem Vindo " <<  dadoslogin.nome << endl;
        cout << "Prima qualquer tecla para continuar" << endl;
        cin.ignore();
        return temp;
      }
      else
      {
        //utlizador nao encontrado, retornar uma estrutura vazia.
        cout << "\nUtilizador não encontrado. "<< endl;
        cout << "Prima qualquer tecla para continuar" << endl;
        cin.ignore();
        return Utilizador();
      }
    }
  }
  cout << endl;
  

}

void lerCSV(const string& nomeFicheiro ,vector<Pergunta>perguntas)
{
  ifstream instream;
  instream.open("Perguntas.csv");
  if (instream.is_open())
  {
    string line;
    while (getline(instream, line, ','))
    {
      Pergunta tempPergunta;
      lerPergunta(line, tempPergunta);
      perguntas.push_back(tempPergunta);
    }
  }
  else
  {
    cout << "\nFicheiro falhou a abrir.";
    return;
  } 
}

void lerPergunta(string& linha, Pergunta& quiz)
{
  stringstream is;
  string temp;
  int cont;
  while (getline(is ,linha,','))
  {
    if (cont == 0)
    {
      quiz.id = atoi(temp.c_str());
    }
    else if (cont == 1)
    {
      quiz.idTema = atoi(temp.c_str());
    }
    else if (cont == 2)
    {
      quiz.escolhas[0] = temp;
    }
     else if (cont == 3)
    {
      quiz.escolhas[1] = temp;
    }
     else if (cont == 4)
    {
      quiz.escolhas[2] = temp;
    }
     else if (cont == 5)
    {
      quiz.escolhas[3] = temp;
    }
     else if (cont == 6)
    {
      quiz.correta = temp;
    }
    ++cont;  
  }
}

