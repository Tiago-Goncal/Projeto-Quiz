#include <iostream>
#include <string>
#include <locale.h>

//ficheiros secundarios
#include "Estruturas.hpp"
#include "Signin.hpp"
#include "Extras.hpp"
#include "Quiz.hpp"
#include "Menuprime.hpp"
#include "tema.hpp"



using namespace std;



int main()
{
    setlocale(LC_ALL, " ");
    boasVindas();
    menu();
    cout << "\nh";

    return 0;
}

