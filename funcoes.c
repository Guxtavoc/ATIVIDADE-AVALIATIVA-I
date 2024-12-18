#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"
#include <string.h>
int incremento(int quantidade, int n){//Implementada, porém não sei se é necessaria...
    switch (n){
    case 3://Caso para incrmentar a quantidade ativa
        quantidade++;
        break;
    }
    return quantidade;
}
void cadastro(dados **aluno,int *quant){
    *quant=incremento(*quant,3);//Incrementa a quantidade
    *aluno=realloc(*aluno,(size_t)(*quant)*sizeof(dados));//Cogitar trocar por realloc ou calloc
    printf("Entre com o nome do aluno: ");
    scanf("%14s",(*aluno)[*quant-1].nome);
    printf("Entre com o Sobrenome do aluno: ");
    scanf("%19s",(*aluno)[*quant-1].sNome);
    strcpy((*aluno)[*quant-1].nomeC,(*aluno)[*quant-1].nome);//Copiando o 1º nome para a variavel
    strcat((*aluno)[*quant-1].nomeC," ");//Adicionando um espaço para evitar comportamentos inesperados durante a ordenação
    strcat((*aluno)[*quant-1].nomeC,(*aluno)[*quant-1].sNome);//Concatenando o sobrenome ao 1º nome
    //Criar menu/função para adicionar os cursos e atrelar seus valores?
    printf("Entre com o nome do curso: ");
    scanf("%19s",(*aluno)[*quant-1].curso);
    printf("Entre com o valor do curso: ");
    scanf("%f",&(*aluno)[*quant-1].valor);
    (*aluno)[*quant-1].mat=*quant+99;//Define matrícula
}

//Criar menu/função para adicionar os cursos e atrelar seus valores?

