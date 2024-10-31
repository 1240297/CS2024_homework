#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

#define BUF_SIZE 5
#define TIMES 13

void *produce(void *param);
void *consume(void *param);

char buffer[BUF_SIZE];
sem_t *elements;
sem_t *spaces;
int array_index = 0;
int offset = 0;

// 生産者関数
void *produce(void *param) {
    int i;
    int sem_value;
    for(i = 0; i<TIMES; i++) {
        sleep(rand() % 5);
        sem_wait(spaces);
        buffer[array_index] = 'a' + offset++;
        array_index++;
        sem_post(elements);
 }
    pthread_exit(0);
}

// 消費者関数
void *consume(void *param) {
    int k;
    int sem_value;
    for(k = 0; k < TIMES * 2; k++) {
        sem_wait(elements);
        array_index--;
        printf("%c was consumed\n", buffer[array_index]);
        sleep(1);
        buffer[array_index] = '\0';
        sem_post(spaces);
    }
    pthread_exit(0);
}


int main(void) {
    sem_unlink("/elements");
    sem_unlink("/spaces");
    elements = sem_open(/*name = */"/elements", O_CREAT, /*mode=*/0644, /*init value=*/0);
    spaces   = sem_open(/*name = */"/spaces",   O_CREAT, /*mode=*/0644, /*init value=*/BUF_SIZE);
        
    if(elements == SEM_FAILED | spaces == SEM_FAILED) {
        perror("sem_open error\n");
        return 1;
    }
    
    pthread_t producer1, producer2, consumer;
    // スレッド作成
    pthread_create(&producer1, NULL, produce, NULL);
    pthread_create(&producer2, NULL, produce, NULL);
    pthread_create(&consumer,  NULL, consume, NULL);
    
    // スレッド待ち
    pthread_join(producer1, NULL);
    pthread_join(producer2, NULL);
    pthread_join(consumer,  NULL);

    // 終了
    sem_close(elements);
    sem_close(spaces);
    sem_unlink("/elements");
    sem_unlink("/spaces");
    
    return 0;
}

