// Funcoes relacionadas aos dados de alunos

#include <stdio.h>
#include "dados.h"
#include "funcoesBasicas.h"
#include "funcoesAluno.h"

//***********************************************************************************************************************
//  Objetivo: Ler os dados de um aluno
//  Parametros: Referencia ao aluno
//  Retorno: Nenhum
void leDadosAluno(Aluno *aluno)
{
    int cpfExiste, cpfValida, flagMatricula;
    leValidaTexto(aluno->nome, "Informe o nome do aluno", "Nome do aluno", 3, TAM_NOME_ALUNO);
    do
    {
        aluno->matricula = leValidaInteiro("Informe a matricula do aluno", "Matricula", MATRICULA_MIN, MATRICULA_MAX);
        flagMatricula = pesquisaAlunoMatricula(aluno->matricula);
        if(flagMatricula)
            printf("A matricula %d ja esta cadastrada!\n", aluno->matricula);
    }
    while(flagMatricula);
    
    do
    {
        leValidaTexto(aluno->cpf, "Informe o cpf do aluno", "CPF", 11, TAM_CPF);
        cpfValida = validaCPF(aluno->cpf);
        cpfExiste = verificaCPFAluno(aluno->cpf);
        if(!cpfValida)
            printf("O CPF %s e invalido!\n", aluno->cpf);
        else if(cpfExiste)
            printf("O CPF %s ja esta cadastrado!\n", aluno->cpf);
    }
    while(cpfExiste == 1 || cpfValida == 0);
    
    aluno->idade = leValidaInteiro("Informe a idade do aluno", "Idade", MIN_IDADE, MAX_IDADE);
    aluno->sexo = leValidaChar("Informe o sexo do aluno: ", "MF");
    geraDataIngresso(&(aluno->dataIngresso));
}

//***********************************************************************************************************************
// Objetivo: Gravar os dados de um aluno
// Parametros: Referencia ao aluno
// Retorno: nenhum
void gravaDadosAluno(Aluno *aluno)
{
    FILE *arq;
    if((arq = fopen(ARQ_ALUNOS,"ab")) != NULL)
    {
        if(fwrite(aluno, sizeof(Aluno), 1, arq))
            puts("Os dados foram gravados com sucesso!");
        else
            puts("Os dados nao puderam ser gravados!");
        fclose(arq);
    }
    else
        puts("Os dados nao puderam ser gravados!");
}

//***********************************************************************************************************************
// Objetivo: Listar todos os alunos cadastrados
// Parametros: Nenhum
// Retorno: nenhum
void listaDadosAlunos()
{
    FILE *arq;
    Aluno aluno;
    char dataIngresso[11], sexo[10], cpf[15];
    int qtdeApresentados = 0;
    printf("%-27s%-12s%-5s%-10s%-12s%-10s\n", "Nome", "CPF", "Idade", "Sexo", "Data Ing.", "Matricula");
    if((arq = fopen(ARQ_ALUNOS,"rb")) != NULL)
    {
        while(!feof(arq))
            if(fread(&aluno, sizeof(Aluno), 1, arq))
            {
                if(aluno.sexo=='M')
                    sprintf(sexo, "MASCULINO");
                else
                    sprintf(sexo, "FEMININO");
                sprintf(dataIngresso, "%02d/%02d/%04d", aluno.dataIngresso.dia, aluno.dataIngresso.mes, aluno.dataIngresso.ano);
                
                printf("%-27.25s", aluno.nome);
                printf("%-12s", aluno.cpf);
                printf("%-5d", aluno.idade);
                printf("%-10s", sexo);
                printf("%-12s", dataIngresso);
                printf("%-10d\n", aluno.matricula);
                
                qtdeApresentados++;
            }
        fclose(arq);
    }
    if(!qtdeApresentados)
    {
        clrscr();
        puts("Nao ha nenhum aluno cadastrado ate o momento!");    
    }
}

