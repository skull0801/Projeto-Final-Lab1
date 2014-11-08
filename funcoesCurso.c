// Funcoes relacianadas aos dados de cursos

#include <stdio.h>
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
		gravaDadosCurso(&curso);
	clrscr();
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
	{
		printf("Nao foi possivel realizar o cadastro!");
		getch();
	}
}

//***********************************************************************************************************************
//  Objetivo: Gravar os dados de um curso num arquivo
//  Parametros: Referencia a um curso
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
//  Objetivo: Encontrar o proximo codigo valido de um curso
//  Parametros: Nenhum
//  Retorno: proximo codigo valido
int achaProximoCodCurso()
{
    int codigo = CODIGO_MIN, qtdCursos = 0;
    Curso *cursos;
    if((cursos = obtemDadosCursosArquivo(&qtdCursos)) != NULL)
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
    else
    	codigo = 0;
    return codigo;
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
// Objetivo: Obter todos os cursos do arquivo
// Parametros: Referencia a quantidade de cursos (valor sera dado pela funcao)
// Retorno: Ponteiro para memoria alocada na qual os cursos estao
Curso * obtemDadosCursosArquivo(int * qtdCursos)
{
    FILE *arq;
    Curso *cursos = NULL;
    
    if((arq = fopen(ARQ_CURSOS, "rb")) != NULL)
    {
        if(!fseek(arq, 0, SEEK_END))
        {
            *qtdCursos = (ftell(arq)/sizeof(Curso));
            
            cursos = malloc(sizeof(Curso)*(*qtdCursos));
            
            if(cursos != NULL)
            {
                rewind(arq);
                if(fread(cursos, sizeof(Curso), *qtdCursos, arq) != *qtdCursos)
                {
                    printf("Erro ao recuperar os dados de cursos!");
                    free(cursos);
                    cursos = NULL;
                }
            }
            else
                printf("Erro ao alocar memoria para cursos!");
        }
        else
            printf("Erro ao obter quantidade de cursos.");
            
        fclose(arq);
    }
    else
        printf("Erro ao abrir o arquivo de cursos.");
        
    return cursos;
}

//***********************************************************************************************************************
// Objetivo: Apresentar todos os cursos
// Parametros: Nenhum
// Retorno: Codigo do curso selecionado
int apresentaTodosCursos(void)
{
    Curso *cursos;
    int qtdCursos, codigoSelecionado = 0;
    if((cursos = obtemDadosCursosArquivo(&qtdCursos))!= NULL)
    {
        codigoSelecionado = apresentaDadosCursos(cursos, qtdCursos);
        free(cursos);
    }
    return codigoSelecionado;
}

//***********************************************************************************************************************
// Objetivo: Apresentar os cursos fornecidos
// Parametros: Ponteiro para cursos (ja alocados), quantidade de cursos
// Retorno: Matricula do cur selecionado (0 se nenhum foi selecionado)   (NAO DESALOCA MEMORIA)
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
                    sprintf(linhasTabela[contador], "%06d - %-25.20s - %5dh", cursos[contador].codigo, cursos[contador].nome, cursos[contador].cargaHoraria);
                    qtdLinhasAlocada++;
                }
                else
                {
                    flag = 1;
                    printf("A memoria para uma das linhas nao pode ser alocada");
                    break;
                }
            }
        }
        else
        {
            flag = 1;
            printf("A memoria para tabela nao pode ser alocada!");
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
    {
        printf("Nao existem cursos cadastrados!");
        getch();
    }
    return codigoSelecionado;
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
        if((arq = fopen(ARQ_CURSOS, "rb")) != NULL)
        {
            if(!fseek(arq, sizeof(Curso)*(posCurso-1), 0))
            {
                if(fread(&curso, sizeof(Curso), 1, arq))
                {
                    apresentaCurso(curso);
                }
                else
                    printf("O curso nao pode ser lido!");
            }
            else
                printf("O curso nao pode ser encontrado!");
            fclose(arq);
        }
        else
            printf("O arquivo de cursos nao pode ser aberto!");
    }
    else
        printf("O curso nao foi encontrado!");
}

