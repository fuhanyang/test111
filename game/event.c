#include<stdlib.h>
#include<time.h>
#include <unistd.h>
#include <conio.h>//使用getch()函数
#include<stdbool.h>
#include"global.h"
#include"item.h"
#include"event.h"


//玩家操作函数
int PlayerBehavior(){
    printf("----------------选择模块---------------\n\n\n");
    return getch()-'0';
};


//抽奖模块函数
int* TenDraw(){
    bool hasGet=false;
    srand(time(NULL));
    static int SPI[10];
    for(int i=0;i<10;i++){
        int index=rand()%100;
        if(index<66&&index>=55){
            SPI[i]=index%3;
            hasGet=true;
        }
        else if(hasGet==false&&i==9){
            SPI[i]=index%3;
        }
        else    SPI[i]=-1;
    }
    return SPI;
};//十连抽
int SingleDraw(){
    srand(time(NULL));
    int index=rand()%100;
    if(index<66&&index>=55)    return index%3;
    return -1;
};//单抽
void CheckDraw_state(){
    printf("玩家当前抽奖次数为%d            请选择你要抽奖的方式\n",PLAYER.LotNum);
    int index;
    while(1){
        index=getch()-'0';
        if(index==EIXT)   return;
        if(index==1){
            if(PLAYER.LotNum<=0){
                printf("抽奖次数不足无法抽奖\n");
                continue;
            }
            int num=SingleDraw();
            PLAYER.LotNum--;
            if(num==-1||MYBAG.SPI[num].level!=0){
                printf("很遗憾没有抽到\n");
                continue;
            }
            printf("抽到了第%d只精灵\n",num+1);
            if(num==0)    MYBAG.SPI[num]=SPI1;
            if(num==1)    MYBAG.SPI[num]=SPI2;
            if(num==2)    MYBAG.SPI[num]=SPI3;
            continue;
        }
        if(index==2){
            if(PLAYER.LotNum<10){
                printf("抽奖次数不足无法抽奖\n");
                continue;      
            }
            int *p=TenDraw();
            PLAYER.LotNum-=10;
            for(int i=0;i<10;i++){
                if(*(p+i)==-1||MYBAG.SPI[*(p+i)].level!=0){
                printf("很遗憾没有抽到\n");
                continue;
                }
                printf("抽到了第%d只精灵\n",*(p+i)+1);
                if(*(p+i)==0)    MYBAG.SPI[*(p+i)]=SPI1;
                if(*(p+i)==1)    MYBAG.SPI[*(p+i)]=SPI2;
                if(*(p+i)==2)    MYBAG.SPI[*(p+i)]=SPI3;
                continue;
            }
        }
        else printf("错误的输入,请重新输入\n");
    }

};



//背包模块函数
void CheckBag_state(){
    while(1){
        printf("输入你要查看的精灵\n");
        int index=getch()-'0';
        if(index>=SPI_1&&index<=SPI_3){
            CheckSPI_state(index,1);
            continue;
        }
        else if(index==EIXT)    return;
        else    printf("错误的输入,请重新输入\n");
    }
};//背包状态



