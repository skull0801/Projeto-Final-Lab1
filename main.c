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
                                    "Alterar os Dados de uma Matricula",
                                    "Excluir uma Matricula",
                                    "Pesquisar uma Matricula",
                                    "Apresentar Alunos Matriculados em um Curso",
                                    "Apresentar Todas as Matriculas Existentes",
                                    "Voltar para Menu Principal"};
                                    
    char *opcoesMenuRelatorios[] = {"Pesquisa por Chave ou Todos",
                                    "Pesquisa de Alunos por Nome",
                                    "Listar Alunos de um Curso",
                                    "Pesquisar Cursos por Nome",
                                    "Alunos Matriculados em um Periodo",
                                    "Situacao Financeira dos Estudantes",
                                    "Voltar para Menu Principal"};
                                    
    char *opcoesPesquisaChave[] = {"Pesquisar Alunos por Matricula",
                                   "Pesquisar Curso por Codigo",
                                   "Pesquisar Matricula de Aluno em Curso",
                                   "Listar Todos os Alunos",
                                   "Listar Todos os Cursos",
                                   "Listar Todos as Matriculas",
                                   "Voltar"};
    
    // Instrucoes
    do
    {
        opcao = menuVertical("MENU PRINCIPAL", opcoesMenuPrincipal, 5, BRANCO, AZUL_C, 1, 10, 5, 1, PRETO, CINZA_C);
        switch(opcao)
        {
            case 1:
                do
                {
                    subOpcao = menuVertical("MENU ALUNOS", opcoesMenuAlunos, 6, BRANCO, AZUL_C, 1, 10, 5, 1, PRETO, CINZA_C);
                    switch(subOpcao)
                    {
                        case 1:
                            cadastraAluno();
                            break;
                        case 2:
                            alteraAluno();
                            break;
                        case 3:
                            excluiAluno();
                            break;
                        case 4:
                            pesquisaAluno();
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
                    subOpcao = menuVertical("MENU CURSOS", opcoesMenuCursos, 6, BRANCO, AZUL_C, 1, 10, 5, 1, PRETO, CINZA_C);
                    switch(subOpcao)
                    {
                        case 1:
                            cadastraCurso();
                            break;
                        case 2:
                            alteraCurso();
                            break;
                        case 3:
                            excluiCurso();
                            break;
                        case 4:
                            pesquisaCurso();
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
                    subOpcao = menuVertical("MENU CADASTRO", opcoesMenuMatriculas, 7, BRANCO, AZUL_C, 1, 10, 5, 1, PRETO, CINZA_C);
                    switch(subOpcao)
                    {
                        case 1:
                            cadastraAlunoEmCurso();
                            getch();
                            clrscr();
                            break;
                        case 2:
                            alteraCadastro();
                            getch();
                            clrscr();
                            break;
                        case 3:
                            excluiMatriculaAlunoEmUmCurso();
                            getch();
                            clrscr();
                            break;
                        case 4:
                            pesquisaApresentaCadastro();
                            getch();
                            clrscr();
                            break;
                        case 5:
                            apresentaAlunosMatriculadosEmUmCurso();
                            getch();
                            clrscr();
                            break;
                        case 6:
                            apresentarTodosAlunosCadastrados();
                            getch();
                            clrscr();
                            break;
                    }
                }
                while(subOpcao != 0 && subOpcao != 7);
                
                break;
            case 4:
                do
                {
                    subOpcao = menuVertical("MENU RELATORIOS", opcoesMenuRelatorios, 7, BRANCO, AZUL_C, 1, 10, 5, 1, PRETO, CINZA_C);
                    switch(subOpcao)
                    {
                        case 1:
                            do
                            {
                                subSubOpcao = menuVertical("MENU RELATORIO 1", opcoesPesquisaChave, 7, BRANCO, AZUL_C, 1, 10, 5, 1, PRETO, CINZA_C);
                                switch(subSubOpcao)
                                {
                                    case 1:
                                        pesquisaApresentaAlunoMatricula();
                                        clrscr();
                                        break;
                                    case 2:
                                        pesquisaApresentaCursoCodigo();
                                        getch();
                                        clrscr();
                                        break;
                                    case 3:
                                        pesquisaApresentaCadastro();
                                        getch();
                                        clrscr();
                                        break;
                                    case 4:
                                        apresentaTodosAlunos();
                                        clrscr();
                                        break;
                                    case 5:
                                        apresentaTodosCursos();
                                        getch();
                                        clrscr();
                                        break;
                                    case 6:
                                        apresentarTodosAlunosCadastrados();
                                        getch();
                                        clrscr();
                                        break;
                                }
                            }
                            while(subSubOpcao != 0 && subSubOpcao != 7);
                            break;
                        case 2:
                            pesquisaApresentaAlunoNome();
                            clrscr();
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
