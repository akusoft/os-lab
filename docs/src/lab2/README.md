# Lab 2：物理内存管理

首先，在实模式下通过 BIOS 15 号中断来探测物理内存大小。

其次，实现连续内存分配算法：首次适配算法（First Fit）。

最后，建立分页机制。

具体而言，要建立二级页表

---

逻辑地址空间与物理地址空间：

- 逻辑地址空间（logical address space）：又称虚拟地址空间（virtual），在 CPU 运行的进程看到的地址，即可执行文件中的地址
- 物理地址空间（physical）：由硬件直接支持的地址空间
- 线性地址空间（linear）：

页与帧：

- 页（page）：逻辑地址空间的基本单元，大小和帧相同
- 帧（frme）：又称页帧，物理地址空间的基本单元，大小是 2 的 n 次幂，在 32 位系统中一般为 4K（4096）字节