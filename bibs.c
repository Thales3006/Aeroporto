#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MIN 60

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
void add_aviao(aviao** a, int codigo, char modelo[], char destino[], int distancia, int tempo_de_voo, float velocidade, int x, int y, int z, int estado, int direcao);
void del_aviao(aviao** a, int pos);
void del_all_aviao(aviao** a);
void del_all_pista(pista** a);
void imprime_aviao(aviao* a);
int tamanho_aviao(aviao* a);
int tamanho_pista(pista* a);
int tamanho_in_pista(pista* a);
aviao* info_Pista(pista* a, int posP, int posA);
aviao* info(aviao* a, int pos);

void pistas(pista** a,int n);
void decolar(pista** aeroporto, aviao** ceu, int pista);
void aterrissando(aviao **a, aviao** pousados, int ciclos);
void iniciasimulacao(pista** aeroporto, aviao** ceu, aviao** pousados, int ciclos);
void aviao_move(aviao* ceu);
void fim(pista **aeroporto,aviao **voando,aviao** pousados);

void add_to_log(FILE* log,aviao* a);
void registrar(aviao **pousados);

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
    add_aviao(&((*a)->head), codigo, modelo, destino, distancia, tempo_de_voo, velocidade, 0, 0, 0, estado, direcao);
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

void add_aviao(aviao** a, int codigo, char modelo[], char destino[], int distancia, int tempo_de_voo, float velocidade, int x, int y, int z, int estado, int direcao){
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

        novo->codigo=codigo;
        strcpy(novo->modelo, modelo);
        strcpy(novo->destino, destino);
        novo->distancia=distancia;
        novo->tempo_de_voo=tempo_de_voo;
        novo->velocidade=velocidade;
        novo->x=x;
        novo->y=y;
        novo->z=z;
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
        printf("%f ",a->velocidade);
        printf("%f ",a->x);
        printf("%f ",a->y);
        printf("%f ",a->z);

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

    a->x += a->velocidade/MIN * cos((a->direcao*M_PI)/180);
    a->y += a->velocidade/MIN * sin((a->direcao*M_PI)/180);
    a->z += a->velocidade/MIN * 0.2;

    add_aviao(ceu, a->codigo, a->modelo, a->destino, a->distancia, a->tempo_de_voo, a->velocidade, a->x, a->y, a->z, a->estado,a->direcao);
    
    rem_from_pista(aeroporto, pista);
}

void aterrissando(aviao **a, aviao** pousados, int ciclos){
    int pos;
    float dist;
    aviao* ceu;

    for(pos=0; pos < tamanho_aviao(*a); pos++){
        ceu = info(*a, pos);
        dist = sqrt( pow(ceu->x, 2) + pow(ceu->y, 2) );

        if( dist >= ceu->distancia ){   // ceu->tempo_de_voo * (ceu->velocidade/MIN)
            ceu->estado=3;
            add_aviao(pousados, ceu->codigo, ceu->modelo, ceu->destino, ceu->distancia, ceu->tempo_de_voo, ceu->velocidade, ceu->x, ceu->y, ceu->z, ceu->estado, ciclos+1);
            del_aviao(a, pos);

            pos--;
            continue;
        }

        if( dist >= ceu->distancia * 0.9 ){ //se tiver mais que 90% do percurso percorrido
            ceu->velocidade *= 0.95;
            ceu->z *= 0.9;
        }
    }
}

void iniciasimulacao(pista** aeroporto, aviao** ceu, aviao** pousados, int ciclos){
    int i;
    for(i=0; i < ciclos; i++){
        aviao_move(*ceu);
        aterrissando(ceu,pousados,i);
    }
    registrar(pousados);
}

void aviao_move(aviao* ceu){
    int pos;
    aviao* avi;

    for(pos=0; pos < tamanho_aviao(ceu) ;pos++){
        avi = info(ceu, pos);

        if( avi->velocidade <= 600 ){
            avi->velocidade += 60;
        }

        avi->x += avi->velocidade/MIN * cos((avi->direcao*M_PI)/180);
        avi->y += avi->velocidade/MIN * sin((avi->direcao*M_PI)/180);

        if(avi->z < 9){
            avi->z += avi->velocidade/MIN * 0.3;
        }
    }   
}

void aviao_move(aviao* ceu){
    int pos;
    aviao* avi;

    for(pos=0; pos < tamanho_aviao(ceu) ;pos++){
        avi = info(ceu, pos);

        if( avi->velocidade <= 600 ){
            avi->velocidade += 60;
        }

        avi->x += avi->velocidade/MIN * cos((avi->direcao*M_PI)/180);
        avi->y += avi->velocidade/MIN * sin((avi->direcao*M_PI)/180);

        if(avi->z < 9){
            avi->z += avi->velocidade/MIN * 0.3;
        }
    }   
}

void fim(pista **aeroporto,aviao **voando,aviao** pousados){

    del_all_pista(aeroporto);
    del_all_aviao(voando);

}

void add_to_log(FILE* log,aviao* a){
    fprintf(log,"%d ",a->codigo);
    fprintf(log,"%s ",a->modelo);
    fprintf(log,"%s ",a->destino);
    fprintf(log,"%d ",a->distancia);
    fprintf(log,"%d ",a->tempo_de_voo);
    fprintf(log,"%f ",a->velocidade);
    fprintf(log,"%f ",a->x);
    fprintf(log,"%f ",a->y);
    fprintf(log,"%f ",a->z);
    fprintf(log,"%d ",a->estado);
    fprintf(log,"%d\n",a->direcao);

}

void registrar(aviao **pousados){
    FILE* log = fopen("log.txt","w");
    int pos;
    aviao* avi;

    fprintf(log," ");
    log = fopen("log.txt","a");

    fprintf(log," Chegaram antes do Tempo:\n");
    for(pos=0; pos < tamanho_aviao(*pousados); pos++){
        avi = info(*pousados,pos);
        if(avi->direcao < avi->tempo_de_voo){
           add_to_log(log,avi); 
        }   
    }
    fprintf(log,"\nChegaram Depois do Tempo:\n");
    for(pos=0; pos < tamanho_aviao(*pousados); pos++){
        avi = info(*pousados,pos);
        if(avi->direcao > avi->tempo_de_voo){
           add_to_log(log,avi); 
        }   
    }
    fprintf(log,"\nTodos os aviões que pousaram:\n");
    for(pos=0; pos < tamanho_aviao(*pousados); pos++){
        avi = info(*pousados,pos);
        add_to_log(log,avi); 
    }

}
