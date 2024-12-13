#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 1000
#define MAX_FIELDS 9
#include "publication_record.h"
#include "publication_stack.h"

void init_stack(PublicationStack* stack) {
    stack->top = NULL;
    stack->size = 0;
}

// Получение текущего размера
int get_size(PublicationStack* stack) {
    return stack->size;
}

// Получение произвольного элемента по индексу
PublicationRecord get_element_at(PublicationStack* stack, int index) {
    Node* current = stack->top;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->record;
}

// Получение указателя на начало (верх стека)
Node* get_head(PublicationStack* stack) {
    return stack->top; 
}

// Получение указателя на конец
Node* get_tail(PublicationStack* stack) {
    Node* current = stack->top;
    while (current->next != NULL) {
        current = current->next; 
    }
    return current; 
}

// Получение следующего элемента от указателя
Node* get_next(Node* node) {
    return node ? node->next : NULL; 
}

// Получение предыдущего элемента от указателя
Node* get_prev(PublicationStack* stack, Node* node) {
    if (node == NULL || stack->top == NULL) return NULL;

    Node* current = stack->top;
    while (current && current->next != node) {
        current = current->next;
    }
    return current;
}

// Добавление элемента в начало
void insert_at_beginning(PublicationStack* stack, PublicationRecord record) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->record = record;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
}

// Добавление элемента в конец
void insert_at_end(PublicationStack* stack, PublicationRecord record) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->record = record;
    new_node->next = NULL;

    if (stack->top == NULL) {
        stack->top = new_node;
    } else {
        Node* tail = get_tail(stack);
        tail->next = new_node;
    }
    stack->size++;
}

// Добавление элемента в произвольное место
void insert_at_index(PublicationStack* stack, PublicationRecord record, int index) {
    if (index == 0) {
        insert_at_beginning(stack, record);
        return;
    }
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->record = record;

    Node* current = stack->top;
    for (int i = 0; i < index - 1; i++) {
        current = current->next; 
    }
    
    new_node->next = current->next;
    current->next = new_node;
    stack->size++;
}

// Удаление элемента из начала
void remove_from_beginning(PublicationStack* stack) {
    Node* temp = stack->top;
    stack->top = stack->top->next;
    free(temp); 
    stack->size--;
}

// Удаление элемента из конца
void remove_from_end(PublicationStack* stack) {
    if (stack->size == 1) {
        free(stack->top); 
        stack->top = NULL;
    } else {
        Node* second_last = stack->top;
        while (second_last->next && second_last->next->next) {
            second_last = second_last->next;
        }
        free(second_last->next);
        second_last->next = NULL;
    }
    stack->size--;
}

// Удаление элемента по индексу
void remove_at_index(PublicationStack* stack, int index) {
    if (index == 0) {
        remove_from_beginning(stack);
        return;
    }

    Node* current = stack->top;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }

    Node* to_remove = current->next; 
    current->next = to_remove->next; 
    free(to_remove); 
    stack->size--;
}

void swap_elements(PublicationStack* stack, int index1, int index2) {
    PublicationRecord record1 = get_element_at(stack, index1);
    PublicationRecord record2 = get_element_at(stack, index2);
    remove_at_index(stack, index1); 
    if (index2 > index1) {
        index2--; 
    }
    remove_at_index(stack, index2); 
    insert_at_index(stack, record1, index2); 
    insert_at_index(stack, record2, index1); 
}

// Преобразование массива в структуру-контейнер
PublicationStack array_to_stack(PublicationRecord* array, int size) {
    PublicationStack stack;
    init_stack(&stack);
    
    for (int i = 0; i < size; i++) {
        insert_at_end(&stack, array[i]);
    }
    
    return stack;
}

// Преобразование структуры-контейнера в массив
PublicationRecord* stack_to_array(PublicationStack* stack) {
    PublicationRecord* array = (PublicationRecord*)malloc(stack->size * sizeof(PublicationRecord));
    
    Node* current = stack->top;
    for (int i = 0; i < stack->size; i++) {
        array[i] = current->record;
        current = current->next;
    }
    
    return array;
}

// Очистка стека
void clear_stack(PublicationStack* stack) {
    while (stack->size > 0) {
        remove_from_beginning(stack);
    }
}


