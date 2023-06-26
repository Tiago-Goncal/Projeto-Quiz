#include <iostream>
#include <string>
#include <locale.h>
#include <conio.h>
#include <vector>
#include <algorithm>

//ficheiros secundarios
#include "Estruturas.h"
#include "Signin.h"
#include "Extras.h"
#include "Quiz.h"


using namespace std;


void menu();

int main()
{
    setlocale(LC_ALL, " ");
    boasVindas();
    menu();

    return 0;
}


