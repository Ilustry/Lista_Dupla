#include <stdio.h>
#include <stdlib.h>

struct Fila{
    int num;
    struct Fila *ant, *prox;
};
struct L1{
    int A;
    struct L1 *ant, *prox;
};
struct L2{
    int B;
    struct L2 *ant, *prox;
};
struct L3{
    int C;
    struct L3 *ant, *prox;
};
struct Fila *Inicio;
struct L1 *Inicio_L1;
struct L2 *Inicio_L2;
struct L3 *Inicio_L3;

void Enfileirar(int num){
    struct Fila *Novo, *Item;

    Novo = malloc(sizeof(struct Fila));
    Novo->num = num;
    Novo->ant = NULL;
    Novo->prox = NULL;

    if(Inicio == NULL){
        Inicio = Novo;
    }
    else{
        Item = Inicio;
        while(Item->prox != NULL){
            Item = Item->prox;
        }
        Novo->ant = Item;
        Item->prox = Novo;
    }
}

int Desenfileirar(){
    if(Inicio == NULL)
        return -1;

    int Elemento;
    Elemento = Inicio->num;

    if(Inicio->prox == NULL){
        Inicio = NULL;
        free(Inicio);
    }
    else{
        Inicio = Inicio->prox;
        Inicio->ant = NULL;
        free(Inicio->ant);
    }

    return Elemento;
}

int Verificar(int num){
    struct L1 *Item_L1 = Inicio_L1;
    struct L2 *Item_L2 = Inicio_L2;
    int retorno = 0;

    if(Item_L1 == NULL){

    }
    else{
        while(Item_L1->prox != NULL && Item_L1->A != num){
            Item_L1 = Item_L1->prox;
        }
        if(Item_L1->A == num)
            retorno += 1;
    }

    if(Item_L2 == NULL){

    }
    else{
        while(Item_L2->prox != NULL && Item_L2->B != num){
            Item_L2 = Item_L2->prox;
        }
        if(Item_L2->B == num)
            retorno += 2;
    }

    return retorno;
}

int inserirL1(int num){

    if(Verificar(num) == 1 || Verificar(num) == 3){
        return 0;
    }
    if(num < 0){
        return 1;
    }

    struct L1 *Novo, *Item;

    Novo = malloc(sizeof(struct L1));
    Novo->A = num;
    Novo->prox = NULL;

    if(Inicio_L1 == NULL){
        Novo->ant = NULL;
        Inicio_L1 = Novo;
    }
    else{
        Item = Inicio_L1;
        while(Item->prox != NULL){
            Item = Item->prox;
        }
        Novo->ant = Item;
        Item->prox = Novo;
    }

    return 0;
}

int inserirL2(int num){

    if(Verificar(num) == 2 || Verificar(num) == 3){
        return 0;
    }
    if(num < 0){
        return 1;
    }

    struct L2 *Novo, *Item;

    Novo = malloc(sizeof(struct L2));
    Novo->B = num;
    Novo->prox = NULL;

    if(Inicio_L2 == NULL){
        Novo->ant = NULL;
        Inicio_L2 = Novo;
    }
    else{
        Item = Inicio_L2;
        while(Item->prox != NULL){
            Item = Item->prox;
        }
        Novo->ant = Item;
        Item->prox = Novo;
    }

    return 0;
}

void unirListas(){
    struct L3 *Item_L3, *Novo;

    if(Inicio_L1 == NULL){

    }
    else{
        struct L1 *Item_L1 = Inicio_L1;
        Novo = malloc(sizeof(struct L3));
        Novo->C = Item_L1->A;
        Novo->ant = NULL;
        Novo->prox = NULL;
        Inicio_L3 = Novo;
        Item_L3 = Inicio_L3;
        while(Item_L1->prox != NULL){
            Novo = malloc(sizeof(struct L3));
            Item_L1 = Item_L1->prox;
            Novo->C = Item_L1->A;
            Novo->ant = Item_L3;
            Novo->prox = NULL;
            Item_L3->prox = Novo;
            Item_L3 = Item_L3->prox;
        }

    }

    if(Inicio_L2 == NULL){

    }
    else{
        struct L2 *Item_L2 = Inicio_L2;
        if(Inicio_L1 == NULL){
            Novo = malloc(sizeof(struct L3));
            Novo->C = Item_L2->B;
            Novo->ant = NULL;
            Novo->prox = NULL;
            Inicio_L3 = Novo;
            Item_L3 = Inicio_L3;
            Item_L2 = Item_L2->prox;
        }
        while(Item_L2 != NULL){
            if(Verificar(Item_L2->B) == 2){
                Novo = malloc(sizeof(struct L3));
                Novo->C = Item_L2->B;
                Novo->ant = Item_L3;
                Novo->prox = NULL;
                Item_L3->prox = Novo;
                Item_L3 = Item_L3->prox;
            }
            Item_L2 = Item_L2->prox;
        }
    }

}

