// Funcoes relacionadas aos dados de Cadastros

#include "dados.h"
#include "funcoesBasicas.h"

//***********************************************************************************************************************
//  Objetivo: Matricular um aluno em um curso
//  Parametros: Nenhum
//  Retorno: Nenhum
void cadastraAlunoEmCurso()
{
    FILE *arqAlunos, *arqCursos, *arqMatriculas;
    int flag = 0, contaAlunos = 0, contaCursos = 0;   
    Curso curso;
    Aluno aluno;
    Cadastro matricula;
    do
    {
        listaDadosAlunos();
        if((arqAlunos = fopen(ARQ_ALUNOS,"rb")) != NULL)
        {
            matricula.matriculaAluno = leValidaInteiro("Informe a matricula do Aluno","Matricula do aluno", MATRICULA_MIN, MATRICULA_MAX);
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
        listaDadosCurso();
        if((arqCursos = fopen(ARQ_CURSOS,"rb")) != NULL)
        {
            matricula.codigoCurso = leValidaInteiro("\nInforme o codigo do Curso","Codigo do curso", CODIGO_MIN, CODIGO_MAX);
            while(!feof(arqCursos))
                if(fread(&curso, sizeof(Curso), 1, arqCursos))
                {
                    contaCursos++;
                    if(curso.codigo == matricula.codigoCurso)
                    {
                        flag = 1;
                        break;
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
    
    matricula.situacaoAluno = leValidaChar("Qual a situacao do aluno?\n1 - Cursando\n2 - Concluiu","12");
    matricula.situacaoPagamento = leValidaChar("Qual a situacao de pagamento do aluno?\n1 - Regular\n2 - Atrasada\n3 - Paga","123");
    if((arqMatriculas = fopen(ARQ_MATRICULAS,"ab")) != NULL)
        if(fwrite(&matricula, sizeof(Cadastro), 1, arqMatriculas))
            puts("Dados cadastrados com sucesso!");
        else
            puts("Os dados nao foram gravados com sucesso!");
    
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
        printf("%-18s%-19s%-19s%-10s\n","Matricula Aluno","Codigo do Curso","Situacao do Aluno","Situacao de Pagamento");
        while(!feof(arq))
            if(fread(&matricula, sizeof(Cadastro), 1, arq))
            {
                printf("%-18d%-19d",matricula.codigoCurso, matricula.matriculaAluno);
                if(matricula.situacaoAluno == '1')
                    printf("%-19s","Cursando");          
                else
                   printf("%-19s","Concluiu");
                if(matricula.situacaoPagamento == '1')
                    printf("%-19s","Regular\n");
                else
                    if(matricula.situacaoPagamento == '2')
                        printf("%-19s","Atrasada\n");
                    else
                        printf("%-19s","Totalmente paga\n");
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
