# 开发环境

本实验在 Ubuntu 18.04 上开发完成，关于 Ubuntu 的安装，这里不再赘述，值得注意的是，如果你使用的是 Windows 10，
其内置了 WSL（Windows Subsystem for Linux）功能，可以更加方便的在 Windows 中使用 Linux 子系统。

安装完 Ubuntu 之后，你需要安装如下必备的开发工具：

- GCC：编译器
- GDB：调试器
- QEMU：模拟器

使用如下命令即可一键安装上述工具：

```bash
sudo apt-get install build-essential gdb qemu -y
```

安装完成后，依次输入如下命令：

```bash
gcc -v
```

```bash
gdb -v
```

```bash
qemu-system-i386 –-version
```

若无明显报错，且正常显示相应的版本信息，即代表安装成功。

## GCC

GCC 是由 GNU 开源组织开发的编译器套装，其中包含了 C 语言编译器 `gcc`、C++ 编译器 `g++`、链接器 `ld`、
汇编器 `ns`、构建器 `make` 等众多工具。在 Ubuntu 中，这些工具被集合进了一个软件包，即 `build-essential`，
所以只需要安装它即可。

## GDB

GDB 同样是由 GNU 开源组织开发的命令行调试器，其可以和 GCC 完美配合。

## QEMU

QEMU 是我们在此实验中所用到的模拟器（或称虚拟机），它会模拟出一个 32 位的 80386 硬件环境，
其用来运行编译生成的 OS 镜像文件。为什么不选择常用的 VMware 或者 VirtualBox，而使用不常见的 QEMU，其原因如下：

- 我们所使用的 Linux 开发环境是在虚拟机中运行的，要在虚拟机中的 Linux 上再安装一个虚拟机，
  VMware 或者 VirtualBox 是不支持的，而 QEMU 则支持。
- QEMU 有很方便的调试功能，配合 GDB 可以实现计算机加电后的逐步调试功能，而 VMware 或者 VirtualBox 则不尽完美。
- QEMU 完全采用命令行操作，更符合 Linux 的设计哲学。

---

除了上述必备工具之外，以下辅助工具你可能也会用到：

## 编辑器

系统自带的编辑器可能不够强大，因此你可能需要一个第三方的编辑器，命令行界面的编辑器推荐使用 Vim，
图形化界面的编辑器推荐使用 [Sublime Text 3](https://www.sublimetext.com/) 。

## 文本差异比较工具

在很多时候，我们需要比较多个文件或文件夹之间的差异，比如比较 Lab1 和 Lab2 之间的差异，
可以帮助我们更好的理解 Lab2 中新增的功能。命令行界面的比较工具可以使用系统自带的 `diff` 命令，
图形化界面的比较工具推荐使用 [Meld](https://meldmerge.org/) 。
