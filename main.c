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
    int posCursoEncontrado;
    char opcao, subOpcao, nomeBusca[100];
    int cod;
// Instrucoes
    do
    {
        apresentaMenu(MENU_PRINCIPAL);
        opcao = leValidaChar("", "1230");
	    switch(opcao)
	    {
            case '1':
                apresentaMenu(MENU_CADASTRO);
                subOpcao = leValidaChar("", "1230");
            	switch(subOpcao)
            	{
            		case '1':
                        puts("Ainda nao implementado!");
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
                apresentaMenu(MENU_BUSCA);
                subOpcao = leValidaChar("", "12340");
				switch(subOpcao)
				{
					case '1':
            			puts("Ainda nao implementado!");
                        getch();
            			break;
            		case '2':
            			cod = leValidaInteiro("Informe o codigo buscado", "Codigo", CODIGO_MIN, CODIGO_MAX);
            			pesquisaCursoCod(cod, 1);
            			getch();
            			break;
            		case '3':
						leValidaTexto(nomeBusca, "Informe o nome do curso", "Nome", 1, TAM_NOME_CURSO);
						pesquisaCursoNome(nomeBusca);  // Mesmo não sendo necessario à solução atual,implementamos o mesmo para prática
						getch();
						break;
            		case '4':
            			puts("Ainda nao implementado!");
                        getch();
            			break;
				}
                break;
            case '3':
                apresentaMenu(MENU_LISTA);
                subOpcao = leValidaChar("", "1230");
            	switch(subOpcao)
            	{
            		case '1':
            			puts("Ainda nao implementado!");
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
	      }
 }
 while(opcao != '0');
 
return 0;
}

