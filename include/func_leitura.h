#ifndef FUNCLEITURA_H
#define FUNCLEITURA_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Estruturas.h"//caminho RELATIVO a este ficheiro

// Function declarations
void lerUtilizador(std::string& linha, Utilizador& dadosUtilizador);
void lerFicheiroUtilizador(std::string filename, std::vector<Utilizador>& lista);
void guardarDadosUtilizador(const Utilizador& dadosUtilizador);
void lerCSV(const std::string& nomeFicheiro, std::vector<Pergunta>& perguntas);
void lerPergunta(std::string& linha, Pergunta& quiz);

#endif // FUNCLEITURA_H
