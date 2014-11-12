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
//  Retorno: Nenhum
int leDadosAluno(Aluno *aluno)
{
    int cpfExiste, cpfValida, flagMatricula;
    leValidaTexto(aluno->nome, "Informe o nome do aluno", "Nome do aluno", 3, TAM_NOME_ALUNO);
    do
    {
        aluno->matricula = leValidaInteiro("Informe a matricula do aluno", "Matricula", MATRICULA_MIN, MATRICULA_MAX);
        flagMatricula = pesquisaAlunoMatricula(aluno->matricula);
        if(flagMatricula)
        {
            printf("A matricula %d ja esta cadastrada!\nPressione M para voltar ao menu!", aluno->matricula);
            if(toupper(getch()) == 'M')
                return 0;
            clrscr();
        }
    }
    while(flagMatricula);
    
    do
    {
        leValidaTexto(aluno->cpf, "Informe o cpf do aluno", "CPF", TAM_CPF-1, TAM_CPF);
        cpfValida = validaCPF(aluno->cpf);
        cpfExiste = verificaCPFAluno(aluno->cpf);
        if(!cpfValida)
            printf("O CPF %s e invalido!\n", aluno->cpf);
        else if(cpfExiste)
            printf("O CPF %s ja esta cadastrado!\n", aluno->cpf);

        if(!cpfValida || cpfExiste)
        {
            printf("Pressione M para voltar ao menu!");
            if(toupper(getch()) == 'M')
                return 0;
            clrscr();
        }
    }
    while(cpfExiste == 1 || cpfValida == 0);
    
    aluno->idade = leValidaInteiro("Informe a idade do aluno", "Idade", MIN_IDADE, MAX_IDADE);
    aluno->sexo = leValidaChar("Informe o sexo do aluno: ", "MF");
    geraDataIngresso(&(aluno->dataIngresso));

    
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
            apresentaAluno(aluno, 1, 1);
            confirmacao = confirmaEscolha(40, 12, "Realmente deseja excluir?");
            limpaJanela(1, 1, 25, 80, PRETO);
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
// Objetivo: Permitir que o usario altere os dados de um aluno
// Parametros: Referencia ao aluno a ser alterado
// Retorno: 1 se as alteracoes devem ser salvas e 0 se nao devem
int alteraDadosAluno(Aluno *aluno)
{
    int opcao = 1, subOpcao, flag, flagSelecao, selecao, aux, val, ultimaSelecao;
    char *campoLido, tecla;
    char *opcoesAlteracao[] = {"Alterar Nome",
                               "Alterar Idade",
                               "Alterar Sexo",
                               "Salvar Mudancas",
                               "Cancelar Mudancas"};
    char *sexos[] = {"MASCULINO", "FEMININO"};

    int pos [6][2] = {4,5, 4,8, 4,11, 4,14, 31,8, 33, 11};
    do
    {
        apresentaAluno(*aluno, 5, 5);
        //opcao = menuVertical("O que deseja fazer?", opcoesAlteracao, 5, BRANCO, AZUL_C, 1, 55, 18, opcao, PRETO, CINZA_E);
        flagSelecao = 0;
        selecao = 0;
        gotoxy(4,5);
        printf("/");
        do
        {
            do
            {
                tecla = toupper(getch());
                if(tecla == 72 || tecla == 75 || tecla == 77 || tecla == 80 || tecla == 27 || tecla == 13) // Verifica se a tecla pressionada e relevante (72 - cima, 75 - esquerda, 77 - direita, 80 - baixo)
                    val = 1;                                                                               // 27 - esc, 13 - enter
                else
                    val = 0;
            }
            while(!val); // Repete ate que uma tecla valida seja pressionada
            
            ultimaSelecao = selecao; // Guarda a ultima selecao antes de muda-la
            if(tecla == 72 || tecla == 75)
                selecao--;
            else if(tecla == 77 || tecla == 80)
                selecao++;
            else if(tecla == 27)
                ultimaSelecao = -1; // O usuario pressionou esc, ou seja nao selecionou nada
            
            if(selecao <= -1)
                selecao = (6)-1;  // Se for menor vai para o ultimo item
            else if(selecao >= (6))
                selecao = 0;   // Se for maior vai para o primeiro item

            gotoxy(pos[ultimaSelecao][0], pos[ultimaSelecao][1]);            // a ultima
            printf("%c", ' ');       // opcao

            if(tecla != 13 && tecla != 27) // Se o usuario pressionou algo diferente de enter ou esc, fazer a mudanca necessaria
            {
                gotoxy(pos[selecao][0], pos[selecao][1]);                           // a posicao
                printf("%c", '/');             // atual
                
                fflush(stdin); // Limpa o buffer do teclado
            }
        }
        while(tecla != 13 && tecla != 27); 

        if(tecla == 13)
            opcao = selecao+1;
        else
            opcao = 0;

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
                        gotoxy(13, 5);
                        textcolor(VERMELHO);
                        printf("Nome invalido!");
                        textcolor(BRANCO);
                        getch();
                    }
                    free(campoLido);
                }
                while(!flag);

                break;
            case 3:
                do
                {
                    limpaJanela(11, 13, 11, 18, PRETO);
                    gotoxy(13, 11);
                    campoLido = leStringEmCampo(5);
                    aux = atoi(campoLido);
                    free(campoLido);
                }
                while(aux < 15 || aux > 150);
                aluno->idade = aux;
                
                break;
            case 6:
                do
                {
                    limpaJanela(10, 43, 15, 55, PRETO);
                    subOpcao = menuVertical("", sexos, 2, BRANCO, AZUL_C, 1, 45, 11, 1, PRETO, CINZA_C);
                }
                while(subOpcao == 0);
                
                aluno->sexo = subOpcao == 1 ? 'M' : 'F';

                break;
        }
    }
    while(opcao != 0);
        
    limpaJanela(5-1, 5, (5-1)+11, 5+TAM_NOME_ALUNO+8, PRETO);
    
    return opcao == 4 ? 1 : 0;
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
    printf("%-*.*s\n", tamAluno-1, tamAluno-1, strlen(aluno.nome) ? aluno.nome : "[Ex. Joao da Silva]");

    desenhaMoldura(linha+2, coluna+6, linha+4, coluna+11+TAM_CPF, PRETO, BRANCO);
    gotoxy(coluna, linha+3);
    printf("CPF:");
    gotoxy(coluna+8, linha+3);
    if(strlen(aluno.cpf))
        sprintf(cpfFormatado, "%3.3s.%3.3s.%3.3s-%2.2s", aluno.cpf, aluno.cpf+3, aluno.cpf+6, aluno.cpf+9);
    else
        sprintf(cpfFormatado, "NUM.ERO.CPF-NU");
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
    printf("%-*.*s\n", 10, 10, (aluno.sexo=='M') ? "MASCULINO" : "FEMININO");

    desenhaMoldura(linha+8, coluna+18, linha+10, coluna+34, PRETO, BRANCO);
    gotoxy(coluna, linha+9);
    printf("Data de Ingresso:");
    gotoxy(coluna+21, linha+9);
    printf("%02d/%02d/%04d", aluno.dataIngresso.dia, aluno.dataIngresso.mes, aluno.dataIngresso.ano);

    // gotoxy(1,1);
    // printf("Nome: %-*.*s\n", TAM_NOME_ALUNO, TAM_NOME_ALUNO, strlen(aluno.nome) ? aluno.nome : "[Ex. Joao da Silva]");
    
    // printf("Matricula: ");
    // if(aluno.matricula)
    //     printf("%06d\n", aluno.matricula);
    // else
    //     printf("%-*.*s\n", 10, 10, "[Ex. 010]");

    // printf("CPF: ");
    // if(strlen(aluno.cpf))
    //     printf("%-*.*s\n", TAM_CPF-1, TAM_CPF-1, aluno.cpf);
    // else
    //     printf("%-*.*s\n", 20, 20, "[Ex. 14851693729]");

    // printf("Idade: ");
    // if(aluno.idade)
    //     printf("%d\n", aluno.idade);
    // else
    //     printf("%-*.*s\n", 10, 10, "[Ex. 23]");

    // printf("Sexo: ");
    // if(aluno.sexo)
    //     printf("%-*.*s\n", 10, 10, (aluno.sexo=='M') ? "MASCULINO" : "FEMININO");
    // else
    //     printf("%-*.*s\n", 15, 15, "[Ex. MASCULINO]");

    // printf("Data de Ingresso: %02d/%02d/%04d", aluno.dataIngresso.dia, aluno.dataIngresso.mes, aluno.dataIngresso.ano);
}

//***********************************************************************************************************************
// Objetivo: Apresentar alunos matriculados em um periodo informado
// Parametros: Nenhum
// Retorno: Nenhum
void apresentaAlunosMatriculadosEmPeriodo(void)
{
    FILE *arq;
    Data dataInicial, dataFinal;
    Aluno *alunos = NULL, *alunosAux, aluno;
    int flagData, flagErro = 0, qtdLidos = 0;

    dataInicial = leValidaData("Informe a data inicial no padrao DD/MM/AAAA");

    do
    {
        dataFinal = leValidaData("Informe data final no padrao DD/MM/AAAA");
        flagData = comparaDatas(dataInicial, dataFinal);
        if(flagData>0)
            apresentaMensagem("A data inicial nao pode ser maior que a final!");
    }
    while(flagData>0);

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