//***********************************************************************************************************************
//  Objetivo: Alterar os dados de um aluno
//  Parametros: Matricula do aluno a ser alterado
//  Retorno: nenhum
void alteraDadosAluno(int matricula)
{
    FILE *arq;
    int posAluno;
    char opcao, confirmacao;
    Aluno aluno;
    
    posAluno = pesquisaAlunoMatricula(matricula);
    
    if(posAluno)
    {
        if((arq = fopen(ARQ_ALUNOS, "rb+")) != NULL )
        {
            if(!fseek(arq, sizeof(Aluno)*(posAluno-1), 0))
            {
                if(fread(&aluno, sizeof(Aluno), 1, arq))
                {
                    do
                    {
                        apresentaAluno(aluno);
                        opcao = leValidaChar("\n\nO que deseja alterar?\n1 - Nome\n2 - Idade\n3 - Sexo\nC - Cancelar\nG - Gravar", "123GC");
                        switch(opcao)
                        {
                            case '1':
                                leValidaTexto(aluno.nome, "Informe o novo nome", "Nome", 3, TAM_NOME_ALUNO);
                                break;
                            case '2':
                                aluno.idade = leValidaInteiro("Informe a nova idade", "Idade", MIN_IDADE, MAX_IDADE);
                                break;
                            case '3':
                                aluno.sexo = leValidaChar("Informe o novo sexo (M/F): ", "MF");
                                break;
                        }
                    }
                    while(opcao != 'C' && opcao != 'G');
                    
                    if(opcao!='C')
                    {
                        apresentaAluno(aluno);
                        confirmacao = leValidaChar("\n\nVoce tem certeza que deseja salvar os dados? (S/N)", "SN");
                        if(confirmacao=='S')
                        {
                            if(!fseek(arq, sizeof(Aluno)*(posAluno-1), 0))
                            {
                                if(fwrite(&aluno, sizeof(Aluno), 1, arq))
                                    printf("Dados alterados com sucesso!");
                                else
                                    printf("Os dados nao puderam ser alterados!");
                            }
                            else
                                printf("Os dados nao puderam ser alterados!");
                        }
                        else
                            printf("Os dados nao foram alterados!");
                    }
                    else
                        printf("Os dados nao foram alterados!");
                }
                else
                    printf("O aluno nao pode ser lido para ser alterado!");
            }
            else
                printf("O aluno nao pode ser lido para ser alterado!");
                
            fclose(arq);
        }
        else
            printf("O arquivo nao pode ser aberto para ser alterado!");
    }
    else
        printf("O aluno nao foi encontrado!");
}

//***********************************************************************************************************************
// Objetivo: Ler o codigo de um aluno, buscar pelo mesmo, e confirmar se o usuario deseja excluir o aluno, caso queira, excluir
// Parametros: Nenhum
// Retorno: Nenhum
void excluiAluno()
{
    Aluno aluno;
    FILE *arq = NULL;
    int posAluno, matricula;
    char opcao;
    
    matricula = leValidaInteiro("Informe a matricula do aluno para excluir", "Matricula", MATRICULA_MIN, MATRICULA_MAX);
    
    posAluno = pesquisaAlunoMatricula(matricula);
    
    if(posAluno)
    {
        if((arq = fopen(ARQ_ALUNOS, "rb")) != NULL)
        {
            if(!fseek(arq, sizeof(Aluno)*(posAluno-1), 0))
            {
                if(fread(&aluno, sizeof(Aluno), 1, arq))
                {
                    apresentaAluno(aluno);
                    opcao = leValidaChar("\n\nTem certeza de que deseja excluir este aluno? (S/N) ", "SN");
                    if(opcao == 'S')
                    {
                        fclose(arq);
                        arq = NULL;
                        excluiDadosAluno(posAluno);
                    }
                    else
                        printf("Os dados nao foram excluidos!");
                }
                else
                    printf("O aluno nao pode ser lido!");
            }
            else
                printf("O aluno nao pode ser encontrado!");
        }
        else
            printf("O arquivo de alunos nao pode ser aberto!");
        
        if(arq != NULL)
            fclose(arq);
    }
    else
        printf("Este aluno nao esta matriculado!");
}

//***********************************************************************************************************************
//  Objetivo: Excluir um aluno
//  Parametros: Posicao do aluno a ser excluido
//  Retorno: nenhum
void excluiDadosAluno(int posAluno)
{
    FILE *arq, *arqTemp;
    int qtdCopiados = 0;
    char opcao;
    Aluno aluno;
    
    if(posAluno)
    {
        if((arq = fopen(ARQ_ALUNOS, "rb")) != NULL )
        {
            if((arqTemp = fopen(ARQ_ALUNOS_TEMP, "wb")) != NULL)
            {
                while(!feof(arq))
                {
                    if(fread(&aluno, sizeof(Aluno), 1, arq))
                    {
                        qtdCopiados++;
                        if(posAluno != qtdCopiados)
                            fwrite(&aluno, sizeof(Aluno), 1, arqTemp);
                    }
                }
                
                fclose(arqTemp);
                fclose(arq);
                
                if(!remove(ARQ_ALUNOS))
                {
                    if(!rename(ARQ_ALUNOS_TEMP, ARQ_ALUNOS))
                        printf("O aluno foi excluido com sucesso!");
                    else
                        printf("O novo arquivo nao pode ser renomeado, todos os dados foram perdidos!");
                }
                else
                    printf("O arquivo antigo nao pode ser excluido, logo o aluno nao foi excluido!");
            }
            else
            {
                printf("O arquivo para exclusao nao pode ser criado!");
                fclose(arq);
            }
        }
        else
            printf("O arquivo nao pode ser aberto para remover o aluno!");
    }
    else
        printf("O aluno nao foi encontrado!");
}

