// Funcoes relacionadas aos dados de alunos

#include <stdio.h>
#include <conio.h>
#include <time.h>
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
    memset(&aluno, 0, sizeof(Aluno));
    geraDataIngresso(&aluno.dataIngresso);
    if(leDadosAluno(&aluno))
    {
        if(gravaDadoArquivo(ARQ_ALUNOS, (void *) &aluno, sizeof(Aluno)))
            apresentaMensagem("O aluno foi salvo com sucesso!");
        else
            apresentaMensagem("O aluno nao pode ser salvo!");
    }
    else
        apresentaMensagem("O aluno nao foi cadastrado!");
}

//***********************************************************************************************************************
//  Objetivo: Ler os dados de um aluno
//  Parametros: Referencia ao aluno
//  Retorno: 1 se leu com sucesso, e 0 se nao leu os dados
int leDadosAluno(Aluno *aluno)
{
    int opcao = 0, subOpcao, flagTudoLido = 0, flag, flagSelecao, selecao, matricula, ultimaSelecao, idade;
    int cpfExiste, cpfValida, flagMatricula;
    int pos [7][2] = {4,5, 4,8, 4,11, 31,8, 33,11, 5+15-1,5+12, 5+30-1,5+12};
    char *campoLido, tecla;
    char *opcoesAlteracao[] = {"Alterar Nome",
                               "Alterar Idade",
                               "Alterar Sexo",
                               "Salvar Mudancas",
                               "Cancelar Mudancas"};
    char *sexos[] = {"MASCULINO", "FEMININO"};
    
    do
    {
        apresentaAluno(*aluno, 5, 5);
        
        gotoxy(5+15, 5+12);
        printf("Salvar");
        
        gotoxy(5+30, 5+12);
        printf("Cancelar");
        
        opcao = simulaMenu(pos, 7, opcao+1);

        switch(opcao)
        {
            case 1:
                do
                {
                    limpaJanela(5, 13, 5, 63, PRETO);
                    gotoxy(13, 5);
                    campoLido = leStringEmCampo(50);
                    if(campoLido != NULL && strlen(campoLido) >= 3)
                    {
                        flag = 1;
                        strcpy(aluno->nome, campoLido);
                    }
                    else
                    {
                        flag = 0;
                        apresentaErroCampo(5, 13, 63, "Nome invalido!");
                    }
                    free(campoLido);
                }
                while(!flag);

                break;
            case 2:
                do
                {
                    limpaJanela(8, 13, 8, 27, PRETO);
                    gotoxy(13, 8);
                    campoLido = leStringEmCampo(11);
                    if(campoLido != NULL)
                    {
                        cpfValida = validaCPF(campoLido);
                        cpfExiste = verificaCPFAluno(campoLido);
                        if(cpfValida == 1 && cpfExiste == 0)
                        {
                            flag = 1;
                            strcpy(aluno->cpf, campoLido);
                        }
                        else
                            flag = 0;
                    }
                    else
                        flag = 0;
                    
                    if(!flag)
                    {
                        if(cpfValida == 0)
                        {
                            if(toupper(apresentaErroCampo(8, 13, 27, "CPF nao existe"))==27)
                                flag = 1;
                        }
                        else if(cpfExiste == 1)
                        {
                            if(toupper(apresentaErroCampo(8, 13, 27, "CPF cadastrado"))==27)
                                flag = 1;
                        }
                        else
                            apresentaErroCampo(8, 13, 27, "Insira novamente");
                    }
                    free(campoLido);
                }
                while(!flag);
                
                break;
            case 3:
                do
                {
                    limpaJanela(11, 13, 11, 20, PRETO);
                    gotoxy(13, 11);
                    campoLido = leStringEmCampo(5);
                    idade = atoi(campoLido);
                    if(idade < MIN_IDADE || idade > MAX_IDADE)
                        apresentaErroCampo(11, 13, 20, "!");
                    free(campoLido);
                }
                while(idade < 15 || idade > 150);
                aluno->idade = idade;
                
                break;
            
            case 4:
                do
                {
                    limpaJanela(8, 45, 8, 63, PRETO);
                    gotoxy(45, 8);
                    campoLido = leStringEmCampo(6);
                    matricula = atoi(campoLido);
                    free(campoLido);
                    gotoxy(45, 8);
                    if(matricula < MATRICULA_MIN || matricula > MATRICULA_MAX)
                    {
                        flag = 1;
                        apresentaErroCampo(8, 45, 63, "Matricula Positiva!");
                    }
                    else
                    {
                        flag = pesquisaAlunoMatricula(matricula);
                        if(flag)
                            apresentaErroCampo(8, 45, 63, "Ja cadastrada");
                    }
                }
                while(flag);
                aluno->matricula = matricula;
                
                break;
            case 5:
                do
                {
                    limpaJanela(10, 43, 15, 55, PRETO);
                    subOpcao = menuVertical("", sexos, 2, BRANCO, AZUL_C, 1, 45, 11, 1, PRETO, CINZA_C);
                }
                while(subOpcao == 0);
                
                aluno->sexo = subOpcao == 1 ? 'M' : 'F';

                break;
        }
        
        if(strlen(aluno->nome) >= 3 && strlen(aluno->cpf) == 11 && aluno->idade >= 15 && aluno->matricula > 0 && aluno->sexo != 0)
            flagTudoLido = 1;
            
        limpaJanela(5-1, 5-2, (5)+12, 5+TAM_NOME_ALUNO+8, PRETO);
        
        if(opcao == 6 && !flagTudoLido)
        {
            apresentaMensagem("Voce deve preencher todos os campos!");
            opcao = 1;
        }
        
        if(opcao == 0 || opcao == 7)
            if(confirmaEscolha(40, 12, "Deseja cancelar?") == 0)
                opcao = 1;
    }
    while(opcao != 0 && opcao != 6 && opcao != 7);
        
    limpaJanela(5-1, 5-1, (5)+12, 5+TAM_NOME_ALUNO+8, PRETO);
    
    return opcao == 6 ? 1 : 0;
    
    return 1;
}

