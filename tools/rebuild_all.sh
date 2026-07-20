#!/usr/bin/env bash
# 重組全部 11 頁（title 定義的唯一來源）。用法：tools/rebuild_all.sh [頁名...]（不給＝全部）
set -euo pipefail
cd "$(dirname "$0")/.."

declare -A TITLES=(
  [foundations]="演算法基礎：insertion sort 與 loop invariant — Foundations（CLRS Ch1–2）"
  [analysis]="漸近分析、遞迴式與隨機化 — Analysis（CLRS Ch3–5）"
  [sorting]="Heapsort、Quicksort 與線性時間排序 — Sorting（CLRS Ch6–9）"
  [structures]="Hash 深化、BST 與紅黑樹 — Structures（CLRS Ch11–13）"
  [dp]="動態規劃 — Dynamic Programming（CLRS Ch14）"
  [greedy_amortized]="貪婪演算法與攤還分析 — Greedy \\& Amortized（CLRS Ch15–16）"
  [graphs1]="Disjoint Set 與圖的走訪深化 — Graphs I（CLRS Ch19–20）"
  [graphs2]="MST 與最短路徑 — Graphs II（CLRS Ch21–24）"
  [np_approx]="NP-Completeness 與近似演算法 — NP \\& Approximation（CLRS Ch34–35）"
  [modern]="現代主題概覽：ML 演算法與 Metaheuristics — Modern Topics（CLRS Ch33）"
  [advanced]="進階主題（補充）：Augmenting、B-Trees、Fib Heaps、LP、KMP — Advanced（CLRS Ch17–18、29、32）"
)

pages=("$@")
[ ${#pages[@]} -eq 0 ] && pages=(foundations analysis sorting structures dp greedy_amortized graphs1 graphs2 np_approx modern advanced)

for p in "${pages[@]}"; do
  tools/build_page.sh "$p.html" "${TITLES[$p]}" "tools/body_$p.html"
done