//战斗模块函数
//取每个精灵第一个技能为主要攻击，第二个为增益(buff)，第三个为先手，第四个为回复(buff)
union EFF ChooseSkill(int index,FuncPtr skill_ptr){
    union EFF i;
    if(index==1||index==3){
        i.num=((int(*)())skill_ptr)();
        return i;
    }
    else{
        i.buff=((struct buff(*)())skill_ptr)();
        return i;
    }
};
int SPI1_skill_1(){
    srand(time(NULL));
    printf("精灵一使用技能1威力60 ");
    return 60+(MYBAG.SPI[0].NowAttri.AttackPower+rand()%10)/10;
}; 
struct buff SPI1_skill_2(){
    printf("精灵一使用技能2获得攻击增益20\%3回合\n\n");
    struct buff Buff={attack,3,20};
    return Buff;
}; 
int SPI1_skill_3(){
    srand(time(NULL));
    printf("精灵一使用技能3威力40 ");
    return 40+(MYBAG.SPI[0].NowAttri.AttackPower+rand()%10)/20;
}; 
struct buff SPI1_skill_4(){
    printf("精灵一使用技能4获得攻击增益20\%3回合\n\n");
    struct buff Buff={attack,3,20};
    return Buff;
}; 
int SPI2_skill_1(){
    srand(time(NULL));
    printf("精灵二使用技能1威力50 ");
    return 50+(MYBAG.SPI[1].NowAttri.AttackPower+rand()%10)/10;
}; 
struct buff SPI2_skill_2(){
    printf("精灵二使用技能2获得攻击增益15\%3回合\n\n");
    struct buff Buff={attack,3,15};
    return Buff;
}; 
int SPI2_skill_3(){
    srand(time(NULL));
    printf("精灵二使用技能3威力30 ");
    return 30+(MYBAG.SPI[1].NowAttri.AttackPower+rand()%10)/10;
}; 
struct buff SPI2_skill_4(){
    printf("精灵二使用技能4获得攻击增益15\%3回合\n\n");
    struct buff Buff={attack,3,15};
    return Buff;
}; 
int SPI3_skill_1(){
    srand(time(NULL));
    printf("精灵三使用技能1威力80 ");
    return 80+(MYBAG.SPI[2].NowAttri.AttackPower+rand()%10)/10;
}; 
struct buff SPI3_skill_2(){
    printf("精灵三使用技能2获得攻击增益25\%3回合\n\n");
    struct buff Buff={attack,3,25};
    return Buff;
}; 
int SPI3_skill_3(){
    srand(time(NULL));
    printf("精灵三使用技能3威力60 ");
    return 60+(MYBAG.SPI[2].NowAttri.AttackPower+rand()%10)/10;
}; 
struct buff SPI3_skill_4(){
    printf("精灵三使用技能4获得攻击增益25\%3回合\n\n");
    struct buff Buff={attack,3,25};
    return Buff;
}; //精灵技能

int Recover(){
    printf("使用了回复\n\n");
    return 60;
};//回复值
struct FightingData InitFightingData(int level){
    struct RoundList* HeadRound ;
    struct FightingData data;
    HeadRound= InitList();
    if(dice()>=3){//初始化回合
        printf("玩家先手\n");
        LastNode=InsertNode(HeadRound,no_buff,no_buff);//玩家先手
        data.field=1;
    }
    else{
        printf("敌方先手\n");
        LastNode=InsertNode(HeadRound,no_buff,no_buff);//AI先手
        data.field=0;
    }
//加载其他战斗数据
    data.node=HeadRound;
    data.enemy=InitEnemy(level);
    for(int i=0;i<3;i++){
        data.MySPI[i]=MYBAG.SPI[i];
        data.MyBlood[i]=data.MySPI[i].NowAttri.BloodVolume;
    }
    data.EnemyBlood=data.enemy.NowAttri.BloodVolume;

