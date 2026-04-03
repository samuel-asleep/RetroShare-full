# GitHub Copilot Instructions — RetroShare-full

## Project Overview

This repository is a **monorepo** that contains the source code for the [RetroShare](https://retroshare.cc) project, a decentralised, encrypted peer-to-peer communication and file-sharing platform. It is maintained as a unified workspace so that changes to the core library and the application can be tracked and edited together.

## Repository Structure

```
RetroShare-full/
├── retroshare/          # Main RetroShare application (UI, plugins, build system)
│   ├── retroshare-gui/  # Qt-based graphical user interface
│   ├── plugins/         # Optional feature plugins (e.g. VOIP, FeedReader)
│   ├── build_scripts/   # Platform-specific build helpers
│   ├── data/            # Application data files
│   └── RetroShare.pro   # Top-level qmake project file
│
├── libretroshare/       # Core library — submodule copy (see below)
│   ├── src/             # C++ library source code
│   └── CMakeLists.txt   # CMake build file
│
└── .github/
    ├── copilot-instructions.md   # This file
    └── workflows/
        ├── sync-from-upstream.yml   # Pull changes FROM upstream repos into this monorepo
        ├── retreoshare.yml          # Push retroshare/ folder TO a target repo
        └── libretroshare.yml        # Push libretroshare/ folder TO a target repo
```

## The `libretroshare` Folder

The `libretroshare/` directory is the **submodule counterpart** to the upstream [RetroShare/libretroshare](https://github.com/RetroShare/libretroshare) repository. In a standard RetroShare checkout it is referenced as a git submodule inside the `retroshare/` project (at `retroshare/libretroshare`).

In this monorepo it is **checked in directly** as a top-level folder so that:
- Edits to the library can be made and committed alongside application changes.
- CI workflows can sync and overwrite it from the upstream source when needed.
- Developers do not need to manage submodule initialisation separately.

> **Important:** When editing `libretroshare/` code, remember that this folder is the local editable copy of what is normally a read-only submodule. Changes here are intentional overrides of upstream content and should be treated accordingly.

## Sync Workflows

| Workflow file | Direction | Trigger |
|---|---|---|
| `sync-from-upstream.yml` | Upstream → this repo (pull) | Manual (`workflow_dispatch`) |
| `retreoshare.yml` | This repo → target repo (push) | Manual (`workflow_dispatch`) |
| `libretroshare.yml` | This repo → target repo (push) | Manual (`workflow_dispatch`) |

### Pulling from Upstream (`sync-from-upstream.yml`)

Run this workflow from the **Actions** tab to overwrite a local folder with the latest content from an upstream repository. It uses `rsync --delete` so any local files not present in the upstream will be removed.

**Inputs:**
- `upstream_repo` — choose `RetroShare/RetroShare` (syncs `retroshare/`) or `RetroShare/libretroshare` (syncs `libretroshare/`)
- `upstream_branch` — branch to pull from (default: `master`)
- `target_folder` — override the destination folder if needed (auto-detected by default)

## Technology Stack

- **Language:** C++17 (library and core), Qt/QML (GUI)
- **Build systems:** qmake (`.pro` files), CMake, Gradle (Android)
- **Platform targets:** Linux, macOS, Windows, Android
- **Key dependencies:** OpenSSL, SQLite, miniupnpc, restbed (REST API), rapidjson

## Coding Conventions

- Follow the existing code style in each file — the codebase uses a mix of older Qt and modern C++ idioms.
- Prefer Qt container types (`QList`, `QString`, etc.) in GUI code and STL types in library code.
- New API endpoints for the JSON API should be added under `libretroshare/src/retroshare/` and registered with the JSON API generator (`jsonapi-generator/`).
