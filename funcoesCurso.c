// Funcoes relacianadas aos dados de cursos

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
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
    
    memset(&curso, 0, sizeof(Curso));
    curso.codigo = achaProximoCodCurso();
    if(curso.codigo != 0)
    {
        if(alteraDadosCurso(&curso))
    		if(gravaDadoArquivo(ARQ_CURSOS, (void*) &curso, sizeof(Curso)))
                apresentaMensagem("O curso foi salvo com sucesso!");
            else
                apresentaMensagem("O curso nao pode ser salvo!");
    }
    else
        apresentaMensagem("O curso nao pode ser cadastrado!");
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
    
    codigo = selecionaCurso();
    
    if(codigo)
        posCurso = pesquisaCursoCodigo(codigo);
    
    if(posCurso)
    {
        if(obtemDadoArquivo(ARQ_CURSOS, (void *) &curso, sizeof(Curso), posCurso))
        {
            opcao = alteraDadosCurso(&curso);
            
            if(opcao == 1)
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
// Objetivo: Permitir que o usario altere os dados de um cuso
// Parametros: Referencia ao curso a ser alterado
// Retorno: 1 se as alteracoes devem ser salvas e 0 se nao devem
int alteraDadosCurso(Curso *curso)
{
    int opcao = 1, flag, horas;
    int pos [5][2] = {4,5, 4,8, 4,11, 5+15-1,5+12, 5+30-1,5+12};
    float mensalidade;
    char *campoLido, *erro = NULL;
    char erroHoras[50], erroMensalidade[50];

    sprintf(erroHoras, "Horas devem estar entre %d e %d!", CARGA_HORARIA_MIN, CARGA_HORARIA_MAX);
    sprintf(erroMensalidade, "Mensalidade deve estar entre %.2f e %.2f", MENSALIDADE_MIN, MENSALIDADE_MAX);
    
    do
    {
        apresentaCurso(*curso, 5, 5);
        
        gotoxy(5+15, 5+12);
        printf("Salvar");
        
        gotoxy(5+30, 5+12);
        printf("Cancelar");
        
        opcao = simulaMenu(pos, 5, opcao);

        switch(opcao)
        {
            case 1:
                do
                {
                    limpaJanela(5, 5+14, 5, 64, PRETO);
                    gotoxy(5+14, 5);
                    campoLido = leStringEmCampo(50);
                    if(campoLido != NULL && strlen(campoLido) >= 3)
                    {
                        flag = 1;
                        strcpy(curso->nome, campoLido);
                    }
                    else
                    {
                        flag = 0;
                        apresentaErroCampo(5, 5+14, 63, "Nome invalido!");
                    }
                    free(campoLido);
                }
                while(!flag);

                break;
            case 2:
                do
                {
                    limpaJanela(5+3, 5+14, 5+3, 27, PRETO);
                    gotoxy(5+14, 5+3);
                    campoLido = leStringEmCampo(5);
                    horas = atoi(campoLido);
                    if(horas < CARGA_HORARIA_MIN || horas > CARGA_HORARIA_MAX)
                        apresentaErroCampo(5+10, 5+20, 5+20+strlen(erroHoras), erroHoras);
                    free(campoLido);
                }
                while(horas < CARGA_HORARIA_MIN || horas > CARGA_HORARIA_MAX);
                
                curso->cargaHoraria = horas;
                
                break;
            case 3:
                do
                {
                    limpaJanela(5+6, 5+14, 5+6, 27, PRETO);
                    gotoxy(5+14, 5+6);
                    campoLido = leStringEmCampo(9);
                    mensalidade = atof(campoLido);
                    if(mensalidade < MENSALIDADE_MIN || mensalidade > MENSALIDADE_MAX)
                        apresentaErroCampo(5+10, 5+14, 5+14+strlen(erroMensalidade), erroMensalidade);
                    free(campoLido);
                }
                while(mensalidade < MENSALIDADE_MIN || mensalidade > MENSALIDADE_MAX);
                
                curso->mensalidade = mensalidade;

                break;
        }

        limpaJanela(5-1, 5-2, (5)+12, 5+TAM_NOME_CURSO+14, PRETO);

        if(opcao == 4 && (strlen(curso->nome) < 3 || curso->cargaHoraria < CARGA_HORARIA_MIN || curso->mensalidade < MENSALIDADE_MIN))
        {
            apresentaMensagem("Voce deve preencher todos os campos!");
            opcao = 1;
        }

        if(opcao == 0 || opcao == 5)
        {
            if(confirmaEscolha(40, 12, "Deseja cancelar?") == 0)
                opcao = 1;
        }
    }
    while(opcao != 0 && opcao != 4 && opcao != 5);
    
    return opcao == 4 ? 1 : 0;
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
            apresentaCurso(curso, 5, 5);
            confirmacao = confirmaEscolha(55, 15, "Realmente deseja excluir?");
            limpaJanela(1, 1, 12, 80, PRETO);
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
            apresentaCurso(curso, 5, 5);
            getch();
            limpaJanela(1, 1, 12, 80, PRETO);
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
// Parametros: Curso, linha da apresentacao e coluna da apresentacao
// Retorno: Nenhum
void apresentaCurso(Curso curso, int linha, int coluna)
{
    desenhaMoldura(linha-1, coluna+12, linha+1, coluna+9+TAM_NOME_CURSO+5, PRETO, BRANCO);
    gotoxy(coluna, linha);
    printf("Nome:");
    gotoxy(coluna+14, linha);
    printf("%-*.*s\n", TAM_NOME_CURSO-1, TAM_NOME_CURSO-1, strlen(curso.nome) ? curso.nome : "[Ex. Curso ABC]");

    desenhaMoldura(linha+2, coluna+50, linha+4, coluna+9+TAM_NOME_CURSO+5, PRETO, BRANCO);
    gotoxy(coluna+42, linha+3);
    printf("Codigo:");
    gotoxy(coluna+52, linha+3);
    if(curso.codigo)
        printf("%06d\n", curso.codigo);
    else
        printf("%-*.*s\n", 10, 10, "[Ex. 0100]");

    desenhaMoldura(linha+2, coluna+12, linha+4, coluna+9+10+5, PRETO, BRANCO);
    gotoxy(coluna, linha+3);
    printf("Horas:");
    gotoxy(coluna+14, linha+3);
    if(curso.cargaHoraria)
        printf("%-8d\n", curso.cargaHoraria);
    else
        printf("%*.*s\n", 8, 8, "[Ex. 10]");

    desenhaMoldura(linha+5, coluna+12, linha+7, coluna+24, PRETO, BRANCO);
    gotoxy(coluna, linha+6);
    printf("Mensalidade:");
    gotoxy(coluna+14, linha+6);
    if(curso.mensalidade)
        printf("%-8.2f", curso.mensalidade);
    else
        printf("%9.9s", "[Ex. 200]");
    
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
    char ** linhasTabela, codigoTexto[7], titulo[TAM_TEXTO_TABELA+1];
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
                        sprintf(linhasTabela[contador], "%06d - %-45.40s -  %04dh - %-10.2f",
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
        	sprintf(titulo, "%-6s - %-45s - %6s - %-10s","Codigo","Nome do Curso","C.Hor.","Mensalidade");
            for(contador=0;contador<qtdCursos;contador+=LINHAS_TABELA)
            {
            	
                qtdItens = qtdCursos - contador > LINHAS_TABELA ? LINHAS_TABELA : qtdCursos - contador;
                
                if(contador+LINHAS_TABELA < qtdCursos)
                {
                    gotoxy(45, LINHA_TABELA+qtdItens+3);
                    printf("Pressione Esc para ver o restante!");
                }
                
                selecao = menuVertical(titulo, &linhasTabela[contador], qtdItens, BRANCO, AZUL_C, 1, 1, LINHA_TABELA, 1, PRETO, CINZA_C);
                
                limpaJanela(LINHA_TABELA+qtdItens+3, 45, LINHA_TABELA+qtdItens+3, 80, PRETO);
                
                if(selecao != 0)
                {
                    strncpy(codigoTexto, linhasTabela[contador+selecao-1], 6);
                    codigoTexto[6] = '\0';
                    codigoSelecionado = atoi(codigoTexto);
                    break;
                }
                else if(contador+LINHAS_TABELA < qtdCursos)
                {
                	if(!confirmaEscolha(40, 12, "Deseja ver o restante dos cursos?"))
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
        free(cursos);
    }
    else if(!verificaArquivoVazio(ARQ_CURSOS))
        codigo = 0;
    return codigo;
}

//***********************************************************************************************************************
//  Objetivo: Obter todos os cursos que possuem alunos matriculados
//  Parametros: Nenhum
//  Retorno: O codigo do curso
int obtemCursosComAlunosMatriculados()
{
	FILE *arq;
	Curso curso, *cursos = NULL, *cursosAux;
	Cadastro *cadastros;
	int qtdeCadastros, qtdeCopiados = 0, flag, flagAloc = 0, cursoEscolhido;
	
	cadastros = (Cadastro *)obtemDadosArquivo(ARQ_MATRICULAS, sizeof(Cadastro), &qtdeCadastros);
	if((arq = fopen(ARQ_CURSOS,"rb")) != NULL)
	{
		while(!feof(arq))
		{
			if(fread(&curso, sizeof(Curso), 1, arq))
			{
				flag = verificaCursoAlunoCadastrado(curso.codigo);
				if(flag == 1)
				{
					if(cursosAux = (Curso *)realloc(cursos,sizeof(Curso)*(qtdeCopiados+1)))
					{
						cursos = cursosAux;
						cursos[qtdeCopiados] = curso;	
						qtdeCopiados++;
					}
					else
					{
						flagAloc = 1;
						break;
					}
					flag = 0;
				}
			}
		}
		fclose(arq);
	}
	else
		apresentaMensagem("O arquivo dos cursos nao pode ser aberto!");
	if(flagAloc == 1)
	{
		apresentaMensagem("Os dados nao puderam ser alocados!");
		if(qtdeCopiados > 0)
			free(cursos);
	}
	else
	{
		cursoEscolhido = apresentaDadosCursos(cursos, qtdeCopiados);
		free(cursos);
	}
	return cursoEscolhido;
}

