// Funcoes relacionadas aos dados de Cadastros

#include <stdio.h>
#include "dados.h"
#include "funcoesBasicas.h"
#include "funcoesCadastro.h"

//***********************************************************************************************************************
//  Objetivo: Matricular um aluno em um curso
//  Parametros: Nenhum
//  Retorno: Nenhum
void cadastraAlunoEmCurso()
{
    FILE *arqAlunos, *arqCursos, *arqMatriculas;
    int flag = 0, flagRepetido = 0, contaAlunos = 0, contaCursos = 0;   
    Curso curso;
    Aluno aluno;
    Cadastro matricula;
    do
    {
        listaDadosAlunos();
        if((arqAlunos = fopen(ARQ_ALUNOS,"rb")) != NULL)
        {
            matricula.matriculaAluno = leValidaInteiro("Informe a matricula do Aluno", "Matricula do aluno", MATRICULA_MIN, MATRICULA_MAX);
            while(!feof(arqAlunos))
            {
                
                if(fread(&aluno, sizeof(Aluno), 1, arqAlunos))
                {
                    contaAlunos++;
                    if(aluno.matricula == matricula.matriculaAluno)
                    {
                        flag = 1;
                        break;
                    }
                    
                }
                
            }
            fclose(arqAlunos);
        }
        else
        {
            puts("O arquivo dos alunos nao foi encontrado!");
            return ;
        }
        
        if(contaAlunos == 0)
        {
            clrscr();
            printf("Nao ha nenhum Aluno cadastrado ate o momento!");
            return;
        }
    }
    while(flag == 0);
    flag = 0;
    do
    {
        listaDadosCursos();
        if((arqCursos = fopen(ARQ_CURSOS,"rb")) != NULL)
        {
            matricula.codigoCurso = leValidaInteiro("\nInforme o codigo do Curso","Codigo do curso", CODIGO_MIN, CODIGO_MAX);
            while(!feof(arqCursos))
            {
                if(fread(&curso, sizeof(Curso), 1, arqCursos))
                {
                    contaCursos++;
                    if(curso.codigo == matricula.codigoCurso)
                    {
                        flag = 1;
                        break;
                    }
                }
            }
            fclose(arqCursos);   
        }
        else
        {
            puts("O arquivo dos cursos nao foi encontrado!");
            return ;
        }
        
        if(contaCursos == 0)
        {
            clrscr();
            printf("Nao ha nenhum Curso cadastrado ate o momento!");
            return;
        }
    }
    while(flag == 0);
    
    flag = verificaAlunoRepetidoCadastrando(curso, aluno);
    if(flag == 0)
    {
        matricula.situacaoAluno = leValidaChar("Qual a situacao do aluno?\n1 - Cursando\n2 - Concluiu","12");
        matricula.situacaoPagamento = leValidaChar("Qual a situacao de pagamento do aluno?\n1 - Regular\n2 - Atrasada\n3 - Paga","123");
        gravaDadosMatricula(matricula);
    }
    else
        puts("O aluno ja esta matriculado nesse curso!");
}

//***********************************************************************************************************************
//  Objetivo: Listar todas as matriculas
//  Parametros: Nenhum
//  Retorno: Nenhum
void listaDadosCadastro()
{
    FILE *arq;
    Cadastro matricula;
    int contaMatriculas;
    if((arq = fopen(ARQ_MATRICULAS,"rb")) != NULL)
    {
        printf("%-18s%-19s%-19s%-10s","Codigo do Curso","Matricula Aluno","Situacao do Aluno","Situacao de Pagamento");
        while(!feof(arq))
            if(fread(&matricula, sizeof(Cadastro), 1, arq))
            {
                printf("\n%-18d%-19d",matricula.codigoCurso, matricula.matriculaAluno);
                if(matricula.situacaoAluno == '1')
                    printf("%-19s","Cursando");          
                else
                   printf("%-19s","Concluiu");
                if(matricula.situacaoPagamento == '1')
                    printf("%-19s","Regular");
                else
                    if(matricula.situacaoPagamento == '2')
                        printf("%-19s","Atrasada");
                    else
                        printf("%-19s","Totalmente paga");
            }
            fclose(arq);
    }
    else
    {
        clrscr();
        puts("Nao ha nenhum aluno matriculado ate o momento");
        return;
    }
}

//***********************************************************************************************************************
//  Objetivo: Gravar os dados de uma matricula(Cadastro)
//  Parametros: A matricula
//  Retorno: Nenhum
void gravaDadosMatricula(Cadastro matricula)
{
    FILE *arq;
    if((arq = fopen(ARQ_MATRICULAS,"ab")) != NULL)
    {
        if(fwrite(&matricula, sizeof(Cadastro), 1, arq))
            puts("Dados cadastrados com sucesso!");
        else
            puts("Os dados nao foram gravados!");
        fclose(arq);
    }
}

//***********************************************************************************************************************
//  Objetivo: Verificar se o aluno ja esta cadastrado em um curso
//  Parametros: O codigo do curso e a matricula do Aluno
//  Retorno: Flag = 1 se o aluno ja estiver cadastrado ou flag = 0 se o aluno nao estiver cadastrado
int verificaAlunoRepetidoCadastrando(Curso curso, Aluno aluno)
{
    int flag = 0;
    FILE *arq;
    Cadastro matricula;
    if((arq = fopen(ARQ_MATRICULAS,"rb")) != NULL)
    {
        while(!feof(arq))
            if(fread(&matricula, sizeof(Cadastro), 1, arq))
                if(matricula.matriculaAluno == aluno.matricula && matricula.codigoCurso == curso.codigo && matricula.situacaoAluno == '1')
                {
                    flag =1;
                    break;
                }
        fclose(arq);
    }
    return flag;
}
