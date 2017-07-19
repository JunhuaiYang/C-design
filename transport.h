#ifndef TRANSPORT_H_INCLUDED
#define TRANSPORT_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include<wincon.h>
#include<stdbool.h>
#include<conio.h>  //?
#include<io.h>    //?
#include<fcntl.h>  //?
#include<sys\stat.h>  //?
#include<time.h>  //?

#define SCR_ROW 25 //屏幕行数
#define SCR_COL 80 //屏幕列数

//货运清单信息
typedef struct transport_data{
    char name[15];   //货物名称
    float quantity;    //数量
    struct transport_date *next;
} TRANSPORT_DATA;

//司机信息
typedef struct driver_data{
    char number[8]; //车辆牌照
    char road[6];  //执行配送路线编号
    char driver[8]; //司机姓名
    char phone[11]; //司机移动电话
}DRIVER_DATA;

//配送车辆基本信息
typedef struct truck_data{
    DRIVER_DATA *pdriver; //司机信息
    float sum; //车总运载量
    TRANSPORT_DATA *goods; //指向货物清单
}TRUCK_DATA;

//经停站点详细信息
typedef struct station_data{
    char road[6]; //固定配送路线编号
    int station_num; //站点序号
    char station_id[10]; //站点编号
    char station_name[50]; //站点名称
    float distance_init; //与起始站点距离
    float distance_up; //与上一个站点距离
    float using_time; //与上一个站点交通耗时
    float stay_time; //停留耗时
    char across_num[20]; //若有交叉固定路线编号，在此给出
    struct station_data *next;
    TRUCK_DATA *truck; //指向车辆基本信息
}STATION_DATA;

//配送路线基本信息
typedef struct road_data{
    char road[6]; //固定配送路线编号
    char road_name[20]; //固定配送路线名称
    short full_station; //固定配送路线总站点数
    float full_distance; //固定配送路线总公里数
    float full_time; //全站点配送总耗时
    char init_station[10]; //起始站点编号
    char fin_station[10]; //终止站点编号
    char charge_person[8]; //负责人姓名
    char call[8]; //负责人办公室电话
    char phone[11]; //负责人移动电话
    char email[50]; //负责人电子邮箱
    struct road_data *next;
    STATION_DATA *station; //指向经停站信息
}ROAD_DATA;

/**
 *屏幕窗口信息链结点结点结构
 */
typedef struct layer_node {
    char LayerNo;            /**< 弹出窗口层数*/
    SMALL_RECT rcArea;       /**< 结构，弹出窗口区域坐标*/
    CHAR_INFO *pContent;     /**< 结构，弹出窗口区域字符单元原信息存储缓冲区*/
    char *pScrAtt;           /**< 弹出窗口区域字符单元原属性值存储缓冲区*/
    struct layer_node *next; /**< 指向下一结点的指针*/
} LAYER_NODE;

/**
 *标签束结构
 */
typedef struct labe1_bundle {
    char **ppLabel;        /**< 标签字符串数组首地址*/
    COORD *pLoc;           /**< 结构，标签定位数组首地址*/
    int num;               /**< 标签个数*/
} LABEL_BUNDLE;

/**
 *热区结构
 */
typedef struct hot_area {
    SMALL_RECT *pArea;     /**< 热区定位数组首地址*/
    char *pSort;           /**< 热区类别(按键、文本框、选项框)数组首地址*/
    char *pTag;            /**< 热区序号数组首地址*/
    int num;               /**< 热区个数*/
} HOT_AREA;

extern LAYER_NODE *gp_top_layer;
extern ROAD_DATA *gp_mhead;
extern CHAR_INFO *gp_buff_menubar_info;
extern CHAR_INFO *gp_buff_stateBar_info;
extern char *gp_scr_att;
extern char *gp_station_code;
extern char gc_sys_state;
extern HANDLE gh_std_out;
extern HANDLE gh_std_in;

