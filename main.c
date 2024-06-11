#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structs:
//O Struct Datas guarda a data da viagem em dia mês e ano por questão de organização.
typedef struct datas {
    int dia;
    int mes;
    int ano;
} Data;

//O Struct Reserva vai guardar os valores de reserva de cada passageiro:
//Exemplo: Passageiro Pedro Silva tem nome Pedro, sobrenome Silva, Classe executiva, etc...
typedef struct reserva {
    char *nome;
    char *sobrenome;
    char *cpf;
    char *numero_assento;
    int classe; //0 ou 1 ; 0 = economica ; 1 = executiva ;
} Reserva;

//O Struct Dados guarda valores gerais do voo como se o voo ja foi aberto, quantos assentos estão disponiveis
typedef struct dados {
    int aberto;          //variável que guarda se o File já foi aberto pela primeira vez (1) ou não (0)
    int assentos;        //número de assentos do voo
    float valores[2];    //Guarda os preços das classes. Convenção: [0] = economica ; [1] = executiva ;
    Reserva *reservas;   //Vetor de structs para acessar a Struct Reserva de cada cliente
    int num_reservas;    //Contador de reservas feitas
    Data data_da_viagem; //Struct com data separada em dia mês e ano
    char *numero_do_voo;
    char *origem;
    char *destino;
} Dados;

//funções:

/*
 - Os valores da struct 'dados' são salvos no arquivo,
   junto do tamanho das arrays nela.
 - Nome: "DATA.DAT"
 - Especificação do Arquivo:
aberto asssentos valores[0] valores[1] num_reservas
dia mes ano tam_voo numero_voo tam_origem origem tam_dest destino

tam_nome nome tam_sobrenome sobrenome
cpf tam_assento numero_assento classe

tam_nome nome tam_sobrenome sobrenome
cpf tam_assento numero_assento classe
    ...
*/
void ler_arquivo(Dados *dados) {
    FILE *fp;
    fp = fopen("DATA.DAT", "r");

    // caso o arquivo não exista, deixe valores genéricos
    dados->aberto = 0;
    dados->assentos = 0;
    dados->valores[0] = 0.0;
    dados->valores[1] = 0.0;
    dados->num_reservas = 0;
    dados->data_da_viagem.dia = 1;
    dados->data_da_viagem.mes = 1;
    dados->data_da_viagem.ano = 1970;
    dados->numero_do_voo = NULL;
    dados->origem = NULL;
    dados->destino = NULL;
    dados->reservas = NULL;
    if (fp == NULL) {
        return;
    }

    fscanf(fp, "%d", &dados->aberto);
    fscanf(fp, " %d", &dados->assentos);
    fscanf(fp, " %f", &dados->valores[0]);
    fscanf(fp, " %f", &dados->valores[1]);
    fscanf(fp, " %d", &dados->num_reservas);
    fscanf(fp, " %d", &dados->data_da_viagem.dia);
    fscanf(fp, " %d", &dados->data_da_viagem.mes);
    fscanf(fp, " %d", &dados->data_da_viagem.ano);

    int tam_part, tam_dest, tam_voo;
    fscanf(fp, " %d", &tam_voo);
    dados->numero_do_voo = (char *) malloc(tam_voo+1);
    fscanf(fp, " %s", dados->numero_do_voo);

    fscanf(fp, " %d", &tam_part);
    dados->origem = (char *) malloc(tam_part+1);
    fscanf(fp, " %s", dados->origem);

    fscanf(fp, " %d", &tam_dest);
    dados->destino = (char *) malloc(tam_dest+1);
    fscanf(fp, " %s", dados->destino);

    // apenas alocar e ler reservas se houver
    if (dados->num_reservas == 0) {
        fclose(fp);
        return;
    }

    int tam_reservas = dados->num_reservas * sizeof(Reserva);
    dados->reservas = (Reserva *) malloc(tam_reservas);
    int i;
    int tam_nome, tam_sobrenome, tam_assento;
    for (i = 0; i < dados->num_reservas; i++) {
        fscanf(fp, " %d", &tam_nome);
        dados->reservas[i].nome = (char *) malloc(tam_nome+1);
        fscanf(fp, " %s", dados->reservas[i].nome);

        fscanf(fp, " %d", &tam_sobrenome);
        dados->reservas[i].sobrenome = (char *) malloc(tam_sobrenome+1);
        fscanf(fp, " %s", dados->reservas[i].sobrenome);

        dados->reservas[i].cpf = (char *) malloc(15);
        fscanf(fp, " %s", dados->reservas[i].cpf);

        fscanf(fp, " %d", &tam_assento);
        dados->reservas[i].numero_assento = (char *) malloc(tam_assento+1);
        fscanf(fp, " %s", dados->reservas[i].numero_assento);

        fscanf(fp, " %d", &dados->reservas[i].classe);
    }

    fclose(fp);
}

