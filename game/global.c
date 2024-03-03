#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<time.h>
#include <conio.h>
#include"global.h"
#include"item.h"
#include"event.h"

//全局常量定义
const char SPI_1_NAME[] = "first";
const char SPI_2_NAME[] = "second";
const char SPI_3_NAME[] = "thrid";
const char ENEMY_1_NAME[] = "low";
const char ENEMY_2_NAME[] = "mid";
const char ENEMY_3_NAME[] = "high";
const char PLAYERFILE_PATH[] = "D:\\game\\files\\files.txt";



//初始化函数的定义
FILE* CreateArch(){//创建存档
    PlayerFile=fopen(PLAYERFILE_PATH,"r+");    
    if(PlayerFile==NULL){
        printf("读取新建存档文件失败\n");
        return NULL;
    }
    char line[100];
    char LastLine[100];
    char *word[100];
    while(fgets(line,sizeof(line),PlayerFile)!=NULL){
        strcpy(LastLine,line);
    }
    word[0]=strtok(LastLine," ");
    for(int i=1; word[i-1]!=NULL;i++){
        word[i]=strtok(NULL," ");
    }
    FILE *file;
    snprintf(filename,sizeof(filename),"D:\\game\\data\\data%d.txt ",atoi(word[0])+1);
    fprintf(PlayerFile,"\n%d %s",atoi(word[0])+1,filename);
    file = fopen(filename,"w");
    if(file==NULL){
        printf("创建失败\n");
        return NULL;
    }
    fprintf(file,"first 1000 20 10 1 1000 20 1 0 1000 10 one two three four .");
    printf("创建成功\n");
    fclose(PlayerFile);
    fflush(file);
    fclose(file);
    file=fopen(filename,"r");
    return file;
    };
