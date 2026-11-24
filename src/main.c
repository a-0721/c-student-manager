#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"student_manager.h"


//参数数量，参数内容 
int main(int argc,char *argv) {


    List list;                   //创建链表
    memset(&list,0,sizeof(List));//内存设置初始化

    
    while(true) {
        
        //菜单功能
        switch(menu()) {
            case EXIT:
                exit(0);
                break;
            case INPUT:                                                                                                
                input_student(&list);
                break;
            case PRINT:
                print_student(&list);
                break;
            case SAVE:
                save_student(&list);
                break;
            case READ:
                read_student(&list);
                break;
            case STATISTICS:
                statistics_student(&list);
                break;
            case SEAR:
                Node *node = search_student(&list);
                    if(!node) {
                        printf("no find\n");
                    }
                    else {
                        printf("|%-19llu||%-19s||%-19llu|\n",node->stu.student_number,
                        node->stu.name,node->stu.id_number);
                    }
                break;
            case MODIFY:
                modify_student(&list);
                auto_save_student(&list);
                break;
                
            case DEL:
                delele_student(&list);
                auto_save_student(&list);
                break;
            default:
                printf("error->please input the true number\n");
                break;
        }

        //暂停
        system("pause");

        //清屏
        system("cls");
    }
    
    return 0;
}