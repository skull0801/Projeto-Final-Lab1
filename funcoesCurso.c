// Funções relacianadas aos dados de cursos

#include <stdio.h>
#include "dados.h"

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
//  Objetivo: Encontrar o proximo código valido de um curso
//  Parâmetros: Nenhum
//  Retorno: próximo código valido
int achaProximoCodCurso()
{
    int codigo = CODIGO_MIN;
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
//  Objetivo: Listar os dados de todos os cursos
//  Parâmetros: nenhum
//  Retorno: Nenhum
void listaDadosCurso()
{
    FILE *arq;
    Curso curso;
    int qtdeApresentados = 0;
    printf("%-50s%-7s%-7s%-10s\n","Nome","Codigo","Horas","Mensalidade");
    if((arq = fopen(ARQ_CURSOS,"rb")) != NULL)
    {
        while(!feof(arq))
            if(fread(&curso, sizeof(Curso), 1, arq))
            {
                printf("%-50s%-7d%-7d%-10.2f\n",curso.nome,curso.codigo,curso.cargaHoraria,curso.mensalidade);
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
//  Objetivo: Pesquisar um curso dentro de um arquivo por código único
//  Parâmetros: codigo a ser pesquisado, e indicador se o dado encontrado deve ser escrito (não zero para sim)
//  Retorno: numero positivo se encontrado(posição do curso de 1 a n, sendo n o numero de cursos), 0 - codigo nao encontrado
int pesquisaCursoCod(int codCursoBusca, int indPrint)
{
    FILE *arq;
    Curso curso;
    int pos = 0;
    if((arq = fopen(ARQ_CURSOS, "rb")) != NULL)
    {
        while(!feof(arq))
            if(fread(&curso, sizeof(Curso), 1, arq))
            {
            	pos++;
                if(codCursoBusca == curso.codigo)
                {
                    if(indPrint)
                    	printf("Nome do Curso: %s\nCodigo: %d\nCarga Horaria: %d\nValor da mensalidade: %.2f\n", curso.nome, curso.codigo, curso.cargaHoraria, curso.mensalidade);
                    flag = 1;
                    break;
                }
            }
        fclose(arq);
    }
    if(indPrint && !pos)
        printf("O curso nao foi encontrado!");
    return pos;
}

//***********************************************************************************************************************
//  Objetivo: Pesquisar um curso dentro de um arquivo por nome
//  Parâmetros: nome a ser pesquisado
//  Retorno: nenhum
void pesquisaCursoNome(char *nomeBusca)
{
    FILE *arq;
    Curso curso;
    int qtdCorrespondencias = 0;
    char copiaNome[TAM_NOME_CURSO];
    
    strToLower(nomeBusca);
    printf("%-50s%-7s%-7s%-10s\n","Nome","Codigo","Horas","Mensalidade");
    
    if((arq = fopen(ARQ_CURSOS, "rb")) != NULL)
    {
        while(!feof(arq))
            if(fread(&curso, sizeof(Curso), 1, arq))
            {
                strcpy(copiaNome, curso.nome);
                strToLower(copiaNome);
                if(strstr(copiaNome, nomeBusca))
                {
                    
                    printf("%-50s%-7d%-7d%-10.2f\n",curso.nome,curso.codigo,curso.cargaHoraria,curso.mensalidade);
                    qtdCorrespondencias++;
                }
            }
            
        fclose(arq);
    }
    
    if(!qtdCorrespondencias)
    {
        clrscr();
        printf("O curso nao foi encontrado!");
    }
}
