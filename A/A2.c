#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid; // プロセスIDを格納する変数

    // 子プロセスを生成
    pid = fork();

    if (pid < 0) {
        // forkの失敗
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // 子プロセスの処理
        printf("child process, PID = %d, parent PID = %d\n", getpid(), getppid());
        exit(EXIT_SUCCESS); // 子プロセスを終了
    } else {
        // 親プロセスの処理
        wait(NULL); // 子プロセスの終了を待つ
        printf("parent process, PID = %d\n", getpid());
    }

    return 0;
}
