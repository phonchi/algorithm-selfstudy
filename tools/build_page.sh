#!/usr/bin/env bash
# 組裝章節頁：head 骨架（沿用 ds-cpp-selfstudy 樣式）＋ extra.css ＋ 頁面內容 ＋ 共用 JS 尾段
# 用法：tools/build_page.sh <輸出檔名> "<title>" <body 內容片段路徑>
# body 片段：從 <body> 後的第一個元素寫到頁面專屬 </script>（含 FLASHCARDS 定義與 viz JS），
#            不含 <body></body> 標籤與共用 JS。
set -euo pipefail
cd "$(dirname "$0")/.."
out="$1"; title="$2"; body="$3"

{
  sed "s|<title>.*</title>|<title>${title}</title>|" tools/_head.fragment
  printf '<style>\n'
  cat tools/extra.css
  printf '</style>\n</head>\n<body>\n'
  cat "$body"
  cat tools/_sharedjs.fragment
  printf '</script>\n'
  cat tools/_tail.fragment
} > "$out"
echo "built $out ($(wc -c < "$out") bytes)"
