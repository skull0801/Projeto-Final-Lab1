// Funcoes relacionadas aos dados de Cadastros

#include <stdio.h>
#include <conio.h>
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
void cadastraAlunoEmCurso(void)
{
    FILE *arqMatriculas;
    int flag = 0, opcao;
    char *opcoesSituacaoAluno[] = {"Cursando",
                                   "Concluiu"};
    char *opcaoSituacaoPagamento[] = {"Regular",
                                      "Atrasada",
                                      "Totalmente Paga"};
    Cadastro cadastro;
    
    memset(&cadastro, 0, sizeof(Cadastro));
    
    cadastro.matriculaAluno = selecionaAluno();

    if(cadastro.matriculaAluno)
    {
        cadastro.codigoCurso = selecionaCurso();
        
        if(cadastro.codigoCurso)
        {
            flag = verificaAlunoRepetidoCadastrando(cadastro.codigoCurso, cadastro.matriculaAluno);

            if(flag == 0)
            {
                opcao = alteraDadosCadastro(&cadastro);

                if(opcao == 1)
                {
                    if(gravaDadoArquivo(ARQ_MATRICULAS, (void*) &cadastro, sizeof(Cadastro)))
                        apresentaMensagem("O aluno foi matriculado com sucesso!");
                    else
                        apresentaMensagem("O aluno nao pode ser matriculado!");
                }
                else
                    apresentaMensagem("O aluno nao foi matriculado!");
            }
            else
                apresentaMensagem("O aluno ja esta matriculado nesse curso!");
        }
        else
            apresentaMensagem("O aluno nao foi matriculado!");
    }
}

//***********************************************************************************************************************
//  Objetivo: Alterar dados do cadastro
//  Parametros: Nenhum
//  Retorno: Nenhum
void alteraCadastro(void)
{
    FILE *arq;
    Cadastro cadastro, *cadastros;
    int flag = 0, codigoCurso = 0, qtdeCadastros, matriculaAluno, opcao, opcaoSituacao, posCadastro, escolha;
    
    char *opcoesSelecao[] = {"Dentre Todos os Cursos com Alunos", 
                             "Pesquisar por Nome", 
                             "Voltar"};

    codigoCurso = selecionaCurso();
    
    if(codigoCurso)
    {
        if((cadastros = obtemAlunosDeCurso(codigoCurso, &qtdeCadastros, 3)) != NULL)
        {
            matriculaAluno = apresentaDadosCadastros(cadastros, qtdeCadastros);

            posCadastro = pesquisaPosicaoCadastro(codigoCurso, matriculaAluno);

            if(posCadastro)
            {
                if(obtemDadoArquivo(ARQ_MATRICULAS, (void *) &cadastro, sizeof(Cadastro), posCadastro))
                {
                    opcao = alteraDadosCadastro(&cadastro);

                    if(opcao == 1)
                    {
                        escolha = confirmaEscolha(35,12, "Realmente deseja salvar?");
                        if(escolha == 1)
                        {
                            if(alteraDadoArquivo(ARQ_MATRICULAS, (void *) &cadastro, sizeof(Cadastro), posCadastro))
                                apresentaMensagem("A matricula foi alterada com sucesso!");
                            else
                                apresentaMensagem("A matricula nao foi alterada!");
                        }
                        else
                            apresentaMensagem("A matricula nao foi alterada!");
                    }
                    else
                        apresentaMensagem("A matricula nao foi alterada!");
                    limpaJanela(1, 1, 10, 80, PRETO);
                }
                else
                    apresentaMensagem("A matricula nao pode ser recuperada!");
            }
            free(cadastros);
        }
        else
            apresentaMensagem("O curso nao tem alunos cadastrados!");
    }
}

