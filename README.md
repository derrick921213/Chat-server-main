# Chat server
## 編譯Server 
```shell
docker compose run --rm -w /chatserver/build dev make server
```
## 編譯Client
```shell
docker compose run --rm -w /chatserver/build dev make client
```
## 編譯所有
```shell
docker compose run --rm -w /chatserver/build dev make
```
## 編譯相依賴(並且將所有Source Code編譯)
```shell
docker compose run dev ./build.sh
```
## 開一個新的任何容器
```shell
docker compose run --rm <dev/server/client>
```
## 進入任何容器
```shell
docker compose exec <dev/server/client> /bin/bash
```
## 專案啟動
```shell
docker compose up -d
```