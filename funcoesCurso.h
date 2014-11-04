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
void ordenaCursosPeloNome(Curso *cursos, int qtdeCursos);
void alteraCurso(void);
void alteraDadosCurso(Curso curso, int posCurso);
void apresentaCurso(Curso curso);

#endif
