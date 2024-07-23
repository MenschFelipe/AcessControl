#include <stdio.h>
#include "user.h"
#include "rfid.h"

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
    int option;

    do {
        print_menu();
        scanf("%d", &option);
        getchar();  // Limpar o buffer de entrada

        switch (option) {
            case 1:
                create_user(users, &user_count);
                break;
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
                create_rfid_tag(tags, &tag_count);
                break;
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
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (option != 9);

    return 0;
}
