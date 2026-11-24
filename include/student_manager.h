#pragma once


typedef enum MenuOptions {
    EXIT,           //退出
    INPUT,          //录入
    PRINT,          //打印
    SAVE,           //保存
    READ,           //读取
    STATISTICS,     //统计
    SEAR,           //查找
    MODIFY,         //修改
    DEL,            //删除
}MenuOptions;


//学生结构
typedef struct Student {
    unsigned long long student_number;//学号
    char name[32];                    //姓名
    unsigned long long id_number;     //身份
}Student;


//节点Node
typedef struct Node {
    Student stu;       //学生数据
    struct Node *next; //指向下一节点的指针
}Node;


//链表数据
typedef struct List {
    Node *front;    //头指针
    int size;       //节点数
}List;


//清理缓存（upper）
void clear_cache();


//int类型输入校准
int read_int(const char *prompt);


//菜单打印兼功能键实现
int menu();


//信息录入
void input_student(List *list);


//信息打印
void print_student(List *list);


//信息保存
void save_student(List *list);


//自动保存
void auto_save_student(List *list);


//信息读取
void read_student(List *list);


//信息统计
void statistics_student(List *list);


//信息查找
Node *search_student(List *list);


//信息修改
void modify_student(List *list);


//信息删除
void delele_student(List *list);