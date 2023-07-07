#include <iostream>
#include <locale>
#include <string>
#include <chrono> //funçoes relacionada a temporizaçao
#include <fstream>
#include <sstream>
#include <vector> 
#include <cstdio> // I/O do estilo de C
#include <cstdlib>
#include <cctype> //classes para lidar com manipulacao de carateres
#include <algorithm> 
#include <thread> //classes para lidar com multiplas linhas de execuçao
#include <mutex>  //classes para transitar entre linhas de execuçao de forma segura
#include <atomic> //classes para gerar variaveis capazes the interagir entre linhas de execuçao diferentes
#include <future> //async

#include <include/Estruturas.h>

using namespace std;

//algumas das funçoes requrem que estes nomes sejam chamados explicitamente
using std::cout;
using std::cin;
using std::vector;

//ESTRUTURAS:H------------------------------------------------------------------
//Esta estrutura representa a forma do objecto "utilizador", esquematizado aqui para que possa ser guardado de forma organizada
struct Utilizador 
  {
    std::string nome = "";
    std::string email = "";
    std::string password = "";
    int pontuacao = 0;
    int highScore = 0;
    int nJogos = 0;
    int totalperguntas= 0;
    int id = 0;

    //overload do operador ==, necessario para poder comparar instancias da estrutura diretamente
    //sem esta funcionalidade os membros teriam de ser comparados indivdualmente
    bool operator==(const Utilizador& other) const
      {
      return (nome == other.nome &&
              email == other.email &&
              password == other.password &&
              pontuacao == other.pontuacao &&
              highScore == other.highScore &&
              nJogos == other.nJogos &&
              totalperguntas == other.totalperguntas &&
              id == other.id);   
      }
  };
  //formato do objecto "pergunta"
  struct Pergunta
  {
    int id;
    int idTema; //1:Cultura Geral|2:Historia|3:Desporto|4:Cinema
    std::string question;
    std::string escolhas[4];
    std::string correta;
  };

/*Declaraçoes de Variaveis e funçoes*/
bool CompareNomeEmailPassword(const Utilizador& lhs, const Utilizador& rhs); //comaparaçao dos 3 campos string de Utilizador

//------------------------------------------------------------------------------
//declara�oes de Extras.h
void boasVindas();
void error();
void vExit();
void drawLoadingBar(); //barra de loading 
void displayTimer(std::atomic<bool>& timeout); //timer

//Declara�oes de func_leitura.h
void lerUtilizador(const string& linha, Utilizador& dadosUtilizador);//ler uma estrutura "utilizador"
void lerFicheiroUtilizador(const string& filename, vector<Utilizador>& lista); //usando a funçao acima, ler um ficheiro com varias estruturas
int countUtilizadores(string filename);
void guardarDadosUtilizador(const Utilizador& dadosUtilizador, const std::string& filename);
void lerPergunta(std::string& linha, Pergunta& quiz); // ler a estrutura "pergunta"
void lerCSV(const string& nomeFicheiro, vector<Pergunta>& perguntas); // ler o ficheiro com as perguntas, diferente pq esta a ler uma tabela

//Declara�oes lider.h
void tabelaLider();

//Menu.h
void menuPrincipal();

//Quiz.h
void quizSemUser(); //assume "emptyUser" 
Utilizador quizComUser(Utilizador& loggedUser);
//Temas
Utilizador quizCGeral(Utilizador& Usuario);
Utilizador quizHistoria(Utilizador& Usuario);
Utilizador quizDesporto(Utilizador& Usuario);
Utilizador quizCinema(Utilizador& Usuario);
//variaveis usada no quiz
vector<Pergunta> questList;// vetor com a lista de perguntas por tema
Utilizador loggedUser;//utilizador com login valido
Utilizador emptyUser;//usado para a versao sem login

//Signin.h
Utilizador Registo();
Utilizador Login(vector<Utilizador>& lista);
void eliminarUtilizador(const std::string& nomeFicheiro, const int& idApagar); //implementada mas nao usada


//outras variaveis
vector<Utilizador> lista; //lista de utlizadores
vector<Pergunta> quizquestions; //lista de perguntas recebidas do ficheiro

/*
Funçao Main
*/
int main()
{
    std::setlocale(LC_ALL, "");
    lerFicheiroUtilizador("Dados_utilizadores.txt", lista); //inicializaçao
    boasVindas();
    drawLoadingBar();
    menuPrincipal();
}

//==================================EXTRAS======================================
void boasVindas()
{
    cout << "==================================================" << endl;
    cout << "=              SEJA BEM-VINDO AO                 =" << endl;
    cout << "=                  QUIZ GAME                     =" << endl;
    cout << "==================================================" << endl;
    cout << "======================@2023=======================" << endl;
    cout << "==================================================" << endl;

    cout << "Prima qualquer tecla para continuar" << endl;
    cin.ignore();
}

void vExit()
{
    //system("CLS");
    cout << "==================================================" << endl;
    cout << "=                Até á próxima!!                 =" << endl;
    cout << "==================================================" << endl<< endl;

    cout << "Prima qualquer tecla para continuar" << endl;
    cin.ignore();
}

