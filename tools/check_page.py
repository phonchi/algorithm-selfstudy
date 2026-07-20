#!/usr/bin/env python3
"""頁面健檢＋FLASHCARDS 抽出：check_page.py <page.html> <flashcards_out.json>"""
import json, pathlib, re, subprocess, sys, tempfile

page, cards_out = sys.argv[1], sys.argv[2]
h = pathlib.Path(page).read_text()
ok = True

def chk(name, cond, detail=""):
    global ok
    print(f"  {'✓' if cond else '✗'} {name}{'' if cond else '  ' + str(detail)}")
    ok = ok and bool(cond)

chk("title", "<title>" in h)
chk("floatNav", 'id="floatNav"' in h)
chk("chapter-nav", "chapter-nav" in h)
chk("closing </html>", h.rstrip().endswith("</html>"))
chk("balanced <section>", h.count("<section") == h.count("</section>"),
    f"{h.count('<section')} vs {h.count('</section>')}")
d = h.count("<div") - h.count("</div>")
chk("balanced <div>", d == 0, d)
chk("FLASHCARDS before engine", h.find("const FLASHCARDS") < h.find("Flashcards engine"))
qz = len(re.findall(r'class="quiz-box"', h))
ct = len(re.findall(r'class="code-tabs"', h))
print(f"  · quiz-box×{qz}  code-tabs×{ct}  sections×{h.count('<section id=')}")

# 每個 quiz 都要有唯一 feedback id 且恰有一個正解
for opts in re.finditer(r'<div class="quiz-options" id="(\w+)Options">(.*?)</div>\s*<div class="quiz-feedback"', h, re.S):
    qid, body = opts.group(1), opts.group(2)
    ncorrect = body.count('data-correct="true"')
    if ncorrect != 1:
        chk(f"quiz {qid} 恰一正解", False, f"正解數={ncorrect}")
ids = re.findall(r'id="(\w+)Feedback"', h)
chk("feedback id 不重複", len(ids) == len(set(ids)), ids)

# node --check 每個 script 區塊
for i, s in enumerate(re.findall(r"<script>(.*?)</script>", h, re.S)):
    with tempfile.NamedTemporaryFile("w", suffix=".js", delete=False) as f:
        f.write(s)
    r = subprocess.run(["node", "--check", f.name], capture_output=True, text=True)
    chk(f"script[{i}] 語法", r.returncode == 0, r.stderr[:200])

# FLASHCARDS 抽出
m = re.search(r"const FLASHCARDS = (\[.*?\]);", h, re.S)
if m:
    cards = json.loads(m.group(1))
    pathlib.Path(cards_out).write_text(json.dumps(cards, ensure_ascii=False, indent=1))
    print(f"  · flashcards×{len(cards)} → {cards_out}")
else:
    chk("FLASHCARDS 存在", False)

sys.exit(0 if ok else 1)
