---
marp: true
theme: default
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

# 基礎からの力学系 (第3章)
#### 参考文献
- [小室，基礎からの力学系，サイエンス社，2002](https://www.saiensu.co.jp/book_support/sgc-17/)
#### Table of contents
- 物体の落下

---
### 物体の落下
原点$O$から鉛直上向きに$x$軸を取り，高さ$x_0$の点から初速度$v_0$で投げ上げた質量$m$の物体の運動
1. 空気抵抗を無視した場合
  $$
  m \frac{d^2x}{dt^2} = -mg \ \ (3.1)
  $$
  $\rightsquigarrow$ $dx/dt = v$とおくと，
  $$
  \begin{cases}
    \frac{dx}{dt} = v \\
    \frac{dv}{dt} = -g
  \end{cases} \ \ (3.2)
  $$
  $\rightsquigarrow$ 2次元自律ベクトル場

---
時刻$t = 0$のとき，$x = x_0, v = v_0$を通る軌道は，
$$
\begin{cases}
  x(t) = \frac{1}{2}gt^2 + v_0t + x_0 \\
  v(t) = -gt + v_0
\end{cases} \ \ (3.3)
$$
で与えられる．
