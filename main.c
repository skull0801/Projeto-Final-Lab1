// Alunos : Marcus Vinicius Campos Fonseca e Lucas Lima da Silva
// Matriculas: UC14101868, UC14102446
// Implementacao: de algumas das funcionalidades do projeto final

#include <stdio.h>
#include <conio.c>
#include "dados.h"
#include "funcoesAluno.h"
#include "funcoesCurso.h"
#include "funcoesBasicas.h"
#include "funcoesCadastro.h"

int main(void)
{
// Declaracoes
    Curso curso;
    Aluno aluno;
    int posCursoEncontrado;
    char opcao, subOpcao, nomeBusca[100];
    int cod;
// Instrucoes
    do
    {
        apresentaMenu(MENU_PRINCIPAL);
        opcao = leValidaChar("", "123450");
	    switch(opcao)
	    {
            case '1':
                apresentaMenu(MENU_CADASTRO);
                subOpcao = leValidaChar("", "1230");
            	switch(subOpcao)
            	{
            		case '1':
                        leDadosAluno(&aluno);
                        gravaDadosAluno(&aluno);
                        getch();
            			break;
            		case '2':
		                leDadosCurso(&curso);
		                gravaDadosCurso(&curso);
		                getch();
		                break;
		            case '3':
                        cadastraAlunoEmCurso();
                        getch();
            			break;
                }	
	            break;
            case '2':
                apresentaMenu(MENU_ALTERAR);
                subOpcao = leValidaChar("", "1230");
            	switch(subOpcao)
            	{
            		case '1':
            			cod = leValidaInteiro("Informe a matricula do aluno a alterar", "Matricula", MATRICULA_MIN, MATRICULA_MAX);
            			alteraDadosAluno(cod);
                        getch();
            			break;
            		case '2':
            			cod = leValidaInteiro("Informe o codigo do curso que deseja editar","Codigo a ser editado",CODIGO_MIN,CODIGO_MAX);
            			alteraDadosCurso(cod);
                        getch();
            			break;
            		case '3':
            			puts("Ainda nao implementado!");
                        getch();
            			break;	
            	}
            	break;
            case '3':
                apresentaMenu(MENU_EXCLUIR);
                subOpcao = leValidaChar("", "1230");
            	switch(subOpcao)
            	{
            		case '1':
            			excluiAluno();
            			getch();
            			break;
            		case '2':
            			excluiCurso();
                        getch();
            			break;
            		case '3':
            			puts("Ainda nao implementado!");
                        getch();
            			break;	
            	}
            	break;
            case '4':
                apresentaMenu(MENU_BUSCA);
                subOpcao = leValidaChar("", "12340");
				switch(subOpcao)
				{
					case '1':
            			cod = leValidaInteiro("Informe a matricula a buscar", "Matricula", MATRICULA_MIN, MATRICULA_MAX);
            			pesquisaAlunoMatricula(cod);
                        getch();
            			break;
            		case '2':
            			cod = leValidaInteiro("Informe o codigo a buscar", "Codigo", CODIGO_MIN, CODIGO_MAX);
            			pesquisaCursoCod(cod);
            			getch();
            			break;
            		case '3':
						leValidaTexto(nomeBusca, "Informe o nome do curso", "Nome", 1, TAM_NOME_CURSO);
						pesquisaCursoNome(nomeBusca);
						getch();
						break;
            		case '4':
            			puts("Ainda nao implementado!");
                        getch();
            			break;
				}
				
                break;
            case '5':
                apresentaMenu(MENU_LISTA);
                subOpcao = leValidaChar("", "1230");
            	switch(subOpcao)
            	{
            		case '1':
                        listaDadosAlunos();
                        getch();
            			break;
            		case '2':
            			listaDadosCurso();
           				getch();
            			break;
            		case '3':
                        listaDadosCadastro();
                        getch();
            			break;	
            	}
            	break;            	
	      }
    }
    while(opcao != '0');
 
    return 0;
}

