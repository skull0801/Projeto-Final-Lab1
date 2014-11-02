// Alunos : Marcus Vinicius Campos Fonseca e Lucas Lima da Silva
// Matriculas: UC14101868, UC14102446
// Implementacao: de algumas das funcionalidades do projeto final

#include <stdio.h>
#include <conio.c>
#include "dados.h"
#include "cores.h"
#include "funcoesAluno.h"
#include "funcoesCurso.h"
#include "funcoesBasicas.h"
#include "funcoesCadastro.h"

int main(void)
{
    // Declaracoes
    int opcao, subOpcao;
    char *opcoesMenuPrincipal[] = {"Alunos",
                                   "Cursos",
                                   "Matriculas",
                                   "Relatorios",
                                   "Sair do Programa"};
                                   
    char *opcoesMenuAlunos[] = {"Cadastrar um Aluno",
                                "Alterar Dados de um Aluno",
                                "Excluir um Aluno",
                                "Pesquisar um Aluno",
                                "Apresentar Alunos Cadastrados",
                                "Voltar para Menu Principal"};
                                
    char *opcoesMenuCursos[] = {"Criar um Novo Curso",
                                "Alterar Dados de um Curso",
                                "Excluir um Curso",
                                "Pesquisar Cursos",
                                "Apresentar Cursos Existentes",
                                "Voltar para Menu Principal"};
                                
    char *opcoesMenuMatriculas[] = {"Matricular Aluno em um Curso",
                                    "Apresentar Matriculas Existentes",
                                    "Voltar para Menu Principal"};
                                    
    char *opcoesMenuRelatorios[] = {"Voltar para Menu Principal"};
    // Instrucoes
    do
    {
        opcao = menuVertical(opcoesMenuPrincipal, 5, BRANCO, MARROM, 1, 10, 5, 1, PRETO, CINZA_C);
        switch(opcao)
        {
            case 1:
                do
                {
                    subOpcao = menuVertical(opcoesMenuAlunos, 6, BRANCO, MARROM, 1, 10, 5, 1, PRETO, CINZA_C);
                    gotoxy(1,1);
                    switch(subOpcao)
                    {
                        case 1:
                            cadastraAluno();
                            getch();
                            clrscr();
                            break;
                        case 2:
                            alteraAluno();
                            getch();
                            clrscr();
                            break;
                        case 3:
                            excluiAluno();
                            getch();
                            clrscr();
                            break;
                        case 4:
                            pesquisaAluno();
                            getch();
                            clrscr();
                            break;
                        case 5:
                            listaDadosAlunos();
                            getch();
                            clrscr();
                            break;
                    }
                }
                while(subOpcao != 0 && subOpcao != 6);
                
                break;
            case 2:
                do
                {
                    subOpcao = menuVertical(opcoesMenuCursos, 6, BRANCO, MARROM, 1, 10, 5, 1, PRETO, CINZA_C);
                    gotoxy(1,1);
                    switch(subOpcao)
                    {
                        case 1:
                            cadastraCurso();
                            getch();
                            clrscr();
                            break;
                        case 2:
                            alteraCurso();
                            getch();
                            clrscr();
                            break;
                        case 3:
                            excluiCurso();
                            getch();
                            clrscr();
                            break;
                        case 4:
                            pesquisaCurso();
                            getch();
                            clrscr();
                            break;
                        case 5:
                            listaDadosCursos();
                            getch();
                            clrscr();
                            break;
                    }
                }
                while(subOpcao != 0 && subOpcao != 6);
                
                break;
            case 3:
                do
                {
                    subOpcao = menuVertical(opcoesMenuMatriculas, 3, BRANCO, MARROM, 1, 10, 5, 1, PRETO, CINZA_C);
                    gotoxy(1,1);
                    switch(subOpcao)
                    {
                        case 1:
                            cadastraAlunoEmCurso();
                            getch();
                            clrscr();
                            break;
                        case 2:
                            listaDadosCadastro();
                            getch();
                            clrscr();
                            break;
                    }
                }
                while(subOpcao != 0 && subOpcao != 3);
                
                break;
            case 4:
                do
                {
                    subOpcao = menuVertical(opcoesMenuRelatorios, 1, BRANCO, MARROM, 1, 10, 5, 1, PRETO, CINZA_C);
                }
                while(subOpcao != 0 && subOpcao != 1);
                
                break;
        }
    }
    while(opcao != 0 && opcao != 5);
    
    return 0;
}