//***********************************************************************************************************************
// Objetivo: Recuperar um aluno de um arquivo, deixar o usuario alterar seus dados, e confirmar se as mudancas devem ser salvas
// Parametros: nenhum
// Retorno: nenhum
void alteraAluno(void)
{
    Aluno aluno;
    int posAluno = 0, matricula, opcao = 1, confirmacao;
    char *opcoesAlteracao[] = {"Alterar Nome",
                               "Alterar Idade",
                               "Alterar Sexo",
                               "Salvar Mudancas",
                               "Cancelar Mudancas"};
    
    matricula = selecionaAluno();
    
    if(matricula)
        posAluno = pesquisaAlunoMatricula(matricula);
    
    if(posAluno)
    {
        if(obtemDadoArquivo(ARQ_ALUNOS, (void *) &aluno, sizeof(Aluno), posAluno))
        {
            opcao = alteraDadosAluno(&aluno);
            
            if(opcao == 1)
            {
                confirmacao = confirmaEscolha(40, 12, "Deseja salvar as mudancas?");
                if(confirmacao == 1)
                    if(alteraDadoArquivo(ARQ_ALUNOS, (void*) &aluno, sizeof(Aluno), posAluno))
                        apresentaMensagem("O aluno foi alterado com sucesso!");
                    else
                        apresentaMensagem("O aluno nao foi alterado!");
                else
                    apresentaMensagem("O aluno nao foi alterado!");
            }
            else
                apresentaMensagem("O aluno nao foi alterado!");
            limpaJanela(1, 1, 9, 80, PRETO);
        }
        else
            apresentaMensagem("O aluno nao pode ser recuperado do arquivo!");
    }
}

