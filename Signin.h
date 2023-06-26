#ifndef SIGNIN_H
#define SIGNIN_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>
#include "Estruturas.h" // Include the "Estruturas.h" header

//declaraçoes
Utilizador Registo(Utilizador);
Utilizador Login();
void lerUtilizador(string& linha, Utilizador& userMestre);
void lerFicheiroUtilizador(string filename,vector<Utilizador>& lista);
void guardarDadosUtilizador(const Utilizador&);
void eliminarUtilizador(const string& nomeFicheiro, const int& idApagar);
void lerPergunta(string& linha, Pergunta& quiz);
void lerCSV(const string& nomeFicheiro,vector<Pergunta>perguntas);

#endif //SIGNIN_H