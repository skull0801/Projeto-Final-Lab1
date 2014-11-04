// Funcoes relacionadas aos dados de alunos

#include <stdio.h>
#include "dados.h"
#include "cores.h"
#include "funcoesBasicas.h"
#include "funcoesAluno.h"

//***********************************************************************************************************************
// Objetivo: Cadastrar aluno
// Parametros: nenhum
// Retorno: nenhum
void cadastraAluno(void)
{
    Aluno aluno;
    leDadosAluno(&aluno);
    gravaDadosAluno(&aluno);
}

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
// Objetivo: Apresentar todos os alunos de um arquivo em forma de menu
// Parametros: Nenhum
// Retorno: Matricula do aluno selecionado (0 se nenhum foi selecionado)
int apresentaDadosAlunos(void)
{
    Aluno *alunos;
    int qtdAlunos, selecao, qtdItens, contador, qtdLinhasAlocada = 0, flag = 0;
    int matriculaSelecao = 0;
    char ** linhasTabela, matriculaTexto[7];
    
    if((alunos = obtemDadosAlunosArquivo(&qtdAlunos)) != NULL)
    {
        if(qtdAlunos != 0)
        {
            
            ordenaAlunosPorNome(alunos, qtdAlunos);
            
            linhasTabela = (char**) malloc(sizeof(char*) * qtdAlunos);
            if(linhasTabela != NULL)
            {
                for(contador=0;contador<qtdAlunos;contador++)
                {
                    linhasTabela[contador] = (char*) malloc(sizeof(char)*(TAM_TEXTO_TABELA));
                    if(linhasTabela[contador] != NULL)
                    {
                        sprintf(linhasTabela[contador], "%06d - %-25.20s - %12s", alunos[contador].matricula, alunos[contador].nome, alunos[contador].cpf);
                        qtdLinhasAlocada++;
                    }
                    else
                    {
                        flag = 1;
                        printf("A memoria para uma das linhas nao pode ser alocada");
                        break;
                    }
                }
            }
            else
            {
                flag = 1;
                printf("A memoria para tabela nao pode ser alocada!");
            }
            
            free(alunos);
            
            if(!flag)
            {
                for(contador=0;contador<qtdAlunos;contador+=10)
                {
                    qtdItens = qtdAlunos - contador > 10 ? 10 : qtdAlunos - contador;
                    
                    selecao = menuVertical(&linhasTabela[contador], qtdItens, BRANCO, AZUL_C, 1, 10, 5, 1, PRETO, CINZA_C);
                    
                    if(selecao != 0)
                    {
                        strncpy(matriculaTexto, linhasTabela[contador+selecao-1], 6);
                        matriculaTexto[6] = '\0';
                        matriculaSelecao = atoi(matriculaTexto);
                        break;
                    }
                    else if(contador+10<qtdAlunos)
                    {
                        if(confirmaEscolha(20, 5))
                            break;
                    }
                }
            }
            
            if(linhasTabela != NULL)
            {
                for(contador=0;contador<qtdLinhasAlocada;contador++)
                    free(linhasTabela[contador]);
                free(linhasTabela);
            }
        }
        else
        {
            printf("Nao existem alunos cadastrados!");
            getch();
        }
    }
    return matriculaSelecao;
}

//***********************************************************************************************************************
// Objetivo: Ordenar os alunos de um vetor por nome
// Parametros: Referencia ao vetor de alunos, e quantidade de alunos
// Retorno: nenhum
void ordenaAlunosPorNome(Aluno *alunos, int qtdAlunos)
{
    Aluno alunoAux;
    int contador, auxiliar;
    for(auxiliar = 0; auxiliar < qtdAlunos-1; auxiliar++)
    {
        for(contador = auxiliar+1; contador < qtdAlunos; contador++)
        {
            if(stricmp(alunos[auxiliar].nome, alunos[contador].nome) > 0)
            {
                alunoAux = alunos[auxiliar];
                alunos[auxiliar] = alunos[contador];
                alunos[contador] = alunoAux;
            }
        }
    }
}

//***********************************************************************************************************************
// Objetivo: Obter todos os alunos do arquivo
// Parametros: Referencia a quantidade de alunos (valor sera dado pela funcao)
// Retorno: Ponteiro para memoria alocada na qual os alunos estao
Aluno * obtemDadosAlunosArquivo(int * qtdAlunos)
{
    FILE *arq;
    Aluno *alunos = NULL;
    
    if((arq = fopen(ARQ_ALUNOS, "rb")) != NULL)
    {
        if(!fseek(arq, 0, SEEK_END))
        {
            *qtdAlunos = (ftell(arq)/sizeof(Aluno));
            
            alunos = malloc(sizeof(Aluno)*(*qtdAlunos));
            
            if(alunos != NULL)
            {
                rewind(arq);
                if(fread(alunos, sizeof(Aluno), *qtdAlunos, arq) != *qtdAlunos)
                {
                    printf("Erro ao recuperar os dados de alunos!");
                    free(alunos);
                    alunos = NULL;
                }
            }
            else
                printf("Erro ao alocar memoria para alunos!");
        }
        else
            printf("Erro ao obter quantidade de alunos.");
            
        fclose(arq);
    }
    else
        printf("Erro ao abrir o arquivo de alunos.");
        
    return alunos;
}

