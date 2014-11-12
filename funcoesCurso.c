// Funcoes relacianadas aos dados de cursos

#include <stdio.h>
#include <conio.h>
#include "dados.h"
#include "cores.h"
#include "funcoesBasicas.h"
#include "funcoesCurso.h"

//***********************************************************************************************************************
// Objetivo: Cadastrar um curso
// Parametros: nenhum
// Retorno: nenhum
void cadastraCurso(void)
{
    Curso curso;
    leDadosCurso(&curso);
    if(curso.codigo != 0)
    {
		if(gravaDadoArquivo(ARQ_CURSOS, (void*) &curso, sizeof(Curso)))
            apresentaMensagem("O curso foi salvo com sucesso!");
        else
            apresentaMensagem("O curso nao pode ser salvo!");
    }
    else
        apresentaMensagem("O curso nao pode ser cadastrado!");
}

//***********************************************************************************************************************
//  Objetivo: Ler os dados de um curso
//  Parametros: Referencia a um curso
//  Retorno: 0 se os dados foram lidos com sucesso ou 1 se houve algum erro
void leDadosCurso(Curso *curso)
{
    curso->codigo = achaProximoCodCurso();
    if(curso->codigo != 0)
    {
	    leValidaTexto(curso->nome, "Informe o nome do curso", "Curso", 3, TAM_NOME_CURSO);
	    curso->cargaHoraria = leValidaInteiro("Informe a carga horaria", "Carga Horaria", CARGA_HORARIA_MIN, CARGA_HORARIA_MAX);
	    curso->mensalidade = leValidaReal("Informe o valor da mensalidade","Mensalidade", MENSALIDADE_MIN, MENSALIDADE_MAX);
	}
	else
		apresentaMensagem("Nao foi possivel realizar o cadastro!");
}

//***********************************************************************************************************************
// Objetivo: Recuperar um curso de um arquivo, deixar o usuario alterar seus dados, e confirmar se as mudancas devem ser salvas
// Parametros: nenhum
// Retorno: nenhum
void alteraCurso(void)
{
    int posCurso = 0, codigo;
    int opcao = 1, confirmacao;
    Curso curso;
    char *opcoesAlteracao[] = {"Alterar Nome",
                               "Alterar Mensalidade",
                               "Alterar Carga Horaria",
                               "Salvar Mudancas",
                               "Cancelar Mudancas"};
    
    codigo = apresentaTodosCursos();
    
    if(codigo)
        posCurso = pesquisaCursoCodigo(codigo);
    
    if(posCurso)
    {
        if(obtemDadoArquivo(ARQ_CURSOS, (void *) &curso, sizeof(Curso), posCurso))
        {
            do
            {
                apresentaCurso(curso);
                opcao = menuVertical("O que deseja fazer?", opcoesAlteracao, 5, BRANCO, AZUL_C, 1, 55, 10, opcao, PRETO, CINZA_E);
                switch(opcao)
                {
                    case 1:
                        leValidaTexto(curso.nome, "Informe qual o novo nome do curso", "Novo nome do curso", 3, TAM_NOME_CURSO);
                        break;
                    case 2:
                        curso.mensalidade = leValidaReal("Informe qual o novo valor da mensalidade", "Novo valor da mensalidade", MENSALIDADE_MIN, MENSALIDADE_MAX);
                        break;
                    case 3:
                        curso.cargaHoraria = leValidaInteiro("Informe qual o novo valor da carga horaria do curso", "Novo valor da carga horaria", CARGA_HORARIA_MIN, CARGA_HORARIA_MAX);
                        break;
                }
            }
            while(opcao != 0 && opcao != 4 && opcao != 5);
            
            if(opcao == 4)
            {
                confirmacao = confirmaEscolha(40, 12, "Deseja salvar as mudancas?");
                if(confirmacao == 1)
                {
                    if(alteraDadoArquivo(ARQ_CURSOS, (void*) &curso, sizeof(Curso), posCurso))
                        apresentaMensagem("O curso foi alterado com sucesso!");
                    else
                        apresentaMensagem("O curso nao foi alterado!");
                }
                else
                    apresentaMensagem("O curso nao foi alterado!");
            }
            else
                apresentaMensagem("O curso nao foi alterado!");
                    
            limpaJanela(1, 1, 9, 80, PRETO);
        }
        else
            apresentaMensagem("O curso nao pode ser recuperado do arquivo!");
    }
}

