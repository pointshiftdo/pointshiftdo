# lib/

Single-file C99/C++ libraries and utilities for reuse in other projects,
inspired by the [stb style](https://github.com/nothings/stb/blob/master/docs/stb_howto.txt).

## fullsendx

As a CLI utility, takes macOS permission grants to wrap around other binaries.
The `launchd` workflow is useful for long-running services.

As a library, enables programs to reuse the permission requests after
validating their applicability.

**WARNING:** `fullsendx` opens potential security risks, as its intention is
to bypass macOS authorization mechanisms in a centralized way.

1. FULL raise of a brow 🤨
2. SEND a shifty look 👀
3. eXec path with utmost confidence 🤝

### Motivation

macOS grants permissions to binaries, taking account their contents. So if
you're developing a tool that, e.g. requires accessibility permissions,
you're inconvenienced with the need to re-grant permissions on every compile.

Alternatively, you can grant permissions to `Terminal.app` and launch from
there. This opens the risk of all other binaries having those permissions
in `Terminal.app` if you forget to turn it off.

### Usage

Single-invocation workflow:

```sh
# full path:
make X=$EXEC_BIN_PATH

# alternatively:
make X=$(which $EXEC_BIN)
```

`launchd` workflow:

```sh
make installd X=$EXEC_BIN_PATH
make statusd
make uninstalld
```
