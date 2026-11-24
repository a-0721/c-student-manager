# 学生管理系统（C 语言 · 学习记录）

这是我用来练习 C 语言基础的小项目：用**单链表**实现一个控制台版的学生信息管理系统。
代码全部自己手写，功能在逐个补齐，仓库用于记录学习过程。

## 功能进度

| 编号 | 功能 | 状态 |
| :--: | --- | :--: |
| 1 | 录入学生信息 | 已完成 |
| 2 | 输出学生信息 | 已完成 |
| 3 | 保存学生信息 | 已完成 |
| 4 | 读取学生信息 | 待实现 |
| 5 | 统计学生信息 | 待实现 |
| 6 | 查找学生信息 | 待实现 |
| 7 | 修改学生信息 | 待实现 |
| 8 | 删除学生信息 | 待实现 |
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

链表采用**头插法**插入，新录入的学生总在表头。

## 文件结构

```
include/
  student_manager.h   类型定义 + 函数声明
src/
  main.c              程序入口：菜单循环 + 功能分发
  student_manager.c   各功能的具体实现
data/                 运行时由「保存」生成 student.bin
```

## 编译运行

环境：Windows + MinGW-w64（gcc 14.2.0）

```powershell
gcc -g src/main.c src/student_manager.c -Iinclude -o main.exe
.\main.exe
```

## 已实现的细节

- `menu()`：打印菜单并返回用户选择
- `read_int()`：带输入校验，输入非数字时提示重新输入
- `input_student()`：`malloc` 新节点后头插进链表，`size` 自增
- `print_student()`：遍历链表逐行输出，链表为空时给出提示
- `save_student()`：用 `fwrite` 把每个 `Student` 以二进制写入 `data/student.bin`，成功后打印保存条数

## 待完成 / 已知问题

- 4~8 号功能还是空实现（`switch` 里先占位）
- 输出表格在中文姓名下对不齐：`printf` 的 `%-15s` 按**字节**补空格，而一个汉字在控制台占 **2 列**，列宽会错位
- 姓名用 `scanf("%s")` 读，不能含空格，后续考虑改用 `fgets`
- 保存前未处理 `data/` 目录不存在的情况，`fopen` 失败只打印错误

## 学习笔记

- 链表头插法：`node->next = list->front; list->front = node;` 两行顺序不能反
- `malloc` 之后一定要判 `NULL`，失败要提前返回
- 二进制读写结构体省事，但要注意结构体内存对齐，跨平台不通用
- `switch` 里每个 `case` 记得 `break`，否则会贯穿到下一个分支

## 提交记录

按功能点小步提交，每个功能单独一次 commit，方便回顾。