/*
 A função segue a mesma lógica da leitura,
 exceto que printa no arquivo ao invés de escanear;
 Os tamanhos das strings são armazenadas para leitura posterior
*/
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

    int tam_part, tam_dest, tam_voo;
    tam_voo = strlen(dados.numero_do_voo);
    tam_part = strlen(dados.origem);
    tam_dest = strlen(dados.destino);
    fprintf(fp, " %d", tam_voo);
    fprintf(fp, " %s", dados.numero_do_voo);
    fprintf(fp, " %d", tam_part);
    fprintf(fp, " %s", dados.origem);
    fprintf(fp, " %d", tam_dest);
    fprintf(fp, " %s", dados.destino);

    // os dados do vetor reservas são armazenados em sequência
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

/*
 Essa função sai do programa adequadamente, salvando os dados da RAM
 e limpando a memória adequadamente
*/
void sair(Dados dados) {
    salvar_arquivo(dados);
    free(dados.numero_do_voo);
    free(dados.origem);
    free(dados.destino);
    for (int i = 0; i < dados.num_reservas; i++) {
        free(dados.reservas[i].nome);
        free(dados.reservas[i].sobrenome);
        free(dados.reservas[i].cpf);
        free(dados.reservas[i].numero_assento);
    }
    if (dados.num_reservas != 0) {
        free(dados.reservas);
    }
    exit(0);
}

/*
 - Armazena os valores passados no comando
 - Marca o voo como aberto
 - Inicializa vetores que se repetirão como NULL
*/
void abrir_voo(Dados *dados) {
    dados->aberto = 1;
    scanf(" %d", &dados->assentos);
    scanf(" %f", &dados->valores[0]);
    scanf(" %f", &dados->valores[1]);
}

/*
 - Printa os dados expecificados e executa sair()
 - Marca o voo como fechado
*/
void fechar_voo(Dados *dados) {
    dados->aberto = 0;
    float total = 0;
    int i, tipo;
    printf("Voo Fechado!\n\n");
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
    sair(*dados);
}

//A função Modificar Reserva recebe um CPF como input e vai inserir na reserva do CPF os dados novos como CPF novo, nome novo, etc...
//Como não é possível saber o tamanho das strings préviamente, alocamos um tamanho grande para receber a string, corrigimos o tamanho com realloc,
//livramos os valores antigos com free() e inserimos os valores novos no Vetor de Structs de Reservas.
void modificar_reserva(Dados *dados) {
    //Essa parte declara as variáveis, aloca espaço para receber as strings,
    //recebe as strings e ajusta o espaço alocado para o tamanho da string.
    char cpf_consulta_mod[15];                                                  
    scanf(" %s", cpf_consulta_mod);                                             

    char *nome_mod = (char *) malloc(100);
    scanf(" %s", nome_mod);
    nome_mod = (char *) realloc(nome_mod, strlen(nome_mod)+1);

    char *sobre_mod = (char *) malloc(100);
    scanf(" %s", sobre_mod);
    sobre_mod = (char *) realloc(sobre_mod, strlen(sobre_mod)+1);

    char *cpf_mod = (char *) malloc(15);
    scanf(" %s", cpf_mod);

    char *assento_mod = (char *) malloc(100);
    scanf(" %s", assento_mod);
    assento_mod = (char *) realloc(assento_mod, strlen(assento_mod)+1);

    for (int i = 0; i < dados->num_reservas; i++) {
        if (strcmp(dados->reservas[i].cpf, cpf_consulta_mod) == 0) {        
            //Essa parte libera os valores antigos salvos na struct
            //e escreve no lugar os dados modificados obtidos na função.
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
            printf("%02d/%02d/%4d\n", dados->data_da_viagem.dia, dados->data_da_viagem.mes, dados->data_da_viagem.ano);
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
                printf("Valores: %.2f\n", dados->valores[0]);
            } else {
                printf("Valores: %.2f\n", dados->valores[1]);
            }
            printf("--------------------------------------------------\n");
            break;
        }
    }
    
}

