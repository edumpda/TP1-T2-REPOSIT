// Exemplos de classes dom�nio, classe entidade e testes de unidade.l

// Incluir cabe�alhos.

#include <iostream>

#include "dominios.h"
#include "entidades.h"
#include "testes.h"

using namespace std;

int main() {

    TUNome testeNome;

    switch (testeNome.run()) {
        case TUNome::SUCESSO:
            cout << "SUCESSO - NOME" << endl;
            break;
        case TUNome::FALHA  :
            cout << "FALHA   - NOME" << endl;
            break;
    }

    TUEmail testeEmail;


    switch (testeEmail.run()) {
        case TUEmail::SUCESSO:
            cout << "SUCESSO - EMAIL" << endl;
            break;
        case TUEmail::FALHA  :
            cout << "FALHA   - EMAIL" << endl;
            break;
    }
    TUSenha testeSenha;

    switch (testeSenha.run()) {
        case TUSenha::SUCESSO:
            cout << "SUCESSO - SENHA" << endl;
            break;
        case TUSenha::FALHA  :
            cout << "FALHA   - SENHA" << endl;
            break;
    }

    TUIdioma testeIdioma;

    switch (testeIdioma.run()) {
        case TUIdioma::SUCESSO:
            cout << "SUCESSO - IDIOMA" << endl;
            break;
        case TUIdioma::FALHA  :
            cout << "FALHA   - IDIOMA" << endl;
            break;
    }

    TUAniversario testeAniversario;

    switch (testeAniversario.run()) {
        case TUAniversario::SUCESSO:
            cout << "SUCESSO - ANIVERSARIO" << endl;
            break;
        case TUAniversario::FALHA  :
            cout << "FALHA   - ANIVERSARIO" << endl;
            break;
    }

    TUDescricao testeDescricao;

    // Invocar m�todo e apresentar mensagem acerca do resultado do teste.

    switch (testeDescricao.run()) {
        case TUDescricao::SUCESSO:
            cout << "SUCESSO - DESCRICAO" << endl;
            break;
        case TUDescricao::FALHA  :
            cout << "FALHA   - DESCRICAO" << endl;
            break;
    }

    TUCodigo testeCodigo;
    switch (testeCodigo.run()) {
        case TUCodigo::SUCESSO:
            cout << "SUCESSO - CODIGO" << endl;
            break;
        case TUCodigo::FALHA  :
            cout << "FALHA   - CODIGO" << endl;
            break;
    }
    TUPais testePais;
    switch (testePais.run()) {
        case TUPais::SUCESSO:
            cout << "SUCESSO - PAIS" << endl;
            break;
        case TUPais::FALHA  :
            cout << "FALHA   - PAIS" << endl;
            break;
    }
    TUCity testeCity;
    switch (testeCity.run()) {
        case TUCity::SUCESSO:
            cout << "SUCESSO - CIDADE" << endl;
            break;
        case TUCity::FALHA  :
            cout << "FALHA   - CIDADE" << endl;
            break;
    }
    TUNota testeNota;
    switch (testeNota.run()) {
        case TUNota::SUCESSO:
            cout << "SUCESSO - NOTA" << endl;
            break;
        case TUNota::FALHA  :
            cout << "FALHA   - NOTA" << endl;
            break;
    }
    TUDescricao_hosp teste_desc;
    switch (teste_desc.run()) {
        case TUDescricao_hosp::SUCESSO:
            cout << "SUCESSO - DESCRICAO_HOSP" << endl;
            break;
        case TUDescricao_hosp::FALHA  :
            cout << "FALHA   - DESCRICAO_HOSP" << endl;
            break;
    }
    TUNota_ava testeNota_ava;
    switch (testeNota_ava.run()) {
        case TUNota_ava::SUCESSO:
            cout << "SUCESSO - NOTA-AVALIACAO" << endl;
            break;
        case TUNota_ava::FALHA  :
            cout << "FALHA   - NOTA-AVALIACAO" << endl;
            break;
    }
    TUCodigo_ava teste_codigo_ava;
    switch (teste_codigo_ava.run()) {
        case TUCodigo_ava::SUCESSO:
            cout << "SUCESSO - CODIGO-AVALIACAO" << endl;
            break;
        case TUCodigo_ava::FALHA  :
            cout << "FALHA   - CODIGO-AVALIACAO" << endl;
            break;
    }
    TUDescricao_ava teste_desc_ava;
    switch (teste_desc_ava.run()) {
        case TUDescricao_ava::SUCESSO:
            cout << "SUCESSO - DESCRICAO-AVALIACAO" << endl;
            break;
        case TUCodigo_ava::FALHA  :
            cout << "FALHA   - DESCRICAO-AVALIACAO" << endl;
            break;
    }
    //-----------------------------------------------------------------------
    // Exemplo de teste de classe entidade.ccccc

    // Instanciar classe de teste de entidade.


    TUUsuario testeUser;

    switch(testeUser.run()){
        case TUUsuario::SUCESSO: cout << "SUCESSO - USUARIO" << endl;
            break;
        case TUUsuario::FALHA  : cout << "FALHA   - USUARIO" << endl;
            break;
    }
    TUHospedagem testeHosp;
    switch(testeHosp.run()){
        case TUHospedagem::SUCESSO: cout << "SUCESSO - HOSPEDAGEM" << endl;
            break;
        case TUHospedagem::FALHA  : cout << "FALHA   - HOSPEDAGEM" << endl;
            break;
    }
    TUAvaliacao testeAvaliacao;
    switch(testeAvaliacao.run()){
        case TUAvaliacao::SUCESSO: cout << "SUCESSO - AVALIACAO" << endl;
            break;
        case TUAvaliacao::FALHA  : cout << "FALHA   - AVALIACAO" << endl;
            break;
    }

    return 0;

}