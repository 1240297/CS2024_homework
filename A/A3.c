#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t pid; // プロセスIDを格納する変数

    // 子プロセスを生成
    pid = fork();

    if (pid < 0) {
        // forkの失敗
        perror("fork failed");
        exit(EXIT_FAILURE);
    }else if (pid == 0) {
        // 子プロセスの処理
        // execute the command "ls -al /usr/local" by exec system call.
        execlp("ls", "ls", "-al", "/usr/local", NULL);

        // execlp失敗時
        perror("execlp failed"); // エラーメッセージを表示
        exit(EXIT_FAILURE); // コマンド実行失敗の場合は終了
    } else {
        // 親プロセスの処理
        // wait for child process termination
        wait(NULL); // 子プロセスの終了を待つ
    }
    return 0;
}