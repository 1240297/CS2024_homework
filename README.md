# 計算機システム論課題
## Homework A
- A1.c
  - inputfile.txtから読み込んだ文字列，氏名，年齢を1行ずつファイルに出力するプログラム
  - システムコールの学習(open, close, write, read)
- A2.c
  - forkシステムコールを使用したプロセス生成
  - 親プロセス，子プロセスのプロセスIDの表示
- A3.c
  - forkシステムコールを使用したプロセス生成
  - 子プロセスにて“ls -al/usr/local”のコマンドを実行

## Homework B
- B1.c
  - pipeを用いたプロセス間通信
- B2.c
  - マルチスレッド処理
  - pthread_createによるスレッドの生成

## Homework C
- C1.c
  - プロセスの優先度設定

## Homework D
- D1.c
  - セマフォアのメッセージ受け渡し
- D2.c
  - 複数スレッドの大域変数の更新
  - 排他制御
- D3.c
  - 生産者・消費者問題
  - 相互排除，同期