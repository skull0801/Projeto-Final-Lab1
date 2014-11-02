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
    gravaDadosCurso(&curso);
}

//***********************************************************************************************************************
//  Objetivo: Ler os dados de um curso
//  Parametros: Referencia a um curso
//  Retorno: 0 se os dados foram lidos com sucesso ou 1 se houve algum erro
void leDadosCurso(Curso *curso)
{
    leValidaTexto(curso->nome, "Informe o nome do curso", "Curso", 3, TAM_NOME_CURSO);
    curso->cargaHoraria = leValidaInteiro("Informe a carga horaria", "Carga Horaria", CARGA_HORARIA_MIN, CARGA_HORARIA_MAX);
    curso->mensalidade = leValidaReal("Informe o valor da mensalidade","Mensalidade", MENSALIDADE_MIN, MENSALIDADE_MAX);
    curso->codigo = achaProximoCodCurso();
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
//  Parametros: nenhum
//  Retorno: Nenhum
void listaDadosCursos()
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
// Objetivo: Pesquisar por um ou mais cursos
// Parametros: nenhum
// Retorno: nenhum
void pesquisaCurso(void)
{
    int codigo, posCurso, opcao;
    char nomeBusca[TAM_NOME_CURSO];
    char *opcoesPesquisa[] = {"Pesquisa por Codigo",
                              "Pesquisa por Nome",
                              "Voltar"};
    FILE *arq;
    Curso curso;
    
    opcao = menuVertical(opcoesPesquisa, 3, BRANCO, AZUL_C, 1, 20, 5, 1, PRETO, CINZA_C);
    clrscr();
    
    switch(opcao)
    {
        case 1:
            codigo = leValidaInteiro("Informe o codigo do curso a pesquisar", "Codigo", CODIGO_MIN, CODIGO_MAX);
            posCurso = pesquisaCursoCod(codigo);
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
                }
                else
                    printf("O arquivo de cursos nao pode ser aberto!");
            }
            else
                printf("O curso nao foi encontrado!");
            break;
        case 2:
			leValidaTexto(nomeBusca, "Informe o nome do curso", "Nome", 1, TAM_NOME_CURSO);
			pesquisaCursoNome(nomeBusca);
			break;
    }
}

//***********************************************************************************************************************
//  Objetivo: Pesquisar um curso dentro de um arquivo por codigo unico
//  Parametros: codigo a ser pesquisado
//  Retorno: numero positivo se encontrado(posicao do curso de 1 a n, sendo n o numero de cursos), 0 - codigo nao encontrado
int pesquisaCursoCod(int codCursoBusca)
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
void pesquisaCursoNome(char *nomeBusca)
{
    FILE *arq;
    Curso curso, *cursos = NULL, *cursosAux;
    int qtdLidos = 0, contador;
    char copiaNome[TAM_NOME_CURSO];
    
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
        ordenaCursosPeloNome(cursos, qtdLidos);
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

//  Objetivo: Ordenar cursos pelo nome
//  Parametros: Referencia a um vetor de cursos e a quantidade de cursos
//  Retorno: Nenhum
void ordenaCursosPeloNome(Curso *cursos, int qtdeCursos)
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
// Objetivo: Recuperar um curso de um arquivo, deixar o usuario alterar seus dados, e confirmar se as mudanças devem ser salvas
// Parâmetros: nenhum
// Retorno: nenhum
void alteraCurso(void)
{
    FILE *arq;
    int posCurso, codigo;
    int opcao, confirmacao;
    Curso curso;
    char *opcoesAlteracao[] = {"Alterar Nome",
                               "Alterar Mensalidade",
                               "Alterar Carga Horaria",
                               "Salvar Mudancas",
                               "Cancelar Mudancas"};
    
    listaDadosCursos();
    
    codigo = leValidaInteiro("\nInforme o codigo do curso que deseja editar","Codigo a ser editado",CODIGO_MIN,CODIGO_MAX);
    
    posCurso = pesquisaCursoCod(codigo);
    
    if(posCurso)
    {
        if((arq = fopen(ARQ_CURSOS, "rb")) != NULL)
        {
            if(!fseek(arq, sizeof(Curso)*(posCurso-1), 0))
            {
                if(fread(&curso, sizeof(Curso), 1, arq))
                {
                    do
                    {
                        apresentaCurso(curso);
                        opcao = menuVertical(opcoesAlteracao, 5, BRANCO, AZUL_C, 1, 55, 1, 1, PRETO, CINZA_E);
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
                        confirmacao = confirmaEscolha(55, 1);
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
                    printf("Os dados do curso nao puderam ser lidos!");
            }
            else
                printf("Os dados do curso nao puderam ser lidos!");
                
            fclose(arq);
        }
        else
            printf("O curso nao pode ser recuperado!");
    }
    else
        printf("O curso nao foi encontrado!"); 
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
    FILE *arq = NULL;
    int posCurso, codigo;
    char confirmacao;
    
    listaDadosCursos();
    
    codigo = leValidaInteiro("\nInforme o codigo do curso a excluir", "Codigo", CODIGO_MIN, CODIGO_MAX);
    
    posCurso = pesquisaCursoCod(codigo);
    
    if(posCurso)
    {
        if((arq = fopen(ARQ_CURSOS, "rb")) != NULL)
        {
            if(!fseek(arq, sizeof(Curso)*(posCurso-1), 0))
            {
                if(fread(&curso, sizeof(Curso), 1, arq))
                {
                    apresentaCurso(curso);
                    confirmacao = confirmaEscolha(55, 1);
                    clrscr();
                    if(confirmacao == 1)
                    {
                        fclose(arq);
                        arq = NULL;
                        excluiDadosCurso(posCurso);
                    }
                    else
                        printf("Os dados nao foram excluidos!");
                }
                else
                    printf("O curso nao pode ser lido!");
            }
            else
                printf("O curso nao pode ser encontrado!");
        }
        else
            printf("O arquivo de curso nao pode ser aberto!");
        
        if(arq != NULL)
            fclose(arq);
    }
    else
        printf("Este curso nao esta cadastrado!");
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
                puts("O arquivo temporario nao pode ser criado!");
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
    printf("Nome do Curso: %s\n", curso.nome);
    printf("Codigo: %d\n", curso.codigo);
    printf("Carga Horaria: %d\n", curso.cargaHoraria);
    printf("Valor da mensalidade: %.2f\n", curso.mensalidade);
}
