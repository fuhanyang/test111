#include<stdlib.h>
#include<time.h>
#include <unistd.h>
#include <conio.h>//ʹ��getch()����
#include<stdbool.h>
#include"global.h"
#include"item.h"
#include"event.h"


//��Ҳ�������
int PlayerBehavior(){
    printf("----------------ѡ��ģ��---------------\n\n\n");
    return getch()-'0';
};


//�齱ģ�麯��
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
};//ʮ����
int SingleDraw(){
    srand(time(NULL));
    int index=rand()%100;
    if(index<66&&index>=55)    return index%3;
    return -1;
};//����
void CheckDraw_state(){
    printf("��ҵ�ǰ�齱����Ϊ%d            ��ѡ����Ҫ�齱�ķ�ʽ\n",PLAYER.LotNum);
    int index;
    while(1){
        index=getch()-'0';
        if(index==EIXT)   return;
        if(index==1){
            if(PLAYER.LotNum<=0){
                printf("�齱���������޷��齱\n");
                continue;
            }
            int num=SingleDraw();
            PLAYER.LotNum--;
            if(num==-1||MYBAG.SPI[num].level!=0){
                printf("���ź�û�г鵽\n");
                continue;
            }
            printf("�鵽�˵�%dֻ����\n",num+1);
            if(num==0)    MYBAG.SPI[num]=SPI1;
            if(num==1)    MYBAG.SPI[num]=SPI2;
            if(num==2)    MYBAG.SPI[num]=SPI3;
            continue;
        }
        if(index==2){
            if(PLAYER.LotNum<10){
                printf("�齱���������޷��齱\n");
                continue;      
            }
            int *p=TenDraw();
            PLAYER.LotNum-=10;
            for(int i=0;i<10;i++){
                if(*(p+i)==-1||MYBAG.SPI[*(p+i)].level!=0){
                printf("���ź�û�г鵽\n");
                continue;
                }
                printf("�鵽�˵�%dֻ����\n",*(p+i)+1);
                if(*(p+i)==0)    MYBAG.SPI[*(p+i)]=SPI1;
                if(*(p+i)==1)    MYBAG.SPI[*(p+i)]=SPI2;
                if(*(p+i)==2)    MYBAG.SPI[*(p+i)]=SPI3;
                continue;
            }
        }
        else printf("���������,����������\n");
    }

};



//����ģ�麯��
void CheckBag_state(){
    while(1){
        printf("������Ҫ�鿴�ľ���\n");
        int index=getch()-'0';
        if(index>=SPI_1&&index<=SPI_3){
            CheckSPI_state(index,1);
            continue;
        }
        else if(index==EIXT)    return;
        else    printf("���������,����������\n");
    }
};//����״̬



//ս��ģ�麯��
//ȡÿ�������һ������Ϊ��Ҫ�������ڶ���Ϊ����(buff)��������Ϊ���֣����ĸ�Ϊ�ظ�(buff)
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
    printf("����һʹ�ü���1����60 ");
    return 60+(MYBAG.SPI[0].NowAttri.AttackPower+rand()%10)/10;
}; 
struct buff SPI1_skill_2(){
    printf("����һʹ�ü���2��ù�������20\%3�غ�\n\n");
    struct buff Buff={attack,3,20};
    return Buff;
}; 
int SPI1_skill_3(){
    srand(time(NULL));
    printf("����һʹ�ü���3����40 ");
    return 40+(MYBAG.SPI[0].NowAttri.AttackPower+rand()%10)/20;
}; 
struct buff SPI1_skill_4(){
    printf("����һʹ�ü���4��ù�������20\%3�غ�\n\n");
    struct buff Buff={attack,3,20};
    return Buff;
}; 
int SPI2_skill_1(){
    srand(time(NULL));
    printf("�����ʹ�ü���1����50 ");
    return 50+(MYBAG.SPI[1].NowAttri.AttackPower+rand()%10)/10;
}; 
struct buff SPI2_skill_2(){
    printf("�����ʹ�ü���2��ù�������15\%3�غ�\n\n");
    struct buff Buff={attack,3,15};
    return Buff;
}; 
int SPI2_skill_3(){
    srand(time(NULL));
    printf("�����ʹ�ü���3����30 ");
    return 30+(MYBAG.SPI[1].NowAttri.AttackPower+rand()%10)/10;
}; 
struct buff SPI2_skill_4(){
    printf("�����ʹ�ü���4��ù�������15\%3�غ�\n\n");
    struct buff Buff={attack,3,15};
    return Buff;
}; 
int SPI3_skill_1(){
    srand(time(NULL));
    printf("������ʹ�ü���1����80 ");
    return 80+(MYBAG.SPI[2].NowAttri.AttackPower+rand()%10)/10;
}; 
struct buff SPI3_skill_2(){
    printf("������ʹ�ü���2��ù�������25\%3�غ�\n\n");
    struct buff Buff={attack,3,25};
    return Buff;
}; 
int SPI3_skill_3(){
    srand(time(NULL));
    printf("������ʹ�ü���3����60 ");
    return 60+(MYBAG.SPI[2].NowAttri.AttackPower+rand()%10)/10;
}; 
struct buff SPI3_skill_4(){
    printf("������ʹ�ü���4��ù�������25\%3�غ�\n\n");
    struct buff Buff={attack,3,25};
    return Buff;
}; //���鼼��

