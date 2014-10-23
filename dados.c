#include <stdio.h>
#include <conio.c>
#include "dados.h"
//  Funções

//  Objetivo: Ler e validar um numero inteiro
//  Parâmetros: Referencia à uma mensagem, referência à identificacao do numero inteiro, valor minimo e valor maximo
//  Retorno: O numero inteiro validado
int leValidaInteiro(const char *msg, const char *identificacao, int valorMin, int valorMax)
{
    int ret, num;
    do
    {
        do
        {
            printf("%s: ",msg);
            fflush(stdin);
            ret = scanf("%d",&num);
            fflush(stdin);
            clrscr();
            if(ret != 1) 
                printf("%s deve ser um numero!\n",identificacao);
        }
        while(ret == 0);
        
        if(num < valorMin || num > valorMax)
            printf("%s deve estar entre %d e %d!!!\n",identificacao, valorMin, valorMax);
    }
    while(num < valorMin || num > valorMax);
    
    return num;
}

//***********************************************************************************************************************
//  Objetivo: Ler e validar um numero Inteiro
//  Parâmetros: Referencia à uma mensagem, referência à identificacao do numero real, valor minimo e valor maximo
//  Retorno: O numero real validado
float leValidaReal(const char *msg, const char *identificacao, float valorMin, float valorMax)
{
    int ret;
    float num;
    do
    {
        do
        {
            printf("%s: ",msg);
            fflush(stdin);
            ret = scanf("%f",&num);
            fflush(stdin);
            clrscr();
            if(ret != 1) 
                printf("%s deve ser um numero real!\n",identificacao);
        }
        while(ret == 0);
        
        if(num < valorMin || num > valorMax)
            printf("%s deve estar entre %.2f e %.2f!!!\n",identificacao,valorMin,valorMax);
    }
    while(num < valorMin || num > valorMax);
    
    return num;
}
//***********************************************************************************************************************
//  Objetivo: Ler e validar um texto
//  Parâmetros: Referencia à uma mensagem, à identificacao,ao texto, o tamanho minimo e o tamanho maximo do texto
//  Retorno: Nenhum
void leValidaTexto(char *texto, const char *msg, const char *identificacao, int valorMin, int valorMax)
{
    int flag;
    do
    {
        fflush(stdin);
        printf("%s: ",msg);
        fgets(texto,valorMax,stdin);
        clrscr();
        if(texto[strlen(texto)-1] == '\n')
            texto[strlen(texto)-1] = '\0';
        if(strlen(texto) < valorMin)
            printf("%s deve ter pelo menos %d caracteres!\n", identificacao, valorMin);
    }
    while(strlen(texto) < valorMin);
    fflush(stdin);
}

//***********************************************************************************************************************
//  Objetivo: Ler e validar um caractere
//  Parâmetros: Referencia à mensagem, e à string de escolhas
//  Retorno: Caractere validado (MAIUSCULO)
char leValidaChar(const char *titulo, const char *escolhas)
{
    char caractere;
	printf("%s", titulo);
    do
    {
        fflush(stdin);
        caractere = toupper(getch());
    }
    while(strchr(escolhas, caractere)==0);
    clrscr();
    return caractere;
}

//***********************************************************************************************************************
//  Objetivo: Pesquisar um curso dentro de um arquivo por código único
//  Parâmetros: codigo a ser pesquisado, e indicador se o dado encontrado deve ser escrito (não zero para sim)
//  Retorno: 1 - codigo foi encontrado, 0 - codigo nao encontrado
int pesquisaCursoCod(int codCursoBusca, int indPrint)
{
    FILE *arq;
    Curso curso;
    int flag = 0;
    if((arq = fopen(ARQ_CURSOS, "rb")) != NULL)
    {
        while(!feof(arq))
            if(fread(&curso, sizeof(Curso), 1, arq))
                if(codCursoBusca == curso.codigo)
                {
                    if(indPrint)
                    printf("Nome do Curso: %s\nCodigo: %d\nCarga Horaria: %d\nValor da mensalidade: %.2f\n", curso.nome, curso.codigo, curso.cargaHoraria, curso.mensalidade);
                    flag = 1;
                    break;
                }
        fclose(arq);
    }
    return flag;
}

