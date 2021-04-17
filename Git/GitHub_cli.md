# GitHub CLIを使う
## 参考
- https://github.com/cli/cli
- https://qiita.com/ryo2132/items/2a29dd7b1627af064d7b
- https://zenn.dev/morinokami/articles/hello-github-cli
- https://github.com/cli/cli/blob/trunk/docs/install_linux.md
## GitHub CLIとは
- GitHubをコマンドラインで動かせるツール
    - GitHubが公式でやってるやつ
## インストール
```
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-key C99B11DEB97541F0
sudo apt-add-repository https://cli.github.com/packages
sudo apt update
sudo apt install gh
```
## 認証
- 自分のGitHubアカウントと連携するための認証が必要
    ```
    gh auth login
    ```
    で指示通りに進める．