#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct aviao{
    int codigo;
    char modelo[10];
    char destino[10];
    int distancia;
    int tempo_de_voo;
    float x;
    float y;
    float z;
    float velocidade;
    int estado;

    int direcao;
    
    struct aviao* prox;

}aviao;

typedef struct pista{
    aviao *head;
    struct pista* prox;
}pista;

void criar_pista(pista** a);
void add_to_pista(pista** a, int pos, int codigo, char modelo[], char destino[], int distancia, int tempo_de_voo, float velocidade, int estado, int direcao);
void del_pista(pista** a, int pos);
void rem_from_pista(pista** a, int pos);
void imprime_pista(pista* a);
void add_aviao(aviao** a, int codigo, char modelo[], char destino[], int distancia, int tempo_de_voo,float velocidade, int estado, int direcao);
void del_aviao(aviao** a, int pos);
void del_all_aviao(aviao** a);
void del_all_pista(pista** a);
void imprime_aviao(aviao* a);
int tamanho_aviao(aviao* a);
int tamanho_pista(pista* a);
int tamanho_in_pista(pista* a);
aviao* info_Pista(pista* a, int posP, int posA);
aviao* info(aviao* a, int pos);
void aterrissando(aviao **a, int i, int pos);
void tempestade(aviao **ceu);
void turbulencia(aviao **ceu);
void pistas(pista** a,int n);
void decolar(pista** aeroporto, aviao** ceu, int pista);
void fim(pista **aeroporto,aviao **voando);

//*****************************************
void criar_pista(pista** a){
    pista* novo=malloc(sizeof(pista));
	if(!*a){
        *a=novo;
	}
    else{
        while((*a)->prox){
            a=&((*a)->prox);
        }
        (*a)->prox=novo;
    }
    novo->prox=NULL;
    novo->head=NULL;
}

void add_to_pista(pista** a,int pos,int codigo, char modelo[], char destino[], int distancia, int tempo_de_voo, float velocidade, int estado, int direcao){
    if(!(*a))return;
	int i;
		for(i=0;i<pos;i++){//achar pista correta
			a=&((*a)->prox);
			if(!*a)return;
		}
    // adiciona o avião
    add_aviao(&((*a)->head), codigo, modelo, destino, distancia, tempo_de_voo, velocidade, estado, direcao);
}

void del_pista(pista** a,int pos){
    if(!*a||pos<0)return;
    int i;
    pista *aux;

    for(i=0;i<pos;i++){//achar pista correta
        a=&((*a)->prox);
        if(!*a)return;
    }
    aux=*a;

    if(aux->head)return;//se tiver aviões na pista

    *a=aux->prox;//remover elemento
    free(aux);
}

void rem_from_pista(pista** a,int pos){
    if(!*a||pos<0)return;
    int i;

    for(i=0;i<pos;i++){//achar pista correta
        a=&((*a)->prox);
        if(!*a)return;
    }
  
    if(!((*a)->head))return;//verificar se há aviao

    del_aviao(&((*a)->head), 0);
}

void imprime_pista(pista* a){
    printf("\e[1;32mAeroporto:\n");
    if(!a){printf("vazio!\e[0m\n");return;}
    int cont=0;

    while(a){ 
        printf("\e[1;32mPista %d:\n",cont+1);
            imprime_aviao(a->head);
        printf("\n");
        cont++;a=a->prox;
    }
    printf("\e[0m");
}

void add_aviao(aviao** a, int codigo, char modelo[], char destino[], int distancia, int tempo_de_voo, float velocidade, int estado, int direcao){
    aviao *novo = malloc(sizeof(aviao));
	if(!*a){
		*a=novo;
	}
    else {
        while((*a)->prox){
            a=&((*a)->prox);
        }
		(*a)->prox=novo;
    }
        novo->prox=NULL;
		novo->x=0;novo->y=0;novo->z=0;
        novo->codigo=codigo;
        strcpy(novo->modelo, modelo);
        strcpy(novo->destino, destino);
        novo->distancia=distancia;
        novo->tempo_de_voo=tempo_de_voo;
        novo->velocidade=velocidade;
        novo->estado=estado;
        novo->direcao=direcao;
}

void del_aviao(aviao** a, int pos){
    if(!*a||pos<0)return;
    int i;
    aviao* aux;

    for(i=0;i<pos;i++){//achar pista correta
        a=&((*a)->prox);
        if(!*a)return;
    }
    aux=*a;

    *a=aux->prox;//remover elemento
    free(aux);
}

void del_all_aviao(aviao**a){
    if(!*a)return;
    aviao *aux=(*a)->prox,*aux1;
    free(*a);
    *a=NULL;

    while (aux){
        aux1=aux->prox;
        free(aux);
        aux=aux1;
    }
}
void del_all_pista(pista** a){
    if(!*a)return;
    pista *aux=(*a)->prox,*aux1;
    del_all_aviao(&((*a)->head));
    free(*a);
    *a=NULL;

    while (aux){
        aux1=aux->prox;
        del_all_aviao(&(aux->head));
        free(aux);
        aux=aux1;
    }
}

