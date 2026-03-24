#include <stdio.h>
#include <stdlib.h>

int main() {
    int size = 5;
    int *scores = (int *)malloc(size * sizeof(int));
    scores[0] = 80;
    scores[1] = 90;
    scores[2] = 75;
    scores[3] = 85;
    scores[4] = 95;
    for (int i = 2; i < size - 1; i++) {
        scores[i] = scores[i + 1];
    }
    size--;
    size += 2;
    scores = (int *)realloc(scores, size * sizeof(int));
    scores[size - 2] = 88;
    scores[size - 1] = 92;
    printf("최종 학생 성적:\n");
    for (int i = 0; i < size; i++) {
        printf("%d번: %d점\n", i + 1, scores[i]);
    }
    free(scores);
    return 0;
}