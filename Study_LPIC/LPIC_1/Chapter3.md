# 3. GNU と UNIX コマンド
## 3.1 コマンドライン操作
### 3.1.1 シェル
**シェル (shell)**
- ユーザからのコマンドを受け付け，必要なプログラムを実行するプログラム
- e.g. Bourne シェル (sh)，bash (Bourne Again Shell)，C シェル (csh)，tcsh，Korn シェル (ksh)，Z シェル (zsh)
    - **Bourne シェル**: UNIX の標準的なシェル
    - **bash**: Bourne を改良したもの．多くの Linux ディストリビューションの標準シェル．
    - **C シェル**: C 言語に似たスクリプトが利用できるシェル．
    - **tcsh**: C シェルを改良したもの．Linux で C シェルとして使われているもの．
    - **Korn シェル**: Bourne シェルを改良したもの．
    - **zsh**: ksh に bash や tcsh の機能を取り入れた高機能シェル．

参考:
- 利用可能なシェルは，`/etc/shells` ファイルで確認することができる．
- `chsh` コマンドを使ってデフォルトのシェルを変更することができる．

Ubuntu 20.04 の利用可能なシェル:
```
ai@ai-VirtualBox:~$ cat /etc/shells
# /etc/shells: valid login shells
/bin/sh
/bin/bash
/usr/bin/bash
/bin/rbash
/usr/bin/rbash
/bin/dash
/usr/bin/dash
```

CentOS 7 の利用可能なシェル:
```
[ai@localhost ~]$ cat /etc/shells
/bin/sh
/bin/bash
/usr/bin/sh
/usr/bin/bash
```

**ログインシェル**
- システムにログインした直後に起動されるシェル
- ユーザごとのログインシェルは，`/etc/passwd` ファイルに記述されている．

Ubuntu 20:
```
ai@ai-VirtualBox:~$ cat /etc/passwd | grep /home/ai
ai:x:1000:1000:Ai Tachibana,,,:/home/ai:/bin/bash
```
CentOS 7:
```
[ai@localhost ~]$ cat /etc/passwd | grep /home/ai
ai:x:1000:1000:Ai Tachibana:/home/ai:/bin/bash
```

- bash では，一般ユーザの場合 `$` が表示され，スーパーユーザ (root) の場合は `#` が表示される．
- 環境変数 `PS1` で，プロンプトの表示形式を自由に設定することができる．

<div style="page-break-before:always"></div>

### 3.1.2 シェルの基本操作と設定
bash には，コマンドラインの作業を効率よく行うためのさまざまな機能がある．

##### コマンドラインの基本操作
|操作|説明|
|---|---|
|**Tab**|コマンドやディレクトリ名を補完する．|
|**Ctrl + A**|行の先頭へカーソルを移動する．|
|**Ctrl + E**|行の最後へカーソルを移動する．|
|**Ctrl + D**|カーソル部分を1文字削除する，ログアウトする．|
|**Ctrl + H**|カーソルの左を1文字削除する (Backspace と同じ)．|
|**Ctrl + L**|画面をクリアしてカレント行を再表示する．|
|**Ctrl + C**|処理を中断する．|
|**Ctrl + S**|画面への出力を停止する (キー入力を受け付けない)．|
|**Ctrl + Q**|画面への出力を再開する．|
|**Ctrl + Z**|処理を一時停止する．|

##### ディレクトリの指定
bash では，ディレクトリを表す特殊記号 (**メタキャラクタ**) を使うことができる．

|メタキャラクタ|説明|
|---|---|
|`~`|ホームディレクトリ|
|`.`|カレントディレクトリ|
|`..`|1つ上のディレクトリ|

<div style="page-break-before:always"></div>

### 3.1.3 シェル変数と環境変数
シェルはユーザと Linux システムとの対話をつかさどる．
⇒ ユーザに関する情報 (e.g. ユーザのホームディレクトリ，ログイン名等) を保持しなければならない．

Linux では，このような情報は変数に保存される．
この変数の有効範囲 (スコープ) によって，シェル変数と環境変数に分けられる．

**シェル変数**
- スコープがその変数を定義したシェル・プロセスのみ．
    - 1人のユーザが bash を複数起動していた場合，複数の bash プロセスが動作する．シェル変数の有効範囲は1つの bash プロセス上にとどまる．
    - 該当するシェル・プロセスを終了すると，シェル変数は失われる．
    - 別のシェルを新しく起動した場合，新しいシェルから元のシェルで定義した内容を参照することはできない．