//***********************************************************************************************************************
// Objetivo: Permitir que o usario altere os dados de um aluno
// Parametros: Referencia ao aluno a ser alterado
// Retorno: 1 se as alteracoes devem ser salvas e 0 se nao devem
int alteraDadosAluno(Aluno *aluno)
{
    int opcao = 1, subOpcao, flag, flagSelecao, selecao, idade, val, ultimaSelecao;
    int pos [5][2] = {4,5, 4,11, 33,11, 5+15-1,5+12, 5+30-1,5+12};
    char *campoLido, tecla;
    char *opcoesAlteracao[] = {"Alterar Nome",
                               "Alterar Idade",
                               "Alterar Sexo",
                               "Salvar Mudancas",
                               "Cancelar Mudancas"};
    char *sexos[] = {"MASCULINO", "FEMININO"};
    
    do
    {
        apresentaAluno(*aluno, 5, 5);
        
        gotoxy(5+15, 5+12);
        printf("Salvar");
        
        gotoxy(5+30, 5+12);
        printf("Cancelar");
        
        opcao = simulaMenu(pos, 5, opcao);

        switch(opcao)
        {
            case 1:
                do
                {
                    limpaJanela(5, 13, 5, 63, PRETO);
                    gotoxy(13, 5);
                    campoLido = leStringEmCampo(50);
                    if(campoLido != NULL && strlen(campoLido) >= 3)
                    {
                        flag = 1;
                        strcpy(aluno->nome, campoLido);
                    }
                    else
                    {
                        flag = 0;
                        apresentaErroCampo(5, 13, 63, "Nome invalido!");
                    }
                    free(campoLido);
                }
                while(!flag);

                break;
            case 2:
                do
                {
                    limpaJanela(11, 13, 11, 20, PRETO);
                    gotoxy(13, 11);
                    campoLido = leStringEmCampo(5);
                    idade = atoi(campoLido);
                    if(idade < MIN_IDADE || idade > MAX_IDADE)
                        apresentaErroCampo(11, 13, 20, "!");
                    free(campoLido);
                }
                while(idade < 15 || idade > 150);
                
                aluno->idade = idade;
                
                break;
            case 3:
                do
                {
                    limpaJanela(10, 43, 15, 55, PRETO);
                    subOpcao = menuVertical("", sexos, 2, BRANCO, AZUL_C, 1, 45, 11, 1, PRETO, CINZA_C);
                }
                while(subOpcao == 0);
                
                aluno->sexo = subOpcao == 1 ? 'M' : 'F';

                break;
        }
        if(opcao == 0 || opcao == 5)
        {
            limpaJanela(5-1, 5-2, (5)+12, 5+TAM_NOME_ALUNO+8, PRETO);
            if(confirmaEscolha(40, 12, "Deseja cancelar?") == 0)
                opcao = 1;
        }
    }
    while(opcao != 0 && opcao != 4 && opcao != 5);
        
    limpaJanela(5-1, 5-1, (5)+12, 5+TAM_NOME_ALUNO+8, PRETO);
    
    return opcao == 4 ? 1 : 0;
}

//***********************************************************************************************************************
// Objetivo: Ler o codigo de um aluno, buscar pelo mesmo, e confirmar se o usuario deseja excluir o aluno, caso queira, excluir
// Parametros: Nenhum
// Retorno: Nenhum
void excluiAluno(void)
{
    Aluno aluno;
    int posAluno = 0, matricula, confirmacao;
    
    matricula = selecionaAluno();
    
    if(matricula)
        posAluno = pesquisaAlunoMatricula(matricula);
    
    if(posAluno)
    {
        if(obtemDadoArquivo(ARQ_ALUNOS, (void *) &aluno, sizeof(Aluno), posAluno))
        {
            apresentaAluno(aluno, 5, 5);
            confirmacao = confirmaEscolha(55, 15, "Realmente deseja excluir?");
            limpaJanela(4, 5, 15, 65, PRETO);
            if(confirmacao == 1)
            {
                if(!verificaAlunoCadastrado(matricula))
                    if(excluiDadoArquivo(ARQ_ALUNOS, sizeof(Aluno), posAluno))
                        apresentaMensagem("O aluno foi excluido com sucesso!");
                    else
                        apresentaMensagem("O aluno nao pode ser excluido!");
                else
                    apresentaMensagem("O aluno esta cadastrado em ao menos um curso!");
            }
            else
                apresentaMensagem("Os dados nao foram excluidos!");
        }
        else
            apresentaMensagem("O aluno nao pode ser recuperado!");
    }
}

