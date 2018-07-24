#include <stdio.h>
#include <stdlib.h>

// コンパイルしないと反映されないことに注意
// 構造体宣言。データーを一つの組みにしていくクラスと同じような働き
int i = 0;
int answer[4];

typedef struct CELL {
	int data;
	struct CELL *next;//メモリの使い方が試験向けというか・・
}CELL;

// 一つ目の関数。データーを格納して、配列に格納している。
CELL * CELL_alloc(int data) {
	CELL *p = malloc(sizeof(CELL));//動的なメモリの確保
	p->data = data;
	p->next = NULL;
	return p;//この書き方嫌い。なので改行して読みやすく
}

CELL * insert1(CELL *head, int data) {
	CELL *new = CELL_alloc(data);//headはNULL,10だとすれば。
	CELL *p = head; //NULL
	i++;
	if (p == NULL || data < p->data) {//先頭に挿入する条件
		new->next = p;//nextは、次の構造体を指している。先頭に挿入。
		answer[i] = data;
		return new;
	}
	else {
		while (p != NULL && p->next) {
			p = p->next;//次の構造体に代入している。
			answer[i] = data;
		}
		new->next = p->next;
		p->next = new;
		answer[i] = data;
		return head;
	}
}

void insert2(CELL **head_p, int data){
	CELL *new = CELL_alloc(data);
	CELL **p = head_p;
	while(&&){
		p = (*p) -> next;
	}
	new -> next = *p;
	*p = new;
}

int main() {
	CELL *head = NULL;

	head = insert1(head, 10);//コンストラクタ実行のように振る舞う。
	head = insert1(head, 30);
	head = insert1(head, 20);

	int c = 0;
	for (c = 0; c < 4; c++) {
		printf("%d\n",answer[c]);
	}
}
