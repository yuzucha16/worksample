#!/usr/bin/env python3
"""gcc -fcallgraph-info の出力（.ci、VCG 形式）から、呼び出しの閉路（再帰）を探す。

使い方: tools/find-cycles.py <file.ci>...
  複数のファイルを渡すと、翻訳単位をまたぐ再帰（a.c の関数 → b.c の関数 → a.c の関数）も見つける。
  閉路に含まれる関数を、1行に1つ出す。無ければ何も出さず、終了コード 0。再帰があれば終了コード 1。
  関数ポインタなどの間接呼び出しは、呼び出し先が分からないので、再帰を検査できない。
  その関数名を、標準エラーに「WARN」として出す（終了コードには影響しない）。
"""
import re
import sys

EDGE = re.compile(r'edge:\s*\{\s*sourcename:\s*"([^"]+)"\s*targetname:\s*"([^"]+)"')


def load(paths):
    graph = {}
    for path in paths:
        with open(path, encoding="utf-8") as f:
            for line in f:
                m = EDGE.search(line)
                if m:
                    graph.setdefault(m.group(1), set()).add(m.group(2))
    return graph


def reaches_itself(graph, start):
    """start から辿って、start に戻れるか（反復の深さ優先探索。再帰は使わない）。"""
    seen = set()
    stack = list(graph.get(start, ()))
    while stack:
        node = stack.pop()
        if node == start:
            return True
        if node not in seen:
            seen.add(node)
            stack.extend(graph.get(node, ()))
    return False


def main(paths):
    graph = load(paths)
    for src, targets in sorted(graph.items()):
        for t in sorted(targets):
            if "indirect" in t:
                print("WARN: 間接呼び出し（再帰を検査できない）: " + src, file=sys.stderr)
    cyclic = sorted(n for n in graph if reaches_itself(graph, n))
    for name in cyclic:
        print(name)
    return 1 if cyclic else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
