#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 기존 함수 선언
double calculateAverage(int scores[], int size);
int getStudentScore(int scores[], int size, int studentNumber);

// 추가된 실습 과제 함수 선언
void printScore(int scores[], int size, double average, int option);

int main() {
    int scores[30]; // 30명의 학생 성적 저장
    int studentNumber;
    double average;

    // 난수 생성 초기화
    srand(time(0));

    // 성적 데이터 초기화
    for (int i = 0; i < 30; i++) {
        scores[i] = rand() % 101; // 0 ~ 100 사이의 난수 생성
    }

    // 평균 계산
    average = calculateAverage(scores, 30);
    printf("학급 평균 점수: %.2f\n\n", average);

    // [테스트] printScore 함수 호출
    printf("--- 전체 학생 성적 (옵션 0) ---\n");
    printScore(scores, 30, average, 0);
    
    printf("\n--- 평균 이상 학생 (옵션 1) ---\n");
    printScore(scores, 30, average, 1);
    
    printf("\n--- 평균 미만 학생 (옵션 2) ---\n");
    printScore(scores, 30, average, 2);

    // 특정 학생 점수 검색
    printf("\n학생 번호를 입력하세요 (1 ~ 30): ");
    scanf("%d", &studentNumber);

    int score = getStudentScore(scores, 30, studentNumber);
    if (score != -1) {
        printf("%d번 학생의 점수: %d\n", studentNumber, score);
    } else {
        printf("유효하지 않은 학생 번호입니다.\n");
    }

    return 0;
}

// 평균 계산 함수
double calculateAverage(int scores[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += scores[i];
    }
    return sum / (double)size;
}

// 특정 학생 점수 검색 함수
int getStudentScore(int scores[], int size, int studentNumber) {
    if (studentNumber >= 1 && studentNumber <= size) {
        return scores[studentNumber - 1];
    } else {
        return -1; // 유효하지 않은 학생 번호
    }
}

// 조건에 따른 학생 정보 출력 함수 구현
void printScore(int scores[], int size, double average, int option) {
    for (int i = 0; i < size; i++) {
        if (option == 0) {
            // 모든 학생 출력
            printf("%d번: %d점\n", i + 1, scores[i]);
        } else if (option == 1 && scores[i] >= average) {
            // 평균 이상 학생 출력
            printf("%d번: %d점\n", i + 1, scores[i]);
        } else if (option == 2 && scores[i] < average) {
            // 평균 미만 학생 출력
            printf("%d번: %d점\n", i + 1, scores[i]);
        }
    }
}