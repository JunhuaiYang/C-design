#include"transport.h"

/** ȫ�ֱ��������ļ�
 *
 *  ������global.h��
 *
 */

//ȫ�ֱ�������

DWORD ul; //��ɫ����

LAYER_NODE *gp_top_layer = NULL;               /*����������Ϣ����ͷ*/
ROAD_DATA *gp_head = NULL;


CHAR_INFO *gp_buff_menubar_info = NULL;     /*��Ų˵�����Ļ���ַ���Ϣ�Ļ�����*/
CHAR_INFO *gp_buff_stateBar_info = NULL;    /*���״̬����Ļ���ַ���Ϣ�Ļ�����*/

//��;����
char *gp_scr_att = NULL;    /*�����Ļ���ַ���Ԫ����ֵ�Ļ�����*/
char *gp_station_code = NULL;   /*���վ����������ݻ�����*/
char gc_sys_state = '\0';   /*��������ϵͳ״̬���ַ�*/

//���
HANDLE gh_std_out;          /*��׼����豸���*/
HANDLE gh_std_in;           /*��׼�����豸���*/

//�˵��ı�
char *gp_sys_name = "�������͹�����Ϣϵͳ";    //ϵͳ����
char *gp_road_filename = "data\\road\\road.dat";   //������·�ļ���
char *gp_station_filename = "data\\station\\station.dat";  //����վ����Ϣ�ļ���
char *gp_truck_filename = "data\\truck\\truck.dat";  //���泵����Ϣ�ļ���
char *gp_goods_filename = "data\\truck\\goods.dat";  //���泵�������嵥

char *ga_main_menu[] = {"�ļ�(F)",             /*ϵͳ���˵���*/
    	                "����ά��(M)",
                        "���ݲ�ѯ(Q)",
                        "����ͳ��(S)",
                        "����(H)"
                       };

char *ga_sub_menu[] = {"[S] ���ݱ���",          /*ϵͳ�Ӳ˵���*/
                       "[B] ���ݱ���",
                       "[R] ���ݻָ�",
                       "[X] �˳�    Alt+X",

                       "[Q] վ����Ϣά��",
                       "[W] ·����Ϣά��",
                       "[E] ������Ϣά��",

                       "[A] ��ѯվ��·��",
                       "[S] ��ѯ·�ߺ�ʱ",
                       "[D] ��ѯ·�����",
                       "[F] ��ѯ·�߾�ͣվ��",
                       "[G] ��ѯ��������",
                       "[H] ��ѯָ��˾�������嵥",
                       "[J] ��ѯ˾����ϵ��ʽ",
                       "[K] ��ѯ�ƶ�����������·��",

                       "[Z] ��ӡ����",
                       "[X] Ϊ�����������ͼƻ�ͼ",

                       "[H] ����",
                       "[A] ����"
                      };

int ga_sub_menu_count[]={4,3,8,2,2};      //�����˵������Ӳ˵��ĸ���
int gi_sel_menu = 1;                        /*��ѡ�е����˵����,��ʼΪ1*/
int gi_sel_sub_menu = 0;                    /*��ѡ�е��Ӳ˵����,��ʼΪ0,��ʾδѡ��*/