void error()
{
    //system("CLS");
    cout << "==================================================" << endl;
    cout << "=                     ERRO.                      =" << endl;
    cout << "==================================================" << endl<< endl;

    cout << "Prima qualquer tecla para continuar" << endl;
    cin.ignore();
}

void drawLoadingBar()//barra com temporizador(10)segundos
{ 
    system("CLS");
    const int barWidth = 70;
    std::cout << "A carregar: [";
    for (int i = 0; i <= barWidth; ++i)
    {
        std::cout << "*";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(70));
    }
    std::cout << "]\n";
}

// Funcao timer, 
void displayTimer(std::atomic<bool>& timeout)
{
    const int duration = 10; 

    for (int i = 0; i < duration; i++) {
        if (timeout)
            return; //sair se a flag mudar

        cout << "\rTempo restante: " << duration - i << " segundos" << flush;
        this_thread::sleep_for(chrono::seconds(1));
    }

    timeout = true; // virar flag
    cout << endl;
}

//converter para minusculas
string toLowerCase(const string& str) {
    string result = str;
    for (char& c : result) {
        c = tolower(c);
    }
    return result;
}

//lambda para comparar de forma case insensitive, serve para ints e strings
auto equals = [](const string& str1, const string& str2) {
    if (isdigit(str1[0]) && isdigit(str2[0])) {
        return str1 == str2; // comparaçao literal
    } else {
        return toLowerCase(str1) == toLowerCase(str2); // comparaçao case insensitive
    }
};
//=================================funcLEITURA==================================
//ler utilizadores individuais
void lerUtilizador(const std::string& linha, Utilizador& dadosUtilizador)
{
  std::stringstream ss(linha);
  std::string field, temp;

  while (std::getline(ss, field, ':'))// ler apenas apartir do ':' para evitar colocar lixo no vetor,
                                      // isto tambem elimina espaços em branco antes do string
  {
    if (!field.empty())
    {
      std::getline(ss, temp);

      // imlars escapos em brancos antes do primeiro carater valido
      temp.erase(0, temp.find_first_not_of(" \t"));

      // ligar os valores os campos especificos
      if (field == "Nome")
        dadosUtilizador.nome = temp;
      else if (field == "Email")
        dadosUtilizador.email = temp;
      else if (field == "Password")
        dadosUtilizador.password = temp;
      else if (field == "UltimaPontuacao")
        dadosUtilizador.pontuacao = std::stoi(temp);
      else if (field == "PontuacaoMaxima")
        dadosUtilizador.highScore = std::stoi(temp);
      else if (field == "NumerodeJogos")
        dadosUtilizador.nJogos = std::stoi(temp);
      else if (field == "TotalPontos")
        dadosUtilizador.totalperguntas = std::stoi(temp);
      else if (field == "ID")
        dadosUtilizador.id = std::stoi(temp);
    }
  }
}
//ler o ficheiro txt
void lerFicheiroUtilizador(const string& filename, vector<Utilizador>& lista)
{
  ifstream instream(filename);
  int contagem = countUtilizadores("Dados_utlizadores.txt"); //contagem manual

  if (instream) // esta aberto?
  {
    string line; //para ler o ficheiro linha a linha
    string block; //acumula os dados lidos ate determinar que uma linha em branco seja encontrada
    while (getline(instream, line))
    {
      if (line.empty())  // linha em branco a separar utilizadores
      {
        Utilizador novoUtilizador;
        lerUtilizador(block, novoUtilizador);
        lista.push_back(novoUtilizador);
        block.clear();
      }
      else
      {
        block += line + "\n";  // coloca um carater \n para avança uma linha
      }
    }

    // validaçao necessaria para lidar com o final do ficheiro
    if (!block.empty())
    {
      Utilizador novoUtilizador;
      lerUtilizador(block, novoUtilizador);
      lista.push_back(novoUtilizador);
    }

    instream.close();
    //debug
    //cout << "\n" << countUtilizadores("Dados_utilizadores.txt")+1 << " Utilizadores registados. " << endl;
  }
  else
  {
    //cout << "\nFicheiro falhou a abrir";
    return;
  }
}
//funçao para contar utilizadores no ficheiro
int countUtilizadores(string filename)
{
  int utilizadorCount = 0;
  ifstream file(filename);
  if (file.is_open())
  {
    string line;//linha a linha
    while (getline(file, line))
    {
      if (line.substr(0, 3) == "ID:")
        utilizadorCount++;
    }
    file.close();
  }
  else
  {
    cout << "Ficheiro falhou a abrir." << endl;
  }

  return utilizadorCount;
}

