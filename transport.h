#ifndef TRANSPORT_H_INCLUDED
#define TRANSPORT_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>  //Win�������
#include<wincon.h>
#include<stdbool.h>
#include<conio.h>  //����̨�����õ�ͷ�ļ�
#include<io.h>    //IO
#include<fcntl.h>  //�ļ����
#include<sys\stat.h>  //����ϵͳ��������
#include<time.h>

#define SCR_ROW 30 //��Ļ����
#define SCR_COL 100 //��Ļ����
#define PAGE_LINE 23  //��ʾ��������

//�����嵥��Ϣ
typedef struct goods_data{
    char road[6]; //�̶�����·�߱��
    char station_id[10]; //վ�����
    int number;   //������
    char name[15];   //��������
    float quantity;    //����
    struct goods_data *next;
} GOODS_DATA;


//���ͳ���������Ϣ
typedef struct truck_data{
    char station_id[10]; //վ�����
    char road[6];  //ִ������·�߱��
    char number[8]; //��������
    char driver[8]; //˾������
    char phone[11]; //˾���ƶ��绰
    GOODS_DATA *goods; //ָ������嵥
}TRUCK_DATA;

//��ͣվ����ϸ��Ϣ
typedef struct station_data{
    char road[6]; //�̶�����·�߱��
    int station_num; //վ����
    char station_id[10]; //վ�����
    char station_name[50]; //վ������
    float distance_init; //����ʼվ�����
    float distance_up; //����һ��վ�����
    float using_time; //����һ��վ�㽻ͨ��ʱ
    float stay_time; //ͣ����ʱ
    char across_num[20]; //���н���̶�·�߱�ţ��ڴ˸���
    struct station_data *next;
    TRUCK_DATA *truck; //ָ����������Ϣ
}STATION_DATA;

typedef struct station_code{
    int station_num;
    char station_name[50];
    struct station_code *next;
}STATION_CODE;

//����·�߻�����Ϣ
typedef struct road_data{
    char road[6]; //�̶�����·�߱��
    char road_name[20]; //�̶�����·������
    short full_station; //�̶�����·����վ����
    float full_distance; //�̶�����·���ܹ�����
    float full_time; //ȫվ�������ܺ�ʱ
    int init_station; //��ʼվ����
    int fin_station; //��ֹվ����
    char charge_person[8]; //����������
    char call[8]; //�����˰칫�ҵ绰
    char phone[11]; //�������ƶ��绰
    char email[50]; //�����˵�������
    struct road_data *next;
    STATION_DATA *station; //ָ��ͣվ��Ϣ
}ROAD_DATA;

/**
 *��Ļ������Ϣ�������ṹ
 */
typedef struct layer_node {
    char LayerNo;            /**< �������ڲ���*/
    SMALL_RECT rcArea;       /**< �ṹ������������������*/
    CHAR_INFO *pContent;     /**< �ṹ���������������ַ���Ԫԭ��Ϣ�洢������*/
    char *pScrAtt;           /**< �������������ַ���Ԫԭ����ֵ�洢������*/
    struct layer_node *next; /**< ָ����һ����ָ��*/
} LAYER_NODE;

/**
 *��ǩ���ṹ
 */
typedef struct labe1_bundle {
    char **ppLabel;        /**< ��ǩ�ַ��������׵�ַ*/
    COORD *pLoc;           /**< �ṹ����ǩ��λ�����׵�ַ*/
    int num;               /**< ��ǩ����*/
} LABEL_BUNDLE;

/**
 *�����ṹ
 �������ǿɵ���ĵط�
 */
typedef struct hot_area {
    SMALL_RECT *pArea;     /**< ������λ�����׵�ַ*/
    char *pSort;           /**< �������(�������ı���ѡ���)�����׵�ַ*/
    char *pTag;            /**< ������������׵�ַ*/
    int num;               /**< ��������*/
} HOT_AREA;