//菜单文本
char *gp_sys_name = "物流配送管理信息系统";    //系统名称
char *gp_road_filename = "data\\road\\road.dat";   //保存线路文件名
char *gp_station_filename = "data\\station\\station.dat";  //保存站点信息文件名
char *gp_truck_filename = "data\\truck\\truck.dat";  //保存车辆信息文件名

char *ga_main_menu[] = {"文件(F)",             /*系统主菜单名*/
    	                "数据维护(M)",
                        "数据查询(Q)",
                        "数据统计(S)",
                        "帮助(H)"
                       };

char *ga_sub_menu[] = {"[S] 数据保存",          /*系统子菜单名*/
                       "[B] 数据备份",
                       "[R] 数据恢复",
                       "[X] 退出    Alt+X",
                       "",           /*空串用来在弹出菜单中分隔子菜单项*/
                       "[Q] 站点信息维护",
                       "[W] 路线信息维护",
                       "[E] 车辆信息维护",
                       "",          /*空串用来在弹出菜单中分隔子菜单项*/
                       "[A] 查询站点路线",
                       "[S] 查询路线耗时",
                       "[D] 查询路线里程",
                       "[F] 查询路线经停站点",
                       "[G] 查询可载重量",
                       "[H] 查询指定司机配送清单",
                       "[J] 查询司机联系方式",
                       "[K] 查询制定车辆的配送路线",
                       "",         /*空串用来在弹出菜单中分隔子菜单项*/
                       "[Z] 打印报表",
                       "[X] 为车辆生成配送计划图",
                       "",         /*空串用来在弹出菜单中分隔子菜单项*/
                       "[H] 帮助"
                       "[A] 关于"
                      };

int ga_sub_menu_count[]={4,3,8,2,2};      //各主菜单项下子菜单的个数
int gi_sel_menu = 1;                        /*被选中的主菜单项号,初始为1*/
int gi_sel_sub_menu = 0;                    /*被选中的子菜单项号,初始为0,表示未选中*/


//函数定义
int LoadCode(char *filename, char **ppbuffer);  /*代码表加载*/
//int CreatList(DORM_NODE **pphead);              /*数据链表初始化*/
void InitInterface();                 /*系统界面初始化*/
void ClearScreen(void);                         /*清屏*/
void ShowMenu(void);                            /*显示菜单栏*/
void PopMenu(int num);                          /*显示下拉菜单*/
void PopPrompt(int num);                        /*显示弹出窗口*/
void PopUp(SMALL_RECT *, WORD, LABEL_BUNDLE *, HOT_AREA *);  /*弹出窗口屏幕信息维护*/
void PopOff(void);                              /*关闭顶层弹出窗口*/
void DrawBox(SMALL_RECT *parea);                /*绘制边框*/
void LocSubMenu(int num, SMALL_RECT *parea);    /*主菜单下拉菜单定位*/
void ShowState(void);                           /*显示状态栏*/
void TagMainMenu(int num);                      /*标记被选中的主菜单项*/
void TagSubMenu(int num);                       /*标记被选中的子菜单项*/
int DealConInput(HOT_AREA *phot_area, int *pihot_num);  /*控制台输入处理*/
void SetHotPoint(HOT_AREA *phot_area, int hot_num);     /*设置热区*/
//void RunSys(DORM_NODE **pphd);                  /*系统功能模块的选择和运行*/
BOOL ExeFunction(int main_menu_num, int sub_menu_num);  /*功能模块的调用*/
//void CloseSys(DORM_NODE *phd);                  /*退出系统*/
BOOL ShowModule(char **pString, int n);

BOOL LoadData(void);           /*数据加载*/
BOOL SaveData(void);           /*保存数据*/
BOOL BackupData(void);         /*备份数据*/
BOOL RestoreData(void);        /*恢复数据*/
BOOL ExitSys(void);            /*退出系统*/
BOOL HelpTopic(void);          /*帮助主体*/
BOOL AboutDorm(void);          /*关于系统*/



#endif // TRANSPORT_H_INCLUDED
