// Alunos : Marcus Vinicius Campos Fonseca e Lucas Lima da Silva
// Matriculas: UC14LINHA_MENU1868, UC14LINHA_MENU2446
// Objetivo: Criar um sistema para facilitar o gerenciamento de alunos e cursos de uma escola de informatica

#include <stdio.h>
#include <conio.c>
#include "dados.h"
#include "cores.h"
#include "funcoesAluno.h"
#include "funcoesCurso.h"
#include "funcoesBasicas.h"
#include "funcoesCadastro.h"

#define LINHA_MENU 10
#define COLUNA_MENU 5

int main(void)
{
    // Declaracoes
    int opcao = 1, subOpcao, subSubOpcao;
    
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
                                    "Pesquisar Cursos",
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
        opcao = menuVertical("ESCOLA DE INFORMATICA", opcoesMenuPrincipal, 5, BRANCO, AZUL_C, 1, LINHA_MENU, COLUNA_MENU, opcao, PRETO, CINZA_C);
        subOpcao = 1;
        switch(opcao)
        {
            case 1:
                do
                {
                    subOpcao = menuVertical("MENU ALUNOS", opcoesMenuAlunos, 6, BRANCO, AZUL_C, 1, LINHA_MENU, COLUNA_MENU, subOpcao, PRETO, CINZA_C);
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
                    subOpcao = menuVertical("MENU CURSOS", opcoesMenuCursos, 6, BRANCO, AZUL_C, 1, LINHA_MENU, COLUNA_MENU, subOpcao, PRETO, CINZA_C);
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
                    subOpcao = menuVertical("MENU CADASTRO", opcoesMenuMatriculas, 7, BRANCO, AZUL_C, 1, LINHA_MENU, COLUNA_MENU, subOpcao, PRETO, CINZA_C);
                    switch(subOpcao)
                    {
                        case 1:
                            cadastraAlunoEmCurso();
                            break;
                        case 2:
                            alteraCadastro();
                            break;
                        case 3:
                            excluiMatriculaAlunoEmUmCurso();
                            break;
                        case 4:
                            pesquisaApresentaCadastro();
                            break;
                        case 5:
                            apresentaAlunosMatriculadosEmUmCurso();
                            break;
                        case 6:
                            apresentarTodosAlunosCadastrados();
                            break;
                    }
                }
                while(subOpcao != 0 && subOpcao != 7);
                
                break;
            case 4:
                do
                {
                    subOpcao = menuVertical("MENU RELATORIOS", opcoesMenuRelatorios, 7, BRANCO, AZUL_C, 1, LINHA_MENU, COLUNA_MENU, subOpcao, PRETO, CINZA_C);
                    subSubOpcao = 1;
                    switch(subOpcao)
                    {
                        case 1:
                            do
                            {
                                subSubOpcao = menuVertical("MENU RELATORIO 1", opcoesPesquisaChave, 7, BRANCO, AZUL_C, 1, LINHA_MENU, COLUNA_MENU, subSubOpcao, PRETO, CINZA_C);
                                switch(subSubOpcao)
                                {
                                    case 1:
                                        pesquisaApresentaAlunoMatricula();
                                        break;
                                    case 2:
                                        pesquisaApresentaCursoCodigo();
                                        break;
                                    case 3:
                                        pesquisaApresentaCadastro();
                                        break;
                                    case 4:
                                        apresentaTodosAlunos();
                                        break;
                                    case 5:
                                        apresentaTodosCursos();
                                        break;
                                    case 6:
                                        apresentarTodosAlunosCadastrados();
                                        break;
                                }
                            }
                            while(subSubOpcao != 0 && subSubOpcao != 7);
                            break;
                        case 2:
                            pesquisaApresentaAlunoNome();
                            break;
                        case 3:
                            apresentaAlunosMatriculadosEmUmCurso();
                            break;
                        case 4:
                            pesquisaCurso();
                            break;
                        case 5:
                            apresentaAlunosMatriculadosEmPeriodo();
                            break;
                        case 6:
                            apresentaAlunosPorSituacao();
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
