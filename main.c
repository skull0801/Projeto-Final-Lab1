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
    char opcao, subOpcao;
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
                        cadastraAluno();
                        getch();
            			break;
            		case '2':
		                cadastraCurso();
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
            			alteraAluno();
                        getch();
            			break;
            		case '2':
                        alteraCurso();
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
                subOpcao = leValidaChar("", "1230");
				switch(subOpcao)
				{
					case '1':
            			pesquisaAluno();
                        getch();
            			break;
            		case '2':
            			pesquisaCurso();
            			getch();
            			break;
            		case '3':
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

