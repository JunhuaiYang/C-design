#include"transport.h"

/** 全局变量定义文件
 *
 *  声明在global.h中
 *
 */

//全局变量定义

LAYER_NODE *gp_top_layer = NULL;               /*弹出窗口信息链链头*/
ROAD_DATA *gp_mhead = NULL;


CHAR_INFO *gp_buff_menubar_info = NULL;     /*存放菜单条屏幕区字符信息的缓冲区*/
CHAR_INFO *gp_buff_stateBar_info = NULL;    /*存放状态条屏幕区字符信息的缓冲区*/

//用途？？
char *gp_scr_att = NULL;    /*存放屏幕上字符单元属性值的缓冲区*/
char *gp_station_code = NULL;   /*存放站点代码表的数据缓冲区*/
char gc_sys_state = '\0';   /*用来保存系统状态的字符*/

//句柄
HANDLE gh_std_out;          /*标准输出设备句柄*/
HANDLE gh_std_in;           /*标准输入设备句柄*/

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