//***********************************************************************************************************************
// Objetivo: Permitir ao usuario alterar os dados de uma matricula
// Parametros: Endereco de uma matricula
// Retorno: 1 se o usuario decidiu salvar os dados, 0 se o usuario desejou cancelar
int alteraDadosCadastro(Cadastro *cadastro)
{
    int opcao = 1;
    int pos [4][2] = {5-1,5+9, 5+43-1,5+9, 5+20-1,5+14, 5+40-1, 5+14};
    char opcaoSituacao;

    char *opcoesSituacaoAluno[] = {"Cursando",
                                   "Concluiu"};
                                   
    char *opcaoSituacaoPagamento[] = {"Regular",
                                      "Atrasada",
                                      "Totalmente Paga"};
    char *sexos[] = {"MASCULINO", "FEMININO"};
    do
    {
        apresentaCadastro(*cadastro, 5, 5);
        
        gotoxy(5+20, 5+14);
        printf("Salvar");
        
        gotoxy(5+40, 5+14);
        printf("Cancelar");

        opcao = simulaMenu(pos, 4, opcao);
        
        switch(opcao)
        {
            case 1:
                do
                {
                    limpaJanela(5+9, 5+12, 5+11, 5+30, PRETO); 
                    opcaoSituacao = menuVertical("", opcaoSituacaoPagamento, 3, BRANCO, AZUL_C, 1, 5+14, 5+9, 1, PRETO, CINZA_C);
                }
                while(!opcaoSituacao);
                
                cadastro->situacaoPagamento = opcaoSituacao + '0';
                break;
                
            case 2:
                do
                {
                    limpaJanela(5+8, 5+54, 5+10, 5+65, PRETO);
                    opcaoSituacao = menuVertical("", opcoesSituacaoAluno, 2, BRANCO, AZUL_C, 1, 5+56, 5+9, 1, PRETO, CINZA_C);
                }
                while(!opcaoSituacao);
                
                cadastro->situacaoAluno = opcaoSituacao + '0';
                break; 
        }    
        
        limpaJanela(5-1, 5-1, (5)+14, 5+51+14, PRETO);   

        if(opcao == 3 && (!cadastro->situacaoAluno || !cadastro->situacaoPagamento))
        {
            apresentaMensagem("Voce deve preencher todos os campos!");
            opcao = 1;
        }

        if(opcao == 0 || opcao == 4)
        {
            if(confirmaEscolha(40, 12, "Deseja cancelar?") == 0)
                opcao = 1;
        }
    }
    while(opcao == 1 || opcao == 2);

    return opcao == 3 ? 1 : 0;
}

//***********************************************************************************************************************
//  Objetivo: Excluir uma matricula de um aluno em um curso
//  Parametros: Nenhum
//  Retorno: Nenhum
void excluiMatriculaAlunoEmUmCurso(void)
{
    int codigoCurso = 0, matriculaASerExcluida, qtdCadastros, posCadastro, confirmacao, opcao;
    FILE *arq;
    Cadastro *cadastros;
    
    char *opcoesSelecao[] = {"Dentre Todos os Cursos com Alunos", 
                             "Pesquisar por Nome", 
                             "Voltar"};

    codigoCurso = selecionaCurso();
    
    if(codigoCurso)
    {
        if((cadastros = obtemAlunosDeCurso(codigoCurso, &qtdCadastros, 3)) != NULL)
        {
            matriculaASerExcluida = apresentaDadosCadastros(cadastros, qtdCadastros);
            
            if(matriculaASerExcluida)
            {
                posCadastro = pesquisaPosicaoCadastro(codigoCurso, matriculaASerExcluida);

                if(posCadastro)
                {
                    confirmacao = confirmaEscolha(40, 12, "Realmente deseja excluir?");
                    
                    limpaJanela(1, 1, 10, 80, PRETO);
                    
                    if(confirmacao == 1)
                    {
                        if(excluiDadoArquivo(ARQ_MATRICULAS, sizeof(Cadastro), posCadastro))
                            apresentaMensagem("A matricula foi excluida com sucesso!");
                        else
                            apresentaMensagem("A matricula nao pode ser excluida!");
                    }
                    else
                        apresentaMensagem("A matricula nao foi excluida!");
                }
                else
                    apresentaMensagem("A matricula nao pode ser excluida!!");
            }
            free(cadastros);
        }
        else
            apresentaMensagem("Nao ha nenhum aluno cadastrado no curso!");
    }
    limpaJanela(1, 1, 10, 80, PRETO);
}

