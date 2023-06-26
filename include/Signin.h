#ifndef SIGNIN_H
#define SIGNIN_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>
#include "include/Estruturas.h" // Include the "Estruturas.h" header
#include "include/func_leitura.h"

//declaraçoes
Utilizador Registo(Utilizador);
Utilizador Login();
void eliminarUtilizador(const string& nomeFicheiro, const int& idApagar);


#endif //SIGNIN_H