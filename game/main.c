#include<stdio.h>
#include <conio.h>
#include"item.h"
#include"global.h"
#include"event.h"

int main(){
    FILE* file;
    while(1){
        printf("ѡ�񴴽��浵���ȡ�浵\n");
        int index = getch()-'0';
        if(index==1)
            file=CreateArch();//����
        else if(index==2)
            file=ReadFilePlayer();//��ȡ
        else{
            printf("����������\n");
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
            printf("�˳�����\n");
            return 0;
        }
    }
    return 0;
}