//вывести стек
void print_stack(PublicationStack* stack) {
       Node* current = stack->top;
       while (current) {
           PublicationRecord rec = current->record;
           printf("%s, %s, %s, %s, %d, %d, %d, %d, %d\n",
                  rec.title,
                  rec.author_last_name,
                  rec.author_initials,
                  rec.journal_title,
                  rec.publication_year,
                  rec.journal_volume,
                  rec.is_in_rinc,
                  rec.page_count,
                  rec.citation_count);
           current = current->next;
       }
   }

//инвертировать стек
/*void reverse_stack(PublicationStack *stack) {
    if (stack->top == NULL) return; 

    PublicationStack temp;
    init_stack(&temp);

    while (get_size(stack) > 0) {
        PublicationRecord pub;
        pub = get_element_at(stack,0);
        remove_from_beginning(stack);
        insert_at_beginning(&temp, pub);
    }

    while (get_size(&temp) > 0) {
        PublicationRecord pub1;
        pub1 = get_element_at(&temp,0);
        remove_from_beginning(&temp);
        insert_at_beginning(stack, pub1);
    }
   if (get_size(stack) > 0){
    PublicationRecord pub = get_element_at(stack,0);
    reverse_stack(stack);
    insert_at_end(stack,pub);
   }

    //free(temp.top);
}*/


void print_help() {
    printf("  --generate N | -g N\n");
    printf("  --sort | -s --in=data.csv --out=output.csv --type=asc|desc\n");
    printf("  --print | -P --in=data.csv --out=output.txt\n");
}

void shaker_sort(PublicationStack* stack) {
    int swapped;
    PublicationRecord last, current;
    do {
        swapped = 0;
        last = get_element_at(stack, 0);
        for (int i = 0; i < get_size(stack) - 1; i++) {
            current = get_element_at(stack, i + 1);
              if (current.publication_year<last.publication_year) {
                swap_elements(stack, i, i + 1);
                swapped = 1;
            } else {
                last = current;
            }
        }
        if (!swapped) break;
        last = get_element_at(stack, get_size(stack) - 1);
        for (int i = get_size(stack) - 2; i >= 0; i--) {
            current = get_element_at(stack, i);
             if (current.publication_year>last.publication_year) {
                swap_elements(stack, i, i + 1);
                swapped = 1;
            } else {
                last = current; 
            }
        }

    } while (swapped);
}

