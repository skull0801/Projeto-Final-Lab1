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

#endif
