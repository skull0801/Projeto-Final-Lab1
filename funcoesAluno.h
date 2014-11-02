// Prototipos para funcoes de alunos
#ifndef FUNCOESALUNO_H
#define FUNCOESALUNO_H
#include "dados.h"

void leDadosAluno(Aluno *aluno);
void gravaDadosAluno(Aluno *aluno);
void listaDadosAlunos(void);
void apresentaAluno(Aluno aluno);
int pesquisaAlunoMatricula(int matriculaBusca);
// void pesquisaAlunoNome(char *nomeBusca);
void alteraDadosAluno(int matricula);
void excluiAluno(void);
void excluiDadosAluno(int posAluno);
int validaCPF(const char *cpf);
int verificaCPFAluno(const char *cpf);

#endif
