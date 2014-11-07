// Funcoes basicas

#include <stdio.h>
#include <time.h>
#include "cores.h"
#include "funcoesBasicas.h"

//***********************************************************************************************************************
//  Objetivo: Ler e validar um numero inteiro
//  Parametros: Referencia a uma mensagem, referencia a identificacao do numero inteiro, valor minimo e valor maximo
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
            printf("%s deve estar entre %d e %d!\n",identificacao, valorMin, valorMax);
    }
    while(num < valorMin || num > valorMax);
    
    return num;
}

//***********************************************************************************************************************
//  Objetivo: Ler e validar um numero Inteiro
//  Parametros: Referencia a uma mensagem, referencia a identificacao do numero real, valor minimo e valor maximo
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
            printf("%s deve estar entre %.2f e %.2f!\n",identificacao,valorMin,valorMax);
    }
    while(num < valorMin || num > valorMax);
    
    return num;
}

//***********************************************************************************************************************
//  Objetivo: Ler e validar um texto
//  Parametros: Referencia a uma mensagem, a identificacao,ao texto, o tamanho minimo e o tamanho maximo do texto
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
//  Parametros: Referencia a mensagem, e a string de escolhas
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
// Objetivo: Registra a data atual
// Parametros: Referencia a uma estrutura de data para guardar a data atual
// Retorno: nenhum
void geraDataIngresso(Data *data)
{
    time_t tempoBruto;
    struct tm *tempoAtual;
    time(&tempoBruto);
    tempoAtual = localtime(&tempoBruto);
    data->dia = tempoAtual->tm_mday;
    data->mes = tempoAtual->tm_mon+1;
    data->ano = tempoAtual->tm_year+1900;
}

//***********************************************************************************************************************
// Objetivo: Passar uma string para minusculo
// Parametros: String a ser passada
// Retorno: nenhum
void strToLower(char *string)
{
    for(;*string;string++)
        *string = tolower(*string);
}

//***********************************************************************************************************************
// Objetivo: Fazer um menu e lidar com as escolhas do usuario
// Parametros: opcoes - Opcoes do menu
//             qtdOpcoes - quantidade de opcoes
//             corL - cor da letra do menu
//             corS - cor da selecaoda opcao do menu
//             moldura - indicador se havera moldura 
//             coluna - coluna inicial da moldura do menu
//             linha - linha inicial da moldura do menu
//             selInicial - selecao inicial da opcao
//             corFundoAtual - cor do fundo antes da chamada do menu
//             corLetraAtual - cor da letra antes da chamada do menu
// Retorno: Indice escolhido pelo usuario, de 1 a n, ou 0 caso esc seja pressionado
int menuVertical(char *opcoes[], int qtdOpcoes, int corLetra, int corSelecao, int moldura, int coluna, int linha, 
         int selecaoInicial, int corFundoAtual, int corLetraAtual)
{
    int contador;
    int val; // Indica se a tecla pressionada e relevante ao menu
    int tecla; // Registra a tecla que o usuario pressionou
    int tamMaiorOpcao; // Registra o tamanho da maior opcao escrita
    int selecao; // Registra o item selecionado no momento
    int ultimaSelecao; // Registra a ultima selecao do menu
    int offset = 2; // Distancia entre moldura e texto do menu
    
    if(linha == 1 && moldura) // Verifica se necessita moldura e comeca na linha 1, se sim move a linha por 1 para nao causar erros ao fazer moldura
        linha += offset;
    if(coluna == 1 && moldura) // Faz o mesmo que para linha com coluna
        coluna += offset;
        
    textcolor(corLetra); // Define a cor das letras do menu
    
    if(selecaoInicial < 1)                  // Valida a selecao inicial
        selecaoInicial = 1;
    else if(selecaoInicial > qtdOpcoes)
        selecaoInicial = qtdOpcoes;
    
    selecao = selecaoInicial - 1;
    
    textbackground(corFundoAtual);
    
    for(contador=0;contador<qtdOpcoes;contador++)
    {
        gotoxy(coluna, linha+contador);
        printf(opcoes[contador]);
        
        if(!contador)
            tamMaiorOpcao = strlen(opcoes[contador]); // Inicializa tamMaiorOpcao com o primeiro tamanho
        else if(strlen(opcoes[contador]) > tamMaiorOpcao)
            tamMaiorOpcao = strlen(opcoes[contador]); // Verifica o tamanho do maior texto escrito
    }            
    
    gotoxy(coluna, linha+selecao);                  // Seleciona
    textbackground(corSelecao);                     // a posicao
    printf("%-*s", tamMaiorOpcao, opcoes[selecao]); // atual
    
    if(moldura)
        desenhaMoldura(linha-(offset), coluna-(offset), linha+contador+(offset-1), coluna+tamMaiorOpcao+(offset-1), corFundoAtual, corLetra);  // Desenha moldura se necessario
    
    do
    {
        do
        {
            tecla = toupper(getch());
            if(tecla == 72 || tecla == 75 || tecla == 77 || tecla == 80 || tecla == 27 || tecla == 13) // Verifica se a tecla pressionada ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â© relevante (72 - cima, 75 - esquerda, 77 - direita, 80 - baixo)
                val = 1;                                                                               // 27 - esc, 13 - enter
            else
                val = 0;
        }
        while(!val); // Repete ate que uma tecla valida seja pressionada
        
        ultimaSelecao = selecao; // Guarda a ultima selecao antes de muda-la
        if(tecla == 72 || tecla == 75)
            selecao--;
        else if(tecla == 77 || tecla == 80)
            selecao++;
        else if(tecla == 27)
            ultimaSelecao = -1; // O usuario pressionou esc, ou seja nao selecionou nada
        
        if(selecao <= -1)
            selecao = qtdOpcoes-1;  // Se for menor vai para o ultimo item
        else if(selecao >= qtdOpcoes)
            selecao = 0;   // Se for maior vai para o primeiro item
            
        textcolor(corLetra);
        if(tecla != 13 && tecla != 27) // Se o usuario pressionou algo diferente de enter ou esc, fazer a mudanca necessaria
        {
            gotoxy(coluna, linha+ultimaSelecao);                        // Deseleciona
            textbackground(corFundoAtual);                              // a ultima
            printf("%-*s", tamMaiorOpcao, opcoes[ultimaSelecao]);       // opcao
            
            gotoxy(coluna, linha+selecao);                              // Seleciona
            textbackground(corSelecao);                                 // a posicao
            printf("%-*s", tamMaiorOpcao, opcoes[selecao]);             // atual
            
            fflush(stdin); // Limpa o buffer do teclado
        }
    }
    while(tecla != 13 && tecla != 27);  // Repete enquanto um item nao for selecionado ou esc nao for pressionado
    
    if(moldura)
        limpaJanela(linha-(offset), coluna-(offset), linha+qtdOpcoes+(offset-1), coluna+tamMaiorOpcao+(offset-1), corFundoAtual);
    else
        limpaJanela(linha, coluna, linha+qtdOpcoes, coluna+tamMaiorOpcao, corFundoAtual);
    
    return ultimaSelecao+1; // Retorna o item selecionado (Retorna 0 se foi pressionado esc)
}

