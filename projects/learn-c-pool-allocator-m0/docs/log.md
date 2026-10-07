# 作業ログ（log）

`learn-c-pool-allocator-m0` の現在状態と次にやること。目的と完了条件は `README.md`。判断の根拠は `docs/decisions.md`。

## Next Actions

- 完了条件の確認をユーザーに頼む（実測値は Log 2026-10-07）。達成なら、close の手順（`docs/drafts/project-close.md`）。
- `feature/m0-no-div` ブランチを、ユーザーが main に取り込むか決める。
- 動作確認の後のチューニング（ユーザーの方針）: 候補は `pool_check` の `on_boundary` の呼び出し、`blocks_in` と連結ループの統合（M0 の `.text` をさらに削る）。やるかはユーザーが決める。

## Open Questions

- README の Open Questions を参照。

## Log

### 2026-10-07

- M0 対応を実装した（ブランチ `feature/m0-no-div`）。ユーザーが、D1（除算を使わない）、自動 + `POOL_NO_HW_DIV`、コピーして育てる、を選んだ（判断は `docs/decisions.md` の「M0 の除算」）。前の Project の成果物を持ち込み、新しい場所で `make check` が通ること（終了コード 0）と、M3 / M4 が `.text` 288 であることを、変更前に確認して基準にした。
- 結果（確認: WSL、`make check` 終了コード 0、`make clean` の後）: Cortex-M0 / M0+ は `.text` 360、`.data` 0、`.bss` 0、未定義シンボルなし。M3 / M4 は 288 のままで、変更前とオブジェクトファイルがバイト単位で同一（`cmp`）。除算を使わない経路は、ホストで `POOL_NO_HW_DIV` を付けて、同じテストを ASan・UBSan つきで `-O1` と `-O2` で実行する（`make test-soft` `test-soft-o2`。`make check` に追加）。`make check-arm` は M0 / M0+ を対象にし、「M0 が `#error` で止まる」確認は外した。
- 実装中の判断: 最初に入れた `on_boundary` のキャリー検査を、`PTRDIFF_MAX` の前提で外した（366 → 360。前提は decisions に記載）。

- Project を作った（「作業を始めて」の open の手順。2回目の Project）。ユーザーが、題材（Cortex-M0 対応）、完了条件の種類（`make check` と実測値の記録）、見直し日（2026-10-20）を選び、前提に「静的な切り替え、M0 はフットプリント優先、動いてからチューニング」を足した。WSL に `gcc` `clang-format` `arm-none-eabi-gcc` `make` があることを確認した（確認: `which`）。
