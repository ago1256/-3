#ifndef STRUCT_CONTAINER_H
#define STRUCT_CONTAINER_H
#include "publication_record.h"

typedef struct Node {
    PublicationRecord record;
    struct Node* next;
} Node;

typedef struct {
    Node* top; // Указатель на верхний элемент стека
    int size;  // Количество элементов в стеке
} PublicationStack;
// Инициализация
void init_stack(PublicationStack* stack);
// Получение текущего размера
int get_size(PublicationStack* stack);
// Получение элемента по индексу
PublicationRecord get_element_at(PublicationStack* stack, int index);
// Получение указателя на верхний элемент
Node* get_head(PublicationStack* stack);
// Получение указателя на последний элемент
Node* get_tail(PublicationStack* stack);
// Получение следующего элемента от указателя
Node* get_next(Node* node);
// Получение предыдущего элемента от указателя
Node* get_prev(PublicationStack* stack, Node* node);
// Добавление элемента в начало стека
void insert_at_beginning(PublicationStack* stack, PublicationRecord record);
// Добавление элемента в конец стека
void insert_at_end(PublicationStack* stack, PublicationRecord record);
// Добавление элемента по индексу
void insert_at_index(PublicationStack* stack, PublicationRecord record, int index);
// Удаление элемента из начала стека
void remove_from_beginning(PublicationStack* stack);
// Удаление элемента из конца стека
void remove_from_end(PublicationStack* stack);
// Удаление элемента по индексу
void remove_at_index(PublicationStack* stack, int index);
// Замена пары элементов по индексам
void swap_elements(PublicationStack* stack, int index1, int index2);
// Преобразование массива в стек
PublicationStack array_to_stack(PublicationRecord* array, int size);
// Преобразование стека в массив
PublicationRecord* stack_to_array(PublicationStack* stack);
// Очистка
void clear_stack(PublicationStack* stack);

#endif 
