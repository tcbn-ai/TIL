# 6. コンテナのネットワーク
- コンテナ間の通信
## 6.1 3つのネットワーク
- Dockerでは，仮想的なネットワークを作り，Dockerホストとコンテナ，もしくはコンテナ間で通信できるように構成できる．
    - ```docker network ls```コマンドで確認できる．
        ```
        ubuntu@ip-172-31-39-72:~$ docker network ls
        NETWORK ID     NAME      DRIVER    SCOPE
        0470037995b8   bridge    bridge    local
        eea371a81d9a   host      host      local
        ecb1fa9b5b68   none      null      local
        ```
        - よく使われるのがbridgeネットワーク
## 6.2 bridgeネットワーク
- 既定のネットワーク
- ```docker run```するときにネットワークのオプションを指定しない場合，これが使われる．
- bridgeネットワークにおいては，それぞれのコンテナのネットワークは独立している．```-p```オプションで，どのコンテナと通信するのかを決める
- 例
    - 2つのhttpdコンテナを利用する場合
        ```
        docker run -dit --name web01 -p 8080:80 httpd:2.4
        docker run -dit --name web02 -p 8081:80 httpd:2.4
        ```
        - 片方をポート8080，もう片方をポート8081に割り当てた
### 6.2.1 コンテナに割り当てられるIPアドレスを確認する
- DockerホストやDockerコンテナは，1つの仮想的なbridgeネットワークで接続される
    - DockerホストやDockerコンテナにはIPアドレスが割り当てられる．
#### 2つのコンテナを起動する
1. 1つ目のコンテナを起動する
    ```
    docker run -dit --name web01 -p 8080:80 httpd:2.4
    ```
2. 2つ目のコンテナを起動する
    ```
    docker run -dit --name web02 -p 8081:80 httpd:2.4
    ```
#### コンテナのIPアドレスを確認する
- 方法
    1. コンテナ内で```ip```コマンドや```ifconfig```コマンドなどを実行して確認する
        - ```docker exec```を使ってコンテナ内でIPアドレスを調べるコマンドを実行する方法
        - httpdコンテナには```ip```コマンドも```ifconfig```コマンドも入っていない
    2. ```docker container inspect```コマンドを使う方法
        - コンテナに対する詳細な情報を調べるコマンド
        - NetworkSettings の部分にIPアドレスが記載されている
            ```
            ubuntu@ip-xxx-xxx-xxx-xxx:~$ docker container inspect --format="{{.NetworkSettings.IPAddress}}" web01
            172.17.0.2
            ```
            - ```--format```オプションで指定する
                - Go言語のtemplateパッケージの書式で指定する
#### DockerホストのIPアドレス
- Docker EngineをインストールしたLinux環境には，docker0というネットワークインターフェースが作られる
    - このインターフェイスを通じてbridgeネットワークに接続している
        ```
        ubuntu@ip-172-31-39-72:~$ ifconfig
        docker0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
                inet 172.17.0.1  netmask 255.255.0.0  broadcast 172.17.255.255
                inet6 fe80::42:d1ff:fefc:c0ab  prefixlen 64  scopeid 0x20<link>
                ether 02:42:d1:fc:c0:ab  txqueuelen 0  (Ethernet)
                RX packets 3  bytes 100 (100.0 B)
                RX errors 0  dropped 0  overruns 0  frame 0
                TX packets 10  bytes 772 (772.0 B)
                TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
        ```
### 6.2.2 bridgeネットワークの招待
- IPマスカレードを使って構成
    - IPアドレスを変換することで，1つのIpアドレスで通信できるようにする技術
- ```-p```オプションは，IPマスカレードのポート転送設定をしている
### 6.2.3 Dockerホスト同士の通信
- コンテナはIPアドレスを持ち，bridgeネットワークに接続されている
    - コンテナ同士はネットワークを通じて互いに自由に通信できる
    - ```-p```オプションが設定されていなくても可能
        - Dockerホスト側で受信したデータをそれぞれのDockerコンテナの特定のポートに転送する設定
        - Dockerコンテナ間の通信では，Dockerホストを経由せず直接やり取りする

