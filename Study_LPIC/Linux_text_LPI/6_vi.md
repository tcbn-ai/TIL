# 6. vi エディタ
## 6.1 vi の基本操作
- vi はページャであり，エディタでもある．
- vi でファイルを開いた場合のモード
    - コマンドモード
        - ページングによる行やページ単位の移動
        - 行の削除，コピー，カット，ペーストなどの編集操作
    - インサートモード
        - 文字入力を受け付ける

#### ファイルを開く
書式:
```
vi [ファイル名]
```

#### ファイルを閉じる
Esc キーを押した後，`:q` と入力する (q は quit の略)．

#### ファイルを保存する
Esc キーを押した後，`:w` と入力する (w は write の略)．
ファイルに変更内容が書き込まれて編集作業を継続できる．

#### ファイルを保存して終了する
Esc キーを押した後，`:wq` と入力する．
`w` によって変更内容が書き込まれ，`q` によってファイルを閉じる．

#### ファイルを保存せずに強制的に閉じる
Esc キーを押した後，`:q!` と入力する．
通常，編集済のファイルはそのままでは閉じることができないが，`!` をつけることで保存せずに強制的に終了できる．

<div style="page-break-before:always"></div>

## 6.2 インサートモードとコマンドモード
vi エディタを起動すると，コマンドモード (コマンドを入力するモード) でファイルが開かれる．
文字列を打ち込むにはインサートモードに切り替える必要がある．切り替えるには `i` コマンド または `a` コマンドを使う．

`vi` コマンドはスクリーンエディタと呼ばれ，基本的にカーソルがある位置に対してコマンドを実行する．

### テキストの入力
##### `i` コマンド
カーソルがある位置 (文字の前) にテキストを入力する (insert)．

実行例:
```
ai@ai-VirtualBox:~/Documents/6_vi_workspace$ cat test.txt
Apple
ai@ai-VirtualBox:~/Documents/6_vi_workspace$ vi test.txt

ai@ai-VirtualBox:~/Documents/6_vi_workspace$ cat test.txt
Appl_inserttest_e
```

カーソルが Apple の e にあると，その前にテキストが入力される．

##### `a` コマンド
カーソルがある文字の後にテキストを入力する (append)．

実行例:
```
ai@ai-VirtualBox:~/Documents/6_vi_workspace$ cat test.txt
Appl_inserttest_e
ai@ai-VirtualBox:~/Documents/6_vi_workspace$ vi test.txt

ai@ai-VirtualBox:~/Documents/6_vi_workspace$ cat test.txt
Appl_inserttest_e_appendtest_
```

カーソルが最後の文字にあると，その後にテキストが入力される．

##### `I` コマンド
行の先頭にテキストを入力する．

実行例:
```
ai@ai-VirtualBox:~/Documents/6_vi_workspace$ cat test.txt 
Appl_inserttest_e_appendtest_
ai@ai-VirtualBox:~/Documents/6_vi_workspace$ vi test.txt
 1L, 41C written
ai@ai-VirtualBox:~/Documents/6_vi_workspace$ cat test.txt 
Inserttest_Appl_inserttest_e_appendtest_
```

行の先頭にテキストが挿入される．

##### `A` コマンド
行の末尾にテキストを追加する．

実行例:
```
ai@ai-VirtualBox:~/Documents/6_vi_workspace$ cat test.txt
Inserttest_Appl_inserttest_e_appendtest_
ai@ai-VirtualBox:~/Documents/6_vi_workspace$ vi test.txt
 1L, 51C written
ai@ai-VirtualBox:~/Documents/6_vi_workspace$ cat test.txt 
Inserttest_Appl_inserttest_e_appendtest_Appendtest
```

##### 文字の削除
文字を間違えたときは，Delete や BackSpace でカーソルの前の1文字が削除できる．
動作は使う環境によって変わる．

### カーソルの移動
##### カーソルの左右移動
`h` コマンドでカーソルを左に移動．`l` コマンドでカーソルを右に移動．
Ubuntu 20 や CentOS 7 で利用できる `vi` コマンドでは，カーソルキーの左右を用いてカーソルの左右移動ができる．

##### カーソルの上下移動
`j` コマンドで下に移動．`k` コマンドで上に移動．
Ubuntu 20 や CentOS 7 で利用できる `vi` コマンドでは，カーソルキーの上下を用いてカーソルの上下移動ができる．

##### 行頭への移動
`0` コマンドを実行すると，現在の行の行頭へ移動することができる．

##### 行末への移動
`$` コマンドを実行すると，現在の行の行末へ移動することができる．

<div style="page-break-before:always"></div>

## 6.3 編集中の大きな移動
### ページ単位の移動
ctrl + `f` コマンド で次のページに移動．ctrl + `b` で前のページに移動．

### 行を指定した移動
##### 行番号を指定した移動
`:10` で 10 行目に移動．

##### コマンドを使った文書頭への移動
`gg` コマンドで文書頭に移動．

##### コマンドを使った文書末への移動
`G` コマンドで文書末に移動．

<div style="page-break-before:always"></div>

## 6.4 さまざまな編集操作
### 文字のカット・アンド・ペースト
文字をカットするコマンドと，カットした文字をペーストするコマンドを使う．

カット・アンド・ペーストで使うコマンド:
|コマンド|内容|
|---|---|
|`x`|1文字削除|
|`dd`|1行削除|
|`yy`|1行コピー|
|n`yy`|n行コピー|
|`p`|カーソルの文字の次または次の行にペースト|
|`P`|カーソルの文字の前または前の行にペースト|
|`u`|カット，ペーストを1回取り消し (アンドゥ)|

`x` コマンドで削除した最後の文字はバッファに入るので，`p` または `P` でペーストできる．

### 行のカット・アンド・ペースト
`dd` コマンドで削除したテキストはバッファに入る．

`p` コマンドの場合，カットした文字列がカーソルの下にペーストされる．

`P` コマンドの場合，カットした文字列がカーソルの上にペーストされる．

### 行のコピー・アンド・ペースト
`yy` コマンドで行全体をコピーすると，文字列はバッファに入る．バッファ内のテキストは `p` コマンドまたは `P` コマンドでペーストできる．

現在の行から下の複数行をコピーしたいときは，コピーしたい行数を `yy` コマンドの前に記述する．

### 編集の取り消し (アンドゥ)
vi エディタでは，全ての編集操作について，`u` コマンドでそれを取り消すことができる (undo)．

<div style="page-break-before:always"></div>

## 6.5 置換と検索
検索と置換に関するコマンド:
|コマンド|内容|
|---|---|
|`/検索文字列`|文字列の検索|
|`n`|下方向へ再検索|
|`N`|上方向へ再検索|
|`:対象の行s/検索文字列/置換文字列/オプション`|文字列を置換する|

### 文字列の検索
書式:
```
/文字列
```

`n` コマンドで1つ次の文字列を再検索，`N` コマンドで1つ前の文字列を再検索，押した回数だけ再検索される．

文字列を検索すると，検索した文字列がハイライト表示される．ハイライトは次の文字列を検索するまで残る．ハイライトを消すには，`:nohlsearch` コマンドを実行する．

### 文字列の置換
置換方法の指定:
|コマンド|内容|
|---|---|
|`:`n`s/old/new`|n 行目の最初の old を new に置換して終了|
|`:`n`s/old/new/g`|n 行目の全ての old を new に置換して終了|
|`:%s/old/new/g`|ファイル全体の検索語句を置換する|
|`:%s/old/new/gc`|置換のたびに確認を求める|