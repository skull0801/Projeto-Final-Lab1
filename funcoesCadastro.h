// Prototipos para funcoes de cadastros
#ifndef FUNCOESCADASTRO_H
#define FUNCOESCADASTRO_H
#include "dados.h"

int leDadosCadastro(Cadastro *cadastro);
void pesquisaCadastro(Cadastro *query, int paramBusca);
void gravaDadosCadastro(Cadastro *cadastro);
void listaDadosCadastro();

#endif
