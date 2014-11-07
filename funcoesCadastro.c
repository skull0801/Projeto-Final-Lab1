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

    if(verificaArquivoVazio(ARQ_CURSOS))
    {
        printf("Nao existem cursos cadastrados!");
        return;
    }
    
    do
    {
        matricula.matriculaAluno = apresentaTodosAlunos();
    }
    while(!matricula.matriculaAluno);
    do
    {
        matricula.codigoCurso = apresentaTodosCursos();
    }
    while(!matricula.codigoCurso);
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
// Objetivo: Verificar se um aluno esta cadastrado em um curso
// Parametros: Matricula do aluno
// Retorno: 1 se aluno esta cadastrado, 0 se nao esta
int verificaAlunoCadastrado(int matriculaAluno)
{
    int flag = 0;
    Cadastro matricula;
    FILE *arq;
    
    if((arq = fopen(ARQ_MATRICULAS,"rb")) != NULL)
    {
        while(!feof(arq))
        {
            if(fread(&matricula, sizeof(Cadastro), 1, arq))
            {
                if(matricula.matriculaAluno == matriculaAluno)
                {
                    flag = 1;
                    break;
                }
            }   
        }
        fclose(arq);   
    }
    
    return flag;
}

//***********************************************************************************************************************
// Objetivo: Verificar se um curso tem um aluno cadastrado
// Parametros: Codigo do curso
// Retorno: 1 se curso tem aluno cadastrado, 0 se nao tem
int verificaCursoAlunoCadastrado(int codigoCurso)
{
    int flag = 0;
    Cadastro matricula;
    FILE *arq;
    
    if((arq = fopen(ARQ_MATRICULAS,"rb")) != NULL)
    {
        while(!feof(arq))
        {
            if(fread(&matricula, sizeof(Cadastro), 1, arq))
            {
                if(matricula.codigoCurso == codigoCurso)
                {
                    flag = 1;
                    break;
                }
            }   
        }
        fclose(arq);   
    }
    
    return flag;
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
        {
            if(fread(&matricula, sizeof(Cadastro), 1, arq))
            {
                if(matricula.matriculaAluno == alunoMatricula)
                {
                    if(matricula.codigoCurso == codCurso)
                    {
                        flag =1;
                        break;
                    }
                }
            }
        }
        fclose(arq);
    }
    return flag;
}

//***********************************************************************************************************************
//  Objetivo: Apresentar os dados para a pesquisa de alunos matriculados em um curso
//  Parametros: Nenhum
//  Retorno: Nenhum
void apresentaAlunosMatriculadosEmUmCurso()
{
    Aluno *alunos;
    int codigoCurso, indicador, qtdAlunos;
    char *situacaoAluno[] = {"Cursando",
                            "Concluido",
                            "Ambos"};
                            
    if(verificaArquivoVazio(ARQ_CURSOS))
    {
        printf("Nao existem cursos cadastrados!");
        getch();
        return;
    }
    
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
    
    if((alunos = obtemAlunosDeCurso(codigoCurso, &qtdAlunos, indicador)) != NULL)
    {
        apresentaDadosAlunos(alunos, qtdAlunos);
        free(alunos);
    }
    if(qtdAlunos == 0)
    {
        puts("Nao ha nenhum aluno cadastrado ate o momento neste curso!");
    }      
}

//***********************************************************************************************************************
// Objetivo: Obter alunos de um curso
// Parametros: Codigo do curso, ponteiro para quantidade de alunos lidos(a ser mudado pela funcao), indicador( 1-Cursando, 2-Concluido e 3-Ambos)
// Retorno: Pointeiro para alunos alocados
Aluno *obtemAlunosDeCurso(int codigoCurso, int *qtdAlunos, int indicador)
{
    Aluno *alunos = NULL, *alunosAux;
    FILE *arq;
    Cadastro matricula;
    int posMatricula, flagErro = 0;
    
    *qtdAlunos = 0;
    
    if((arq = fopen(ARQ_MATRICULAS,"rb")) != NULL)
    {
        while(!feof(arq))
        {
            if(fread(&matricula, sizeof(Cadastro), 1, arq))
            {
                if(matricula.codigoCurso == codigoCurso && (indicador == 3 || indicador + '0' == matricula.situacaoAluno))
                {
                    alunosAux = (Aluno*) realloc(alunos, (*qtdAlunos+1) * sizeof(Aluno));
                    if(alunosAux != NULL)
                    {
                        alunos = alunosAux;
                        posMatricula = pesquisaAlunoMatricula(matricula.matriculaAluno);
                        if(posMatricula)
                        {
                            if(obtemAlunoArquivo(&alunos[*qtdAlunos], posMatricula))
                            {
                                (*qtdAlunos)++;
                            }
                            else
                            {
                                flagErro = 1;
                                break;
                            }
                        }
                        else
                        {
                            flagErro = 1;
                            break;
                        }
                    }
                    else
                    {
                        flagErro = 1;
                        break;
                    }
                }
            }
        }
        fclose(arq);
    }
    if(flagErro)
    {
        if(alunos != NULL)
        {
            free(alunos);
            alunos = NULL;
        }
    }
    return alunos;
}

