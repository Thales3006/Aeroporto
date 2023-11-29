#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MIN 60
#define ARRAY_SIZE 100

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

//********************************************

int menu(pista** aeroporto, aviao **ceu, aviao **pousados, int ciclos);

void pistas(pista** a,int n);
void decolar(pista** aeroporto, aviao** ceu, int pista);
void aterrissando(aviao **a, aviao** pousados, int ciclos);
void aterrissagem_forcada(aviao **ceu, aviao** pousados, int codigo, int ciclos);
void iniciasimulacao(pista** aeroporto, aviao** ceu, aviao** pousados, int ciclos, int *clima);
void aviao_move(aviao* ceu);
void tempestade(aviao **ceu);
void neblina(aviao **ceu);
void turbulencia(aviao **ceu);
int colisao(aviao* ceu);
int colidiu(aviao* ceu, float x, float y, float z);
void fim(pista **aeroporto,aviao **voando,aviao** pousados);

void add_to_log(FILE* log,aviao* a);
void registrar(pista** aeroporto, aviao **ceu, aviao **pousados, int* contadores);

//*****************************************

int menu(pista** aeroporto, aviao **ceu, aviao **pousados, int ciclos){
    int command;
    int param1, param2, param3, param4;
    char *paramS1 = (char*)malloc(sizeof(char)*ARRAY_SIZE), *paramS2 = (char*)malloc(sizeof(char)*ARRAY_SIZE);
    int verif;
    if(!paramS1||!paramS2){
        printf("Sem memoria o suficiente!");
        exit(1);
    }
        printf("\nCOMANDOS:\n");
        printf("1 - Inserir aviao no aeroporto\n");
        printf("2 - Decolar aviao\n");
        printf("3 - Aterrissagem forcada\n");
        printf("4 - Construir uma pista\n");
        printf("5 - Destruir uma pista\n");
        printf("6 - Continuar\n");
        printf("7 - Finalizar mais cedo\n");
    do{
        scanf("%d",&command);
        setbuf(stdin, NULL);
        if(command<=0||command>7)printf("\nComando invalido!\n");
    }while(command<=0||command>7);

    switch(command){
        case 1:
            do{
                verif = 1;
                printf("Numero da pista para inserir: ");
                    if(!scanf("%d",&param1))verif = 0;
                    setbuf(stdin, NULL);
                printf("Insira as informacoes do aviao:\n");
                printf("Codigo: ");
                    if(!scanf("%d",&param2))verif = 0;
                    setbuf(stdin, NULL);
                printf("Modelo: ");
                    if(!scanf("%s",paramS1))verif = 0;
                    setbuf(stdin, NULL);
                printf("Destino: ");
                    if(!scanf("%s",paramS2))verif = 0;
                    setbuf(stdin, NULL);
                printf("Distancia: ");
                    if(!scanf("%d",&param3))verif = 0;
                    setbuf(stdin, NULL);
                printf("Tempo de voo: ");
                    if(!scanf("%d",&param4))verif = 0;
                    setbuf(stdin, NULL);

                if(!verif || (param1<=0||param1>tamanho_pista(*aeroporto)) || param3 <= 0 || param4 <= 0)printf("\nAlgum valor invalido!\n");
            }while(!verif || (param1<=0||param1>tamanho_pista(*aeroporto)) || param3 <= 0 || param4 <= 0);
            add_to_pista(aeroporto, param1-1, param2, paramS1, paramS2, param3, param4, 0, 1, 0);

            break;
        case 2:
            do{
                verif = 1;
                printf("Numero da pista para decolar: ");
                    if(!scanf("%d",&param1))verif = 0;
                    setbuf(stdin, NULL);
                if(!verif || param1<=0 || param1>tamanho_pista(*aeroporto))printf("\nValor invalido!\n");
            }while(!verif || param1<=0 || param1>tamanho_pista(*aeroporto));
            decolar(aeroporto, ceu, param1 - 1);

            break;
        case 3:
            do{
                verif = 1;
                printf("Codigo do aviao para ser aterrissado: ");
                    if(!scanf("%d",&param1))verif = 0;
                    setbuf(stdin, NULL);
                if(!verif || param1<=0)printf("\nValor invalido!\n");
            }while(!verif || param1<=0);
            aterrissagem_forcada(ceu, pousados, param1, ciclos);
            break;
        case 4: criar_pista(aeroporto);
            break;
        case 5: 
            do{
                verif = 1;
                printf("Numero da pista para deletar: ");
                    if(!scanf("%d",&param1))verif = 0;
                    setbuf(stdin, NULL);
                if(!verif || param1<=0 || param1>tamanho_pista(*aeroporto))printf("\nValor invalido!\n");
            }while(!verif || param1<=0 || param1>tamanho_pista(*aeroporto));
            del_pista(aeroporto,param1-1);

            break;
        case 6: break;

        case 7:
            return 0; 
    }
    return 1;
}