#### コンテナ同士の疎通を確認する
1. 第3のコンテナを作る
    - ubuntuのイメージから，疎通確認用の第3のコンテナを作ってシェルを起動する
        - ```curl```コマンドを使うから
        ```
        ubuntu@ip-172-31-39-72:~$ docker run --rm -it ubuntu /bin/bash
        Unable to find image 'ubuntu:latest' locally
        latest: Pulling from library/ubuntu
        a70d879fa598: Pull complete 
        c4394a92d1f8: Pull complete 
        10e6159c56c0: Pull complete 
        Digest: sha256:3c9c713e0979e9bd6061ed52ac1e9e1f246c9495aa063619d9d695fb8039aa1f
        Status: Downloaded newer image for ubuntu:latest
        root@0de66f1a5531:/# 
        ```
2. 実験に必要なソフトをインストールする
    - ```ip```，```ping```，```curl```を使う
        ```
        root@0de66f1a5531:/# apt update
        root@0de66f1a5531:/# apt -y upgrade
        root@0de66f1a5531:/# apt install -y iproute2 iputils-ping curl
        ```
3. 自身のIPアドレスを確認する
    ```
    root@0de66f1a5531:/# ip addr
    1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
        link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
        inet 127.0.0.1/8 scope host lo
        valid_lft forever preferred_lft forever
    8: eth0@if9: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue state UP group default 
        link/ether 02:42:ac:11:00:04 brd ff:ff:ff:ff:ff:ff link-netnsid 0
        inet 172.17.0.4/16 brd 172.17.255.255 scope global eth0
        valid_lft forever preferred_lft forever
    ```
4. ```ping```で疎通確認する
    - web01 (172.17.0.2) に対して
        ```
        root@0de66f1a5531:/# ping -c 4 172.17.0.2
        PING 172.17.0.2 (172.17.0.2) 56(84) bytes of data.
        64 bytes from 172.17.0.2: icmp_seq=1 ttl=64 time=0.092 ms
        64 bytes from 172.17.0.2: icmp_seq=2 ttl=64 time=0.057 ms
        64 bytes from 172.17.0.2: icmp_seq=3 ttl=64 time=0.056 ms
        64 bytes from 172.17.0.2: icmp_seq=4 ttl=64 time=0.054 ms

        --- 172.17.0.2 ping statistics ---
        4 packets transmitted, 4 received, 0% packet loss, time 3068ms
        rtt min/avg/max/mdev = 0.054/0.064/0.092/0.015 ms
        ```
    - web02 (172.17.0.3) に対して
        ```
        root@0de66f1a5531:/# ping -c 4 172.17.0.3
        PING 172.17.0.3 (172.17.0.3) 56(84) bytes of data.
        64 bytes from 172.17.0.3: icmp_seq=1 ttl=64 time=0.076 ms
        64 bytes from 172.17.0.3: icmp_seq=2 ttl=64 time=0.061 ms
        64 bytes from 172.17.0.3: icmp_seq=3 ttl=64 time=0.054 ms
        64 bytes from 172.17.0.3: icmp_seq=4 ttl=64 time=0.067 ms

        --- 172.17.0.3 ping statistics ---
        4 packets transmitted, 4 received, 0% packet loss, time 3063ms
        rtt min/avg/max/mdev = 0.054/0.064/0.076/0.008 ms
        ```
5. コンテンツを取得する
    - web01 (172.17.0.2) に対して
        ```
        root@0de66f1a5531:/# curl http://172.17.0.2/
        <html><body><h1>It works!</h1></body></html>
        ```
    - web02 (172.17.0.3) に対して
        ```
        root@0de66f1a5531:/# curl http://172.17.0.3/
        <html><body><h1>It works!</h1></body></html>
        ```
6. IPアドレス以外では接続できないことを確認する
    ```
    root@0de66f1a5531:/# ping -c 4 web01     
    ping: web01: Name or service not known
    ```
7. 後始末
    - ```exit```で終了