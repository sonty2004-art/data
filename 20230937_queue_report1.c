#include <stdio.h>
#include <stdbool.h>

// 1. 큐의 크기를 30으로 변경
#define SIZE 30  

typedef struct {
    int data[SIZE];  // 고정된 크기의 배열
    int front;  // 큐의 첫 번째 요소 인덱스
    int rear;   // 큐의 마지막 요소 인덱스
} LinearQueue;

// 초기화 함수
void initQueue(LinearQueue *q) {
    q->front = 0;
    q->rear = -1;  // rear를 -1로 설정하여 첫 번째 삽입 시 0이 되도록 함
}

// 큐가 비어 있는지 확인
bool isEmpty(LinearQueue *q) {
    return q->rear < q->front;  // rear가 front보다 작으면 비어 있음
}

// 큐가 가득 찼는지 확인
bool isFull(LinearQueue *q) {
    return q->rear == SIZE - 1;  // rear가 배열 끝에 도달하면 가득 참
}

// 삽입 함수
bool enqueue(LinearQueue *q, int value) {
    if (isFull(q)) {
        printf("큐가 가득 찼습니다.\n");
        return false;
    }
    q->rear++;
    q->data[q->rear] = value;  // rear 위치에 데이터 추가
    return true;
}

// 삭제 함수
int dequeue(LinearQueue *q) {
    if (isEmpty(q)) {
        printf("큐가 비어 있습니다.\n");
        return -1;  // 큐가 비어 있을 때 -1 반환
    }
    int value = q->data[q->front];
    q->front++;
    
    // 2. 큐가 비었을 경우 큐를 초기화하는 코드 추가
    if (isEmpty(q)) {
        initQueue(q);
    }
    
    return value;
}

// 3. 큐의 현재 상태를 출력하는 함수 추가
void printQueue(LinearQueue *q) {
    if (isEmpty(q)) {
        printf("큐가 비어 있습니다.\n");
        return;
    }
    printf("큐 데이터: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->data[i]);
    }
    printf("\n");
}

// 4. 메뉴를 통한 사용자 입력 처리 구현
int main() {
    LinearQueue q;
    initQueue(&q);
    int choice, value;

    while (true) {
        printf("\n1. 삽입  2. 삭제  3. 큐 데이터 출력  4. 종료\n");
        printf("메뉴 선택: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("삽입할 데이터: ");
                scanf("%d", &value);
                enqueue(&q, value);
                break;
            case 2:
                value = dequeue(&q);
                if (value != -1) {
                    printf("삭제된 데이터: %d\n", value);
                }
                break;
            case 3:
                printQueue(&q);
                break;
            case 4:
                return 0;
            default:
                printf("잘못된 입력입니다.\n");
        }
    }
    return 0;
}