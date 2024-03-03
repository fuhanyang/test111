#ifndef COMMON_G
#define COMMON_G

#include<stdio.h>

//���庯��ָ������
typedef void* (*FuncPtr)();

//��Ϸ�ṹ��Ķ���
struct attribute//������ֵ
{
    int BloodVolume;//Ѫ��
    int AttackPower;//������
};
struct experience{//����ֵ
    int NowValue;//��ǰ����ֵ
    int total;//��ǰ������
    int Coe;//�ɳ�ϵ��
};
struct spirit{//����
    char name[20];                        ////������ʹ��const�����ʹ��const�Ͳ���ʹ��ȫ�ֱ���MYBAG��
    struct attribute InitData;//��ʼ����
    struct attribute Coe;//�ɳ�ϵ��
    struct attribute NowAttri;//��ǰ����
    int level;//�ȼ�
    struct experience EXP;
    char SkillName[4][20];//����
    FuncPtr skills[4];
};
struct bag{//��ұ���
    struct spirit SPI[3];
};
struct AI{//���Բ���
    int AI_kind;
};
struct stage{//�ؿ�
    const char name[20];
    const struct spirit SPI;
    const struct AI AI;
};
struct PlayerData{//�������
    char name[20];
    struct bag* BAG;//ȫ�ֱ�����ҵĳ�Աָ��ȫ�ֱ�������
    int LotNum;//�齱����
    int operation[8];//��Ҳ���
};
struct buff{
    int BuffType;
    int BuffTime;
    int BuffVal;
};
struct FightingData{//ս������
    struct RoundList* node;
    struct spirit enemy;
    struct spirit MySPI[3];
    int EnemyBlood;
    int MyBlood[3];
    int field;
};
struct JackPot{//�齱��
    int num[100];
};
union EFF{//����Ч������
    int num;
    struct buff buff;
};
struct RoundList{//�غϽڵ�
    struct buff MyBuff;
    struct buff EnemyBuff;
    struct RoundList* next;
};


//��ʼ������������
FILE* CreateArch();//�����浵
FILE* ReadFilePlayer();//��ȡ�浵
void InitPlayer(FILE *file);//��ʼ�����
void InitBag(FILE *file);//��ʼ������
struct spirit InitEnemy(int level);//��ʼ���жԾ���
struct spirit InitMySPI(FILE* file);//��ʼ���ҵľ���
void InitJackPot();//��ʼ������
void DefaultInit(FILE *file);//Ĭ�ϻ����ĳ�ʼ��
struct RoundList* InitList();
struct RoundList* InsertNode(struct RoundList *head,struct buff MyBuff,struct buff EnemyBuff);
void DeleteNode(struct RoundList* round);
void DeleteList(struct RoundList* round);
//ȫ�ֳ�������
extern const char SPI_1_NAME[];
extern const char SPI_2_NAME[];
extern const char SPI_3_NAME[];
extern const char ENEMY_1_NAME[];
extern const char ENEMY_2_NAME[];
extern const char ENEMY_3_NAME[];
extern const char PLAYERFILE_PATH[];



#endif

