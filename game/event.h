#ifndef COMMON_E
#define COMMON_E

#include<stdbool.h>




//�¼���������

//��Ҳ�������
int PlayerBehavior();


//�齱ģ�麯��
int* TenDraw();//ʮ����
int SingleDraw();//����
void CheckDraw_state();

//����ģ�麯��
bool CheckSPI_state(int index,int p);//����״̬
void CheckBag_state();//����״̬



//ս��ģ�麯��
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
struct buff SPI3_skill_4(); //���鼼��
int Recover();//�ظ�ֵ
struct FightingData InitFightingData(int ScapeLevel);//��ʼ��ս������
int dice();//�����Ӻ���
int EXP_value(int val);
int DamageValue(int SkillVal,int DiceVal,struct buff buff);//�˺�ֵ����
int RecoverValue(int RecoverVal,int DiceVal);//�ظ�ֵ����
bool TurnSPI(int index);//�л�����
char PlayerOpt();//��Ҳ���
bool PlayerDo(int num,struct FightingData* data);
void AIDo(struct FightingData* data);//AI����,����ֵ���ж��»غ��Ƿ��ܲ���
bool Round(struct FightingData* data);
bool TurnRound(struct FightingData* data);//�غ�
void Fight(int level);//ս������
void SPI_upgrade(int level);//��������


//�ؿ�ģ�麯��
void CheckStage();//��ս�ؿ�

//����д��ģ��
void Write_File();



#endif