//********************************************************
// FUNÇÕES DE AUXILIO DE CRIAÇÃO E ALTERAÇÃO DE LISTAS ENCADEADAS

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

//******************************************************
// FUNÇÕES REFERENTES AO PROJETO


void pistas(pista** a,int n){
    int i;
    for(i=0;i<n;i++){
        criar_pista(a);
    }
}

void decolar(pista** aeroporto, aviao** ceu, int pista) {
    srand(time(NULL));

    if (!*aeroporto) { // verifica se há aviões
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

void aterrissagem_forcada(aviao **ceu, aviao** pousados, int codigo, int ciclos){
    int pos;
    float dist;
    aviao* avi;

    for(pos=0; pos < tamanho_aviao(*ceu); pos++){
        avi = info(*ceu, pos);

        if( avi->codigo == codigo ){
            avi->estado=3;
            add_aviao(pousados, avi->codigo, avi->modelo, avi->destino, avi->distancia, avi->tempo_de_voo, avi->velocidade, avi->x, avi->y, avi->z, avi->estado, ciclos+1);
            del_aviao(ceu, pos);
            return;
        }
    }
    printf("Nao foi encontrado o aviao com esse codigo!\n");
}

void iniciasimulacao(pista** aeroporto, aviao** ceu, aviao** pousados, int ciclos, int* clima){
    int i;
    int temp = *clima, nebl = *(clima+1),turb = *(clima+2);
    int* contadores = malloc(sizeof(int)*4);

    if(!contadores){
        printf("Sem memoria o suficiente!");
        exit(1);
    }

    *(contadores+0) = 0;
    *(contadores+1) = 0;
    *(contadores+2) = 0;
    *(contadores+3) = 0;

    for(i=0; i < ciclos; i++, temp -= 1, nebl-= 1, turb-= 1){

        if( temp == 0 ){
            tempestade(ceu);
            temp = *clima+1;
            *(contadores+0) += 1;
        }
        if( nebl == 0 ){
            neblina(ceu);
            nebl = *(clima+1)+1;
            *(contadores+1) += 1;
        }
        if( turb == 0 ){
            turbulencia(ceu);
            turb = *(clima+2)+1;
            *(contadores+2) += 1;
        }

        aviao_move(*ceu);
        *(contadores+3) += colisao(*ceu);
        aterrissando(ceu,pousados,i);
        if(!menu(aeroporto, ceu, pousados, i))break;

    }
    registrar(aeroporto, ceu, pousados, contadores);
}

void aviao_move(aviao* ceu){
    if(!ceu)return;
    int pos;
    aviao* avi;

        for(pos=0; pos < tamanho_aviao(ceu) ;pos++){
            avi = info(ceu, pos);

            if( avi->velocidade <= 600 ){
                avi->velocidade += avi->velocidade/(avi->z+3);
            }

            avi->x += avi->velocidade/MIN * cos((avi->direcao*M_PI)/180);
            avi->y += avi->velocidade/MIN * sin((avi->direcao*M_PI)/180);

            if(avi->z < 9){
                avi->z += avi->z/(avi->velocidade-1);
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
        //printf("Tempestade fraca, avance rapidamente\n");
        afetado->z -= 0.3;
        afetado->velocidade += (afetado->velocidade) * 0.1;
    } else {
        //printf("Tempestade forte, diminua a velocidade!\n");
        afetado->z -= 0.3;
        afetado->velocidade -= (afetado->velocidade) * 0.1;
    }
}

void neblina(aviao **ceu){
	if(!*ceu) return;
	int a = tamanho_aviao(*ceu);
	aviao *nebuloso = info(*ceu, rand() % a);

	nebuloso->z = nebuloso->z - 0.5;
	//printf("\nALERTA!!\nHá neblina no céu, a velocidade será reduzida em 5%% permanentemente!\n");
	nebuloso->velocidade = nebuloso->velocidade * 0.95;
	
}

void turbulencia(aviao **ceu) {
    if (!*ceu) // Verifica se há aviões no ceu
        return;
    int tam = tamanho_aviao(*ceu); // conta quantos aviões há no ceu
    int sorteado = rand() % tam;
    aviao *afetado = info(*ceu, sorteado);
    //printf("Aviao com turbulencia, reduza a velocidade\n");
    afetado->velocidade -=  afetado->velocidade * 0.15; //altera a velocidade
    
}

int colisao(aviao* ceu){
    if(!ceu)return 0;
    int pos, contador = 0;
    float vel, x, y, z;
    aviao* avi;

    for(pos=0; pos < tamanho_aviao(ceu) ;pos++){
        avi = info(ceu, pos);
        vel = avi->velocidade;
        x = avi->x,
        y = avi->y,
        z = avi->y;


        if( vel <= 600 ){
            vel += vel/(z+3);
        }

        x += vel/MIN * cos((avi->direcao*M_PI)/180);
        y += vel/MIN * sin((avi->direcao*M_PI)/180);

        if(z < 9){
            z += z/(vel-1);
        }

        if(colidiu(ceu, x, y, z)){
            while(colidiu(ceu, x, y, z)){
                z += vel * 0.05;
                contador++;
                }
            avi->z = z;
        }
    }
    return contador;
}
int colidiu(aviao* ceu, float x, float y, float z){
    int pos;
    aviao* avi;
    for(pos=0; pos < tamanho_aviao(ceu) ;pos++){
        avi = info(ceu, pos);

        if(avi->x==x && avi->y==y && avi->z==z){
            return 1;
        }


    }
    return 0;
}

void fim(pista **aeroporto,aviao **voando,aviao** pousados){

    del_all_pista(aeroporto);
    del_all_aviao(voando);
    del_all_aviao(pousados);

}

void add_to_log(FILE* log,aviao* a){
    fprintf(log,"Código: %d ",a->codigo);
    fprintf(log,"Modelo: %s ",a->modelo);
    fprintf(log,"Destino: %s ",a->destino);
    fprintf(log,"Distância: %d ",a->distancia);
    fprintf(log,"Tempo esperado: %d ",a->tempo_de_voo);
    //fprintf(log,"%f ",a->velocidade);
    //fprintf(log,"%f ",a->x);
    //fprintf(log,"%f ",a->y);
    //fprintf(log,"%f ",a->z);
    //fprintf(log,"%d ",a->estado);
}

void registrar(pista** aeroporto, aviao **ceu, aviao **pousados, int* contadores){
    FILE* log = fopen("log.txt","w");
    int pos, cont = 0, bool=0;
    aviao* avi;
    pista* pis;

    fprintf(log," ");
    log = fopen("log.txt","a");

    fprintf(log," /**********************************************************/\n");
    fprintf(log," /                          LOG                             /\n");
    fprintf(log,"/**********************************************************/\n");

    fprintf(log, "Colisoes Evitadas: %d\n", *(contadores+3));

    fprintf(log,"\nChegaram antes do Tempo:\n");
    for(pos=0; pos < tamanho_aviao(*pousados); pos++){
        avi = info(*pousados,pos);
        if(avi->direcao < avi->tempo_de_voo){
           add_to_log(log,avi);
           fprintf(log,"Tempo Real: %d\n",avi->direcao);
           bool=1;
        }   
    }
    if(!bool)fprintf(log,"Nenhum.\n");
    else bool = 0;

    fprintf(log,"\nChegaram Depois do Tempo:\n");
    for(pos=0; pos < tamanho_aviao(*pousados); pos++){
        avi = info(*pousados,pos);
        if(avi->direcao > avi->tempo_de_voo){
           add_to_log(log,avi);
           fprintf(log,"Tempo Real: %d\n",avi->direcao);
           bool=1; 
        }   
    }
    if(!bool)fprintf(log,"Nenhum.\n");
    else bool = 0;

    fprintf(log, "\nOcorrencia de Tempestades: %d\n", *(contadores+0));
    fprintf(log, "Ocorrencia de Neblina: %d\n", *(contadores+1));
    fprintf(log, "Ocorrencia de Turbulencias: %d\n", *(contadores+2));

    fprintf(log,"\nTodos os avioes que pousaram:\n");
    if(*pousados)
        for(pos=0; pos < tamanho_aviao(*pousados); pos++){
            avi = info(*pousados,pos);
            add_to_log(log,avi);
            fprintf(log,"Tempo Real: %d\n",avi->direcao);
        }
    else fprintf(log,"Nenhum.\n");

    fprintf(log,"\nTodos os avioes que continuaram voando:\n");
    if(*ceu)
        for(pos=0; pos < tamanho_aviao(*ceu); pos++){
            avi = info(*ceu,pos);
            add_to_log(log,avi);
            fprintf(log,"\n");
        }
    else fprintf(log,"Nenhum.");

    fprintf(log,"\nTodos os avioes no aeroporto:\n");
    if(*aeroporto){
        for( pis=*aeroporto; pis; pis = pis->prox, cont++ ){
            fprintf(log,"Pista %d:\n", cont+1);

            if(pis->head){
                for( pos=0; pos < tamanho_aviao(pis->head); pos++ ){
                    avi = info(pis->head, pos);
                    add_to_log(log, avi);
                    fprintf(log,"\n");
                }
            }
            else fprintf(log,"Nenhum.\n");
        }

    }
    else fprintf(log,"Nenhum.");


}