FILE* ReadFilePlayer(){//读取存档
    printf("输入要读取的存档\n");
    int index = getch()-'0';
    PlayerFile=fopen(PLAYERFILE_PATH,"r+");    
    if(PlayerFile==NULL){
        printf("读取存档文件失败");
        return NULL;
    }
    char line[100];
    char *word[100];    
    for(int i=0;i<index;i++){
        if(fgets(line,sizeof(line),PlayerFile)==NULL){
            printf("没有这个存档,读取失败\n");
            return NULL;
        }    
    }
    word[0]=strtok(line," ");
    for(int i=1; word[i-1]!=NULL;i++){
        printf("%s\n",word[i-1]);
        word[i]=strtok(NULL," ");
    }
    FILE *file;
    file = fopen(word[1],"a+");
    strcpy(filename,word[1]);
    if(file==NULL){
        printf("读取失败\n");
        return NULL;
    }
    printf("读取成功成功\n");
    fclose(PlayerFile);
    file=fopen(word[1],"r");
    return file;
};
void InitPlayer(FILE *file){//初始化玩家
    printf("请输入玩家名称\n");
    char name[20];
    scanf("%s",name);
    strcpy(PLAYER.name,name);
    printf("你的名字为:%s\n",PLAYER.name);
    PLAYER.LotNum=0;
    InitBag(file);
    fclose(file);
};
void InitBag(FILE *file){//初始化背包
    printf("准备初始化背包\n");
    MYBAG.SPI[0]=InitMySPI(file);
    MYBAG.SPI[1]=InitMySPI(file);
    MYBAG.SPI[2]=InitMySPI(file);
    printf("背包初始化完成\n");
};
struct spirit InitEnemy(int level){//初始化敌对精灵
    struct spirit enemy={0};
    if(level==low){
        strcpy(enemy.name,ENEMY_1_NAME);
        enemy.NowAttri.BloodVolume= 1000;
        enemy.NowAttri.AttackPower=2;
        enemy.skills[0] =(FuncPtr)SPI1_skill_1;
        enemy.skills[1] =(FuncPtr)SPI1_skill_2;
        enemy.skills[2] =(FuncPtr)SPI1_skill_3;
        enemy.skills[3] =(FuncPtr)SPI1_skill_4;
        printf("敌人初始化完成\n");
        return enemy;
    }
    if(level==mid){
        strcpy(enemy.name,ENEMY_2_NAME);
        enemy.NowAttri.BloodVolume= 1500;
        enemy.NowAttri.AttackPower=3;
        enemy.skills[0] =(FuncPtr)SPI1_skill_1;
        enemy.skills[1] =(FuncPtr)SPI1_skill_2;
        enemy.skills[2] =(FuncPtr)SPI1_skill_3;
        enemy.skills[3] =(FuncPtr)SPI1_skill_4;        
        return enemy;
    }
    if(level==high){
        strcpy(enemy.name,ENEMY_3_NAME);   
        enemy.NowAttri.BloodVolume= 2500;
        enemy.NowAttri.AttackPower=4;
        enemy.skills[0] =(FuncPtr)SPI1_skill_1;
        enemy.skills[1] =(FuncPtr)SPI1_skill_2;
        enemy.skills[2] =(FuncPtr)SPI1_skill_3;
        enemy.skills[3] =(FuncPtr)SPI1_skill_4;
        return enemy;
    }
};
struct spirit InitMySPI(FILE *file){//初始化我的精灵
    printf("准备初始化精灵\n");
    struct spirit MySPI;
    char DataLine[100];
    char *Data[100];
    if(fgets(DataLine,sizeof(DataLine),file)==NULL){
        printf("没有这个精灵\n");
        return no_SPI;
    }
    Data[0]=strtok(DataLine," ");
    for(int i=1; Data[i-1]!=NULL;i++){
        //printf("%s\n",Data[i-1]);
        Data[i]=strtok(NULL," ");
    }
    strcpy(MySPI.name,Data[0]);
    MySPI.InitData.BloodVolume=atoi(Data[1]);
    MySPI.InitData.AttackPower=atoi(Data[2]);
    MySPI.Coe.BloodVolume=atoi(Data[3]);
    MySPI.Coe.AttackPower=atoi(Data[4]);
    MySPI.NowAttri.BloodVolume=atoi(Data[5]);
    MySPI.NowAttri.AttackPower=atoi(Data[6]);
    MySPI.level=atoi(Data[7]);
    MySPI.EXP.NowValue=atoi(Data[8]);
    MySPI.EXP.total=atoi(Data[9]);
    MySPI.EXP.Coe=atoi(Data[10]);
    strcpy(MySPI.SkillName[0],Data[11]);
    strcpy(MySPI.SkillName[1],Data[12]);
    strcpy(MySPI.SkillName[2],Data[13]);
    strcpy(MySPI.SkillName[3],Data[14]);
    if(strcmp(MySPI.name,SPI_1_NAME)){
        MySPI.skills[0] =(FuncPtr)SPI1_skill_1;
        MySPI.skills[1] =(FuncPtr)SPI1_skill_2;
        MySPI.skills[2] =(FuncPtr)SPI1_skill_3;
        MySPI.skills[3] =(FuncPtr)SPI1_skill_4;
    }
    if(strcmp(MySPI.name,SPI_2_NAME)){
        MySPI.skills[0] =(FuncPtr)SPI2_skill_1;
        MySPI.skills[1] =(FuncPtr)SPI2_skill_2;
        MySPI.skills[2] =(FuncPtr)SPI2_skill_3;
        MySPI.skills[3] =(FuncPtr)SPI2_skill_4;
    }
    if(strcmp(MySPI.name,SPI_3_NAME)){
        MySPI.skills[0] =(FuncPtr)SPI3_skill_1;
        MySPI.skills[1] =(FuncPtr)SPI3_skill_2;
        MySPI.skills[2] =(FuncPtr)SPI3_skill_3;
        MySPI.skills[3] =(FuncPtr)SPI3_skill_4;
    }
    printf("初始化精灵完成\n");
    return MySPI;
};
void InitJackPot(){//初始化奖池
    srand(time(NULL));
    for(int i=0;i<100;i++){
        JACKPOT.num[i]=rand()%10;
    }
    printf("奖池初始化成功\n");
};
void DefaultInit(FILE *file){
    InitPlayer(file);
    InitJackPot();
    SPI2.Coe.AttackPower=1;
    SPI2.Coe.BloodVolume=15;
    SPI2.EXP.Coe=15;
    SPI2.EXP.NowValue=0;
    SPI2.EXP.total=1500;
    SPI2.InitData.AttackPower=15;
    SPI2.InitData.BloodVolume=1500;
    SPI2.level=1;
    SPI2.NowAttri.AttackPower=15;
    SPI2.NowAttri.BloodVolume=1500;
    SPI2.skills[0] =(FuncPtr)SPI2_skill_1;
    SPI2.skills[1] =(FuncPtr)SPI2_skill_2;
    SPI2.skills[2] =(FuncPtr)SPI2_skill_3;
    SPI2.skills[3] =(FuncPtr)SPI2_skill_4;

    SPI3.Coe.AttackPower=2;
    SPI3.Coe.BloodVolume=5;
    SPI3.EXP.Coe=15;
    SPI3.EXP.NowValue=0;
    SPI3.EXP.total=1500;
    SPI3.InitData.AttackPower=35;
    SPI3.InitData.BloodVolume=700;
    SPI3.level=1;
    SPI3.NowAttri.AttackPower=35;
    SPI3.NowAttri.BloodVolume=700;
    SPI3.skills[0] =(FuncPtr)SPI3_skill_1;
    SPI3.skills[1] =(FuncPtr)SPI3_skill_2;
    SPI3.skills[2] =(FuncPtr)SPI3_skill_3;
    SPI3.skills[3] =(FuncPtr)SPI3_skill_4;
};//默认环境的初始化
struct RoundList* InitList(){//初始化回合
    struct RoundList *head=(struct RoundList*)malloc(sizeof(struct RoundList));
    if(head==NULL){
        printf("回合列表初始化失败\n");
        return NULL;
    }
    printf("回合列表初始化成功\n");
    return head;
};
struct RoundList* InsertNode(struct RoundList* node,struct buff MyBuff,struct buff EnemyBuff){//加载回合,field为1是自己回合，为0是敌方回合
    struct RoundList* round = (struct RoundList*)malloc(sizeof(struct RoundList));
    if(round==NULL){
        printf("加载回合失败\n");
        return NULL;
    }
    node->next=round;
    round->MyBuff=MyBuff;
    round->EnemyBuff=EnemyBuff;
    round->next=NULL;
    return round;//返回最后的节点地址
};
void DeleteNode(struct RoundList* round){//删除传入回合的下一回合
    struct RoundList* node=round->next;
    round->next=round->next->next;
    if(node!=NULL)
        free(node);
    //printf("删除成功\n");
};
void DeleteList(struct RoundList* round){
    struct RoundList* p=round;
    while(round!=NULL){
        p=p->next;
        free(round);
        round=p;
    }
    return;
}