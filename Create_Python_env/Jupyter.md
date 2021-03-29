# Pipenv + VSCodeでJupyter Notebookを使う
## はじめに
- PipenvでもJupyter Notebookを使いたかった
- VSCodeでもJupyter Notebookを使えることを知った
## Require
- Ubuntu18 または Ubuntu20
- WSL
## 仮想環境の作成
- https://github.com/SeeKT/MyKnowledge/blob/master/Python/Ubuntu_python.md にまとめました．
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