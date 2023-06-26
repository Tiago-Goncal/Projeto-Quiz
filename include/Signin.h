#ifndef SIGNIN_H
#define SIGNIN_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>
#include "Estruturas.h"//caminho RELATIVO a este ficheiro
#include "func_leitura.h"

//declaraçoes
Utilizador Registo(Utilizador);
Utilizador Login();
void eliminarUtilizador(const std::string& nomeFicheiro, const int& idApagar);


#endif //SIGNIN_H