// Prototipos para funcoes de cadastros
#ifndef FUNCOESCADASTRO_H
#define FUNCOESCADASTRO_H
#include "dados.h"

void cadastraAlunoEmCurso();
void listaDadosCadastro();
void gravaDadosMatricula(Cadastro matricula);
void apresentaAlunosMatriculadosEmUmCurso();
int verificaAlunoRepetidoCadastrando(int codCurso, int alunoMatricula);
Cadastro * obtemDadosCadastroMatriculas(int *qtdeMatriculados);

#endif