void imprime(dados *aluno,int n){//Função temporaria...
    printf("Quantidade cadastrada = %d\n",n);//DEBUG, verificador da quantidade
    for(int i=0;i<n;i++){
            printf("Nome: %s ",aluno[i].nomeC);
            printf("Sobrenome: %s ",aluno[i].sNome);
            printf("Curso: %s ",aluno[i].curso);
            printf("Valor: %.2f ",aluno[i].valor);
            printf("Matricula: %d \n",aluno[i].mat);
        }
}
void busca(dados *aluno,int n){//Falta implementar
    int op,tMat,encontrado,x;
    char tNome[15];
    do{
        encontrado=0;
        printf("Selecione o tipo de termo que deseja utilizar para a Busca\n1 - Nome\n2 - Matricula\n");
        printf("0 - Retornar ao menu principal\n");
        scanf("%d",&op);
        switch (op){
        case 1:
        printf("Digite o nome do aluno para a busca: ");
        scanf("%s",tNome);
        x=BuscaBNome(aluno,n,tNome);
        if(x>=0){
            printf("Matricula: %d ",aluno[x-100].mat);
            printf("Nome: %s ",aluno[x-100].nome);
            printf("%s ",aluno[x-100].sNome);
            printf("Curso: %s ",aluno[x-100].curso);
            printf("Mensalidade: R$%.2f\n",aluno[x-100].valor);
            encontrado=1;
            break;
            }
            break;
        case 2:
        printf("Digite a matricula para busca: ");
        scanf("%d",&tMat);
        x=BuscaBMat(tMat,aluno,n);
        if(x>=0){
            printf("Matricula: %d ",aluno[x].mat);
            printf("Nome: %s ",aluno[x].nome);
            printf("%s ",aluno[x].sNome);
            printf("Curso: %s ",aluno[x].curso);
            printf("Mensalidade: R$%.2f\n",aluno[x].valor);
            encontrado=1;
            break;
            }
            break;
        case 0:
        printf("Voltando ao menu principal...");
            break;        
        default:
            break;
        }
        if(encontrado==0)
            printf("informacao nao localizada!\nPor favor tente novamente\n");
    }while(op!=0);
}
int BuscaBMat(int x,dados *aluno,int n){//Codigo de busca binaria do Slago
	int i,f,m;
	i=0;
	f=n-1;
	while(i<=f){
		m=(i+f)/2;
		if(x==aluno[m].mat) 
            return m;
		if(x<aluno[m].mat) 
            f=m-1;
		else i=m+1;
	}
	return -1;
}
int BuscaBNome(dados *aluno, int n, char *nome){//COMPLETA, EU ACHO
    int i,j,x=0;
    dados *copia=malloc((size_t)n *sizeof(dados));//considerar utilizar size_t
    dados iguais[n];
    //printf("Ate aqui funciona\n");
    for(int b=0;b<n;b++)//copiando o vetor para evitar perca de dados
        copia[b]=aluno[b];
    for(i=1;i<n;i++) {//Algoritmo de ordenação bubble sort (Slago) para ordem alfabetica
        for(j=0;j<n-i;j++){
            if(strcasecmp(copia[j].nomeC,copia[j+1].nomeC)>0){
                dados temp=copia[j];
                copia[j]=copia[j+1];
                copia[j+1]=temp;
            }
        }
    }
    int ini=0,fim=n-1,meio;
    while(ini<=fim){//Algoritmo de busca binaria (Internet)
        meio=(ini+fim)/2;
        int cmp=strcasecmp(nome,copia[meio].nome);
        if(cmp==0){//fazer captar mais de um igual, mas como?
            iguais[x]=copia[meio];
            x++;
            continue;
        }
        if(cmp<0){
            fim=meio-1;
        }else{
            ini=meio+1;
        }
    }
    if(x==1){
        free(copia);
        return iguais[0].mat;
    }else if(x==0){
        free(copia);
        return -1;
    }else{
        printf("Mais de um aluno identificado com esse nome!\n");
        for(int a=0;a<x;a++)
            printf("Sobrenome: %s - Matricula: %d\n",iguais[a].sNome,iguais[a].mat);
        printf("Digite a matricula correspondente: ");
        int tmat;
        scanf("%d",&tmat);
        for(int b=0;b<x;b++){
            if(tmat==iguais[b].mat){
                free(copia);
                return tmat;
            }  
        }
        printf("Matricula digitada invalida, tente novamente!\n");
    }
    free(copia);
    return -1;
}
void relatorio_mensalidade(dados *aluno,int n){
    int op,i,j;
    dados *copia=malloc((size_t)n*sizeof(dados));
    for(int a=0;a<n;a++)
        copia[a]=aluno[a];
    do{
    printf("1 - Ordem crescente\n2 - Ordem Decrescente\n0 - Retornar ao menu anterior\n");
    printf("Digite a opcao que deseja: ");
    scanf("%d",&op);
    switch (op){
    case 1:
	for(i=1; i<n; i++)
		for(j=0; j<n-i; j++)
			if(copia[j].valor>copia[j+1].valor ) {
				dados x = copia[j];
				copia[j] = copia[j+1];
				copia[j+1] = x;
			}
            op=0;
        break;
    case 2:
    for(i=1; i<n; i++)
		for(j=0; j<n-i; j++)
			if(copia[j].valor<copia[j+1].valor ) {
				dados x = copia[j];
				copia[j] = copia[j+1];
				copia[j+1] = x;
			}
            op=0;
        break;
    case 0:
        printf("Retornando ao menu anterior!\n");
        break;
    default:
        printf("Opcao invalida!, tente novamente\n");
        break;
    }
    }while(op!=0);
    printf("Imprimindo relatorio\n");
    for(int a=0;a<n;a++)
        printf("Nome Completo: %s, Curso: %s, Mensalidade: %f\n",copia[a].nomeC,copia[a].curso,copia[a].valor);
    free(copia);
}
void troca(dados *a, dados *b) {
    dados temp = *a;
    *a = *b;
    *b = temp;
}
int particiona(dados alunos[], int baixo, int alto) {
    char pivo[15];
    strcpy(pivo, alunos[alto].nome); // Escolhe o nome do último aluno como pivô
    int i = baixo - 1;

    for (int j = baixo; j < alto; j++) {
        if (strcmp(alunos[j].nome, pivo) < 0) { // Comparação alfabética
            i++;
            troca(&alunos[i], &alunos[j]);
        }
    }
    troca(&alunos[i + 1], &alunos[alto]);
    return i + 1;
}
void quicksort(dados alunos[], int baixo, int alto) {//Codigo do quick sort pegado da internet
    if (baixo < alto) {
        int pi = particiona(alunos, baixo, alto);
        quicksort(alunos, baixo, pi - 1);
        quicksort(alunos, pi + 1, alto);
    }
}
void imprimeRelatorio(dados *aluno,int quant){
    printf("Imprimindo relatorio\n");
    for(int a=0;a<quant;a++)
        printf("Nome Completo: %s, Curso: %s, Mensalidade: %f\n",aluno[a].nomeC,aluno[a].curso,aluno[a].valor);
}