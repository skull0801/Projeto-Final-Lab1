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
void pesquisaCurso(void);
void pesquisaApresentaCursoCodigo(void);
void pesquisaApresentaCursoNome(void);
int pesquisaCursoCodigo(int codCursoBusca);

// Apresentacao
void apresentaCurso(Curso curso);
int apresentaTodosCursos(void);
int apresentaDadosCursos(Curso *cursos, int qtdeCursos);

// Obtencao do arquivo
Curso * obtemDadosCursosArquivo(int * qtdCursos);

// Comparacao
int comparaCursosCodigo(const void *p1, const void *p2);
int comparaCursosNome(const void *p1, const void *p2);

// Codigo
int achaProximoCodCurso(void);

#endif