void imprime_aviao(aviao* a){
    printf("\e[1;32m");
    if(!a){printf("vazia!\e[0m\n");return;}
 
    for(;a;){
        printf("%d ",a->codigo);
        printf("%s ",a->modelo);
        printf("%s ",a->destino);
        printf("%d ",a->distancia);
        printf("%d ",a->tempo_de_voo);
        printf("%f ",a->x);
        printf("%f ",a->y);
        printf("%f ",a->z);
        printf("%f ",a->velocidade);
        printf("%d ",a->estado);
        printf("%d \n",a->direcao);

        a=a->prox;
    }
    printf("\e[0m");
    return;
}

int tamanho_aviao(aviao* a){
    int i;
    for(i=0;a;i++){
        a=a->prox;
    }
    return i;
}

int tamanho_pista(pista* a){
    int i;
    for(i=0;a;i++){
        a=a->prox;
    }
    return i;
}
int tamanho_in_pista(pista* a){
    int i;

    for(i=0;a;){
        i+=tamanho_aviao(a->head);
        a=a->prox;
    }
    return i;
}

aviao* info_Pista(pista* a,int posP,int posA){
    if(!a||posP<0||posA<0)return NULL;
    int i;
    for(i=0;i<posP;i++){//achar pista
        a = a->prox;
        if(!a)return NULL;
    }
    return info(a->head,posA);

}

aviao* info(aviao* a,int pos){
    if(!a||pos<0)return NULL;
    int i;
    for(i=0;i<pos;i++){//achar aviao
        a = a->prox;
        if(!a)return NULL;
    }
    return a;
}

void pistas(pista** a,int n){
    int i;
    for(i=0;i<n;i++){
        criar_pista(a);
    }
}

void decolar(pista** aeroporto, aviao** ceu, int pista) {
    srand(time(NULL));

    if (!*aeroporto) { // verifica se há aviões
        printf("Nenhum aviao na pista\n");
        return;
    }
    // Adiciona o avião no céu e remove da pista especificada
    aviao* a = info_Pista(*aeroporto, pista, 0);
    if(!a)return;//caso aviao nao exista

    a->velocidade = 260 + rand() % 60;
    a->estado = 2;
    a->direcao = rand() % 360;
    add_aviao(ceu, a->codigo, a->modelo, a->destino, a->distancia, a->tempo_de_voo, a->velocidade, a->estado,a->direcao);
    rem_from_pista(aeroporto, pista);
}
void aterrissando(aviao **a, int i, int pos){
    int  min,t, d;
    float w, v, z;
    if((!(*a))||((*a)->estado)!=2){ //verifica se o avião esta decolado
        printf("\nNão há avião decolado."); 
        return;//se não há avião no céu, não há avião decolado
    }
    aviao* ceu = info(*a, 0);
    d=((ceu)->distancia)/10; //d receberá a distancia do avião d agora é 10% da distancia
    t=(ceu)->tempo_de_voo;  
        if((i*((ceu)->velocidade))<=((ceu)->distancia -d) && (i*((ceu)->velocidade))){//se a velocidade pelo tempo for igual a 10% da distancia, então          
            ceu->distancia = d;
            w=(float)d*60/(ceu->velocidade);//deslocamento pela velocidade 
            v=ceu->velocidade/w;//velocidade por horas pq o parametro é velocidade por horas
            d=d/w;
            z=ceu->z/w;
            for( min=(int)w; min>=0;min--){
                ceu->velocidade=ceu->velocidade-(int)v;
                ceu->distancia=ceu->distancia-(int)d;
                ceu->z = (ceu->z) -(int)z; 
                if((ceu->distancia)<=100){
                    ceu->estado=3;
                     del_aviao(a, 0);
                    

                }
            }
        }
}

void tempestade(aviao **ceu) {
    if (!*ceu) // Verifica se há aviões no ceu
        return;
    int tam = tamanho_aviao(*ceu); // conta quantos aviões há no ceu
    int sorteado = rand() % tam;
    int tempestade = rand() % 2; // decide se a tempestade sera forte ou fraca
    aviao *afetado = info(*ceu, sorteado);

    // altera a latitude e a velocidade conforme a tempestade
    if (tempestade == 0) {
        printf("Tempestade fraca, avance rapidamente\n");
        afetado->z -= 0.3;
        afetado->velocidade += (afetado->velocidade) * 0.1;
    } else {
        printf("Tempestade forte, diminua a velocidade!\n");
        afetado->z -= 0.3;
        afetado->velocidade -= (afetado->velocidade) * 0.1;
    }
}

void turbulencia(aviao **ceu) {
    if (!*ceu) // Verifica se há aviões no ceu
        return;
    int tam = tamanho_aviao(*ceu); // conta quantos aviões há no ceu
    int sorteado = rand() % tam;
    aviao *afetado = info(*ceu, sorteado);
    printf("Aviao com turbulencia, reduza a velocidade\n");
    afetado->velocidade -=  afetado->velocidade * 0.15; //altera a velocidade
}

void fim(pista **aeroporto,aviao **voando){
    del_all_pista(aeroporto);
    del_all_aviao(voando);

}
