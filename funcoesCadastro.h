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
void apresentaCadastro(Cadastro cadastro, int linha, int coluna);
void pesquisaApresentaCadastro(void);
void apresentaTodosAlunosCadastrados(void);
void apresentaAlunosMatriculadosEmUmCurso(void);
void apresentaAlunosPorSituacao(void);
int apresentaDadosCadastros(Cadastro *cadastros, int qtdeCadastros);
int apresentaCursosDeAluno(int matriculaAluno);

Cadastro *obtemAlunosDeCurso(int codigoCurso, int *qtdCadastros, int indicador);
Cadastro *obtemAlunosPorSituacaoPagamento(int *qtdCadastros, int indicador);

// Verificacao
int verificaAlunoCadastrado(int matriculaAluno);
int verificaCursoAlunoCadastrado(int codigoCurso);
int verificaAlunoRepetidoCadastrando(int codCurso, int alunoMatricula);

// Comparacao
int comparaCadastroCodigo(const void *p1, const void *p2);

#endif
