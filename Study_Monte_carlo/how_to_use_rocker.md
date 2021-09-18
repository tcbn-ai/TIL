# RStudio Serverを使う
### 使い方
```
docker run --rm -d -p 8787:8787 -e PASSWORD=[yourpasswordhere] -v [mountdir]:/home/rstudio rocker/tidyverse
```

- mountdirにカレントディレクトリを指定するときは，`$(pwd)`とすればよい．

として，

http://localhost:8787

にアクセス．ユーザ名に`rstudio`，パスワードに指定したパスワードを入力．