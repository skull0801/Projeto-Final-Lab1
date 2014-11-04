// Prototipos para funcoes de alunos
#ifndef FUNCOESALUNO_H
#define FUNCOESALUNO_H
#include "dados.h"

void cadastraAluno(void);
void leDadosAluno(Aluno *aluno);
void gravaDadosAluno(Aluno *aluno);
void listaDadosAlunos(void);
void apresentaAluno(Aluno aluno);
void pesquisaAluno(void);
int apresentaDadosAlunos(void);
Aluno * obtemDadosAlunosArquivo(int * qtdAlunos);
void ordenaAlunosPorNome(Aluno *alunos, int qtdAlunos);
int pesquisaAlunoMatricula(int matriculaBusca);
// void pesquisaAlunoNome(char *nomeBusca);
void alteraAluno(void);
void alteraDadosAluno(Aluno aluno, int posAluno);
void excluiAluno(void);
void excluiDadosAluno(int posAluno);
int validaCPF(const char *cpf);
int verificaCPFAluno(const char *cpf);

#endif
