# 演算法 × CLRS 互動自學網站

NSYSU 演算法課程的互動自學網站，對應教科書《Introduction to Algorithms》第四版（CLRS 4e）。
線上網址：https://phonchi.github.io/algorithm-selfstudy/

## 內容

- `index.html`：課程總覽（16 週課程地圖＋11 章卡片＋配套資源）
- 10 個授課章節頁＋1 個補充主題頁（`advanced.html`）
- 每個演算法附 **pseudocode／C++／Python** 三版對照分頁籤
  - Python 實作取自 CLRS 4e 官方程式碼（Linda Xiao & Tom Cormen，MIT License）
  - C++ 實作為本課程自寫，皆經 `g++ -std=c++17` 編譯與執行驗證
  - pseudocode 為本站以 HTML 重排之版本（風格仿 CLRS，非官方圖檔）
- 每節 quiz（逐選項回饋）、關鍵詞彙卡（`data/flashcards_zh/`）、互動逐步動畫

## 技術

純靜態 HTML（無 build step），樣式與 JS 全部內嵌，透過 GitHub Pages 部署。
頁面骨架沿用姊妹站 [ds-cpp-selfstudy](https://github.com/phonchi/ds-cpp-selfstudy)。

`tools/build_page.sh <輸出> "<title>" <body片段>` 可從 `tools/_head.fragment`＋`tools/extra.css`＋內容片段組裝章節頁；`src/` 存放驗證用的 C++／Python 原始碼。
