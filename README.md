# 学生管理系统（C 语言 · 学习记录）

这是我用来练习 C 语言基础的小项目：用**单链表**实现一个控制台版的学生信息管理系统。
代码全部自己手写，从菜单、链表操作到二进制文件读写，一边写一边补功能，仓库用于记录学习过程。

## 功能进度

| 编号 | 功能 | 状态 |
| :--: | --- | :--: |
| 1 | 录入学生信息 | 已完成 |
| 2 | 输出学生信息 | 已完成 |
| 3 | 保存学生信息 | 已完成 |
| 4 | 读取学生信息 | 已完成 |
| 5 | 统计学生信息 | 已完成 |
| 6 | 查找学生信息 | 已完成 |
| 7 | 修改学生信息 | 已完成 |
| 8 | 删除学生信息 | 已完成 |
| 0 | 退出 | 已完成 |

## 数据结构

```c
typedef struct Student {
    unsigned long long student_number; // 学号
    char name[32];                     // 姓名
    unsigned long long id_number;      // 身份证
} Student;

typedef struct Node {
    Student stu;       // 数据域
    struct Node *next; // 指向下一节点
} Node;

typedef struct List {
    Node *front; // 头指针
    int size;    // 节点数
} List;
```

链表采用**头插法**插入；学号和身份证都用 `unsigned long long` 存，避免位数不够。

## 文件结构

```
include/
  student_manager.h   类型定义 + 全部函数声明
src/
  main.c             程序入口：菜单循环 + 功能分发
  student_manager.c  各功能的具体实现
data/                 运行时由「保存」生成 student.bin
```

## 编译运行

环境：Windows + MinGW-w64（gcc 14.2.0）

```powershell
gcc -g src/main.c src/student_manager.c -Iinclude -o main.exe
.\main.exe
```

> 保存/读取用的是相对路径 `data/student.bin`，相对于**当前工作目录**。
> 在仓库根目录直接运行 `.\main.exe` 即可，`data/` 目录已随仓库一起提交。

仓库里也放了一份已经编译好的 `main.exe`（Windows x64，gcc 14.2.0 编译），
不方便装编译器时可以直接下载使用；想自己重新编译就用上面的命令，产物同名覆盖即可。

## 下载

不想自己编译的话，直接取现成的：

- 发布页（推荐）：[Releases](https://github.com/a-0721/c-student-manager/releases)
- 或仓库根目录的 [`main.exe`](main.exe)

下载后放在仓库根目录（或任何 `data/` 的同级目录）运行即可。

## 各功能的实现要点

- `menu()`：打印菜单，交给 `read_int()` 读一个整数返回
- `read_int()`：`scanf("%d")` 返回 1 才算读成功，否则提示重输并清空缓冲区
- `clear_cache()`：吃掉本行剩余字符直到 `\n`；读到 `EOF`（比如输入被重定向、提前结束）就打印提示并退出程序
- `create_node()`：`malloc` 一个节点并置 `next = NULL`，供「录入」和「读取」复用
- `input_student()`：新建节点 → 依次读学号/姓名/身份证 → 头插进链表 → `size++`
- `print_student()`：遍历链表逐行输出；链表为空时提示「未录入任何信息」
- `save_student()`：非空检查 → 以 `wb` 打开文件 → 循环 `fwrite` 每个 `Student` → 关文件并打印保存条数
- `auto_save_student()`：和保存逻辑一样，但**不打印**，供修改/删除后自动落盘
- `read_student()`：以 `rb` 打开 → 循环 `fread` 建节点、头插 → 读到文件末尾停止 → 打印总条数
- `statistics_student()`：直接输出 `list->size`
- `search_student()`：读入一个字符串，先用 `sscanf` 尝试转成学号，再遍历链表，**姓名或学号**任一匹配即返回节点指针（`main` 里负责打印，找不到就提示 `no find`）
- `modify_student()`：同样按姓名/学号定位，命中后询问是否修改身份证，改完退出循环；`main` 中随后调用 `auto_save_student()` 落盘
- `delele_student()`：双指针 `prevnode` + `curnode` 遍历；命中后区分「删的是首元节点」和「删的是中间节点」两种情况，`free` 并 `size--`；`main` 中随后自动保存
- `main()`：`switch(menu())` 分发，`default` 分支处理非法选择

## 学习笔记

- **单链表删除为什么需要前驱指针**：链只能单向走，要删当前节点就得改上一个节点的 `next`，所以边遍历边保存 `prevnode`
- **首元节点要单独判断**：`prevnode == NULL` 说明删的是第一个节点，直接改 `list->front`
- **`fread` 的返回值比 `feof` 可靠**：`feof` 是「读失败之后」才置位，容易多循环一次；所以用 `fread(...) == 0` 判断结束更稳
- **用字符串统一输入**：查找/修改/删除都先读成一个字符串，再用 `sscanf` 尝试转学号，这样一套输入能同时支持「按学号」和「按姓名」两种查找
- **改完立刻自动保存**：`modify` / `delete` 之后调 `auto_save_student()`，避免用户忘记按保存
- **`malloc` 判空、`free` 配对**：`create_node()` 里判 `NULL`，删除时记得 `free`
- **头插法两行顺序不能反**：`node->next = list->front; list->front = node;`

## 待改进

- 路径 `data/student.bin` 依赖运行目录，在别的目录启动会读不到文件
- 输出表格按**字节**补空格（`%-19s`），中文姓名占 2 列却按 3 字节算，列会错位
- 姓名用 `scanf("%s")` 读，不能含空格；后续考虑 `fgets`
- 删除时如果没找到学生，没有给用户任何提示
- 修改时若命中后选择「不改」，会直接 `return`，不会继续找下一个同名记录
- `main` 的第二个参数应为 `char **argv`
- 学号/身份证输入负数或非数字时没有校验

## 提交记录

按功能点小步提交，每个功能单独一次 commit，方便回顾每一步的思路。
