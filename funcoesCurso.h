// Prototipos para funcoes de cursos
#ifndef FUNCOESCURSO_H
#define FUNCOESCURSO_H
#include "dados.h"

void cadastraCurso(void);
void leDadosCurso(Curso *curso);
void gravaDadosCurso(Curso *curso);
void listaDadosCursos();
void excluiCurso(void);
void excluiDadosCurso(int posCurso);
void pesquisaCurso(void);
int pesquisaCursoCodigo(int codCursoBusca);
void pesquisaApresentaCursoCodigo(void);
void pesquisaApresentaCursoNome(void);
int achaProximoCodCurso();
int apresentaTodosCursos(void);
int apresentaDadosCursos(Curso *cursos, int qtdeCursos);
void ordenaCursosPorNome(Curso *cursos, int qtdeCursos);
void alteraCurso(void);
void alteraDadosCurso(Curso curso, int posCurso);
void apresentaCurso(Curso curso);
int obtemCursoArquivo(Curso *curso, int posCurso);
Curso * obtemDadosCursosArquivo(int * qtdCursos);
int comparaCursosCodigo(const void *p1, const void *p2);
int comparaCursosNome(const void *p1, const void *p2);

#endif
