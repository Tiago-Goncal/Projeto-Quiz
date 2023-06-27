
#include "include/lider.h"


int maiorpontuacao(Utilizador a, Utilizador b)
{
    return a.pontuacao < b.pontuacao;
}

void tabelaLider()

{
    int escolha;
    std::vector<Utilizador> leader;
    std::vector<Utilizador> sortedLeader;
    Utilizador ranker;
    lerFicheiroUtilizador("Dados_utilizador.txt",leader);

    for (int i = 0; i < leader.size(); i++)
    {
       sortedLeader.at(i) = leader.at(i); 
       sortedLeader.push_back(ranker);
    }
    //organizar os valores do vecotr baseado em pontuaçao total
    //std::sort(sortedLeader.begin(), sortedLeader.end(),maiorpontuacao(sortedLeader.));
    std::cout << "\nLeaderboard: ";
    std::cout << "\n[1]: Ver.";
    std::cout << "\n[2]: Sair.";
    std::cin >> escolha;

    switch (escolha)
    {
    case 1:
         for (int i = 0; i < 2; i++)
        {
            std::cout << "\n" << i+1  << ": "<< sortedLeader[i].nome << "\nPontos: " << sortedLeader[i].pontuacao
            << "\nMelhor pontuacao: " << sortedLeader[i].highScore << "\n# de jogos: " << sortedLeader[i].nJogos;
            std::cout << std::endl << std::endl; 
        }
        break;
    
    case 2:

    default:
        break;
    }
   
    


    


}