//***********************************************************************************************************************
//  Objetivo: Excluir uma matricula de um aluno em um curso
//  Parametros: Nenhum
//  Retorno: Nenhum
void excluiMatriculaAlunoEmUmCurso()
{
    int codigoCurso, matriculaASerExcluida, qtdAlunos;
    FILE *arq;
    Aluno *alunos;
    
    if(verificaArquivoVazio(ARQ_CURSOS))
    {
        printf("Nao existem cursos cadastrados!");
        getch();
        return;
    }
    
    do
    {
        codigoCurso = apresentaTodosCursos();
    }
    while(codigoCurso == 0);
    
    if((alunos = obtemAlunosDeCurso(codigoCurso, &qtdAlunos, 3)) != NULL)
    {
        matriculaASerExcluida = apresentaDadosAlunos(alunos, qtdAlunos);
        excluiMatriculaAluno(matriculaASerExcluida, codigoCurso);
        free(alunos);
    }
    else
    {
        puts("Nao ha nenhum aluno cadastrado no curso!");
    }
}

//***********************************************************************************************************************
//  Objetivo: Excluir uma matricula do arquivo
//  Parametros: A posicao da matricula no Arquivo
//  Retorno: Nenhum
void excluiMatriculaAluno(int matriculaAExcluir, int codCurso)
{
    FILE *arq, *arqTemp;
    int qtdeCopiadados;
    Cadastro matricula;
    if(matriculaAExcluir)
    {
        if((arq = fopen(ARQ_MATRICULAS, "rb")) != NULL )
        {
            if((arqTemp = fopen(ARQ_MATRICULAS_TEMP, "wb")) != NULL)
            {
                while(!feof(arq))
                {
                    if(fread(&matricula, sizeof(Cadastro), 1, arq))
                    {
                        qtdeCopiadados++;
                        if(matriculaAExcluir != matricula.matriculaAluno || codCurso!= matricula.codigoCurso)
                            fwrite(&matricula, sizeof(Cadastro), 1, arqTemp);
                    }
                }
            }
            fclose(arqTemp);
            fclose(arq);
        }
                if(!remove(ARQ_MATRICULAS))
                    {
                        if(!rename(ARQ_MATRICULAS_TEMP, ARQ_MATRICULAS))
                            printf("A matricula foi excluida com sucesso!");
                            
                        else
                        {
                            printf("O novo arquivo nao pode ser renomeado, todos os dados foram perdidos!");
                        }
                    }
                    else
                    {
                        printf("O arquivo antigo nao pode ser excluido, logo a matricula nao foi excluida!");
                    }
        }
}

//***********************************************************************************************************************
//  Objetivo: Encontrar a posicao de uma matricula em um arquivo 
//  Parametros: O codigo do curso e a matricula
//  Retorno: A posicao da matricula no arquivo
int pesquisaPosicaoCadastro(int codCurso, int matriculaAluno)
{
    int posMatricula = 0, flag = 0;
    Cadastro matricula;
    FILE *arq;
    
    if((arq = fopen(ARQ_MATRICULAS,"rb")) != NULL)
    {
        while(!feof(arq))
        {
            if(fread(&matricula, sizeof(Cadastro), 1, arq))
            {
                posMatricula++;
                if(matricula.codigoCurso == codCurso)
                {
                    if(matricula.matriculaAluno == matriculaAluno)
                    {
                        flag = 1;
                        break;
                    }
                }
            }   
        }
        fclose(arq);   
    }
  
    if(!flag)
        posMatricula = 0;
    return posMatricula;
}

