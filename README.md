# works

個人用 PC の作業場（Obsidian の Vault のトップ）。PARA でこの PC のローカルの作業（個人開発など）を管理し、共有ナレッジ（`resources/`）を参照する。この PC だけのローカルなリポジトリ（remote: `worksample`。公開）。規約は `AGENTS.md`。

## 構成と管理

| パス | 内容 | 管理 |
|---|---|---|
| `areas/` `projects/` `archives/` | PARA。この PC のローカルの作業 | このリポジトリ |
| `docs/` `AGENTS.md` `CLAUDE.md` | この PC の作業ログと規約 | このリポジトリ |
| `resources/` | 共有ナレッジ（`workbase`）。Vault 全体の規約は `resources/AGENTS.md`。このリポジトリの `.gitignore` で除外する | 別リポジトリ（git 操作は `resources/` の中で行う） |
| `resources_p/` | PC ローカルの resources（この PC だけの情報の置き場） | 追跡しない |
| `repos/` | ghq で clone した独立のリポジトリ（`dotfiles`、`zed-vba` など）。このリポジトリの `.gitignore` で除外する | 各リポジトリ（作業の前に、その `AGENTS.md` / `CLAUDE.md` を読む。git 操作はそのリポジトリの中で行う） |
| `.obsidian/` | Obsidian の設定。dotfiles からのジャンクション。このリポジトリでは追跡しない | dotfiles |
| `.claudian/` | Claudian プラグインの設定。依頼がなければ編集しない | なし（未追跡） |

## 入口

- 現在の状態と次にやること: `docs/log.md`
- 下位の単位（`resources/`、`repos/` の各リポジトリ）の続き: 「<名前> の続き」と言う。読み方は `resources/workflow-kit/docs-rules.md` の「読む順番」
