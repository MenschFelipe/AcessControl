#ifndef RFID_H
#define RFID_H

#include "user.h"

#define MAX_TAGS 100
#define MAX_LENGTH 100

typedef struct {
    int id;
    int user_id;
    char tag_code[MAX_LENGTH];
} RFIDTag;

void create_rfid_tag(RFIDTag tags[], int *tag_count, User users[], int user_count);
void list_rfid_tags(RFIDTag tags[], int tag_count);
void update_rfid_tag(RFIDTag tags[], int tag_count);
void delete_rfid_tag(RFIDTag tags[], int *tag_count);
int is_hex_string(const char *str);

#endif // RFID_H
