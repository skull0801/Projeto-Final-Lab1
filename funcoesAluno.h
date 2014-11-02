// Prototipos para funcoes de alunos
#ifndef FUNCOESALUNO_H
#define FUNCOESALUNO_H
#include "dados.h"

void leDadosAluno(Aluno *aluno);
void gravaDadosAluno(Aluno *aluno);
void listaDadosAlunos();
int pesquisaAlunoMatricula(int matriculaBusca, int indPrint);
// void pesquisaAlunoNome(char *nomeBusca);
void alteraDadosAluno(int matricula);
void excluiDadosAluno(int matricula);
int validaCPF(const char *cpf);
int verificaCPFAluno(const char *cpf);

#endif
