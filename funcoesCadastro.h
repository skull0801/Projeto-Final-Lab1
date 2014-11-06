// Prototipos para funcoes de cadastros
#ifndef FUNCOESCADASTRO_H
#define FUNCOESCADASTRO_H
#include "dados.h"

void cadastraAlunoEmCurso();
void listaDadosCadastro();
void gravaDadosMatricula(Cadastro matricula);
void apresentaAlunosMatriculadosEmUmCurso();
int verificaAlunoRepetidoCadastrando(int codCurso, int alunoMatricula);
void apresentaAlunosMatriculadosEmUmCurso();
void excluiMatriculaAluno(int matricula, int codCurso);
void apresentarTodosAlunosCadastrados();
void alteraDadosCadastro();
int obtemCadastroArquivo(Cadastro *matricula, int posCadastro);
Aluno *obtemAlunosDeCurso(int codigoCurso, int *qtdAlunos, int indicador);

#endif
