/*
    Tipos de dados 
*/

#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <string>

using namespace std;

  struct Utilizador
  {
    std::string nome = "";
    std::string email = "";
    std::string password = "";
    int pontuacao = 0;
    int highScore = 0;
    int nJogos = 0;
    int totalperguntas= 0;
    int id = 0;
  };

  struct Pergunta
  {
    int id;
    int idTema; //1:Cultura Geral|2:Historia|3:Desporto|4:Cinema
    string question;
    string escolhas[4];
    string correta;

  };

  #endif // ESTRUTURAS_H