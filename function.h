#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

#include"global.h"
#include"transport.h"

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
BOOL DeleteStationBase(void);  //ɾ��վ��

BOOL InsertRoad(void); //����·��
BOOL InsertStation(void); //����վ��

BOOL InsertGoods(void); //��������嵥
BOOL EditGoods(void);  //�༭�����嵥
BOOL DeleteGoods(void);  //ɾ������



#endif // FUNCTION_H_INCLUDED