void guardarDadosUtilizador(const Utilizador& dadosUtilizador, const std::string& filename)
{
  //ifstream leitura("Dados_utlizadores.txt", ios::in); // ler ficheiro
  ofstream file(filename,std::ios::app);//abrir ficheiro no modo append


  if (file.is_open())//esta aberto? se sim, entao escrever.
  {
    cout << "\nficheiro aberto com sucesso";
    file << "Nome: " << dadosUtilizador.nome << endl;
    file << "Email: " << dadosUtilizador.email << endl;
    file << "Password: " << dadosUtilizador.password << endl;
    file << "UltimaPontuaçao: " << dadosUtilizador.pontuacao << endl;
    file << "PontuaçaoMaxima: " << dadosUtilizador.highScore << endl;
    file << "NumerodeJogos: " << dadosUtilizador.nJogos << endl;
    file << "TotalPontos: " << dadosUtilizador.totalperguntas << endl;
    file << "ID: " << dadosUtilizador.id << endl;
    file << endl;
    file.close();
    cout <<"\nDados guardados";
  }
  else
  {
    cout << "Falha a abrir o ficheiro.";
  }
}
//ler tabela .CSV
void lerCSV(const string& nomeFicheiro, vector<Pergunta>& perguntas)
{
  ifstream instream;
  instream.open(nomeFicheiro);
  if (instream)
  {
    string line;
    while (getline(instream, line))
    {
      Pergunta tempPergunta;
      lerPergunta(line, tempPergunta);//ler linha
      perguntas.push_back(tempPergunta);//proximo elemento do vetor
    }
    instream.close();//fechar
  }
  else
  {
    cout << "\nFicheiro falhou a abrir.";
    return;
  }
}
//ler a estrutura "pergunta"
void lerPergunta(string& linha, Pergunta& quiz)
{
  istringstream is(linha);
  string temp;
  int cont= 0;
  while (getline(is ,temp,',')) //num ficheiro csv o carater delimitador e a virgula
  {
    if (cont == 0)
    {
      quiz.id = atoi(temp.c_str());
    }
    else if (cont == 1)
    {
      quiz.idTema = atoi(temp.c_str());
    }
    else if (cont == 2)
    {
      quiz.question = temp;
    }
    else if (cont == 3)
    {
      quiz.escolhas[0] = temp;
    }
     else if (cont == 4)
    {
      quiz.escolhas[1] = temp;
    }
     else if (cont == 5)
    {
      quiz.escolhas[2] = temp;
    }
     else if (cont == 6)
    {
      quiz.escolhas[3] = temp;
    }
     else if (cont == 7)
    {
      quiz.correta = temp;
    }
    ++cont;
  }
}

//===================lider.cpp==================================================

//le o ficheiro e apresenta os 3 utliazores melhor classificados baseado em totalperguntas respondidas.
void tabelaLider()
{
    std::vector<Utilizador> leader;
    lerFicheiroUtilizador("Dados_utilizadores.txt", leader);

    std::sort(leader.begin(), leader.end(), [](const Utilizador& u1, const Utilizador& u2) {
        return u1.totalperguntas > u2.totalperguntas;
    }); //lambda para realizar organizaçao descrecente

    std::cout << "\nLideres: \n";

    int numUsers = std::min(static_cast<int>(leader.size()), 3);

    for (int i = 0; i < numUsers; i++)
    {
        std::cout << i + 1 << ": " << leader[i].nome << "\n"
                  << "Melhor pontuacao: " << leader[i].highScore << "\n"
                  << "# de jogos: " << leader[i].nJogos << "\n"
                  << "Total perguntas: " << leader[i].totalperguntas << "\n\n";
    }
}


//============================Menu.CPP==========================================

void menuPrincipal()
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
        cin.ignore(numeric_limits<streamsize>::max(),'\n');//limpar o buffer

        switch (escolha)
        {
            case 1:
                system("CLS");
                lerFicheiroUtilizador("Dados_utilizadores.txt", lista);
                loggedUser = Login(lista);
                break;
            case 2:
                system("CLS");
                Registo();
                break;

            case 3:
                system("CLS");
                //Iniciar jogo
                if (loggedUser==emptyUser)
                {
                    quizSemUser();
                    break;
                }
                else
                {
                    quizComUser(loggedUser);
                    break;
                }
                break;
            case 4:
                system("CLS");
                vExit();
                break;
            case 5:
                system("CLS");
                //Tabela de lideres
                tabelaLider();
                break;
            default:

                error();
                //BRR! Erro
                break;

        }
    }
}

//======================================quizz.cpp===============================