//***********************************************************************************************************************
// Objetivo: Recuperar um aluno de um arquivo, deixar o usuario alterar seus dados, e confirmar se as mudanÃ§as devem ser salvas
// ParÃ¢metros: nenhum
// Retorno: nenhum
void alteraAluno(void)
{
    FILE *arq;
    int posAluno, matricula;
    int opcao, confirmacao;
    char *opcoesAlteracao[] = {"Alterar Nome",
                               "Alterar Idade",
                               "Alterar Sexo",
                               "Salvar Mudancas",
                               "Cancelar Mudancas"};
    Aluno aluno;
    
    matricula = apresentaDadosAlunos();
    
    posAluno = pesquisaAlunoMatricula(matricula);
    
    gotoxy(1,1);
    
    if(posAluno)
    {
        if((arq = fopen(ARQ_ALUNOS, "rb")) != NULL)
        {
            if(!fseek(arq, sizeof(Aluno)*(posAluno-1), 0))
            {
                if(fread(&aluno, sizeof(Aluno), 1, arq))
                {
                    do
                    {
                        apresentaAluno(aluno);
                        opcao = menuVertical(opcoesAlteracao, 5, BRANCO, AZUL_C, 1, 55, 1, 1, PRETO, CINZA_E);
                        gotoxy(1, 8);
                        switch(opcao)
                        {
                            case 1:
                                leValidaTexto(aluno.nome, "Informe o novo nome", "Nome", 3, TAM_NOME_ALUNO);
                                break;
                            case 2:
                                aluno.idade = leValidaInteiro("Informe a nova idade", "Idade", MIN_IDADE, MAX_IDADE);
                                break;
                            case 3:
                                aluno.sexo = leValidaChar("Informe o novo sexo (M/F): ", "MF");
                                break;
                        }
                    }
                    while(opcao != 0 && opcao != 4 && opcao != 5);
                    
                    if(opcao == 4)
                    {
                        confirmacao = confirmaEscolha(55, 1);
                        clrscr();
                        if(confirmacao == 1)
                        {
                            alteraDadosAluno(aluno, posAluno);
                        }
                        else
                            printf("Os dados nao foram alterados!");
                    }
                    else
                        printf("Os dados nao foram alterados!");
                }
                else
                    printf("Os dados do aluno nao puderam ser lidos!");
            }
            else
                printf("Os dados do aluno nao puderam ser lidos!");
            fclose(arq);
        }
        else
            printf("O aluno nao pode ser recuperado!");
    }
}

//***********************************************************************************************************************
//  Objetivo: Salvar alteracoes nos dados de um aluno
//  Parametros: Dados do aluno, posicao do aluno no arquivo
//  Retorno: nenhum
void alteraDadosAluno(Aluno aluno, int posAluno)
{
    FILE *arq;
    
    if(posAluno)
    {
        if((arq = fopen(ARQ_ALUNOS, "rb+")) != NULL )
        {
            if(!fseek(arq, sizeof(Aluno)*(posAluno-1), 0))
            {
                if(fwrite(&aluno, sizeof(Aluno), 1, arq))
                    printf("Os dados foram alterados com sucesso!");
                else
                    printf("Os dados nao puderam ser alterados!");
            }
            else
                printf("O aluno nao pode ser recuperado!");
                
            fclose(arq);
        }
        else
            printf("O arquivo nao pode ser aberto para ser alterado!");
    }
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
    int confirmacao;
    
    matricula = apresentaDadosAlunos();
    
    posAluno = pesquisaAlunoMatricula(matricula);
    
    gotoxy(1,1);
    
    if(posAluno)
    {
        if((arq = fopen(ARQ_ALUNOS, "rb")) != NULL)
        {
            if(!fseek(arq, sizeof(Aluno)*(posAluno-1), 0))
            {
                if(fread(&aluno, sizeof(Aluno), 1, arq))
                {
                    apresentaAluno(aluno);
                    confirmacao = confirmaEscolha(55, 1);
                    clrscr();
                    if(confirmacao == 1)
                    {
                        if(fclose(arq) == 0)
                        {
                            arq = NULL;
                            excluiDadosAluno(posAluno);
                        }
                        else
                            printf("O arquivo nao pode ser fechado para ser alterado!");
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
}

//***********************************************************************************************************************
//  Objetivo: Excluir um aluno
//  Parametros: Posicao do aluno a ser excluido
//  Retorno: nenhum
void excluiDadosAluno(int posAluno)
{
    FILE *arq, *arqTemp;
    int qtdCopiados = 0;
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
                
                if(!fclose(arqTemp) && !fclose(arq))
                {
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
                    printf("Os arquivos nao puderam ser fechados para alteracao!");
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
}

//***********************************************************************************************************************
// Objetivo: Pesquisar por um ou mais alunos
// Parametros: nenhum
// Retorno: nenhum
void pesquisaAluno(void)
{
    FILE *arq;
    Aluno aluno;
    int matricula, posAluno;
    
    matricula = leValidaInteiro("Informe a matricula do aluno a pesquisar", "Matricula", MATRICULA_MIN, MATRICULA_MAX);
    
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
                }
                else
                    printf("O aluno nao pode ser lido!");
            }
            else
                printf("O aluno nao pode ser recuperado!");
        }
        else
            printf("O arquivo de alunos nao pode ser aberto!");
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