//***********************************************************************************************************************
// Objetivo: Pesquisar um cadastro especifico
// Parametros: nenhum
// Retorno: nenhum
void pesquisaApresentaCadastro()
{
    int codigoCurso, matriculaAluno, posCadastro;
    Cadastro cadastro;
    
    codigoCurso = leValidaInteiro("Informe o codigo do curso", "Codigo", CODIGO_MIN, CODIGO_MAX);
    
    matriculaAluno = leValidaInteiro("Informe a matricula do aluno", "Matricula", MATRICULA_MIN, MATRICULA_MAX);
    
    posCadastro = pesquisaPosicaoCadastro(codigoCurso, matriculaAluno);
    
    if(posCadastro)
    {
        if(obtemCadastroArquivo(&cadastro, posCadastro))
        {
            apresentaCadastro(cadastro);
        }
        else
        {
            printf("O cadastro nao pode ser recuperado!");
        }
    }
    else
    {
        printf("O cadastro nao foi encontrado!");
    }
}

//***********************************************************************************************************************
//  Objetivo: Apresentar todos os alunos matriculados em todos os cursos
//  Parametros: Nenhum
//  Retorno: Nenhum
void apresentarTodosAlunosCadastrados()
{
    FILE *arq;
    Cadastro *matriculas, matricula, matriculaAux;
    int qtdeMatriculas, contador, auxiliar, flag = 0;
    char situacaoAluno[9], situacaoPagamento[16];
    if((arq = fopen(ARQ_MATRICULAS,"rb")) != NULL)
    {
        if(!fseek(arq, 0, SEEK_END))
        {
            qtdeMatriculas = ftell(arq)/sizeof(Cadastro);
            matriculas = (Cadastro*) malloc(sizeof(Cadastro)*qtdeMatriculas);
            if(matriculas != NULL)
            {
                rewind(arq);
                if(fread(matriculas, sizeof(Cadastro), qtdeMatriculas, arq) != qtdeMatriculas)
                {
                    puts("Nao consegui ler do arquivo!");
                    free(matriculas);
                    matriculas = NULL;
                    flag = 1;
                }
            }
            else
            {
                puts("Nao foi possivel alocar a memoria!");
                flag = 1;   
            }
        }
        fclose(arq);
    }
    else
        flag = 1;
    if(flag)
        puts("Houve um erro, os dados dos alunos nao foram alocados!");
    else
    {
        
        for(contador = 0; contador < qtdeMatriculas-1; contador++)
        {
            for(auxiliar = contador+1; auxiliar < qtdeMatriculas; auxiliar++)
            {
                if(matriculas[contador].codigoCurso < matriculas[auxiliar].codigoCurso)
                {
                    matriculaAux = matriculas[auxiliar];
                    matriculas[auxiliar] = matriculas[contador];                
                    matriculas[contador] = matriculaAux;
                }   
            }   
        }
        printf("%-18s%-19s%-19s%-16s","Codigo do Curso","Matricula Aluno","Situacao do Aluno","Situacao de Pagamento");
        for(contador = 0; contador < qtdeMatriculas; contador++)
        {
            if(matriculas[contador].situacaoAluno == '1')
                        sprintf(situacaoAluno,"Cursando");          
                    else
                        sprintf(situacaoAluno,"Concluiu");
                    switch(matriculas[contador].situacaoPagamento)
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
                    printf("\n%-18d%-19d%-19s%-16s", 
                           matriculas[contador].codigoCurso, matriculas[contador].matriculaAluno, situacaoAluno, situacaoPagamento);
        }          
    }
    if(qtdeMatriculas == 0)
    {
        puts("Nao ha nenhum aluno matriculado neste curso!");
        getch();
    }
}

