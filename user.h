#ifndef USER_H
#define USER_H

#define MAX_USERS 500
#define MAX_NAME_LENGTH 100
#define MAX_BLOCK_LENGTH 20
#define MAX_UNIT_LENGTH 10

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char block[MAX_BLOCK_LENGTH];
    char unit[MAX_UNIT_LENGTH];
} User;

void create_user(User users[], int *user_count);
void list_users(User users[], int user_count);
void update_user(User users[], int user_count);
void delete_user(User users[], int *user_count);

#endif /* USER_H */
