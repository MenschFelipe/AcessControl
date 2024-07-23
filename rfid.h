#ifndef RFID_H
#define RFID_H

#define MAX_TAGS 500
#define MAX_LENGTH 100

typedef struct {
    int id;
    int user_id;
    char tag_code[MAX_LENGTH];
} RFIDTag;

void create_rfid_tag(RFIDTag tags[], int *tag_count);
void list_rfid_tags(RFIDTag tags[], int tag_count);
void update_rfid_tag(RFIDTag tags[], int tag_count);
void delete_rfid_tag(RFIDTag tags[], int *tag_count);

#endif /* RFID_H */