//***********************************************************************************************************************
//  Objetivo: Ler os dados de um curso
//  Parâmetros: Referência a um curso
//  Retorno: 0 se os dados foram lidos com sucesso ou 1 se houve algum erro
void leDadosCurso(Curso *curso)
{
    leValidaTexto(curso->nome, "Informe o nome do curso", "Curso", 3, TAM_NOME_CURSO);
    curso->cargaHoraria = leValidaInteiro("Informe a carga horaria", "Carga Horaria", CARGA_HORARIA_MIN, CARGA_HORARIA_MAX);
    curso->mensalidade = leValidaReal("Informe o valor da mensalidade","Mensalidade",MENSALIDADE_MIN,MENSALIDADE_MAX);
    curso->codigo = achaProximoCodCurso();
}

//***********************************************************************************************************************
//  Objetivo: Encontrar o proximo código valido de um curso
//  Parâmetros: Nenhum
//  Retorno: próximo código valido
int achaProximoCodCurso()
{
    int codigo = 1001;
    Curso curso;
    FILE *arq;
    if(( arq = fopen(ARQ_CURSOS, "rb")) != NULL)
    {
        while(!feof(arq))
            if(fread(&curso, sizeof(Curso), 1, arq))
            {
                if(codigo != curso.codigo)
                    break;
                codigo++;
            }
        fclose(arq);
    }
    return codigo;
}

//***********************************************************************************************************************
//  Objetivo: Gravar os dados de um curso num arquivo
//  Parâmetros: Referência a um curso
//  Retorno: Nenhum
void gravaDadosCurso(Curso *curso)
{
    FILE *arq;
    if((arq = fopen(ARQ_CURSOS,"ab")) != NULL)
    {
        if(fwrite(curso, sizeof(Curso), 1, arq))
            puts("Os dados foram gravados com sucesso!");
        else
            puts("Os dados nao puderam ser gravados!");
        fclose(arq);
    }
}

//***********************************************************************************************************************
//  Objetivo: Listar os dados de todos os cursos
//  Parâmetros: nenhum
//  Retorno: Nenhum
void listaDadosCurso()
{
    FILE *arq;
    Curso curso;
    int qtdeApresentados = 0;
    printf("%-50s%-9s%-10s%-11s\n","Nome","Codigo","Horas","Mensalidade");
    if((arq = fopen(ARQ_CURSOS,"rb")) != NULL)
    {
        while(!feof(arq))
            if(fread(&curso, sizeof(Curso), 1, arq))
            {
                printf("%-50s%-9d%-10d%-11.2f\n",curso.nome,curso.codigo,curso.cargaHoraria,curso.mensalidade);
                qtdeApresentados++;
            }
        fclose(arq);
    }
    if(!qtdeApresentados)
    {
        clrscr();
        puts("Nao ha nenhum curso cadastrado ate o momento!");    
    }
}

//***********************************************************************************************************************
//  Objetivo: Pesquisar um aluno dentro de um arquivo por matricula
//  Parâmetros: matricula a ser pesquisada, indicador se o dado encontrado deve ser escrito (não zero para sim)
//  Retorno: 1 - matricula foi encontrada, 0 - codigo nao encontrada
int pesquisaAlunoMatricula(int matriculaBusca, int indPrint)
{
    FILE *arq;
    Aluno aluno;
    int flag = 0;
    if((arq = fopen(ARQ_CURSOS, "rb")) != NULL)
    {
        while(!feof(arq))
            if(fread(&aluno, sizeof(Aluno), 1, arq))
                if(matriculaBusca == aluno.matricula)
                {
                    if(indPrint)
                        // TODO Formatar dados saida aluno
                        printf("");
                    flag = 1;
                    break;
                }
        fclose(arq);
    }
    return flag;
}
