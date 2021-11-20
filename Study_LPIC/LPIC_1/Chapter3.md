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

<div style="page-break-before:always"></div>

### 3.1.4 環境変数 `PATH`
- プロンプトが表示されている状態でコマンドを入力すると，シェルはそのコマンド (プログラム) を実行する．
- コマンドには，**内部コマンド** と **外部コマンド** がある．
    - 内部コマンド: シェル自体に組み込まれているもの
    - 外部コマンド: 独立したプログラムとして存在するもの

e.g. 
- `ls`: `/bin/ls` が実行される外部コマンド
- `cd`: シェルに組み込まれている内部コマンド

外部コマンドの場合，シェルはそのコマンドがどこに置かれているかを，環境変数 `PATH` に指定されたディレクトリを順に調べて見つけ出す．

- コマンドが置かれたディレクトリを環境変数 `PATH` に追加することを，「パスを通す」という．
- パスの通っていない場所に置かれているコマンドやプログラムを実行する場合，絶対パスまたは相対パスを指定する必要がある．
    - **絶対パス** 表記
        - 最上位のディレクトリ (`/`) から表記する方法．
        - システム内のファイル位置を一意に示す．
    - **相対パス** 表記
        - カレントディレクトリ (`.`) を基点とした相対位置で表す．
    

例えば，CentOS 7 の場合，`PATH` 変数に含まれているディレクトリは以下．
```
[ai@localhost ~]$ echo $PATH
/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/ai/.local/bin:/home/ai/bin
```

`PATH` 変数に含まれていないディレクトリにコマンドでも，絶対パスを指定すれば実行することができる (コマンドを実行する権限は必要)．

環境変数 `PATH` にパスを追加するには，`~/.bash_profile` などの環境設定ファイルの `PATH` 設定を修正するか，以下のコマンドを使用する．
```
PATH=$PATH:追加するディレクトリ名
```

e.g. `/opt/bin` ディレクトリを環境変数 `PATH` の末尾に追加:
```
[ai@localhost ~]$ PATH=$PATH:/opt/bin
[ai@localhost ~]$ echo $PATH
/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/ai/.local/bin:/home/ai/bin:/opt/bin
```

- シェルは，環境変数 `PATH` の先頭から順にディレクトリを検索する．
    - 同名のプログラムがあった場合は，環境変数 `PATH` の先頭に近い方のディレクトリに置かれているプログラムが実行される．

例えば，次のようにしてしまうとパスが通っているディレクトリが `/opt/bin` のみになり，外部コマンドが使えなくなる． 
```
PATH=/opt/bin
```

通常，セキュリティ上の理由から，環境変数 `PATH` にはカレントディレクトリを含めない．カレントディレクトリにあるプログラムを実行するには，カレントディレクトリを意味する `./` を明示する．

<div style="page-break-before:always"></div>

### 3.1.5 コマンドの実行
コマンドラインは次のような要素から成り立っている．
```
コマンド オプション 引数
```
- コマンド
    - 実行可能なプログラムまたはスクリプト
- オプション
    - コマンドに対して動作を指示するスイッチ
    - ハイフン (`-` もしくは `--`) に続けて指定する．例外的にハイフンを必要としないコマンドもある．
- 引数
    - コマンドに渡す値．
    - 引数の有無で動作が変わるコマンド，引数を取らないコマンド，複数の引数が必要なコマンドなどがある．

コマンドは，1行に複数並べて実行できる．

複数のコマンドの実行制御:
|コマンド|説明|
|----|----|
|`コマンド1; コマンド2`|コマンド1に続いてコマンド2を実行する|
|`コマンド1 && コマンド2`|コマンド1が正常に終了したときのみコマンド2を実行する|
|`コマンド1 || コマンド2`|コマンド1が正常に終了しなかった場合のみコマンド2を実行する|
|`(コマンド1; コマンド2)`|コマンド1とコマンド2を，ひとまとまりのコマンドグループとして実行する|
|`{ コマンド1; コマンド2; }`|現在のシェル内でコマンド1とコマンド2を実行する|

