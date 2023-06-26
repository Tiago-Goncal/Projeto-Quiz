#ifndef QUIZ_H
#define QUIZ_H

#include <iostream>
#include <chrono>
#include <algorithm>
#include <cctype>
#include <vector>
#include "include\Estruturas.h"
#include "include/func_leitura.h"
#include "include/Menu.h"


void quizSemUser();
Utilizador quizComUser(Utilizador& loggedUser);
Utilizador quizCGeral(Utilizador& Usuario);

#endif // QUIZ_H