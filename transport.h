#ifndef TRANSPORT_H_INCLUDED
#define TRANSPORT_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include<wincon.h>
#include<conio.h>  //?
#include<io.h>    //?
#include<fcntl.h>  //?
#include<sys\stat.h>  //?
#include<time.h>  //?

#define SCR_ROW 25 //��Ļ����
#define SCR_COL 80 //��Ļ����

//�����嵥��Ϣ
typedef struct transport_data{
    char name[15];
    int quantity;
    struct transport_date *next;
} TransportData;



#endif // TRANSPORT_H_INCLUDED
