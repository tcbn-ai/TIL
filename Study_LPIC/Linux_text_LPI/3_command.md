# 3 基本的なコマンド

## 3.1 ファイル操作

#### `ls` コマンド
ファイル名やディレクトリ名を指定して情報を取得する．

書式:
```
ls [option] [ファイル or ディレクトリ]
```

option:
```
-a
隠しファイル等も全て (All) 出力する．

-l
長 (Long) 形式で出力する．

-t
最終更新時間 (Time) によってソートして出力する．

-r
逆順 (Reverse) にソートして出力する．
```

実行例:
```
ai@ai-VirtualBox:~$ ls
Desktop  Documents  Downloads  Music  Pictures  Public  Templates  Videos
```

```
ai@ai-VirtualBox:~$ ls /usr/
bin  games  include  lib  lib32  lib64  libexec  libx32  local  sbin  share  src
```

ワイルドカード (`*, ?`) を使ってファイルを絞り込んでリスト表示することもできる．

例:
```
ai@ai-VirtualBox:/etc$ ls *.conf
adduser.conf          fuse.conf        logrotate.conf           rsyslog.conf
apg.conf              gai.conf         ltrace.conf              rygel.conf
appstream.conf        hdparm.conf      mke2fs.conf              sensors3.conf
brltty.conf           host.conf        mtools.conf              sysctl.conf
ca-certificates.conf  kernel-img.conf  nsswitch.conf            ucf.conf
debconf.conf          kerneloops.conf  pam.conf                 usb_modeswitch.conf       
deluser.conf          ld.so.conf       pnm2ppa.conf             xattr.conf
e2scrub.conf          libao.conf       popularity-contest.conf
fprintd.conf          libaudit.conf    resolv.conf
```

`*` は任意の文字列を示している．

```
ai@ai-VirtualBox:/etc$ ls ???.conf
apg.conf  gai.conf  pam.conf  ucf.conf
```

ファイル名の文字数が分かっている場合は `?` を使って絞り込むこともできる．`?` 1つにつき，何らかの1文字を示す．

`-l` オプションを付けると，情報が長形式で出力される．
```
ai@ai-VirtualBox:~$ ls -l
total 32
drwxr-xr-x 2 ai ai 4096 11月 16 08:50 Desktop
drwxr-xr-x 2 ai ai 4096 11月 16 08:50 Documents
drwxr-xr-x 2 ai ai 4096 11月 16 08:50 Downloads
drwxr-xr-x 2 ai ai 4096 11月 16 08:50 Music
drwxr-xr-x 2 ai ai 4096 11月 16 08:50 Pictures
drwxr-xr-x 2 ai ai 4096 11月 16 08:50 Public
drwxr-xr-x 2 ai ai 4096 11月 16 08:50 Templates
drwxr-xr-x 2 ai ai 4096 11月 16 08:50 Videos
```

```
ai@ai-VirtualBox:~$ ls -la
total 76
drwxr-xr-x 15 ai   ai   4096 11月 16 10:56 .
drwxr-xr-x  3 root root 4096 11月 16 08:44 ..
-rw-------  1 ai   ai    759 11月 16 11:11 .bash_history
-rw-r--r--  1 ai   ai    220 11月 16 08:44 .bash_logout
-rw-r--r--  1 ai   ai   3771 11月 16 08:44 .bashrc
drwxr-xr-x 11 ai   ai   4096 11月 16 10:56 .cache
drwx------ 11 ai   ai   4096 11月 16 09:09 .config
drwxr-xr-x  2 ai   ai   4096 11月 16 08:50 Desktop
drwxr-xr-x  2 ai   ai   4096 11月 16 08:50 Documents
drwxr-xr-x  2 ai   ai   4096 11月 16 08:50 Downloads
drwx------  3 ai   ai   4096 11月 16 08:50 .gnupg
drwxr-xr-x  3 ai   ai   4096 11月 16 08:50 .local
drwxr-xr-x  2 ai   ai   4096 11月 16 08:50 Music
drwxr-xr-x  2 ai   ai   4096 11月 16 08:50 Pictures
-rw-r--r--  1 ai   ai    807 11月 16 08:44 .profile
drwxr-xr-x  2 ai   ai   4096 11月 16 08:50 Public
drwx------  2 ai   ai   4096 11月 16 10:56 .ssh
-rw-r--r--  1 ai   ai      0 11月 16 08:51 .sudo_as_admin_successful
drwxr-xr-x  2 ai   ai   4096 11月 16 08:50 Templates
drwxr-xr-x  2 ai   ai   4096 11月 16 08:50 Videos
```

