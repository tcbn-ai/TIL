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

# A Graduate Course in Applied Cryptography (Chap. 2.1)

---
## 2. Encryption
この章では，以下の状況を想定する．

- Alice と Bob が秘密の鍵 $k$ を共有している．
- 盗聴者が存在する状況下で，メッセージ $m$ の秘匿性を維持したままネットワークを介して送信したい．

###### Remark
- この章で紹介する技術が "secure communication" に関連する課題を全て解決するわけではない．

---

## 2.1 Shannon ciphers and perfect security
### 2.1.1 Definition of a Shannon cipher
ここでは，**Shanon cipher** と呼ばれる，暗号化の基本的なメカニズムを紹介する．

##### Notation
- $\mathcal{K}$: 鍵空間 (key space)
- $\mathcal{M}$: 平文空間 (message space)
- $\mathcal{C}$: 暗号文空間 (cipertext space)

---
#### Shannon cipher
Shannon cipher は，$(\mathcal{K}, \mathcal{M}, \mathcal{C})$ 上で定義される組
$$\mathcal{E} = (E, D)$$ 
である．ただし，

- $E: \mathcal{K} \times \mathcal{M} \to \mathcal{C}$ は暗号化関数 (encryption function).
    - $c = E(k, m)$ は，$k$ の下での $m$ の暗号化．
- $D: \mathcal{K} \times \mathcal{C} \to \mathcal{M}$ は復号化関数 (decryption function).
    - $m = D(k, c)$ は，$k$ の下での $c$ の復号化．

---

ここで，cipher は，次の **correctness property** を満たす必要がある．

$$\forall k \in \mathcal{K}, \forall m \in \mathcal{M}, D(k, E(k, m)) = m.$$

これは，任意の鍵に対して，任意の平文を暗号化して復号したものがもとの平文に一致するということである．

ここで，Alice が Bob に $c = E(k, m) \in \mathcal{C}$ を送ったとする．Bob が $c$ を復号化したときに，$D(k, c) = m$ となるためには，$c$ が Alice と Bob の通信の間に改ざんされていないことが求められる．

以下，$\mathcal{K}, \mathcal{M}, \mathcal{C}$ は有限集合とする．

---
##### Ex. 2.1 A one-time pad
- Shannon cipher $\mathcal{E} = (E, D)$ で，鍵，メッセージ，暗号文の長さが全て等しいものである．
    - $\mathcal{E}$ は $(\mathcal{K}, \mathcal{M}, \mathcal{C})$ 上で定義され，fixed parameter $L$ に対して
    $$\mathcal{K} \coloneqq \mathcal{M} \coloneqq \mathcal{C} \coloneqq \{0, 1\}^L.$$
- 暗号化関数，復号化関数は以下で定義．
    $$E(k, m) \coloneqq k \oplus m \\ D(k, m) \coloneqq k \oplus c$$
    - $\oplus$ は bit-wise explusive-OR.

---

$\forall x, y, z \in \{0, 1\}^L$ に対して以下が成立．
$$x \oplus y = y \oplus x, \; x \oplus (y \oplus z) = (x \oplus y) \oplus z, \\ x \oplus 0^L = x, \; x \oplus x = 0^L.$$

$\rightsquigarrow$ $\mathcal{E}$ に対して correctness property が成立．
$$D(k, E(k, m)) = D(k, k \oplus m) = k \oplus (k \oplus m) \\ = (k \oplus k) \oplus m = 0^L \oplus m = m, \; \; \forall k, m \in \{0, 1\}^L.$$

---

### 2.1.2 Perfect security
ここでは，"secure" な cipher を数学的に定義する．
$\rightsquigarrow$ **perfect security** が "gold standard" for security.

- one-time pad は perfect security を満たす．
    - key が message と同じ長さで，実用的ではない．
- 任意の perfect secure cipher は，message space と同じサイズの key space を持たなければならない．

$\rightsquigarrow$ security の定義を弱めたい

---

Perfect security は，「暗号文の知識がもとのメッセージを推測する可能性を高めるか？」という観点で定義されている．

###### Def. 2.1 (Perfect security)
$\mathcal{E} = (E, D)$ を，$(\mathcal{K}, \mathcal{M}, \mathcal{C})$ 上で定義された Shannon cipher とする．確率変数 $\bm{k}$ が，$\mathcal{K}$ 上で一様に分布するような試行を考える．

