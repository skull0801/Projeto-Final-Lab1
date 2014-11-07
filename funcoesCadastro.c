// Funcoes relacionadas aos dados de Cadastros

#include <stdio.h>
#include "dados.h"
#include "cores.h"
#include "funcoesBasicas.h"
#include "funcoesCadastro.h"
#include "funcoesCurso.h"
#include "funcoesAluno.h"

//***********************************************************************************************************************
//  Objetivo: Matricular um aluno em um curso
//  Parametros: Nenhum
//  Retorno: Nenhum
void cadastraAlunoEmCurso()
{
    FILE *arqMatriculas;
    int flag, opcao;
    char *opcoesSituacaoAluno[] = {"Cursando",
                                   "Concluiu"};
    char *opcaoSituacaoPagamento[] = {"Regular",
                                      "Atrasada",
                                      "Totalmente Paga"};
    Cadastro matricula;
    matricula.matriculaAluno = apresentaTodosAlunos();
    matricula.codigoCurso = apresentaTodosCursos();
    flag = verificaAlunoRepetidoCadastrando(matricula.codigoCurso, matricula.matriculaAluno);
    if(flag == 0)
    {
        do
        {
            opcao = menuVertical(opcoesSituacaoAluno, 2, BRANCO, AZUL_C, 1, 20, 5, 1, PRETO, CINZA_C);
        }
        while(!opcao);
        matricula.situacaoAluno = opcao + '0';
        do
        {
            opcao = menuVertical(opcaoSituacaoPagamento, 3, BRANCO, AZUL_C, 1, 20, 5, 1, PRETO, CINZA_C);
        }
        while(!opcao);
        
        matricula.situacaoPagamento = opcao + '0';
        gravaDadosMatricula(matricula);
    }
    else
        puts("O aluno ja esta matriculado nesse curso!");
}

//***********************************************************************************************************************
//  Objetivo: Listar todas as matriculas
//  Parametros: Nenhum
//  Retorno: Nenhum
void listaDadosCadastro()
{
    FILE *arq;
    Cadastro matricula;
    int contaMatriculas;
    char situacaoAluno[9], situacaoPagamento[16];
    if((arq = fopen(ARQ_MATRICULAS,"rb")) != NULL)
    {
        printf("%-18s%-19s%-19s%-16s","Codigo do Curso","Matricula Aluno","Situacao do Aluno","Situacao de Pagamento");
        while(!feof(arq))
            if(fread(&matricula, sizeof(Cadastro), 1, arq))
            {
                if(matricula.situacaoAluno == '1')
                    sprintf(situacaoAluno,"Cursando");          
                else
                    sprintf(situacaoAluno,"Concluiu");
                switch(matricula.situacaoPagamento)
                {
                    case '1':
                        sprintf(situacaoPagamento,"Regular");
                        break;
                    case '2':
                        sprintf(situacaoPagamento,"Atrasada");
                        break;
                    case '3':
                        sprintf(situacaoPagamento,"Totalmente paga");
                        break;
                }
                printf("\n%-18d%-19d%-19s%-16s",matricula.codigoCurso, matricula.matriculaAluno, situacaoAluno, situacaoPagamento);
            }
            fclose(arq);
    }
    else
    {
        clrscr();
        puts("Nao ha nenhum aluno matriculado ate o momento");
        return;
    }
}

//***********************************************************************************************************************
//  Objetivo: Gravar os dados de uma matricula(Cadastro)
//  Parametros: A matricula
//  Retorno: Nenhum
void gravaDadosMatricula(Cadastro matricula)
{
    FILE *arq;
    if((arq = fopen(ARQ_MATRICULAS,"ab")) != NULL)
    {
        if(fwrite(&matricula, sizeof(Cadastro), 1, arq))
            puts("Dados cadastrados com sucesso!");
        else
            puts("Os dados nao foram gravados!");
        fclose(arq);
    }
}

//***********************************************************************************************************************
//  Objetivo: Verificar se o aluno ja esta cadastrado em um curso
//  Parametros: O codigo do curso e a matricula do Aluno
//  Retorno: Flag = 1 se o aluno ja estiver cadastrado ou flag = 0 se o aluno nao estiver cadastrado
int verificaAlunoRepetidoCadastrando(int codCurso, int alunoMatricula)
{
    int flag = 0;
    FILE *arq;
    Cadastro matricula;
    if((arq = fopen(ARQ_MATRICULAS,"rb")) != NULL)
    {
        while(!feof(arq))
            if(fread(&matricula, sizeof(Cadastro), 1, arq))
                if(matricula.matriculaAluno == alunoMatricula)
                    if(matricula.codigoCurso == codCurso) 
                        if(matricula.situacaoAluno == '1')
                        {
                            flag =1;
                            break;
                        }
        fclose(arq);
    }
    else
        puts("O arquivo nao pode ser aberto!");
    return flag;
}

