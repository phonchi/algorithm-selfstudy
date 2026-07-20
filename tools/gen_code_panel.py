#!/usr/bin/env python3
"""產生 code-tab 面板 HTML：pygments 上色＋（--run）實跑產 expected-out。

用法：
  tools/gen_code_panel.py src/sorting/heapsort.py [--run] [--size .72rem] [--tag "輸出"]
  tools/gen_code_panel.py src/sorting/heapsort.cpp --run

輸出到 stdout（人工貼進 tools/body_*.html）：
  <div class="pseudo-code" style="font-size:...">…上色碼…</div>
  <div class="expected-out"><span class="eo-tag">…</span><pre>實跑輸出</pre></div>
"""
import html
import pathlib
import subprocess
import sys
import tempfile

from pygments import lex
from pygments.lexers import CppLexer, PythonLexer
from pygments.token import Comment, Keyword, Name, Number, String, Token


def hl(code, lexer):
    """上色成頁面慣用 span 類別（kw/fn/num/com/str），每行包 .line，空行補空白。"""
    out = []
    for tok, val in lex(code.strip("\n"), lexer):
        cls = None
        if tok in Comment.Preproc or tok in Comment.PreprocFile:
            cls = "kw"
        elif tok in Comment:
            cls = "com"
        elif tok in String or tok in Token.Literal.String.Char:
            cls = "str"
        elif tok in Number:
            cls = "num"
        elif tok in Keyword:
            cls = "kw"
        elif tok in Name.Function or tok in Name.Builtin:
            cls = "fn"
        # token 內可能含換行（如 C++ 的 preproc/註解）：先拆行、每段各自包 span，
        # 否則 .line 包裝會把 span 切斷成不平衡巢狀
        pieces = []
        for piece in html.escape(val, quote=False).split("\n"):
            if cls and piece:
                pieces.append('<span class="' + cls + '">' + piece + "</span>")
            else:
                pieces.append(piece)
        out.append("\n".join(pieces))
    lines = "".join(out).split("\n")
    return "\n".join(
        '<span class="line">' + (l if l.strip() else " ") + "</span>" for l in lines
    )


def run_source(path):
    """實跑 .py／.cpp，回傳 stdout（失敗直接讓例外炸出來）。"""
    if path.suffix == ".py":
        r = subprocess.run(
            [sys.executable, str(path)], capture_output=True, text=True, check=True
        )
        return r.stdout
    if path.suffix == ".cpp":
        with tempfile.NamedTemporaryFile(suffix=".out", delete=False) as f:
            exe = f.name
        subprocess.run(
            ["g++", "-std=c++17", "-O2", "-o", exe, str(path)], check=True
        )
        r = subprocess.run([exe], capture_output=True, text=True, check=True)
        return r.stdout
    raise SystemExit("不支援的副檔名：" + path.suffix)


def main():
    args = sys.argv[1:]
    if not args:
        raise SystemExit(__doc__)
    path = pathlib.Path(args[0])
    do_run = "--run" in args
    size = args[args.index("--size") + 1] if "--size" in args else ".72rem"
    tag = args[args.index("--tag") + 1] if "--tag" in args else "執行輸出（" + str(path) + "）"

    code = path.read_text()
    lexer = PythonLexer() if path.suffix == ".py" else CppLexer()
    print('<div class="pseudo-code" style="font-size:' + size + ';">' + hl(code, lexer) + "</div>")
    if do_run:
        out = run_source(path)
        print(
            '<div class="expected-out"><span class="eo-tag">' + html.escape(tag)
            + "</span><pre>" + html.escape(out.rstrip("\n")) + "</pre></div>"
        )


if __name__ == "__main__":
    main()