実行例:
```
[ai@localhost ~]$ ls; ls -a
LPIC_workspace
.  ..  .bash_history  .bash_logout  .bash_profile  .bashrc  LPIC_workspace

[ai@localhost ~]$ cat .bash_profile | grep PATH && pwd
PATH=$PATH:$HOME/.local/bin:$HOME/bin
export PATH
/home/ai <- 正常に終了したので，pwd が実行される．

[ai@localhost ~]$ cat LPIC_workspace && echo $PATH
cat: LPIC_workspace: Is a directory 
    <- 正常に終了しなかったので，echo $PATH は実行されない．

[ai@localhost ~]$ cat LPIC_workspace || echo 'This is not a file!'
cat: LPIC_workspace: Is a directory
This is not a file! <- 正常に終了しなかったので，echo ... が実行される．

[ai@localhost ~]$ cat .bash_profile | grep PATH || pwd
PATH=$PATH:$HOME/.local/bin:$HOME/bin
export PATH
    <- 正常に終了したので，pwd は実行されない．

[ai@localhost ~]$ (date; pwd; ls -a)
2021年 11月 20日 土曜日 15:48:20 JST
/home/ai
.  ..  .bash_history  .bash_logout  .bash_profile  .bashrc  LPIC_workspace

[ai@localhost ~]$ { date; pwd; ls -a; }
2021年 11月 20日 土曜日 15:48:47 JST
/home/ai
.  ..  .bash_history  .bash_logout  .bash_profile  .bashrc  LPIC_workspace
```

<div style="page-break-before:always"></div>


### 3.1.6 引用符
##### 単一引用符 `'`
単一引用符の中は，全て文字列であると解釈される．
```
[ai@localhost ~]$ echo $LANG
en_US.UTF-8 <- 環境変数 LANG の内容が出力される．
[ai@localhost ~]$ echo '$LANG'
$LANG       <- 文字列 $LANG が出力される．
```

