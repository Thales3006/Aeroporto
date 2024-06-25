//*****************************************************************************

//TRABALHO DE ESTRUTURA DE DADOS 1

//FEITO POR:
// THALES JANISCH SANTOS            a2566737
// MARCOS VINICIUS SANTOS PASSOS    a2566672
// JOAO PAULO SIMPLICIO             a2566656

// Na nossa biblioteca se encontra a maioria das funções 
// aqui apenas temos a main e a parse, que é a função que lê
// o arquivo de entrada e chama as funções da biblioteca.

//Testado no LINUX e WINDOWS
//Supostamente é para funcionar em qualquer um dos dois sitemas operacionais

//Comandos para rodar
//
// gcc -c bibs.c
// gcc main.c bibs.o -lm -o main
// ./main

//*****************************************************************************


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"bibs.h"

void parse(pista** aeroporto, aviao** ceu, aviao** pousados,FILE* entrada);

int main(){
    pista* aeroporto = NULL; // "lista de listas" com os aviões que não decolaram
    aviao* voando = NULL; // lista com os aviões voando
    aviao* pousados = NULL; // lista com os aviões que ja terminaram seu percurso
    FILE * entrada = fopen("entrada.txt","r"); //arquivo para leitura de dados
    if(!entrada){
        printf("\nNao foi possivel abrir o arquivo!\n");
        exit(1);
    }

    parse(&aeroporto, &voando, &pousados, entrada);

    return 0;
}

void parse(pista** aeroporto, aviao** ceu, aviao** pousados,FILE* entrada){//faz a interpretação do arquivo entrada.txt
                                                                           //chama as funções da nossa biblioteca bibs
    char* cmd_line = malloc(sizeof(char)*ARRAY_SIZE);
    char* comando = malloc(sizeof(char)*ARRAY_SIZE);
    int* argI = malloc(sizeof(int)*4);//variaveis para os argumentos passados em entrada.txt
    char* argS = malloc(sizeof(char)*2*ARRAY_SIZE);
    int* clima = malloc(sizeof(int)*3);

    if(!cmd_line||!comando||!argI||!argS||!clima){//verifica se a memoria foi concedida pelo S.O.
        printf("\nSem memoria o suficiente!\n");
        exit(1);
    }

    *(clima+0)=-1;
    *(clima+1)=-1;
    *(clima+2)=-1;

    while( feof(entrada) == 0 ){// le o arquivo inteiro
        fgets(cmd_line, 100, entrada);//le cada linha e passa para uma string

        strcpy(comando,strtok(cmd_line," "));

        if(strcmp(comando,"pistas")==0){
            *(argI+0)= atoi(strtok(NULL," "));
            
            pistas(aeroporto, argI[0] );
        }

        else if(strcmp(comando,"insere_aviao")==0){
            *(argI+0)= atoi(strtok(NULL," "));
            *(argI+1)= atoi(strtok(NULL," "));
            strcpy((argS+0*ARRAY_SIZE), strtok(NULL," "));
            strcpy((argS+1*ARRAY_SIZE), strtok(NULL," "));
            *(argI+2)= atoi(strtok(NULL," "));
            *(argI+3)= atoi(strtok(NULL," "));

            add_to_pista(aeroporto, *(argI+0)-1, *(argI+1), (argS+0*ARRAY_SIZE), (argS+1*ARRAY_SIZE), *(argI+2), *(argI+3), 0, 1, 0);
        }

        else if(strcmp(comando,"decolar")==0){
            *(argI+0)= atoi(strtok(NULL," "));

            decolar(aeroporto, ceu, *(argI+0)-1);
        }

        else if(strcmp(comando,"tempestade")==0){
            *(clima+0)= atoi(strtok(NULL," "));
            *(clima+0)-= 1;
        }
        else if(strcmp(comando,"neblina")==0){
            *(clima+1)= atoi(strtok(NULL," "));
            *(clima+1)-= 1;
        }
        else if(strcmp(comando,"turbulencia")==0){
            *(clima+2)= atoi(strtok(NULL," "));
            *(clima+2)-= 1;
        }

        else if(strcmp(comando,"iniciasimulacao")==0){
            *(argI+0)= atoi(strtok(NULL," "));

            iniciasimulacao(aeroporto, ceu, pousados, *(argI+0), clima);
        }
        
        else if(strcmp(comando,"fim")==0){
            fim(aeroporto,ceu,pousados);
        }
    }
    fim(aeroporto,ceu,pousados);
}
