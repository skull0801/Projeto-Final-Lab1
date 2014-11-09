// Prototipos para funcoes basicas
#ifndef FUNCOESBASICAS_H
#define FUNCOESBASICAS_H
#include "dados.h"

// Leitura de dados
int leValidaInteiro(const char *msg, const char *identificacao, int valorMin, int valorMax);
float leValidaReal(const char *msg, const char *identificacao, float valorMin, float valorMax);
void leValidaTexto(char *texto, const char *msg, const char *identificacao, int valorMin, int valorMax);
char leValidaChar(const char *titulo, const char *escolhas);
char * leStringEmCampo(int limite);

// Datas
int transformaStringEmData(Data *data, char *dataTexto);
int validaData(Data data);
Data leValidaData(const char *titulo);
int comparaDatas(Data d1, Data d2);

// Tranformacao de dados
void strToLower(char *string);

// Menus e limpeza de menus
int menuVertical(const char *titulo, char *opcoes[], int qtdOpcoes, int corLetra, int corSelecao, int moldura, int coluna, int linha, int selecaoInicial, int corFundoAtual, int corLetraAtual);
void desenhaMoldura(int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal, int corFundo, int corLetra);
void limpaJanela(int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal, int corFundo);
int confirmaEscolha(int coluna, int linha, char *titulo);

// Arquivo
int gravaDadoArquivo(const char *nomeArquivo, const void *dado, int tamanhoDado);
int alteraDadoArquivo(const char *nomeArquivo, const void *dado, int tamanhoDado, int posDado);
int excluiDadoArquivo(const char *nomeArquivo, int tamanhoDado, int posDado);
int obtemDadoArquivo(const char *nomeArquivo, void *dado, int tamanhoDado, int posDado);
void * obtemDadosArquivo(const char *nomeArquivo, int tamanhoDado, int * qtdDados);
void * obtemDadosArquivoCondicao(const char *nomeArquivo, int tamanhoDado, int *qtdDados, void *dadoCondicao, int (*condicao)(const void *p1, const void *p2));
int verificaArquivoVazio(char *nomeArquivo);

#endif
