# UbuntuにKindleを入れる
## 参考
- https://www.kkaneko.jp/tools/server/wine.html
- https://qiita.com/nanbuwks/items/b3fdcfcaedb4e4d04ce3
## 手順
1. (Ubuntu 18.04) FAudioのインストール
    ```
    wget https://download.opensuse.org/repositories/Emulators:/Wine:/Debian/xUbuntu_18.04/amd64/libfaudio0_19.07-0~bionic_amd64.deb
    sudo dpkg -i libfaudio0_19.07-0~bionic_amd64.deb
    ```
    - うまくいかない場合は
        ```
        sudo apt install ./libfaudio0_19.07-0~bionic_amd64.deb
        sudo apt --fix-broken install
        ```
        を試したあとに
        ```
        sudo dpkg -i libfaudio0_19.07-0~bionic_amd64.deb
        ```
        を実行する．
2. Wineのインストール
    - install_wine.shにシェルを作った．
3. Kindleダウンロード
    - https://kindle-for-pc.jp.uptodown.com/windows/download/1179941
    からexeファイルをダウンロードして，
    ```
    wine kindle-for-pc-1-17-44183.exe
    ```
    - 怒られたので，
        ```
        sudo apt-get install wine32-development
        ```
        を実行後に
        ```
        wine kindle-for-pc-1-17-44183.exe
        ```
        を実行．
    - 何故かアプリケーションが立ち上がらなかった．
        - 原因がわからないが，Ubuntu18はwineでエラーがかなり出るっぽいです．
4. Ubuntuのアップデート
    - Ubuntu20にアップデートしたらいける可能性があったので，アップデートしました．
        ```
        sudo apt update
        sudo apt install update-manager
        sudo apt dist-upgrade
        sudo do-release update -d
        ```
5. Wineの再インストール
    - 上記シェルの実行
    - さらに，winetrickを入れたあとに```winetricks cjkfonts```を入れる．
6. Kindleダウンロード
    - 古いものではうまくいかない可能性があるので，拾えるもので最も新しいバージョンにする．
    - https://kindle-for-pc.jp.uptodown.com/windows
    - 最新版をインストール