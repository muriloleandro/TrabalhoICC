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
    char *cpf;
    char *numero_assento;
    int classe; // 0 ou 1 ; 0 = economica ; 1 = executiva ;
} Reserva;

typedef struct dados {
    int aberto;
    int assentos;
    float valores[2]; // convenção: 0 = economica ; 1 = executiva ;
    Reserva *reservas;
    int num_reservas;
    Data data_da_viagem;
    char *numero_do_voo;
    char *origem;
    char *destino;
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
    fscanf(fp, " %d", &dados->data_da_viagem.dia);
    fscanf(fp, " %d", &dados->data_da_viagem.mes);
    fscanf(fp, " %d", &dados->data_da_viagem.ano);
    int tam_part, tam_dest;
    fscanf(fp, " %d", &tam_part);
    dados->origem = (char *) malloc(tam_part * sizeof(char));
    fscanf(fp, " %s", dados->origem);

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
    fprintf(fp, " %d", dados.data_da_viagem.dia);
    fprintf(fp, " %d", dados.data_da_viagem.mes);
    fprintf(fp, " %d", dados.data_da_viagem.ano);
    int tam_part, tam_dest;
    tam_part = strlen(dados.origem);
    tam_dest = strlen(dados.destino);
    fprintf(fp, " %d", tam_part);
    fprintf(fp, " %d", dados.origem);
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

        fprintf(fp, " %s", dados.reservas[i].cpf);

        fprintf(fp, " %d", tam_assento);
        fprintf(fp, " %s", dados.reservas[i].numero_assento);

        fprintf(fp, " %d", dados.reservas[i].classe);
    }

    fclose(fp);
}

void sair(Dados dados) {
    salvar_arquivo(dados);
    exit(0);
}

void modificar_reserva(Dados *dados) {
    char cpf_consulta_mod[15];
    scanf(" %s", cpf_consulta_mod);
    char *nome_mod = (char *) malloc(100 * sizeof(char));
    scanf(" %s", nome_mod);
    nome_mod = (char *) realloc(nome_mod, strlen(nome_mod)*sizeof(char));
    char *sobre_mod = (char *) malloc(100 * sizeof(char));
    scanf(" %s", sobre_mod);
    sobre_mod = (char *) realloc(sobre_mod, strlen(sobre_mod)*sizeof(char));
    char *cpf_mod = (char *) malloc(15 * sizeof(char));
    scanf(" %s", cpf_mod);
    char *assento_mod = (char *) malloc(100 * sizeof(char));
    scanf(" %s", assento_mod);
    assento_mod = (char *) realloc(assento_mod, strlen(assento_mod)*sizeof(char));
    for (int i = 0; i < dados->num_reservas; i++) {
        if (strcmp(dados->reservas[i].cpf, cpf_consulta_mod) == 0) {
            free(dados->reservas[i].cpf);
            dados->reservas[i].cpf = cpf_mod;
            free(dados->reservas[i].nome);
            dados->reservas[i].nome = nome_mod;
            free(dados->reservas[i].sobrenome);
            dados->reservas[i].sobrenome = sobre_mod;
            free(dados->reservas[i].numero_assento);
            dados->reservas[i].numero_assento = assento_mod;
            printf("Reserva Modificada:\n");
            printf("%s\n", cpf_consulta_mod);
            printf("%s %s\n", dados->reservas[i].nome, dados->reservas[i].sobrenome);
            printf("%s/%s/%s\n", dados->data_da_viagem.dia, dados->data_da_viagem.mes, dados->data_da_viagem.ano);
            printf("Voo: %s\n", dados->numero_do_voo);
            printf("Assento: %s\n", dados->reservas[i].numero_assento);
            if (dados->reservas[i].classe == 0) {
                printf("Classe: economica\n");
            }
            else {
                printf("Classe: executiva");
            }
            printf("Trecho: %s %s\n", dados->origem, dados->destino);
            if (dados->reservas[i].classe == 0) {
                printf("Valores: %s\n", dados->valores[0]);
            }
            else {
                printf("Valores: %s\n", dados->valores[1]);
            }
            printf("--------------------------------------------------\n");
            break;
        }
    }
    
}

void cancelar_reserva(Dados *dados) {
    char cancelado[15];
    scanf(" %s", cancelado);
    for (int i = 0; i < dados->num_reservas; i++){
        if (strcmp(dados->reservas[i].cpf, cancelado) == 0){
            for (int j = i; j < dados->num_reservas - 1; j++){
                dados->reservas[j] = dados->reservas[j + 1];
            }
            dados->num_reservas = dados->num_reservas - 1;
            dados->reservas = (Reserva *) realloc(dados->reservas, dados->num_reservas * sizeof(Reserva));
            printf("%s\n", cancelado);
            printf("%s %s\n", dados->reservas[i].nome, dados->reservas[i].sobrenome);
            printf("%s\n", dados->data_da_viagem);
            printf("Voo: %s\n", dados->numero_do_voo);
            printf("Assento: %s\n", dados->reservas[i].numero_assento);
            if (dados->reservas[i].classe == 0) {
                printf("Classe: economica\n");
            }
            else {
                printf("Classe: executiva\n");
            }
            printf("Trecho: %s %s\n", dados->origem, dados->destino);
            if (dados->reservas[i].classe == 0) {
                printf("Valor: %s\n", dados->valores[0]);
            }
            else {
                printf("Valor: %s\n", dados->valores[1]);
            }
            break;
        }
    }
    printf("--------------------------------------------------\n");
}