//***********************************************************************************************************************
// Objetivo: Pesquisar um cadastro especifico
// Parametros: nenhum
// Retorno: nenhum
void pesquisaApresentaCadastro(void)
{
    int codigoCurso, matriculaAluno, posCadastro;
    Cadastro cadastro;
    
    codigoCurso = leValidaInteiro("Informe o codigo do curso", "Codigo", CODIGO_MIN, CODIGO_MAX);
    
    matriculaAluno = leValidaInteiro("Informe a matricula do aluno", "Matricula", MATRICULA_MIN, MATRICULA_MAX);
    
    posCadastro = pesquisaPosicaoCadastro(codigoCurso, matriculaAluno);
    
    if(posCadastro)
    {
        if(obtemDadoArquivo(ARQ_MATRICULAS, (void *) &cadastro, sizeof(Cadastro), posCadastro))
            apresentaCadastro(cadastro, 5, 5);
        else
            apresentaMensagem("O cadastro nao pode ser recuperado!");
    }
    else
        apresentaMensagem("O cadastro nao foi encontrado!");
    
}

//***********************************************************************************************************************
//  Objetivo: Apresentar os dados de um cadastro
//  Paramentos: O cadastro
//  Retorno: Nenhum
void apresentaCadastro(Cadastro cadastro, int linha, int coluna)
{
    Aluno aluno;
    Curso curso;
    char sit = cadastro.situacaoPagamento;
    int posAluno, posCurso;
    
    if(posAluno = pesquisaAlunoMatricula(cadastro.matriculaAluno))
    {
        if(obtemDadoArquivo(ARQ_ALUNOS, &aluno, sizeof(Aluno), posAluno))
        {
            desenhaMoldura(linha-1, coluna+12, linha+1, coluna+14+TAM_NOME_ALUNO, PRETO, BRANCO);
            gotoxy(coluna, linha);
            printf("Aluno:");
            gotoxy(coluna+14, linha);
            printf("%-*.*s\n", TAM_NOME_ALUNO-1, TAM_NOME_ALUNO-1, strlen(aluno.nome) ? aluno.nome : "[Ex. Jose da Silva]");
        }
    }
    
    if(posCurso = pesquisaCursoCodigo(cadastro.codigoCurso))
    {
        if(obtemDadoArquivo(ARQ_CURSOS, &curso, sizeof(Curso), posCurso))
        {
            desenhaMoldura(linha+2, coluna+12, linha+4, coluna+14+TAM_NOME_CURSO, PRETO, BRANCO);
            gotoxy(coluna, linha+3);
            printf("Curso:");
            gotoxy(coluna+14, linha+3);
            printf("%-*.*s\n", TAM_NOME_CURSO-1, TAM_NOME_CURSO-1, strlen(curso.nome) ? curso.nome : "[Ex. Curso ABC]");
        }
    }
    
    desenhaMoldura(linha+5, coluna+47, linha+7, coluna+65, PRETO, BRANCO);
    gotoxy(coluna+36, linha+6);
    printf("Matricula:");
    gotoxy(coluna+49, linha+6);
    if(cadastro.matriculaAluno)
        printf("%06d\n", cadastro.matriculaAluno);
    else
        printf("%-*.*s\n", 10, 10, "[Ex. 010]");

    desenhaMoldura(linha+5, coluna+12, linha+7, coluna+9+10+5, PRETO, BRANCO);
    gotoxy(coluna, linha+6);
    printf("Codigo:");
    gotoxy(coluna+14, linha+6);
    if(cadastro.codigoCurso)
        printf("%06d\n", cadastro.codigoCurso);
    else
        printf("%-*.*s\n", 10, 10, "[Ex. 0100]");
    
    desenhaMoldura(linha+8, coluna+12, linha+10, coluna+30, PRETO, BRANCO);
    gotoxy(coluna, linha+9);
    printf("Financeiro:");
    gotoxy(coluna+14, linha+9);
    printf("%-*.*s\n", 16, 16, sit == '1' ? "Regular" : (sit == '2' ? "Atrasado" : (sit == '3' ? "Totalmente Pago" : "" )));

    desenhaMoldura(linha+8, coluna+54, linha+10, coluna+65, PRETO, BRANCO);
    gotoxy(coluna+43, linha+9);
    printf("Conclusao:");
    gotoxy(coluna+56, linha+9);
    printf("%-*.*s\n", 9, 9, cadastro.situacaoAluno == '1' ? "Cursando" : (cadastro.situacaoAluno == '2' ? "Concluiu" : ""));
}

