# Docker上でGitHubのリポジトリを使う + VSCodeで動かす
## 参考
- https://qiita.com/Y-Kanoh/items/94b3ea3df97fcd1546ce
- https://qiita.com/yagince/items/deba267f789604643bab
- https://stackoverflow.com/questions/65644782/how-to-install-pip-for-python-3-9-on-ubuntu-20-04
- https://biomedicalhacks.com/2020-12-01/docker-jupyter/
## 前提
- Dockerが導入済み
## 1. sshキー作成用のコンテナの準備
- GitHubとの接続用のsshキーを事前に作成する
    - ホストOSでコンテナを作成し，中に入る
        ```
        [Host OS]
        # sshキー作成用のコンテナの作成
        docker run -itd --name make-ssh-key ubuntu:20.04
        # コンテナ内に入る
        docker exec -it make-ssh-key /bin/bash
        ```
    - コンテナ内でsshキーを作成し，コンテナから出る
        ```
        apt -y update
        apt -y upgrade
        apt -y install git
        cd /root
        # 何もなければ3回Enter
        ssh-keygen -t rsa -b 4096 -C [comment]
        # sshキーをGitHubに登録
        cat /root/.ssh/id_rsa.pub   # 表示されたものをコピー
        exit
        ```
    - ホストOSに，コンテナ内のsshキーをコピー
        ```
        docker cp make-ssh-key:/root/.ssh [working dir]
        # コピーできたかを確認
        ls -a
        # sshキー作成用のコンテナの削除
        docker stop make-ssh-key
        docker rm make-ssh-key
        # 削除されているかを確認
        docker ps -a
        ```
        - もともとホストOSに.sshディレクトリがあるときは適当なディレクトリを作ってその中にコピーしないと危ない
    
## 2. dockerfileの準備
- 今回の目的
    - Docker内で自分のリポジトリを使う
    - python3.9環境をDocker内に作る
- 参考: https://qiita.com/Y-Kanoh/items/94b3ea3df97fcd1546ce
    ```dockerfile
    FROM ubuntu:20.04
    # タイムゾーンの指定を回避する
    ## 参考: https://qiita.com/yagince/items/deba267f789604643bab
    ENV DEBIAN_FRONTEND=noninteractive

    # install git
    RUN apt -y update && apt -y upgrade
    RUN apt -y install git curl

    # add ssh key (.sshをこのdockerfileと同階層に配置)
    ADD .ssh /root/.ssh
    RUN chmod 600 /root/.ssh/*

    # install python 3.9
    ## 参考: https://stackoverflow.com/questions/65644782/how-to-install-pip-for-python-3-9-on-ubuntu-20-04
    ## add PPA
    RUN apt -y install software-properties-common
    RUN add-apt-repository ppa:deadsnakes/ppa
    RUN apt-get -y install python3.9 python3.9-dev python3.9-distutils
    ## install pip
    RUN curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
    RUN python3.9 get-pip.py
    ## install pipenv
    RUN pip install pipenv

    # プロジェクトをクローンするディレクトリ
    ## /usr/local 以下に自分のリポジトリがクローンされる
    WORKDIR /usr/local
    RUN git clone git@github.com:[user name]/[repositiory].git
    ```

## 3. コンテナイメージの作成とVSCodeの利用
- 参考: https://biomedicalhacks.com/2020-12-01/docker-jupyter/
1. dockerfileと同じ階層に```.ssh```ディレクトリを配置して，Dockerイメージを作成する．
2. dockerfileがあるディレクトリで```code ./```．
3. VSCodeの拡張機能としてRemote Containersをインストール．
4. VSCodeの左下の緑の部分をクリック．```Reopen in Container```を選択し，```From Dockerfile```を選択．
    - 初回はイメージのビルドが作成される．
5. プロジェクトフォルダに```.devcontainer```が作成され，その下に```devcontainer.json```が作成される．

## 4. 使用時
- VSCodeのターミナル (下のプル) で
    ```
    cd /usr/local/[repository]
    code ./
    ```
    とすると，自分のリポジトリをVSCodeで開ける．
- Jupyter NotebookのようなGUIの操作もできた．
- VSCodeの拡張機能でgit pushやpullもできる．