    printf("战斗数据初始化成功\n");
    return data;
};//初始化战斗数据
int dice(){//掷骰子函数
    srand(time(NULL));
    int diceval = rand()%6+1;
    printf("掷出了%d点     ",diceval);
    return diceval;
};
int EXP_value(int val){
    return val*(dice()*20+100)/100;
};
int DamageValue(int SkillVal,int DiceVal,struct buff buff){//伤害值结算
    if(buff.BuffType==attack){
        printf("造成%d点伤害\n",SkillVal/10*(10+DiceVal*2)*(buff.BuffVal+100)/100);
        return SkillVal/10*(10+DiceVal*2)*(buff.BuffVal+100)/100;
    }
    else
        printf("造成%d点伤害\n",(SkillVal/10)*(10+DiceVal*2));
        return (SkillVal/10)*(10+DiceVal*2);
};
int RecoverValue(int RecoverVal,int DiceVal){
    return RecoverVal*(DiceVal*20+100)/100;
};//回复值结算
bool TurnSPI(int index){
    if(NowSPI+6==index){
        printf("错误的切换,请重新选择\n");
        return false;
    }
    printf(" %d 精灵切换为 %d 精灵\n\n",NowSPI+1,index-5);
    NowSPI=index-6;
    return true;
};//切换精灵
char PlayerOpt(){
    printf("请进行你的操作\n\n\n");
    char opt;
    opt = getch();
    return opt;
};//玩家操作
bool PlayerDo(int num,struct FightingData* data){
        if(num==EIXT)
            return false;
        if(num>=SKL_1&&num<=SKL_4){
            if(num==SKL_1||num==SKL_3){
                printf("我");
                int val = DamageValue(ChooseSkill(num,data->MySPI[NowSPI].skills[num-1]).num,dice(),data->node->next->MyBuff);
                data->EnemyBlood-=val;
                if(data->EnemyBlood<=0) data->EnemyBlood=0;
                printf("敌方精灵血量为%d\n\n",data->EnemyBlood);
            }
            else{
                printf("我");
                struct buff buff =ChooseSkill(num,data->MySPI[NowSPI].skills[num-1]).buff;
                struct RoundList* BuffNode=data->node->next->next;
                for(int i=0;i<buff.BuffTime;i++){
                    if(BuffNode==NULL){
                        LastNode = InsertNode(LastNode,buff,no_buff);
                        BuffNode=LastNode->next;
                    }
                    else{
                        BuffNode->MyBuff=buff;
                        BuffNode=BuffNode->next;
                    }
                }
            }
        }
        else if(num==Medicine){
            printf("我");
            int val = RecoverValue(Recover(),dice());
            if(data->MyBlood[NowSPI]+val<=data->MySPI[NowSPI].NowAttri.BloodVolume)
                data->MyBlood[NowSPI]=data->MySPI[NowSPI].NowAttri.BloodVolume;
            else data->MyBlood[NowSPI]+=val;
        }
        else if(num<=SPI_3&&num>=SPI_1){
            if(!TurnSPI(num)){
                PlayerDo(getch()-'0',data);
            }
        }
        return true;
};
void AIDo(struct FightingData* data){
    srand(time(NULL));
    int index = rand()%100;
    if(index<50)
        index=1;
    else if(index>=50&&index<=65)
        index=2;
    else if(index>65&&index<=85)
        index=3;
    else if(index>85&&index<=95)
        index=4;
    else
        index=5;
    if(index>=SKL_1&&index<=SKL_4){
        if(index==SKL_1||index==SKL_3){
            printf("敌人");
            int val = DamageValue(ChooseSkill(index,data->enemy.skills[index-1]).num,dice(),data->node->next->EnemyBuff);
            data->MyBlood[NowSPI]-=val;
            if(data->MyBlood[NowSPI]<=0)    data->MyBlood[NowSPI]=0;
            printf("我的精灵血量为%d\n\n",data->MyBlood[NowSPI]);
            }
        else{
            printf("敌人");
            struct buff buff =ChooseSkill(index,data->enemy.skills[index-1]).buff;
            struct RoundList* BuffNode=data->node->next->next;
            for(int i=0;i<buff.BuffTime;i++){
                if(BuffNode==NULL){
                    LastNode = InsertNode(LastNode,no_buff,buff);
                    BuffNode=LastNode->next;
                }
                else{
                    BuffNode->EnemyBuff=buff;
                    BuffNode=BuffNode->next;
                }
                }
            }
        }
        if(index==Medicine){
            printf("敌人");
            int val = RecoverValue(Recover(),dice());
            if(data->EnemyBlood+val<=data->enemy.NowAttri.BloodVolume)
                data->EnemyBlood=data->enemy.NowAttri.BloodVolume;
            else data->EnemyBlood+=val;
        }
};//AI操作
bool CheckSPI_state(int index,int p){
    if(MYBAG.SPI[index-6].level==0){
        printf("没有这只精灵,请重新选择\n");
        return false;
    }
    if(p==1){
        printf("精灵名字为%s\n",MYBAG.SPI[index-6].name) ;
        printf("攻击力成长系数为%d\n",MYBAG.SPI[index-6].Coe.AttackPower) ;
        printf("血量成长系数为%d\n",MYBAG.SPI[index-6].Coe.BloodVolume) ;
        printf("当前经验值为%d\n",MYBAG.SPI[index-6].EXP.NowValue) ;
        printf("升级总共需要经验值%d\n",MYBAG.SPI[index-6].EXP.total) ;
        printf("初始攻击力为%d\n",MYBAG.SPI[index-6].InitData.AttackPower) ;
        printf("初始血量为%d\n",MYBAG.SPI[index-6].InitData.BloodVolume) ;
        printf("当前等级为%d\n",MYBAG.SPI[index-6].level) ;
        printf("当前攻击力为%d\n",MYBAG.SPI[index-6].NowAttri.AttackPower) ;
        printf("当前血量为%d\n",MYBAG.SPI[index-6].NowAttri.BloodVolume) ;
    }
    // MYBAG.SPI[index-6].SkillName[0];
    // MYBAG.SPI[index-6].SkillName[1];
    // MYBAG.SPI[index-6].SkillName[2];
    // MYBAG.SPI[index-6].SkillName[3];
    return true;

};//精灵状态 ,第二个参数确定是不是局内查看

