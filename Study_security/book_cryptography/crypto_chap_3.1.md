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

# A Graduate Course in Applied Cryptography (Chap. 3.1)

---
## 3.1 Pseudo-random generators
One-time pad は，鍵，平文，暗号文がすべて $L$-bit string だった．
$\rightsquigarrow$ 鍵長を短くしたい．

idea: 

- $\ell$-bit $(\ell \ll L)$ の "seed" $s$ を暗号化鍵に使う．
- この seed を $L$-bit に引きのばす．
    - $s$ は，$\ell$-bit strings を $L$-bit string にうつす efficient, deterministic algorithm $G$ によって引きのばされる．

---

鍵空間と平文，暗号文空間は以下で定義される．

- key space: $\{0, 1\}^{\ell}$
- message and ciphetext space: $\{0, 1\}^{L}$

$s \in \{0, 1\}^{\ell}, m, c \in \{0, 1\}^{L}$ に対して暗号化と復号化は以下で定義される．

$$E(s, m) \coloneqq G(s) \oplus m, \; \; D(s, c) \coloneqq G(s) \oplus c.$$

この modified one-time pad は，**stream cipher** と呼ばれ，$G$ は **pseudo-random generator** と呼ばれる．