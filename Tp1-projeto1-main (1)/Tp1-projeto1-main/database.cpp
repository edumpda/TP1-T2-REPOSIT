#include "entidades.h"
#include "dominios.h"
#include "sqlite3.h"
#include "database.h"
#include <string>
#include <sstream>

//Atributo estatico container List.

list<ElementoResultado> ComandoSQL::listaResultado;

//---------------------------------------------------------------------------
//Classe ErroPersistencia.

EErroPersistencia::EErroPersistencia(string mensagem)
{
        this->mensagem = mensagem;
}

string EErroPersistencia::what()
{
        return mensagem;
}

//---------------------------------------------------------------------------
//Classe ElementoResultado.

void ElementoResultado::setNomeColuna(const string &nomeColuna)
{
        this->nomeColuna = nomeColuna;
}

void ElementoResultado::setValorColuna(const string &valorColuna)
{
        this->valorColuna = valorColuna;
}

//---------------------------------------------------------------------------
//Classe ComandoSQL.

void ComandoSQL::conectar()
{
        rc = sqlite3_open(nomeBancoDados, &bd);
        if (rc != SQLITE_OK)
                throw EErroPersistencia("Erro na conexao ao banco de dados");
}

void ComandoSQL::desconectar()
{
        rc = sqlite3_close(bd);
        if (rc != SQLITE_OK)
                throw EErroPersistencia("Erro na desconexao ao banco de dados");
}

void ComandoSQL::executar()
{
        conectar();
        rc = sqlite3_exec(bd, comandoSQL.c_str(), callback, 0, &mensagem);

        if (rc != SQLITE_OK)
        {
                sqlite3_free(mensagem);
                desconectar();
                throw EErroPersistencia("Erro na execucao do comando SQL");
        }

        desconectar();
}

int ComandoSQL::callback(void *NotUsed, int argc, char **valorColuna, char **nomeColuna)
{
        NotUsed = 0;
        ElementoResultado elemento;
        int i;
        for (i = 0; i < argc; i++)
        {
                elemento.setNomeColuna(nomeColuna[i]);
                elemento.setValorColuna(valorColuna[i] ? valorColuna[i] : "NULL");
                listaResultado.push_front(elemento);
        }
        return 0;
}

ComandoSenha::ComandoSenha(Email email)
{
        comandoSQL = "SELECT senha FROM usuario WHERE email = '";
        // senha da tabela usuario onde email eh o getemail
        comandoSQL += email.getEmail();
        comandoSQL += "'";
}

string ComandoSenha::getResultado()
{
        ElementoResultado resultado;
        string senha;

        if (listaResultado.empty())
        {
                throw EErroPersistencia("Lista Vazia.");
        }

        resultado = listaResultado.back();
        listaResultado.pop_back(); // dado que a gente vai excluir

        senha = resultado.getValorColuna();

        return senha;
}

// ---------------------------------------------
// Implementa????o do comando Cadastrar Usuario
// ---------------------------------------------

ComandoCadastrarUsuario::ComandoCadastrarUsuario(Usuario usuario)
{
        comandoSQL = "INSERT INTO usuario VALUES (";
        comandoSQL += "'" + usuario.getEmail().getEmail() + "', ";
        comandoSQL += "'" + usuario.getNome().getNome() + "', ";
        comandoSQL += "'" + usuario.getSenha().getSenha() + "')";
}

// ---------------------------------------------
// Implementa????o do comando Descadastrar Usuario
// ---------------------------------------------

ComandoDescadastrarUsuario::ComandoDescadastrarUsuario(Email email)
{
        comandoSQL = "DELETE FROM usuario WHERE email = '";
        comandoSQL += email.getEmail();
        comandoSQL += "'";
}

// ---------------------------------------------
// Implementa????o do comando Editar Usu??rio
// ---------------------------------------------

ComandoEditarUsuario::ComandoEditarUsuario(Usuario usuario)
{
        comandoSQL = "UPDATE usuario ";
        comandoSQL += "SET nome = '" + usuario.getNome().getNome();
        comandoSQL += "', senha = '" + usuario.getSenha().getSenha();
        comandoSQL += "' WHERE email = '" + usuario.getEmail().getEmail();
        comandoSQL += "'";
}


//--------------------------------------------------------------------------------------
//|                                 Hospedagem                                           |
//--------------------------------------------------------------------------------------

// ------------------------------------------------
// Implementa????o do comando Cadastrar Hospedagem
// ------------------------------------------------
ComandoCadastrarHospedagem::ComandoCadastrarHospedagem(Hospedagem hospedagem, Email email, int digito_verificador)
{
        comandoSQL = "INSERT INTO Hospedagem VALUES (";
        comandoSQL += "NULL, ";
        comandoSQL += "NULL, ";
        comandoSQL += "'" + hospedagem.getCidade().getCidade() + "', ";
        comandoSQL += "'" + hospedagem.getPais().getPais() + "', ";
        comandoSQL += "'" + hospedagem.getDescricao().getDescricao() + "', ";
        comandoSQL += "'" + to_string(digito_verificador) + "', ";
        comandoSQL += "'" + email.getEmail() + "')";
}