$\mathcal{E}$ が **perfectly secure** Shannon cipher
$\overset{\text{def}}{\Longleftrightarrow} \forall m_0, m_1 \in \mathcal{M}, \forall c \in \mathcal{C},$ 
$$\mathrm{Pr}[E(\bm{k}, m_0) = c] = \mathrm{Pr}[E(\bm{k}, m_1)] = c.$$ 

---

上で定義した perfect security と同値な条件を示す．

###### Th. 2.1
$\mathcal{E} = (E, D)$ を $(\mathcal{K}, \mathcal{M}, \mathcal{C})$ 上で定義された Shannon cipher とする．以下は同値．

1. $\mathcal{E}$ は perfectly secure
1. $\forall c \in \mathcal{C}, \exists N_c \ \text{s.t.} \ \forall m \in \mathcal{M},$
    $$|\{k \in \mathcal{K}:E(k, m) = c\}| = N_c.$$
1. 確率変数 $\bm{k}$ が $\mathcal{K}$ 上に一様に分布するならば，各 $m$ に対して確率変数 $E(\bm{k}, m)$ は同分布である．

---

###### Th. 2.2
One-time pad は，perfectly secure Shannon cipher である．

###### Proof
$(\mathcal{K}, \mathcal{M}, \mathcal{C})$ 上で定義された Shannon cipher $\mathcal{E} = (E, D)$ が one-time pad であるとする．ただし，$\mathcal{K} \coloneqq \mathcal{M} \coloneqq \mathcal{C} \coloneqq \{0, 1\}^L$ とする．このとき，
$$\forall m \in \{0, 1\}^L, \forall c \in \{0, 1\}^L, \exists k \in \{0, 1\}^L \ \text{s.t.} \ k \oplus m = c,$$
つまり，$k \coloneqq m \oplus c$ である．つまり，$\mathcal{E}$ は Th. 2.1 の条件2を満たす ($N_c = 1 \ \forall c \in \mathcal{C}$)． 

---

盗聴者が暗号文に対して predicate $\phi$ を適用している状況を考える．ただし，$\phi: \mathcal{C} \to \{0, 1\}$ は，$\mathcal{C}$ 上の boolean-valued function.
$\rightsquigarrow$ Perfect security は，暗号文に対する predicate がメッセージの何の情報も漏らさないことを保証する．

###### Th. 2.3
$\mathcal{E} = (E, D)$ を $(\mathcal{K}, \mathcal{M}, \mathcal{C})$ 上で定義された Shannon cipher とする．確率変数 $\bm{k}$ が，$\mathcal{K}$ 上で一様に分布するような試行を考える．このとき，$\mathcal{E}$ が perfectly secure であることの必要十分条件は以下．
$\forall \phi: \text{predicate on } \mathcal{C}, \forall m_0, m_1 \in \mathcal{M},$
$$\mathrm{Pr}[\phi(E(\bm{k}, m_0))] = \mathrm{Pr}[\phi(E(\bm{k}, m_1))].$$

---
また，perfect security は，暗号文を見た後でも平文に対する情報が増えないということを保証する．

###### Th. 2.4
$\mathcal{E} = (E, D)$ を $(\mathcal{K}, \mathcal{M}, \mathcal{C})$ 上で定義された Shannon cipher とする．確率変数 $\bm{k}, \bm{m}$ に対する以下の試行を考える．
- $\bm{k}$ は $\mathcal{K}$ 上で一様に分布する．
- $\bm{m}$ は $\mathcal{M}$ 上の分布．
- $\bm{k}$ と $\bm{m}$ は独立．

--- 

確率変数 $\bm{c} \coloneqq E(\bm{k}, \bm{m})$ を定義する．このとき，以下が成り立つ．
- $\mathcal{E}$ が perfectly secure ならば，$\bm{c}$ と $\bm{m}$ は独立である．
- 逆に，$\bm{c}$ と $\bm{m}$ が独立で，各メッセージ $m \in \mathcal{M}$ が非ゼロの確率で生じるならば，$\mathcal{E}$ は perfectly secure である．

ここで，「$\bm{m}$ と $\bm{k}$ が独立な確率変数である」という仮定は理にかなっている．

---

### 2.1.3 The bad news
One-time pad は perfectly secure な Shanon cipher で最も鍵の長さが短い．

###### Th. 2.5
$\mathcal{E} = (E, D)$ を $(\mathcal{K}, \mathcal{M}, \mathcal{C})$ 上で定義された Shannon cipher とする．$\mathcal{E}$ が perfectly secure ならば，$|\mathcal{K}| \geq |\mathcal{M}|$ である．