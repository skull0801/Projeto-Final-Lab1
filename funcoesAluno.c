// Funções relacionadas aos dados de alunos

#include <stdio.h>
#include "dados.h"

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