//Funcao Cancelar Reserva vai receber um CPF como input, buscar esse CPF na lista de reservas e substituir os dados desse CPF pelo CPF do proximo da lista.
//Essa funcao muda todas as reservas na frente do CPF cancelado para um valor atras, assim o CPF cancelado eh substituido pelo proximo e o proximo e substituido pelo
//proximo do proximo, tirando os "buracos" da lista de reservas.
void cancelar_reserva(Dados *dados) {
    char cancelado[15];
    scanf(" %s", cancelado);
    for (int i = 0; i < dados->num_reservas; i++){                 
        //Essa parte itera os itens da lista de reservas ate achar um CPF igual ao do input.
        if (strcmp(dados->reservas[i].cpf, cancelado) == 0){
            free(dados->reservas[i].nome);
            free(dados->reservas[i].sobrenome);
            free(dados->reservas[i].cpf);
            free(dados->reservas[i].numero_assento);
            
            for (int j = i; j < dados->num_reservas - 1; j++){       
                //Essa parte vai mover os itens da lista de reserva que estao apos o CPF cancelado em 1 posicao
                //para tras. Ele faz isso n - 1 vezes para nao puxar um lixo de memoria para a ultima posicao.
                dados->reservas[j] = dados->reservas[j + 1];          
            }
            dados->num_reservas = dados->num_reservas - 1;    
            //Esse trecho diminui uma reserva
            if (dados->num_reservas != 0) {
                dados->reservas = (Reserva *) realloc(dados->reservas, dados->num_reservas * sizeof(Reserva));
            } else {
                free(dados->reservas);
            }
            
            //Esse pedaço faz um Realloc no Vetor de Structs Reservas
            //para ajustar o espaço alocado na Heap para o novo tamanho do Vetor.
                                                                                                          
            dados->assentos = dados->assentos + 1;   
            //Esse pedaço adiciona 1 ao numero de assentos (No cancelamento um assento é livrado).
            break;
        }
    }
}

//A Função Fechar Dia escreve a quantidade de reservas (calculada anteriormente), calcula a posição reitarando a soma dos preços das classes e escreve a posição.
void fechar_dia(Dados dados) {
    float posicao = 0;
    printf("Fechamento do dia: \n");
    printf("Quantidade de reservas: %d\n", dados.num_reservas);
    for (int i = 0; i < dados.num_reservas; i++) {         
        //Essa parte itera o numero de reservas. Para cada reserva ela verifica se a classe é executiva ou econômica
        //e soma esse preço para fazer a contagem da "posição".
        if (dados.reservas[i].classe == 0) {               
            posicao += dados.valores[0]; 
            //soma da classe econômica
        }
        else {
            posicao += dados.valores[1];  
            //soma da classe executiva
        }
    }
    printf("Posição: %.2f\n", posicao);
    printf("--------------------------------------------------\n");
    sair(dados);
}