`ls` コマンドのオプションはまとめてもまとめなくても同じ結果になる．また，順不同である．

<div style="page-break-before:always"></div>

#### `cp` コマンド
ファイルのコピーを行う．

書式:
```
cp [option] コピー元 コピー先
```

実行例:
```
cp src-file dst-file
```

例:
```
ai@ai-VirtualBox:~/Documents/3_copy_workspace$ ls
dst-dir  src-dir  src-file.txt
```
このようなディレクトリに対してコピーを実行する．

- ファイルを別名のファイルとしてコピーする場合
    - `src-file` がファイル名，`dst-file` が存在しないファイル名の場合，`src-file` のコピーとして `dst-file` が作成される．
    ```
    ai@ai-VirtualBox:~/Documents/3_copy_workspace$ cp src-file.txt dst-file.txt
    ai@ai-VirtualBox:~/Documents/3_copy_workspace$ ls
    dst-dir  dst-file.txt  src-dir  src-file.txt
    ```

- ファイルをディレクトリにコピー
    - `src-file` がファイル名，`dst-file` がディレクトリ名の場合，`dst-file` の下にファイル `src-file` のコピーが作成される．
    ```
    ai@ai-VirtualBox:~/Documents/3_copy_workspace$ ls dst-dir/
    ai@ai-VirtualBox:~/Documents/3_copy_workspace$ cp src-file.txt dst-dir/
    ai@ai-VirtualBox:~/Documents/3_copy_workspace$ ls dst-dir/
    src-file.txt
    ```

- ファイルを新しいファイルで上書き
    - `src-file` がファイル名で，`dst-file` が存在するファイル名の場合，`dst-file` は `src-file` のコピーで上書きされる．
    ```
    ai@ai-VirtualBox:~/Documents/3_copy_workspace$ cat src-file.txt 
    src-file
    ai@ai-VirtualBox:~/Documents/3_copy_workspace$ cat dst-file.txt 
    dst-file
    ai@ai-VirtualBox:~/Documents/3_copy_workspace$ cp src-file.txt dst-file.txt 
    ai@ai-VirtualBox:~/Documents/3_copy_workspace$ cat dst-file.txt 
    src-file
    ```

option:
```
-i
処理を行うときに確認する (e.g. 上書きコピーをするとき)．

-r
ディレクトリの中にあるすべてのファイル・ディレクトリをコピーする．

-p
元ファイルの情報 (e.g. 所有者・属性・更新日時) を保存する．
```

実行例:
```
ai@ai-VirtualBox:~/Documents/3_copy_workspace$ cat src-file.txt 
src-file
ai@ai-VirtualBox:~/Documents/3_copy_workspace$ cat dst-file.txt 
dst-file
ai@ai-VirtualBox:~/Documents/3_copy_workspace$ cp -i src-file.txt dst-file.txt 
cp: overwrite 'dst-file.txt'? n
ai@ai-VirtualBox:~/Documents/3_copy_workspace$ cat dst-file.txt 
dst-file
```

```
ai@ai-VirtualBox:~/Documents/3_copy_workspace$ ls src-dir/
src-file-indir.txt  src-subdir
ai@ai-VirtualBox:~/Documents/3_copy_workspace$ cp -r src-dir/ dst-dir/
ai@ai-VirtualBox:~/Documents/3_copy_workspace$ ls dst-dir/src-dir/
src-file-indir.txt  src-subdir
```

```
ai@ai-VirtualBox:~/Documents/3_copy_workspace$ ls -l
total 16
drwxrwxr-x 3 ai ai 4096 11月 16 11:48 dst-dir
-rw-rw-r-- 1 ai ai    9 11月 16 11:46 dst-file.txt
drwxrwxr-x 3 ai ai 4096 11月 16 11:45 src-dir
-rw-rw-r-- 1 ai ai    9 11月 16 11:46 src-file.txt
ai@ai-VirtualBox:~/Documents/3_copy_workspace$ date
2021年 11月 16日 火曜日 11:51:20 JST
ai@ai-VirtualBox:~/Documents/3_copy_workspace$ cp -p src-file.txt dst-file_sametime.txt
ai@ai-VirtualBox:~/Documents/3_copy_workspace$ ls -l
total 20
drwxrwxr-x 3 ai ai 4096 11月 16 11:48 dst-dir
-rw-rw-r-- 1 ai ai    9 11月 16 11:46 dst-file_sametime.txt
-rw-rw-r-- 1 ai ai    9 11月 16 11:46 dst-file.txt
drwxrwxr-x 3 ai ai 4096 11月 16 11:45 src-dir
-rw-rw-r-- 1 ai ai    9 11月 16 11:46 src-file.txt
```

