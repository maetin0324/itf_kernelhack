# 概要
2023年度　筑波大学情報学群情報科学類　主専攻実験カーネルハックにて作成したカーネルモジュール等

## `emoji_dev' 使用方法
1. `./emoji_dev/` に移動
2. `make` でコンパイル
3. `sudo insmod EmojiDriver.ko` でカーネルモジュールをロード
4. 作成された`/dev/emoji_device0`にwriteで:bow:を書き込むとUTF-8のバイナリがreadで吐き出される

## `kthread` 使用方法
1. `./kthread/` に移動
2. `make` でコンパイル
3. `sudo insmod Kthread.ko` でカーネルモジュールをロード
4. `dmesg` でログに定期的にナノ秒単位の時間が出力される

## `time_procfs` 使用方法
1. `./time_procfs/` に移動
2. `make` でコンパイル
3. `sudo insmod TimeProcfs.ko` でカーネルモジュールをロード
4. `cat /proc/time_procfs` で時間が表示される