//***********************************************************************************************************************
// Objetivo: Pesquisar por um ou mais cursos
// Parametros: nenhum
// Retorno: nenhum
void pesquisaCurso(void)
{
    int opcao;
    char *opcoesPesquisa[] = {"Pesquisa por Codigo",
                              "Pesquisa por Nome",
                              "Voltar"};
    
    opcao = menuVertical("O QUE DESEJA FAZER?", opcoesPesquisa, 3, BRANCO, AZUL_C, 1, 20, 5, 1, PRETO, CINZA_C);
    clrscr();
    
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
            if(fread(&curso, sizeof(Curso), 1, arq))
            {
            	pos++;
                if(codCursoBusca == curso.codigo)
                {
                    flag = 1;
                    break;
                }
            }
        fclose(arq);
    }
    if(!flag)
        pos = 0;
    return pos;
}

//***********************************************************************************************************************
//  Objetivo: Pesquisar um curso dentro de um arquivo por nome
//  Parametros: nome a ser pesquisado
//  Retorno: nenhum
void pesquisaApresentaCursoNome()
{
    FILE *arq;
    Curso curso, *cursos = NULL, *cursosAux;
    int qtdLidos = 0, contador;
    char copiaNome[TAM_NOME_CURSO], nomeBusca[TAM_NOME_CURSO];
    
	leValidaTexto(nomeBusca, "Informe o nome do curso", "Nome", 1, TAM_NOME_CURSO);
	
    strToLower(nomeBusca);
    printf("%-50s%-7s%-7s%-10s\n","Nome","Codigo","Horas","Mensalidade");
    
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
                        break;
                }
            }
            else
                break;
        }
        fclose(arq);
    }
    
    if(qtdLidos)
    {
        ordenaCursosPorNome(cursos, qtdLidos);
        for(contador = 0; contador < qtdLidos; contador++)
                printf("%-50s%-7d%-7d%-10.2f\n", cursos[contador].nome, cursos[contador].codigo, 
                cursos[contador].cargaHoraria,cursos[contador].mensalidade);
        free(cursos);
    }
    else
    {
        clrscr();
        puts("Nao houve nenhuma correspondencia!");   
    }
}

//***********************************************************************************************************************
// Objetivo: Encontrar um curso no arquivo
// Parametros: Ponteiro para curso, e posicao do curso no arquivo
// Retorno: 1 para sucesso, e 0 caso nao tenha encontrado
int obtemCursoArquivo(Curso *curso, int posCurso)
{
    FILE *arq;
    int flag = 0;
    if((arq = fopen(ARQ_CURSOS, "rb")) != NULL)
    {
        if(!fseek(arq, sizeof(Curso)*(posCurso-1), 0))
        {
            if(fread(curso, sizeof(Curso), 1, arq))
            {
                flag = 1;
            }
        }
        fclose(arq);
    }
    return flag;
}

//***********************************************************************************************************************
//  Objetivo: Ordenar cursos pelo nome
//  Parametros: Referencia a um vetor de cursos e a quantidade de cursos
//  Retorno: Nenhum
void ordenaCursosPorNome(Curso *cursos, int qtdeCursos)
{
    Curso cursoAux;
    int contador, auxiliar;
    for(auxiliar = 0; auxiliar < qtdeCursos-1; auxiliar++)
    {
        for(contador = auxiliar+1; contador < qtdeCursos; contador++)
        {
            if(stricmp(cursos[auxiliar].nome, cursos[contador].nome) > 0)
            {
                cursoAux = cursos[auxiliar];
                cursos[auxiliar] = cursos[contador];
                cursos[contador] = cursoAux;
            }
        }
    }
}

//***********************************************************************************************************************
// Objetivo: Recuperar um curso de um arquivo, deixar o usuario alterar seus dados, e confirmar se as mudancas devem ser salvas
// Parametros: nenhum
// Retorno: nenhum
void alteraCurso(void)
{
    int posCurso, codigo;
    int opcao, confirmacao;
    Curso curso;
    char *opcoesAlteracao[] = {"Alterar Nome",
                               "Alterar Mensalidade",
                               "Alterar Carga Horaria",
                               "Salvar Mudancas",
                               "Cancelar Mudancas"};
    
    codigo = apresentaTodosCursos();
    
    posCurso = pesquisaCursoCodigo(codigo);
    
    if(posCurso)
    {
        if(obtemCursoArquivo(&curso, posCurso))
        {
            do
            {
                apresentaCurso(curso);
                opcao = menuVertical("O QUE DESEJA FAZER?", opcoesAlteracao, 5, BRANCO, AZUL_C, 1, 55, 1, 1, PRETO, CINZA_E);
                gotoxy(1, 6);
				switch(opcao)
				{
					case 1:
						leValidaTexto(curso.nome, "Informe qual o novo nome do curso", "Novo nome do curso", 3, TAM_NOME_CURSO);
						break;
					case 2:
						curso.mensalidade = leValidaReal("Informe qual o novo valor da mensalidade", "Novo valor da mensalidade", MENSALIDADE_MIN, MENSALIDADE_MAX);
						break;
					case 3:
						curso.cargaHoraria = leValidaInteiro("Informe qual o novo valor da carga horaria do curso", "Novo valor da carga horaria", CARGA_HORARIA_MIN,CARGA_HORARIA_MAX);
						break;
				}
            }
            while(opcao != 0 && opcao != 4 && opcao != 5);
            
            if(opcao == 4)
            {
                confirmacao = confirmaEscolha(55, 1, "Tem certeza?");
                clrscr();
                if(confirmacao == 1)
                {
                    alteraDadosCurso(curso, posCurso);
                }
                else
                    printf("Os dados nao foram alterados!");
            }
            else
                printf("Os dados nao foram alterados!");
        }
        else
            printf("O curso nao pode ser recuperado!");
    }
}

