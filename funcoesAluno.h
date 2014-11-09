// Prototipos para funcoes de alunos
#ifndef FUNCOESALUNO_H
#define FUNCOESALUNO_H
#include "dados.h"

// Cadastro
void cadastraAluno(void);
int leDadosAluno(Aluno *aluno);

// Alteracao
void alteraAluno(void);

// Exclusao
void excluiAluno(void);

// Pesquisa
void pesquisaAluno(void);
int pesquisaAlunoMatricula(int matriculaBusca);
int pesquisaApresentaAlunoNome(void);
void pesquisaApresentaAlunoMatricula(void);

// Apresentacao
void apresentaAluno(Aluno aluno);
void apresentaAlunosMatriculadosEmPeriodo(void);
int apresentaTodosAlunos(void);
int apresentaDadosAlunos(Aluno *alunos, int qtdAlunos);

// CPF
int validaCPF(const char *cpf);
int verificaCPFAluno(const char *cpf);

// Comparacao
int comparaAlunos(const void *p1, const void *p2);
int comparaNomesAlunos(const void *p1, const void *p2);

// Data
void geraDataIngresso(Data *data);

#endif
