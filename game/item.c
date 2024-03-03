#include<stdio.h>
#include"global.h"
#include"item.h"
//全局变量的定义
struct PlayerData PLAYER;//玩家
struct bag MYBAG;//玩家的背包
struct JackPot JACKPOT;//此次登录生成的奖池
struct stage LOW;//三种难度关卡
struct stage MID;
struct stage HIGH;
struct buff no_buff = {attack,0,0};
struct spirit no_SPI = {.level=0};
struct spirit SPI1;
struct spirit SPI2={.name="second",.SkillName[0]="one",.SkillName[1]="two",.SkillName[2]="three",.SkillName[3]="four"};
struct spirit SPI3={.name="third",.SkillName[0]="one",.SkillName[1]="two",.SkillName[2]="three",.SkillName[3]="four"};
struct RoundList* LastNode=NULL;
FILE *PlayerFile;//存储所有存档的文件
FILE *ThisPlayer;//存储某个存档的数据的文件
int NowSPI =0;
char filename[100];