//menu de tema no evento de o utlizador nao estar registado
void quizSemUser()
{
    //TODO:ler ficheiro com as perguntas SOLVED.
    int pick;
    system("CLS");
    cout << "\nBem-Vindo " << endl;
    cout << "\nSelecione um tema[1-4](ou selecione 5 para sair): " << endl;
    cout << "\n[1] Cultura Geral.";
    cout << "\n[2] Historia.";
    cout << "\n[3] Desporto.";
    cout << "\n[4] Cinema.";
    cout << ">>>>";
    cin >> pick;

  if (pick >= 1 && pick <= 4)
  {
    switch (pick)
    {
      case 1:
        cout << "Cultura Geral: " << endl;
        cout << "\nPrima qualquer tecla para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(),'\n');//limpar o buffer
        quizCGeral(emptyUser);
        break;
      case 2:
        cout << "Historia: " << endl;
        cout << "\nPrima qualquer tecla para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(),'\n');//limpar o buffer
        quizHistoria(emptyUser);
        break;
      case 3:
        cout << "Desporto: " << endl;
        cout << "\nPrima qualquer tecla para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(),'\n');//limpar o buffer
        quizDesporto(emptyUser);
        break;
      case 4:
        cout << "Cinema: " << endl;
        cout << "\nPrima qualquer tecla para continuar...";
        cin.ignore();
        quizCinema(emptyUser);
        break;
      case 5:
        menuPrincipal();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');//limpar o buffer
        break;
      default:
        quizSemUser();
        break;
    }
  }
  else if (pick == 5)
    {
        menuPrincipal();
        cin.clear();
        cin.ignore();
    }
  else
    { 
      cout << "Escolha inválida. Tente novamente." << endl;
      quizSemUser(); // entrada invalida, a funçao cham-se a si propria para voltar a atras
    }
  
    
}
//versao do menu de tema com utilizador conhnecido
Utilizador quizComUser(Utilizador& loggedUser)
{
    int pick;
    system("CLS");
    cout << "\nBem-Vindo " << loggedUser.nome << " !" << endl;
    cout << "\nSelecione um tema[1-4](ou selecione 5 para sair): " << endl;
    cout << "\n[1] Cultura Geral.";
    cout << "\n[2] Historia.";
    cout << "\n[3] Desporto.";
    cout << "\n[4] Cinema.";
    cout << "\n>>>>";
    cin >> pick;

   if (pick >= 1 && pick <= 4)
    {
    switch (pick)
    {
      case 1:
        cout << "Cultura Geral: " << endl;
        cout << "\nPrima qualquer tecla para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(),'\n');//limpar o buffer
        quizCGeral(loggedUser);
        break;
      case 2:
        cout << "Historia: " << endl;
        cout << "\nPrima qualquer tecla para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(),'\n');//limpar o buffer
        quizHistoria(loggedUser);
        break;
      case 3:
        cout << "Desporto: " << endl;
        cout << "\nPrima qualquer tecla para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(),'\n');//limpar o buffer
        quizDesporto(loggedUser);
        break;
      case 4:
        cout << "Cinema: " << endl;
        cout << "\nPrima qualquer tecla para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(),'\n');//limpar o buffer
        quizCinema(loggedUser);
        break;
      case 5:
        menuPrincipal();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');//limpar o buffer
        break;
      default:
        quizComUser(loggedUser);
        break;
    }
  }
  else if (pick == 5)
    {
        menuPrincipal();
        cin.clear();
        cin.ignore();
    }
  else
    {
      cout << "Escolha inválida. Tente novamente." << endl;
      quizComUser(loggedUser); // entrada invalida, a funçao cham-se a si propria para voltar a atras
    }
    return loggedUser;
}
//==========================CUULTURA_GERAL=============================================================
Utilizador quizCGeral(Utilizador& loggedUser)
{
    vector<Pergunta>questList;
    Pergunta temp;
    vector<Pergunta> culturaGeral;
    string answer;
    int pontos= 0, rightquest = 0;
    atomic<bool> timeout(false); //variavel com a flag the timeout, 
                                //Atomic e usado aqui para que a variavel seja visivel entre threads

    lerCSV("Perguntas.csv", questList);//ler ficheiro com perguntas
  
    for (int i = 0;  i < questList.size(); i++) //seleccionar perguntas
    {
        temp = questList[i];
        if (temp.idTema == 1) // verificar se a pergunta e do tipo certo
        {
            culturaGeral.push_back(temp); // guardar o vetor "cultura geral" para ser usado
        }
    }

    cout << "\nO quiz de Cultura Geral começa brevemente..." << endl;
    cout << "\nPrima qualquer tecla para continuar.";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');//limpar o buffer;

    std::mutex mtx;//isto é um mutex, um objecto necessario para facilitar sincronizaçao do objecto thread

    for (int i = 0; i < culturaGeral.size(); i++)//escrever a pergunta
    {
      //reset da flag do timer
      cout << flush;
      timeout = false;
      system("CLS");

      cout << "\nPergunta #" << i+1 << " : "<< endl;
      cout << culturaGeral.at(i).question << endl;
      cout << culturaGeral.at(i).escolhas[0] << endl;
      cout << culturaGeral.at(i).escolhas[1] << endl;
      cout << culturaGeral.at(i).escolhas[2] << endl;
      cout << culturaGeral.at(i).escolhas[3] << endl;
      cout << "\n>>>";

      //inicio do temporizador, isto e uma tarefa do typo async para o possa correr enquanto espera por input
      
        auto timerFuture = async(launch::async, [&timeout]() {
            const int duration = 10;
            for (int i = 0; i < duration; i++) {
                if (timeout)
                    return;

                cout << "\rTempo restante: " << duration - i << " segundos" << flush;
                this_thread::sleep_for(chrono::seconds(1));
            }
            timeout = true;
            cout << endl;
        });

        string answer;
        getline(cin, answer); //input
        cin.clear();
        if (answer.empty()) 
        {
            timerFuture.wait_for(chrono::seconds(0));
            if (timerFuture.wait_for(chrono::seconds(0)) == future_status::timeout) 
            {
                cout << "\nTempo esgotado! Resposta não submetida." << endl;
                cout << "Pressione qualquer tecla para avançar para a próxima pergunta...";
                cin.ignore();
                cin.clear();
                continue;
            }
            else
            {
              timerFuture.wait();//esperar
            }
        }
            /*
            if (timeout) {
                cout << "\nTempo esgotado! Resposta não submetida." << endl;
                cout << "\nPressione qualquer tecla para avançar para a próxima pergunta...";
                cin.ignore();
                cin.clear();
                continue;
            }
            */
            if (equals(answer, culturaGeral.at(i).correta)) {
                cout << "\nResposta Correta!";
                cout << " ";
                pontos = pontos + 5;
                rightquest = rightquest + 1;
            }
            else {
                cout << "\nResposta Errada!" << endl;
                cout << "a Resposta era:  " << culturaGeral.at(i).correta << endl;
                //system("CLS");
            }
        
    }
    //final da ronda
    cout << "\nPontuaçao final: " << pontos << " com "<< rightquest << " perguntas corretas. ";
    //atualizaçao de dados, na versao sem utilizador "loggedUser" = ao emptyuser
    loggedUser.pontuacao = loggedUser.pontuacao + pontos;
    if (loggedUser.highScore<pontos)
    {
      loggedUser.highScore = pontos;
    }
    loggedUser.nJogos = loggedUser.nJogos+1;
    loggedUser.totalperguntas = loggedUser.totalperguntas+rightquest;
    guardarDadosUtilizador(loggedUser, "Dados_Utilizadores.txt"); //guardar a nova entrada no ficheiro

    return loggedUser;
}

