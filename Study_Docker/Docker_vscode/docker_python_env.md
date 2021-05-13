# Docker containerとしてPython環境を構築する
## 目的
- Python環境を構築したいけど，手元のPCの環境を汚したくない
- 失敗してもやり直したい

## 環境
- ホストOS
    - Ubuntu20.04
        - Docker導入済み
        - ```../shellscript/install_docker.sh```
- Docker Image
    - [python](https://hub.docker.com/_/python)の[3.8.10-buster](https://github.com/docker-library/python/blob/e0e01b8482ea14352c710134329cdd93ece88317/3.8/buster/Dockerfile)

## やり方
- [tcbn-ai/Docker_python_env](https://github.com/tcbn-ai/Docker_python_env)に載せている．