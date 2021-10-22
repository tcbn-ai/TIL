---
marp: true
theme: gaia
header: ''
footer: 'Kosuke Toda ([@SeeKT](https://github.com/SeeKT))'

size: 16:9
---
<!-- paginate: true -->

<style>
img[alt~="center"] {
  display: block;
  margin: 0 auto;
}
</style>

# A Graduate Course in Applied Cryptography (Chap. 2.2)

---
## 2.2 Computational ciphers and semantic security

- perfect security の基準に従うと，鍵長はメッセージ以上でなければならない．
- この節では，短い鍵を用いて長いメッセージを暗号化するために， security requirements を緩める．

$\rightsquigarrow$ *computational feasible* adversaries のみ考慮する．
$\rightsquigarrow$ **semantic security**.

---

### 2.2.1 Definition of a computational cipher
##### Notations
- $\mathcal{K}$: finite key space
- $\mathcal{M}$: finite message space
- $\mathcal{C}$: finite ciphertext space
- $E$: encryption algorithm
- $D$: decryption algorithm

---
$(\mathcal{K}, \mathcal{M}, \mathcal{C})$ 上で定義された **computational cipher** $\mathcal{E} = (E, D)$ は，efficient algorithms $E, D$ のペアである．

ここで，$E$ は probabilistic algorithm とする．計算が確率的であることを強調するため，$E(k, m)$ を実行し，変数 $c$ を得る操作を
$$c \overset{R}{\leftarrow} E(k, m)$$
と表す．同様に，変数 $k$ を key space から一様ランダムに得る操作を
$$k \overset{R}{\leftarrow} \mathcal{K}$$
と表す．

---
ここでは，決定的な復号化アルゴリズムのみ扱う．

暗号化したメッセージを復号化したものがもとのメッセージと一致すること (**correctness requirements**) は，以下のように表される．

$\forall k \in \mathcal{K}, \forall m \in \mathcal{M},$
$$c \overset{R}{\leftarrow} E(k, m), m^{\prime} \leftarrow D(k, c) \Rightarrow m = m^{\prime} \ \text{with probability } 1.$$

以降，computational cipher を単に cipher と表す．また，encryption algorithm が deterministic である cipher を **deterministic cipher** と表す．

---
##### Remark
- deterministic cipher は Shannon cipher である．
- computational cipher が Shannon cipher であるとは限らない．
- Shannon cipher は computational cipher である必要はない．

---

### 2.2.2 Definition of semantic security