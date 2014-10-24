#ifndef DADOS_H
#define DADOS_H
#include <time.h>

// Definições
#define TAM_NOME_ALUNO 81
#define TAM_NOME_CURSO 51
#define TAM_CPF 12
#define CODIGO_MIN 1001
#define CODIGO_MAX 99999
#define CARGA_HORARIA_MIN 20
#define CARGA_HORARIA_MAX 1000
#define MENSALIDADE_MIN 100
#define MENSALIDADE_MAX 100000
#define ARQ_ALUNOS "alunos.txt"
#define ARQ_CURSOS "cursos.txt"
#define ARQ_MATRICULAS "mat.txt"
#define MENU_PRINCIPAL "menu.txt"
#define MENU_BUSCA "subMenuBusca.txt"
#define MENU_CADASTRO "subMenuCadastro.txt"
#define MENU_LISTA "subMenuLista.txt"

// Estruturas
// Aluno
typedef struct
{
    char nome[TAM_NOME_ALUNO], cpf[TAM_CPF], sexo;
    int idade, matricula;
    struct tm dataIngresso;
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

/*  Funções
//  Protótipos
int leValidaInteiro(const char *msg, const char *identificacao, int valorMin, int valorMax);
float leValidaReal(const char *msg, const char *identificacao, float valorMin, float valorMax);
void leValidaTexto(char *texto, const char *msg, const char *identificacao, int valorMin, int valorMax);
char leValidaChar(const char *titulo, const char *escolhas);

void leDadosCurso(Curso *curso);
void gravaDadosCurso(Curso *curso);
void listaDadosCurso();
int pesquisaCursoCod(int codCursoBusca, int indPrint);
void pesquisaCursoNome(char *nomeBusca);

void apresentaMenu(char *nomeArquivo);

// Funcionais
void strToLower(char *string);

// Ainda nao serao usadas

int leDadosAluno(Aluno *aluno);
void gravaDadosAluno(Aluno *aluno);
void listaDadosAlunos();
void pesquisaAlunoNome(char *nomeBusca);
int pesquisaAlunoMatricula(int matriculaBusca, int indPrint);

int leDadosCadastro(Cadastro *cadastro);
void pesquisaCadastro(Cadastro *query, int paramBusca);
void gravaDadosCadastro(Cadastro *cadastro);
void listaDadosCadastro();
*/

#endif
