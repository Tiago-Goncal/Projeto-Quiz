#include <iostream>
#include <string>
#include <locale.h>
#include <conio.h>
#include <vector>
#include <algorithm>

//ficheiros secundarios
#include "include/Estruturas.h"
#include "include/func_leitura.h"
#include "include/Menu.h"
#include "include/Signin.h"
#include "include/Extras.h"
#include "include/Quiz.h"


using namespace std;


int main()
{
    setlocale(LC_ALL, " ");
    boasVindas();
    menuPrincipal();

    return 0;
}


