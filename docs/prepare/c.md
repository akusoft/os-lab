## C语言

本节不会讲述 C 语言的基本语法，只会就某些特性做简要说明。

### 编译过程

一个 C 语言源代码变成二进制可执行文件，大致要经过 4 个步骤，以 `test.c` 为例说明：

1. 预处理：`test.c` 经过编译预处理程序（cpp）生成 `test.i`，主要处理源代码文件中的编译预处理指令。
2. 编译：`test.i` 经过编译器（gcc）生成 `test.s`，`test.s` 为汇编语言。
3. 汇编：`test.s` 经过汇编器（ns）生成 `test.o`，`test.o` 为二进制代码。
4. 链接：`test.o` 经过链接器（ld）生成 `test`，`test` 为可执行文件。

### 头文件

头文件是存放**声明**的地方，声明（declare）和定义（define）是两个不同的概念，声明是不产生代码的东西，而定义是产生代码的东西，声明可以包括**函数原型**和**变量声明**等等，以下举例说明：

```c
// 变量定义
int a;

// 变量声明
extern int a;


// 函数定义
int
plus(int a, int b){
    return a+b;
}

// 函数原型，即函数声明
int plus(int a, int b);
```

在大型项目中，往往需要把一个源代码文件中对外公开的函数或变量的声明放到其对应的头文件中，当其他源代码文件想要使用其提供的函数或变量时，需要先使用编译预处理指令 `#include` 引入其头文件。

对于不愿对外公开的函数或变量，可以在其前加上 `static` 修饰符，使其只能在其源代码文件中被使用。

为了防止头文件中结构体的重复声明，需要使用**标准头文件结构**，运用条件编译和宏，可以保证这个头文件在一个编译单元中只会被 `#include` 一次。示例如下：

```c
#ifndef __TEST_H__
#define __TEST_H__

extern int a;
int plus(int a, int b);

#endif
```

### 面向对象

利用结构体和函数指针，可以实现 C 语言的面向对象特性，下面以一个计算器对象为例说明，假设计算器对象包含类型、价格等属性和加法、乘法等方法：

```c
#include <stdio.h>

// 定义一个计算器结构体，其对外提供统一的接口
struct calc{
    char *type;
    int price;
    int (*plus)(int a, int b);
    int (*multiply)(int a, int b);
};

// 定义具体的加法方法
int
int_plus(int a, int b){
    return a+b;
}

// 定义具体的乘法方法
int
int_multiply(int a, int b){
    return a*b;
}

// 定义具体的计算器
struct calc int_calc = {
    .type = "Integer Calculator",
    .price = 10,
    .plus = int_plus,
    .multiply = int_multiply,
};

// 进行相关调用
int
main(void){
    struct calc *calc;
    calc = &int_calc;
    printf("%s\n", calc->type);
    printf("￥%d\n", calc->price);
    printf("3+5=%d\n", calc->plus(3, 5));
    printf("3*5=%d\n", calc->multiply(3, 5));
    return 0;
}
```

通过使用这种方法，我们可以方便的更改具体的计算器实现。

### 代码风格

关于代码风格的讨论，向来都没有一个绝对正确的答案，但是统一的代码风格有助于每个人更好的阅读理解代码，在此实验中，我们采用如下规定的代码风格：

#### 换行

函数返回值类型和函数名之间换一行，这样可以更方便的使用 `grep` 命令找到函数实现，GNU 和 BSD 等开源代码多采用这种风格，以下是示例：

```c
void
trap(struct trapframe *tf) {
    trap_dispatch(tf);
}
// 可以使用grep ^trap命令找到函数实现
```

类似的，起始大括号不换行，同样可以参考上面的示例。