<div style="page-break-before:always"></div>

#### `mv` コマンド
ファイルの移動，またはファイル名の変更をするときに用いる．

書式:
```
mv [option] 移動元ファイル 移動先ファイル
```

option:
```
-i
処理を行うときに確認する．

-f
強制的に処理を実行する．
```

実行例:
```
mv src-file dst-file
```

例:
```
ai@ai-VirtualBox:~/Documents/3_move_workspace$ ls
dst-dir  src-dir  src-file.txt
```

- ファイルを別のディレクトリに移動
    - `src-file` がファイル名で，`dst-file` が存在するディレクトリの場合，ファイル `src-file` がディレクトリ `dst-file` の下に移動する．
    ```
    ai@ai-VirtualBox:~/Documents/3_move_workspace$ ls
    dst-dir  src-dir  src-file.txt
    ai@ai-VirtualBox:~/Documents/3_move_workspace$ mv src-file.txt dst-dir/
    ai@ai-VirtualBox:~/Documents/3_move_workspace$ ls
    dst-dir  src-dir
    ai@ai-VirtualBox:~/Documents/3_move_workspace$ mv dst-dir/src-file.txt .
    ai@ai-VirtualBox:~/Documents/3_move_workspace$ ls
    dst-dir  src-dir  src-file.txt
    ai@ai-VirtualBox:~/Documents/3_move_workspace$ ls dst-dir/
    ai@ai-VirtualBox:~/Documents/3_move_workspace$ mv src-file.txt dst-dir/
    ai@ai-VirtualBox:~/Documents/3_move_workspace$ ls
    dst-dir  src-dir
    ai@ai-VirtualBox:~/Documents/3_move_workspace$ ls dst-dir/
    src-file.txt
    ```

- ディレクトリを別のディレクトリに移動
    - `src-file` がディレクトリ名で，`dst-file` が存在するディレクトリの場合，ディレクトリ `src-file` はディレクトリ `dst-file` の下に移動する．
    ```
    ai@ai-VirtualBox:~/Documents/3_move_workspace$ ls
    dst-dir  src-dir
    ai@ai-VirtualBox:~/Documents/3_move_workspace$ mv src-dir/ dst-dir/
    ai@ai-VirtualBox:~/Documents/3_move_workspace$ ls
    dst-dir
    ai@ai-VirtualBox:~/Documents/3_move_workspace$ ls dst-dir/
    src-dir  src-file.txt
    ```

- ファイル名の変更
    - `src-file` がファイル名で，`dst-file` が存在しないファイル名の場合，ファイル `dst-file` にファイル名が変更される．
    ```
    ai@ai-VirtualBox:~/Documents/3_move_workspace/dst-dir$ ls
    src-dir  src-file.txt
    ai@ai-VirtualBox:~/Documents/3_move_workspace/dst-dir$ mv src-file.txt dst-file.txt
    ai@ai-VirtualBox:~/Documents/3_move_workspace/dst-dir$ ls
    dst-file.txt  src-dir
    ```

- ディレクトリ名の変更
    - `src-file` がディレクトリ名で，`dst-file` が存在しないディレクトリ名の場合，ディレクトリ `dst-file` にディレクトリ名が変更される．
    ```
    ai@ai-VirtualBox:~/Documents/3_move_workspace/dst-dir$ ls
    dst-file.txt  src-dir
    ai@ai-VirtualBox:~/Documents/3_move_workspace/dst-dir$ mv src-dir/ dst-subdir/
    ai@ai-VirtualBox:~/Documents/3_move_workspace/dst-dir$ ls
    dst-file.txt  dst-subdir
    ```


<div style="page-break-before:always"></div>

#### `rm` コマンド
作成したファイルを削除するときに利用する．

書式:
```
rm [option] ファイル名
```

option:
```
-i
処理を行うときの確認をする．

-f
強制的に処理を実行する．

-r
ディレクトリ内のファイルやディレクトリも削除する．
```