//***********************************************************************************************************************
// Objetivo: Ler o codigo de um curso, buscar pelo mesmo, e confirmar se o usuario deseja excluir o curso, caso queira, excluir
// Parametros: Nenhum
// Retorno: Nenhum
void excluiCurso(void)
{
    Curso curso;
    int posCurso = 0, codigo;
    char confirmacao;
    
    codigo = apresentaTodosCursos();
    
    if(codigo)
        posCurso = pesquisaCursoCodigo(codigo);
    
    if(posCurso)
    {
        if(obtemDadoArquivo(ARQ_CURSOS, (void *) &curso, sizeof(Curso), posCurso))
        {
            apresentaCurso(curso);
            confirmacao = confirmaEscolha(40, 12, "Realmente deseja excluir?");
            limpaJanela(1, 1, 9, 80, PRETO);
            if(confirmacao == 1)
            {
                if(!verificaCursoAlunoCadastrado(codigo))
                    if(excluiDadoArquivo(ARQ_CURSOS, sizeof(Curso), posCurso))
                        apresentaMensagem("O curso foi excluido com sucesso!");
                    else
                        apresentaMensagem("O curso nao foi excluido!");
                else
                    apresentaMensagem("O curso tem ao menos um aluno cadastrado no mesmo!");
            }
            else
                apresentaMensagem("Os dados nao foram excluidos!");
        }
        else
            apresentaMensagem("O arquivo de curso nao pode ser aberto!");
    }
}

//*********************************************************************************************************************** 
// Objetivo: Permitir ao usuario selecionar um curso dentre varios, dependendo de sua escolha 
// Parametros: nenhum 
// Retorno: Codigo do curso selecionado (0 se nao selecionar ninguem) 
int selecionaCurso(void) 
{ 
    int opcao, codigo = 0; 
    char *opcoesSelecao[] = {"Dentre Todos os Cursos", 
                             "Pesquisar por Nome", 
                             "Voltar"}; 

    opcao = menuVertical("Como deseja selecionar os cursos?", opcoesSelecao, 3, BRANCO, AZUL_C, 1, 20, 5, 1, PRETO, CINZA_C); 
         
    switch(opcao) 
    { 
        case 1: 
            codigo = apresentaTodosCursos(); 
            break; 
        case 2: 
            codigo = pesquisaApresentaCursoNome(); 
            break; 
    } 
     
    return codigo; 
}

//***********************************************************************************************************************
// Objetivo: Pesquisar por um ou mais cursos
// Parametros: nenhum
// Retorno: nenhum
void pesquisaCurso(void)
{
    int opcao = 1;
    char *opcoesPesquisa[] = {"Pesquisa por Codigo",
                              "Pesquisa por Nome",
                              "Voltar"};
    do
    {
        opcao = menuVertical("Pesquisa de um Curso", opcoesPesquisa, 3, BRANCO, AZUL_C, 1, 20, 5, opcao, PRETO, CINZA_C);
        
        switch(opcao)
        {
            case 1:
                pesquisaApresentaCursoCodigo();
                break;
            case 2:
                pesquisaApresentaCursoNome();
                break;
        }
    }
    while(opcao != 0 && opcao != 3);
}