NextIdHospedagem::NextIdHospedagem() {}()
{
        comandoSQL = "SELECT seq + 1 FROM SQLITE_SEQUENCE WHERE name='Hospedagem'";
}
int NextIdHospedagem::getResultado()
{
        ElementoResultado resultado;
        int result;

        if (listaResultado.empty())
        {
                throw EErroPersistencia("Lista Vazia.");
        }
        resultado = listaResultado.back();
        listaResultado.pop_back();

        result = stoi(resultado.getValorColuna());
        return result;
}

// ------------------------------------------------
// Implementa????o do comando Descadastrar Hospedagem
// ------------------------------------------------
ComandoDescadastrarHospedagem::ComandoDescadastrarHospedagem(Codigo codigo, Email email)
{
        string icodigo = codigo.getCodigo();
        icodigo.pop_back();
        comandoSQL = "DELETE FROM Hospedagem WHERE (Codigo = '";
        comandoSQL += icodigo;
        comandoSQL += "') AND (Guia = '";
        comandoSQL += email.getEmail();
        comandoSQL += "')";
}

ListarHospedagem::ListarHospedagem()
{
        comandoSQL = "SELECT Codigo FROM Hospedagem";
}

// ------------------------------------------------
// Implementa????o do comando Editar Hospedagem
// ------------------------------------------------

ComandoEditarHospedagem::ComandoEditarHospedagem(Hospedagem hospedagem, Email email)
{
        comandoSQL = "UPDATE Hospedagem ";
        comandoSQL += ", Cidade = '" + excursao.getCidade().getCidade();
        comandoSQL += ", Descricao = '" + excursao.getDescricao().getDescricao();
        comandoSQL += "', Pais = '" + excursao.getPais().getPais();
        comandoSQL += "' WHERE (Codigo = '" + hospedagem.getCodigo().getCodigo();
        comandoSQL += "') AND (Guia = '" + email.getEmail() + "')";
}

// ------------------------------------------------
// Implementa????o do comando Listar Hospedagens
// ------------------------------------------------

ComandoListarHospedagem::ComandoListarHospedagem()
{
        comandoSQL = "SELECT * FROM Hospedagem";
}

//--------------------------------------------------------------------------------------
//|                                  Avalia????o                                         |
//--------------------------------------------------------------------------------------

// ------------------------------------------------
// Implementa????o do comando Cadastrar Avalia????o
// ------------------------------------------------

ComandoCadastrarAvaliacao::ComandoCadastrarAvaliacao(Avaliacao avaliacao, Email email, Codigo codigo)
{
        comandoSQL = "INSERT INTO Avaliacao VALUES (";
        comandoSQL += "NULL, ";
        comandoSQL += "'" + to_string(avaliacao.getNota().getNota()) + "', ";
        comandoSQL += "'" + avaliacao.getDescricao().getDescricao() + "', ";
        comandoSQL += "'" + codigo.getCodigo() + "')";
}

GetNotasAvaliacao::GetNotasAvaliacao()
{
        comandoSQL = "SELECT Nota FROM Avaliacao";
}
list<string> GetNotasAvaliacao::getResultado()
{
        ElementoResultado resultado;

        if (listaResultado.empty())
        {
                throw EErroPersistencia("Lista Vazia.");
        }
        resultado = listaResultado.back();
        listaResultado.pop_back();

        return resultado.getValoresColuna();
}

ComandoDescadastrarAvaliacao::ComandoDescadastrarAvaliacao(Codigo codigo, Email email)
{
        comandoSQL = "DELETE FROM Avaliacao WHERE (Codigo = '";
        comandoSQL += codigo.getCodigo();
        comandoSQL += "') AND (Avaliador = '";
        comandoSQL += email.getEmail();
        comandoSQL += "')";
}

// ------------------------------------------------
// Implementa????o do comando Editar Avalia????o
// ------------------------------------------------

ComandoEditarAvaliacao::ComandoEditarAvaliacao(Avaliacao avaliacao, Email email)
{
        comandoSQL = "UPDATE Avaliacao ";
        comandoSQL += "SET Nota = '" + avaliacao.getNota().getNota();
        comandoSQL += "', Descricao = " + avaliacao.getDescricao().getDescricao();
        comandoSQL += "' WHERE (Codigo = '" + avaliacao.getCodigo().getCodigo();
        comandoSQL += "') AND (Avaliador = '" + email.getEmail() + "')";
}

// ------------------------------------------------
// Implementa????o do comando Listar Avalia????es
// ------------------------------------------------

ComandoListarAvaliacoes::ComandoListarAvaliacoes(Email)
{
        comandoSQL = "SELECT * FROM Excursao";
}