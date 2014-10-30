// FunÃƒÂ§ÃƒÂµes relacionadas aos dados de alunos

#include <stdio.h>
#include "dados.h"

//***********************************************************************************************************************
//  Objetivo: Ler os dados de um aluno
//  ParÃƒÂ¢metros: ReferÃƒÂªncia ao aluno
//  Retorno: Nenhum
void leDadosAluno(Aluno *aluno)
{
    int cpfExiste, cpfValida, flagMatricula;
    leValidaTexto(aluno->nome, "Informe o nome do aluno", "Nome do aluno", 3, TAM_NOME_ALUNO);
    do
    {
        aluno->matricula = leValidaInteiro("Informe a matricula do aluno", "Matricula", MATRICULA_MIN, MATRICULA_MAX);
        flagMatricula = pesquisaAlunoMatricula(aluno->matricula, 0);
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
// ParÃƒÂ¢metros: ReferÃƒÂªncia ao aluno
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
// ParÃƒÂ¢metros: Nenhum
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
                sprintf(dataIngresso, "%2d/%2d/%4d", aluno.dataIngresso.dia, aluno.dataIngresso.mes, aluno.dataIngresso.ano);
                
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
//  ParÃƒÂ¢metros: Matricula do aluno a ser alterado
//  Retorno: nenhum
void alteraDadosAluno(int matricula)
{
    FILE *arq;
    int posAluno;
    char opcao;
    Aluno aluno;
    
    posAluno = pesquisaAlunoMatricula(matricula, 1);
    if(posAluno)
    {
        if((arq = fopen(ARQ_ALUNOS, "rb+")) != NULL )
        {
            if(!fseek(arq, sizeof(Aluno)*(posAluno-1), 0))
            {
                if(fread(&aluno, sizeof(Aluno), 1, arq))
                {
                    opcao = leValidaChar("\n\nO que deseja alterar?\n1 - Nome\n2 - Idade\n3 - Sexo\n0 - Sair", "1230");
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
                    if(opcao!='0')
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
                {
                    clrscr();
                    printf("O aluno nao pode ser lido para ser alterado!");
                }
            }
            else
            {
                clrscr();
                printf("O aluno nao pode ser lido para ser alterado!");
            }
            fclose(arq);
        }
        else
        {
            clrscr();
            printf("O arquivo nao pode ser aberto para ser alterado!");
        }
    }
}

//***********************************************************************************************************************
//  Objetivo: Excluir um aluno
//  ParÃ¢metros: Matricula do aluno a ser excluido
//  Retorno: nenhum
void excluiDadosAluno(int matricula)
{
    FILE *arq, *arqTemp;
    int posAluno, qtdCopiados = 0;
    char opcao;
    Aluno aluno;
    
    posAluno = pesquisaAlunoMatricula(matricula, 1);
    if(posAluno)
    {
        opcao = leValidaChar("\n\nTem certeza de que deseja excluir este aluno? (S/N) ", "SN");
        if(opcao=='S')
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
                        {
                            printf("O aluno foi excluido com sucesso!");
                        }
                        else
                        {
                            clrscr();
                            printf("O novo arquivo nao pode ser renomeado, todos os dados foram perdidos!");
                        }
                    }
                    else
                    {
                        clrscr();
                        printf("O arquivo antigo nao pode ser excluido, logo o aluno nao foi excluido!");
                    }
                    
                }
                else
                {
                    clrscr();
                    printf("O arquivo para exclusao nao pode ser criado!");
                }
            }
            else
            {
                clrscr();
                printf("O arquivo nao pode ser aberto para remover o aluno!");
            }
        }
        else
        {
            clrscr();
            printf("Os dados do aluno nao foram excluidos!");
        }
    }
}

//***********************************************************************************************************************
//  Objetivo: Pesquisar um aluno dentro de um arquivo por matricula
//  ParÃƒÂ¢metros: matricula a ser pesquisada, indicador se o dado encontrado deve ser escrito (nÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â£o zero para sim)
//  Retorno: numero positivo se encontrado (posicao do aluno no arquivo de 1 a n, sendo n o numero de alunos), 0 - codigo nao encontrado
int pesquisaAlunoMatricula(int matriculaBusca, int indPrint)
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
                    if(indPrint)
                    {
                        printf("Nome: %s\n", aluno.nome);
                        printf("Matricula: %d\n", aluno.matricula);
                        printf("CPF: %s\n", aluno.cpf);
                        printf("Idade: %d\nSexo: %s\n", aluno.idade, (aluno.sexo=='M') ? "MASCULINO" : "FEMININO");
                        printf("Data de Ingresso: %2d/%2d/%4d", aluno.dataIngresso.dia, aluno.dataIngresso.mes, aluno.dataIngresso.ano);
                    }
                    flag = 1;
                    break;
                }
            }
        }
        fclose(arq);
    }
    if(indPrint && !flag)
        printf("O aluno nao foi encontrado!");
    if(!flag)
        pos = 0;
    return pos;
}

//***********************************************************************************************************************
//  Objetivo: Validar um cpf
//  ParÃƒÂ¢metros: Cpf a ser validado
//  Retorno: 1 - Cpf ÃƒÂ© valido, 0 - Cpf ÃƒÂ© invalido
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
//  Objetivo: Verificar se o cpf de um aluno jÃƒÂ¡ esta cadastrado
//  ParÃƒÂ¢metros: ReferÃƒÂªncia ao cpf a ser buscado
//  Retorno: 1 - O cpf existe, 0 - O cpf nÃƒÂ£o existe
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
