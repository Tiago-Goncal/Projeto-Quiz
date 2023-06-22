/*
    Tipos de dados 
*/

#ifndef ESTRUTURAS_H
#define  ESTRUTURAS_H

#include <string>

  struct Utilizador
  {
    std::string nome;
    std::string email;
    std::string password;
    int pontuacao = 0;
    int highScore = 0;
    int nJogos = 0;
    int totalperguntas= 0;
  };


  #endif // ESTRUTURAS