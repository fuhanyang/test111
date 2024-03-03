#ifndef COMMON_E
#define COMMON_E

#include<stdbool.h>




//事件函数声明

//玩家操作函数
int PlayerBehavior();


//抽奖模块函数
int* TenDraw();//十连抽
int SingleDraw();//单抽
void CheckDraw_state();

//背包模块函数
bool CheckSPI_state(int index,int p);//精灵状态
void CheckBag_state();//背包状态



//战斗模块函数
union EFF ChooseSkill(int index,FuncPtr skill_ptr);
int SPI1_skill_1(); 
struct buff SPI1_skill_2(); 
int SPI1_skill_3(); 
struct buff SPI1_skill_4(); 
int SPI2_skill_1(); 
struct buff SPI2_skill_2(); 
int SPI2_skill_3(); 
struct buff SPI2_skill_4(); 
int SPI3_skill_1(); 
struct buff SPI3_skill_2(); 
int SPI3_skill_3(); 
struct buff SPI3_skill_4(); //精灵技能
int Recover();//回复值
struct FightingData InitFightingData(int ScapeLevel);//初始化战斗数据
int dice();//掷骰子函数
int EXP_value(int val);
int DamageValue(int SkillVal,int DiceVal,struct buff buff);//伤害值结算
int RecoverValue(int RecoverVal,int DiceVal);//回复值结算
bool TurnSPI(int index);//切换精灵
char PlayerOpt();//玩家操作
bool PlayerDo(int num,struct FightingData* data);
void AIDo(struct FightingData* data);//AI操作,返回值来判断下回合是否能操作
bool Round(struct FightingData* data);
bool TurnRound(struct FightingData* data);//回合
void Fight(int level);//战斗结束
void SPI_upgrade(int level);//精灵升级


//关卡模块函数
void CheckStage();//挑战关卡

//数据写入模块
void Write_File();



#endif
