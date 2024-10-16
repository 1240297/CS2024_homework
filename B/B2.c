#include <stdio.h>
#include <pthread.h>
#include <string.h>

// 大域変数 char bufBI, bufClを定義する
char bufB[256];
char bufC[256];

#define BUFFER_SIZE 256

// スレッドB 関数
void *threadB(void *arg) {
    // bufB[]へメッセージを書き込む
    strncpy(bufB, "msgB", BUFFER_SIZE);
    pthread_exit(0); // 終了
}

// スレッドC 関数
void *threadC(void *arg) {
    // bufC[]へメッセージを書き込む
    strncpy(bufC, "msgC", BUFFER_SIZE);
    pthread_exit(0); // 終了
}

// プロセス
int main() {
    pthread_t tidB, tidC; // スレッドIDの宣言

    // スレッドB をpthread_createにより生成する
    if (pthread_create(&tidB, NULL, threadB, NULL) != 0) {
        perror("Failed to create thread B");
        return 1;
    }

    // スレッドC をpthread_createにより生成する
    if (pthread_create(&tidC, NULL, threadC, NULL) != 0) {
        perror("Failed to create thread C");
        return 1;
    }

    // スレッドB,Cの終了を待つ
    pthread_join(tidB, NULL);
    pthread_join(tidC, NULL);

    // bufBDとbufClを標準出力へ表示する
    printf("bufB: %s\n", bufB);
    printf("bufC: %s\n", bufC);

    // 終了
    return 0;
}