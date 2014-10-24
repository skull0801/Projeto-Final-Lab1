// Funções basicas

#include <stdio.h>
#include "dados.h"

//***********************************************************************************************************************
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
// Objetivo: Passar uma string para minusculo
// Parâmetros: String a ser passada
// Retorno: nenhum
void strToLower(char *string)
{
    for(;*string;string++)
        *string = tolower(*string);
}

//***********************************************************************************************************************
// Objetivo: Apresentar menu contido em um arquivo
// Parâmetros: Nome do arquivo de menu
// Retorno: nenhum
void apresentaMenu(char *nomeArquivo)
{
    FILE * menu;
    char caractere;
    clrscr();
    if((menu = fopen(nomeArquivo, "r")) != NULL)
    {
        while(!feof(menu) && (caractere = getc(menu)) != EOF)
            putc(caractere, stdout);
        fclose(menu);
    }
}
