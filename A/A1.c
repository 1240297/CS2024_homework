#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

// 氏名・年齢：初期値有りグローバル変数で定義する
// 氏名は文字列型，年齢は整数型で999以下
char name[] = "Kazutoshi Yokoyama";
int age = 59;

// バッファサイズの定義
#define BUFFER_SIZE 1024

// int char 変換
int int_to_str(int num, char *str) {
    int i = 0, j, temp;
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return i;
    }

    // 数字を逆順に格納
    while (num > 0 && i < BUFFER_SIZE - 1) {
        str[i++] = (num % 10) + '0';
        num /= 10;
    }

    // 逆順を正しい順序にする
    for (j = 0; j < i / 2; j++) {
        temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }

    str[i] = '\0';
    return i;
}

// 書き出すファイル名は，実行時に引数で"./outputfile.txt"を指定する．
// openシステムコール，closeシステムコール，writeシステムコール，readシステムコールのみを使用し，他のライブラリ関数は使用しない．
int main(int argc, char *argv[]){
    ssize_t bytes_read; // 何バイト読み込んだか
    char buffer[BUFFER_SIZE];
    int buffer_pos = 0;

    int fd_in = open("inputfile.txt", O_RDONLY);
    int fd_out = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    //printf("%s = %d\n", argv[1], fd_out);

    // read(int d, void *buf, size_t nbytes);
    bytes_read = read(fd_in, buffer + buffer_pos, BUFFER_SIZE - buffer_pos - 1);
    bytes_read += buffer_pos;
    buffer[bytes_read] = '\0'; // NULL文字入れる

    //printf("%zd", bytes_read);

    // write(int d, const void *buf, size_t nbytes);
    int bytes_written = write(fd_out, buffer, bytes_read);
    if (bytes_written == 0) printf("error\n");
    bytes_written = write(fd_out, name, sizeof(name)-1);
    if (bytes_written == 0) printf("error\n");
    write(fd_out, "\n", 1);

    char age_str[12];
    int len = int_to_str(age, age_str);
    bytes_written = write(fd_out, age_str, len);
    //bytes_written = write(fd_out, age, sizeof(age)-1);
    if (bytes_written == 0) printf("error\n");


    //printf("bytes_written = %d\n", bytes_written);
}

