#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"student_manager.h"


void clear_cache() {
    int c;
    while((c = getchar()) != '\n' && c != EOF) {
        if(c == EOF) {
            printf("检测到程序结束，程序退出\n");
            exit(0);
        }
    }
}


int read_int(const char *prompt) {
    int value;
    while(true) {
        if(prompt != NULL) {
            printf("%s",prompt);
        }

        if(scanf("%d",&value) == 1) {
            return value;
        }
        else {
            printf("error:请重新输入\n");
            clear_cache();
        }
    }
}


static Node *create_node() {
    //创建节点
    Node *node = (Node*)malloc(sizeof(Node));
    if(node != NULL) {
        node->next = NULL;
    }
    return node;
}


int menu() {
    printf("-------------------------------------------------------------\n");
    printf("*                  欢迎使用学生管理系统                     *\n");
    printf("*                      版本号V1.0                           *\n");
    printf("-------------------------------------------------------------\n");
    printf("*                   1） 录入学生信息                        *\n");
    printf("*                   2） 输出学生信息                        *\n");
    printf("*                   3） 保存学生信息                        *\n");
    printf("*                   4） 读取学生信息                        *\n");
    printf("*                   5） 统计学生信息                        *\n");
    printf("*                   6） 查找学生信息                        *\n");
    printf("*                   7） 修改学生信息                        *\n");
    printf("*                   8） 删除学生信息                        *\n");
    printf("*                       0）exit                             *\n");
    printf("-------------------------------------------------------------\n");
    printf("select--->");
    
    int select = -1;
    select = read_int("<选择>");
    return select;
}


void input_student(List *list) {    
    //创建节点
    Node *node = create_node();
    if(!node) {
        printf("create error:your device may be low on memony");
        return;
    } 

    //录入信息
    printf("学号-->");
    scanf(" %llu",&node->stu.student_number);

    printf("姓名-->");
    scanf("%s",node->stu.name);

    printf("id-->"); 
    scanf(" %llu",&node->stu.id_number);


    //插入到链表中
    node->next = list->front;//list->front是头指针指向的节点
    list->front = node;
    list->size++;
}


void print_student(List *list) {

    printf("-------------------------------------------------------------\n");
    printf("*                  欢迎使用学生管理系统                     *\n");
    printf("*                      版本号V1.0                           *\n");
    printf("-------------------------------------------------------------\n");
    printf("*     *学号*               *姓名*             *ID*          *\n");
    printf("-------------------------------------------------------------\n");


    //遍历链表
    Node *curnode = list->front;

    if(list->front == NULL) {
        printf("未录入任何信息\n");
    }
    
    while(curnode != NULL) {
        printf("|%-19llu||%-19s||%-19llu|\n"
        ,curnode->stu.student_number,curnode->stu.name,curnode->stu.id_number);
        curnode = curnode->next;
    }
}


void save_student(List *list) {

    if(list->front == NULL) {
        printf("file save failed\n");
        return;
    }

    //打开文件
    FILE *fp = fopen("../data/student.bin","wb");
    if(fp == NULL) {
        perror("file open failed");
        return;
    }

    //保存信息
    Node *curnode = list->front;

    int count = 0;
    while(curnode != NULL) {

        size_t written = fwrite(&curnode->stu,sizeof(Student),1,fp);

        if(written != 1) {
            perror("data save failed");
            fclose(fp);
            return;
        }

        count++;
        curnode = curnode->next;
    }   

    //关闭文件
    fclose(fp);

    //提示保存成功
    printf("-------------------------------------------------------------\n");
    printf("*                       saved success                       *\n");
    printf("*                         total %d                           *\n",count);
    printf("-------------------------------------------------------------\n");
}


void auto_save_student(List *list) {

    if(list->front == NULL) {
        printf("file save failed\n");
        return;
    }

    //打开文件
    FILE *fp = fopen("../data/student.bin","wb");
    if(fp == NULL) {
        perror("file open failed");
        return;
    }

    //保存信息
    Node *curnode = list->front;

    int count = 0;
    while(curnode != NULL) {

        size_t written = fwrite(&curnode->stu,sizeof(Student),1,fp);

        if(written != 1) {
            perror("data save failed");
            fclose(fp);
            return;
        }

        count++;
        curnode = curnode->next;
    }   

    //关闭文件
    fclose(fp);

    printf("saved success\n");
}


void read_student(List *list) {

    //打开文件
    FILE *fp = fopen("../data/student.bin","rb");
    if(!fp) {
        perror("file open failed");
        return;
    }

    //读取学生信息
    while(!feof(fp)) {

        Node *node = create_node();
        if(!node) {
            break;
        }

        size_t written = fread(&node->stu,sizeof(Student),1,fp);
        if(written == 0) {
            free(node);
            break;
        }

        node->next = list->front;
        list->front = node;
        list->size++;
    }

    //关闭文件
    fclose(fp);

    printf("-------------------------------------------------------------\n");
    printf("*                       reading success                     *\n");
    printf("*                         total %d                           *\n",list->size);
    printf("-------------------------------------------------------------\n");
}


void statistics_student(List *list) {

    printf("学生总人数->%d\n",list->size);
}


Node *search_student(List *list) {

    char name[32];
    printf("请输入查找学生的学号或姓名->");
    scanf("%s",name);

    //转换类型
    unsigned long long number = -1;
    sscanf(name,"%llu",&number);

    Node *curnode = list->front;
    while(curnode != NULL) {

        if(strcmp(curnode->stu.name,name) == 0 ||   //比较姓名
           curnode->stu.student_number == number) { //比较学号
            return curnode;
        }

        curnode = curnode->next;
    }
    
    return NULL;
}


void modify_student(List *list) {

    char name[32];
    printf("请输入修改学生的学号或姓名->");
    scanf("%s",name);

    //转换类型
    unsigned long long number = -1;
    sscanf(name,"%llu",&number);

    Node *curnode = list->front;
    while(curnode != NULL) {

        if(strcmp(curnode->stu.name,name) == 0 ||   //比较姓名
           curnode->stu.student_number == number) { //比较学号
            
            int choose;
            printf("是否选择修改%s的信息ID(0 or 1)-->",curnode->stu.name);
            scanf(" %d",&choose);
            if(choose) {
                printf("请输入修改信息ID->");
                scanf(" %llu",&curnode->stu.id_number);
                break;
            }
            else {
                return;
            }
        }

        curnode = curnode->next;
    }
}


void delele_student(List *list) {

    //判断是否有数据
    if(list->size == 0) {
        printf("no student data\n");
        return;
    }
    
    char name[32];
    printf("请输入删除学生的学号或姓名->");
    scanf("%s",name);

    //转换类型
    unsigned long long number = -1;
    sscanf(name,"%llu",&number);

    Node *curnode = list->front;
    Node *prevnode = NULL;
    while(curnode != NULL) {

        if(strcmp(curnode->stu.name,name) == 0 ||   //比较姓名
           curnode->stu.student_number == number) { //比较学号
            break;
        }

        prevnode = curnode;
        curnode = curnode->next;
    }


    if(curnode) {
        //删除的是首元节点
        if(prevnode == NULL) {
            list->front = curnode->next;
        }
        else {
            prevnode->next = curnode->next;
        }

        free(curnode);
        list->size--;
        printf("delete success\n");
    }
}