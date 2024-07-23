#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rfid.h"

void create_rfid_tag(RFIDTag tags[], int *tag_count) {
    RFIDTag new_tag;

    printf("Criando nova TAG RFID...\n");
    printf("Digite o ID do usuário associado: ");
    scanf("%d", &new_tag.user_id);
    getchar(); // Limpar o buffer de entrada

    printf("Digite o código da TAG RFID: ");
    fgets(new_tag.tag_code, MAX_LENGTH, stdin);
    new_tag.tag_code[strcspn(new_tag.tag_code, "\n")] = '\0';

    new_tag.id = (*tag_count) + 1;

    tags[*tag_count] = new_tag;
    (*tag_count)++;

    FILE *fp;
    fp = fopen("rfids.txt", "a");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return;
    }

    fprintf(fp, "%d;%d;%s\n", new_tag.id, new_tag.user_id, new_tag.tag_code);

    fclose(fp);

    printf("TAG RFID criada e salva no arquivo rfids.txt.\n");
}

void list_rfid_tags(RFIDTag tags[], int tag_count) {
    printf("\nLista de TAGs RFID:\n");

    FILE *fp;
    fp = fopen("rfids.txt", "r");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    int id;
    int user_id;
    char tag_code[MAX_LENGTH];

    while (fscanf(fp, "%d;%d;%[^\n]\n", &id, &user_id, tag_code) != EOF) {
        printf("ID: %d\n", id);
        printf("ID do usuário associado: %d\n", user_id);
        printf("Código da TAG RFID: %s\n", tag_code);
        printf("--------------------\n");
    }

    fclose(fp);
}

void update_rfid_tag(RFIDTag tags[], int tag_count) {
    int id;
    printf("Digite o ID da TAG RFID que deseja atualizar: ");
    scanf("%d", &id);
    getchar(); // Limpar o buffer de entrada

    int found = 0;
    for (int i = 0; i < tag_count; ++i) {
        if (tags[i].id == id) {
            found = 1;

            printf("Atualizando informações da TAG RFID ID %d:\n", id);

            printf("Digite o novo ID do usuário associado (ou pressione Enter para manter o mesmo): ");
            scanf("%d", &tags[i].user_id);
            getchar(); // Limpar o buffer de entrada

            printf("Digite o novo código da TAG RFID (ou pressione Enter para manter o mesmo): ");
            fgets(tags[i].tag_code, MAX_LENGTH, stdin);
            tags[i].tag_code[strcspn(tags[i].tag_code, "\n")] = '\0';

            FILE *fp;
            fp = fopen("rfids.txt", "r+");
            if (fp == NULL) {
                perror("Erro ao abrir o arquivo para atualização");
                return;
            }

            FILE *temp_fp;
            temp_fp = fopen("temp_rfids.txt", "w");
            if (temp_fp == NULL) {
                perror("Erro ao abrir o arquivo temporário para escrita");
                fclose(fp);
                return;
            }

            int file_id;
            int file_user_id;
            char file_tag_code[MAX_LENGTH];
            while (fscanf(fp, "%d;%d;%[^\n]\n", &file_id, &file_user_id, file_tag_code) != EOF) {
                if (file_id == id) {
                    fprintf(temp_fp, "%d;%d;%s\n", id, tags[i].user_id, tags[i].tag_code);
                } else {
                    fprintf(temp_fp, "%d;%d;%s\n", file_id, file_user_id, file_tag_code);
                }
            }

            fclose(fp);
            fclose(temp_fp);

            remove("rfids.txt");
            rename("temp_rfids.txt", "rfids.txt");

            printf("TAG RFID ID %d atualizada com sucesso.\n", id);
            break;
        }
    }

    if (!found) {
        printf("TAG RFID ID %d não encontrada.\n", id);
    }
}

void delete_rfid_tag(RFIDTag tags[], int *tag_count) {
    int id;
    printf("Digite o ID da TAG RFID que deseja excluir: ");
    scanf("%d", &id);
    getchar(); // Limpar o buffer de entrada

    int found = 0;
    for (int i = 0; i < *tag_count; ++i) {
        if (tags[i].id == id) {
            found = 1;

            tags[i].user_id = 0;
            strcpy(tags[i].tag_code, "");

            FILE *fp;
            fp = fopen("rfids.txt", "r+");
            if (fp == NULL) {
                perror("Erro ao abrir o arquivo para exclusão");
                return;
            }

            FILE *temp_fp;
            temp_fp = fopen("temp_rfids.txt", "w");
            if (temp_fp == NULL) {
                perror("Erro ao abrir o arquivo temporário para escrita");
                fclose(fp);
                return;
            }

            int file_id;
            int file_user_id;
            char file_tag_code[MAX_LENGTH];
            while (fscanf(fp, "%d;%d;%[^\n]\n", &file_id, &file_user_id, file_tag_code) != EOF) {
                if (file_id != id) {
                    fprintf(temp_fp, "%d;%d;%s\n", file_id, file_user_id, file_tag_code);
                }
            }

            fclose(fp);
            fclose(temp_fp);

            remove("rfids.txt");
            rename("temp_rfids.txt", "rfids.txt");

            printf("TAG RFID ID %d excluída com sucesso.\n", id);
            break;
        }
    }

    if (!found) {
        printf("TAG RFID ID %d não encontrada.\n", id);
    }
}
