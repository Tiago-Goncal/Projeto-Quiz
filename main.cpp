#include <iostream>
#include <locale.h>
#include <string>
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <algorithm>

using namespace std;

using std::cout;
using std::cin;
using std::vector;


//ESTRUTURAS:H------------------------------------------------------------------
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
  struct Pergunta
  {
    int id;
    int idTema; //1:Cultura Geral|2:Historia|3:Desporto|4:Cinema
    std::string question;
    std::string escolhas[4];
    std::string correta;

  };
/*Declaraçoes de Variaveis e funçoes*/
bool CompareNomeEmailPassword(const Utilizador& lhs, const Utilizador& rhs);

//------------------------------------------------------------------------------
//declara�oes de Extras.h
void boasVindas();
void error();
void vExit();
void drawLoadingBar(); //barra de loading com timer de 10 segundos

//Declara�oes de func_leitura.h
void lerUtilizador(const string& linha, Utilizador& dadosUtilizador);
void lerFicheiroUtilizador(const string& filename, vector<Utilizador>& lista);
int countUtilizadores(string filename);
void guardarDadosUtilizador(const Utilizador& dadosUtilizador, const std::string& filename);
void lerCSV(const string& nomeFicheiro, vector<Pergunta>& perguntas);
void lerPergunta(std::string& linha, Pergunta& quiz);

//Declara�oes lider.h
void tabelaLider();


//Menu.h
void menuPrincipal();

//Quiz.h
void quizSemUser();
Utilizador quizComUser(Utilizador& loggedUser);
Utilizador quizCGeral(Utilizador& Usuario);
//Utilizador quizHistoria(Utilizador& Usuario);
//Utilizador quizDesporto(Utilizador& Usuario);
//Utilizador quizCinema(Utilizador& Usuario);

vector<Pergunta> questList;// vetor com a lista de perguntas por tema
unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count(); //numero aleatoria para a funçao shuffle
Utilizador loggedUser;//utilizador com login valido
Utilizador emptyUser;//usado para a versao sem login

//Signin.h
Utilizador Registo();
Utilizador Login(vector<Utilizador>& lista);
void eliminarUtilizador(const std::string& nomeFicheiro, const int& idApagar);

vector<Utilizador> lista;
Utilizador dadosUtilizador;
vector<Pergunta> quizquestions;

/*

Funçao Main

*/
int main()
{
    setlocale(LC_ALL, " ");
    lerFicheiroUtilizador("Dados_utilizadores.txt", lista); //inicializaçao
    boasVindas();
    drawLoadingBar();
    menuPrincipal();
}

