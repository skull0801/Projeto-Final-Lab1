// Alunos : Marcus Vinicius Campos Fonseca e Lucas Lima da Silva
// Matriculas: UC14101868, UC14102446

/*
 Sintese
    Objetivo: Criar um sistema para facilitar o gerenciamento de alunos e cursos de uma escola de informatica
    
    Entrada:  Para cadastrar aluno (Nome, CPF, Idade, Matricula, Sexo), para curso (Nome, Mensalidade, Carga Horaria)
              e para cadastro (Situacoes financeira e de conclusao), para alterar, excluir e pesquisar: alunos (Nome ou matricula),
              cursos (Nome ou codigo), e matriculas (Nome do curso), para pesquisa de data (data inicial e final), o restante das
              selecoes sao feitas por meio de menu vertical
              
    Saida:    Apresentacao de dados cadastrais de aluno, de cursos e matriculas (pesquisa por chave unica), tabelas com alunos e cursos
              correspondentes (pesquisa por parte do nome, situacao do aluno, ou alunos matriculados em periodo)
           
*/

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
                                   
    char *tituloMenu[] = {"MENU ALUNOS",
                          "MENU CURSOS",
                          "MENU CADASTRO",
                          "MENU RELATORIOS"};
                          
                                   
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
                                    "Apresentar Todas as Matriculas Existentes",
                                    "Apresentar Alunos Matriculados em um Curso",
                                    "Voltar para Menu Principal"};
                                    
    char *opcoesMenuRelatorios[] = {"Pesquisa por Chave ou Todos",
                                    "Pesquisa de Alunos por Nome",
                                    "Listar Alunos de um Curso",
                                    "Pesquisa de Cursos por Nome",
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
                                   
    int qtdOpcoes[] = {6, 6, 7, 7};
    
    char **opcoesMenu[] = {opcoesMenuAlunos, opcoesMenuCursos, opcoesMenuMatriculas, opcoesMenuRelatorios};
    
    void (*funcoesAluno[])() = {cadastraAluno, alteraAluno, excluiAluno, pesquisaAluno, apresentaAlunos};
    
    void (*funcoesCurso[])() = {cadastraCurso, alteraCurso, excluiCurso, pesquisaCurso, apresentaCursos};
    
    void (*funcoesMatricula[])() = {cadastraAlunoEmCurso, alteraCadastro, excluiMatriculaAlunoEmUmCurso, 
                                    pesquisaApresentaCadastro, apresentaTodosAlunosCadastrados, 
                                    apresentaAlunosMatriculadosEmUmCurso};
                                    
    void (*funcoesRelatorios[])() = {cadastraAluno, pesquisaAlunoNome, apresentaAlunosMatriculadosEmUmCurso, 
                                     pesquisaCursoNome, apresentaAlunosMatriculadosEmPeriodo, apresentaAlunosPorSituacao};
                                    
    void (**funcoes[])() = {funcoesAluno, funcoesCurso, funcoesMatricula, funcoesRelatorios};
    // Instrucoes
    do if((opcao = menuVertical("ESCOLA DE INFORMATICA", opcoesMenuPrincipal, 5, BRANCO, AZUL_C, 1, LINHA_MENU, COLUNA_MENU, opcao, PRETO, CINZA_C)) != 0 && opcao != 5)
        do if((subOpcao = menuVertical(tituloMenu[opcao-1], opcoesMenu[opcao-1], qtdOpcoes[opcao-1], BRANCO, AZUL_C, 1, LINHA_MENU, COLUNA_MENU, subOpcao, PRETO, CINZA_C)) != 0 && subOpcao != qtdOpcoes[opcao-1])
            (*(funcoes[opcao-1])[subOpcao-1])();
        while(subOpcao != 0 && subOpcao != qtdOpcoes[opcao-1]);
    while(opcao != 0 && opcao != 5);
    
    return 0;
}
