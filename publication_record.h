#ifndef STRUCT_RECORD_H
#define STRUCT_RECORD_H

typedef struct {
    char title[256];
    char author_last_name[256];
    char author_initials[10];
    char journal_title[256];
    int publication_year;
    int journal_volume;
    int is_in_rinc; // 0 - NO, 1 - YES
    int page_count;
    int citation_count;
} PublicationRecord;
#endif 