##### 二重引用符 `"`
二重引用符内も文字列であるとみなされるが，二重引用符内に変数があれば，その変数の内容が展開される．
また，二重引用符内にバッククオーテーション (``` ` ```) が使われていると，その中も展開される．
```
[ai@localhost ~]$ echo $LANG
en_US.UTF-8
[ai@localhost ~]$ echo "Locale: $LANG"
Locale: en_US.UTF-8
```

展開させたくない場合は，バックスラッシュ (`\`) を使う．バックスラッシュ直後の文字はすべて通常の文字とみなされる．バックスラッシュは **エスケープ文字** と呼ばれる．
```
[ai@localhost ~]$ echo "\$LANG: $LANG"
$LANG: en_US.UTF-8
```

##### バッククオーテーション ``` ` ```
- バッククオーテーション内にコマンドがあれば，コマンドを実行した結果が展開される．
- 変数の場合は，変数に格納されているコマンドを実行した結果が展開される．

```
[ai@localhost ~]$ echo "The current directory is `pwd`."
The current directory is /home/ai.
```

`$(コマンド)` を使ってもよい．バッククオーテーションはシングルクオーテーションと紛らわしいので，こちらの書き方の方が良い．
```
[ai@localhost ~]$ echo "The current directory is $(pwd)."
The current directory is /home/ai.
```

<div style="page-break-before:always"></div>

### 3.1.7 コマンド履歴
一度使ったコマンドをもう一度使ったり，一度だけ変更して使いたい場合は，bash の履歴機能を利用することができる．

**history** コマンド
- コマンド履歴が順に表示される．
- 古いものから順に番号がついているので，この履歴番号を直接指定して実行することもできる．
- 履歴番号を指定してコマンドを再度実行するには，`!履歴番号` のようにする．
- コマンド履歴は，`~/.bash_history` ファイルに保存されている．

```
[ai@localhost ~]$ history
    1  exit
    2  su -
    3  exit
    (略)
   57  echo "The current directory is $(pwd)."
   58  history
[ai@localhost ~]$ !57
echo "The current directory is $(pwd)." <- 実際に実行されるコマンドが表示される．
The current directory is /home/ai.
```

bash の履歴機能:
|コマンド|内容|
|---|---|
|`↑ (Ctrl + P)`|1つ前のコマンドを表示する|
|`↓ (Ctrl + N)`|1つ次のコマンドを表示する|
|`!文字列`|実行したコマンドの中で，指定した文字列から始まるコマンドを実行する|
|`!?文字列`|実行したコマンドの中で，指定した文字列を含むコマンドを実行する|
|`!!`|直前に実行したコマンドを再実行する|
|`!履歴番号`|履歴番号のコマンドを実行する|

### 3.1.8 マニュアルの参照
- Linux では，**オンラインマニュアルページ** (**man ページ**) が標準で用意されている．
    - man ページは，`man` コマンドで表示できる．
- マニュアルを構成するファイルは，`/usr/share/man` に置かれている．
    - man ページへの検索ディレクトリは，環境変数 `MANPATH` が参照される．
        - `MANPATH` に何も指定されていない場合は，`/etc/man.config` (`/etc/man.conf`, `/etc/man_db.conf`, `/etc/manpath.config` 等) に指定されたデフォルトのリストが使われる．
- `man` コマンドは，環境変数 `PAGER` で指定されたページやプログラム (通常は `less`) で表示を行うが，好みに応じて変更することができる．

```
man [オプション] [セクション] コマンド名あるいはキーワード
```

`man` コマンドの主なオプション:
|オプション|説明|
|---|---|
|`-a`|すべてのセクションのマニュアルを表示する|
|`-f`|指定されたキーワード (完全一致) を含むドキュメントを表示する (`whatis` と同じ)|
|`-k`|指定されたキーワード (部分一致) を含むドキュメントを表示する (`apropos` と同じ)|
|`-w`|マニュアルの置かれているディレクトリを表示する|

man ページの見出し:
|見出し|説明|
|---|---|
|`NAME`|コマンドやファイルの名前と簡単な説明|
|`SYNOPSIS`|書式 (オプションや引数)|
|`DESCRIPTION`|詳細な説明|
|`OPTIONS`|指定できるオプションの説明|
|`FILES`|設定ファイルなど，関連するファイル|
|`ENVIRONMENT`|関連する環境変数|
|`NOTES`|その他の注意事項|
|`BUGS`|既知の不具合|
|`SEE ALSO`|関連項目|
|`AUTHOR`|プログラムやドキュメントの著者|

man ページの表示には，`less` コマンドというページャが使われている．

`less` の主なキー操作:
|キー操作|説明|
|---|---|
|`k`, `↑`|上方向に1行スクロール|
|`j`, `↓`|下方向に1行スクロール|
|Space, `f`|下方向に1画面スクロール|
|`b`|上方向に1画面スクロール|
|`q`|終了|
|`/検索文字列`|下方向に文字列を検索|
|`?検索文字列`|上方向に文字列を検索|
|`h`|ヘルプを表示する|

同一の名前で異なる内容を扱えるようにするため，セクション (章) が設定されている．**セクション** は，ドキュメントの内容による分類であり，Linux では次のようになっている．

セクション:
|セクション|説明|
|---|---|
|1|ユーザコマンド|
|2|システムコール (カーネルの機能を使うための関数)|
|3|ライブラリ (C言語の関数)|
|4|デバイスファイル|
|5|設定ファイル|
|6|ゲーム|
|7|その他|
|8|システム管理コマンド|
|9|Linux 独自のカーネル用コマンド|

`whatis` コマンドを使うと，指定した検索キーワードと完全にマッチした一覧が表示される．
```
[ai@localhost ~]$ whatis crontab
crontab (1)          - maintains crontab files for individual users
crontab (5)          - files used to schedule the execution of programs
```

`apropos` コマンドを使うと，指定されたキーワードがマニュアルタイトルもしくは NAME 欄に含まれるマニュアルの項目一覧を表示する．
```
[ai@localhost ~]$ apropos crontab
anacrontab (5)       - configuration file for Anacron
crontab (1)          - maintains crontab files for individual users
crontab (5)          - files used to schedule the execution of programs
crontabs (4)         - configuration and scripts for running periodical jobs
```