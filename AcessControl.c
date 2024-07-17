#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 200     // Definir o máximo de usuários
#define MAX_TAGS 500      // Definir o máximo de tags RFID
#define MAX_LENGTH 100    // Definir o tamanho máximo para strings

// Estrutura user
typedef struct {
    int id;
    char name[MAX_LENGTH];
    char email[MAX_LENGTH];
} User;

// Estrutura RFID
typedef struct {
    int id;
    char tag_code[MAX_LENGTH];
} RFIDTag;

// Print menu
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

// Função para criar um novo usuário
void create_user(User users[], int *user_count) {
    User new_user;
    printf("Criando novo usuário...\n");

    // Capturar informações do novo usuário
    printf("Digite o nome do usuário: ");
    fgets(new_user.name, MAX_LENGTH, stdin);
    new_user.name[strcspn(new_user.name, "\n")] = '\0'; 
    printf("Digite o e-mail do usuário: ");
    fgets(new_user.email, MAX_LENGTH, stdin);
    new_user.email[strcspn(new_user.email, "\n")] = '\0'; 

    // Abrir arquivo para leitura do último ID
    FILE *fp;
    fp = fopen("usuarios.txt", "r");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        return;
    }

    // Variáveis para leitura dos dados do arquivo
    char line[MAX_LENGTH];
    int last_id = 0;

    // Ler até o final do arquivo para obter o último ID
    while (fgets(line, sizeof(line), fp) != NULL) {
        int id;
        sscanf(line, "%d;", &id);
        if (id > last_id) {
            last_id = id;
        }
    }

    
    fclose(fp);

    // Definir o ID do novo usuário
    new_user.id = last_id + 1;

    // Adicionar o novo usuário ao array
    users[*user_count] = new_user;
    (*user_count)++; // Incrementar o contador de usuários

    //Salvar no arquvio
    fp = fopen("usuarios.txt", "a");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return;
    }

    // Escrever dados do novo usuário no arquivo em uma nova linha
    fprintf(fp, "%d;%s;%s\n", new_user.id, new_user.name, new_user.email);

    // Fechar o arquivo
    fclose(fp);

    printf("Usuário criado e salvo no arquivo usuarios.txt.\n");
}

// Função para listar todos os usuários
void list_users(User users[], int user_count) {
       printf("\nLista de Usuários:\n");

    // Abrir arquivo para leitura
    FILE *fp;
    fp = fopen("usuarios.txt", "r");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    // Variáveis para leitura dos dados do arquivo
    char line[MAX_LENGTH];
    int id;
    char name[MAX_LENGTH];
    char email[MAX_LENGTH];

    // Ler e exibir cada linha do arquivo
    while (fgets(line, sizeof(line), fp) != NULL) {
        // Extrair dados da linha usando strtok
        char *token = strtok(line, ";");
        if (token != NULL) {
            id = atoi(token);
            token = strtok(NULL, ";");
            if (token != NULL) {
                strcpy(name, token);
                token = strtok(NULL, ";");
                if (token != NULL) {
                    strcpy(email, token);

                    // Exibir os dados do usuário
                    printf("ID: %d\n", id);
                    printf("Nome: %s\n", name);
                    printf("E-mail: %s\n", email);
                    printf("--------------------\n");
                }
            }
        }
    }

    // Fechar o arquivo
    fclose(fp);
}


// Função para atualizar um usuário existente
void update_user(User users[], int user_count) {
    // construction
}

// Função para deletar um usuário existente
void delete_user(User users[], int *user_count) {
    //construction
}

// Função para criar uma nova tag RFID
void create_rfid_tag(RFIDTag tags[], int *tag_count) {
    // construction
}

// Função para listar todas as tags RFID
void list_rfid_tags(RFIDTag tags[], int tag_count) {
    // construction
}

// Função para atualizar uma tag RFID existente
void update_rfid_tag(RFIDTag tags[], int tag_count) {

    // construction
}
// Função para deletar uma tag RFID existente
void delete_rfid_tag(RFIDTag tags[], int *tag_count) {
    // construction
}

int main() {
    User users[MAX_USERS];      // Array para armazenar os usuários
    RFIDTag tags[MAX_TAGS];     // Array para armazenar as tags RFID
    int user_count = 0;         // Contador de usuários
    int tag_count = 0;          // Contador de tags RFID
    int option;                 // Opção escolhida pelo usuário

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
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (option != 9);

    return 0;
}