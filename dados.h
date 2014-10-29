#ifndef DADOS_H
#define DADOS_H
#include <time.h>

// DefiniÃ§Ãµes
#define TAM_NOME_ALUNO 81
#define TAM_NOME_CURSO 51
#define TAM_CPF 12
#define CODIGO_MIN 1001
#define CODIGO_MAX 99999
#define MATRICULA_MIN 1
#define MATRICULA_MAX 9999999
#define CARGA_HORARIA_MIN 30
#define CARGA_HORARIA_MAX 1000
#define MENSALIDADE_MIN 250.0
#define MENSALIDADE_MAX 10000.0
#define MIN_IDADE 15
#define MAX_IDADE 150
#define ARQ_ALUNOS "alunos.b"
#define ARQ_ALUNOS_TEMP "alTemp.b"
#define ARQ_CURSOS "cursos.b"
#define ARQ_MATRICULAS "matriculas.b"
#define MENU_PRINCIPAL "menu.txt"
#define MENU_BUSCA "subMenuBusca.txt"
#define MENU_CADASTRO "subMenuCadastro.txt"
#define MENU_ALTERAR "subMenuAlterar.txt"
#define MENU_EXCLUIR "subMenuExcluir.txt"
#define MENU_LISTA "subMenuLista.txt"

// Estruturas
// Data
typedef struct
{
    int dia, mes, ano;
}Data;

// Aluno
typedef struct
{
    char nome[TAM_NOME_ALUNO], cpf[TAM_CPF], sexo;
    int idade, matricula;
    Data dataIngresso;
}Aluno;

// Curso
typedef struct
{
    char nome[TAM_NOME_CURSO];
    int codigo, cargaHoraria;
    float mensalidade;
}Curso;

// Matricula
typedef struct
{
    int matriculaAluno, codigoCurso;
    char situacaoAluno, situacaoPagamento;
}Cadastro;

//   FunÃ§Ãµes
//  ProtÃ³tipos
int leValidaInteiro(const char *msg, const char *identificacao, int valorMin, int valorMax);
float leValidaReal(const char *msg, const char *identificacao, float valorMin, float valorMax);
void leValidaTexto(char *texto, const char *msg, const char *identificacao, int valorMin, int valorMax);
char leValidaChar(const char *titulo, const char *escolhas);
void strToLower(char *string);
void apresentaMenu(char *nomeArquivo);
void geraDataIngresso(Data *data);

void leDadosCurso(Curso *curso);
void gravaDadosCurso(Curso *curso);
void listaDadosCurso();
int pesquisaCursoCod(int codCursoBusca, int indPrint);
void pesquisaCursoNome(char *nomeBusca);
int achaProximoCodCurso();
void ordenaCursosPeloNome(Curso *cursos, int qtdeCursos);

void leDadosAluno(Aluno *aluno);
void gravaDadosAluno(Aluno *aluno);
void listaDadosAlunos();
int pesquisaAlunoMatricula(int matriculaBusca, int indPrint);
// void pesquisaAlunoNome(char *nomeBusca);
void alteraDadosAluno(int matricula);
void excluiDadosAluno(int matricula);
int validaCPF(const char *cpf);
int verificaCPFAluno(const char *cpf);


/* Ainda nao serao usadas

int leDadosCadastro(Cadastro *cadastro);
void pesquisaCadastro(Cadastro *query, int paramBusca);
void gravaDadosCadastro(Cadastro *cadastro);
void listaDadosCadastro();
*/
#endif
