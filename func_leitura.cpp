#include "func_leitura.h"

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