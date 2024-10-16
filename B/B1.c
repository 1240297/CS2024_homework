#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

// バッファサイズの定義
#define BUFFER_SIZE 256

int main(){
    int p_pipefd[2], c_pipefd[2]; // pipefd_p(p->c), pipefd_c(c->p)
    pid_t pid;
    char p_msg[BUFFER_SIZE];
    char c_msg[BUFFER_SIZE];
    
    // pipeの生成 (parent -> child)
    if (pipe(p_pipefd) == -1) {
        perror("parent->child pipe failed");
        exit(EXIT_FAILURE);
    }

    // pipeの生成 (child -> parent)
    if (pipe(c_pipefd) == -1) {
        perror("child->parent pipe failed");
        exit(EXIT_FAILURE);
    }
    
    pid = fork(); // 子プロセスの生成
    

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);

    } else if(pid == 0) {
        // 子プロセスの処理
        close(p_pipefd[1]); // p->c の書き込みを閉じる
        close(c_pipefd[0]); // c->p の読み取りを閉じる

        // 親プロセスからのメッセージを pipeから読み込む
        read(p_pipefd[0], c_msg, BUFFER_SIZE);
        close(p_pipefd[0]);

        // メッセージに”from child process”の文字列を追加
        strcat(c_msg, " from child process");

        // 親プロセスへのメッセージを pipeに書き込む
        write(c_pipefd[1], c_msg, strlen(c_msg));
        close(c_pipefd[1]);

        exit(EXIT_SUCCESS); // 終了

    } else {
        // 親プロセスの処理
        close(p_pipefd[0]); // p->c の読み取りを閉じる
        close(c_pipefd[1]); // c->p の書き込みを閉じる

        // 標準入力から文字列のメッセージを受け取る (メッセージは256バイト以下)
        printf("Enter: ");
        fgets(p_msg, BUFFER_SIZE, stdin); // 256バイト上限

        p_msg[strcspn(p_msg, "\n")] = 0;

        // 子プロセスへのメッセージを pipeに書き込む "Yokoyama"
        write(p_pipefd[1], p_msg, strlen(p_msg));
        close(p_pipefd[1]);

        // 子プロセスからのメッセージを pipe から読み込む
        read(c_pipefd[0], p_msg, BUFFER_SIZE);
        close(c_pipefd[0]);

        // 子プロセスの終了を待つ
        wait(NULL);

        // 標準出力へメッセージを表示
        printf("msg: %s\n", p_msg);
    }
    return 0;
}