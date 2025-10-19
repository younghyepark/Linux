#include <stdio.h>     
#include <stdlib.h>     
#include <unistd.h>     
#include <sys/wait.h>   
#include <math.h>       
#define _USE_MATH_DEFINES
#define N 4

// 테일러 급수 계산 함수 (병렬)
void sinx_taylor(int num_elements, int terms, double* x, double* result) {
    int fd[num_elements][2];

    for (int i = 0; i < num_elements; i++) {
        pipe(fd[i]);  // 파이프 생성

        if (fork() == 0) {  // 자식 프로세스
            close(fd[i][0]); // 읽기 닫기

            double value = x[i];
            double numer = x[i]*x[i]*x[i];
            double denom = 6.0;
            int sign = -1;
            for (int j = 1; j <= terms; j++) {
                value += (double)sign * numer / denom;
                numer *= x[i]*x[i];
                denom *= (2.0*j + 2.0)*(2.0*j + 3.0);
                sign *= -1;
            }

            write(fd[i][1], &value, sizeof(double)); // 부모에게 전송
            close(fd[i][1]);
            exit(0); // 자식 종료
        } else {
            close(fd[i][1]); // 부모는 쓰기 닫기
        }
    }

    
    for (int i = 0; i < num_elements; i++) {
        wait(NULL); // 자식 종료 대기
        read(fd[i][0], &result[i], sizeof(double));
        close(fd[i][0]);
    }
}

int main() {
    double x[N] = {0, M_PI/6., M_PI/3., 0.134};
    double res[N];

    // 병렬 테일러 계산
    sinx_taylor(N, 3, x, res);

    // 출력
    for (int i = 0; i < N; i++) {
        printf("sin(%.2f) by Taylor series = %f\n", x[i], res[i]);
        printf("sin(%.2f) = %f\n", x[i], sin(x[i]));
    }

    return 0;
}

