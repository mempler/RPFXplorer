# ![RPFXplorer](Img/logo.png)

![Windows 7](https://img.shields.io/badge/-Windows%207-red?logo=windows)
![Windows 8](https://img.shields.io/badge/-Windows%208-green?logo=windows)
![Windows 10](https://img.shields.io/badge/-Windows%2010-blue?logo=windows)
![Windows 11](https://img.shields.io/badge/-Windows%2011-yellow?logo=windows)

# Index

- [!RPFXplorer](#)
- [Index](#index)
  - [Description](#description)
  - [Compilation](#compilation)
  - [Debugging](#debugging)
  - [TODO](#todo)
  - [License](#license)

## Description

Explore RPF files just like [OpenIV](https://openiv.com/) or [CodeWalker](https://github.com/dexyfex/CodeWalker)
just with the big difference that everything is implemented right into your Windows File Explorer!

## Compilation

Building straight forward. `git clone` the repository, go into it and run `generate_vs2022.bat`
Afterwards you can open the generated solution, select `Debug` & `Win64` and press `CTRL+B` to build the whole repo.

Once it's been build, you can run `.\enable_extension.bat` as admin to run the `Shell Extension`.
Please note that `.\enable_extension.bat` will restart your explorer! So if you have done some work not saved, tough luck :/

## Debugging

Debugging is a bit weird as we're loading a `Shell Extension` we must debug the `explorer.exe` (before we load our DLL)
Though, it's pretty straight forward as I've written some automized scripts for them.

Run `.\enable_extension.bat` as admin, dont open an explorer window. Attach the debugger on Visual Studio (Debug -> Attach To Process) to `explorer.exe`

## TODO

Things we must do to make this ready to use for everyone!

| State |               Description |
| :---- | ------------------------: |
| [ ]   |     Read-Only file access |
| [ ]   |             Writable file |
| [ ]   |      Rename a file/folder |
| [ ]   | Drag & Drop a file/folder |
| [ ]   |   Dolphin support (Linux) |

TODO: add more things here which are tracked in issues

## License

RPFXplorer's code is licensed under the [MIT licence](https://opensource.org/licenses/MIT). Please see [the licence file](./LICENSE) for more information. [tl;dr](https://tldrlegal.com/license/mit-license) you can do whatever you want as long as you include the original copyright and license notice in any copy of the software/source.
