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
} Reserva;

typedef struct dados {
    int aberto;
    int assentos;
    float valores[2]; // convenção: 0 = economica ; 1 = executiva ;
    Reserva *reservas;
    int num_reservas;
} Dados;


//funções:

/* FORMATO DO ARQUIVO
aberto asssentos valores[0] valores[1] num_reservas
dia mes ano tam_part partida tam_dest destino

tam_nome nome tam_sobrenome sobrenome
cpf tam_assento numero_assento classe
    ...

*/
void ler_arquivo(Dados *dados) {
    FILE *fp;
    fp = fopen("DATA.DAT", "r");
    fscanf(fp, "%d", &dados->aberto);
    fscanf(fp, " %d", &dados->assentos);
    fscanf(fp, " %f", &dados->valores[0]);
    fscanf(fp, " %f", &dados->valores[1]);
    fscanf(fp, " %d", &dados->num_reservas);
    fscanf(fp, " %d", &dados->data_do_voo.dia);
    fscanf(fp, " %d", &dados->data_do_voo.mes);
    fscanf(fp, " %d", &dados->data_do_voo.ano);
    int tam_part, tam_dest;
    fscanf(fp, " %d", &tam_part);
    dados->partida = (char *) malloc(tam_part * sizeof(char));
    fscanf(fp, " %s", dados->partida);

    fscanf(fp, " %d", &tam_dest);
    dados->destino = (char *) malloc(tam_dest * sizeof(char));
    fscanf(fp, " %s", dados->destino);

    int tam_reservas = dados->num_reservas * sizeof(Reserva);
    dados->reservas = (Reserva *) malloc(tam_reservas);
    int i;
    for (i = 0; i < dados->num_reservas; i++) {
        int tam_nome, tam_sobrenome, tam_assento;
        fscanf(fp, " %d", &tam_nome);
        dados->reservas[i].nome = (char *) malloc(tam_nome * sizeof(char));
        fscanf(fp, " %s", dados->reservas[i].nome);

        fscanf(fp, " %d", &tam_sobrenome);
        dados->reservas[i].sobrenome = (char *) malloc(tam_sobrenome * sizeof(char));
        fscanf(fp, " %s", dados->reservas[i].sobrenome);

        dados->reservas[i].cpf = (char *) malloc(15 * sizeof(char));
        fscanf(fp, " %s", dados->reservas[i].cpf);

        fscanf(fp, " %d", &tam_assento);
        dados->reservas[i].numero_assento = (char *) malloc(tam_assento * sizeof(char));
        fscanf(fp, " %s", dados->reservas[i].numero_assento);

        fscanf(fp, " %d", dados->reservas[i].classe);
    }

    fclose(fp);
}

void salvar_arquivo(Dados dados) {
    FILE *fp;
    fp = fopen("DATA.DAT", "w");
    fprintf(fp, "%d", dados.aberto);
    fprintf(fp, " %d", dados.assentos);
    fprintf(fp, " %.2f", dados.valores[0]);
    fprintf(fp, " %.2f", dados.valores[1]);
    fprintf(fp, " %d", dados.num_reservas);
    fprintf(fp, " %d", dados.data_do_voo.dia);
    fprintf(fp, " %d", dados.data_do_voo.mes);
    fprintf(fp, " %d", dados.data_do_voo.ano);
    int tam_part, tam_dest;
    tam_part = strlen(dados.partida);
    tam_dest = strlen(dados.destino);
    fprintf(fp, " %d", tam_part);
    fprintf(fp, " %d", dados.partida);
    fprintf(fp, " %d", tam_dest);
    fprintf(fp, " %s", dados.destino);

    int i;
    for (i = 0; i < dados.num_reservas; i++) {
        int tam_nome, tam_sobrenome, tam_assento;
        tam_nome = strlen(dados.reservas[i].nome);
        tam_sobrenome = strlen(dados.reservas[i].sobrenome);
        tam_assento = strlen(dados.reservas[i].numero_assento);

        fprintf(fp, " %d", tam_nome);
        fprintf(fp, " %s", dados.reservas[i].nome);

        fprintf(fp, " %d", tam_sobrenome);
        fprintf(fp, " %s", dados.reservas[i].sobrenome);

        fprintf(" %s", dados.reservas[i].cpf);

        fprintf(fp, " %d", tam_assento);
        fprintf(fp, " %s", dados.reservas[i].numero_assento);

        fprintf(fp, " %d", dados->reservas[i].classe);
    }

    fclose(fp);
}


void cancelar_reserva(Dados *dados) {
    char cancelado[15];
    scanf("%s", cancelado);
    for(int i = 0; i < dados->num_reservas; i++){
        if(strcmp(dados->reservas[i].cpf, cancelado) == 0){
            for(int j = i; j < dados->num_reservas - 1; j++){
                dados->reservas[j] = dados->reservas[j + 1];
            }
            dados->num_reservas = dados->num_reservas - 1;
            dados->reservas = (Reserva *) realloc(dados->num_reservas * sizeof(Reserva));
            break;
        }
    }
    for(int i = 0; i < 10; i++){
        printf("-----");
    }
    printf("\n");
}

void fechar_dia(Dados dados) {
    float posicao = 0;
    printf("Fechamento do dia: \n");
    printf("Quantidade de reservas: %d\n", dados.num_reservas);
    for(int i = 0; i < dados.num_reservas; i++) {
        if (dados.reservas[i].classe == 0) {
            posicao += dados.valores[0];
        }
        else {
            posição += dados.valores[1];
        }
    }
    printf("Posição: %.2f\n", posicao);
    for(int i = 0; i < 10; i++){
        printf("-----");
    }
    printf("\n");
    exit(0);
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
