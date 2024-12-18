#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
int main (){
    int quant=0;
    dados *pessoa=NULL;//criando a variavel como nula para evitar erros de memoria.
    menu1(pessoa,quant);
    free(pessoa);
    return 0;
}