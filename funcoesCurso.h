// Prototipos para funcoes de cursos
#ifndef FUNCOESCURSO_H
#define FUNCOESCURSO_H
#include "dados.h"

// Cadastro
void cadastraCurso(void);
void leDadosCurso(Curso *curso);

// Alteracao
void alteraCurso(void);

// Exclusao
void excluiCurso(void);

// Pesquisa
int selecionaCurso(void);
void pesquisaCurso(void);
void pesquisaApresentaCursoCodigo(void);
int pesquisaApresentaCursoNome(void);
int pesquisaCursoCodigo(int codCursoBusca);

// Apresentacao
void apresentaCurso(Curso curso, int linha, int coluna);
int apresentaTodosCursos(void);
int apresentaDadosCursos(Curso *cursos, int qtdeCursos);
int obtemCursosComAlunosMatriculados();

// Comparacao
int comparaCursosCodigo(const void *p1, const void *p2);
int comparaCursosNome(const void *p1, const void *p2);

// Codigo
int achaProximoCodCurso(void);

#endif