int Recover(){
    printf("ʹ���˻ظ�\n\n");
    return 60;
};//�ظ�ֵ
struct FightingData InitFightingData(int level){
    struct RoundList* HeadRound ;
    struct FightingData data;
    HeadRound= InitList();
    if(dice()>=3){//��ʼ���غ�
        printf("�������\n");
        LastNode=InsertNode(HeadRound,no_buff,no_buff);//�������
        data.field=1;
    }
    else{
        printf("�з�����\n");
        LastNode=InsertNode(HeadRound,no_buff,no_buff);//AI����
        data.field=0;
    }
//��������ս������
    data.node=HeadRound;
    data.enemy=InitEnemy(level);
    for(int i=0;i<3;i++){
        data.MySPI[i]=MYBAG.SPI[i];
        data.MyBlood[i]=data.MySPI[i].NowAttri.BloodVolume;
    }
    data.EnemyBlood=data.enemy.NowAttri.BloodVolume;

    printf("ս�����ݳ�ʼ���ɹ�\n");
    return data;
};//��ʼ��ս������
int dice(){//�����Ӻ���
    srand(time(NULL));
    int diceval = rand()%6+1;
    printf("������%d��     ",diceval);
    return diceval;
};
int EXP_value(int val){
    return val*(dice()*20+100)/100;
};
int DamageValue(int SkillVal,int DiceVal,struct buff buff){//�˺�ֵ����
    if(buff.BuffType==attack){
        printf("���%d���˺�\n",SkillVal/10*(10+DiceVal*2)*(buff.BuffVal+100)/100);
        return SkillVal/10*(10+DiceVal*2)*(buff.BuffVal+100)/100;
    }
    else
        printf("���%d���˺�\n",(SkillVal/10)*(10+DiceVal*2));
        return (SkillVal/10)*(10+DiceVal*2);
};
int RecoverValue(int RecoverVal,int DiceVal){
    return RecoverVal*(DiceVal*20+100)/100;
};//�ظ�ֵ����
bool TurnSPI(int index){
    if(NowSPI+6==index){
        printf("������л�,������ѡ��\n");
        return false;
    }
    printf(" %d �����л�Ϊ %d ����\n\n",NowSPI+1,index-5);
    NowSPI=index-6;
    return true;
};//�л�����
char PlayerOpt(){
    printf("�������Ĳ���\n\n\n");
    char opt;
    opt = getch();
    return opt;
};//��Ҳ���
bool PlayerDo(int num,struct FightingData* data){
        if(num==EIXT)
            return false;
        if(num>=SKL_1&&num<=SKL_4){
            if(num==SKL_1||num==SKL_3){
                printf("��");
                int val = DamageValue(ChooseSkill(num,data->MySPI[NowSPI].skills[num-1]).num,dice(),data->node->next->MyBuff);
                data->EnemyBlood-=val;
                if(data->EnemyBlood<=0) data->EnemyBlood=0;
                printf("�з�����Ѫ��Ϊ%d\n\n",data->EnemyBlood);
            }
            else{
                printf("��");
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
            printf("��");
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
            printf("����");
            int val = DamageValue(ChooseSkill(index,data->enemy.skills[index-1]).num,dice(),data->node->next->EnemyBuff);
            data->MyBlood[NowSPI]-=val;
            if(data->MyBlood[NowSPI]<=0)    data->MyBlood[NowSPI]=0;
            printf("�ҵľ���Ѫ��Ϊ%d\n\n",data->MyBlood[NowSPI]);
            }
        else{
            printf("����");
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
            printf("����");
            int val = RecoverValue(Recover(),dice());
            if(data->EnemyBlood+val<=data->enemy.NowAttri.BloodVolume)
                data->EnemyBlood=data->enemy.NowAttri.BloodVolume;
            else data->EnemyBlood+=val;
        }
};//AI����
bool CheckSPI_state(int index,int p){
    if(MYBAG.SPI[index-6].level==0){
        printf("û����ֻ����,������ѡ��\n");
        return false;
    }
    if(p==1){
        printf("��������Ϊ%s\n",MYBAG.SPI[index-6].name) ;
        printf("�������ɳ�ϵ��Ϊ%d\n",MYBAG.SPI[index-6].Coe.AttackPower) ;
        printf("Ѫ���ɳ�ϵ��Ϊ%d\n",MYBAG.SPI[index-6].Coe.BloodVolume) ;
        printf("��ǰ����ֵΪ%d\n",MYBAG.SPI[index-6].EXP.NowValue) ;
        printf("�����ܹ���Ҫ����ֵ%d\n",MYBAG.SPI[index-6].EXP.total) ;
        printf("��ʼ������Ϊ%d\n",MYBAG.SPI[index-6].InitData.AttackPower) ;
        printf("��ʼѪ��Ϊ%d\n",MYBAG.SPI[index-6].InitData.BloodVolume) ;
        printf("��ǰ�ȼ�Ϊ%d\n",MYBAG.SPI[index-6].level) ;
        printf("��ǰ������Ϊ%d\n",MYBAG.SPI[index-6].NowAttri.AttackPower) ;
        printf("��ǰѪ��Ϊ%d\n",MYBAG.SPI[index-6].NowAttri.BloodVolume) ;
    }
    // MYBAG.SPI[index-6].SkillName[0];
    // MYBAG.SPI[index-6].SkillName[1];
    // MYBAG.SPI[index-6].SkillName[2];
    // MYBAG.SPI[index-6].SkillName[3];
    return true;

};//����״̬ ,�ڶ�������ȷ���ǲ��Ǿ��ڲ鿴

bool Round(struct FightingData* data){//����غ�
    while(1){
        printf("�غϿ�ʼ\n");
        int index=PlayerOpt()-'0';//��Ҳ���
        if(index==EIXT)    return false;
        if(data->node->next->next==NULL)//������һ���غ�
            LastNode = InsertNode(LastNode,no_buff,no_buff);
        if(data->field==0&&index!=SKL_3){
            AIDo(data);
            if(!TurnRound(data)){    
                printf("���ܼ���\n");
                return false;
            }
            PlayerDo(index,data);
            if(!TurnRound(data)){    
                printf("���ܼ���\n");
                return false;
            }
        }
        else if(index<=SPI_3&&index>=SKL_1){//����ȳ���
            PlayerDo(index,data);
            if(!TurnRound(data)){    
                printf("���ܼ���\n");
                return false;
            }
            AIDo(data);
            if(!TurnRound(data)){    
                printf("���ܼ���\n");
                return false;
            }
        }
        else{
            printf("����Ĳ���,������ѡ��\n");
            continue;
        }
        return true;
    }


    //ѡȡ����
};//�غ�
bool TurnRound(struct FightingData* data){//ս���ܷ����
    if(data->EnemyBlood<=0)
        return false;
    if(data->MyBlood[0]<=0&&data->MyBlood[1]<=0&&data->MyBlood[2]<=0)
        return false;
    while(data->MyBlood[NowSPI]<=0){
        if(CheckSPI_state(NowSPI+6,0))
            printf("�� %d ����������,���л�����\n",NowSPI+1);
        int index=getch()-'0'; 
        if(index<SPI_1||index>SPI_3){
            printf("����Ĳ���,������ѡ��\n");
            continue;
        }
        bool ok=TurnSPI(index);
        while(!CheckSPI_state(index,0)||!ok){
            index=getch()-'0';
            if(index<SPI_1||index>SPI_3){
                printf("����Ĳ���,������ѡ��\n");
                continue;
            }
            ok=TurnSPI(index);
        };//��������Ҳ��ǵ�ǰ��������ֹѭ��
    }
    return true;
};//�غ��ܷ����
void Fight(int level){
    struct FightingData data=InitFightingData(level);
    while(1){

        if(Round(&data)){
            if(data.node->next!=LastNode)
                DeleteNode(data.node);//��һ�غϽ�����׼��������һ�غ�
            else     continue;
        }
        else if(data.EnemyBlood<=0){
            printf("սʤ����\n");
            SPI_upgrade(level);
            PLAYER.LotNum+=level;
            NowSPI=0;
            DeleteList(data.node);
            return;
        }
        else if(data.MyBlood[NowSPI]<=0){
            printf("�����˻���\n");
            DeleteList(data.node);
            NowSPI=0;
            return;
        }
        else{
            printf("�˳��غ�\n");
            DeleteList(data.node);
            NowSPI=0;
            return;
        }
     }
};//ս������
void SPI_upgrade(int level){
    int val;
    if(level==low)    val=EXP_value(100);
    if(level==mid)    val=EXP_value(200);
    if(level==high)   val=EXP_value(350);
    printf("���%d����\n",val);
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
};//��������



//�ؿ�ģ�麯��


void CheckStage(){
    int index;
    while(1){
        printf("ѡ��Ҫ���еĹؿ�\n");
        index= getch()-'0';
        if(index==EIXT)     return;
        if(index<low||index>high){
            printf("�����ѡ��,������ѡ��\n");
            continue;
        }
        else Fight(index);
    }
};


//����д��ģ��
void Write_File(){
    FILE* file=fopen(filename,"w+");
    if(file==NULL){
        printf("�浵ʧ��\n");
        return;
    }   
    fclose(file);//����ļ�֮ǰ��
    file=fopen(filename,"a");//׷��д��
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
    printf("�浵�ɹ�\n");
    fflush(file);
    fclose(file);
    return;
}
