// Funcoes relacianadas aos dados de cursos

#include <stdio.h>
#include "dados.h"

//***********************************************************************************************************************
//  Objetivo: Ler os dados de um curso
//  Parametros: Referencia a um curso
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
//  Objetivo: Pesquisar um curso dentro de um arquivo por codigo unico
//  Parametros: codigo a ser pesquisado, e indicador se o dado encontrado deve ser escrito (nao zero para sim)
//  Retorno: numero positivo se encontrado(posicao do curso de 1 a n, sendo n o numero de cursos), 0 - codigo nao encontrado
int pesquisaCursoCod(int codCursoBusca, int indPrint)
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
                    if(indPrint)
                    	printf("Nome do Curso: %s\nCodigo: %d\nCarga Horaria: %d\nValor da mensalidade: %.2f\n", curso.nome, curso.codigo, curso.cargaHoraria, curso.mensalidade);
                    flag = 1;
                    break;
                }
            }
        fclose(arq);
    }
    if(indPrint && !flag)
        printf("O curso nao foi encontrado!");
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
//	Objetivo: Editar os dados de um curso
//	Parametros: O codigo do curso a ser alterado
//	Retorno: Nenhum
void alteraDadosCurso(int codigoBusca)
{
	char opcao,confirma;
	FILE *arq;
	int posCurso;
	Curso curso;
	posCurso = pesquisaCursoCod(codigoBusca, 1);

	if(posCurso)
	{
		if((arq = fopen(ARQ_CURSOS,"rb+")) != NULL)
		{
			if(!fseek(arq, sizeof(Curso)*(posCurso-1),0))
			{
				if((fread(&curso, sizeof(Curso), 1, arq)) == 1)
				{
					printf("Qual dos dados deseja alterar?\n1 - Alterar nome do curso\n2 - Alterar valor da mensalidade\n3 - Alterar a carga horaria\n0 - Voltar");
					opcao = leValidaChar("","1230");
					switch(opcao)
					{
						case '1':
							leValidaTexto(curso.nome,"Informe qual o novo nome do curso","Novo nome do curso",3,TAM_NOME_CURSO);
							break;
						case '2':
							curso.mensalidade = leValidaReal("Informe qual o novo valor da mensalidade", "Novo valor da mensalidade", MENSALIDADE_MIN, MENSALIDADE_MAX);
							break;
						case '3':
							curso.cargaHoraria = leValidaInteiro("Informe qual o novo valor da carga horaria do curso", "Novo valor da carga horaria", CARGA_HORARIA_MIN,CARGA_HORARIA_MAX);
							break;
					}
					if(opcao != '0')
					{
                        if(!fseek(arq, sizeof(Curso)*(posCurso-1),0))
    	               	{
                			if((fwrite(&curso, sizeof(Curso), 1, arq)) == 1)
                				puts("Dados alterados com sucesso!");
                			else
                				puts("Houve um erro na alteracao dos dados!");
                		}
                		else
                			puts("Os dados nao foram encontrados!");
    				}
    				else
    				    puts("Os dados nao foram alterados!");
                }
                else
                {
                    clrscr();
                    puts("O curso nao pode ser lido!");
                }
			}
			else
            {
                clrscr();   
                puts("O dado nao pode ser encontrado!");
            }
            fclose(arq);
		}
		else
		{
            clrscr();
            puts("O arquivo dos cursos nao pode ser encontrado!");
        }
	}
}

//***********************************************************************************************************************
//	Objetivo: Excluir um curso
//	Parametros: codigo do curso a ser excluido
//	Retorno: Nenhum
void excluiDadosCurso(int codExclusao)
{
    FILE *arq, *arqTemp;
    char opcao;
    int posCurso, contaCopiados = 0;
    Curso curso;
    posCurso = pesquisaCursoCod(codExclusao, 1);
    if(posCurso)
    {
        opcao = leValidaChar("\n\nTem certeza de que deseja excluir este curso? (S/N) ", "SN");
        if(opcao == 'S')
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
                        {
                            puts("O curso foi removido com sucesso!");
                        }
                    }
                    else
                    {
                        puts("O arquivo nao pode ser removido");
                    }
                }
                else
                {
                    clrscr();
                    puts("O arquivo temporario nao pode ser criado!");
                }
            }
            else
            {
                clrscr();
                puts("O curso nao foi encontrado!");
            }
        }
    }
}
