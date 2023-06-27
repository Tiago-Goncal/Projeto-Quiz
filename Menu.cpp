#include "include/Menu.h"


extern Utilizador loggedUser;//declarada em quiz, guarda o utilizador logado
extern Utilizador dadosUtilizador;//declarada em signin recebe os dados para um novo registo

//definiçao
int menuPrincipal() //isto esta a ser visto como declaraçao em vez de definiçao
{
    system("CLS");
    int escolha = 0;
    int loginstatus = 0;
    

    while (escolha != 4)
    {
        std::cout << "\nSelecione:" << std::endl;
        std::cout << "[1]:Iniciar sessão" << std::endl;
        std::cout << "[2]:Registar" << std::endl;
        std::cout << "[3]:Iniciar jogo" << std::endl;
        std::cout << "[4]:Sair" << std::endl;
        std::cout << "[5]:Tabela de lideres" << std::endl;
        std::cout << ">>>>" << std::endl;
        std::cin >> escolha;

        switch (escolha)
        {
            case 1:
            
                system("CLS");
                loggedUser = Login();
                if (loggedUser==Utilizador())//esta comparaçao utiliza uma versao do operador == definida no header Estruturas.h
                {
                    loginstatus = 0;
                    menuPrincipal();
                }
                else
                {
                    loginstatus = 1;
                    menuPrincipal();
                }
                
                break;
            
            case 2:
            
                system("CLS");
                Registo(dadosUtilizador);
                break;
            
            case 3:
            
                system("CLS");
                //Iniciar jogo
                if (loginstatus == 0)
                {
                    quizSemUser();
                }
                else if (loginstatus == 1)
                {
                    quizComUser(loggedUser);
                }
                break;
            
            case 4:
            
                //system("CLS");
                vExit();
                break;
            
            case 5:
            
                system("CLS");
                //Tabela de lideres
                break;
            
            default:
            
                error();
                //BRR! Erro
                break;
            
        }
    }
    return 0;
}