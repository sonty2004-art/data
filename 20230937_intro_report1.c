#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    int score[10];
    int sum = 0;
    float avg = 0;
    int i; 
    srand(time(NULL));
    for (i = 0; i < 10; i++) {
        score[i] = rand() % 101; 
    }
    for (i = 0; i < 10; i++) {
        printf("%d번 학생 점수: %d\n", i + 1, score[i]);
        sum = sum + score[i]; 
    }
    avg = sum / 10.0; 
    printf("------------------------\n");
    printf("전체 합계: %d\n", sum);
    printf("평균 점수: %f\n", avg); 
    return 0;
}