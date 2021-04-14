# Pipenv + VSCodeでJupyter Notebookを使う
## はじめに
- PipenvでもJupyter Notebookを使いたかった
- VSCodeでもJupyter Notebookを使えることを知った
## Require
- Ubuntu18 または Ubuntu20
- WSL
## pipの導入 (Linuxの場合)
- 参考: https://qiita.com/123h4wk/items/d5aece92d1ee47ce603c
- シェルを2つ作った．
1. シェルに実行権限を与える
  ```
  chmod 755 install_pyenv.sh
  chmod 755 install_python3.sh
  ```
2. 順に実行
  ```
  ./install_pyenv.sh
  ./install_python3.sh
  ```
3. ローカルで使用するPythonを指定する．
  - 例: ~/Python_env/ でPython3.7.10を有効にする
    ```
    mkdir Python_env && cd Python_env
    pyenv local 3.7.10
    ```
4. 確認
  ```
  python --version
  pip --version
  ```
## pipenvの導入
- これは上で作ったlocal env以下のディレクトリで行う．
1. インストール
  ```
  pip install pipenv
  ```
2. アップグレード
  ```
  pip install --upgrade pipenv
  ```

## pipenvの使い方
### 仮想環境を作る
#### 初めて仮想環境を作るとき
1. 仮想環境を作る (Pipfileが作られる)
  ```
  pipenv --python 3
  ```
  - これはpython3系の仮想環境を作っている
2. 仮想環境にパッケージをインストール
  ```
  pipenv install --skip-lock numpy scipy ...
  ```
  - --skip-lockでPipfile.lockが作られないようにしている．
#### 既にPipfileがあるときで，その設定をもとに仮想環境を作りたいとき
1. Pipfileの設定をインストールする
  ```
  pipenv install --skip-lock
  ```
  - これでPipfileに記述されている通りの仮想環境をローカルに作ることができる
### 仮想環境の操作
1. 仮想環境に入る
  ```
  pipenv shell
  ```
  - これで前に(仮想環境の名前)がついていたらok
2. 仮想環境から出る
  ```
  exit
  ```
3. 仮想環境を消す
  ```
  pipenv --rm
  ```
4. 仮想環境のパスを確認する
  ```
  pipenv --venv
  ```

仮想環境に入ったら，```python *.py```とすると，その仮想環境のPython versionで実行される
## ipykernelとjupyterの導入
- 仮想環境が作成されているものとします．
- ipykernelとjupyterのinstall
    ```
    pipenv install ipykernel jupyter
    ```
- 仮想環境に入り，jupyterで使うkernelを作成する
    ```
    pipenv shell
    python -m ipykernel install --user --name=<name>
    ```
    - \<name>は適当な名前 (e.g. "Py_env_39")
- VSCodeの拡張機能 (Jupyter) をinstall
- 例: Py_env_39という仮想環境でkernel名がPy_env_39
    ![vs_jupyter](https://raw.githubusercontent.com/SeeKT/MyKnowledge/images/vscode_jupyter/jupyter.png "VsCodeでJupyter")