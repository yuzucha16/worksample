# 作業ログ（log）

`learn-c-pool-allocator-m0` の現在状態と次にやること。目的と完了条件は `README.md`。判断の根拠は `docs/decisions.md`。

## Next Actions

- チューニングを取り込むかを、ユーザーが決める（判断材料は Log 2026-10-07 の「チューニングの見積もり」。取り込む範囲が決まったら、ブランチを切って実装する）。
- チューニングを終えたら（またはやらないと決めたら）、close の手順（`docs/drafts/project-close.md`）。完了条件は達成済み。

## Open Questions

- README の Open Questions を参照。

## Log

### 2026-10-07

- 完了条件の達成を、ユーザーが確認した（`make check` とフットプリント測定）。`feature/m0-no-div` を main にマージした（`3891cae`、`--no-ff`）。
- **チューニングの見積もり（提案。未承認・未実装）**。ユーザーの依頼で、実装の前に測った。基準は main の M0 `.text` 360（`-Os`、freestanding、`arm-none-eabi-gcc 13.2.1`、確認: WSL、`size`）。関数ごと（`nm --size-sort`）: `pool_init` 138、`locate` 66（`on_boundary` と範囲検査を含む）、`pool_check` 64、`pool_free` 42、`is_initialized` 26、`pool_alloc` 24。試作は一時ディレクトリ（`POOL_NO_HW_DIV` を付けて、リポジトリは変更していない）。

  | 案 | M0 `.text` | 基準比 | 内容 | 挙動の変化 |
  |---|---|---|---|---|
  | L1+L2 | 350 | −2.8% | `blocks_in` と連結ループの統合（354）、`on_boundary` を定数シフトに（−4） | なし |
  | L1+L2+L4 | 320 | **−11.1%（10% 達成）** | `is_initialized` を `p != NULL && p->base != NULL` に縮める | `block_size` と `capacity` の健全性検査が無くなる |
  | L1+L2+L3 | 304 | **−15.6%** | 境界検査（`on_boundary`）を、ビルド時に外せる | `pool_free` が、ブロックの途中を指すポインタを `POOL_ERR_PTR` にしなくなる |
  | L1+L2+L3+L4 | 268 | **−25.6%（20% 達成）** | 両方 | 両方 |

  - 安全な変更だけ（L1+L2）では 3% 弱。10% 以上は、検査を減らす変更（L3 か L4）が要る。20% は、両方が要る。
  - 効かなかったもの: コンパイラのフラグ（`-O2` は 380、`-fno-inline` は 484、そのほか 350 のまま）、`is_initialized` の強制インライン（362。悪化）。
  - 注意（試作の測定の落とし穴）: 統合ループを共通コードに入れると、M3 / M4 も 288 から 290 に変わる。実装するときは、M0 の経路（`POOL_SOFT_DIV`）の中だけに入れ、M3 / M4 のオブジェクトが変更前とバイト単位で同一であることを、今回と同じ `cmp` で確かめる。
- M0 対応を実装した（ブランチ `feature/m0-no-div`）。ユーザーが、D1（除算を使わない）、自動 + `POOL_NO_HW_DIV`、コピーして育てる、を選んだ（判断は `docs/decisions.md` の「M0 の除算」）。前の Project の成果物を持ち込み、新しい場所で `make check` が通ること（終了コード 0）と、M3 / M4 が `.text` 288 であることを、変更前に確認して基準にした。
- 結果（確認: WSL、`make check` 終了コード 0、`make clean` の後）: Cortex-M0 / M0+ は `.text` 360、`.data` 0、`.bss` 0、未定義シンボルなし。M3 / M4 は 288 のままで、変更前とオブジェクトファイルがバイト単位で同一（`cmp`）。除算を使わない経路は、ホストで `POOL_NO_HW_DIV` を付けて、同じテストを ASan・UBSan つきで `-O1` と `-O2` で実行する（`make test-soft` `test-soft-o2`。`make check` に追加）。`make check-arm` は M0 / M0+ を対象にし、「M0 が `#error` で止まる」確認は外した。
- 実装中の判断: 最初に入れた `on_boundary` のキャリー検査を、`PTRDIFF_MAX` の前提で外した（366 → 360。前提は decisions に記載）。

- Project を作った（「作業を始めて」の open の手順。2回目の Project）。ユーザーが、題材（Cortex-M0 対応）、完了条件の種類（`make check` と実測値の記録）、見直し日（2026-10-20）を選び、前提に「静的な切り替え、M0 はフットプリント優先、動いてからチューニング」を足した。WSL に `gcc` `clang-format` `arm-none-eabi-gcc` `make` があることを確認した（確認: `which`）。
