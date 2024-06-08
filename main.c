#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//structs:
typedef struct datas {
    unsigned short int dia;
    unsigned short int mes;
    unsigned short int ano;
} Data;

typedef struct reserva {
    char *nome;
    char *sobrenome;
    char cpf[15];
    char *numero_assento;
    int classe; // 0 ou 1 ; 0 = economica ; 1 = executiva ;
    Data data_da_viagem;

} Reserva;

typedef struct dados {
    int aberto;
    int assentos;
    float valores[2]; // convenção: 0 = economica ; 1 = executiva ;
    Reserva *reservas;
} Dados;


//funções:




//main:
int main(void) {
    Dados dados;
    ler_arquivo(&dados);



    salvar_arquivo(dados);
    return 0;
}