bool Round(struct FightingData* data){//定义回合
    while(1){
        printf("回合开始\n");
        int index=PlayerOpt()-'0';//玩家操作
        if(index==EIXT)    return false;
        if(data->node->next->next==NULL)//加入下一个回合
            LastNode = InsertNode(LastNode,no_buff,no_buff);
        if(data->field==0&&index!=SKL_3){
            AIDo(data);
            if(!TurnRound(data)){    
                printf("不能继续\n");
                return false;
            }
            PlayerDo(index,data);
            if(!TurnRound(data)){    
                printf("不能继续\n");
                return false;
            }
        }
        else if(index<=SPI_3&&index>=SKL_1){//玩家先出手
            PlayerDo(index,data);
            if(!TurnRound(data)){    
                printf("不能继续\n");
                return false;
            }
            AIDo(data);
            if(!TurnRound(data)){    
                printf("不能继续\n");
                return false;
            }
        }
        else{
            printf("错误的操作,请重新选择\n");
            continue;
        }
        return true;
    }


    //选取技能
};//回合
bool TurnRound(struct FightingData* data){//战斗能否继续
    if(data->EnemyBlood<=0)
        return false;
    if(data->MyBlood[0]<=0&&data->MyBlood[1]<=0&&data->MyBlood[2]<=0)
        return false;
    while(data->MyBlood[NowSPI]<=0){
        if(CheckSPI_state(NowSPI+6,0))
            printf("第 %d 精灵已死亡,请切换精灵\n",NowSPI+1);
        int index=getch()-'0'; 
        if(index<SPI_1||index>SPI_3){
            printf("错误的操作,请重新选择\n");
            continue;
        }
        bool ok=TurnSPI(index);
        while(!CheckSPI_state(index,0)||!ok){
            index=getch()-'0';
            if(index<SPI_1||index>SPI_3){
                printf("错误的操作,请重新选择\n");
                continue;
            }
            ok=TurnSPI(index);
        };//精灵存在且不是当前精灵则终止循环
    }
    return true;
};//回合能否继续
void Fight(int level){
    struct FightingData data=InitFightingData(level);
    while(1){

        if(Round(&data)){
            if(data.node->next!=LastNode)
                DeleteNode(data.node);//这一回合结束，准备进入下一回合
            else     continue;
        }
        else if(data.EnemyBlood<=0){
            printf("战胜敌人\n");
            SPI_upgrade(level);
            PLAYER.LotNum+=level;
            NowSPI=0;
            DeleteList(data.node);
            return;
        }
        else if(data.MyBlood[NowSPI]<=0){
            printf("被敌人击败\n");
            DeleteList(data.node);
            NowSPI=0;
            return;
        }
        else{
            printf("退出回合\n");
            DeleteList(data.node);
            NowSPI=0;
            return;
        }
     }
};//战斗结束
void SPI_upgrade(int level){
    int val;
    if(level==low)    val=EXP_value(100);
    if(level==mid)    val=EXP_value(200);
    if(level==high)   val=EXP_value(350);
    printf("获得%d经验\n",val);
    for(int i=0;i<3;i++){
        if(MYBAG.SPI[i].level==0)   continue;
        MYBAG.SPI[i].EXP.NowValue+=val;
        while(MYBAG.SPI[i].EXP.NowValue>=MYBAG.SPI[i].EXP.total){
            MYBAG.SPI[i].EXP.NowValue=MYBAG.SPI[i].EXP.NowValue+val-MYBAG.SPI[i].EXP.total;
            val=0;
            MYBAG.SPI[i].level++;
            MYBAG.SPI[i].EXP.total+=level*MYBAG.SPI[i].EXP.Coe;
            MYBAG.SPI[i].NowAttri.AttackPower+=MYBAG.SPI[i].Coe.AttackPower+level%2;
            MYBAG.SPI[i].NowAttri.BloodVolume+=MYBAG.SPI[i].Coe.BloodVolume+level%10;
        }
    }
};//精灵升级