実行例:
```
rm file-delete
```

例:
```
ai@ai-VirtualBox:~/Documents/3_remove_workspace$ ls
dir-delete  file-delete.txt
```

- ファイルを削除するとき
    ```
    ai@ai-VirtualBox:~/Documents/3_remove_workspace$ rm file-delete.txt 
    ai@ai-VirtualBox:~/Documents/3_remove_workspace$ ls
    dir-delete
    ```

- ディレクトリを削除するとき
    ```
    ai@ai-VirtualBox:~/Documents/3_remove_workspace$ ls
    dir-delete
    ai@ai-VirtualBox:~/Documents/3_remove_workspace$ rm -r dir-delete/
    ai@ai-VirtualBox:~/Documents/3_remove_workspace$ ls
    ai@ai-VirtualBox:~/Documents/3_remove_workspace$ 
    ```

`-r` は recursive (再帰) を示すオプションである．ディレクトリの中のディレクトリの中の...というような階層構造の中まで処理を行うことを表す．


<div style="page-break-before:always"></div>

## 3.2 ディレクトリの操作

#### `pwd` コマンド
現在のディレクトリを表示する (Print Working Directory)．

書式:
```
pwd
```

実行例:
```
ai@ai-VirtualBox:~$ pwd
/home/ai
```

#### `cd` コマンド
現在いるディレクトリを変更できる (Change Directory)．ディレクトリを指定しない場合はホームディレクトリに移動する．

```
cd [ディレクトリ名]
```

実行例:
```
ai@ai-VirtualBox:~$ cd /usr/
ai@ai-VirtualBox:/usr$ pwd
/usr
```

#### `mkdir` コマンド
ディレクトリの作成

書式:
```
mkdir [option] ディレクトリ名
```

option:
```
-p
指定されたディレクトリの上位ディレクトリも作成する
```

実行例:
```
ai@ai-VirtualBox:~/Documents/3_makedir_workspace$ ls
ai@ai-VirtualBox:~/Documents/3_makedir_workspace$ mkdir -p dir/subdir/subsubdir
ai@ai-VirtualBox:~/Documents/3_makedir_workspace$ ls -R
.:
dir

./dir:
subdir

./dir/subdir:
subsubdir

./dir/subdir/subsubdir:
```

#### `rmdir` コマンド
ディレクトリを削除する．

書式:
```
rmdir [option] ディレクトリ名
```

option:
```
-p
指定した階層までのディレクトリを一括で削除する．
オプションがないときは最下層のみ削除する．
対象とするディレクトリ内は空でなければならない．

(例) dict1/dict2 ディレクトリを一括で削除
rmdir -p dict1/dict2
```

実行例:
```
ai@ai-VirtualBox:~/Documents/3_makedir_workspace$ ls -R
.:
dir

./dir:
subdir

./dir/subdir:
subsubdir

./dir/subdir/subsubdir:
file.txt
ai@ai-VirtualBox:~/Documents/3_makedir_workspace$ rmdir -p dir/subdir/subsubdir/
rmdir: failed to remove 'dir/subdir/subsubdir/': Directory not empty
ai@ai-VirtualBox:~/Documents/3_makedir_workspace$ rm -r dir/
ai@ai-VirtualBox:~/Documents/3_makedir_workspace$ ls
```

#### 特別なディレクトリ
- カレントディレクトリ `.`
    - 現在のディレクトリ．操作の際は `.` で表す．

- 親ディレクトリ `..`
    - 1階層上のディレクトリ．`/home/ai` の親ディレクトリは `/home`．

- ホームディレクトリ `~`
    - ユーザの作業開始位置となるディレクトリ．ログイン直後はホームディレクトリにいる．

- ルートディレクトリ `/`
    - ディレクトリ階層の最上位階層．

#### 絶対パス指定と相対パス指定
- 絶対パス指定
    - ルートディレクトリから見たパスでファイルやディレクトリを指定．
- 相対パス指定
    - 自分が現在いる位置から見たパスでファイルやディレクトリを指定．


<div style="page-break-before:always"></div>

## 3.3 ファイルの内容を表示

#### `cat` コマンド
ファイルの内容を確認する．

書式:
```
cat [option] ファイル名
```

オプション:
```
-n
行番号を付加して表示．
```

