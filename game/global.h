#ifndef COMMON_G
#define COMMON_G

#include<stdio.h>

//定义函数指针类型
typedef void* (*FuncPtr)();

//游戏结构体的定义
struct attribute//精灵数值
{
    int BloodVolume;//血量
    int AttackPower;//攻击力
};
struct experience{//经验值
    int NowValue;//当前经验值
    int total;//当前经验条
    int Coe;//成长系数
};
struct spirit{//精灵
    char name[20];                        ////本来想使用const，结果使用const就不能使用全局变量MYBAG了
    struct attribute InitData;//初始属性
    struct attribute Coe;//成长系数
    struct attribute NowAttri;//当前属性
    int level;//等级
    struct experience EXP;
    char SkillName[4][20];//技能
    FuncPtr skills[4];
};
struct bag{//玩家背包
    struct spirit SPI[3];
};
struct AI{//电脑操作
    int AI_kind;
};
struct stage{//关卡
    const char name[20];
    const struct spirit SPI;
    const struct AI AI;
};
struct PlayerData{//玩家数据
    char name[20];
    struct bag* BAG;//全局变量玩家的成员指向全局变量背包
    int LotNum;//抽奖次数
    int operation[8];//玩家操作
};
struct buff{
    int BuffType;
    int BuffTime;
    int BuffVal;
};
struct FightingData{//战斗数据
    struct RoundList* node;
    struct spirit enemy;
    struct spirit MySPI[3];
    int EnemyBlood;
    int MyBlood[3];
    int field;
};
struct JackPot{//抽奖池
    int num[100];
};
union EFF{//技能效果返回
    int num;
    struct buff buff;
};
struct RoundList{//回合节点
    struct buff MyBuff;
    struct buff EnemyBuff;
    struct RoundList* next;
};


//初始化函数的声明
FILE* CreateArch();//创建存档
FILE* ReadFilePlayer();//读取存档
void InitPlayer(FILE *file);//初始化玩家
void InitBag(FILE *file);//初始化背包
struct spirit InitEnemy(int level);//初始化敌对精灵
struct spirit InitMySPI(FILE* file);//初始化我的精灵
void InitJackPot();//初始化奖池
void DefaultInit(FILE *file);//默认环境的初始化
struct RoundList* InitList();
struct RoundList* InsertNode(struct RoundList *head,struct buff MyBuff,struct buff EnemyBuff);
void DeleteNode(struct RoundList* round);
void DeleteList(struct RoundList* round);
//全局常量声明
extern const char SPI_1_NAME[];
extern const char SPI_2_NAME[];
extern const char SPI_3_NAME[];
extern const char ENEMY_1_NAME[];
extern const char ENEMY_2_NAME[];
extern const char ENEMY_3_NAME[];
extern const char PLAYERFILE_PATH[];



#endif

