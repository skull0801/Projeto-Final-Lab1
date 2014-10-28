// FunÃ§Ãµes relacionadas aos dados de alunos

#include <stdio.h>
#include "dados.h"

//***********************************************************************************************************************
//  Objetivo: Pesquisar um aluno dentro de um arquivo por matricula
//  ParÃ¢metros: matricula a ser pesquisada, indicador se o dado encontrado deve ser escrito (nÃ£o zero para sim)
//  Retorno: numero positivo se encontrado (posicao do aluno no arquivo de 1 a n, sendo n o numero de alunos), 0 - codigo nao encontrado
int pesquisaAlunoMatricula(int matriculaBusca, int indPrint)
{
    FILE *arq;
    Aluno aluno;
    int pos = 0, flag = 0;
    if((arq = fopen(ARQ_CURSOS, "rb")) != NULL)
    {
        while(!feof(arq))
            if(fread(&aluno, sizeof(Aluno), 1, arq))
            {
                pos++;
                if(matriculaBusca == aluno.matricula)
                {
                    if(indPrint)
                        // TODO Formatar dados saida aluno
                        printf("");
                    flag = 1;
                    break;
                }
            }
        fclose(arq);
    }
    if(indPrint && !flag)
        printf("O aluno nao foi encontrado!");
    return pos;
}