//***********************************************************************************************************************
//  Objetivo: Pesquisar um curso dentro de um arquivo por nome
//  Parametros: nome a ser pesquisado
//  Retorno: nenhum
int pesquisaApresentaCursoNome(void)
{
    FILE *arq;
    Curso curso, *cursos = NULL, *cursosAux;
    int qtdLidos = 0, flag = 0, codigo = 0;
    char copiaNome[TAM_NOME_CURSO], nomeBusca[TAM_NOME_CURSO];
    
    leValidaTexto(nomeBusca, "Informe o nome do curso", "Nome", 1, TAM_NOME_CURSO);
    
    strToLower(nomeBusca);
    
    if((arq = fopen(ARQ_CURSOS, "rb")) != NULL)
    {
        while(!feof(arq))
        {
            if(fread(&curso, sizeof(Curso), 1, arq))
            {
                strcpy(copiaNome, curso.nome);
                strToLower(copiaNome);
                if(strstr(copiaNome, nomeBusca))
                {
                    cursosAux = (Curso *) realloc(cursos, sizeof(Curso)*(qtdLidos+1));
                    if(cursosAux != NULL)
                    {
                        cursos = cursosAux;
                        cursos[qtdLidos] = curso;
                        qtdLidos++;
                    }
                    else
                    {
                        apresentaMensagem("Erro ao alocar memoria para cursos!");
                        flag = 1;
                        break;
                    }
                }
            }
        }
        fclose(arq);
    }
    
    if(!flag)
    {
        if(qtdLidos)
        {
            codigo = apresentaDadosCursos(cursos, qtdLidos);
            free(cursos);
        }
        else
            apresentaMensagem("Nao houve nenhuma correspondencia!");
    }
    else
        if(qtdLidos)
            free(cursos);
    return codigo; 
}

//***********************************************************************************************************************
// Objetivo: Pesquisar e apresentar um curso por codigo
// Parametros: nenhum
// Retorno: nenhum
void pesquisaApresentaCursoCodigo(void)
{
    FILE *arq;
    int codigo, posCurso;
    Curso curso;
    
    codigo = leValidaInteiro("Informe o codigo do curso a pesquisar", "Codigo", CODIGO_MIN, CODIGO_MAX);
    
    posCurso = pesquisaCursoCodigo(codigo);
    
    if(posCurso)
    {
        if(obtemDadoArquivo(ARQ_CURSOS, &curso, sizeof(Curso), posCurso))
        {
            apresentaCurso(curso);
            getch();
            limpaJanela(1, 1, 10, 80, PRETO);
        }
        else
            apresentaMensagem("O curso nao pode ser recuperado!");
    }
    else
        apresentaMensagem("O curso nao foi encontrado!");
}

//***********************************************************************************************************************
//  Objetivo: Pesquisar um curso dentro de um arquivo por codigo unico
//  Parametros: codigo a ser pesquisado
//  Retorno: numero positivo se encontrado(posicao do curso de 1 a n, sendo n o numero de cursos), 0 - codigo nao encontrado
int pesquisaCursoCodigo(int codCursoBusca)
{
    FILE *arq;
    Curso curso;
    int pos = 0, flag = 0;
    if((arq = fopen(ARQ_CURSOS, "rb")) != NULL)
    {
        while(!feof(arq))
        {
            if(fread(&curso, sizeof(Curso), 1, arq))
            {
                pos++;
                if(codCursoBusca == curso.codigo)
                {
                    flag = 1;
                    break;
                }
            }
        }
        fclose(arq);
    }
    if(!flag)
        pos = 0;
    return pos;
}

//***********************************************************************************************************************
// Objetivo: Apresentar um curso
// Parametros: Curso
// Retorno: Nenhum
void apresentaCurso(Curso curso)
{
    gotoxy(1,1);
    printf("Nome do Curso: %s\n", curso.nome);
    printf("Codigo: %d\n", curso.codigo);
    printf("Carga Horaria: %d\n", curso.cargaHoraria);
    printf("Valor da mensalidade: %.2f\n", curso.mensalidade);
}

//***********************************************************************************************************************
// Objetivo: Apresentar todos os cursos
// Parametros: Nenhum
// Retorno: Codigo do curso selecionado
int apresentaTodosCursos(void)
{
    Curso *cursos;
    int qtdCursos, codigoSelecionado = 0;
    if((cursos = (Curso *) obtemDadosArquivo(ARQ_CURSOS, sizeof(Curso), &qtdCursos))!= NULL)
    {
        codigoSelecionado = apresentaDadosCursos(cursos, qtdCursos);
        free(cursos);
    }
    return codigoSelecionado;
}

