#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

void *func1(void *param);
void *func2(void *param);
int counter = 0;
sem_t *sem;

int main(void) {
 sem = sem_open(/*name = */"/sem", O_CREAT | O_EXCL, /*mode=*/0644, /*init value=*/1);
    if(sem == SEM_FAILED) {
        perror("sem_open error\n");
        return 1;
    }
    
    pthread_t tid1, tid2;
    // スレッド作成
    pthread_create(&tid1, NULL, func1, NULL);
    pthread_create(&tid2, NULL, func2, NULL);
    // スレッド待機
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    sem_close(sem);
    sem_unlink("/sem");
    return 0;
}

// 3加算する関数
void *func1(void *param) {
    int i, tmp;
    for(i = 0; i<10; i++) {
        sleep(rand() % 4);
        sem_wait(sem);
        tmp = counter;
        tmp = tmp + 3;
        counter = tmp;
        printf("\n i = %d counter->%d", i, counter);
        sem_post(sem);
 }
    pthread_exit(0);
}

// 5加算する関数
void *func2(void *param) {
    int k, tmp;
    for(k = 0; k < 10; k++) {
        sleep(rand() % 4);
        sem_wait(sem);
        tmp = counter;
        tmp = tmp + 5;
        counter = tmp;
        printf("\n k = %d counter->%d", k, counter);
        sem_post(sem);
    }
    pthread_exit(0);
}