//===============================HISTORIA=======================================

Utilizador quizHistoria(Utilizador& loggedUser)
{
    vector<Pergunta>questList;
    Pergunta temp;
    vector<Pergunta> historia;
    string answer;
    int pontos= 0, rightquest = 0;
    atomic<bool> timeout(false); //variavel com a flag the timeout, 
                                //Atomic e usado aqui para que a variavel seja visivel entre threads

    lerCSV("Perguntas.csv", questList);//ler ficheiro com perguntas
  
    for (int i = 0;  i < questList.size(); i++) //seleccionar perguntas
    {
        temp = questList[i];
        if (temp.idTema == 2) // verificar se a pergunta e valida para o pedido
        {
            historia.push_back(temp); // guardar o vetor "cultura geral" para ser usado
        }
    }

    cout << "\nO quiz de Historia começa brevemente..." << endl;
    cout << "\nPrima qualquer tecla para continuar.";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');//limpar o buffer;

    std::mutex mtx;//isto é um mutex, um objecto necessario para facilitar sincronizaçao do objecto thread

    for (int i = 0; i < historia.size(); i++)//escrever a pergunta
    {
      //reset da flag do timer
      cout << flush;
      timeout = false;
      system("CLS");

      cout << "\nPergunta #" << i+1 << " : "<< endl;
      cout << historia.at(i).question << endl;
      cout << historia.at(i).escolhas[0] << endl;
      cout << historia.at(i).escolhas[1] << endl;
      cout << historia.at(i).escolhas[2] << endl;
      cout << historia.at(i).escolhas[3] << endl;
      cout << "\n>>>";

      //inicio do temporizador
      
        auto timerFuture = async(launch::async, [&timeout]() {
            const int duration = 10;
            for (int i = 0; i < duration; i++) {
                if (timeout)
                    return;

                cout << "\rTempo restante: " << duration - i << " segundos" << flush;
                this_thread::sleep_for(chrono::seconds(1));
            }
            timeout = true;
            cout << endl;
        });

        string answer;
        getline(cin, answer);
        cin.clear();
        if (answer.empty()) 
        {
            timerFuture.wait_for(chrono::seconds(0));
            if (timerFuture.wait_for(chrono::seconds(0)) == future_status::timeout) 
            {
                cout << "\nTempo esgotado! Resposta não submetida." << endl;
                cout << "Pressione qualquer tecla para avançar para a próxima pergunta...";
                cin.ignore();
                cin.clear();
                continue;
            }
            else
            {
              timerFuture.wait();//esperar
            }
        }

            if (equals(answer, historia.at(i).correta)) {
                cout << "\nResposta Correta!";
                cout << " ";
                pontos = pontos + 5;
                rightquest = rightquest + 1;
            }
            else {
                cout << "\nResposta Errada!" << endl;
                cout << "a Resposta era:  " << historia.at(i).correta << endl;
                //system("CLS");
            }
        
    }

    cout << "\nPontuaçao final: " << pontos << " com "<< rightquest << " perguntas corretas. ";
    //atualizaçao de dados
    loggedUser.pontuacao = loggedUser.pontuacao + pontos;
    if (loggedUser.highScore<pontos)
    {
      loggedUser.highScore = pontos;
    }
    loggedUser.nJogos = loggedUser.nJogos+1;
    loggedUser.totalperguntas = loggedUser.totalperguntas+rightquest;
    guardarDadosUtilizador(loggedUser, "Dados_Utilizadores.txt"); //guardar a nova entrada no ficheiro

    return loggedUser;
}

