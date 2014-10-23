// Aluno : 

/*
 Sintese
   Objetivo:
 
   Entrada : 

   Saida   :  

*/

#include "dados.h"

int main(void)
{
// Declaracoes
    Curso curso;
    int posCursoEncontrado;
    char opcao,opcaoSubMenu;
    int cod;
// Instrucoes
  do
  {
      opcao = leValidaChar("***************************************\nMenu Principal\n***************************************\n1 - Cadastrar\n2 - Pesquisar\n3 - Listar\n0 - Sair\n***************************************\n",
	  					   "1230");
		      switch(opcao)
		      {
	            case '1':
		            	opcaoSubMenu = leValidaChar("***************************************\nCadastros\n***************************************\n1 - Cadastrar Aluno\n2 - Cadastrar Curso\n3 - Matricular Aluno\n0 - Voltar\n***************************************\n",
												    "1230");
		            	switch(opcaoSubMenu)
		            	{
		            		case '1':
		            			puts("Ainda nao implementado!\n");
		            			getch();
		            			break;
		            		case '2':
				                leDadosCurso(&curso);
				                gravaDadosCurso(&curso);
				                break;
				            case '3':
		            			puts("Ainda nao implementado!\n");
		            			getch();
		            			break;
						}	
		               break;
		            case '2':
						opcaoSubMenu = leValidaChar("***************************************\nBusca\n***************************************\n1 - Buscar um Aluno\n2 - Buscar um Curso\n3 - Buscar **** \n0 - Voltar\n***************************************\n",
													"1230");
						switch(opcaoSubMenu)
						{
							case '1':
								puts("Ainda nao implementado!\n");
		            			getch();
		            			break;
		            		case '2':
		            			cod = leValidaInteiro("Informe o codigo buscado","Codigo",1000,2000000);
	                			pesquisaCursoCod(cod, 1);
	                			getch();
	                			break;
	                		case '3':
	                			puts("Ainda nao implementado!\n");
		            			getch();
		            			break;
						}
	                break;
	            case '3':
	                	opcaoSubMenu = leValidaChar("***************************************\nListar\n***************************************\n1 - Listar alunos\n2 - Listar Cursos\n3 - Listar ****\n0 - Voltar\n***************************************\n",
													"1230");
	                	switch(opcaoSubMenu)
	                	{
	                		case '1':
	                			puts("Ainda nao implementado!\n");
		            			getch();
		            			break;
		            		case '2':
		            			listaDadosCurso();
	               				getch();
	                			break;
	                		case '3':
	                			puts("Ainda nao implementado!\n");
		            			getch();
		            			break;	
	                	}
		      }
 }
 while(opcao != '0');
 
return 0;
}

