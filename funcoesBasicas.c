// Funcoes basicas

#include <stdio.h>
#include <conio.h>
#include "cores.h"
#include "dados.h"
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
// Objetivo: Ler uma string com limite
// Parametros: tamanho maximo
// Retorno: Endereco para a string alocada dinamicamente
char * leStringEmCampo(int limite)
{
    char *string = NULL, *stringAux, caractere;
    int contador = 0, qtdCaracteres = 0;
    do
    {
        stringAux = (char *)realloc(string, sizeof(char)*(qtdCaracteres+1));
        contador = qtdCaracteres;
        
        if(stringAux != NULL)
        {
            string = stringAux;
            fflush(stdin);
            caractere = getch();
            if(caractere==8)
            {
                if(qtdCaracteres>0)
                {
                    printf("\b \b");
                    qtdCaracteres--;
                }
            }
            else if(qtdCaracteres<limite && caractere>=32 || caractere == 13)
            {
                string[qtdCaracteres++] = caractere;
                putc(caractere, stdout);
            }
        }
        else
            break;
    }
    while(string[contador]!=13);
    
    if(stringAux == NULL && string != NULL)
    {
        free(string);
        string = NULL;
    }
    
    if(string != NULL)
        string[contador] = '\0';
        
    return string;
}

//***********************************************************************************************************************
// Objetivo: Transformar uma string em uma data
// Parametros: Referencia para uma estrutura de data, e a uma string
// Retorno: 1 se a transformacao foi possivel, 0 se nao foi possivel
int transformaStringEmData(Data *data, char *dataTexto)
{
    char aux[5];
    int retorno = 0;
    if(strlen(dataTexto) == 10)
    {
        strncpy(aux, dataTexto, 2);
        aux[2] = '\0';
        data->dia = atoi(aux);
        
        if(data->dia > 0 && dataTexto[2] == '/')
        {
            strncpy(aux, dataTexto+3, 2);
            aux[2] = '\0';
            data->mes = atoi(aux);
            
            if(data->mes > 0 || data->mes == 0 && dataTexto[10] == '0' && dataTexto[5] == '/')
            {
                strncpy(aux, dataTexto+6, 4);
                aux[4] = '\0';
                data->ano = atoi(aux);
                
                if(data->ano > 0)
                    retorno = 1;
            }
        }
    }

    return retorno;
}

//***********************************************************************************************************************
// Objetivo: Validar uma data
// Parametros: Uma estrutura data
// Retorno: 1 se a data for valida, 0 se for invalida
int validaData(Data data)
{
    int retorno = 1;

    if(data.ano < 0 || data.mes<1 || data.mes >12 || data.dia >31)
       return 0;

    switch(data.mes)
    {
       case 4:
       case 6:
       case 9:
       case 11:
            if(data.dia > 30)
               retorno = 0;

            break;
       case 2:
            if((data.ano%4 == 0 && data.ano%100 !=0) ||(data.ano % 400 == 0))
            {
               if(data.dia >29)
                  retorno = 0;
            }      
            else
            {
               if(data.dia >28)
                  retorno = 0;                                      
            }

            break;      
    }

    return retorno;
}

//***********************************************************************************************************************
// Objetivo: Ler e validar uma data
// Parametros: Referencia ao titulo a ser mostrado
// Retorno: Data valida
Data leValidaData(const char *titulo)
{
    int flag;
    char *dataTexto, aux[5];
    Data data;

    do
    {
        printf("%s: ", titulo);
        dataTexto = leStringEmCampo(10);
        if(transformaStringEmData(&data, dataTexto))
            flag = validaData(data);
        else
            flag = 0;
        clrscr();
        
        if(!flag)
            printf("Esta nao e uma data valida!\n");

        free(dataTexto);
    }
    while(!flag);

    return data;
}

