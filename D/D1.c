#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void *func(void *param);
sem_t *sem;
char buf[256];

int main() {
    pthread_t tid;

    // セマフォオープン（新規作成、初期値 0）
    sem = sem_open("/example_sem", O_CREAT, 0644, 0);

    // スレッドを作成する
    pthread_create(&tid, NULL, func, NULL);

    printf("Parent process : Input message > ");
    scanf("%255s", buf);

    // セマフォ　インクリメントしてfuncを起動
    sem_post(sem);

    // スレッドの終了待機
    pthread_join(tid, NULL);

    // セマフォ　クローズ，削除
    sem_close(sem);
    sem_unlink("/example_sem");

    return 0;
}

void *func(void *param) {
    // セマフォのデクリメントを待ち
    sem_wait(sem);

    printf("Thread -> %s\n", buf);

    pthread_exit(0);
}
