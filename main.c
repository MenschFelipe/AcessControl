#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "rfid.h"

// Função para carregar os usuários do arquivo
void load_users(User users[], int *user_count, int *next_id) {
    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    int id;
    char name[MAX_NAME_LENGTH];
    char block[MAX_BLOCK_LENGTH];
    char unit[MAX_UNIT_LENGTH];

    *user_count = 0;
    *next_id = 1;

    while (fscanf(fp, "%d;%[^;];%[^;];%[^\n]\n", &id, name, block, unit) != EOF) {
        users[*user_count].id = id;
        strcpy(users[*user_count].name, name);
        strcpy(users[*user_count].block, block);
        strcpy(users[*user_count].unit, unit);
        (*user_count)++;
        if (id >= *next_id) {
            *next_id = id + 1;
        }
    }

    fclose(fp);
}

// Função para carregar as tags RFID do arquivo
void load_rfid_tags(RFIDTag tags[], int *tag_count) {
    FILE *fp = fopen("rfids.txt", "r");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    int id;
    int user_id;
    char tag_code[MAX_LENGTH];

    *tag_count = 0;

    while (fscanf(fp, "%d;%d;%[^\n]\n", &id, &user_id, tag_code) != EOF) {
        tags[*tag_count].id = id;
        tags[*tag_count].user_id = user_id;
        strcpy(tags[*tag_count].tag_code, tag_code);
        (*tag_count)++;
    }

    fclose(fp);
}

// Função para imprimir o menu
void print_menu() {
    printf("\n=== Menu ===\n");
    printf("1. Criar usuário\n");
    printf("2. Listar usuários\n");
    printf("3. Atualizar usuário\n");
    printf("4. Deletar usuário\n");
    printf("5. Criar tag RFID\n");
    printf("6. Listar tags RFID\n");
    printf("7. Atualizar tag RFID\n");
    printf("8. Deletar tag RFID\n");
    printf("9. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    User users[MAX_USERS];
    RFIDTag tags[MAX_TAGS];
    int user_count = 0;
    int tag_count = 0;
    int next_user_id = 1;
    int option;

    load_users(users, &user_count, &next_user_id);
    load_rfid_tags(tags, &tag_count);

    print_menu();
    if (scanf("%d", &option) != 1) {
        while (getchar() != '\n'); // Limpar o buffer de entrada
        printf("Entrada inválida. Tente novamente.\n");
        return 1; // Encerrar o programa com código de erro
    }
    getchar(); // Limpar o buffer de entrada

    switch (option) {
        case 1:
            create_user(users, &user_count, &next_user_id);
            return 0; // Encerra o programa após criar o usuário
        case 2:
            list_users(users, user_count);
            break;
        case 3:
            update_user(users, user_count);
            break;
        case 4:
            delete_user(users, &user_count);
            break;
        case 5:
            create_rfid_tag(tags, &tag_count, users, user_count);
            return 0; // Encerra o programa após criar a tag RFID
        case 6:
            list_rfid_tags(tags, tag_count);
            break;
        case 7:
            update_rfid_tag(tags, tag_count);
            break;
        case 8:
            delete_rfid_tag(tags, &tag_count);
            break;
        case 9:
            printf("Saindo do programa.\n");
            break;
        default:
            printf("Opção inválida. Saindo do programa.\n");
    }

    return 0;
}