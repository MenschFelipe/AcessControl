// user.h
#ifndef USER_H
#define USER_H

#define MAX_NAME_LENGTH 100
#define MAX_BLOCK_LENGTH 50
#define MAX_UNIT_LENGTH 50
#define MAX_USERS 100

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char block[MAX_BLOCK_LENGTH];
    char unit[MAX_UNIT_LENGTH];
} User;

void create_user(User users[], int *user_count, int *next_user_id);
void list_users(User users[], int user_count);
void update_user(User users[], int user_count);
void delete_user(User users[], int *user_count);
int user_exists(User users[], int user_count, int user_id);

#endif // USER_H