//***********************************************************************************************************************
//	Objetivo: Editar os dados de um curso
//	Parametros: O codigo do curso a ser alterado
//	Retorno: Nenhum
void alteraDadosCurso(Curso curso, int posCurso)
{
	FILE *arq;

    if(posCurso)
    {
        if((arq = fopen(ARQ_CURSOS, "rb+")) != NULL)
        {
            if(!fseek(arq, sizeof(Curso)*(posCurso-1), 0))
            {
                if(fwrite(&curso, sizeof(Curso), 1, arq))
                    printf("Os dados foram alterados com sucesso!");
                else
                    printf("Os dados nao puderam ser alterados!");
            }
            else
                printf("O curso nao pode ser recuperado!");
                
            fclose(arq);
        }
        else
            printf("O arquivo nao pode ser aberto para ser alterado!");
    }
}

//***********************************************************************************************************************
// Objetivo: Ler o codigo de um curso, buscar pelo mesmo, e confirmar se o usuario deseja excluir o curso, caso queira, excluir
// Parametros: Nenhum
// Retorno: Nenhum
void excluiCurso(void)
{
    Curso curso;
    int posCurso, codigo;
    char confirmacao;
    
    codigo = apresentaTodosCursos();
    
    posCurso = pesquisaCursoCodigo(codigo);
    
    if(posCurso)
    {
        if(obtemCursoArquivo(&curso, posCurso))
        {
            apresentaCurso(curso);
            confirmacao = confirmaEscolha(55, 1, "Voce tem certeza?");
            clrscr();
            if(confirmacao == 1)
            {
                if(!verificaCursoAlunoCadastrado(codigo))
                    excluiDadosCurso(posCurso);
                else
                    printf("O curso tem ao menos um aluno cadastrado no mesmo!");
            }
            else
                printf("Os dados nao foram excluidos!");
        }
        else
            printf("O arquivo de curso nao pode ser aberto!");
    }
}

//***********************************************************************************************************************
//	Objetivo: Excluir um curso
//	Parametros: posicao do curso a ser excluido
//	Retorno: Nenhum
void excluiDadosCurso(int posCurso)
{
    FILE *arq, *arqTemp;
    char opcao;
    int contaCopiados = 0;
    Curso curso;
    
    if(posCurso)
    {
		if((arq = fopen(ARQ_CURSOS,"rb")) != NULL)
		{
            if((arqTemp = fopen(ARQ_CURSOS_TEMP,"wb")) != NULL)
            {
                while(!feof(arq))
                {
                    if((fread(&curso, sizeof(Curso), 1, arq)) == 1)
                    {
                        contaCopiados++;
                        if(posCurso != contaCopiados)
                            if(fwrite(&curso, sizeof(Curso), 1,arqTemp) != 1)
                                puts("Os dados nao puderam ser excluidos!");
                    }
                }
                
                fclose(arqTemp);
                fclose(arq);
                
                if(remove(ARQ_CURSOS) == 0)
                {
                    if(rename(ARQ_CURSOS_TEMP,ARQ_CURSOS) == 0)
                        puts("O curso foi removido com sucesso!");
                    else
                        puts("O arquivo antigo nao pode ser renomeado. Todos os dados foram perdidos!");
                }
                else
                    puts("O arquivo nao pode ser removido");
            }
            else
            {
                fclose(arq);
                puts("O arquivo temporario nao pode ser criado!");
            }
        }
        else
            puts("O curso nao foi encontrado!");
    }
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
