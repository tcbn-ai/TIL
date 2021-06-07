---
marp: true
theme: default
header: ''
footer: 'Kosuke Toda ([@SeeKT](https://github.com/SeeKT))'

size: 16:9
---
<!-- paginate: true -->
# 基礎からの力学系 (第2章)
#### 参考文献
- [小室，基礎からの力学系，サイエンス社，2002](https://www.saiensu.co.jp/book_support/sgc-17/)
#### Table of contents
- 連続時間力学系

---
### 連続時間力学系 ― ベクトル場 ―
- 通常の微分積分学の教科書で扱われる微分方程式の定義と，力学系理論で扱われる微分方程式との関係について．
- 独立変数を$t$とする．

###### Def 2.1
1. $n$階常微分方程式
- $F: D \ (\subset \mathbb{R}^{n + 2}) \to \mathbb{R}$: $n + 2$変数実数値関数 $(n \geq 1)$
    $$
    F(t, x, x^{\prime}, \ldots, x^{(n)}) = 0 \ \ (2.1)
    $$
    を$n$階常微分方程式という．

---
###### Def 2.1 (続き)
2. 正規形の$n$階常微分方程式
- $f: D_0 \ (\subset \mathbb{R}^{n + 1}) \to \mathbb{R}$: $n + 1$変数実数値関数
    $$
    x^{(n)} = f(t, x, x^{\prime}, \ldots, x^{(n - 1)}) \ \ (2.2)
    $$
    を正規形の$n$階常微分方程式という．

3. $1$階連立常微分方程式 / 常微分方程式系
$f_1, \ldots, f_n: D_0 \to \mathbb{R}$に対して，
$$
\begin{cases}
    \frac{dx_1}{dt} = f_1(t, x_1, \ldots, x_n) \\
    \cdots \\
    \frac{dx_n}{dt} = f_n(t, x_1, \ldots, x_n)
\end{cases} \ \ (2.3)
$$
を$1$階連立常微分方程式という．

---

$1$階連立常微分方程式は，$\boldsymbol{x} = (x_1, \ldots, x_n) \in \mathbb{R}^n$および写像$g: \mathbb{R} \times \mathbb{R}^n \to \mathbb{R}^n$,
$$
g(t, \boldsymbol{x}) = (f_1(t, x_1, \ldots, x_n), \ldots, f_n(t, x_1, \ldots, x_n)) \ \ (2.4)
$$
によって，
$$
\frac{d \boldsymbol{x}}{dt} = g(t, \boldsymbol{x}) \ \ (2.5)
$$
のように表される ($\mathbb{R}^n$における常微分方程式)．以下，$\dot{\boldsymbol{x}} \coloneqq d\boldsymbol{x}/dt$とする．

$\rightsquigarrow$ 連続時間力学系を表現する代表的な数学モデル

ODE (2.5) において，写像$g$が時間$t$を陽に含むか含まないかは，力学系理論での扱いに違いが生じる．
- 自律系
    - 写像$g$が時間$t$を陽に含まない場合

---
###### Def 2.2 (自律系)
1. $\boldsymbol{x} \coloneqq (x_1, \ldots, x_n) \in \mathbb{R}^n$とする．$f: D \ (\subset \mathbb{R}^n) \to \mathbb{R}$を，
    $$
    f(\boldsymbol{x}) = (f_1(\boldsymbol{x}), \ldots, \boldsymbol{x})^{\mathrm{T}} \ \ (2.6)
    $$
    とする．このとき，ODE
    $$
    \dot{\boldsymbol{x}}  = f(\boldsymbol{x}) \ \ (2.7) \Longleftrightarrow \begin{cases}
        \dot{x}_1 = f_1(x_1, \ldots, x_n) \\
        \cdots \\
        \dot{x}_n = f_n(x_1, \ldots, x_n)
    \end{cases} \ \ (2.8)
    $$
    を自律系という．

---
###### Def 2.2 (続き)
2. $D$を相空間，$D$の各点$\boldsymbol{x}$にベクトル$f(\boldsymbol{x})$を対応させる写像
    $$
    f: \boldsymbol{x} \mapsto f(\boldsymbol{x})
    $$
    をベクトル場という．
    - ベクトル場はODEを幾何学的に表現したもの．力学系の理論ではベクトル場はODEと同じ意味で使われることが多い．
3. 区間$I \subset \mathbb{R}$で定義された曲線$\boldsymbol{x}: I \to \mathbb{R}^n$が
    $$
    \dot{\boldsymbol{x}} = f(\boldsymbol{x}(t)) \ \ (2.10)
    $$
    を満たすとき，$\boldsymbol{x}$はODE (2.7)の解 (解曲線) であるという．
    - $\boldsymbol{x}(0)$: 初期値
    - ODEの解$\boldsymbol{x}$は，ベクトル場の軌道 (orbit) とも呼ばれる．

---
###### Def 2.2 (続き)
4. $I \subset \mathbb{R}$を$0$を含む開区間，$D \subset \mathbb{R}^n$とする．写像$\varphi: I \times D \to \mathbb{R}^n$が$\varphi(0, \boldsymbol{x}_0) = \boldsymbol{x}_0$を満たし，各$\boldsymbol{x}_0 \in D$を固定するとき，
    $$
    \frac{d \varphi(t, \boldsymbol{x}_0)}{dt} = f(\varphi(t, \boldsymbol{x}_0)) \ \ (2.11)
    $$
    を満たすならば，$\varphi$はODE (2.7)の流れ (flow) であるという (ベクトル場(2.9)の流れとも呼ばれる)．

---
###### 例 2.1
