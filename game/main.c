#include<stdio.h>
#include <conio.h>
#include"item.h"
#include"global.h"
#include"event.h"

int main(){
    FILE* file;
    while(1){
        printf("选择创建存档或读取存档\n");
        int index = getch()-'0';
        if(index==1)
            file=CreateArch();//创建
        else if(index==2)
            file=ReadFilePlayer();//读取
        else{
            printf("请重新输入\n");
            continue;
        }
        if(file==NULL)    continue;
        DefaultInit(file);
        break;
    }
    while(1){
        int index;
        index=PlayerBehavior();
        if(index==1)    CheckStage();
        if(index==2)    CheckBag_state();
        if(index==3)    CheckDraw_state();
        if(index==4)    Write_File();
        if(index==EIXT){
            printf("退出程序\n");
            return 0;
        }
    }
    return 0;
}


