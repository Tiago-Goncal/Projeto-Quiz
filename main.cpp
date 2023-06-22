#include <iostream>
#include <string>
#include <locale.h>

//ficheiros secundarios
#include "Estruturas.hpp"
#include "exit.hpp"
#include "error.hpp"
#include "Signin.hpp"
#include "boasvindas.hpp"
#include "Menuprime.hpp"


using namespace std;



int main()
{
    boasVindas();
    menu();
    cout << "\nh";

    return 0;
}

