#include <stdio.h>
#include "funcoes.h"
void menu_relatorios(dados *aluno,int quant){
    int op;
    do{
    printf("1 - Valor das mensalidades\n2 - Pelo nome do curso\n");
    printf("0 - Retornar ao menu principal\nEscolha como deseja que os dados sejam organizados: ");
    scanf("%d",&op);
    switch (op){
    case 1:
        relatorio_mensalidade(aluno,quant);
        break;
    case 2:
        quicksort(aluno, 0, quant - 1);
        imprimeRelatorio(aluno,quant);
        break;
    case 0:
        printf("Retornando ao menu princial...\n");
        break;
    default:
        printf("Opcao invalidada, tente novamente\n");
        break;
    }
    }while(op!=0);
}
void menu1(dados *aluno,int quant){
    int op;
    printf("Ola servidor, Bem vindo ao SIGEFA (sistema de gerenciamento estudantil da Faculdade Aurora)!");
    do{
        printf("\n1 - Cadastro de estudantes\n2 - Busca de estudantes\n3 - Relatorio de estudantes\n4 - Consultar/Cadastrar cursos\n");
        printf("0 - Fechar o SIGEFA\nDigite a opcao que deseja: ");
        scanf("%d",&op);
        printf("\n");
        switch (op){
        case 0:
            printf("Encerrando a aplicacao...\n\n");
            break;
        case 1:
            printf("Abrindo menu de cadastro...\n");
            cadastro(&aluno,&quant);
            break;        
        case 2:
            printf("Abrindo menu de busca...\n");
            busca(aluno,quant);
            break;        
        case 3:
            printf("Abrindo menu de relatorios...\n");
            menu_relatorios(aluno,quant);
            //imprime(aluno,quant);
            break;
        case 4:
            break;
        default:
        printf("Opcao invalida! Tente novamente.\n");
            break;
        }
    }while(op!=0);
}