# 作業ログ（log）

`learn-c-pool-allocator-m0` の現在状態と次にやること。目的と完了条件は `README.md`。判断の根拠は `docs/decisions.md`。

## Next Actions

- 前の Project の `src/` `tests/` `Makefile` `tools/` をこの Project に持ってくる方法を決める（README の Open Questions）。
- Cortex-M0 向けの除算の置き換えと、静的な切り替えの方式を、フットプリント優先で比べ、判断をユーザーに諮る。

## Open Questions

- README の Open Questions を参照。

## Log

### 2026-10-07

- Project を作った（「作業を始めて」の open の手順。2回目の Project）。ユーザーが、題材（Cortex-M0 対応）、完了条件の種類（`make check` と実測値の記録）、見直し日（2026-10-20）を選び、前提に「静的な切り替え、M0 はフットプリント優先、動いてからチューニング」を足した。WSL に `gcc` `clang-format` `arm-none-eabi-gcc` `make` があることを確認した（確認: `which`）。