//***********************************************************************************************************************
//  Objetivo: Apresentar todos os alunos matriculados
//  Parametros: nenhum
//  Retorno: nenhum
void apresentaTodosAlunosCadastrados(void)
{
    Cadastro *cadastros;
    int qtdCadastros = 0, matriculaSelecionada = 0;
    if((cadastros = (Cadastro *) obtemDadosArquivo(ARQ_MATRICULAS, sizeof(Cadastro), &qtdCadastros)) != NULL)
    {
        apresentaDadosCadastros(cadastros, qtdCadastros);
        free(cadastros);
    }
}

//***********************************************************************************************************************
//  Objetivo: Apresentar todos os alunos matriculados em um curso
//  Parametros: Ponteiro para cadastros alocados, quantidade de cadastros
//  Retorno: Matricula do aluno selecionado
int apresentaDadosCadastros(Cadastro *cadastros, int qtdeCadastros)
{
    int contador, flag = 0, qtdeLinhasAlocadas = 0, qtdeItens, selecao, matriculaSelecionada = 0, posAluno;
    char **linhasTabela, titulo[TAM_TEXTO_TABELA+1], matriculaTexto[7];
    Aluno aluno;
    
    sprintf(titulo,"%-9s%-18s%-29s%-13s%-10s", "Matr.", "CPF", "Nome Aluno", "Situacao", "Codigo");
    
    if(qtdeCadastros > 0)
    {
        linhasTabela = (char **)malloc(sizeof(char*)*qtdeCadastros);
        if(linhasTabela != NULL)
        {
            
            for(contador = 0; contador < qtdeCadastros; contador++)
            {
                posAluno = pesquisaAlunoMatricula(cadastros[contador].matriculaAluno);
                if(obtemDadoArquivo(ARQ_ALUNOS, &aluno, sizeof(Aluno), posAluno))
                {
                    linhasTabela[contador] = (char *)malloc(sizeof(char)*(TAM_TEXTO_TABELA+1));
                    if(linhasTabela[contador] != NULL)
                    {
                        sprintf(linhasTabela[contador], "%06d   %3.3s.%3.3s.%3.3s-%2.2s   %-29.27s%-15.15s%-06d", aluno.matricula, aluno.cpf, 
                        aluno.cpf+3, aluno.cpf+6, aluno.cpf+9, aluno.nome, 
                        cadastros[contador].situacaoAluno == '1' ? "Cursando" : "Concluiu", cadastros[contador].codigoCurso);
                        qtdeLinhasAlocadas++;
                    }
                    else
                    {
                        apresentaMensagem("A memoria para as linhas nao puderam ser alocadas!");
                        flag = 1;
                        break;
                    }
                }
                else
                {
                    apresentaMensagem("Um aluno nao pode ser recuperado");
                    flag = 1;
                    break;
                    
                }
            }
        }
        else
        {
            apresentaMensagem("A memoria nao pode ser alocadas!");
            flag = 1;
        }
        
        if(!flag)
        {
            for(contador=0;contador<qtdeCadastros;contador+=LINHAS_TABELA)
            {
                qtdeItens = qtdeCadastros - contador > LINHAS_TABELA ? LINHAS_TABELA : qtdeCadastros - contador;
                
                if(contador+LINHAS_TABELA<qtdeCadastros)
                {
                    gotoxy(45, LINHA_TABELA+qtdeItens+3);
                    printf("Pressione Esc para ver o restante!");
                }

                selecao = menuVertical(titulo, &linhasTabela[contador], qtdeItens, BRANCO, AZUL_C, 1, COLUNA_TABELA, LINHA_TABELA, 1, PRETO, CINZA_C);
                
                limpaJanela(LINHA_TABELA+qtdeItens+3, 45, LINHA_TABELA+qtdeItens+3, 80, PRETO);
                
                if(selecao != 0)
                {
                    strncpy(matriculaTexto, linhasTabela[contador+selecao-1], 6);
                    matriculaTexto[6] = '\0';
                    matriculaSelecionada = atoi(matriculaTexto);
                    break;
                }
                else if(contador+LINHAS_TABELA<qtdeCadastros)
                {
                    if(!confirmaEscolha(40, 12, "Deseja ver o restante das Matriculas?"))
                        break;
                }
            }
        }
        
        if(linhasTabela != NULL)
        {
            for(contador=0;contador<qtdeLinhasAlocadas;contador++)
                free(linhasTabela[contador]);
            free(linhasTabela);
        }
    }
    
    return matriculaSelecionada;
}