//***********************************************************************************************************************
// Objetivo: Apresentar os cursos fornecidos
// Parametros: Ponteiro para cursos (ja alocados), quantidade de cursos
// Retorno: Matricula do curso selecionado (0 se nenhum foi selecionado)   (NAO DESALOCA MEMORIA)
int apresentaDadosCursos(Curso *cursos, int qtdCursos)
{
    int selecao, qtdItens, contador, qtdLinhasAlocada = 0, flag = 0;
    int codigoSelecionado = 0;
    char ** linhasTabela, codigoTexto[7];
    if(qtdCursos > 0)
    {
        qsort(cursos, qtdCursos, sizeof(Curso), comparaCursosNome);
        
        linhasTabela = (char**) malloc(sizeof(char*) * qtdCursos);
        if(linhasTabela != NULL)
        {
            for(contador=0;contador<qtdCursos;contador++)
            {
                linhasTabela[contador] = (char*) malloc(sizeof(char)*(TAM_TEXTO_TABELA));
                if(linhasTabela[contador] != NULL)
                    {
                        sprintf(linhasTabela[contador], "%06d - %-25.20s -  %04dh - %-10.2f",
                        cursos[contador].codigo, cursos[contador].nome, cursos[contador].cargaHoraria, cursos[contador].mensalidade);
                    qtdLinhasAlocada++;
                }
                else
                {
                    flag = 1;
                    apresentaMensagem("A memoria para uma das linhas nao pode ser alocada");
                    break;
                }
            }
        }
        else
        {
            flag = 1;
            apresentaMensagem("A memoria para tabela nao pode ser alocada!");
        }
        
        if(!flag)
        {
            for(contador=0;contador<qtdCursos;contador+=10)
            {
                qtdItens = qtdCursos - contador > 10 ? 10 : qtdCursos - contador;
                
                selecao = menuVertical("CURSOS", &linhasTabela[contador], qtdItens, BRANCO, AZUL_C, 1, 10, 5, 1, PRETO, CINZA_C);
                
                if(selecao != 0)
                {
                    strncpy(codigoTexto, linhasTabela[contador+selecao-1], 6);
                    codigoTexto[6] = '\0';
                    codigoSelecionado = atoi(codigoTexto);
                    break;
                }
                else if(contador+10<qtdCursos)
                {
                    if(!confirmaEscolha(20, 5, "Deseja continuar?"))
                        break;
                }
            }
        }
        
        if(linhasTabela != NULL)
        {
            for(contador=0;contador<qtdLinhasAlocada;contador++)
                free(linhasTabela[contador]);
            free(linhasTabela);
        }
    }
    else
        apresentaMensagem("Nao existem cursos cadastrados!");
        
    return codigoSelecionado;
}

//***********************************************************************************************************************
// Objetivo: Compara dois cursos (por codigo)
// Parametros: Ponteiro para os dois alunos
// Retorno: resultado da comparacao dos dois nomes(inteiro)
int comparaCursosCodigo(const void *p1, const void *p2)
{
    Curso *curso1, *curso2;
    curso1 = (Curso *) p1;
    curso2 = (Curso *) p2;
    return curso1->codigo - curso2->codigo;
}

//***********************************************************************************************************************
// Objetivo: Compara dois cursos (por codigo)
// Parametros: Ponteiro para os dois alunos
// Retorno: resultado da comparacao dos dois nomes(inteiro)
int comparaCursosNome(const void *p1, const void *p2)
{
    Curso *curso1, *curso2;
    curso1 = (Curso *) p1;
    curso2 = (Curso *) p2;
    return stricmp(curso1->nome, curso2->nome);
}

//***********************************************************************************************************************
//  Objetivo: Encontrar o proximo codigo valido de um curso
//  Parametros: Nenhum
//  Retorno: proximo codigo valido
int achaProximoCodCurso(void)
{
    int codigo = CODIGO_MIN, qtdCursos = 0;
    Curso *cursos;
    if((cursos = (Curso *) obtemDadosArquivo(ARQ_CURSOS, sizeof(Curso), &qtdCursos)) != NULL)
    {
        if(qtdCursos>0)
        {
            qsort(cursos, qtdCursos, sizeof(Curso), comparaCursosCodigo);
            
            for(;codigo-CODIGO_MIN<qtdCursos;codigo++)
            {
                if(codigo != cursos[codigo-CODIGO_MIN].codigo)
                {
                    break;
                }
            }
        }
    }
    else if(!verificaArquivoVazio(ARQ_CURSOS))
        codigo = 0;
    return codigo;
}