void fechar_dia(Dados dados) {
    float posicao = 0;
    printf("Fechamento do dia: \n");
    printf("Quantidade de reservas: %d\n", dados.num_reservas);
    for (int i = 0; i < dados.num_reservas; i++) {
        if (dados.reservas[i].classe == 0) {
            posicao += dados.valores[0];
        }
        else {
            posicao += dados.valores[1];
        }
    }
    printf("Posição: %.2f\n", posicao);
    printf("--------------------------------------------------\n");
    sair(dados);
}

void ler_reserva(Dados *dados){
    float valor;
    char exec[10] = "executivo";
    char classe_do_voo[10];

    if(dados->assentos == 0){
        return;
    }

    dados->reservas = (Reserva*)malloc(dados->num_reservas*sizeof(Reserva));

    dados->reservas->nome = (char*)malloc(100*sizeof(char));
    scanf("%[^\n]s", dados->reservas->nome);
    dados->reservas->nome = realloc(dados->reservas->nome, strlen(dados->reservas->nome));

    dados->reservas->sobrenome = (char*)malloc(100*sizeof(char));
    scanf("%[^\n]s", dados->reservas->sobrenome);
    dados->reservas->sobrenome = realloc(dados->reservas->sobrenome, strlen(dados->reservas->sobrenome));

    scanf("%[^\n]s", dados->reservas->cpf);

    scanf("%hu %hu %hu", &(dados->data_da_viagem.dia), &(dados->data_da_viagem.mes), &(dados->data_da_viagem.ano));

    for (int i=0; i<4; i++){
        scanf("%c", (dados -> numero_do_voo+i));
    }

    dados->reservas->numero_assento = (char*)malloc(10*sizeof(char));
    scanf("%[^\n]s", dados->reservas->numero_assento);
    dados->reservas->numero_assento = realloc(dados->reservas->numero_assento, strlen(dados->reservas->numero_assento));

    for (int i=0; i<9; i++){
        scanf("%c", &(classe_do_voo[i]));
    }
    if(strcmp(exec, classe_do_voo)==0){
        dados->reservas-> classe = 1;
    }else{
        dados->reservas->classe = 0;
    }

    scanf("%f", &valor);

    dados->origem = (char*)malloc(100*sizeof(char));
    scanf("%[^\n]s", dados->origem);
    dados->origem = realloc(dados->origem, strlen(dados->origem));

    dados->destino = (char*)malloc(100*sizeof(char));
    scanf("%[^\n]s", dados->destino);
    dados->destino = realloc(dados->destino, strlen(dados->destino));

    dados->num_reservas++;
}

void consultar_reserva(Dados *dados){
    int num;
    char cpf_consultado [15];
    scanf("%[^\n]s", cpf_consultado);
    for (int i=0; i<dados->num_reservas; i++){
        if(strcmp(cpf_consultado, dados->reservas[i].cpf)==0){
            num=i;
            break;
        }
    }
    printf("%s\n", dados->reservas[num].cpf);
    printf("%s %s\n", dados->reservas[num].nome, dados->reservas[num].sobrenome);
    printf("%hu/%hu/%hu\n", dados->data_da_viagem.dia, dados->data_da_viagem.mes, dados->data_da_viagem.ano);
    printf("Voo: %s\n", dados->numero_do_voo);
    printf("Assento: %s\n", dados->reservas[num].numero_assento);
    if(dados->reservas[num].classe == 0){
        printf("Classe: economica\n");
    }else{
        printf("Classe: economica\n");
    }
    printf("Trecho: %s %s\n", dados->origem, dados->destino);
    printf("Valor: %.2f\n", dados->valores[(dados->reservas[num].classe)]);
    printf("--------------------------------------------------\n");
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

void comando(Dados *dados){
    char comando[3];
    scanf("%s", comando);
    if(*comando == 'A'){
        abrir_voo(dados);
    }
    if(*comando == 'M'){
        modificar_reserva(dados);
    }
    if(*comando == 'R'){
        ler_reserva(dados);
    }
    if(*comando == 'C' && *(comando+1) == 'A'){
        cancelar_reserva(dados);
    }
    if((*comando == 'C' && *(comando+1) == 'R')){
        consultar_reserva(dados);
    }
    if(*comando == 'F' && *(comando+1) == 'V'){
        fechar_voo(dados);
    }
    if(*comando == 'F' && *(comando+1) == 'D'){
        fechar_dia(*dados);
    }
}

int main(void) {
    Dados dados;
    ler_arquivo(&dados);

    while (1) {
        comando(&dados);
    }
    salvar_arquivo(dados);
    return 0;
}