//***********************************************************************************************************************
//  Objetivo: Apresentar os dados para a pesquisa de alunos matriculados em um curso
//  Parametros: Nenhum
//  Retorno: Nenhum
void apresentaAlunosMatriculadosEmUmCurso(void)
{
    Cadastro *cadastros;
    int codigoCurso, indicador, qtdCadastros;
    char *situacaoAluno[] = {"Cursando",
                             "Concluido",
                             "Ambos"};
    
    codigoCurso = selecionaCurso();
    
    if(codigoCurso)
    {
        indicador = menuVertical("Qual a situacao de curso que deseja?", situacaoAluno, 3, BRANCO, AZUL_C, 1, 20, 5, 1, PRETO, CINZA_C);
        
        if(indicador)
        {
            if((cadastros = obtemAlunosDeCurso(codigoCurso, &qtdCadastros, indicador)) != NULL)
            {
                apresentaDadosCadastros(cadastros, qtdCadastros);
                free(cadastros);
            }
            else if(qtdCadastros == 0)
            {
                apresentaMensagem("Nao ha nenhum aluno cadastrado ate o momento neste curso com a situacao escolhida!");
            }
        }
    }
}

//***********************************************************************************************************************
//  Objetivo: Apresentar matriculados com a situacao financeira indicada
//  Parametros: Nenhum
//  Retorno: Nenhum
void apresentaAlunosPorSituacao(void)
{
    Cadastro *cadastros;
    int indicador, qtdCadastros;
    char *situacaoAluno[] = {"Regular",
                             "Atrasada",
                             "Totalmente Paga"};
    
    indicador = menuVertical("Qual a situacao de pagamento que deseja?", situacaoAluno, 3, BRANCO, AZUL_C, 1, 20, 5, 1, PRETO, CINZA_C);
    
    if(indicador)
    {
        if((cadastros = obtemAlunosPorSituacaoPagamento(&qtdCadastros, indicador)) != NULL)
        {
            gotoxy(COLUNA_TABELA+1, LINHA_TABELA-4);
            printf("Alunos com situacao financeira: %s", situacaoAluno[indicador-1]);
            apresentaDadosCadastros(cadastros, qtdCadastros);
            limpaJanela(LINHA_TABELA-4, COLUNA_TABELA+1, LINHA_TABELA-4, 75, PRETO);
            free(cadastros);
        }
        if(qtdCadastros == 0)
        {
            apresentaMensagem("Nao ha nenhum aluno cadastrado com esta situacao!");;
        }
    }
}

