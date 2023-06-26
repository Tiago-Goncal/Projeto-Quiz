
#include "include/Quiz.h"


//declaraçoes
vector<Pergunta> questList;// vetor com a lista de perguntas por tema
unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count(); //numero aleatoria para a funçao shuffle
Utilizador loggedUser;//utilizador com login valido
Utilizador emptyUser;//usado para a versao sem login

//1:Cultura Geral|2:Historia|3:Desporto|4:Cinema
void quizSemUser()
{
    //ler ficheiro com as perguntas
    int pick;
    cout << "\nBem-Vindo" << endl;
    cout << "\nSelecione um tema[1-4](ou selecione 5 para sair): " << endl;
    cout << "\n[1] Cultura Geral.";
    cout << "\n[2] Historia.";
    cout << "\n[3] Desporto.";
    cout << "\n[4] Cinema.";
    cout << ">>>>";
    cin >> pick;

    switch (pick)
    {
    case 1:
        cout << "Cultura Geral: " << endl;
        cout << "\nPrima qualquer tecla para continuar...";
        quizCGeral(emptyUser);
        cin.ignore();
        break;
    case 2:
        cout << "Historia: " << endl;
        cout << "\nPrima qualquer tecla para continuar...";
        cin.ignore();
        break;
    case 3:
        cout << "Desporto: " << endl;
        cout << "\nPrima qualquer tecla para continuar...";
        cin.ignore();
        break;
    case 4:
        cout << "Cinema: " << endl;
        cout << "\nPrima qualquer tecla para continuar...";
        cin.ignore();
        break;
    case 5:
        menu();
        cin.clear();
        cin.ignore();
        break;
    default:
        quizSemUser();
        break;
    }
}

Utilizador quizComUser(Utilizador& loggedUser)
{
    int pick;
    cout << "\nBem-Vindo" << loggedUser.nome << " !" << endl;
    cout << "\nSelecione um tema[1-4](ou selecione 5 para sair): " << endl;
    cout << "\n[1] Cultura Geral.";
    cout << "\n[2] Historia.";
    cout << "\n[3] Desporto.";
    cout << "\n[4] Cinema.";
    cout << ">>>>";
    cin >> pick;

    switch (pick)
    {
    case 1:
        cout << "Cultura Geral: " << endl;
        cout << "\nPrima qualquer tecla para continuar...";
        cin.ignore();
        quizCGeral(loggedUser);
        break;
    case 2:
        cout << "Historia: " << endl;
        cout << "\nPrima qualquer tecla para continuar...";
        cin.ignore();
        break;
    case 3:
        cout << "Desporto: " << endl;
        cout << "\nPrima qualquer tecla para continuar...";
        cin.ignore();
        break;
    case 4:
        cout << "Cinema: " << endl;
        cout << "\nPrima qualquer tecla para continuar...";
        cin.ignore();
        break;
    case 5:
        menu();
        cin.clear();
        cin.ignore();
        break;
    default:
        system("CLS");
        quizComUser(loggedUser);
        break;
    }

    return loggedUser;
}

Utilizador quizCGeral(Utilizador& Usuario)
{
    lerCSV("Perguntas.csv", questList);//ler ficheiro com perguntas
    Pergunta temp;
    vector<Pergunta> culturaGeral;
    string answer;
    int pontos, rightquest;
    
    for (int i = 0;  i < questList.size(); i++) //seleccionar perguntas
    {
        temp = questList[i];
        if (temp.idTema == 1) // verificar se a pergunta e valida para o pedido
        {
            culturaGeral.push_back(temp); // guardar o vetor "cultura geral" para ser usado
        } 
    }

    cout << "\nO quiz de Cultura Geral começa brevemente..." << endl;
    shuffle(culturaGeral.begin(), culturaGeral.end(), seed);//
    cout << "\nPrima qualquer tecla para continuar.";
    cin.clear();
    cin.ignore();

    for (int i = 0; i < 10; i++)//escrever a pergunta
    {
      cout << "\nPergunta #" << i+1 << " : "<< endl;
      cout << culturaGeral.at(i).question << endl;
      cout << culturaGeral.at(i).escolhas[0] << endl;
      cout << culturaGeral.at(i).escolhas[1] << endl;
      cout << culturaGeral.at(i).escolhas[2] << endl;
      cout << culturaGeral.at(i).escolhas[3] << endl;
      getline(cin, answer, ' ');
      //insert timer here.
      if (std::equal(answer.begin(), answer.end(), culturaGeral.at(i).correta.begin(),
      [](char ch1, char ch2) {
      return std::tolower(ch1) == std::tolower(ch2);//isto e uma funçao lambda serve para que a respotas nao queira saber de maisuculas
    }))
        {
           cout << "\nResposta Correta!";
           cout << " ";
           pontos = pontos+5;
           rightquest = rightquest+1;
        }
        else
        {
          cout << "\nResposta Errada!" << endl;
          cout << "a Resposta era:  " <<  culturaGeral.at(i).correta << endl;
          system("CLS");
        }
        
    }

    cout << "\nPontuaçao final: " << pontos << " com "<< rightquest << "perguntas corretas. ";
    //atualizaçao de dados
    Usuario.pontuacao = Usuario.pontuacao + pontos;
    if (Usuario.highScore<pontos)
    {
      Usuario.highScore = pontos;
    }
    Usuario.nJogos = loggedUser.nJogos+1;
    Usuario.totalperguntas = Usuario.totalperguntas+rightquest;   
    guardarDadosUtilizador(Usuario); //guardar a nova entrada no ficheiro
    
    return Usuario;
}


