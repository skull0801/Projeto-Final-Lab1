// Prototipos para funcoes de cadastros
#ifndef FUNCOESCADASTRO_H
#define FUNCOESCADASTRO_H
#include "dados.h"

// Cadastro
void cadastraAlunoEmCurso(void);

// Alteracao
void alteraCadastro(void);

// Exclusao
void excluiMatriculaAlunoEmUmCurso(void);
void excluiMatriculaAluno(int matricula, int codCurso);

// Apresentacao
void listaDadosCadastro(void);
void apresentaCadastro(Cadastro cadastro);
void pesquisaApresentaCadastro(void);
void apresentaTodosAlunosCadastrados(void);
void apresentaAlunosMatriculadosEmUmCurso(void);
int apresentaDadosCadastros(Cadastro *cadastros, int qtdeCadastros);

Cadastro *obtemAlunosDeCurso(int codigoCurso, int *qtdCadastros, int indicador);
Cadastro *obtemAlunosPorSituacaoPagamento(int *qtdCadastros, int indicador);

// Verificacao
int verificaAlunoCadastrado(int matriculaAluno);
int verificaCursoAlunoCadastrado(int codigoCurso);
int verificaAlunoRepetidoCadastrando(int codCurso, int alunoMatricula);

// Comparacao
int comparaCadastroCodigo(const void *p1, const void *p2);

#endif
