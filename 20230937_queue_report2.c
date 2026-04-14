#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10  // 최대 작업 대기열 크기

// 프린터 작업 구조체
typedef struct {
    char documentName[50];
    int numPages;
} PrintJob;

typedef struct {
    PrintJob queue[SIZE];
    int front;
    int rear;
} PrintQueue;

// 초기화 함수
void initQueue(PrintQueue *q) {
    q->front = 0;
    q->rear = 0;
}

// 큐가 비어 있는지 확인
bool isEmpty(PrintQueue *q) {
    return q->front == q->rear;
}

// 큐가 가득 찼는지 확인
bool isFull(PrintQueue *q) {
    return (q->rear + 1) % SIZE == q->front;
}

// [개선과제 1] 작업 추가 함수 수정
bool enqueue(PrintQueue *q, char *documentName, int numPages) {
    // 1-b: 큐에 추가되기 전 검사
    // 1-a: 페이지 수가 50장을 초과하면 거부 메시지 출력
    if (numPages > 50) {
        printf("페이지 수가 50장을 초과하여 작업을 추가할 수 없습니다.\n");
        return false;
    }

    if (isFull(q)) {
        printf("대기열이 가득 찼습니다. 작업을 추가할 수 없습니다.\n");
        return false;
    }
    
    strcpy(q->queue[q->rear].documentName, documentName);
    q->queue[q->rear].numPages = numPages;
    q->rear = (q->rear + 1) % SIZE;
    printf("작업 '%s' (%d 페이지)가 대기열에 추가되었습니다.\n", documentName, numPages);
    return true;
}

// 작업 제거 함수
PrintJob dequeue(PrintQueue *q) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다. 작업이 없습니다.\n");
        PrintJob emptyJob = {"", 0};
        return emptyJob;
    }
    PrintJob job = q->queue[q->front];
    q->front = (q->front + 1) % SIZE;
    return job;
}

// [개선과제 2] 인쇄 취소 함수 추가
void cancelJob(PrintQueue *q, const char *documentName) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다.\n");
        return;
    }

    int i = q->front;
    bool found = false;

    // 2-a: 큐 내부를 순회하며 문서 검색
    while (i != q->rear) {
        if (strcmp(q->queue[i].documentName, documentName) == 0) {
            found = true;
            break;
        }
        i = (i + 1) % SIZE;
    }

    // 2-b: 문서 이름이 존재하지 않을 경우 메시지 출력
    if (!found) {
        printf("해당 문서가 없습니다\n");
        return;
    }

    // 2-c: 제거 작업 이후의 작업을 한 칸씩 앞으로 이동 (대기열 유지)
    int curr = i;
    int next = (curr + 1) % SIZE;
    while (next != q->rear) {
        q->queue[curr] = q->queue[next];
        curr = next;
        next = (next + 1) % SIZE;
    }
    q->rear = curr; // 마지막 작업을 앞으로 당겼으므로 rear 위치를 1 감소(순환 구조에 맞게)시킴

    printf("작업 '%s'이(가) 대기열에서 취소되었습니다.\n", documentName);
}

// [개선과제 3] 대기열 전체 비우기 함수 추가
void clearQueue(PrintQueue *q) {
    // 3-a, 3-b: 모든 작업을 초기 상태로 되돌림
    q->front = 0;
    q->rear = 0;
    
    // 3-c: 메시지 출력
    printf("대기열 초기화\n");
}

// 대기열 상태 출력 함수
void printQueue(PrintQueue *q) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다.\n");
        return;
    }
    printf("현재 대기 중인 작업:\n");
    int i = q->front;
    while (i != q->rear) {
        printf("- %s (%d 페이지)\n", q->queue[i].documentName, q->queue[i].numPages);
        i = (i + 1) % SIZE;
    }
}

int main() {
    PrintQueue q;
    initQueue(&q);

    int choice;
    char documentName[50];
    int numPages;

    while (true) {
        // 메뉴 구성 변경
        printf("\n1. 작업 추가\n2. 작업 처리\n3. 대기열 출력\n4. 인쇄 취소\n5. 대기열 전체 비우기\n6. 종료\n선택: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("문서 이름: ");
                scanf("%49s", documentName); 
                printf("페이지 수: ");
                scanf("%d", &numPages);
                enqueue(&q, documentName, numPages);
                break;
            case 2: { 
                PrintJob job = dequeue(&q);
                if (strlen(job.documentName) > 0) {
                    printf("작업 '%s' (%d 페이지)를 처리 중입니다...\n", job.documentName, job.numPages);
                }
                break;
            }
            case 3:
                printQueue(&q);
                break;
            case 4:
                printf("취소할 문서 이름: ");
                scanf("%49s", documentName);
                cancelJob(&q, documentName);
                break;
            case 5:
                clearQueue(&q);
                break;
            case 6:
                printf("프로그램을 종료합니다.\n");
                return 0;
            default:
                printf("잘못된 입력입니다. 다시 선택해 주세요.\n");
                break;
        }
    }
}