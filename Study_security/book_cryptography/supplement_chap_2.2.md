# Supplement of chapter 2.2
## The proof of Th 2.7

##### Th 2.7
$(\mathcal{K}, \mathcal{M}, \mathcal{C})$ 上で定義された $\mathcal{E} = (E, D)$ を考える．$\mathcal{E}$ が semantically secure ならば，$\mathcal{E}$ は secure against message recovery である．

##### Proof
$\mathcal{E}$ が semantically secure であることを仮定する．このとき，$\mathcal{E}$ が secure against message recovery であることを示す．

$\mathcal{E}$ が secure against message recovery であることを示すには，Attack Game 2.2 において，任意の efficient adversary $\mathcal{A}$ は negligible advantage を持つことを示す必要がある．これを示すために，任意の efficient adversary $\mathcal{A}$ (given) に対して，$\mathcal{A}$ の message recovery advantage $MR\mathrm{adv}[\mathcal{A}, \mathcal{E}]$ が negligible であることを示す．$p$ を message recovery game において $\mathcal{A}$ が勝利する確率とすると，定義より，
$$MR\mathrm{adv}[\mathcal{A}, \mathcal{E}] = |p - 1/|\mathcal{M}||$$
である．

$\mathcal{A}$ から Attack Game 2.1 における semantic security advantage が以下のようになる efficient adversary $\mathcal{B}$ を構成したとする．
$$MR\mathrm{adv}[\mathcal{A}, \mathcal{E}] \leq SS\mathrm{adv}[\mathcal{B}, \mathcal{E}]. \tag{2.5}$$
$\mathcal{B}$ は efficient であり，$\mathcal{E}$ は semantically secure であると仮定していることから，(2.5) の右辺は negligible である．よって，$MR\mathrm{adv}[\mathcal{A}, \mathcal{E}]$ も negligible である．

よって，どのように (2.5) を満たす $\mathcal{B}$ を構成するかということを示せば良い．

$\mathcal{B}$ の動作を以下に示す．

- Adversary $\mathcal{B}$ は，2つのランダムなメッセージ $m_0, m_1 \in \mathcal{M}$ を生成し，それを SS challenger に送る．
- SS challenger は，暗号文 $c$ を $\mathcal{B}$ に送る．$\mathcal{B}$ はそれを $\mathcal{A}$ に送る．
    - あたかも $\mathcal{A}$ の MR challenger から来たかのように．
- $\mathcal{A}$ が message $\hat{m}$ を出力するとき，$\mathcal{B}$ は，$\hat{b}$ を以下のように出力する．
    $$\hat{b} = \begin{cases} 1 & \text{if } \hat{m} = m_1, \\ 0 & \text{otherwise}. \end{cases}$$

ここで，Bの実行時間は基本的にAの実行時間と同じであることに注意する．次に，$\mathcal{B}$ の SS advantage を分析する．

$b = 0, 1$ に対して，$p_b$ を $\mathcal{B}$ の SS challenger が $m_b$ を暗号化したときに $\mathcal{B}$ が $1$ を出力する確率とする．定義より，
$$SS\mathrm{adv}[\mathcal{B}, \mathcal{E}] = |p_1 - p_0|$$
である．

- $c = E(k, m_1)$ のとき，$p_1$ は $\mathcal{A}$ が message recovery game に勝利する確率に等しい．
    $\rightsquigarrow$ $p_1 = p$.
- $c = E(k, m_0)$ のとき，$\mathcal{A}$ の出力は $m_1$ に依らない．
    $\rightsquigarrow$ $p_0 = 1/|\mathcal{M}|$.

よって，
$$SS\mathrm{adv}[\mathcal{B}, \mathcal{E}] = |p_1 - p_0| = |p - 1/|\mathcal{M}|| = MR\mathrm{adv}[\mathcal{A}, \mathcal{E}]$$
を得るので，(2.5) が示される．