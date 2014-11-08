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
void apresentarTodosAlunosCadastrados(void);
void apresentaAlunosMatriculadosEmUmCurso(void);

Aluno *obtemAlunosDeCurso(int codigoCurso, int *qtdAlunos, int indicador);

// Verificacao
int verificaAlunoCadastrado(int matriculaAluno);
int verificaCursoAlunoCadastrado(int codigoCurso);
int verificaAlunoRepetidoCadastrando(int codCurso, int alunoMatricula);

#endif
