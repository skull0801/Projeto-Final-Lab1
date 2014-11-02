// Prototipos para funcoes de cursos
#ifndef FUNCOESCURSO_H
#define FUNCOESCURSO_H
#include "dados.h"

void leDadosCurso(Curso *curso);
void gravaDadosCurso(Curso *curso);
void listaDadosCurso();
int pesquisaCursoCod(int codCursoBusca, int indPrint);
void pesquisaCursoNome(char *nomeBusca);
int achaProximoCodCurso();
void ordenaCursosPeloNome(Curso *cursos, int qtdeCursos);
void alteraDadosCurso(int codigoBusca);

#endif
