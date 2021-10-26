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

# A Graduate Course in Applied Cryptography (Chap. 2.3)

---
## 2.3 Mathematical details

ここまで，*efficient* や *negligible* という用語を特に数学的な定義を与えることなく用いてきた．

- computational cipher は *efficient* な 暗号化/復号化 アルゴリズムを持つ必要がある．
- semantically secure cipher のために，*efficient* adversary が Attack Game 2.1 で *negligible* advantage を持っていることが求められる．

$\rightsquigarrow$ この節では，これらの用語の数学的な定義を与える．

---

数学的な定義に入る前に，直感的な説明を述べる．

- an efficient encryption or decryption algorithm
    - とても素早く計算できる暗号化/復号化アルゴリズム
        - 10 - 100 computer cycles / byte 程度
- an efficient adversary
    - 大きいが feasible な時間 (やリソース) を用いて計算できるアルゴリズム．
- an adversary's advantage as being negligible
    - 全ての実用的な目的に対して，adversary の advantage がゼロとみなせる．

---

### 2.3.1 Negligible, super-poly, and poly-bounded functions

##### negligible function
直感的には，関数 $f: \mathbb{Z}_{\geq 0} \to \mathbb{R}$ が $n \to \infty$ で $0$ に収束し，その収束速度がどのような多項式の inverse よりも大きいこと．

###### Def. 2.5 
関数 $f: \mathbb{Z}_{\geq 1} \to \mathbb{R}$ が **negligible** であるとは，任意の $c \in \mathbb{R}_{> 0}$ に対して，$n_0 \in \mathbb{Z}_{\geq 1}$ が存在し，任意の $n \geq n_0$ に対して $|f(n)| < 1/n^c$ であることである．

---

###### Th 2.11 
関数 $f: \mathbb{Z}_{\geq 1} \to \mathbb{R}$ が negligible であるための必要十分条件は，任意の $c > 0$ に対して
$$\lim_{n \to \infty} f(n) n^c = 0$$
が成り立つことである．

(証明略)

---

###### negligible function の例
$$2^{-n}, 2^{-\sqrt{n}}, n^{-\log n}.$$

###### non-negligible function の例
$$\frac{1}{1000n^4 + n^2 \log n}, \frac{1}{n^{100}}$$

---
##### super-poly, poly-bounded

###### Def. 2.6
関数 $f: \mathbb{Z}_{\geq 1} \to \mathbb{R}$ で，$1/f$ が negligible であるものは **super-poly** と呼ばれる．

poly-bounded function とは，ある多項式で抑えられる関数である．

###### Def. 2.7
関数 $f: \mathbb{Z}_{\geq 1} \to \mathbb{R}$ が **poly-bounded** であるとは，$c, d \in \mathbb{R}_{>0}$ が存在して，任意の非負整数 $n \geq 0$ に対して $|f(n)| \leq n^c + d$ が成り立つことである．

---

### 2.3.2 Computational ciphers: the formalities

ここまで，computational cipher $\mathcal{E} = (E, D)$ は $(\mathcal{K}, \mathcal{M}, \mathcal{C})$ 上で定義され，$\mathcal{K}$ は鍵空間，$\mathcal{M}$ は平分空間，$\mathcal{C}$ は暗号文空間で，それぞれ有限集合であるとしていた．
$\rightsquigarrow$ 正確な定義を述べる．

数理モデルでは，鍵，平文，暗号文空間の $\mathcal{E}$ の族に以下を関連付ける．

- **security parameter** $\lambda$: 正の整数．
- **system parameter** $\Lambda$: bit string.

---

よって，有限集合 $\mathcal{K}, \mathcal{M}, \mathcal{C}$ の代わりに有限集合の族
$$ \{\mathcal{K}_{\lambda, \Lambda} \}_{\lambda, \Lambda}, \; \{\mathcal{M}_{\lambda, \Lambda} \}_{\lambda, \Lambda}, \; \{\mathcal{C}_{\lambda, \Lambda} \}_{\lambda, \Lambda} $$
を用いる．定義のために，これを bit strings の集合とみなす．

アイデアは，「cipher $\mathcal{E}$ が配置 (deploy) されるときに，security parameter $\lambda$ が固定される」というもの．

$\lambda$ が大きいと security の強度が高いが，暗号化と復号に時間がかかる
$\rightsquigarrow$ security parameter は，security と efficiency の trade-off を調整するもの．

---

$\lambda$ が選ばれた後，cipher に特有のアルゴリズムを用いて $\Lambda$ が生成される．

アイデアは，「system parameter $\Lambda$ は cipher の fixed instance に詳細な説明を与える」というもの．
$$(\mathcal{K}, \mathcal{M}, \mathcal{C}) = (\mathcal{K}_{\lambda, \Lambda}, \mathcal{M}_{\lambda, \Lambda}, \mathcal{C}_{\lambda, \Lambda})$$

- fixed instance が 大規模なシステムにデプロイされ，多くの部分で使われる．
- $\lambda, \Lambda$ は public であり，adversary を含め全員が知ることができる．