//***********************************************************************************************************************
//  Objetivo: Apresentar os dados para a pesquisa de alunos matriculados em um curso
//  Parametros: Nenhum
//  Retorno: Nenhum
void pesquisaAlunosMatriculadosEmUmCurso()
{
    int codigoCurso, indicador;
    char *situacaoAluno[] = {"Cursando",
                            "Concluido",
                            "Ambos"};
    do
    {
        codigoCurso = apresentaTodosCursos();
    }
    while(codigoCurso == 0);
    
    do
    {
        indicador = menuVertical(situacaoAluno, 3, BRANCO, AZUL_C, 1, 20, 5, 1, PRETO, CINZA_C);
    }
    while(indicador == 0);
    apresentaAlunosMatriculadosEmUmCurso(codigoCurso, indicador);
}

//***********************************************************************************************************************
//  Objetivo: Apresentar os todos os alunos matriculados em um curso
//  Parametros: Codigo do curso a ser apresentado e o indicador( 1-Cursando, 2-Concluido e 3-Ambos)
//  Retorno: Nenhum
void apresentaAlunosMatriculadosEmUmCurso(int codCurso, int indicador)
{
    FILE *arq;
    Cadastro matricula;
    int flag, qtdeApresentados = 0;
    char situacaoAluno[9], situacaoPagamento[16];
    if((arq = fopen(ARQ_MATRICULAS,"rb")) != NULL)
    {
        while(!feof(arq))
            if(fread(&matricula, sizeof(Cadastro), 1, arq))
                if(codCurso == matricula.codigoCurso)
                {
                    flag = 0;
                    switch(indicador)
                    {
                        case 1:
                            if(matricula.situacaoAluno == '1')
                                flag = 1;
                            break;
                        case 2:
                            if(matricula.situacaoAluno == '2')
                                flag = 1;
                            break;
                        case 3:
                            flag = 1;
                            break;
                    }
                    if(flag == 1)
                    {
                        qtdeApresentados++;
                        if(matricula.situacaoAluno == '1')
                            sprintf(situacaoAluno,"Cursando");          
                        else
                            sprintf(situacaoAluno,"Concluiu");
                        switch(matricula.situacaoPagamento)
                        {
                            case '1':
                                sprintf(situacaoPagamento,"Regular");
                                break;
                            case '2':
                                sprintf(situacaoPagamento,"Atrasada");
                                break;
                            case '3':
                                sprintf(situacaoPagamento,"Totalmente paga");
                                break;
                        }
                        gotoxy(1,1);
                        printf("\n%-18d%-19d%-19s%-16s",matricula.codigoCurso, matricula.matriculaAluno, situacaoAluno, situacaoPagamento);
                    }
                }    
    }
}
//***********************************************************************************************************************
//  Objetivo: Excluir uma matricula de um aluno em um curso
//  Parametros: Nenhum
//  Retorno: Nenhum
void excluiMatriculaAlunoEmUmCurso()
{
    int codigoCurso, matriculaASerExcluida, qtdeAlunos = 0, flagErro = 0, posMatricula;
    FILE *arq;
    Aluno *alunos = NULL, *alunosAux = NULL, aluno;
    Cadastro matricula;
    do
    {
        codigoCurso = apresentaTodosCursos();
    }
    while(codigoCurso == 0);
    if((arq = fopen(ARQ_MATRICULAS,"rb")) != NULL)
    {
        while(!feof(arq))
        {
            if(fread(&matricula, sizeof(Cadastro), 1, arq))
            {
                if(matricula.codigoCurso == codigoCurso)
                {
                    alunosAux = (Aluno*) realloc(alunos, (qtdeAlunos+1) * sizeof(Aluno));
                    if(alunosAux != NULL)
                    {
                        alunos = alunosAux;
                        posMatricula = pesquisaAlunoMatricula(matricula.matriculaAluno);
                        if(posMatricula)
                        {
                            if(obtemAlunoArquivo(&alunos[qtdeAlunos], posMatricula))
                            {
                                qtdeAlunos++;
                            }
                            else
                            {
                                printf("Nao pode obter aluno!");
                                flagErro = 1;
                                break;
                            }
                        }
                        else
                        {
                            printf("Nao encontrou aluno!");
                            flagErro = 1;
                            break;
                        }
                    }
                    else
                    {
                        printf("Nao alocou memoria!");
                        flagErro = 1;
                        break;
                    }
                }
            }
        }
        fclose(arq);
        if(!flagErro && qtdeAlunos)
        {
            matriculaASerExcluida = apresentaDadosAlunos(alunos, qtdeAlunos);
            //funcao
        }
        if(alunosAux == NULL)
        {
            if(alunos != NULL)
            {
                free(alunos);
            }
        }
        else
        {
            free(alunos);
        }
    }
}
