// Prototipos para funcoes basicas
#ifndef FUNCOESBASICAS_H
#define FUNCOESBASICAS_H
#include "dados.h"

int leValidaInteiro(const char *msg, const char *identificacao, int valorMin, int valorMax);
float leValidaReal(const char *msg, const char *identificacao, float valorMin, float valorMax);
void leValidaTexto(char *texto, const char *msg, const char *identificacao, int valorMin, int valorMax);
char leValidaChar(const char *titulo, const char *escolhas);
void strToLower(char *string);
void apresentaMenu(char *nomeArquivo);
void geraDataIngresso(Data *data);
int menuVertical(char *opcoes[], int qtdOpcoes, int corLetra, int corSelecao, int moldura, int coluna, int linha, int selecaoInicial, int corFundoAtual, int corLetraAtual);
void desenhaMoldura(int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal, int corFundo, int corLetra);
void limpaJanela(int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal, int corFundo);
char * leStringEmCampo(int limite);
int verificaArquivoVazio(char *nomeArquivo);
int confirmaEscolha(int coluna, int linha, char *titulo);

#endif