//==================================DESPORTO====================================
Utilizador quizDesporto(Utilizador& loggedUser)
{
    vector<Pergunta>questList;
    Pergunta temp;
    vector<Pergunta> desporto;
    string answer;
    int pontos= 0, rightquest = 0;
    atomic<bool> timeout(false); //variavel com a flag the timeout, 
                                //Atomic e usado aqui para que a variavel seja visivel entre threads

    lerCSV("Perguntas.csv", questList);//ler ficheiro com perguntas
  
    for (int i = 0;  i < questList.size(); i++) //seleccionar perguntas
    {
        temp = questList[i];
        if (temp.idTema == 3) // verificar se a pergunta e valida para o pedido
        {
            desporto.push_back(temp); // guardar o vetor "cultura geral" para ser usado
        }
    }

    cout << "\nO quiz de Desporto começa brevemente..." << endl;
    cout << "\nPrima qualquer tecla para continuar.";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');//limpar o buffer;

    std::mutex mtx;//isto é um mutex, um objecto necessario para facilitar sincronizaçao do objecto thread

    for (int i = 0; i < desporto.size(); i++)//escrever a pergunta
    {
      //reset da flag do timer
      cout << flush;
      timeout = false;
      system("CLS");

      cout << "\nPergunta #" << i+1 << " : "<< endl;
      cout << desporto.at(i).question << endl;
      cout << desporto.at(i).escolhas[0] << endl;
      cout << desporto.at(i).escolhas[1] << endl;
      cout << desporto.at(i).escolhas[2] << endl;
      cout << desporto.at(i).escolhas[3] << endl;
      cout << "\n>>>";

      //inicio do temporizador
      
        auto timerFuture = async(launch::async, [&timeout]() {
            const int duration = 10;
            for (int i = 0; i < duration; i++) {
                if (timeout)
                    return;

                cout << "\rTempo restante: " << duration - i << " segundos" << flush;
                this_thread::sleep_for(chrono::seconds(1));
            }
            timeout = true;
            cout << endl;
        });

        string answer;
        getline(cin, answer);
        cin.clear();
        if (answer.empty()) 
        {
            timerFuture.wait_for(chrono::seconds(0));
            if (timerFuture.wait_for(chrono::seconds(0)) == future_status::timeout) 
            {
                cout << "\nTempo esgotado! Resposta não submetida." << endl;
                cout << "Pressione qualquer tecla para avançar para a próxima pergunta...";
                cin.ignore();
                cin.clear();
                continue;
            }
            else
            {
              timerFuture.wait();//esperar
            }
        }

            if (equals(answer, desporto.at(i).correta)) {
                cout << "\nResposta Correta!";
                cout << " ";
                pontos = pontos + 5;
                rightquest = rightquest + 1;
            }
            else {
                cout << "\nResposta Errada!" << endl;
                cout << "a Resposta era:  " << desporto.at(i).correta << endl;
                //system("CLS");
            }
        
    }

    cout << "\nPontuaçao final: " << pontos << " com "<< rightquest << " perguntas corretas. ";
    //atualizaçao de dados
    loggedUser.pontuacao = loggedUser.pontuacao + pontos;
    if (loggedUser.highScore<pontos)
    {
      loggedUser.highScore = pontos;
    }
    loggedUser.nJogos = loggedUser.nJogos+1;
    loggedUser.totalperguntas = loggedUser.totalperguntas+rightquest;
    guardarDadosUtilizador(loggedUser, "Dados_Utilizadores.txt"); //guardar a nova entrada no ficheiro

    return loggedUser;
}

