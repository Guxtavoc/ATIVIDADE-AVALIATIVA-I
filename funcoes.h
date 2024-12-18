typedef struct{
    int mat;
    char nome[15], sNome[20], curso[20],nomeC[36];
    float valor;
}dados;
typedef struct{
    char nome[20];
    float valor;
}curso;
//se 1 quantidade ativa, se 2 quantidade de cursos, 3 quantidade total
int incremento(int quantidade,int n);
void cadastro(dados **aluno,int *quant);
void busca(dados *aluno,int n);
void imprime(dados *aluno,int quant);
int BuscaBMat(int x, dados *aluno, int n);
int BuscaBNome(dados *aluno, int n,char *nome);
void relatorio_mensalidade(dados *aluno,int n);
//void relatorio_curso(dados *aluno,int n);
void troca(dados *a, dados *b);
int particiona(dados alunos[], int baixo, int alto);
void quicksort(dados alunos[], int baixo, int alto);
void imprimeRelatorio(dados *aluno,int quant); 