//***********************************************************************************************************************
// Objetivo: Compara duas datas
// Parametros: Duas datas
// Retorno: < 0 se primeira for menor que a segunda, 0 se as duas forem iguais, > 0 se a primeiro for maior que a segunda
int comparaDatas(Data d1, Data d2)
{
    return d1.ano - d2.ano ? d1.ano - d2.ano : (d1.mes - d2.mes ? d1.mes - d2.mes : (d1.dia - d2.dia ? d1.dia - d2.dia : 0));
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
// Parametros: titulo - Titulo do menu
//             opcoes - Opcoes do menu
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
int menuVertical(const char *titulo, char *opcoes[], int qtdOpcoes, int corLetra, int corSelecao, int moldura, int coluna, int linha, 
         int selecaoInicial, int corFundoAtual, int corLetraAtual)
{
    int contador;
    int val; // Indica se a tecla pressionada e relevante ao menu
    int tecla; // Registra a tecla que o usuario pressionou
    int tamMaiorOpcao; // Registra o tamanho da maior opcao escrita
    int selecao; // Registra o item selecionado no momento
    int ultimaSelecao; // Registra a ultima selecao do menu
    int colunaTitulo, linhaTitulo, tamTitulo; // Registram a posicao do titulo do menu
    int offset = 2; // Distancia entre moldura e texto do menu
    
    if(linha == 1 && moldura) // Verifica se necessita moldura e comeca na linha 1, se sim move a linha por 1 para nao causar erros ao fazer moldura
        linha += offset;
    if(coluna == 1 && moldura) // Faz o mesmo que para linha com coluna
        coluna += offset;
    
    linha+=1; // Cria espaco para titulo
    linhaTitulo = linha-1;
        
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
    {
        desenhaMoldura(linha-(offset), coluna-(offset), linha+contador+(offset-1), coluna+tamMaiorOpcao+(offset-1), corFundoAtual, corLetra);  // Desenha moldura se necessario
        linhaTitulo -= 2;
    }

    // Escreve titulo do menu
    if(strlen(titulo))
    {
        colunaTitulo = coluna+(tamMaiorOpcao/2)-(strlen(titulo)/2);
        colunaTitulo = colunaTitulo > 0 ? colunaTitulo : 1;
        tamTitulo = strlen(titulo)+colunaTitulo > 80 ? 80-colunaTitulo : strlen(titulo);
        gotoxy(colunaTitulo, linhaTitulo);
        printf("%-*.*s", tamTitulo, tamTitulo, titulo);
    }

    do
    {
        do
        {
            tecla = toupper(getch());
            if(tecla == 72 || tecla == 75 || tecla == 77 || tecla == 80 || tecla == 27 || tecla == 13) // Verifica se a tecla pressionada e relevante (72 - cima, 75 - esquerda, 77 - direita, 80 - baixo)
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
    
    if(strlen(titulo))    
        limpaJanela(linhaTitulo, colunaTitulo, linhaTitulo, colunaTitulo+tamTitulo, corFundoAtual); // Limpa titulo do menu
    
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
    resposta = menuVertical(titulo, opcoesConfirma, 2, BRANCO, AZUL_C, 1, coluna, linha, 2, PRETO, CINZA_E);
    if(resposta != 1)
        resposta = 0;
    return resposta;
}

//***********************************************************************************************************************
// Objetivo: Apresentar uma mensagem no meio da tela esperando um prompt do usuario
// Parametros: Referencia ao texto a ser escrito
// Retorno: Nenhum
void apresentaMensagem(char *mensagem)
{
    int linhas, linhaInicial, contador, tamLinha;
    if(strlen(mensagem)>25)
    {
        for(contador = 20;mensagem[contador]!=' ';contador++);
        tamLinha = contador;
    }
    else
        tamLinha = strlen(mensagem);
    linhas = strlen(mensagem)/tamLinha + 1;
    desenhaMoldura(12-linhas, 40-tamLinha/2-2, 12+linhas, 40+tamLinha/2+2, PRETO, BRANCO);
    linhaInicial = 12-linhas/2;
    for(contador=0;contador<linhas;contador++)
    {
        gotoxy(40-tamLinha/2, linhaInicial+contador);
        printf("%-*.*s", tamLinha, tamLinha, mensagem+(contador*tamLinha));
    }
    getch();
    limpaJanela(12-linhas, 40-tamLinha/2-2, 12+linhas, 40+tamLinha/2+2, PRETO);
}

//***********************************************************************************************************************
// Objetivo: Gravar dado em arquivo
// Parametros: Nome do arquivo, Ponteiro void para o dado, Tamando do dado
// Retorno: 1 se o dado foi gravado, 0 se o dado nao foi gravado
int gravaDadoArquivo(const char *nomeArquivo, const void *dado, int tamanhoDado)
{
    FILE *arq;
    int retorno = 0;

    if((arq = fopen(nomeArquivo,"ab")) != NULL)
    {
        if(fwrite(dado, tamanhoDado, 1, arq) == 1)
            retorno = 1;
        fclose(arq);
    }
    return retorno;
}

//***********************************************************************************************************************
//  Objetivo: Alterar os dados de um arquivo em uma posicao
//  Parametros: Nome do arquivo, Ponteiro void para o dado, Tamanho do dado, Posicao do dado no arquivo
//  Retorno: 1 se o dado foi alterado, 0 se o dado nao foi alterado
int alteraDadoArquivo(const char *nomeArquivo, const void *dado, int tamanhoDado, int posDado)
{
    FILE *arq;
    int retorno = 0;

    if((arq = fopen(nomeArquivo, "rb+")) != NULL)
    {
        if(!fseek(arq, tamanhoDado*(posDado-1), SEEK_SET))
        {
            if(fwrite(dado, tamanhoDado, 1, arq) == 1)
                retorno = 1;
        }
        else
            apresentaMensagem("O dado nao pode ser encontrado no arquivo!");

        fclose(arq);
    }
    else
        apresentaMensagem("O arquivo nao pode ser aberto para ser alterado!");
    
    return retorno;
}

//***********************************************************************************************************************
//  Objetivo: Excluir um dado de um arquivo
//  Parametros: Nome do arquivo, Tamando do dado, Posicao do dado no arquivo
//  Retorno: 1 se o dado foi excluido, 0 se o dado nao foi excluido
int excluiDadoArquivo(const char *nomeArquivo, int tamanhoDado, int posDado)
{
    FILE *arq, *arqTemp, *arqBackup;
    int qtdCopiados = 0, qtdBytesArquivo, retorno = 0, flag = 0;
    void *dado, *dadosBackup;
    
    if((dado = malloc(tamanhoDado)) != NULL)
    {
        if((arq = fopen(nomeArquivo, "rb")) != NULL)
        {
            if((arqTemp = fopen(ARQ_TEMP, "wb")) != NULL)
            {
                while(!feof(arq))
                {
                    if((fread(dado, tamanhoDado, 1, arq)) == 1)
                    {
                        qtdCopiados++;
                        if(posDado != qtdCopiados)
                            if(fwrite(dado, tamanhoDado, 1, arqTemp) != 1)
                                flag = 1;
                    }
                }
                
                fclose(arqTemp);
                
                if((arqBackup = fopen(ARQ_BACKUP, "wb")) != NULL)
                {
                    qtdBytesArquivo = ftell(arq);
                    if((dadosBackup = malloc(qtdBytesArquivo)) != NULL)
                    {
                        rewind(arq);
                        if(fread(dadosBackup, qtdBytesArquivo, 1, arq))
                        {
                            fclose(arq);
                            if(fwrite(dadosBackup, qtdBytesArquivo, 1, arqBackup))
                            {
                                fclose(arqBackup);
                                if(remove(nomeArquivo) == 0)
                                {
                                    if(rename(ARQ_TEMP, nomeArquivo) == 0)
                                    {
                                        retorno = 1;
                                        remove(ARQ_BACKUP);
                                    }
                                    else if(rename(ARQ_BACKUP, nomeArquivo) == 0)
                                        apresentaMensagem("O dado nao pode ser removido!");
                                    else
                                        apresentaMensagem("O dado nao pode ser removido mas os dados foram perdidos!");
                                }
                                else
                                    apresentaMensagem("O arquivo original nao pode ser removido!");
                            }
                            else
                                apresentaMensagem("Os dados de backup nao puderam ser copiados!");
                        }
                        else
                            apresentaMensagem("Os dados de backup nao puderam ser lidos!");
                    }
                    else
                    {
                        apresentaMensagem("A memoria para guardar os dados de backup nao pode ser alocada!");
                        fclose(arq);
                        fclose(arqBackup);
                    }
                }
                else
                {
                    apresentaMensagem("O arquivo de backup nao pode ser criado!");
                    fclose(arq);
                }
            }
            else
            {
                apresentaMensagem("O arquivo temporario nao pode ser criado!");
                fclose(arq);
            }
        }
        else
            apresentaMensagem("O arquivo nao pode ser aberto!");
            
        free(dado);
    }
    else
        apresentaMensagem("O arquivo nao pode ser lido!");
        
    return retorno;
}

//***********************************************************************************************************************
// Objetivo: Obter um dado de um arquivo em certa posicao
// Parametros: Nome do arquivo, ponteiro para aonde os dados serao guardados, tamanho do dado, posicao do dado no arquivo
// Retorno: 1 para sucesso, e 0 caso nao tenha encontrado
int obtemDadoArquivo(const char *nomeArquivo, void *dado, int tamanhoDado, int posDado)
{
    FILE *arq;
    int flag = 0;

    if((arq = fopen(nomeArquivo, "rb")) != NULL)
    {
        if(!fseek(arq, tamanhoDado*(posDado-1), 0))
        {
            if(fread(dado, tamanhoDado, 1, arq))
            {
                flag = 1;
            }
        }
        fclose(arq);
    }
    return flag;
}

//***********************************************************************************************************************
// Objetivo: Obter todos os dados de arquivo
// Parametros: Nome do arquivo, Tamanho do dado, Referencia a quantidade de dados (valor sera dado pela funcao)
// Retorno: Ponteiro para memoria alocada na qual os dados estao
void *obtemDadosArquivo(const char *nomeArquivo, int tamanhoDado, int * qtdDados)
{
    FILE *arq;
    void *dados = NULL;
    
    if((arq = fopen(nomeArquivo, "rb")) != NULL)
    {
        if(!fseek(arq, 0, SEEK_END))
        {
            *qtdDados = (ftell(arq)/tamanhoDado);
            
            if(*qtdDados>0 && ftell(arq)%tamanhoDado == 0)
            {
                dados = malloc(tamanhoDado*(*qtdDados));
                
                if(dados != NULL)
                {
                    rewind(arq);
                    if(fread(dados, tamanhoDado, *qtdDados, arq) != *qtdDados)
                    {
                        apresentaMensagem("Erro ao recuperar os dados!");
                        free(dados);
                        dados = NULL;
                        *qtdDados = 0;
                    }
                }
                else
                    apresentaMensagem("Erro ao alocar memoria para dados!");
            }
            else
                apresentaMensagem("Nao existem dados no arquivo ou o arquivo esta corrompido!");
        }
        else
            apresentaMensagem("Erro ao obter quantidade de dados.");
            
        fclose(arq);
    }
    else
        apresentaMensagem("Erro ao abrir o arquivo de dados.");
        
    return dados;
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
