#ifndef COMMON_I
#define COMMON_I

#include<stdio.h>
#include"global.h"

//ȫ�ֱ���������
extern struct PlayerData PLAYER;//���
extern struct bag MYBAG;//��ҵı���
extern struct JackPot JACKPOT;//�˴ε�¼���ɵĽ���
extern struct stage LOW;//�����Ѷȹؿ�
extern struct stage MID;
extern struct stage HIGH;
extern FILE *PlayerFile;//�洢���д浵���ļ�
extern struct spirit no_SPI;
extern struct spirit SPI1;
extern struct spirit SPI2;
extern struct spirit SPI3;
extern struct buff no_buff;
extern struct RoundList* LastNode;
extern int NowSPI;
extern char filename[100];//��ǰ�浵��·��
//ö�ٶ���
enum  Option{ 
        SKL_1=1,SKL_2,SKL_3,SKL_4,
        Medicine=5,
        SPI_1=6,SPI_2,SPI_3,
        EIXT=0
};
enum  Level{ low=1,mid,high
};
enum Type{ attack=0,recover
};


//�궨��



#endif