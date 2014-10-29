// Alunos : Marcus Vinícius Campos Fonseca e Lucas Lima da Silva
// Matrículas: UC14101868, UC14102446
// Implementação de algumas das funcionalidades do projeto final

#include <stdio.h>
#include <conio.c>
#include "dados.h"

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
            			puts("Ainda nao implementado!");
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
            			cod = leValidaInteiro("Informe a matricula a buscar", "Matricula", MATRICULA_MIN, MATRICULA_MAX);
            			alteraDadosAluno(cod);
                        getch();
            			break;
            		case '2':
            			puts("Ainda nao implementado!");
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
            			puts("Ainda nao implementado!");
                        getch();
            			break;
            		case '2':
            			puts("Ainda nao implementado!");
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
            			pesquisaAlunoMatricula(cod, 1);
                        getch();
            			break;
            		case '2':
            			cod = leValidaInteiro("Informe o codigo a buscar", "Codigo", CODIGO_MIN, CODIGO_MAX);
            			pesquisaCursoCod(cod, 1);
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
            			puts("Ainda nao implementado!");
                        getch();
            			break;	
            	}
            	break;            	
	      }
 }
 while(opcao != '0');
 
return 0;
}