//==================================EXTRAS======================================
void boasVindas()
{

    cout << "|=========================|" << endl;
    cout << "|====SEJA BEM-VINDO AO====|" << endl;
    cout << "|========QUIZ GAME========!" << endl;
    cout << "|=========================|" << endl;

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
    const int barWidth = 70;
    std::cout << "A carregar: [";
    for (int i = 0; i <= barWidth; ++i)
    {
        std::cout << "*";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "]\n";
}


//=================================funcLEITURA==================================

//ler utilizadores individuais
void lerUtilizador(const std::string& linha, Utilizador& dadosUtilizador)
{
  std::stringstream ss(linha);
  std::string field, temp;

  while (std::getline(ss, field, ':'))
  {
    if (!field.empty())
    {
      std::getline(ss, temp);

      // Remove leading whitespaces from the value
      temp.erase(0, temp.find_first_not_of(" \t"));

      // Assign the value to the corresponding member of the struct
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
//ler i ficheiro txt
void lerFicheiroUtilizador(const string& filename, vector<Utilizador>& lista)
{
  ifstream instream(filename);
  int contagem = countUtilizadores("Dados_utlizadores.txt"); //contagem manual

  if (instream) // esta aberto?
  {
    string line; //para ler o ficheiro linha a linha
    string block; //acumula os dados lidos ate determinar que uma instancia da estrutura foi lida
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
    cout << "\n" << countUtilizadores("Dados_utilizadores.txt")+1 << " Utilizadores registados. " << endl;
  }
  else
  {
    cout << "\nFicheiro falhou a abrir";
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
    cerr << "Ficheiro falhou a abrir." << endl;
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

void lerPergunta(string& linha, Pergunta& quiz)
{
  istringstream is(linha);
  string temp;
  int cont= 0;
  while (getline(is ,temp,','))
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
    //TODO:ler ficheiro com as perguntas
    int pick;
    system("CLS");
    cout << "\nBem-Vindo" << endl;
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
        break;
      case 3:
        cout << "Desporto: " << endl;
        cout << "\nPrima qualquer tecla para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(),'\n');//limpar o buffer
        getchar();
        break;
      case 4:
        cout << "Cinema: " << endl;
        cout << "\nPrima qualquer tecla para continuar...";
        cin.ignore();
        getchar();
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
    cout << "\nBem-Vindo" << loggedUser.nome << " !" << endl;
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
        break;
      case 3:
        cout << "Desporto: " << endl;
        cout << "\nPrima qualquer tecla para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(),'\n');//limpar o buffer
        break;
      case 4:
        cout << "Cinema: " << endl;
        cout << "\nPrima qualquer tecla para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(),'\n');//limpar o buffer
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
      quizComUser(loggedUser); // entrada invalida, a funçao cham-se a si propria para voltar a atras
    }

    return loggedUser;
}

Utilizador quizCGeral(Utilizador& loggedUser)
{
    vector<Pergunta>questList;
    Pergunta temp;
    vector<Pergunta> culturaGeral;
    string answer;
    int pontos= 0, rightquest = 0;
    //bool timeout = false; //para tomar nota do tempo limite

    lerCSV("Perguntas.csv", questList);//ler ficheiro com perguntas
  

    for (int i = 0;  i < questList.size(); i++) //seleccionar perguntas
    {
        temp = questList[i];
        if (temp.idTema == 1) // verificar se a pergunta e valida para o pedido
        {
            culturaGeral.push_back(temp); // guardar o vetor "cultura geral" para ser usado
        }
    }

    cout << "\nO quiz de Cultura Geral começa brevemente..." << endl;
    //shuffle(culturaGeral.begin(), culturaGeral.end(), seed);//
    cout << "\nPrima qualquer tecla para continuar.";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');//limpar o buffer;

    for (int i = 0; i < culturaGeral.size(); i++)//escrever a pergunta
    {
      cout << "\nPergunta #" << i+1 << " : "<< endl;
      cout << culturaGeral.at(i).question << endl;
      cout << culturaGeral.at(i).escolhas[0] << endl;
      cout << culturaGeral.at(i).escolhas[1] << endl;
      cout << culturaGeral.at(i).escolhas[2] << endl;
      cout << culturaGeral.at(i).escolhas[3] << endl;
      cout << "\n>>>";

      // Start the timer
      auto startTime = chrono::steady_clock::now();

      //drawLoadingBar();//tempo começa a contar
      getline(cin, answer, ' ');
      cin.clear();
      cin.ignore();

      //temporizador
      auto endTime = chrono::steady_clock::now();
      auto elapsed = chrono::duration_cast<chrono::seconds>(endTime - startTime).count();
      // tempo esgotou: passar a proxima pergunta.
      if (elapsed >= 10) {
        cout << "\nTempo esgotado! Resposta não submetida." << endl;
        continue;
      }

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
 
//comparaçoa dos campos string da estrutura, isto existe proque o operador nao pode recber outro overload
bool CompareNomeEmailPassword(const Utilizador& lhs, const Utilizador& rhs)
{
    return (lhs.nome.compare(rhs.nome) == 0 &&
            lhs.email.compare(rhs.email) == 0 &&
            lhs.password.compare(rhs.password) == 0);
}