//***********************************************************************************************************************
// Objetivo: Obter cadastros de um curso
// Parametros: Codigo do curso, ponteiro para quantidade de cadastros lidos(a ser mudado pela funcao), indicador( 1-Cursando, 2-Concluido e 3-Ambos)
// Retorno: Pointeiro para cadastros alocados
Cadastro *obtemAlunosDeCurso(int codigoCurso, int *qtdCadastros, int indicador)
{
    Cadastro *cadastros = NULL, *cadastrosAux, cadastro;
    FILE *arq;
    
    *qtdCadastros = 0;
    
    if((arq = fopen(ARQ_MATRICULAS,"rb")) != NULL)
    {
        while(!feof(arq))
        {
            if(fread(&cadastro, sizeof(Cadastro), 1, arq))
            {
                if(cadastro.codigoCurso == codigoCurso && (indicador == 3 || indicador + '0' == cadastro.situacaoAluno))
                {
                    cadastrosAux = (Cadastro*) realloc(cadastros, (*qtdCadastros+1) * sizeof(Cadastro));
                    if(cadastrosAux != NULL)
                    {
                        cadastros = cadastrosAux;
                        cadastros[*qtdCadastros] = cadastro;
                        (*qtdCadastros)++;
                    }
                    else 
                    {   
                        if(cadastros != NULL)
                        {
                            free(cadastros);
                            cadastros = NULL;
                        }
                        apresentaMensagem("Erro ao alocar memoria para cadastro!");
                        break;
                    }
                }
            }
        }
        fclose(arq);
    }
    return cadastros;
}

//***********************************************************************************************************************
// Objetivo: Obter cadastros com situacao de pagamento indicada
// Parametros: Ponteiro para quantidade de cadastros lidos(a ser mudado pela funcao), indicador(1 - Regular, 2 - Atrasado, 3 - Pago)
// Retorno: Ponteiro para cadastros alocados
Cadastro *obtemAlunosPorSituacaoPagamento(int *qtdCadastros, int indicador)
{
    Cadastro *cadastros = NULL, *cadastrosAux, cadastro;
    FILE *arq;
    
    *qtdCadastros = 0;
    
    if((arq = fopen(ARQ_MATRICULAS,"rb")) != NULL)
    {
        while(!feof(arq))
        {
            if(fread(&cadastro, sizeof(Cadastro), 1, arq))
            {
                if(indicador + '0' == cadastro.situacaoPagamento)
                {
                    cadastrosAux = (Cadastro*) realloc(cadastros, (*qtdCadastros+1) * sizeof(Cadastro));
                    if(cadastrosAux != NULL)
                    {
                        cadastros = cadastrosAux;
                        cadastros[*qtdCadastros] = cadastro;
                        (*qtdCadastros)++;
                    }
                    else 
                    {   
                        if(cadastros != NULL)
                        {
                            free(cadastros);
                            cadastros = NULL;
                        }
                        apresentaMensagem("Erro ao alocar memoria para cadastro!");
                        break;
                    }
                }
            }
        }
        fclose(arq);
    }
    return cadastros;
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
//  Objetivo: Verificar entre 2 codigos de curso, qual ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â© o maior 
//  Parametros: Os codigos do curso
//  Retorno: Numero positivo se o primeiro codigo for mais, negativo se o segundo for maior ou zero se forem iguais
int comparaCadastroCodigo(const void *p1, const void *p2)
{
    Cadastro *cadastro1, *cadastro2;
    cadastro1 = (Cadastro *) p1;
    cadastro2 = (Cadastro *) p2;
    return cadastro1->codigoCurso - cadastro2->codigoCurso;
}
