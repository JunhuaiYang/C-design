#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

/** ȫ�ֱ����õ�����ͷ�ļ�
 *
 *  �����������global.c��
 *
 */

#include"transport.h"

extern DWORD ul;
extern LAYER_NODE *gp_top_layer;
extern ROAD_DATA *gp_head;
extern CHAR_INFO *gp_buff_menubar_info;
extern CHAR_INFO *gp_buff_stateBar_info;
extern char *gp_scr_att;
extern char *gp_station_code;
extern char gc_sys_state;
extern HANDLE gh_std_out;
extern HANDLE gh_std_in;

//�˵��ı�
extern char *gp_sys_name ;    //ϵͳ����
extern char *gp_road_filename ;   //������·�ļ���
extern char *gp_station_filename ;  //����վ����Ϣ�ļ���
extern char *gp_truck_filename ;  //���泵����Ϣ�ļ���
extern char *gp_goods_filename ;

extern char *ga_main_menu[] ;

extern char *ga_sub_menu[];

extern int ga_sub_menu_count[];      //�����˵������Ӳ˵��ĸ���
extern int gi_sel_menu ;
extern int gi_sel_sub_menu ;

#endif // GLOBAL_H_INCLUDED
