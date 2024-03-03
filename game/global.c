#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<time.h>
#include <conio.h>
#include"global.h"
#include"item.h"
#include"event.h"

//ȫ�ֳ�������
const char SPI_1_NAME[] = "first";
const char SPI_2_NAME[] = "second";
const char SPI_3_NAME[] = "thrid";
const char ENEMY_1_NAME[] = "low";
const char ENEMY_2_NAME[] = "mid";
const char ENEMY_3_NAME[] = "high";
const char PLAYERFILE_PATH[] = "D:\\game\\files\\files.txt";



//��ʼ�������Ķ���
FILE* CreateArch(){//�����浵
    PlayerFile=fopen(PLAYERFILE_PATH,"r+");    
    if(PlayerFile==NULL){
        printf("��ȡ�½��浵�ļ�ʧ��\n");
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
        printf("����ʧ��\n");
        return NULL;
    }
    fprintf(file,"first 1000 20 10 1 1000 20 1 0 1000 10 one two three four .");
    printf("�����ɹ�\n");
    fclose(PlayerFile);
    fflush(file);
    fclose(file);
    file=fopen(filename,"r");
    return file;
    };
FILE* ReadFilePlayer(){//��ȡ�浵
    printf("����Ҫ��ȡ�Ĵ浵\n");
    int index = getch()-'0';
    PlayerFile=fopen(PLAYERFILE_PATH,"r+");    
    if(PlayerFile==NULL){
        printf("��ȡ�浵�ļ�ʧ��");
        return NULL;
    }
    char line[100];
    char *word[100];    
    for(int i=0;i<index;i++){
        if(fgets(line,sizeof(line),PlayerFile)==NULL){
            printf("û������浵,��ȡʧ��\n");
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
        printf("��ȡʧ��\n");
        return NULL;
    }
    printf("��ȡ�ɹ��ɹ�\n");
    fclose(PlayerFile);
    file=fopen(word[1],"r");
    return file;
};
void InitPlayer(FILE *file){//��ʼ�����
    printf("�������������\n");
    char name[20];
    scanf("%s",name);
    strcpy(PLAYER.name,name);
    printf("�������Ϊ:%s\n",PLAYER.name);
    PLAYER.LotNum=0;
    InitBag(file);
    fclose(file);
};
void InitBag(FILE *file){//��ʼ������
    printf("׼����ʼ������\n");
    MYBAG.SPI[0]=InitMySPI(file);
    MYBAG.SPI[1]=InitMySPI(file);
    MYBAG.SPI[2]=InitMySPI(file);
    printf("������ʼ�����\n");
};
struct spirit InitEnemy(int level){//��ʼ���жԾ���
    struct spirit enemy={0};
    if(level==low){
        strcpy(enemy.name,ENEMY_1_NAME);
        enemy.NowAttri.BloodVolume= 1000;
        enemy.NowAttri.AttackPower=2;
        enemy.skills[0] =(FuncPtr)SPI1_skill_1;
        enemy.skills[1] =(FuncPtr)SPI1_skill_2;
        enemy.skills[2] =(FuncPtr)SPI1_skill_3;
        enemy.skills[3] =(FuncPtr)SPI1_skill_4;
        printf("���˳�ʼ�����\n");
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
struct spirit InitMySPI(FILE *file){//��ʼ���ҵľ���
    printf("׼����ʼ������\n");
    struct spirit MySPI;
    char DataLine[100];
    char *Data[100];
    if(fgets(DataLine,sizeof(DataLine),file)==NULL){
        printf("û���������\n");
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
    printf("��ʼ���������\n");
    return MySPI;
};
void InitJackPot(){//��ʼ������
    srand(time(NULL));
    for(int i=0;i<100;i++){
        JACKPOT.num[i]=rand()%10;
    }
    printf("���س�ʼ���ɹ�\n");
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
};//Ĭ�ϻ����ĳ�ʼ��
struct RoundList* InitList(){//��ʼ���غ�
    struct RoundList *head=(struct RoundList*)malloc(sizeof(struct RoundList));
    if(head==NULL){
        printf("�غ��б��ʼ��ʧ��\n");
        return NULL;
    }
    printf("�غ��б��ʼ���ɹ�\n");
    return head;
};
struct RoundList* InsertNode(struct RoundList* node,struct buff MyBuff,struct buff EnemyBuff){//���ػغ�,fieldΪ1���Լ��غϣ�Ϊ0�ǵз��غ�
    struct RoundList* round = (struct RoundList*)malloc(sizeof(struct RoundList));
    if(round==NULL){
        printf("���ػغ�ʧ��\n");
        return NULL;
    }
    node->next=round;
    round->MyBuff=MyBuff;
    round->EnemyBuff=EnemyBuff;
    round->next=NULL;
    return round;//�������Ľڵ��ַ
};
void DeleteNode(struct RoundList* round){//ɾ������غϵ���һ�غ�
    struct RoundList* node=round->next;
    round->next=round->next->next;
    if(node!=NULL)
        free(node);
    //printf("ɾ���ɹ�\n");
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