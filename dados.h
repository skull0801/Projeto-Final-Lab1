#ifndef DADOS_H
#define DADOS_H

// Definicoes
#define TAM_NOME_ALUNO 51
#define TAM_NOME_CURSO 51
#define TAM_CPF 12
#define TAM_TEXTO_TABELA 75
#define LINHAS_TABELA 15
#define LINHA_TABELA 5
#define COLUNA_TABELA 1
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
#define ARQ_TEMP "temp.b"
#define ARQ_BACKUP "back.b"
#define ARQ_ALUNOS "alunos.b"
#define ARQ_CURSOS "cursos.b"
#define ARQ_MATRICULAS "matriculas.b"

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

#endif