//��������
BOOL MakeDir(void);                          //�����ļ���
int CreatList(ROAD_DATA **pphead);              /*���������ʼ��*/
int LoadCode(void);                 //��������
void InitInterface(void);                 /*ϵͳ�����ʼ��*/
void ClearScreen(void);                         /*����*/
void ShowMenu(void);                            /*��ʾ�˵���*/
void PopMenu(int num);                          /*��ʾ�����˵�*/
int PopPrompt(char** ppString,int* iHot);                        /*��ʾ��������*/
void PopUp(SMALL_RECT *, WORD, LABEL_BUNDLE *, HOT_AREA *);  /*����������Ļ��Ϣά��*/
void PopOff(void);                              /*�رն��㵯������*/
void DrawBox(SMALL_RECT *parea);                /*���Ʊ߿�*/
void LocSubMenu(int num, SMALL_RECT *parea);    /*���˵������˵���λ*/
void ShowState(void);                           /*��ʾ״̬��*/
void TagMainMenu(int num);                      /*��Ǳ�ѡ�е����˵���*/
void TagSubMenu(int num);                       /*��Ǳ�ѡ�е��Ӳ˵���*/
int DealInput(HOT_AREA *phot_area, int *pihot_num);  /*����̨���봦��*/
void SetHotPoint(HOT_AREA *phot_area, int hot_num);     /*��������*/
void RunSys(ROAD_DATA **pphd);                  /*ϵͳ����ģ���ѡ�������*/
BOOL ExeFunction(int main_menu_num, int sub_menu_num);  /*����ģ��ĵ���*/
void CloseSys(ROAD_DATA *phd);                  /*�˳�ϵͳ*/
BOOL ShowModule(char **pString, int n);  //��ʾ��Ϣ
int PopWindowMenu(char **pString, int n,int areanum, int* tag); //�������ڲ˵�
void ReFresh();   // ˢ�½���
void GotoXY(int x, int y); //�ƶ����
int PopTextBox(char **ppstring, int hot, int *tag); //�ı���
void Show_Cursor(BOOL boo); //�����ʾ

BOOL LoadData(void);           /*���ݼ���*/
BOOL SaveData(void);           /*��������*/
BOOL BackupData(void);         /*��������*/
BOOL RestoreData(void);        /*�ָ�����*/
BOOL ExitSys(void);            /*�˳�ϵͳ*/
BOOL HelpTopic(void);          /*��������*/
BOOL About(void);          /*����ϵͳ*/

void SeceletSort(ROAD_DATA **head); //����

BOOL StationCode(void);  //վ����Ϣά��
BOOL RoodCoad(void);  //·����Ϣά��
BOOL TruckCode(void);  // ������Ϣά��

BOOL FindStationRoad(void); //��ѯվ��·��
BOOL FindRoadTime(void);  //��ѯ·�ߺ�ʱ
BOOL FindRoadDistance(void);  //��ѯ·�����
BOOL FindRoad(void);  //��ѯ·�߾�ͣվ��
BOOL FindWeight(void);  //��ѯ��������
BOOL FindDriverGoods(void); //��ѯָ��˾�������嵥
BOOL FindDriverPhone(void);  //��ѯ˾����ϵ��ʽ
BOOL FindTruck(void);  //��ѯ�ƶ�����������·��

BOOL FormCreate(void);   //���ɱ��
BOOL TransportMap(void);  //��������ͼ

BOOL NewStation(void); //¼��վ����Ϣ
BOOL LookStation(void); //�鿴��¼���վ��
BOOL EditStation(void); //�༭վ����Ϣ
BOOL DeleteStation(void); //ɾ��վ����Ϣ

BOOL NewRoad(void);  //¼��·��
BOOL LookRoad(void); //�鿴����·��
BOOL EditRoad(void); //�༭·��
BOOL DeleteRoad(void); //ɾ��·��
BOOL SaveRoad(void);  //����·����Ϣ

BOOL EditTruck(void); //�༭�����ͼ�ʻԱ��Ϣ

BOOL SaveStation(void);//���������ļ�

BOOL EditRoadBase(void); //�༭·�߻�����Ϣ
BOOL EditStationBase(void); //�༭վ�������Ϣ

BOOL InsertRoad(void); //����·��
BOOL InsertStation(void); //����վ��
BOOL InsertGoods(void); //��������嵥

#endif // TRANSPORT_H_INCLUDED
