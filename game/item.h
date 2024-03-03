#ifndef COMMON_I
#define COMMON_I

#include<stdio.h>
#include"global.h"

//全局变量的声明
extern struct PlayerData PLAYER;//玩家
extern struct bag MYBAG;//玩家的背包
extern struct JackPot JACKPOT;//此次登录生成的奖池
extern struct stage LOW;//三种难度关卡
extern struct stage MID;
extern struct stage HIGH;
extern FILE *PlayerFile;//存储所有存档的文件
extern struct spirit no_SPI;
extern struct spirit SPI1;
extern struct spirit SPI2;
extern struct spirit SPI3;
extern struct buff no_buff;
extern struct RoundList* LastNode;
extern int NowSPI;
extern char filename[100];//当前存档的路径
//枚举定义
enum  Option{ 
        SKL_1=1,SKL_2,SKL_3,SKL_4,
        Medicine=5,
        SPI_1=6,SPI_2,SPI_3,
        EIXT=0
};
enum  Level{ low=1,mid,high
};
enum Type{ attack=0,recover
};


//宏定义



#endif