void shaker_sort_reverse(PublicationStack* stack) {
    int swapped;
    PublicationRecord last, current;
    do {
        swapped = 0;
        last = get_element_at(stack, 0);
        for (int i = 0; i < get_size(stack) - 1; i++) {
            current = get_element_at(stack, i + 1);
              if (current.publication_year>last.publication_year) {
                swap_elements(stack, i, i + 1);
                swapped = 1;
            } else {
                last = current;
            }
        }
        if (!swapped) break;
        last = get_element_at(stack, get_size(stack) - 1);
        for (int i = get_size(stack) - 2; i >= 0; i--) {
            current = get_element_at(stack, i);
             if (current.publication_year<last.publication_year) {
                swap_elements(stack, i, i + 1);
                swapped = 1;
            } else {
                last = current; 
            }
        }

    } while (swapped);
}
void generate_random_string(char *str, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < length; i++) {
        str[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    str[length] = '0';
}
void generate_data(int n, const char *output_file) {
    FILE *file = output_file ? fopen(output_file, "w") : stdout;
    if (!file) {
        perror("Error opening file");
        return;
    }
    for (int i = 0; i < n; i++) {
        PublicationRecord pub;
        generate_random_string(pub.title, 20);
        generate_random_string(pub.author_last_name, 10);
        generate_random_string(pub.author_initials, 5);
        generate_random_string(pub.journal_title, 15);
        pub.publication_year = 2000 + rand() % 24;
        pub.journal_volume = rand() % 10 + 1;
        pub.is_in_rinc = rand() % 2;
        pub.page_count = rand() % 100 + 1; 
        pub.citation_count = rand() % 100;

        fprintf(file, "%s,%s,%s,%s,%d,%d,%d,%d,%d\n",
                pub.title,
                pub.author_last_name,
                pub.author_initials,
                pub.journal_title,
                pub.publication_year,
                pub.journal_volume,
                pub.is_in_rinc,
                pub.page_count,
                pub.citation_count);
    }

    if (output_file) fclose(file);
}

// Функция для сортировки данных по году выпуска
void sort_data(const char *input_file, const char *output_file, int ascending) {
    FILE *file = input_file ? fopen(input_file, "r") : stdin;

    PublicationStack A;
    init_stack(&A);
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        PublicationRecord pub;
        line[strcspn(line, "\n")] = 0;
        char *token = strtok(line, ",");
        if (token) strncpy(pub.title, token, sizeof(pub.title));
        token = strtok(NULL, ",");
        if (token) strncpy(pub.author_last_name, token, sizeof(pub.author_last_name));
        token = strtok(NULL, ",");
        if (token) strncpy(pub.author_initials, token, sizeof(pub.author_initials));
        token = strtok(NULL, ",");
        if (token) strncpy(pub.journal_title, token, sizeof(pub.journal_title));
        token = strtok(NULL, ",");
        if (token) pub.publication_year = atoi(token);
        token = strtok(NULL, ",");
        if (token) pub.journal_volume = atoi(token);
        token = strtok(NULL, ",");
        if (token) pub.is_in_rinc = atoi(token);
        token = strtok(NULL, ",");
        if (token) pub.page_count = atoi(token);
        token = strtok(NULL, ",");
        if (token) pub.citation_count = atoi(token);
        insert_at_beginning(&A, pub);
    }
    fclose(file);
    shaker_sort_reverse(&A);
    //if (ascending == 0) {
    //}

    file = output_file ? fopen(output_file, "w") : stdout;
    if (!file) {
        perror("Error opening output file");
        return;
    }

    for (int i = 0; i < get_size(&A); i++) {
        stack_to_array(&A);
        PublicationRecord B;
        B = get_element_at(&A,i);
        fprintf(file, "%s,%s,%s,%s,%d,%d,%d,%d,%d\n",
                B.title,
                B.author_last_name,
                B.author_initials,
                B.journal_title,
                B.publication_year,
                B.journal_volume,
                B.is_in_rinc,
                B.page_count,
                B.citation_count);
    }
    free(A.top);
    fclose(file);
}

void print_data(const char *input_file, const char *output_file) {
    FILE *file = input_file ? fopen(input_file, "r") : stdin;
    if (!file) {
        perror("Error opening input file");
        return;
    }
    
    FILE *out_file = output_file ? fopen(output_file, "w") : stdout;
    fprintf(out_file, "%-20s %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s\n",
            "Title", "Author last name", "Initials", "Journal Title", "Year",
            "Volume", "In RINC", "Pages", "Citations");

    char line[MAX_LINE_LENGTH];
    PublicationRecord pub;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        char *token = strtok(line, ",");
        if (token) strncpy(pub.title, token, sizeof(pub.title));
        token = strtok(NULL, ",");
        if (token) strncpy(pub.author_last_name, token, sizeof(pub.author_last_name));
        token = strtok(NULL, ",");
        if (token) strncpy(pub.author_initials, token, sizeof(pub.author_initials));
        token = strtok(NULL, ",");
        if (token) strncpy(pub.journal_title, token, sizeof(pub.journal_title));
        token = strtok(NULL, ",");
        if (token) pub.publication_year = atoi(token);
        token = strtok(NULL, ",");
        if (token) pub.journal_volume = atoi(token);
        token = strtok(NULL, ",");
        if (token) pub.is_in_rinc = atoi(token);
        token = strtok(NULL, ",");
        if (token) pub.page_count = atoi(token);
        token = strtok(NULL, ",");
        if (token) pub.citation_count = atoi(token);

        fprintf(out_file, "%-20s %-20s %-10s %-20s %-10d %-10d %-10d %-10d %-10d\n",
                pub.title,
                pub.author_last_name,
                pub.author_initials,
                pub.journal_title,
                pub.publication_year,
                pub.journal_volume,
                pub.is_in_rinc,
                pub.page_count,
                pub.citation_count);
    }

    fclose(file);
    if (output_file) fclose(out_file);
}


