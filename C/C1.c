#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/wait.h>

#define LOOP_COUNT 1000000

//（1）親プロセスが開始時刻を取得し、子プロセスを生成する。
//（2）親プロセスは、優先度を-19に設定する。子プロセスの優先度を19に設定する。
//（3）親プロセスと子プロセスはCPU処理を実行する。
//（4）親プロセスと子プロセスは終了時刻を取得し、実行時間を表示する。

// 空ループ関数
void loop_work() {
    volatile int i;
    for (i = 0; i < LOOP_COUNT; i++); // 空ループ
}

// 時刻差分の計算関数
double get_time_diff(struct timeval start, struct timeval end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
}

int main() {
    struct timeval start_time;
    struct timeval end_time;
    pid_t pid;


    // 開始時刻の取得
    gettimeofday(&start_time, NULL);

    // 子プロセスの生成
    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // 子プロセスの処理
        // 優先度設定(19)
        if (setpriority(PRIO_PROCESS, 0, 19) == -1) {
            perror("setpriority failed in child");
            return 1;
        }
        // CPU処理
        // 空ループ
        loop_work();

        // 終了時刻の取得
        gettimeofday(&end_time, NULL);

        // 実行時間表示
        printf("child time: %f seconds\n", get_time_diff(start_time, end_time));

    } else {
        // 親プロセスの処理
        // 優先度設定(-19)
        if (setpriority(PRIO_PROCESS, 0, -19) == -1) {
            perror("setpriority failed in parent");
            return 1;
        }

        // CPU処理
        // 空ループ
        loop_work();

        // 終了時刻の取得
        gettimeofday(&end_time, NULL);

        // 実行時間表示
        printf("parent time: %f seconds\n", get_time_diff(start_time, end_time));

        wait(NULL);
    }

    return 0;
}
