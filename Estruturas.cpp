#include <Estruturas.h>


//comparaçao dos campos string da estrutura, isto existe proque o operador == nao pode receber outro overload
bool CompareNomeEmailPassword(const Utilizador& lhs, const Utilizador& rhs)
{
    return (lhs.nome.compare(rhs.nome) == 0 &&
            lhs.email.compare(rhs.email) == 0 &&
            lhs.password.compare(rhs.password) == 0);
}