void ler_reserva(Dados *dados){
    //essa funcao visa ler e armazenar as reservas no aviao que serao fornecidas pelo//
    //usuario, guardando-as na memoria via alocacao dinamica para otimizar memoria//
    float valor;//criado para armazenar o valor fornecido, que sera descartado, considerando//
    //o fato dos 2 valores (economico e executivo) ja serem providenciados em 'abrir voo'//
    char exec[10] = "executiva";//pra comparar com a classe fornecida pelo usuario//
    char classe_do_voo[10];//a dita classe que sera comparada//

    if(dados->assentos == 0) {
        fechar_voo(dados);
    }//checa se existem assentos disponiveis; caso nao, ele volta para a main para falar//
    //que o voo esta cheio//

    dados->num_reservas++;//aumenta o numero de reservas, ja que um novo usuario esta sendo//
    //cadastrado no sistema//

    if (dados->num_reservas == 1) {
        dados->reservas = (Reserva *) malloc(sizeof(Reserva));
    } else {
        dados->reservas = (Reserva *) realloc(dados->reservas, dados->num_reservas * sizeof(Reserva));
    }//realoca mais espaço para a nova reserva que sera armazenada;

    int n = dados->num_reservas-1;//n serve para especificar qual posicao do vetor de structs//
    //'reservas' estamos acessando//

    dados->reservas[n].nome = (char *) malloc(100);
    scanf(" %s", dados->reservas[n].nome);
    dados->reservas[n].nome = (char *) realloc(dados->reservas[n].nome, strlen(dados->reservas[n].nome)+1);
    //armazena o nome do usuario na memoria//

    dados->reservas[n].sobrenome = (char *) malloc(100);
    scanf(" %s", dados->reservas[n].sobrenome);
    dados->reservas[n].sobrenome = (char *) realloc(dados->reservas[n].sobrenome, strlen(dados->reservas[n].sobrenome)+1);
    //armazena seu sobrenome//

    dados->reservas[n].cpf = (char *) malloc(15);
    scanf(" %s", dados->reservas[n].cpf);//armazena o CPF//

    scanf("%d", &dados->data_da_viagem.dia);
    scanf("%d", &dados->data_da_viagem.mes);
    scanf("%d", &dados->data_da_viagem.ano);//armazena as datas//

    if (dados->numero_do_voo != NULL) {
        free(dados->numero_do_voo);
    }
    dados->numero_do_voo = (char *) malloc(100);
    scanf(" %s", dados->numero_do_voo);//armazena o numero do voo//
    dados->numero_do_voo = (char *) realloc(dados->numero_do_voo, strlen(dados->numero_do_voo)+1);

    dados->reservas[n].numero_assento = (char *) malloc(10);
    scanf(" %s", dados->reservas[n].numero_assento);//reserva os assentos//
    dados->reservas[n].numero_assento = (char *) realloc(dados->reservas[n].numero_assento, strlen(dados->reservas[n].numero_assento)+1);

    scanf(" %s", classe_do_voo);
    if (strcmp(exec, classe_do_voo) == 0) {
        dados->reservas[n].classe = 1;
    } else {
        dados->reservas[n].classe = 0;
    }//checa, comparando com 'executiva', qual a classe financeira do voo do sujeito//

    scanf("%f", &valor);//guarda o valor, que eh inutil nesse contexto//

    if (dados->origem != NULL) {
        free(dados->origem);
    }
    dados->origem = (char *) malloc(100);
    scanf(" %s", dados->origem);
    dados->origem = (char *) realloc(dados->origem, strlen(dados->origem)+1);//guarda origem do voo//

    if (dados->destino != NULL) {
        free(dados->destino);
    }
    dados->destino = (char *) malloc(100);
    scanf(" %s", dados->destino);
    dados->destino = (char *) realloc(dados->destino, strlen(dados->destino)+1);//guarda destino do voo//

    dados->assentos = dados->assentos - 1;
}

void consultar_reserva(Dados *dados){
    //esta funcao visa providenciar a consulta dos dados da reserva do passageiro, via CPF//
    int num;
    char cpf_consultado [15];
    scanf(" %s", cpf_consultado);
    for (int i=0; i<dados->num_reservas; i++){
        if(strcmp(cpf_consultado, dados->reservas[i].cpf)==0){
            num=i;
            break;
        }
    }//desejamos descobrir em qual parte do vetor 'reservas' esta o CPF que buscamos, e//
    //armazenaremos em 'num'//
    printf("%s\n", dados->reservas[num].cpf);
    printf("%s %s\n", dados->reservas[num].nome, dados->reservas[num].sobrenome);
    printf("%02d/%02d/%04d\n", dados->data_da_viagem.dia, dados->data_da_viagem.mes, dados->data_da_viagem.ano);
    printf("Voo: %s\n", dados->numero_do_voo);
    printf("Assento: %s\n", dados->reservas[num].numero_assento);
    if (dados->reservas[num].classe == 0) {//checa o valor de classe para descobri-la//
        printf("Classe: economica\n");
    } else {
        printf("Classe: executiva\n");
    }
    printf("Trecho: %s %s\n", dados->origem, dados->destino);
    printf("Valor: %.2f\n", dados->valores[dados->reservas[num].classe]);
    printf("--------------------------------------------------\n");
}

void comando(Dados *dados){//com essa funcao, queremos descobrir a partir das primeiras duas//
//iniciais fornecidas qual comando devemos executar//
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

/*
 A lógica da main() consiste em:
 - Criar um struct dos dados, e ler eles do arquivo
 - Entrar num loop infinito de leitura de comandos
 O programa sairá quando forem executados o fechamento do voo e fechamento do dia
*/
int main(void) {
    Dados dados;
    ler_arquivo(&dados);

    while (1) {
        comando(&dados);
    }
    return 0;
}