**環境変数**
- その変数を定義したシェル上，およびそのシェルで実行されるプログラムにも引き継がれる変数．
- シェル変数を `export` コマンドでエクスポートすることで設定する．


```
(bash)
[ai@localhost ~]$ EV=world  <- 変数設定
[ai@localhost ~]$ SV=local  <- 変数設定
[ai@localhost ~]$ export EV <- エクスポート
[ai@localhost ~]$ bash      <- 新しいシェルを起動
```

```
(bash (子プロセス))
[ai@localhost ~]$ echo $EV
world   <- 変数 EV の内容が表示される．
[ai@localhost ~]$ echo $SV
        <- 変数 SV は子プロセスでは未定義．
[ai@localhost ~]$ EV='new world'    <- 変数 EV を再定義
[ai@localhost ~]$ exit              <- このシェルを終了
exit
```

```
(bash)
[ai@localhost ~]$ echo $EV
world   <- 子プロセスでの変更は繁栄されていない．
```

主な環境変数:
|環境変数|説明|
|---|---|
|`EDITOR`|デフォルトのエディタのパス|
|`HISTFILE`|コマンド履歴を格納するファイル|
|`HISTFILESIZE`|`HISTFILE` に保存する履歴数|
|`HOME`|カレントユーザのホームディレクトリ|
|`HOSTNAME`|ホスト名|
|`LANG`|ロケール (言語処理方式)|
|`LOGNAME`|ログインシェルのユーザ名|
|`PATH`|コマンドやプログラムを検索するディレクトリリスト|
|`PS1`|プロンプトの表示文字列|
|`PS2`|複数行にわたる入力時のプロンプト|
|`PWD`|カレントディレクトリ|
|`TERM`|端末の種類|
|`USER`|現在のユーザ|

###### Remark
- 端末
    - 入出力に特化した機器
        - キーボードから入力された文字をコンピュータに送る機能
        - コンピュータから送られてきた信号をディスプレイに表示する機能
    - 初期のコンピュータは，キーボードとディスプレイのセットを複数接続し，複数のユーザが同時に利用できるようになっていた．
    
- 端末エミュレータ
    - 端末をソフトウェアで実現したもの
        - e.g. GNOME-terminal, Konsole, TeraTerm

変数を定義する書式は以下．
```
変数名=値
```

- `=` の前後にスペースが入らないように注意．
- 変数名には，英字，数字，アンダーバーを使うことが可能．
    - 先頭の文字に数字を使うことはできない．
    - 大文字と小文字は区別される．
- 値にスペースが入る場合は，`"` (二重引用符) または `'` (単一引用符) で囲む．

定義された変数は `echo` コマンドを使って参照できる (`echo - display a line of text`)．
```
echo [文字列または$変数名]
```

e.g.
```
[ai@localhost ~]$ lpi='Linux Professional Institute'
[ai@localhost ~]$ echo $lpi
Linux Professional Institute
```

変数を削除するには，`unset` コマンドを使う．このとき，変数の先頭には `$` 記号をつけない．
```
unset 変数名
```

- 定義されている環境変数を一覧表示するには，`env` コマンドか，`printenv` コマンドを使う．
- 環境変数とシェル変数を両方表示したい場合は，`set` コマンドを使う．

シェル変数は，新たに起動したシェルから参照することはできない．`export` コマンドでエクスポートすることで参照できるようになる．
```
export 変数名[=値]
```

実行例:
```
[ai@localhost ~]$ VAR=lpic
[ai@localhost ~]$ echo $VAR
lpic    <- VAR 変数の内容の出力
[ai@localhost ~]$ bash  <- bash を新たに起動
[ai@localhost ~]$ echo $VAR
        <- 新しいシェルでは VAR 変数が定義されていないので何も表示されない．
[ai@localhost ~]$ exit
exit
[ai@localhost ~]$ export VAR    <- VAR 変数を export
[ai@localhost ~]$ bash  <- bash を新たに起動
[ai@localhost ~]$ echo $VAR
lpic    <- VAR が環境変数になったことで，表示される．
```

エクスポートと変数定義は1行で書くこともできる．
```
export VAR=lpic
```

###### Remark
- 定義には `$` は不要．
- 参照には `$` が必要．