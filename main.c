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
    int num_reservas;
} Dados;


//funções:

void ler_arquivo(Dados *dados) {

}

void abrir_voo(Dados *dados) {
    dados->aberto = 1;
    scanf(" %d", &dados->assentos);
    scanf(" %f", &dados->valores[0]);
    scanf(" %f", &dados->valores[1]);
}

void fechar_voo(Dados *dados) {
    dados->aberto = 0;
    float total = 0;
    int i, tipo;
    for (i = 0; i < dados->num_reservas; i++) {
        tipo = dados->reservas[i].classe;
        total += dados->valores[tipo];

        printf("%s\n", dados->reservas[i].cpf);
        printf("%s ", dados->reservas[i].nome);
        printf("%s\n", dados->reservas[i].sobrenome);
        printf("%s\n\n", dados->reservas[i].numero_assento);
    }
    printf("Valor Total: %.2f\n", total);
    printf("--------------------------------------------------\n");
}

//main:
int main(void) {
    Dados dados;
    
    ler_arquivo(&dados);



    salvar_arquivo(dados);
    return 0;
}