//***********************************************************************************************************************
//  Objetivo: Pesquisar um aluno dentro de um arquivo por matricula
//  Parametros: matricula a ser pesquisada
//  Retorno: numero positivo se encontrado (posicao do aluno no arquivo de 1 a n, sendo n o numero de alunos), 0 - codigo nao encontrado
int pesquisaAlunoMatricula(int matriculaBusca)
{
    FILE *arq;
    Aluno aluno;
    int pos = 0, flag = 0;
    if((arq = fopen(ARQ_ALUNOS, "rb")) != NULL)
    {
        while(!feof(arq))
        {
            if(fread(&aluno, sizeof(Aluno), 1, arq))
            {
                pos++;
                if(matriculaBusca == aluno.matricula)
                {
                    flag = 1;
                    break;
                }
            }
        }
        fclose(arq);
    }
    if(!flag)
        pos = 0;
    return pos;
}

//***********************************************************************************************************************
// Objetivo: Apresentar os dados de um aluno
// Parametros: Um aluno
// Retorno: nenhum
void apresentaAluno(Aluno aluno)
{
    printf("Nome: %s\n", aluno.nome);
    printf("Matricula: %d\n", aluno.matricula);
    printf("CPF: %s\n", aluno.cpf);
    printf("Idade: %d\nSexo: %s\n", aluno.idade, (aluno.sexo=='M') ? "MASCULINO" : "FEMININO");
    printf("Data de Ingresso: %02d/%02d/%04d", aluno.dataIngresso.dia, aluno.dataIngresso.mes, aluno.dataIngresso.ano);
}

//***********************************************************************************************************************
//  Objetivo: Validar um cpf
//  Parametros: Cpf a ser validado
//  Retorno: 1 - Cpf e valido, 0 - Cpf e invalido
int validaCPF(const char *cpf)
{
    char *cpfsInvalidos[] = {"11111111111",
                        "22222222222",
                        "33333333333",
                        "44444444444",
                        "55555555555",
                        "66666666666",
                        "77777777777",
                        "88888888888",
                        "99999999999"};
    int flag = 1, soma, contador, auxDig, digVeri[2], digitos[11];
    
    if(strlen(cpf) != 11)
        return 0;
    
    for(contador=0;contador<9;contador++)
    {
        if(strcmp(cpf, cpfsInvalidos[contador])==0)
        {
            flag = 0;
            break;
        }
    }
    
    if(!flag)
        return 0;
    
    for(contador=0;contador<12;contador++)
    {
        digitos[contador] = cpf[contador] - '0';
    }
    
    // Obtem primeiro digito de verificacao
    auxDig = 10;
    soma = 0;
    for(contador=0;contador<9;contador++, auxDig--)
    {
        soma += digitos[contador] * auxDig;
    }
    
    digVeri[0] = soma % 11;
    digVeri[0] = digVeri[0] < 2 ? 0 : 11 - digVeri[0];
    
    // Obtem segundo digito de verificacao
    auxDig = 11;
    soma = 0;
    
    for(contador=0;contador<10;contador++, auxDig--)
    {
        soma += digitos[contador] * auxDig;
    }
    
    digVeri[1] = soma % 11;
    digVeri[1] = digVeri[1] < 2 ? 0 : 11 - digVeri[1];
    
    // Verifica se os digitos correspondem
    if(digVeri[0] != digitos[9] || digVeri[1] != digitos[10])
        flag = 0;
    
    return flag;
}

//***********************************************************************************************************************
//  Objetivo: Verificar se o cpf de um aluno ja esta cadastrado
//  Parametros: Referencia ao cpf a ser buscado
//  Retorno: 1 - O cpf existe, 0 - O cpf nao existe
int verificaCPFAluno(const char *cpf)
{
    FILE *arq;
    Aluno aluno;
    int flag = 0;
    if((arq = fopen(ARQ_ALUNOS, "rb")) != NULL)
    {
        while(!feof(arq))
        {
            if(fread(&aluno, sizeof(Aluno), 1, arq))
            {
                if(stricmp(aluno.cpf, cpf) == 0)
                {
                    flag = 1;
                    break;
                }
            }
        }
        fclose(arq);
    }
    return flag;
}