実行例:
```
ai@ai-VirtualBox:~$ cat ~/.bash_logout 
# ~/.bash_logout: executed by bash(1) when login shell exits.

# when leaving the console clear the screen to increase privacy

if [ "$SHLVL" = 1 ]; then
    [ -x /usr/bin/clear_console ] && /usr/bin/clear_console -q
fi
```

```
ai@ai-VirtualBox:~$ cat -n ~/.bash_logout 
     1  # ~/.bash_logout: executed by bash(1) when login shell exits.
     2
     3  # when leaving the console clear the screen to increase privacy
     4
     5  if [ "$SHLVL" = 1 ]; then
     6      [ -x /usr/bin/clear_console ] && /usr/bin/clear_console -q
     7  fi
```

#### ページャを使った表示
`cat` コマンドを使ってファイルの内容を表示するとき，行数がたくさんあると表示が流れてしまう．

- ページング
    - たくさんの行があっても，画面制御を行いスクロールを途中で止めてくれる機能

- ページャ
    - ページングを実現するコマンド
    - e.g. `more`, `less`

書式:
```
more ファイル名
less ファイル名
```

ページャでファイルを開いた後は，次のようにコマンド入力すると操作できる．

`more` コマンド:
| 項目 | 内容 |
|---|---|
| スペース | 次のページに進む |
| b | 前の一画面に戻る (back) |
| f | 次の一画面に進む (forward) |
| /単語 | 単語の検索．nで検索結果をジャンプ． |
| q | ページャコマンドの終了 (quit) |

`less` コマンド:
| 項目 | 内容 |
|---|---|
| スペース | 次のページに進む |
| b | 前の一画面に戻る (back) |
| f | 次の一画面に進む (forward) |
| ↑ | 前の行に進む |
| ↓ | 次の行に進む |
| /単語 | 単語の検索．nで検索結果をジャンプ． |
| q | ページャコマンドの終了 (quit) |


<div style="page-break-before:always"></div>

#### `find` コマンド
ファイルがどこのディレクトリに存在するかを検索する．

書式:
```
find パス -name ファイル名
```

実行例:
```
ai@ai-VirtualBox:~$ sudo find /etc/ -name hosts
[sudo] password for ai: 
/etc/avahi/hosts
/etc/hosts
```

<div style="page-break-before:always"></div>

## 3.5 コマンドのパス
コマンドの実体はプログラム．プログラムもファイルの一種であり，`/bin` や `/sbin` といったプログラム用のディレクトリに配置されている．

#### `which` コマンド
基本的なコマンドを実行するとき，実体であるプログラムがどのディレクトリに配置されているかを意識する必要はない．これは，`PATH` という環境変数にプログラムが配置されているディレクトリが設定されているため．

`which` コマンドを用いると，`PATH` 環境変数に含まれるディレクトリ配下に配置されているコマンドのパスを表示することができる．

書式:
```
which コマンド名
```

実行例:
```
ai@ai-VirtualBox:~$ echo $PATH
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
ai@ai-VirtualBox:~$ which cat
/usr/bin/cat
```

コマンドが存在するディレクトリが `PATH` 環境変数に含まれていないと，`which` コマンドの結果はエラーとなる．

<div style="page-break-before:always"></div>

## 3.6 ヘルプの使い方
実行したいコマンドに対して `--help` オプションなどをつけて実行することで，コマンドの実行に使えるオプションを調べることができる．

書式:
```
コマンド --help
```

実行例:
```
ai@ai-VirtualBox:~$ cat --help
Usage: cat [OPTION]... [FILE]...
Concatenate FILE(s) to standard output.

With no FILE, or when FILE is -, read standard input.

  -A, --show-all           equivalent to -vET
  -b, --number-nonblank    number nonempty output lines, overrides -n
(略)
```

<div style="page-break-before:always"></div>

## 3.7 マニュアルの使い方
#### `man` コマンド
書式:
```
man [option] コマンド名
```

option:
```
-k 単語
'単語' が含まれるエントリ一覧を出力する．
```

#### セクション
マニュアルの内容を分野ごとに分け，その分野を指定したもの．

マニュアルのセクション:
| 項目 | 内容 |
|---|---|
|1| ユーザコマンド |
|2| システムコール |
|3| システムライブラリや関数 |
|4| デバイスやデバイスドライバ |
|5| ファイルの形式 |
|6| ゲームやデモなど |
|7| その他 |
|8| システム管理系のコマンド |
|9| カーネルなどの情報 |