int excluirEmOrdem(){
    if(Inicio_L3 == NULL)
        return -1;
    struct L3 *Item;
    int retorno = 0;

    Item = Inicio_L3;
    retorno = Item->C;
    while(Item->prox != NULL){
        Item = Item->prox;
        if(retorno > Item->C)
            retorno = Item->C;
    }
    Item = Inicio_L3;
    while(Item->C != retorno){
        Item = Item->prox;
    }
    if(Item == Inicio_L3 && Item->prox != NULL ){
        Inicio_L3 = Inicio_L3->prox;
        Inicio_L3->ant = NULL;
        free(Inicio_L3->ant);
    }
    else if(Item == Inicio_L3 && Item->prox == NULL){
        Inicio_L3 = NULL;
        free(Inicio_L3);
    }
    else if(Item->prox == NULL && Item != Inicio_L3){
        Item->ant->prox = NULL;
        Item = NULL;
        free(Item);
    }
    else{
        Item->ant->prox = Item->prox;
        Item->prox->ant = Item->ant;
        free(Item);
    }

    return retorno;
}

int geraFila(){
    int retorno = 1;

    if(Inicio_L3 == NULL){

    }
    else{
        do{
            retorno = excluirEmOrdem();
            if(retorno != -1)
                Enfileirar(retorno);

        }while(retorno != -1);
        retorno = 0;
    }
    return retorno;
}

void Imprimir(){
    if(Inicio == NULL)
        return;
    struct Fila *Item = Inicio;

    printf("Elementos do conjunto C:\n");
    while(Item != NULL){
        printf("%d | ", Item->num);
        Item = Item->prox;
    }
}


int main()
{
    int opc, x;

    do{
        printf("//////////////////////////////\n");
        printf("/'          'MENU'          '/\n");
        printf("/'--------------------------'/\n");
        printf("/'1.Inserir na lista        '/\n");
        printf("/'2.Gerar conjunto C        '/\n");
        printf("/'3.Enfileirar conjunto C   '/\n");
        printf("/'4.Retirar/exibir elementos'/\n");
        printf("//////////////////////////////\n");

        scanf("%d", &opc);
        switch(opc){
            case 1:
                do{
                printf("\n1.Inserir no conjunto A\n");
                printf("2.Inserir no conjunto B\n");
                scanf("%d", &opc);
                if(opc != 1 && opc != 2){

                }
                else{
                printf("Informe o elemento a ser inserido.");
                scanf("%d", &x);
                }
                if(opc == 1){
                    inserirL1(x);
                }
                else{
                    inserirL2(x);
                }
                }while(opc != 1 && opc != 2);
                break;
            case 2:
                if(Inicio_L1 != NULL || Inicio_L2 != NULL){
                    unirListas();
                    printf("Conjunto C gerado com sucesso.\n");
                }
                else
                    printf("Listas vazias.\n");
                break;
            case 3:
                x = geraFila();
                if(x == 0)
                    printf("Fila gerada.\n");
                else if(x == 1)
                    printf("Conjunto C vazio.\n");
                break;
            case 4:
                x = 1;
                int y = 0;
                float media = 0;
                opc = -1;
                if(Inicio == NULL){
                    printf("\nFila vazia.\n");
                }
                else if(Inicio != NULL){
                    printf("\n");
                    Imprimir();
                    printf("\n\n");
                    while(y != -1){
                        y = Desenfileirar();
                        x += y;
                        opc += 1;
                    }
                    media = (float)x/opc;
                    printf("Media: %.2f\n", media);
                }
                opc = 4;
                break;

        }

        printf("\n\n\n");
    }while(opc != 0);

  return 0;
}
