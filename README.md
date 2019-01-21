# 為 簡單的 Arduino Blink 範例 加上 夢幻後門

我們提供 一序列 簡單 blink 範例, 在 esp32 的 WiFiBoy 開發板上, 逐步使 blink 範例 加上 後門, 展現夢幻效果。

我們所謂 後門, 就是要在 Arduino 程式中, 啟動一個 virtual machine。 在程式執行同時, 這 virtual machine 可進行一些額外工作,
或 直接改變 程式的 執行效果。
