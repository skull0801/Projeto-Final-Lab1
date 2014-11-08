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

// Apresentacao
void apresentaAluno(Aluno aluno);
int apresentaTodosAlunos(void);
int apresentaDadosAlunos(Aluno *alunos, int qtdAlunos);

// Pesquisa
void pesquisaAluno(void);
int pesquisaAlunoMatricula(int matriculaBusca);
void pesquisaApresentaAlunoNome();
void pesquisaApresentaAlunoMatricula();

// Obtencao do arquivo
Aluno * obtemDadosAlunosArquivo(int * qtdAlunos);
int obtemAlunoArquivo(Aluno *aluno, int posAluno);

// CPF
int validaCPF(const char *cpf);
int verificaCPFAluno(const char *cpf);

// Comparacao
int comparaAlunos(const void *p1, const void *p2);

// Data
void geraDataIngresso(Data *data);

#endif
