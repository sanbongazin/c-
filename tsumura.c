#include <stdio.h>
#include <stdlib.h>

// 構造体宣言。データーを一つの組みにしていくクラスと同じような働き

typedef struct CELL{
    int data; 
    struct CELL *next;//メモリの使い方が試験向けというか・・
}CELL;

// 一つ目の関数。データーを格納して、配列に格納している。
CELL * CELL_alloc (int data){
    CELL *p = malloc (sizeof (CELL));//動的なメモリの確保
    p -> data = data; 
    p -> next = NULL; 
    return p;//この書き方嫌い。なので改行して読みやすく
}

CELL * insert1 (CELL *head, int data){
    CELL *new = CELL_alloc(data);//headはNULL,10だとすれば。
    CELL *p = head; //NULL
    if(p == NULL || p-> next -> data > data){//先頭に挿入する条件
        new -> next = p;//nextは、次の構造体を指している。先頭に挿入。
        return new;
    }else{
        while(p != NULL && data < p-> next ->data){
            p = p->next;//次の構造体に代入している。
        }
        new -> next = p -> next; 
        p -> next = new;
        return head;
    }
}

int main (){
    CELL *head = NULL;
    
    head = insert1 (head, 10);//コンストラクタ実行のように振る舞う。
    // printf(head);
    head = insert1 (head, 30);
    head = insert1 (head, 20);
    }