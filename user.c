#include <stdio.h>
#include <string.h>
#include "user.h"

void create_user(User users[], int *user_count) {
    User new_user;

    printf("Criando novo usuário...\n");
    printf("Digite o nome do usuário: ");
    fgets(new_user.name, MAX_NAME_LENGTH, stdin);
    new_user.name[strcspn(new_user.name, "\n")] = '\0';

    printf("Digite o bloco do usuário: ");
    fgets(new_user.block, MAX_BLOCK_LENGTH, stdin);
    new_user.block[strcspn(new_user.block, "\n")] = '\0';

    printf("Digite a unidade do usuário: ");
    fgets(new_user.unit, MAX_UNIT_LENGTH, stdin);
    new_user.unit[strcspn(new_user.unit, "\n")] = '\0';

    new_user.id = (*user_count) + 1;

    users[*user_count] = new_user;
    (*user_count)++;

    FILE *fp;
    fp = fopen("users.txt", "a");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return;
    }

    fprintf(fp, "%d;%s;%s;%s\n", new_user.id, new_user.name, new_user.block, new_user.unit);

    fclose(fp);

    printf("Usuário criado com sucesso.\n");
}

void list_users(User users[], int user_count) {
    printf("\nLista de Usuários:\n");

    FILE *fp;
    fp = fopen("users.txt", "r");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    int id;
    char name[MAX_NAME_LENGTH];
    char block[MAX_BLOCK_LENGTH];
    char unit[MAX_UNIT_LENGTH];

    while (fscanf(fp, "%d;%[^;];%[^;];%[^\n]\n", &id, name, block, unit) != EOF) {
        printf("ID: %d\n", id);
        printf("Nome: %s\n", name);
        printf("Bloco: %s\n", block);
        printf("Unidade: %s\n", unit);
        printf("--------------------\n");
    }

    fclose(fp);
}

void update_user(User users[], int user_count) {
    int id;
    printf("Digite o ID do usuário que deseja atualizar: ");
    scanf("%d", &id);
    getchar(); // Limpar o buffer de entrada

    int found = 0;
    for (int i = 0; i < user_count; ++i) {
        if (users[i].id == id) {
            found = 1;

            printf("Atualizando informações do usuário ID %d:\n", id);

            printf("Digite o novo nome do usuário: ");
            fgets(users[i].name, MAX_NAME_LENGTH, stdin);
            users[i].name[strcspn(users[i].name, "\n")] = '\0';

            printf("Digite o novo bloco do usuário: ");
            fgets(users[i].block, MAX_BLOCK_LENGTH, stdin);
            users[i].block[strcspn(users[i].block, "\n")] = '\0';

            printf("Digite a nova unidade do usuário: ");
            fgets(users[i].unit, MAX_UNIT_LENGTH, stdin);
            users[i].unit[strcspn(users[i].unit, "\n")] = '\0';

            FILE *fp;
            fp = fopen("users.txt", "r+");
            if (fp == NULL) {
                perror("Erro ao abrir o arquivo para atualização");
                return;
            }

            FILE *temp_fp;
            temp_fp = fopen("temp_users.txt", "w");
            if (temp_fp == NULL) {
                perror("Erro ao abrir o arquivo temporário para escrita");
                fclose(fp);
                return;
            }

            int file_id;
            char file_name[MAX_NAME_LENGTH];
            char file_block[MAX_BLOCK_LENGTH];
            char file_unit[MAX_UNIT_LENGTH];
            while (fscanf(fp, "%d;%[^;];%[^;];%[^\n]\n", &file_id, file_name, file_block, file_unit) != EOF) {
                if (file_id == id) {
                    fprintf(temp_fp, "%d;%s;%s;%s\n", id, users[i].name, users[i].block, users[i].unit);
                } else {
                    fprintf(temp_fp, "%d;%s;%s;%s\n", file_id, file_name, file_block, file_unit);
                }
            }

            fclose(fp);
            fclose(temp_fp);

            remove("users.txt");
            rename("temp_users.txt", "users.txt");

            printf("Usuário ID %d atualizado com sucesso.\n", id);
            break;
        }
    }

    if (!found) {
        printf("Usuário ID %d não encontrado.\n", id);
    }
}

void delete_user(User users[], int *user_count) {
    int id;
    printf("Digite o ID do usuário que deseja excluir: ");
    scanf("%d", &id);
    getchar(); // Limpar o buffer de entrada

    int found = 0;
    for (int i = 0; i < *user_count; ++i) {
        if (users[i].id == id) {
            found = 1;

            users[i].id = 0;
            strcpy(users[i].name, "");
            strcpy(users[i].block, "");
            strcpy(users[i].unit, "");

            FILE *fp;
            fp = fopen("users.txt", "r+");
            if (fp == NULL) {
                perror("Erro ao abrir o arquivo para exclusão");
                return;
            }

            FILE *temp_fp;
            temp_fp = fopen("temp_users.txt", "w");
            if (temp_fp == NULL) {
                perror("Erro ao abrir o arquivo temporário para escrita");
                fclose(fp);
                return;
            }

            int file_id;
            char file_name[MAX_NAME_LENGTH];
            char file_block[MAX_BLOCK_LENGTH];
            char file_unit[MAX_UNIT_LENGTH];
            while (fscanf(fp, "%d;%[^;];%[^;];%[^\n]\n", &file_id, file_name, file_block, file_unit) != EOF) {
                if (file_id != id) {
                    fprintf(temp_fp, "%d;%s;%s;%s\n", file_id, file_name, file_block, file_unit);
                }
            }

            fclose(fp);
            fclose(temp_fp);

            remove("users.txt");
            rename("temp_users.txt", "users.txt");

            printf("Usuário ID %d excluído com sucesso.\n", id);
            break;
        }
    }

    if (!found) {
        printf("Usuário ID %d não encontrado.\n", id);
    }
}