//***********************************************************************************************************************
//  Objetivo: Alterar dados do cadastro
//  Parametros: Nenhum
//  Retorno: Nenhum
void alteraCadastro()
{
    FILE *arq;
    Cadastro cadastro;
    Aluno *alunos;
    int flag = 0, codigoCurso, qtdeAlunos, matriculaAluno, opcao, opcaoSituacao, posCadastro, escolha;
    char *opcoesSituacaoAluno[] = {"Cursando",
                                   "Concluiu"};
                                   
    char *opcaoSituacaoPagamento[] = {"Regular",
                                      "Atrasada",
                                      "Totalmente Paga"};
                                      
    char *opcoesAlteracao[] = {"Alterar Situacao aluno",
                               "Alterar Situacao da mensalidade",
                               "Salvar alteracoes",
                               "Cancelar Mudancas"};

    if(verificaArquivoVazio(ARQ_CURSOS))
    {
        printf("Nao existem cursos cadastrados!");
        return;
    }
    
    do
    {
        codigoCurso = apresentaTodosCursos();
    }
    while(codigoCurso == 0);
    
    if((alunos = obtemAlunosDeCurso(codigoCurso, &qtdeAlunos, 3)) != NULL)
    {
        do
        {
            matriculaAluno = apresentaDadosAlunos(alunos, qtdeAlunos);
        }
        while(matriculaAluno == 0);
        posCadastro = pesquisaPosicaoCadastro(codigoCurso, matriculaAluno);
        if(posCadastro)
        {
            if(obtemCadastroArquivo(&cadastro, posCadastro))
            {
                do
                {
                    clrscr();
                    apresentaCadastro(cadastro);
                    opcao = menuVertical(opcoesAlteracao, 4, BRANCO, AZUL_C, 1, 48, 1, 1, PRETO, CINZA_C);
                    
                    switch(opcao)
                    {
                        case 1:
                            do
                            {
                                opcaoSituacao = menuVertical(opcoesSituacaoAluno, 2, BRANCO, AZUL_C, 1, 71, 1, 1, PRETO, CINZA_C);
                            }
                            while(!opcaoSituacao);
                            
                            cadastro.situacaoAluno = opcaoSituacao + '0';
                            break; 
                        case 2:
                            do
                            {
                                opcaoSituacao = menuVertical(opcaoSituacaoPagamento, 3, BRANCO, AZUL_C, 1, 64, 1, 1, PRETO, CINZA_C);
                            }
                            while(!opcaoSituacao);
                            
                            cadastro.situacaoPagamento = opcaoSituacao + '0';
                            break;
                    }
                }
                while(opcao == 1 || opcao == 2);
                if(opcao == 3)
                {
                    escolha = confirmaEscolha(55,5, "Voce tem certeza?");
                    if(escolha)
                        alteraDadosCadastro(cadastro, posCadastro);
                    else
                        puts("Os dados nao foram alterados!");
                }
                else
                    puts("Os dados nao foram alterados!");
            }
            else
                puts("A matricula nao pode ser recuperada!");
            
           
        }
        free(alunos);
    }
    else
    {
        puts("Nao ha nenhum aluno cadastrado neste curso ate o momento!");
    }
}

//***********************************************************************************************************************
// Objetivo: Encontrar um cadastro no arquivo
// Parametros: Ponteiro para cadastro, e posicao do cadastro no arquivo
// Retorno: 1 para sucesso, e 0 caso nao tenha encontrado
int obtemCadastroArquivo(Cadastro *matricula, int posCadastro)
{
    FILE *arq;
    int flag = 0;
    if((arq = fopen(ARQ_MATRICULAS, "rb")) != NULL)
    {
        if(!fseek(arq, sizeof(Cadastro)*(posCadastro-1), 0))
        {
            if(fread(matricula, sizeof(Cadastro), 1, arq))
            {
                flag = 1;
            }
        }
        fclose(arq);
    }
    return flag;
}

//***********************************************************************************************************************
// Objetivo: Alterar os dados de um aluno
// Parametros: O Cadastro para alterar e a posicao do aluno no arquivo
// Retorno: 1 para sucesso, e 0 caso nao tenha encontrado
void alteraDadosCadastro(Cadastro matricula, int posCadastro)
{
    FILE *arq;
    int flag = 0;
    if(( arq = fopen(ARQ_MATRICULAS,"rb+")) != NULL)
    {
        if(!fseek(arq, sizeof(Cadastro)*(posCadastro - 1), 0))
        {
            if(fwrite(&matricula, sizeof(Cadastro), 1, arq))
            {
                puts("Os dados foram alterados com sucesso!");   
            }
            else
            {
                puts("Os dados nao puderam ser alterados!");   
            }
        }
        fclose(arq);
    }
}

//  Objetivo: Apresentar os dados de um cadastro
//  Paramentos: O cadastro
//  Retorno: Nenhum
void apresentaCadastro(Cadastro cadastro)
{
    gotoxy(1,1);
    printf("Matricula Aluno: %d\n", cadastro.matriculaAluno);
    printf("Codigo do Curso: %d\n", cadastro.codigoCurso);
    printf("Situacao Financeira: %s\n", cadastro.situacaoPagamento == '1' ? "Regular" : (cadastro.situacaoPagamento == '2' ? "Atrasado" : "Totalmente Pago" ));
    printf("Situacao do Aluno: %s", cadastro.situacaoAluno == '1' ? "Cursando" : "Concluido");
}
