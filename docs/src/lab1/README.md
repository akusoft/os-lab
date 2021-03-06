# Lab 1：启动和 bootloader

操作系统通过**中断**与底层硬件进行交互，通过**系统调用**和**异常**与上层应用程序进行交互。中断、异常和系统调用又被统称为中断（广义上的中断），其中中断又被称为**硬中断**，异常和系统调用又被称为**软中断**。

计算机加电，启动 BIOS，BIOS 加载 bootloader，bootloader 加载 OS 内核。

bootloader 主要完成的工作为：

- 从实模式切换到保护模式
- 建立分段机制
- 加载 OS 内核

具体而言，通过设置 A20 门和 CR0 寄存器以切换到保护模式，要建立段表（GDT）。

OS 内核主要完成的工作为：

- 建立中断机制
- 打印函数调用栈关系。

具体而言，要初始化中断向量表（IDT）。

---

数据块与扇区：

- 数据块（block）：逻辑存储单元，可能由多个扇区组成
- 扇区（sector）：磁盘的物理存储单元

---

## 实验目的
