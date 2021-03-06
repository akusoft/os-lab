# Lab 7：同步互斥

## 同步互斥

**同步**是指协调多线程对共享数据的访问，即任何时刻只能有一个线程执行临界区代码。

锁是一个抽象的数据结构，其包含：

- 一个二进制变量（锁定/解锁）
- `Lock::Acquire()`：锁被释放前一直等待，然后得到锁
- `Lock::Release()`：释放锁，唤醒任何等待的进程

使用锁来控制临界区访问：

```c++
lock_next_pid->Acquire();
new_pid = next_pid++;
lock_next_pid->Release();
```

## 信号量

**信号量**（semaphore）是操作系统提供的一种协调共享资源访问的方法。

信号是一种抽象数据类型，由一个整形（`sem`）变量和两个原子操作组成：

- `P()`：Prolaag，荷兰语尝试减少，`sem` 减 1，如 sem<0，进入等待，否则继续
- `V()`：Verhoog，荷兰语增加，`sem` 加 1，如 sem<=0，唤醒一个等待进程

```c++
class Semaphore {
    int sem;
    WaitQueue q;
}

Semaphore::P() {
    sem--;
    if (sem < 0) {
        Add this thread t to q;
        block(p);
    }
}

Semaphore::V() {
    sem++;
    if (sem <= 0) {
        Remove a thread t from q;
        wakeup(t);
    }
}
```

## 管程

## 死锁

**死锁**是由于竞争资源或者通信关系，两个或更多线程在执行中出现，永远相互等待只能由其他进程引发的事件。

比如线程 1 正在使用文件 A，同时想要使用文件 B，而文件 B 此时正被线程 2 所使用，线程 2 此时又想使用文件 A，这就造成了死锁。

出现死锁必须同时满足以下 4 个必要条件：

- **互斥**：任何时刻只能有一个进程使用一个资源实例。
- **持有并等待**：进程保持至少一个资源，并正在等待获取其他进程持有的资源。
- **非抢占**：资源只能在进程使用后自愿释放。
- **循环等待**：

死锁的处理方法有：

- **死锁预防**（Deadlock Prevention）：确保系统永远不会进入死锁状态。
- **死锁避免**（Deadlock Avoidance）：在使用前进行判断，只允许不会出现死锁的进程请求资源。
- **死锁检测和恢复**（Deadlock Detection & Recovery）：在检测到运行系统进入死锁状态后，进行恢复。

通常操作系统忽略死锁，由应用进程处理死锁。

**银行家算法**是死锁避免的一种方法。

## 进程通信

**进程通信**（IPC，Inter-Process Communication）是进程进行通信和同步的机制。

任何 IPC 都提供 2 个基本操作：

- 发送操作：`send(message)`
- 接收操作：`receive(message)`

进程通信流程：

1. 在通信进程间建立通信链路
2. 通过 `send`/`receive` 交换消息

进程通信方式有：

### 直接通信

**直接通信**是在两个进程之间建立一个通信信道（即共享信道），两个进程必须同时存在才能够进行通信。

要进行直接通信，进程必须正确的命名对方：

- `send(P, message)`：发送信息到进程 P
- `receive(Q, message)`：从进程 Q 接收消息

直接通信中的通信链路具有以下属性：

- 自动建立链路
- 一条链路恰好对应一对通信进程
- 每对进程之间只有一个链路存在
- 链路可以是单向的，但通常是双向的

### 间接通信

**间接通信**是通过操作系统维护的消息队列实现进程间的消息接收和发送。

在间接通信中，每个消息队列都有一个唯一的标识，只有共享了相同消息队列的进程，才能够通信。

间接通信中通信链路具有以下属性：

- 只有共享了相同消息队列的进程，才建立链路
- 链路可以是单向或双向
- 消息队列可以与多个进程相关联
- 每对进程可以共享多个消息队列

间接通信的通信流程如下：

1. 创建一个新的消息队列
2. 通过消息队列发送和接收消息
3. 销毁消息队列

间接通信的基本通信操作：

- `send(A, message)`：发送信息到队列 A
- `receive(A, message)`：从队列 A 接收消息

---

进程通信可划分为阻塞（同步）或非阻塞（异步）：

- **阻塞通信**
  - **阻塞发送**：发送者在发送消息后进入等待，直到接收者成功收到。
  - **阻塞接收**：接收者在请求接收消息后进入等待，直到成功收到一个消息。
- **非阻塞通信**
  - **非阻塞发送**：发送者在消息发送后，可立即进行其他操作。
  - **非阻塞接收**：没有消息发送时，接收者在请求接收消息后，接收不到任何消息。

进程发送的消息在链路上可能有 3 种缓冲方式：

- **0 容量**：发送方必须等待接收方
- **有限容量**：通信链路缓冲队列满时，发送方必须等待
- **无限容量**：发送方不需要等待

进程间通信的 4 种方法：

### 信号

**信号**（Signal）是进程间的软件中断通知和处理机制。如：`Ctrl + c` 或 `kill -9`。

信号的接收处理：

- 捕获（catch）：执行进程指定的信号处理函数被调用
- 忽略（Ignore）：执行操作系统指定的缺省处理，例如进程终止、进程挂起等
- 屏蔽（Mask）：禁止进程接收和处理信号，可能是暂时的（当处理同样类型的信号）

信号的不足在于传送的信息量小，只有一个信号类型，仅仅用来做一种快速的响应机制，它比别的通信要快。

### 管道

**管道**（Pipe）是进程间基于**内存文件**的通信机制。如：`ls | more`。

管道是 Linux 中一种比较常见的做法。

### 消息队列

**消息队列**（Message Queues）是由操作系统维护的以字节序列为基本单位的间接通信机制。

### 共享内存

**共享内存**是把同一个物理内存区域同时映射到多个进程的内存地址空间的通信机制。

共享内存的优点是快速、方便地共享数据，缺点是必须用额外的同步机制来协调数据访问。

## 实验

实现锁机制、信号量机制。
