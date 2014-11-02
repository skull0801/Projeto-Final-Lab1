// Prototipos para funcoes de cursos
#ifndef FUNCOESCURSO_H
#define FUNCOESCURSO_H
#include "dados.h"

void cadastraCurso(void);
void leDadosCurso(Curso *curso);
void gravaDadosCurso(Curso *curso);
void listaDadosCurso();
void excluiCurso(void);
void excluiDadosCurso(int posCurso);
void pesquisaCurso(void);
int pesquisaCursoCod(int codCursoBusca);
void pesquisaCursoNome(char *nomeBusca);
int achaProximoCodCurso();
void ordenaCursosPeloNome(Curso *cursos, int qtdeCursos);
void alteraCurso(void);
void alteraDadosCurso(Curso curso, int posCurso);
void apresentaCurso(Curso curso);

#endif
