# CasADiの使い方
## はじめに
最適制御問題を数値的に解くためのツールとして，CasADiを用いる．使い方を勉強する．
### 参考
- [CasADi's documentation](https://web.casadi.org/docs/)
- [CasADi's GitHub Repository](https://github.com/casadi/casadi)

### Install
```bash
pip install casadi
```

## Documentについて
以下，ドキュメントの解釈を行う．
### 1. Introduction
- CasADiは，gradient-basedの数値最適化 (特に最適制御に重点をおいている) のためのツール．
- ユーザに最適制御問題を入力させ，その解を返すわけではなく，最適制御問題のソルバーを少しのプログラミング作業で効率的に実装するために使用できる "building block" を提供するもの．

### 2. Obtaining and installing
- open-source tool
- C++で書かれている．front-endにはPythonもある．

### 3. Symbolic framework
- CasADiのcoreは， "self-contained symbolic framework" であること．
    - MATLABのような "everything-is-a-matrix" 構文で記号式を構築できる．

#### 3.1. The `sx` symbols
