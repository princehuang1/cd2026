#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char ch;
    struct Node* next;
} Node;

Node* head = NULL;
Node* tail = NULL;

void process_char(char c);
void print_list();
void free_list();

int main() {
    FILE *file = fopen("main.c", "r");
    if (file == NULL) {
        printf("無法開啟檔案 main.c！\n");
        return 1;
    }

    int c;
    while ((c = fgetc(file)) != EOF) {
        process_char((char)c);
    }

    fclose(file);
    print_list();
    printf("\n"); 
    
    free_list();

    return 0;
}

void process_char(char c) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("記憶體配置失敗！\n");
        exit(1);
    }
    new_node->ch = c;
    new_node->next = NULL;

    if (head == NULL) {
        head = new_node;
        tail = new_node;
    } else {
        tail->next = new_node;
        tail = new_node;
    }
}

void print_list() {
    Node* current = head;
    while (current != NULL) {
        if (current->ch == '\n') {
            printf("'\\n' ");
        } else if (current->ch == '\t') {
            printf("'\\t' ");
        } else if (current->ch == ' ') {
            printf("' ' "); 
        } else {
            printf("'%c' ", current->ch);
        }
        current = current->next;
    }
}

void free_list() {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}
