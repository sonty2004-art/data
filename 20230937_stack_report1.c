#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int *data;
    int top;
    int capacity;
} Stack;
void initStack(Stack *s, int initialSize) {
    s->data = (int *)malloc(initialSize * sizeof(int));
    if (s->data == NULL) {
        printf("메모리 할당 실패!\n");
        exit(1);
    }
    s->top = -1;
    s->capacity = initialSize;
}
int isEmpty(Stack *s) {
    return s->top == -1;
}
int isFull(Stack *s) {
    return s->top == s->capacity - 1;
}
void expandStack(Stack *s) {
    int newCapacity = s->capacity + 5;
    int *newData = (int *)realloc(s->data, newCapacity * sizeof(int));
    if (newData == NULL) {
        printf("메모리 재할당 실패!\n");
        exit(1);
    }
    s->data = newData;
    s->capacity = newCapacity;
}
void push(Stack *s, int value) {
    if (isFull(s)) {
        expandStack(s);
    }
    s->data[++(s->top)] = value;
}
int pop(Stack *s) {
    if (isEmpty(s)) {
        return -1;
    }
    return s->data[(s->top)--];
}
int peek(Stack *s) {
    if (isEmpty(s)) {
        return -1;
    }
    return s->data[s->top];
}
void freeStack(Stack *s) {
    free(s->data);
}
int main() {
    Stack s;
    char str[101]; 
    initStack(&s, 100);
    printf("문자열을 입력하세요: ");
    scanf("%100[^\n]", str);
    for (int i = 0; str[i] != '\0'; i++) {
        push(&s, str[i]);
    }
    printf("거꾸로 출력된 문자열: ");
    while (!isEmpty(&s)) {
        printf("%c", pop(&s));
    }
    printf("\n");
    freeStack(&s);
    return 0;
}
