// Prototipos para funcoes de cadastros
#ifndef FUNCOESCADASTRO_H
#define FUNCOESCADASTRO_H
#include "dados.h"

void cadastraAlunoEmCurso();
void listaDadosCadastro();
void gravaDadosMatricula(Cadastro matricula);
int verificaAlunoRepetidoCadastrando(Curso curso, Aluno aluno);

#endif
