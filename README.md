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

Building is somewhat straight forward. setup [VCPKG](https://vcpkg.io/en/getting-started.html), `git clone` the repository and run `generate_vs2022.bat`.
Afterwards you can open the generated solution and build it with `CTRL+B`.

Once it's been build, you can run `.\enable_extension.bat` as admin to enable &register the `Shell Extension` within your explorer.
Please note that `.\enable_extension.bat` will restart your explorer! So if you have done some work that is not saved, tough luck :/

## Debugging

Debugging is a bit weird as we're loading a `Shell Extension` we must debug the `explorer.exe` (before we load our DLL)
Though, it's pretty straight forward as I've written some automized scripts for them.

Run `.\enable_extension.bat` as admin, dont open an explorer window. Attach the debugger on Visual Studio (Debug -> Attach To Process) to `explorer.exe`

## License

RPFXplorer's code is licensed under the [MIT licence](https://opensource.org/licenses/MIT). Please see [the licence file](./LICENSE) for more information. [tl;dr](https://tldrlegal.com/license/mit-license) you can do whatever you want as long as you include the original copyright and license notice in any copy of the software/source.