//===================================CINEMA=====================================
Utilizador quizCinema(Utilizador& loggedUser)
{
    vector<Pergunta>questList;
    Pergunta temp;
    vector<Pergunta> cinema;
    string answer;
    int pontos= 0, rightquest = 0;
    atomic<bool> timeout(false); //variavel com a flag the timeout, 
                                //Atomic e usado aqui para que a variavel seja visivel entre threads

    lerCSV("Perguntas.csv", questList);//ler ficheiro com perguntas
  
    for (int i = 0;  i < questList.size(); i++) //seleccionar perguntas
    {
        temp = questList[i];
        if (temp.idTema == 4) // verificar se a pergunta e valida para o pedido
        {
            cinema.push_back(temp); // guardar o vetor "cultura geral" para ser usado
        }
    }

    cout << "\nO quiz de Cinema começa brevemente..." << endl;
    cout << "\nPrima qualquer tecla para continuar.";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');//limpar o buffer;

    std::mutex mtx;//isto é um mutex, um objecto necessario para facilitar sincronizaçao do objecto thread

    for (int i = 0; i < cinema.size(); i++)//escrever a pergunta
    {
      //reset da flag do timer
      cout << flush;
      timeout = false;
      system("CLS");

      cout << "\nPergunta #" << i+1 << " : "<< endl;
      cout << cinema.at(i).question << endl;
      cout << cinema.at(i).escolhas[0] << endl;
      cout << cinema.at(i).escolhas[1] << endl;
      cout << cinema.at(i).escolhas[2] << endl;
      cout << cinema.at(i).escolhas[3] << endl;
      cout << "\n>>>";

      //inicio do temporizador
      
        auto timerFuture = async(launch::async, [&timeout]() {
            const int duration = 10;
            for (int i = 0; i < duration; i++) {
                if (timeout)
                    return;

                cout << "\rTempo restante: " << duration - i << " segundos" << flush;
                this_thread::sleep_for(chrono::seconds(1));
            }
            timeout = true;
            cout << endl;
        });

        string answer;
        getline(cin, answer);
        cin.clear();
        if (answer.empty()) 
        {
            timerFuture.wait_for(chrono::seconds(0));
            if (timerFuture.wait_for(chrono::seconds(0)) == future_status::timeout) 
            {
                cout << "\nTempo esgotado! Resposta não submetida." << endl;
                cout << "Pressione qualquer tecla para avançar para a próxima pergunta...";
                cin.ignore();
                cin.clear();
                continue;
            }
            else
            {
              timerFuture.wait();//esperar
            }
        }

            if (equals(answer, cinema.at(i).correta)) {
                cout << "\nResposta Correta!";
                cout << " ";
                pontos = pontos + 5;
                rightquest = rightquest + 1;
            }
            else {
                cout << "\nResposta Errada!" << endl;
                cout << "a Resposta era:  " << cinema.at(i).correta << endl;
                //system("CLS");
            }
        
    }

    cout << "\nPontuaçao final: " << pontos << " com "<< rightquest << " perguntas corretas. ";
    //atualizaçao de dados
    loggedUser.pontuacao = loggedUser.pontuacao + pontos;
    if (loggedUser.highScore<pontos)
    {
      loggedUser.highScore = pontos;
    }
    loggedUser.nJogos = loggedUser.nJogos+1;
    loggedUser.totalperguntas = loggedUser.totalperguntas+rightquest;
    guardarDadosUtilizador(loggedUser, "Dados_Utilizadores.txt"); //guardar a nova entrada no ficheiro

    return loggedUser;
}


//===================================signin.cpp=================================

//esta funçao serve para criar um novo utlizador
//validar a entrada
//enviar o resultado para ser guardado
Utilizador Registo()
{
  //variaveis internas
  Utilizador dadosUtilizador;
  string tempPass;
  int totalUtilizadores;

  countUtilizadores("Dados_utilizadores.txt");
  system("CLS");

  cout << "\nRegisto: " << endl;
  cout << "\nNome: ";
  getline(cin, dadosUtilizador.nome ,'\n');
  cin.ignore(numeric_limits<streamsize>::max(),'\n');//limpar o buffer
  cin.clear();

  cout << "\nEmail: ";
  getline(cin, dadosUtilizador.email,'\n');
  cin.ignore(numeric_limits<streamsize>::max(),'\n');//limpar o buffer
  cin.clear();
  //cout << "DEBUG: EMAIL";

  cout << "\nPalavrapasse: ";
  getline(cin, dadosUtilizador.password,'\n');
  cin.ignore(numeric_limits<streamsize>::max(),'\n');//limpar o buffer
  cin.clear();

  cout << "\nConfirme a palavra passe: ";
  getline(cin, tempPass, '\n');
  cin.ignore(numeric_limits<streamsize>::max(),'\n');//limpar o buffer
  cin.clear();

  //validaçao da palavra passe
  if (tempPass != dadosUtilizador.password || tempPass.length()==0) // as palavras passes sao diferentes
  {
    cout << "\nPalavra passe nao confirmada";
    tempPass.clear();
    cout << "\nPrima qualquer tecla para continuar...";
    cin.ignore();
    return Registo();//voltar a chamar registo ate que ocorra com sucesso
  }
  else if (dadosUtilizador.nome.length()== 0 || //verifica se algum dos campos esta vazio
  dadosUtilizador.email.length()== 0 || dadosUtilizador.password.length()== 0)
  {
    cout << "\nCampos obrigatorios estao vazios. ";
    cout << "\nPrima qualquer tecla para continuar...";
    cin.ignore();
    Registo();//voltar a chamar registo ate que ocorra com sucesso
  }
  else if(dadosUtilizador.email.find('@') == string::npos && //validaçao de mail, procura por uma arroba e um ponto
  dadosUtilizador.email.find('.') == string::npos)
  {
    cout << "\nEmail Inválido.";
    cout << "\nPrima qualquer tecla para continuar...";
    cin.ignore();
    Registo();//voltar a chamar registo ate que ocorra com sucesso
  }
  else
  {
    lerFicheiroUtilizador("Dados_utilizadores.txt",lista);
    dadosUtilizador.id=countUtilizadores("Dados_utilizadores.txt")+1;//conta utilizadores antes de guardar
    guardarDadosUtilizador(dadosUtilizador, "Dados_utilizadores.txt");
  }
  return dadosUtilizador;//o registo acabou com sucesso se o codigo chegou aqui
}


