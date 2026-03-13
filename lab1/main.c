#include <stdio.h>
#include <stdlib.h>

// 定義 Linked-list 節點
typedef struct Node {
    char ch;
    struct Node* next;
} Node;

// 宣告 Linked-list 的頭尾指標
Node* head = NULL;
Node* tail = NULL;

// 函式宣告
void process_char(char c);
void print_list();
void free_list();

int main() {
    // 依照簡報要求，讀取 main.c (即程式自己的原始碼)
    FILE *file = fopen("main.c", "r");
    if (file == NULL) {
        printf("無法開啟檔案！請確認檔案名稱是否為 main.c 且在同一個目錄下。\n");
        return 1;
    }

    int c;
    // 逐字元讀取，包含空白、換行與 Tab，直到檔案結束 (EOF)
    while ((c = fgetc(file)) != EOF) {
        process_char((char)c);
    }

    fclose(file);

    // 必須從 link-list 把每一個 char 輸出
    print_list();

    // 釋放記憶體，養成良好習慣
    free_list();

    return 0;
}

// 將讀取到的字元加入 Linked-list 尾端，保持原始字元流 (Character Stream) 的順序
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

// 從 Linked-list 依序印出字元
void print_list() {
    Node* current = head;
    while (current != NULL) {
        // 依照圖片的格式輸出特殊字元
        if (current->ch == '\n') {
            printf("'\\n' ");
        } else if (current->ch == '\t') {
            printf("'\\t' ");
        } else if (current->ch == ' ') {
            // 圖片中空白字元有時以底線或開口方塊表示，這裡使用標準空白。
            // 若助教嚴格要求看見空白符號，可改成 printf("'_' "); 或 printf("'␣' ");
            printf("' ' "); 
        } else {
            printf("'%c' ", current->ch);
        }
        current = current->next;
    }
    printf("\n");
}

// 清除 Linked-list 釋放記憶體
void free_list() {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}
