
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
void tempestade(aviao **ceu);
void turbulencia(aviao **ceu);
void pistas(pista** a,int n);
void decolar(pista** aeroporto, aviao** ceu, int pista);
void fim(pista **aeroporto,aviao **voando);

