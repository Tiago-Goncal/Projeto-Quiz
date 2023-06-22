#include <iostream>
#include <string>

//ficheiros secundarios
#include "Signin.hpp"
#include "boasvindas.hpp"
#include "Menuprime.hpp"
#include "exit.hpp"
#include "error.hpp"

using namespace std;

  struct Utilizador
  {
    string nome;
    string email;
    string password;
    int pontuacao = 0;
    int highScore = 0;
    int nJogos = 0;
    int totalperguntas= 0;
  };


int main()
{
    boasVindas();
    menu();
    cout << "\nh";

    return 0;
}