//eliminar entradas de utilizador
//detectar a entrada a apagar baseado em id
//mentar a integridade do ficheiro
void eliminarUtilizador(const string& nomeficheiro, const int& idApagar)
{
  vector<Utilizador> lista;
  lerFicheiroUtilizador(nomeficheiro, lista);
  int encontrado=0;//esta valor passa a ser1 se o id for encontrado

  

  //percorrer o vetor e procurar o id selecionado
  for (size_t i = 0; i < lista.size(); i++)
  {
    if (lista[i].id == idApagar)
    {
       encontrado = 1;
       lista.erase(lista.begin()+ i);
       break;
    }
  }
  if (encontrado = 1)
  {
    //Criaçao de um ficheiro temporario para manipulaçao segura
    ofstream tempfile("Tempfile.txt");
    if (!tempfile) //o ficheiro falhou a abrir
    {
      cout << "Ficheiro nao pode ser criado." << endl;
      return;
    }
  
     for (size_t i = 0; i < lista.size(); i++)
    {
      lista[i].id = i + 1;
      //escrever no ficheiro temporario
      tempfile << "Nome: " << lista[i].nome << endl;
      tempfile << "Email: " << lista[i].email << endl;
      tempfile << "Password: " << lista[i].password << endl;
      tempfile << "UltimaPontuacao: " << lista[i].pontuacao << endl;
      tempfile << "PontuacaoMaxima: " << lista[i].highScore << endl;
      tempfile << "NumerodeJogos: " << lista[i].nJogos << endl;
      tempfile << "TotalPontos: " << lista[i].totalperguntas << endl;
      tempfile << "ID: " << lista[i].id << endl;
      tempfile << endl;
    }

    //fechar ficheiro temporario
    tempfile.close();

    //apagar o ficheiro antigo e renomear o temporario com os novos dados
    if (remove(nomeficheiro.c_str()) != 0)
    {
      cout << "Erro a apagar ficheiro" << endl;
      return;
    }
    if (rename("Tempfile.txt", nomeficheiro.c_str()) != 0)
    {
      cout << "Erro a renomear ficheiro" << endl;
      return;
    }

    //confirmaçao
    cout << "Utilizador com o ID " << idApagar << " removido." << endl;
  }
  else//utilizador nao encontrado
  {
    cout << "Utilizador com o ID " << idApagar << " não existe." << endl;
  }
}

Utilizador Login(vector<Utilizador>& lista)
{
  //Login
  //passos
  //1:receber os dados od utilizador
  //2:confirmar se estes sao validos
  //3:carregar os ficheiro com os dados de utilizador
  //4:comparar com o registo
  Utilizador dadoslogin;

  system("CLS");
  cout << "\nLogin: ";
  cout << "\nNome: ";
  getline(cin, dadoslogin.nome, '\n');
  cin.ignore(numeric_limits<streamsize>::max(),'\n');//limpar o buffer
  cin.clear();
  
  cout << "\nEmail: ";
  getline(cin, dadoslogin.email,'\n');
  cin.ignore(numeric_limits<streamsize>::max(),'\n');//limpar o buffer
  cin.clear();
  
  cout << "\nPassword: ";
  getline(cin, dadoslogin.password,'\n');
  cin.ignore(numeric_limits<streamsize>::max(),'\n');//limpar o buffer
  cin.clear();
  //campos vazios
  if (dadoslogin.nome.length()== 0 || dadoslogin.email.length()== 0 || dadoslogin.password.length()== 0)
  {
    cout << "\nCampos obrigatorios estão vazios" << endl;
    //limpar variavel
    dadoslogin.nome.clear();
    dadoslogin.email.clear();
    dadoslogin.password.clear();
    return Login(lista);
  }
  else
  {

    int encontrado = 0;
    for (size_t i = 0; i < lista.size(); i++)
    {
      const Utilizador& temp = lista[i];
      if (CompareNomeEmailPassword(temp,dadoslogin))
      {
        encontrado = 1;
        cout << "\nUtilizador encontrado." << endl;
        cout << "\nBem Vindo " << dadoslogin.nome << endl;
        cout << "Prima qualquer tecla para continuar..." << endl;
        cin.ignore();
        return temp;
      }
    }

    if (!encontrado)
    {
      cout << "\nUtilizador não encontrado." << endl;
    }
    else
    {
      cout << "\nPrima qualquer tecla para continuar..." << endl;
      cin.ignore();
    }
  }
  // se nao for encontrado retornar uma estrutura vazia
  return emptyUser;
}