//***********************************************************************************************************************
// Objetivo: Desenha uma moldura
// Parametros: linha inicial, coluna inicial , linha final , coluna final, cor do fundo da janela e cor da letra(moldura)
// Retorno: nenhum
void desenhaMoldura(int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal, int corFundo, int corLetra)
{
    int contador, qtdLinhas, qtdColunas;
    qtdLinhas = linhaFinal - linhaInicial;
    qtdColunas = colunaFinal - colunaInicial;
    
    textbackground(corFundo);
    textcolor(corLetra);
    
    for(contador=1;contador<qtdColunas;contador++)
    {
        gotoxy(colunaInicial+contador, linhaInicial);
        printf("%c", 205);
        gotoxy(colunaInicial+contador, linhaFinal);
        printf("%c", 205);
    }
    
    for(contador=1;contador<qtdLinhas;contador++)
    {
        gotoxy(colunaInicial, linhaInicial+contador);
        printf("%c", 186);
        gotoxy(colunaFinal, linhaInicial+contador);
        printf("%c", 186);
    }
    
    gotoxy(colunaInicial, linhaInicial);
    printf("%c", 201);
    gotoxy(colunaFinal, linhaInicial);
    printf("%c", 187);
    gotoxy(colunaInicial, linhaFinal);
    printf("%c", 200);
    gotoxy(colunaFinal, linhaFinal);
    printf("%c", 188);
}

//***********************************************************************************************************************
// Objetivo: Limpar uma parte da janela
// Parametros: linha inicial, coluna inicial, linha final, coluna final e cor da janela
// Retorno: nenhum
void limpaJanela(int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal, int corFundo)
{
    int linha, coluna;
    textbackground(corFundo);
    for(linha = linhaInicial; linha <= linhaFinal; linha++)
    {
        for(coluna = colunaInicial; coluna <= colunaFinal; coluna++)
        {
            gotoxy(coluna, linha);
            printf(" ");
        }
    }
    gotoxy(1,1);
}

//***********************************************************************************************************************
// Objetivo: Confirmar uma escolha do usuario
// Parametros: Coluna e linha onde a confirmacao deve comecar, e referencia ao titulo
// Retorno: 1 para confirma, 0 para nao confirma
int confirmaEscolha(int coluna, int linha, char *titulo)
{
    char *opcoesConfirma[] = {"Sim", "Nao"};
    int resposta;
    
    gotoxy(coluna, linha);
    printf("%-*.*s", 80-coluna, 80-coluna, titulo);
    resposta = menuVertical(opcoesConfirma, 2, BRANCO, AZUL_C, 1, coluna+6, linha+3, 2, PRETO, CINZA_E);
    if(resposta != 1)
        resposta = 0;
    return resposta;
}

//***********************************************************************************************************************
// Objetivo: Verifica se um arquivo esta vazio
// Parametros: Nome do Arquivo
// Retorno: 1 se esta vazio ou nao existe e 0 se existe e nao esta vazio
int verificaArquivoVazio(char *nomeArquivo)
{
    int flag = 1;
    FILE *arq;
    if((arq = fopen(nomeArquivo, "rb")) != NULL)
    {
        if(!fseek(arq, 0, SEEK_END))
        {
            if(ftell(arq)>0)
            {
                flag = 0;
            }
        }
        fclose(arq);
    }
    return flag;
}
