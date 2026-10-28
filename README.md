# snprecomp-mod-template

A mod template for the [Sin and Punishment recomp](https://github.com/wootbeer/snprecomp).

The example mod is **Health Regen**: while you're hurt, your health slowly fills back up. You can set the speed in the Mods menu.

Copy this repo, change the code in `src/` and the info in `mod.toml`, and you have your own mod.

## What You Need
- `clang` and `make`. Use clang 18. clang 19 has trouble with MIPS.
  - Windows: install with [chocolatey](https://chocolatey.org/): `choco install llvm --version 18.1.8` and `choco install make`.
  - Linux: install `clang`, `lld`, `make` and `zip` from your package manager.
  - macOS: install `llvm`, `make` and `zip` with Homebrew. Apple's clang won't work.
- `RecompModTool` from the [N64Recomp releases](https://github.com/N64Recomp/N64Recomp/releases/tag/mod-tool-release). Put it in this folder.

## Building
1. Run `make nrm`.
2. Your mod is `build/snp_health_regen.nrm`.

Or skip all that: push to GitHub and the Build action makes the `.nrm` for you. Get it from the run's Artifacts.

## Installing
Open the Mods tab in the recomp and drop the `.nrm` file in. Turn the mod on and start the game.

## Files
| File | What it is |
|---|---|
| `src/main.c` | The mod's code. |
| `mod.toml` | Mod name, ID, version, authors and options. |
| `include/snp.h` | Game variables we know about (health, time, continues). |
| `include/modding.h` | `RECOMP_HOOK`, `RECOMP_PATCH` and the rest. Don't edit. |
| `include/recompconfig.h` | Read your mod's options. |
| `include/recomputils.h` | Memory and dependency helpers. |
| `syms/snp.jp.syms.toml` | Every game function's name and address. Copied from snprecomp's `SnPSyms/`. |

## Making Your Own Mod

### Hooks and patches
- `RECOMP_HOOK("func_name")` runs your function right before the game's. The game's function still runs. Use this when you can.
- `RECOMP_HOOK_RETURN("func_name")` runs your function right after the game's.
- `RECOMP_PATCH` replaces a game function completely. Name your function the same as the game's. Only one mod can patch a function.

The game has no decompilation, so functions are just named by address (`func_8004C55C`). The names have to match `syms/snp.jp.syms.toml`.

### Reading and changing game memory
Game variables are just addresses. See `include/snp.h`:

```c
#define SNP_HEALTH (*(volatile s32*)0x800D5A98)
```

Then use it like a normal variable: `SNP_HEALTH = 100;`

Add your own addresses to `snp.h` as you find them.

### Japanese and English ROMs
The recomp plays both, and one mod runs on both. The game code is the same, but some data addresses are different. The ones in `snp.h` are the same on both. If you find a new address, test it on both ROMs.

### Don't touch these functions
snprecomp already changes these. Hooking or patching them will undo snprecomp's own fixes, or the mod won't load:

- Patched: `func_8004D748`
- Hooked: `func_80025CA4` `func_80025E44` `func_80029070` `func_8002BCE0` `func_80032AA0` `func_80032F2C` `func_80033128` `func_80033170` `func_80033758` `func_80033A40` `func_80033AC4` `func_80034054` `func_8003A5F0` `func_8003A9CC` `func_8003C0D0` `func_8004D7B0` `func_8004E4A0` `func_8004E640` `func_80052064` `func_80054B64` `func_800AB924` `func_800D42F8` `guMtxF2L`

The list comes from snprecomp's `snp.jp.toml` and `patches/`. Check there if snprecomp gets updated.

### Options
Options go in `mod.toml` under `[[manifest.config_options]]` and show up in the Mods menu. Read them in code with `recomp_get_config_u32("id")`.

### Not there yet
- `recomp_printf` (printing to the console) isn't in snprecomp yet. A mod that uses it won't load.

## More Info
- [N64Recomp modding guide](https://hackmd.io/fMDiGEJ9TBSjomuZZOgzNg): hooks, patches, events and talking to other mods.
- [Banjo-Kazooie mod template](https://github.com/BanjoRecomp/BKRecompModTemplate): this template is based on it.
