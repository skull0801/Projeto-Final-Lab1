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
    int opcao, subOpcao, subSubOpcao;
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
                                    "Apresentar todos os alunos matriculados",
                                    "Excluir a matricula de um aluno em um curso",
                                    "Alterar os dados de um cadastro",
                                    "Voltar para Menu Principal"};
                                    
    char *opcoesMenuRelatorios[] = {"Pesquisa por Chave dos Dados",
                                    "Pesquisa de Alunos por Nome",
                                    "Listar Alunos de um Curso",
                                    "Pesquisar Cursos por Nome",
                                    "Alunos Matriculados em um Periodo",
                                    "Situacao Financeira dos Estudantes",
                                    "Voltar para Menu Principal"};
                                    
    char *opcoesPesquisaChave[] = {"Pesquisar Alunos por Matricula",
                                   "Pesquisar Curso por Codigo",
                                   "Pesquisar Matricula de Aluno em Curso",
                                   "Voltar"};
    
    
    // Instrucoes
    do
    {
        opcao = menuVertical(opcoesMenuPrincipal, 5, BRANCO, AZUL_C, 1, 10, 5, 1, PRETO, CINZA_C);
        switch(opcao)
        {
            case 1:
                do
                {
                    subOpcao = menuVertical(opcoesMenuAlunos, 6, BRANCO, AZUL_C, 1, 10, 5, 1, PRETO, CINZA_C);
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
                            apresentaTodosAlunos();
                            break;
                    }
                }
                while(subOpcao != 0 && subOpcao != 6);
                
                break;
            case 2:
                do
                {
                    subOpcao = menuVertical(opcoesMenuCursos, 6, BRANCO, AZUL_C, 1, 10, 5, 1, PRETO, CINZA_C);
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
                            clrscr();
                            break;
                        case 4:
                            pesquisaCurso();
                            getch();
                            clrscr();
                            break;
                        case 5:
                            apresentaTodosCursos();
                            break;
                    }
                }
                while(subOpcao != 0 && subOpcao != 6);
                
                break;
            case 3:
                do
                {
                    subOpcao = menuVertical(opcoesMenuMatriculas, 6, BRANCO, AZUL_C, 1, 10, 5, 1, PRETO, CINZA_C);
                    gotoxy(1,1);
                    switch(subOpcao)
                    {
                        case 1:
                            cadastraAlunoEmCurso();
                            getch();
                            clrscr();
                            break;
                        case 2:
                            apresentaAlunosMatriculadosEmUmCurso();
                            clrscr();
                            break;
                        case 3:
                            apresentarTodosAlunosCadastrados();
                            getch();
                            clrscr();
                            break;
                        case 4:
                            excluiMatriculaAlunoEmUmCurso();
                            getch();
                            clrscr();
                            break;
                        case 5:
                            alteraCadastro();
                            getch();
                            clrscr();
                            break;
                    }
                }
                while(subOpcao != 0 && subOpcao != 6);
                
                break;
            case 4:
                do
                {
                    subOpcao = menuVertical(opcoesMenuRelatorios, 7, BRANCO, AZUL_C, 1, 10, 5, 1, PRETO, CINZA_C);
                    gotoxy(1,1);
                    switch(subOpcao)
                    {
                        case 1:
                            do
                            {
                                subSubOpcao = menuVertical(opcoesPesquisaChave, 4, BRANCO, AZUL_C, 1, 10, 5, 1, PRETO, CINZA_C);
                                gotoxy(1,1);
                                switch(subSubOpcao)
                                {
                                    case 1:
                                        pesquisaAluno();
                                        getch();
                                        clrscr();
                                        break;
                                    case 2:
                                        pesquisaApresentaCursoCodigo();
                                        getch();
                                        clrscr();
                                        break;
                                }
                            }
                            while(subSubOpcao != 0 && subSubOpcao != 4);
                            
                            break;
                        case 3:
                            apresentaAlunosMatriculadosEmUmCurso();
                            clrscr();
                            break;
                        case 4:
                            pesquisaApresentaCursoNome();
                            getch();
                            clrscr();
                            break;
                    }
                }
                while(subOpcao != 0 && subOpcao != 7);
                
                break;
        }
    }
    while(opcao != 0 && opcao != 5);
    
    return 0;
}