//关卡模块函数


void CheckStage(){
    int index;
    while(1){
        printf("选择要进行的关卡\n");
        index= getch()-'0';
        if(index==EIXT)     return;
        if(index<low||index>high){
            printf("错误的选择,请重新选择\n");
            continue;
        }
        else Fight(index);
    }
};


//数据写入模块
void Write_File(){
    FILE* file=fopen(filename,"w+");
    if(file==NULL){
        printf("存档失败\n");
        return;
    }   
    fclose(file);//清空文件之前；
    file=fopen(filename,"a");//追加写入
    for(int i=0;i<3;i++){
        if(MYBAG.SPI[i].level!=0){
            fprintf(file,"%s ",MYBAG.SPI[i].name);
            fprintf(file,"%d ",MYBAG.SPI[i].InitData.BloodVolume);
            fprintf(file,"%d ",MYBAG.SPI[i].InitData.AttackPower);
            fprintf(file,"%d ",MYBAG.SPI[i].Coe.BloodVolume);
            fprintf(file,"%d ",MYBAG.SPI[i].Coe.AttackPower);
            fprintf(file,"%d ",MYBAG.SPI[i].NowAttri.BloodVolume);
            fprintf(file,"%d ",MYBAG.SPI[i].NowAttri.AttackPower);
            fprintf(file,"%d ",MYBAG.SPI[i].level);
            fprintf(file,"%d ",MYBAG.SPI[i].EXP.NowValue);
            fprintf(file,"%d ",MYBAG.SPI[i].EXP.total);
            fprintf(file,"%d ",MYBAG.SPI[i].EXP.Coe);
            fprintf(file,"%s ",MYBAG.SPI[i].SkillName[0]);
            fprintf(file,"%s ",MYBAG.SPI[i].SkillName[1]);
            fprintf(file,"%s ",MYBAG.SPI[i].SkillName[2]);
            fprintf(file,"%s \n",MYBAG.SPI[i].SkillName[3]);
        }
    }
    printf("存档成功\n");
    fflush(file);
    fclose(file);
    return;
}
