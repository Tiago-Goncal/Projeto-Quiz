/*
Este Ficheiro serve para:

 - lidar com a rececao de dados de utlizador no registo
 - Guardar estes dados num ficheiro de texto
 - ler os dados deste ficheiro na funçao login
 - lidar com a eliminaçao de utilizadores

*/
#include "include/Signin.h"


using namespace std;

//declaraçoes


//variaveis

vector<Utilizador> lista;
Utilizador dadosUtilizador;
vector<Pergunta> quizquestions;

//guardar dados no ficheiro

//esta funçao le o fichiro de texto linha a linha

//ler o ficheiro com os dados de utilizador

//registo: implementaçao
Utilizador Registo(Utilizador)
{
  //Utilizador dadosUtilizador;
  string tempPass;

  cout << "\nRegisto: ";
  cout << "\nNome: ";
  getline(cin, dadosUtilizador.nome);
  cout << "\nEmail: ";
  getline(cin, dadosUtilizador.email);
  cout << "\nPalavrapasse: ";
  getline(cin, dadosUtilizador.password);
  cout << "\nConfirme a palavra passe: ";
  getline(cin, tempPass);
  if (tempPass != dadosUtilizador.password || tempPass.length()==0)
  {
    cout << "\nPalavra passe nao confirmada";
    tempPass.clear();
    Registo(dadosUtilizador);
  }
  else
  {
    cout << "\nPalavra passe Confirmada.";
  }
  

  if (dadosUtilizador.nome.length()== 0 || 
  dadosUtilizador.email.length()== 0 || dadosUtilizador.password.length()== 0)
  {
    cout << "\nCampos obrigatorios estao vazios. ";
    cout << "\nPrima qualquer tecla para continuar...";
    cin.ignore();
    Registo(dadosUtilizador);
  }
  else if(dadosUtilizador.email.find('@') == string::npos && 
  dadosUtilizador.email.find('.') == string::npos)
  {
    cout << "\nEmail Não valido.";
    cout << "\nPrima qualquer tecla para continuar...";
    cin.ignore();
    Registo(dadosUtilizador);
  }
  else
  {
    dadosUtilizador.id= dadosUtilizador.id+1;
    guardarDadosUtilizador(dadosUtilizador);
  }

  return dadosUtilizador;
}
void eliminarUtilizador(const string& nomeficheiro, const int& idApagar)
{
  ifstream ficheiro("Dados_utilizador.txt");
  if (!ficheiro) //o ficheiro falhou a abrir
  {
    cout << "Ficheiro nao encontrado." << endl;
    return;
  }
  //ler
  while (ficheiro >> dadosUtilizador.nome >> dadosUtilizador.email >> 
  dadosUtilizador.password >> dadosUtilizador.pontuacao >> dadosUtilizador.highScore >> 
  dadosUtilizador.nJogos >> dadosUtilizador.totalperguntas >> dadosUtilizador.id)
  {
    lista.push_back(dadosUtilizador);
  }
  ficheiro.close();

  //Criaçao de um ficheiro temporario para manipulaçao segura
  ofstream tempfile("Tempfile.txt"); 
  if (!tempfile) //o ficheiro falhou a abrir
  {
    cout << "Ficheiro nao pode ser criado." << endl;
    return;
  }
  //percorrer o vetor e procurar o id selecionado
  int encontrado=0;//esta valor passa a ser1 se o id for encontrado

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
  }
  else
  {
    cout << "Utilizador com o ID " << idApagar << " não existe." << endl;
  }
  //fechar ficheiro temporario
  tempfile.close();

  //apagar o ficheiro antigo e renomear o temporario com os novos dados
  if (remove(nomeficheiro.c_str())!= 0)
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
  
Utilizador Login()
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
  getline(cin, dadoslogin.nome);
  cout << "\nEmail: ";
  getline(cin, dadoslogin.email);
  cout << "\nPassword: ";
  getline(cin, dadoslogin.password);
  //campos vazios
  if (dadoslogin.nome.length()== 0 || dadoslogin.email.length()== 0 || dadoslogin.password.length()== 0)
  {
    cout << "\nCampos obrigatorios estão vazios" << endl;
    //limpar variavel
    dadoslogin.nome.clear();
    dadoslogin.email.clear();
    dadoslogin.password.clear();
    Login();
  }
  else
  {
    //ler e procurar se os valores introduzidos correspondem a um utilizador valido
    int encontrado = 0;
    lerFicheiroUtilizador("Dados_utilizadores.txt",lista);
    for (const Utilizador& temp : lista)
    {
      if (temp.nome == dadoslogin.nome && temp.email == dadoslogin.email && temp.password == dadoslogin.password)
      {
        //utilizador encontrado, reter a estrutura para uso futuro
        encontrado = 1;
        cout << "\nUtilizador encontrado. "<< endl;
        cout << "\nBem Vindo " <<  dadoslogin.nome << endl;
        cout << "Prima qualquer tecla para continuar" << endl;
        cin.ignore();
        return temp;
      }
      else
      {
        //utlizador nao encontrado, retornar uma estrutura vazia.
        cout << "\nUtilizador não encontrado. "<< endl;
        cout << "Prima qualquer tecla para continuar" << endl;
        cin.ignore();
        return Utilizador();
      }
    }
  }
  cout << endl;
  

}


//As funçoes abaixo sao para lse a lista que contem as perguntas.