//*********************************************************************************************************************** 
// Objetivo: Permitir ao usuario selecionar um aluno dentre varios, dependendo de sua escolha 
// Parametros: nenhum 
// Retorno: Matricula do aluno selecionado (0 se nao selecionar ninguem) 
int selecionaAluno(void) 
{ 
    int opcao, matricula = 0; 
    char *opcoesSelecao[] = {"Dentre Todos os Alunos", 
                             "Pesquisar por Nome", 
                             "Voltar"}; 

    opcao = menuVertical("Como deseja selecionar o aluno?", opcoesSelecao, 3, BRANCO, AZUL_C, 1, 20, 5, 1, PRETO, CINZA_C); 
         
    switch(opcao) 
    { 
        case 1: 
            matricula = apresentaTodosAlunos(); 
            break; 
        case 2: 
            matricula = pesquisaApresentaAlunoNome(); 
            break; 
    } 
     
    return matricula; 
} 


//***********************************************************************************************************************
// Objetivo: Pesquisar por um ou mais alunos
// Parametros: nenhum
// Retorno: nenhum
void pesquisaAluno(void)
{
    int opcao = 1;
    char *opcoesPesquisa[] = {"Pesquisa por Matricula",
                              "Pesquisa por Nome",
                              "Voltar"};
    
    do
    {
        opcao = menuVertical("Pesquisa de Aluno", opcoesPesquisa, 3, BRANCO, AZUL_C, 1, 20, 5, opcao, PRETO, CINZA_C);
        
        switch(opcao)
        {
            case 1:
                pesquisaApresentaAlunoMatricula();
                break;
            case 2:
                pesquisaApresentaAlunoNome();
                break;
        }
    }
    while(opcao != 0 && opcao != 3);
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
//  Objetivo: Pesquisar um aluno dentro de um arquivo por nome
//  Parametros: nenhum
//  Retorno: a matricula do aluno escolhido
int pesquisaApresentaAlunoNome(void)
{
    FILE *arq;
    Aluno aluno, *alunos = NULL, *alunosAux;
    int qtdLidos = 0, flag = 0, matriculaEscolhida;
    char copiaNome[TAM_NOME_ALUNO], nomeBusca[TAM_NOME_ALUNO];
    
    leValidaTexto(nomeBusca, "Informe o nome do aluno", "Nome", 1, TAM_NOME_ALUNO);
    
    strToLower(nomeBusca);
    
    if((arq = fopen(ARQ_ALUNOS, "rb")) != NULL)
    {
        while(!feof(arq))
        {
            if(fread(&aluno, sizeof(Aluno), 1, arq))
            {
                strcpy(copiaNome, aluno.nome);
                strToLower(copiaNome);
                if(strstr(copiaNome, nomeBusca))
                {
                    alunosAux = (Aluno *) realloc(alunos, sizeof(Aluno)*(qtdLidos+1));
                    if(alunosAux != NULL)
                    {
                        alunos = alunosAux;
                        alunos[qtdLidos] = aluno;
                        qtdLidos++;
                    }
                    else
                    {
                        apresentaMensagem("Houve erro na alocacao de memoria!");
                        flag = 1;
                        if(qtdLidos)
                            free(alunos);
                        break;
                    }
                }
            }
        }
        fclose(arq);
    }
    
    if(!flag)
    {
        if(qtdLidos)
        {
            matriculaEscolhida = apresentaDadosAlunos(alunos, qtdLidos);
            free(alunos);
        }
        else
            apresentaMensagem("Nao houve nenhuma correspondencia!");
    }
    
    return matriculaEscolhida;
}

//***********************************************************************************************************************
// Objetivo: Pesquisar um aluno por matricula e apresentar
// Parametros: nenhum
// Retorno: nenhum
void pesquisaApresentaAlunoMatricula(void)
{
    FILE *arq;
    Aluno aluno;
    int matricula, posAluno;
    
    matricula = leValidaInteiro("Informe a matricula a pesquisar", "Matricula", MATRICULA_MIN, MATRICULA_MAX);
    
    posAluno = pesquisaAlunoMatricula(matricula);
    
    if(obtemDadoArquivo(ARQ_ALUNOS, (void *) &aluno, sizeof(Aluno), posAluno))
    {
        apresentaAluno(aluno, 5, 5);
        getch();
        limpaJanela(5-1, 5, (5-1)+11, 5+TAM_NOME_ALUNO+8, PRETO);
    }
    else
        apresentaMensagem("O aluno nao foi encontrado!");
}

//***********************************************************************************************************************
// Objetivo: Apresentar os dados de um aluno
// Parametros: Um aluno
// Retorno: nenhum
void apresentaAluno(Aluno aluno, int linha, int coluna)
{
    int tamAluno = 51;
    char cpfFormatado[15];
    char *titulos[] = {"Nome", "CPF", "Matricula", "Idade", "Sexo", "Data de Ingresso"};

    desenhaMoldura(linha-1, coluna+6, linha+1, coluna+8+tamAluno, PRETO, BRANCO);
    gotoxy(coluna, linha);
    printf("Nome:");
    gotoxy(coluna+8, linha);
    printf("%-*.*s\n", tamAluno-1, tamAluno-1, strlen(aluno.nome) ? aluno.nome : "[Ex. Jose da Silva]");

    desenhaMoldura(linha+2, coluna+6, linha+4, coluna+11+TAM_CPF, PRETO, BRANCO);
    gotoxy(coluna, linha+3);
    printf("CPF:");
    gotoxy(coluna+8, linha+3);
    if(strlen(aluno.cpf))
        sprintf(cpfFormatado, "%3.3s.%3.3s.%3.3s-%2.2s", aluno.cpf, aluno.cpf+3, aluno.cpf+6, aluno.cpf+9);
    else
        sprintf(cpfFormatado, "NUMEROCPFNU");
    printf("%-*.*s", TAM_CPF+2, TAM_CPF+2, cpfFormatado);

    desenhaMoldura(linha+2, coluna+26+TAM_CPF, linha+4, coluna+8+tamAluno, PRETO, BRANCO);
    gotoxy(coluna+15+TAM_CPF, linha+3);
    printf("Matricula:");
    gotoxy(coluna+28+TAM_CPF, linha+3);
    if(aluno.matricula)
        printf("%06d\n", aluno.matricula);
    else
        printf("%-*.*s\n", 10, 10, "[Ex. 010]");

    desenhaMoldura(linha+5, coluna+6, linha+7, coluna+17, PRETO, BRANCO);
    gotoxy(coluna, linha+6);
    printf("Idade:");
    gotoxy(coluna+8, linha+6);
    if(aluno.idade)
        printf("%-8d\n", aluno.idade);
    else
        printf("%*.*s\n", 8, 8, "[Ex. 23]");

    desenhaMoldura(linha+5, coluna+26+TAM_CPF, linha+7, coluna-1+tamAluno, PRETO, BRANCO);
    gotoxy(coluna+29, linha+6);
    printf("Sexo:");
    gotoxy(coluna+28+TAM_CPF, linha+6);
    printf("%-*.*s\n", 10, 10, (aluno.sexo=='M') ? "MASCULINO" : (aluno.sexo=='F' ? "FEMININO" : "SEXO"));

    desenhaMoldura(linha+8, coluna+18, linha+10, coluna+34, PRETO, BRANCO);
    gotoxy(coluna, linha+9);
    printf("Data de Ingresso:");
    gotoxy(coluna+21, linha+9);
    printf("%02d/%02d/%04d", aluno.dataIngresso.dia, aluno.dataIngresso.mes, aluno.dataIngresso.ano);
}

//***********************************************************************************************************************
// Objetivo: Apresentar alunos matriculados em um periodo informado
// Parametros: Nenhum
// Retorno: Nenhum
void apresentaAlunosMatriculadosEmPeriodo(void)
{
    FILE *arq;
    Data dataInicial, dataFinal, bucket;
    Aluno *alunos = NULL, *alunosAux, aluno;
    int flagData, flagErro = 0, qtdLidos = 0;

    dataInicial = leValidaData("Informe a data inicial no padrao DD/MM/AAAA");
    dataFinal = leValidaData("Informe data final no padrao DD/MM/AAAA");
    
    if(comparaDatas(dataInicial, dataFinal) > 0)
    {
        bucket = dataInicial;
        dataInicial = dataFinal;
        dataFinal = bucket;
    }

    if((arq = fopen(ARQ_ALUNOS, "rb")) != NULL)
    {
        while(!feof(arq))
        {
            if(fread(&aluno, sizeof(Aluno), 1, arq))
            {
                if(comparaDatas(aluno.dataIngresso, dataInicial) >= 0 && comparaDatas(aluno.dataIngresso, dataFinal) <= 0)
                {
                    alunosAux = (Aluno *) realloc(alunos, sizeof(Aluno)*(qtdLidos+1));
                    if(alunosAux != NULL)
                    {
                        alunos = alunosAux;
                        alunos[qtdLidos] = aluno;
                        qtdLidos++;
                    }
                    else
                    {
                        apresentaMensagem("Houve erro na alocacao de memoria!");
                        flagErro = 1;
                        if(qtdLidos)
                            free(alunos);
                        break;
                    }
                }
            }
        }
        fclose(arq);
    }

    if(!flagErro)
    {
        if(qtdLidos)
        {
            apresentaDadosAlunos(alunos, qtdLidos);
            free(alunos);
        }
        else
            apresentaMensagem("Nao houve nenhuma correspondencia!");
    }
}

//***********************************************************************************************************************
// Objetivo: Apresentar todos os alunos
// Parametros: Nenhum
// Retorno: Matricula do aluno selecionado
int apresentaTodosAlunos(void)
{
    Aluno *alunos;
    int qtdAlunos = 0, matriculaSelecionada = 0;
    
    if((alunos = (Aluno *) obtemDadosArquivo(ARQ_ALUNOS, sizeof(Aluno), &qtdAlunos)) != NULL)
    {
        matriculaSelecionada = apresentaDadosAlunos(alunos, qtdAlunos);
        free(alunos);
    }
    
    return matriculaSelecionada;
}

//***********************************************************************************************************************
// Objetivo: Apresentar os alunos fornecidos
// Parametros: Ponteiro para alunos (ja alocados), quantidade de alunos
// Retorno: Matricula do aluno selecionado (0 se nenhum foi selecionado)   (NAO DESALOCA MEMORIA)
int apresentaDadosAlunos(Aluno *alunos, int qtdAlunos)
{
    int selecao, qtdItens, contador, qtdLinhasAlocada = 0, flag = 0;
    int matriculaSelecao = 0;
    char ** linhasTabela, matriculaTexto[7], titulo[TAM_TEXTO_TABELA+1];
    if(qtdAlunos > 0)
    {
        qsort(alunos, qtdAlunos, sizeof(Aluno), comparaAlunos);
        
        linhasTabela = (char**) malloc(sizeof(char*) * qtdAlunos);
        
        if(linhasTabela != NULL)
        {
            for(contador=0;contador<qtdAlunos;contador++)
            {
                linhasTabela[contador] = (char*) malloc(sizeof(char)*(TAM_TEXTO_TABELA+1));
                if(linhasTabela[contador] != NULL)
                {
                    sprintf(linhasTabela[contador], "%06d %-24.22s%5d %-10s%3.3s.%3.3s.%3.3s-%2.2s     %02d/%02d/%04d", alunos[contador].matricula, alunos[contador].nome, alunos[contador].idade,
                            alunos[contador].sexo == 'M' ? "MASCULINO" : "FEMININO", alunos[contador].cpf, alunos[contador].cpf+3, alunos[contador].cpf+6, alunos[contador].cpf+9, 
                            alunos[contador].dataIngresso.dia, alunos[contador].dataIngresso.mes, alunos[contador].dataIngresso.ano);
                    qtdLinhasAlocada++;
                }
                else
                {
                    flag = 1;
                    apresentaMensagem("A memoria para uma das linhas da tabela nao pode ser alocada");
                    break;
                }
            }
        }
        else
        {
            flag = 1;
            apresentaMensagem("A memoria para tabela nao pode ser alocada!");
        }
        
        if(!flag)
        {
            sprintf(titulo, "%-6s %-24.22s%-5.5s %-10s%-19s%-12s", "Matr.", "Nome", "Idade", "Sexo", "CPF", "D. Ingresso");

            for(contador=0;contador<qtdAlunos;contador+=LINHAS_TABELA)
            {
                qtdItens = qtdAlunos - contador > LINHAS_TABELA ? LINHAS_TABELA : qtdAlunos - contador;
                
                if(contador+LINHAS_TABELA<qtdAlunos)
                {
                    gotoxy(45, LINHA_TABELA_ALUNOS+qtdItens+3);
                    printf("Pressione Esc para ver o restante!");
                }

                selecao = menuVertical(titulo, &linhasTabela[contador], qtdItens, BRANCO, AZUL_C, 1, COLUNA_TABELA_ALUNOS, LINHA_TABELA_ALUNOS, 1, PRETO, CINZA_C);
                
                limpaJanela(LINHA_TABELA_ALUNOS+qtdItens+3, 45, LINHA_TABELA_ALUNOS+qtdItens+3, 80, PRETO);
                
                if(selecao != 0)
                {
                    strncpy(matriculaTexto, linhasTabela[contador+selecao-1], 6);
                    matriculaTexto[6] = '\0';
                    matriculaSelecao = atoi(matriculaTexto);
                    break;
                }
                else if(contador+LINHAS_TABELA<qtdAlunos)
                {
                    if(!confirmaEscolha(40, 12, "Deseja ver o restante dos alunos?"))
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
    
    return matriculaSelecao;
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
                             "99999999999",
                             "00000000000"};
                        
    int flag = 1, soma, contador, auxDig, digVeri[2], digitos[11];
    
    if(strlen(cpf) != 11)
        return 0;
    
    for(contador=0;contador<10;contador++)
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

//***********************************************************************************************************************
// Objetivo: Compara dois alunos (por nome)
// Parametros: Ponteiro para os dois alunos
// Retorno: resultado da comparacao dos dois nomes(inteiro)
int comparaAlunos(const void *p1, const void *p2)
{
    Aluno *aluno1, *aluno2;
    aluno1 = (Aluno *) p1;
    aluno2 = (Aluno *) p2;
    return stricmp(aluno1->nome, aluno2->nome);
}

//***********************************************************************************************************************
// Objetivo: Registra a data atual
// Parametros: Referencia a uma estrutura de data para guardar a data atual
// Retorno: nenhum
void geraDataIngresso(Data *data)
{
    time_t tempoBruto;
    struct tm *tempoAtual;
    time(&tempoBruto);
    tempoAtual = localtime(&tempoBruto);
    data->dia = tempoAtual->tm_mday;
    data->mes = tempoAtual->tm_mon+1;
    data->ano = tempoAtual->tm_year+1900;
}

