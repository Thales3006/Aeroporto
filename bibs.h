
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

// FUNÇÕES DE AUXILIO DE CRIAÇÃO E ALTERAÇÃO DE LISTAS ENCADEADAS

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
//FUNÇÕES REFERENTES AO PROJETO

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

void grafico(aviao* ceu);

//*****************************************
