#include<stdio.h>
#include"global.h"
#include"item.h"
//ȫ�ֱ����Ķ���
struct PlayerData PLAYER;//���
struct bag MYBAG;//��ҵı���
struct JackPot JACKPOT;//�˴ε�¼���ɵĽ���
struct stage LOW;//�����Ѷȹؿ�
struct stage MID;
struct stage HIGH;
struct buff no_buff = {attack,0,0};
struct spirit no_SPI = {.level=0};
struct spirit SPI1;
struct spirit SPI2={.name="second",.SkillName[0]="one",.SkillName[1]="two",.SkillName[2]="three",.SkillName[3]="four"};
struct spirit SPI3={.name="third",.SkillName[0]="one",.SkillName[1]="two",.SkillName[2]="three",.SkillName[3]="four"};
struct RoundList* LastNode=NULL;
FILE *PlayerFile;//�洢���д浵���ļ�
FILE *ThisPlayer;//�洢ĳ���浵�����ݵ��ļ�
int NowSPI =0;
char filename[100];