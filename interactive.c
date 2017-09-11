#include"global.h"

/**
 *
 * \brief ���ļ���Ҫ���潻������ĺ���
 *
 */

 BOOL ExeFunction(int m, int s)
{
    BOOL bRet = TRUE;
    /*����ָ�����飬����������й��ܺ�������ڵ�ַ*/
    BOOL (*pFunction[ga_sub_menu_count[0]+ga_sub_menu_count[1]+ga_sub_menu_count[2]+ga_sub_menu_count[3]+ga_sub_menu_count[4]])(void);
    int i, loc;

    /*�����ܺ�����ڵ�ַ�����빦�ܺ����������˵��ź��Ӳ˵��Ŷ�Ӧ�±������Ԫ��*/
    pFunction[0] = SaveData;
    pFunction[1] = ExitSys;

    pFunction[2] = StationCode;
    pFunction[3] = RoodCoad;
    pFunction[4] = TruckCode;

    pFunction[5] = FindStationRoad;
    pFunction[6] = FindRoadTime;
    pFunction[7] = FindRoadDistance;
    pFunction[8] = FindRoad;
    pFunction[9] = FindWeight;
    pFunction[10] = FindDriverGoods;
    pFunction[11] = FindDriverPhone;
    pFunction[12] = FindTruck;

    pFunction[13] = FormCreate;
    pFunction[14] = TransportMap;

    pFunction[15] = HelpTopic;
    pFunction[16] = About;

    for (i=1,loc=0; i<m; i++)  /*�������˵��ź��Ӳ˵��ż����Ӧ�±�*/
    {
        loc += ga_sub_menu_count[i-1];
    }
    loc += s - 1;

    if (pFunction[loc] != NULL)
    {
        bRet = (*pFunction[loc])();  /*�ú���ָ�������ָ��Ĺ��ܺ���*/
    }

    return bRet;
}

BOOL SaveData(void)
{
    char *pCh= "ȷ�ϱ���������";
    int iHot = 1;
    int sRet;
    BOOL bRet;

    sRet = PopPrompt(&pCh, &iHot);
    if (sRet == 13 && iHot == 1)
    {
        SaveRoad();
        bRet = TRUE;
    }
    else
    {
        bRet = TRUE;
    }
    PopOff();


    return bRet;
}


BOOL ExitSys(void)
{
    char *pCh = "ȷ���˳�ϵͳ��";
    int iHot = 1;
    int sRet;
    BOOL bRet;

    sRet = PopPrompt(&pCh, &iHot);

    if (sRet== 13 && iHot == 1)
    {
        bRet = FALSE;
    }
    else
    {
        bRet = TRUE;
    }
    PopOff();

    return bRet;
}

BOOL StationCode(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"վ����Ϣά��",
                           "�鿴��¼���վ��",
                           "¼��վ����Ϣ",
                           "�༭վ����Ϣ",
                           "ɾ��վ����Ϣ",
                           "����"
                          };

    int sTag = 1;
    int sRet;

    sRet = PopWindowMenu(plabel_name, 6, 5, &sTag); //��������

    if (sRet== 13 && sTag == 1)
    {
        PopOff();
        LookStation();
    }
    else if (sRet==13 && sTag ==2)
    {
        PopOff();
        NewStation();
    }
    else if (sRet==13 && sTag == 3)
    {
        PopOff();
        EditStation();
    }
    else if (sRet==13 && sTag == 4)
    {
        PopOff();
        DeleteStation();
    }
    else
    {
        PopOff();
    }

    return bRet;
}

BOOL RoodCoad(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"·����Ϣά��",
                           "�鿴����·��",
                           "¼��·��",
                           "�༭·��",
                           "ɾ��·��",
                           "����"
                          };
    int sTag = 1;
    int sRet;

    sRet = PopWindowMenu(plabel_name, 6, 5, &sTag); //��������

    if (sRet== 13 && sTag == 1)
    {
        PopOff();
        LookRoad();
    }
    else if (sRet==13 && sTag ==2)
    {
        PopOff();
        NewRoad();
    }
    else if (sRet==13 && sTag == 3)
    {
        PopOff();
        EditRoad();
    }
    else if (sRet==13 && sTag == 4)
    {
        PopOff();
        DeleteRoad();
    }
    else
    {
        PopOff();
    }

    return bRet;
}

BOOL TruckCode(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"��������ʻԱ��Ϣά��",
                           "�༭��������ʻԱ��Ϣ",
                           "��������嵥",
                           "�༭�����嵥",
                           "ɾ�������嵥",
                           "����"
                          };

    int sTag = 1;
    int sRet;

    sRet = PopWindowMenu(plabel_name, 6, 5, &sTag); //��������
    if(sRet == 13 && sTag==1)
    {
        PopOff();
        EditTruck();
    }
    else if (sRet==13 && sTag ==2)
    {
        PopOff();
        InsertGoods();
    }
    else if (sRet==13 && sTag == 3)
    {
        PopOff();
        EditGoods();
    }
    else if (sRet==13 && sTag == 4)
    {
        PopOff();
        DeleteGoods();
    }
    else
    {
        PopOff();
    }

    return bRet;
}

BOOL FindStationRoad(void)
{
    BOOL bRet = TRUE;
    ROAD_DATA *proad;
    STATION_DATA *pstation;
    int find;
    STATION_CODE *tail;
    char tfind[20];
    int flag = 0;

    GotoXY(40,3);
    printf("��ѯվ��·��");
    loop21:
    printf("\n\n\t\t������Ҫ��ѯ��վ���ţ�");
    Show_Cursor(TRUE);
    scanf("%d",&find);
    Show_Cursor(FALSE);
    tail = gp_station_code;

    while(tail->station_num != find )
    {
        tail = tail->next;
        if(tail == NULL)
        {
            printf("\tδ���ҵ��ñ�ţ������³��ԣ�");
            goto loop21;
        }
    }
    printf("\n\t\t��վ����Ϊ�� %d     վ������Ϊ��%s",tail->station_num,tail->station_name);
    printf("\n\n\t\t������վ���·���У�\n");
    strcpy(tfind, tail->station_name);
    proad = gp_head;
    while(proad)
    {
        pstation = proad->station;
        while(pstation)
        {
            if(!strcmp(pstation->station_name,tfind))
            {
                flag = 1;
                printf("\t\t%s---%s\n",proad->road, proad->road_name);
                break;
            }
        }
        proad = proad->next;
    }
    if(flag == 0) printf("\n\t\tû���ҵ���·");

    printf("\n\t\t�밴���������");
    getch();
    ReFresh();



    return bRet;
}

BOOL FindRoadTime(void)
{
    BOOL bRet = TRUE;
    float longest, shortest;
    ROAD_DATA *proad;
    char road_num[6],road_name[10];


    GotoXY(40,3);
    printf("��ѯ��ʱ�����̵�·��");

    if(gp_head != NULL)
    {
        proad = gp_head;
        longest = proad->full_time;
        strcpy(road_num,proad->road);
        strcpy(road_name,proad->road_name);
        proad = proad->next;
        while(proad)
        {
            if(proad->full_time > longest)
            {
                longest = proad->full_time;
                strcpy(road_num,proad->road);
                strcpy(road_name,proad->road_name);
            }
            proad = proad->next;
        }
        printf("\n\n\t\t��ʱ���·��Ϊ %s----%s  ·������ʱ��Ϊ��%.2f�����ӣ�",road_num,road_name,longest);

        proad = gp_head;
        shortest = proad->full_time;
        strcpy(road_num,proad->road);
        strcpy(road_name,proad->road_name);
        proad = proad->next;
        while(proad)
        {
            if(proad->full_time < shortest)
            {
                shortest = proad->full_time;
                strcpy(road_num,proad->road);
                strcpy(road_name,proad->road_name);
            }
            proad = proad->next;
        }
        printf("\n\n\t\t��ʱ��̵�·��Ϊ %s----%s  ·������ʱ��Ϊ��%.2f�����ӣ�",road_num,road_name,shortest);
    }
    else  //����ͷ����
    {
        printf("\n\n\t\t��ǰû��¼��·�ߣ���ȥ¼��·��");
    }
    printf("\n\n\t\t�밴���������...");
    getch();
    ReFresh();

    return bRet;
}

BOOL FindRoadDistance(void)
{
BOOL bRet = TRUE;
    float longest, shortest;
    ROAD_DATA *proad;
    char road_num[6],road_name[10];


    GotoXY(40,3);
    printf("��ѯ·�߹����������̵�·��");

    if(gp_head != NULL)
    {
        proad = gp_head;
        longest = proad->full_distance;
        strcpy(road_num,proad->road);
        strcpy(road_name,proad->road_name);
        proad = proad->next;
        while(proad)
        {
            if(proad->full_distance > longest)
            {
                longest = proad->full_distance;
                strcpy(road_num,proad->road);
                strcpy(road_name,proad->road_name);
            }
            proad = proad->next;
        }
        printf("\n\n\t\t���������·��Ϊ %s----%s  ·�������Ϊ��%.2f�����",road_num,road_name,longest);

        proad = gp_head;
        shortest = proad->full_distance;
        strcpy(road_num,proad->road);
        strcpy(road_name,proad->road_name);
        proad = proad->next;
        while(proad)
        {
            if(proad->full_distance < shortest)
            {
                shortest = proad->full_distance;
                strcpy(road_num,proad->road);
                strcpy(road_name,proad->road_name);
            }
            proad = proad->next;
        }
        printf("\n\n\t\t��������̵�·��Ϊ %s----%s  ·�������Ϊ��%.2f�����",road_num,road_name,shortest);
    }
    else  //����ͷ����
    {
        printf("\n\n\t\t��ǰû��¼��·�ߣ���ȥ¼��·��");
    }
    printf("\n\n\t\t�밴���������...");
    getch();
    ReFresh();

    return bRet;
}

BOOL FindRoad(void)
{
    BOOL bRet = TRUE;
    ROAD_DATA *proad;
    STATION_DATA *pstation;
    char fname[6];
    char key;

    GotoXY(40,3);
    printf("��ѯָ��·�ߵ����о�ͣվ�㡣");

    printf("\n\n\t\t\t��ǰ����·�ߣ�");
    proad = gp_head;
    printf("\n\t\t");
    if(gp_head == NULL)
    {
        printf("��ǰû��·��¼�룬��ǰȥ¼��·�ߣ�");
        getch();
        ReFresh();
        return FALSE;
    }
    while(proad)
    {
        printf("\n\t\t%s--%s  ",proad->road,proad->road_name);
        proad=proad->next;
    }

    //����·�����
    loop24:
    printf("\n\n\t\t������Ҫ��ѯ��·��(��1����)��");
    Show_Cursor(TRUE);
    scanf("%s",fname);
    Show_Cursor(FALSE);
    proad = gp_head;
    while(strcmp(fname,proad->road) != 0)
    {
        proad=proad->next;
        if(proad == NULL)
        {
            printf("\n\n\t\tû���ҵ���·�ߣ����������룡��E�˳�");
            key = getch();
            if(key == 'e' || key == 'E')
            {
                ReFresh();
                return FALSE;
            }
            goto loop24;
        }
    }
    printf("\n\t\t���ҵ�����·����·�ߵľ�ͣվ����ϢΪ��\n\n\t\t");
    pstation = proad->station;
    while(pstation->next)
    {
        printf("%s -> ",pstation->station_name);
        pstation = pstation->next;
    }
    printf("%s",pstation->station_name);

    printf("\n\n\t\t�밴���������");
    getch();
    ReFresh();

    return bRet;
}

BOOL FindWeight(void)
{
    BOOL bRet = TRUE;
    ROAD_DATA *proad;
    STATION_DATA *pstation;
    TRUCK_DATA *ptruck, *ptruck_head;
    char fstation[20];
    float fvloume;
    int flag = 0;

    GotoXY(30,3);
    printf("��ѯ��ͣĳվ����ʣ����ػ�����Ϊָ�������ĳ���");

    if(gp_head != NULL)
    {
        printf("\n\n\t\t������Ҫ��ѯ��վ��:");
        Show_Cursor(TRUE);
        scanf("%s",fstation);
        printf("\n\t\t������ָ����������");
        scanf("%f",&fvloume);
        Show_Cursor(FALSE);

        ReFresh();
        GotoXY(30,3);
        printf("��ѯ��ͣĳվ����ʣ����ػ�����Ϊָ�������ĳ���");
        printf("\n\n\t\t��ѯ���Ϊ��");
        proad = gp_head;
        while(proad)
        {
            pstation = proad->station;
            ptruck_head = pstation->truck;
            while(pstation)
            {
                ptruck = pstation->truck;
                if(strcmp(pstation->station_name,fstation) == 0)
                {
                    if(ptruck->left_volume > fvloume)
                    {
                        flag = 1;
                        printf("\n\n\t\t%s---%s\tվ�����:%s\tվ������:%s\n\t\t�������գ�%s\t˾��������%s\t˾���ƶ��绰��%s\n\t\tʣ����ػ���Ϊ:%.2f",
                               proad->road,proad->road_name,pstation->station_id,pstation->station_name,ptruck_head->number,ptruck_head->driver,ptruck_head->phone,ptruck->left_volume);
                    }
                }
                pstation = pstation->next;
            }
            proad = proad->next;
        }
        if(flag == 0)
        {
            printf("\n\n\t\tû���ҵ���");
        }
    }
    else
    {
        printf("\n\t\t��ǰû��·��¼�룡��ȥ¼��·��");
    }

    printf("\n\t\t�밴���������...");
    getch();
    ReFresh();

    return bRet;
}

BOOL FindDriverGoods(void)
{
    BOOL bRet = TRUE;
    char fdriver[8];
    ROAD_DATA *proad;
    STATION_DATA *pstation;
    TRUCK_DATA *ptruck;
    GOODS_DATA *pgoods;
    int flag = 0;

    GotoXY(35,3);
    printf("��ѯָ��˾���������嵥");
    printf("\n\n\t\t��������Ҫ��ѯ��˾����");
    Show_Cursor(TRUE);
    scanf("%s",fdriver);

    if(gp_head != NULL)
    {
        proad = gp_head;
        while(proad)
        {
            pstation = proad->station;
            ptruck = pstation->truck;
            if(!strcmp(fdriver,ptruck->driver))
            {
                flag = 1;
                printf("\n\n\t\t%s---%s\tվ����ţ�%s\tվ�����ƣ�%s",proad->road,proad->road_name,pstation->station_id,pstation->station_name);
                printf("\n\t\t��վ�ػ�");
                pgoods = ptruck->goods;
                printf("\n\t\t������\t��������\t�������֣�");
                while(pgoods)
                {
                    printf("\n\t\t%d\t\t%s\t%.2f",pgoods->number,pgoods->name,pgoods->quantity);
                    pgoods = pgoods->next;
                }
                pstation = pstation->next;
                while(pstation)
                {
                    ptruck = pstation->truck;
                    pgoods = ptruck->goods;
                    printf("\n\n\t\t%s---%s\tվ����ţ�%s\tվ�����ƣ�%s",proad->road,proad->road_name,pstation->station_id,pstation->station_name);
                    printf("\n\t\t��վж��");
                    printf("\n\t\t������\t��������\t�������֣�");
                    while(pgoods)
                    {
                        printf("\n\t\t%d\t\t%s\t%.2f",pgoods->number,pgoods->name,pgoods->quantity);
                        pgoods = pgoods->next;
                    }
                    pstation = pstation->next;
                }
            }
            proad = proad->next;
        }
        if(flag == 0) printf("\n\t\tû���ҵ���˾����");
    }
    else
    {
        printf("\n\t\t��ǰû��·��¼�룡��ȥ¼��·��");
    }

    printf("\n\n\t\t�밴���������...");
    getch();
    ReFresh();


    return bRet;
}

BOOL FindDriverPhone(void)
{
    BOOL bRet = TRUE;
    char fdriver[8];
    ROAD_DATA *proad;
    STATION_DATA *pstation;
    TRUCK_DATA *ptruck;
    int flag = 0;

    GotoXY(35,3);
    printf("��ѯָ��������˾����ϵ��ʽ");
    printf("\n\n\t\t��������Ҫ��ѯ�ĳ��ƺţ�");
    Show_Cursor(TRUE);
    scanf("%s",fdriver);

    if(gp_head != NULL)
    {
        proad = gp_head;
        while(proad)
        {
            pstation = proad->station;
            ptruck = pstation->truck;
            if(!strcmp(fdriver,ptruck->number))
            {
                flag = 1;
                printf("\n\n\t\t%s---%s",proad->road,proad->road_name);
                printf("\n\t\t���ƺţ�%s\t˾��������%s\n\t\t˾����ϵ��ʽ:%s",ptruck->number,ptruck->driver,ptruck->phone);
            }
            proad = proad->next;
        }
        if(flag == 0) printf("\n\t\tû���ҵ��ó�����");
    }
    else
    {
        printf("\n\t\t��ǰû��·��¼�룡��ȥ¼��·��");
    }

    printf("\n\n\t\t�밴���������...");
    getch();
    ReFresh();




    return bRet;
}

BOOL FindTruck(void)
{
    BOOL bRet = TRUE;
    char fdriver[8];
    ROAD_DATA *proad;
    STATION_DATA *pstation;
    TRUCK_DATA *ptruck;
    int flag = 0;


    GotoXY(35,3);
    printf("��ѯָ������������·��");
    printf("\n\n\t\t��������Ҫ��ѯ�ĳ��ƺţ�");
    Show_Cursor(TRUE);
    scanf("%s",fdriver);

    if(gp_head != NULL)
    {
        proad = gp_head;
        while(proad)
        {
            pstation = proad->station;
            ptruck = pstation->truck;
            if(!strcmp(fdriver,ptruck->number))
            {
                flag = 1;
                printf("\n\n\t\t��ǰ·��Ϊ:%s---%s\n\t\t",proad->road,proad->road_name);
                while(pstation->next)
                {
                    printf("%s->",pstation->station_name);
                    pstation = pstation->next;
                }
                printf("%s",pstation->station_name);

            }
            proad = proad->next;
        }
        if(flag == 0) printf("\n\t\tû���ҵ��ó�����");
    }
    else
    {
        printf("\n\t\t��ǰû��·��¼�룡��ȥ¼��·��");
    }
    Show_Cursor(FALSE);
    printf("\n\n\t\t�밴���������");
    getch();
    ReFresh();


    return bRet;
}

BOOL FormCreate(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"��ʾ��Ϣ",
                           "�ù�����δ��ɣ���鿴���ͼƻ�ͼ��",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    return bRet;
}

BOOL TransportMap(void)
{
    BOOL bRet = TRUE;
    ROAD_DATA *proad;
    STATION_DATA *pstation;
    TRUCK_DATA *ptruck;
    GOODS_DATA *pgoods;
    SMALL_RECT Rc;
    COORD pos,size;
    int page = 0, page_count = 0, line_count = 0, i = 0;


    ClearScreen();
    if(gp_head == NULL)
    {
        printf("\t\t��ǰû��¼��·�ߣ�����¼��·�ߣ�");
        getch();
        return FALSE;
    }

    //��ҳ������
    proad = gp_head;
    while(proad)
    {
        page++;
        proad = proad->next;
    }

    size.X = SCR_COL;
    size.Y = page*80;  //��Ź�������
    SetConsoleScreenBufferSize(gh_std_out, size);
    //��ʾ����
    proad = gp_head;
    while(proad)
    {
        //��ʼ��
        pstation = proad->station;
        ptruck = pstation->truck;
        pgoods = ptruck->goods;
        //���Ʊ߿��ʼ��
        Rc.Left = 4;
        Rc.Right = 95;
        Rc.Top = line_count;
        page_count++;
        line_count++;
        GotoXY(40,line_count);
        printf("%s ���ͼƻ�",ptruck->number);
        line_count++;
        pos.X = 5;
        pos.Y = line_count;
        //���Ʒָ�
        for(i=0;i<90;i++,pos.X++)
            WriteConsoleOutputCharacter(gh_std_out,"-",1,pos,&ul);
        line_count+=2;
        GotoXY(0,line_count);
        printf("\t\t\t\t˾��������%s    ˾���ƶ��绰��%s",ptruck->driver,ptruck->phone);
        line_count+=2;
        GotoXY(0,line_count);
        printf("\t�̶�����·�߱��:%s    �̶�����·������:%s",proad->road,proad->road_name);
        line_count++;
        printf("\n\t�̶�����·����վ����:%d    �̶�����·���ܹ�����:%.2f    ȫվ�������ܺ�ʱ:%.2f�����ӣ�",proad->full_station,proad->full_distance,proad->full_time);
        line_count+=2;
        printf("\n\n\t����������:%s\t\t  �����˰칫�ҵ绰:%s",proad->charge_person,proad->call);
        line_count++;
        printf("\n\t�������ƶ��绰:%s\t  �����˵�������:%s",proad->phone,proad->email);

        line_count+=2;
        printf("\n\n\t·�߾�ͣվ�㣺");
        i = 0;
        line_count++;
        printf("\n\t");
        while(pstation->next)
        {
            i++;
            if(i%8 == 0)
            {
                printf("\n\t");
                line_count++;
            }
            printf("%s -> ",pstation->station_name);
            pstation = pstation->next;
        }
        printf("%s\n",pstation->station_name);
        line_count++;

        //�ͻ��嵥
        line_count++;
        pos.X = 5;
        pos.Y = line_count;
        //���Ʒָ�
        for(i=0;i<90;i++,pos.X++)
            WriteConsoleOutputCharacter(gh_std_out,"-",1,pos,&ul);
        printf("\n\n\t\t\t\t\t�ͻ��嵥");
        line_count++;

        pstation = proad->station;
        ptruck = pstation->truck;
        pgoods = ptruck->goods;
        printf("\n\n\t\t\tվ����ţ�%s\tվ�����ƣ�%s\n",pstation->station_id,pstation->station_name);
        line_count+=3;
        printf("\n\t\t��վ�ػ�");
        line_count++;
        printf("\n\t\t������\t��������\t�������֣�");
        line_count++;
        while(pgoods)
        {
            printf("\n\t\t%d\t\t%-16s%.2f",pgoods->number,pgoods->name,pgoods->quantity);
            line_count++;
            pgoods = pgoods->next;
        }
        pstation = pstation->next;
        while(pstation)
        {
            ptruck = pstation->truck;
            pgoods = ptruck->goods;
            printf("\n\n\t\t\tվ����ţ�%s\tվ�����ƣ�%s\n",pstation->station_id,pstation->station_name);
            printf("\n\t\t��վж��");
            printf("\n\t\t������\t��������\t�������֣�");
            line_count+=5;
            while(pgoods)
            {
                printf("\n\t\t%d\t\t%-16s%.2f",pgoods->number,pgoods->name,pgoods->quantity);
                line_count++;
                pgoods = pgoods->next;
            }
            pstation = pstation->next;
        }

        //���߾�
        line_count+=3;

        Rc.Bottom = line_count;
        //���Ʊ߿�
        DrawBox(&Rc);
        line_count++;
        GotoXY(85,line_count);
        printf("��%dҳ����%dҳ",page_count,page);

        line_count+=5;

        proad = proad->next;
    }
    //����������Ļ������ʹ��պú���
    size.Y = line_count+4;
    SetConsoleScreenBufferSize(gh_std_out, size);

    printf("\n\n\n\t\t�밴������˳�...");
    getch();
    ReFresh();
    size.X = SCR_COL;
    size.Y = SCR_ROW;
    SetConsoleScreenBufferSize(gh_std_out, size); /*���ô��ڻ�������С100*30*/



    return bRet;
}


BOOL HelpTopic(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"����",
                           "��������ɼ��̻������������̿����������Ҽ����ո񣬻س�������",
                           "һЩ��ݼ���",
                           "F1  ��ʾ��������    Alt+X  �˳�ϵͳ",
                           "Alt+�˵��ϵ���ĸ�ɿ���ѡ��˵�",
                           "������վ�㰴ťΪվ������ĸ��ģ�·�߰�ť�ͳ�����ť���Ƕ�·����Ϣ�ı༭��",
                           "",
                           "Attention: ��������ʱ��ע�⽫����̨�����е� ����ѡ�� �رգ�",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 9);

    return bRet;
}

BOOL About(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"����",
                           "�������ƣ��������͹�����Ϣϵͳ",
                           "��������CodeBlocks",
                           "��������������1601����������",
                           "ѧ�ţ�U201614907",
                           "Vision: 1.0",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 7);

    return bRet;
}

BOOL NewStation(void)
{
    BOOL bRet = TRUE;
    STATION_CODE *tail;
    char new_station[50];
    char* pCh = "�Ƿ񱣴����ݣ�";
    int sHot = 1;

    GotoXY(40,3);
    printf("¼��վ����Ϣ\n");
    printf("\t\tĿǰ��վ����Ϊ��%lu\n\n",gul_station_count);
    printf("\t\t��վ����Ϊ��%lu(�Զ�����)\n",gul_station_count+1);
    printf("\t\t��������վ�����ƣ�25�����ڣ�:\n\t\t");

    Show_Cursor(TRUE);
    scanf("%s",new_station);
    Show_Cursor(FALSE);

    tail = gp_station_code;

    if (PopPrompt(&pCh,&sHot) == 13 && sHot == 1)
    {
        while(tail->next) tail = tail->next;
        tail->next = (STATION_CODE*)malloc(sizeof(STATION_CODE));
        tail = tail->next;
        tail->station_num= ++gul_station_count;
        strcpy(tail->station_name,new_station);
        tail->next=NULL;

        bRet = SaveStation();
    }

    PopOff();
    ReFresh();

    return bRet;
}



BOOL LookStation(void)
{
    BOOL bRet = TRUE;
    char *plabel_name = "�鿴��¼���վ��";
    STATION_CODE *tail;
    int i,  page, sTag=1, sRet, count=1, flag = 1;
    const int Col = 4, Row=4;

    page = gul_station_count/PAGE_LINE + 1;
    tail = gp_station_code;
    GotoXY(Col,Row-1);           //�ƶ����
    printf("���\tվ������");   //��ͷ
    if(page==1)   //��һҳ
    {
        for(i=0;tail;tail = tail->next,i++)
        {
            GotoXY(Col,Row+i);
            printf("%d\t\t%s",tail->station_num,tail->station_name);
        }
        GotoXY(80,1);
        printf("�� %d ҳ���� %d ҳ",count,page);
        PopOff();
        sRet = PopTextBox(&plabel_name, flag, &sTag);
        PopOff();
        ReFresh();
    }
    /**
     * \brief ��ҳ����ʵ�֣�
     *
     */

    //��ҳ
    else
    {
        flag = 2;   //��һҳ���
        for(i=0;tail&&i<23;tail = tail->next,i++)
        {      //�ȴ�ӡ
            GotoXY(Col,Row+i);
            printf("%d\t\t%s",tail->station_num,tail->station_name);
        }
        GotoXY(80,1);
        printf("�� %d ҳ���� %d ҳ",count,page);
        sRet = PopTextBox(&plabel_name, flag , &sTag);
        count = 1;   //�ڼ�ҳ
        while(TRUE)
        {
            if(sRet == 13 && sTag ==2 && flag ==2)  //2����һҳ
            {
                count++;
                if(count == page) flag = 4;
                else flag = 3;
            }
            else if(sRet == 13 && sTag ==2 && flag ==3)  //3, ��һҳ
            {
                count++;
                if(count == page) flag = 4;
                else flag = 3;
            }
            else if(sRet == 13 && sTag ==3 && flag ==3) //3,��һҳ
            {
                count--;
                if(count == 1) flag = 2;
                else flag = 3;
            }
            else if(sRet == 13 && sTag ==2 && flag ==4)//4,��һҳ
            {
                count--;
                if(count == 1) flag = 2;
                else flag = 3;
            }
            else
            {
                break;
            }
            PopOff();
            ReFresh();
            GotoXY(Col,Row-1);           //�ƶ����
            printf("���\tվ������");   //��ͷ
            //for(tail = gp_station_code; (count-1)*23+1 == tail->station_num; tail= tail->next);
            tail = gp_station_code;
            while(TRUE)    //����
            {
                if((count-1)*23+1 == tail->station_num) break;
                tail= tail->next;
            }
            for(i=0; tail&&i<23; tail = tail->next,i++)
                {
                    GotoXY(Col,Row+i);
                    printf("%d\t\t%s",tail->station_num,tail->station_name);
                }
            if(sTag == 3) sTag = 2;     //stag�Ĵ���
            GotoXY(80,1);
            printf("�� %d ҳ���� %d ҳ",count,page);
            sRet = PopTextBox(&plabel_name, flag , &sTag);
        }
        PopOff();
        ReFresh();
    }


    return bRet;
}

BOOL EditStation(void)
{
    BOOL bRet = FALSE;
    STATION_CODE *tail;
    char new_station[50];
    char* pCh = "�Ƿ񱣴����ݣ�";
    int sHot = 1, find;
    char key;

    loop:
    GotoXY(40,3);
    printf("�༭վ����Ϣ\n");
    printf("\t\t������Ҫ���ĵ�վ���ţ�");
    Show_Cursor(TRUE);
    scanf("%d",&find);
    Show_Cursor(FALSE);

    tail = gp_station_code;
    while(tail->station_num != find )
    {
        tail = tail->next;
        if(tail == NULL)
        {
            printf("\tδ���ҵ��ñ�ţ������³��ԣ�");
            getch();
            ReFresh();
            goto loop;
        }
    }
    printf("\t\t��վ����ϢΪ��\n");
    printf("\t\t��ţ�%d\tվ�����ƣ�%s",tail->station_num,tail->station_name);
    printf("\n\t\t�Ƿ���ģ� ȷ���밴Y��ȡ���밴�����\n");
    //getchar();
    key = getch();

    if (key == 'y' || key == 'Y')
    {
        printf("\t\t������վ�����ƣ�");
        Show_Cursor(TRUE);
        scanf("%s",new_station);
        Show_Cursor(FALSE);
        if (PopPrompt(&pCh,&sHot) == 13 && sHot == 1)
        {
            strcpy(tail->station_name,new_station);
            bRet = SaveStation();
        }
        PopOff();
    }
    printf("�밴�������������");
    getch();
    ReFresh();
    return bRet;
}

BOOL DeleteStation(void)
{
    BOOL bRet = TRUE;
    int find;
    char key;
    STATION_CODE *tail, *uper;

    loop1:
    GotoXY(40,3);
    printf("ɾ��վ����Ϣ\n");
    printf("\t\t������Ҫɾ����վ���ţ�");
    Show_Cursor(TRUE);
    scanf("%d",&find);
    Show_Cursor(FALSE);
    tail = gp_station_code;

    while(tail->station_num != find )
    {
        uper = tail;
        tail = tail->next;
        if(tail == NULL)
        {
            printf("\tδ���ҵ��ñ�ţ������³��ԣ�");
            getch();
            ReFresh();
            goto loop1;
        }
    }
    printf("\t\t��վ����ϢΪ��\n");
    printf("\t\t��ţ�%d\tվ�����ƣ�%s",tail->station_num,tail->station_name);
    printf("\n\t\t�Ƿ�ɾ���� ȷ���밴Y��ȡ���밴�����\n");
    key = getch();

    if (key == 'y' || key == 'Y')
    {
        uper->next = tail->next;
        free(tail);
        tail = uper->next;
        while(tail)
        {
            tail->station_num--;
            tail = tail->next;
        }
        gul_station_count--;
        bRet = SaveStation();
        if(bRet) printf("\t\tɾ���ɹ�������");
        printf("\n\n\t\t���������������");
        getch();
    }
    ReFresh();

    return bRet;
}

BOOL NewRoad(void)
{
    BOOL bRet = TRUE;
    ROAD_DATA *proad;
    STATION_DATA *psta, *pista, *pfsta, *prun;
    TRUCK_DATA *ptruck;
    GOODS_DATA *pgoods, *pgoods_find;
    STATION_CODE *tail;
    int find, station_count=0, sHot=1, goods_count, goods_find;
    char key;
    char init[50],fin[50], roadnum[6], stationnum[10];
    char *plusname="����";
    char *plussta="��վ";
    float fdistance, ftime=0, fvolume, fvolume_up;
    char* pCh = "�Ƿ񱣴����ݣ�";


    GotoXY(40,3);
    printf("¼��·����Ϣ\n");

    proad = (ROAD_DATA*)malloc(sizeof(ROAD_DATA));
    proad->station = NULL;
    proad->next = NULL;

    printf("\t\t��ǰ·��������%lu\n",gul_road_count);
    gul_road_count++;
    itoa(gul_road_count,roadnum,10);  //����ת��Ϊ�ַ���
    strcat(roadnum,plusname);  //�ַ�������

    printf("\n\t\t��ǰ�̶�����·�߱�ţ��Զ����ɣ���%s\n", roadnum);
    strcpy(proad->road,roadnum);

    printf("\n\t\t������̶�����·�����ƣ�\t\t�磺��ɽ��\n\t\t");
    Show_Cursor(TRUE);   //��ʾ���
    scanf("%s",proad->road_name);

    loop2:
    printf("\n\t\t��������ʼվ���ţ�");
    scanf("%d",&find);

    tail = gp_station_code;

    while(tail->station_num != find )
    {
        tail = tail->next;
        if(tail == NULL)
        {
            printf("\n\tδ���ҵ��ñ�ţ������³��ԣ�");
            getch();
            goto loop2;
        }
    }
    printf("\n\t\t��վ����ϢΪ��\n");
    printf("\t\t��ţ�%d\tվ�����ƣ�%s",tail->station_num,tail->station_name);
    printf("\n\t\t\tȷ���밴�������ȡ���밴N");
    key = getch();
    if(key == 'N' || key == 'n')
    {
        goto loop2;
    }
    proad->init_station = tail->station_num;       //��ʼվ����Ҳ���
    pista = (STATION_DATA*)malloc(sizeof(STATION_DATA));
    pista->next = NULL;
    pista->station_num = tail->station_num;
    strcpy(init,tail->station_name);
    strcpy(pista->station_name,tail->station_name);

    loop3:
    printf("\n\t\t�������յ�վ���ţ�");
    scanf("%d",&find);

    tail = gp_station_code;

    while(tail->station_num != find )
    {
        tail = tail->next;
        if(tail == NULL)
        {
            printf("\n\tδ���ҵ��ñ�ţ������³��ԣ�");
            getch();
            goto loop2;
        }
    }
    Show_Cursor(FALSE);  //���ع��
    printf("\t\t��վ����ϢΪ��\n");
    printf("\t\t��ţ�%d\tվ�����ƣ�%s",tail->station_num,tail->station_name);
    Show_Cursor(FALSE);  //���ع��
    printf("\n\t\t\tȷ���밴�������ȡ���밴N");
    key = getch();
    if(key == 'N' || key == 'n')
    {
        goto loop3;
    }
    proad->fin_station = tail->station_num;         //��ֹվ�� ����
    pfsta = (STATION_DATA*)malloc(sizeof(STATION_DATA));
    pfsta->station_num = tail->station_num;
    strcpy(fin,tail->station_name);
    strcpy(pfsta->station_name,tail->station_name);


    ReFresh(); //����һҳ����
    GotoXY(40,3);
    printf("¼��·����Ϣ\n");
    Show_Cursor(TRUE);

    printf("\n\t\t�����븺����������");
    scanf("%s",proad->charge_person);
    printf("\n\t\t�����븺���˰칫�ҵ绰 ���̶��绰����");
    scanf("%s",proad->call);
    printf("\n\t\t�����븺�����ƶ��绰��");
    scanf("%s",proad->phone);
    printf("\n\t\t�����븺���˵������䣺");
    scanf("%s",proad->email);
    Show_Cursor(FALSE);  //���ع��
    printf("\n\n\n\t\t�밴�������������ʼ¼�뾭ͣվ����Ϣ");
    key = getch();


    //��ʼվվ����Ϣ¼��
    ReFresh(); //����һҳ����
    GotoXY(40,3);
    printf("¼��·����Ϣ\n");
    Show_Cursor(TRUE);

    proad->station = pista;

    printf("\n\t\t\t��ʼվ����Ϣ¼��\n");
    station_count++;
    itoa(station_count,stationnum,10);   //վ���������
    strcat(stationnum,plussta);
    strcpy(pista->station_id,stationnum);
    printf("\n\t\t��ǰվ����ţ�%s",pista->station_id);
    printf("\n\t\t��ʼվ���ţ�%d",pista->station_num);
    printf("\n\t\tվ�����ƣ�%s",pista->station_name);
    printf("\n\t\t�������ڴ�ͣ����ʱ�����ӣ���");
    scanf("%f",&pista->stay_time);
    Show_Cursor(FALSE);  //���ع��
    printf("\n\t\t��վ���Ƿ��н���̶�·�߱�ţ������밴Y��û�������������");
    key = getch();
    if(key == 'y' || key == 'Y')
    {
        Show_Cursor(TRUE);
        printf("\n\t\t�������ڴ�վ��Ľ���̶�·�߱�ţ�");
        scanf("%s",pista->across_num);
    }
    else
    {
        pista->across_num[0] ='\0';
    }
    strcpy(pista->road, roadnum);
    pista->distance_init = 0;
    pista->distance_up = 0;
    pista->using_time = 0;
    pista->next = NULL;
    Show_Cursor(FALSE);  //���ع��
    printf("\n\n\t\t�밴��������복����Ϣ������");
    key = getch();

    //������Ϣ¼��
    ReFresh(); //����һҳ����
    GotoXY(40,3);
    printf("\n\n\t\t¼�복����Ϣ\n");
    Show_Cursor(TRUE);

    ptruck = (TRUCK_DATA*)malloc(sizeof(TRUCK_DATA));
    pista->truck = ptruck;
    //ptruck->station_num = pista->station_num;
    strcpy(ptruck->station_id,pista->station_id);
    strcpy(ptruck->road,roadnum);

    printf("\n\t\t�����복�����գ�");
    scanf("%s",ptruck->number);
    printf("\n\t\t������˾��������");
    scanf("%s",ptruck->driver);
    printf("\n\t\t������˾���ƶ��绰��");
    scanf("%s",ptruck->phone);
    printf("\n\t\t������ó����������֣���");
    scanf("%f",&ptruck->volume);

    Show_Cursor(FALSE);  //���ع��
    printf("\n\n\t\t�밴����������ػ��嵥������");
    key = getch();

    //�ػ���Ϣ¼��
    ReFresh(); //����һҳ����
    GotoXY(40,3);
    printf("¼��·����Ϣ\n");
    Show_Cursor(TRUE);

    //��ͷ
    fvolume =0;
    printf("\n\t\t\t��ʼվ�ػ���Ϣ¼�룺\n");
    pgoods = (GOODS_DATA*)malloc(sizeof(GOODS_DATA));
    ptruck->goods = pgoods;
    printf("\n\t\t�밴��ʽ �������� �������֣� ���룡\n\n");
    printf("\t\t");
    Show_Cursor(TRUE);
    scanf("%s%f",pgoods->name,&pgoods->quantity);
    fvolume += pgoods->quantity;
    goods_count = 1;
    pgoods->number = goods_count++;
    //pgoods->station_num = ptruck->station_num;
    strcpy(ptruck->station_id,pista->station_id);
    strcpy(pgoods->station_id,pista->station_id);
    strcpy(pgoods->road, pista->road);  //��ȫ·����Ϣ
    Show_Cursor(FALSE);  //���ع��
    printf("\t\t��ǰ�����ţ�%d  �밴���������������밴N\n",pgoods->number);
    key = getch();

    while(key != 'n' && key != 'N')
    {
        Show_Cursor(TRUE);
        pgoods->next = (GOODS_DATA*)malloc(sizeof(GOODS_DATA));
        pgoods = pgoods->next;
        printf("\t\t");
        scanf("%s%f",pgoods->name,&pgoods->quantity);
        pgoods->number = goods_count++;
        fvolume += pgoods->quantity;
        //pgoods->station_num = ptruck->station_num;  //��ȫ·����Ϣ
        strcpy(pgoods->road, pista->road);
        strcpy(pgoods->station_id,pista->station_id);
        Show_Cursor(FALSE);  //���ع��
        printf("\t\t��ǰ�����ţ�%d  �밴���������������밴N\n",pgoods->number);
        key = getch();
        //if(key == 'n' || key == 'N') break;
    }
    pgoods->next = NULL;
    ptruck->left_volume = ptruck->volume - fvolume;
    fvolume_up = ptruck->volume - fvolume;

    psta=pista;

    printf("\n\t\t��������������һ��վ����Ϣ�������밴N");
    key = getch();

    while(key != 'n' && key != 'N')
    {
        psta->next = (STATION_DATA*)malloc(sizeof(STATION_DATA));
        psta=psta->next;
        psta->next = NULL;
        //��վ����Ϣ¼��
        ReFresh(); //����һҳ����
        GotoXY(40,3);
        printf("¼��·����Ϣ\n");
        Show_Cursor(TRUE);

        printf("\n\t\t\t��ͣվ����Ϣ¼��\n");
        station_count++;
        itoa(station_count,stationnum,10);   //վ���������
        strcat(stationnum,plussta);
        strcpy(psta->station_id,stationnum);
        strcpy(psta->road, roadnum);
        printf("\n\t\t��ǰվ����ţ�%s",psta->station_id);

        loop4:
        printf("\n\t\t������վ���ţ�");
        scanf("%d",&find);
        tail = gp_station_code;

        while(tail->station_num != find )
        {
            tail = tail->next;
            if(tail == NULL)
            {
                printf("\n\tδ���ҵ��ñ�ţ������³��ԣ�");
                getch();
                goto loop4;
            }
        }
        printf("\n\t\t��վ����ϢΪ��\n");
        printf("\t\t��ţ�%d\tվ�����ƣ�%s",tail->station_num,tail->station_name);
        printf("\n\t\t\tȷ���밴�������ȡ���밴N");
        key = getch();
        if(key == 'N' || key == 'n')
        {
            goto loop4;
        }
        strcpy(psta->road, roadnum);
        psta->station_num = find;
        strcpy(psta->station_name,tail->station_name);
        printf("\n\t\t����������һ��վ����루km����");
        scanf("%f",&psta->distance_up);
        //��������ʼվ�����
        prun = pista;
        fdistance = 0;
        while(prun != NULL)
        {
            fdistance+=prun->distance_up;
            prun=prun->next;
        }
        printf("\n\t\t����ʼվ����루km�����Զ����ɣ���%.2f",fdistance);
        psta->distance_init = fdistance;
        printf("\n\t\t������������һ��վ�㽻ͨ��ʱ��min����");
        scanf("%f",&psta->using_time);
        printf("\n\t\t�������ڴ�ͣ����ʱ�����ӣ���");
        scanf("%f",&psta->stay_time);
        Show_Cursor(FALSE);  //���ع��
        printf("\n\t\t��վ���Ƿ��н���̶�·�߱�ţ������밴Y��û�������������");
        key = getch();
        if(key == 'y' || key == 'Y')
        {
            Show_Cursor(TRUE);
            printf("\n\t\t�������ڴ�վ��Ľ���̶�·�߱�ţ�");
            scanf("%s",psta->across_num);
        }
        else
        {
            psta->across_num[0] ='\0';
        }
        strcpy(psta->road, proad->road);

        ptruck = (TRUCK_DATA*)malloc(sizeof(TRUCK_DATA));
        psta->truck = ptruck;
        strcpy(ptruck->road,roadnum);
        strcpy(ptruck->station_id,stationnum);
        printf("\n\n\t\t�밴���������ж���嵥������");
        key = getch();

        //ж����Ϣ¼��
        ReFresh(); //����һҳ����
        GotoXY(40,3);
        printf("¼��·����Ϣ\n");
        Show_Cursor(TRUE);

        //��ͷ
        fvolume = 0;
        printf("\n\t\t\t%sվж������Ϣ¼�룺\n",psta->station_name);
        pgoods = (GOODS_DATA*)malloc(sizeof(GOODS_DATA));
        ptruck->goods = pgoods;
        printf("\n\t\t��������ţ�");
        Show_Cursor(TRUE);
        scanf("%d",&goods_find);
        if(goods_find<=goods_count)
        {
            pgoods_find = pista->truck->goods;
            while(TRUE)
            {
                if(goods_find == pgoods_find->number) break;
                pgoods_find = pgoods_find->next;
                if(pgoods_find == NULL)
                {
                    printf("\t\t��������������\n");
                    scanf("%d",&goods_find);
                    pgoods_find = proad->station->truck->goods;
                }
            }
            Show_Cursor(FALSE);  //���ع��
            printf("\n\t\t�������ƣ�%s\t������ж���������֣���",pgoods_find->name);
            Show_Cursor(TRUE);
            scanf("%f",&pgoods->quantity);
            fvolume += pgoods->quantity;
            pgoods->number = goods_find;
            strcpy(pgoods->name ,pgoods_find->name);
            //pgoods->station_num = ptruck->station_num;  //��ȫ·����Ϣ
            strcpy(ptruck->station_id,psta->station_id);
            strcpy(pgoods->station_id,psta->station_id);
            strcpy(pgoods->road, psta->road);
            printf("\t\t�밴���������������밴N\n");
            key = getch();
        }
        else printf("����");    //�Ҳ���
        //�ڶ�����ʼ
        while(key != 'n' && key != 'N')
        {
            Show_Cursor(TRUE);
            pgoods->next = (GOODS_DATA*)malloc(sizeof(GOODS_DATA));
            pgoods = pgoods->next;
            printf("\n\t\t��������ţ�");
            Show_Cursor(TRUE);
            scanf("%d",&goods_find);
            if(goods_find<=goods_count)
            {
                pgoods_find = pista->truck->goods;
                while(TRUE)
                {
                    if(goods_find == pgoods_find->number) break;
                    pgoods_find = pgoods_find->next;
                    if(pgoods_find == NULL)
                    {
                        printf("\t\t��������������\n");
                        scanf("%d",&goods_find);
                        pgoods_find = proad->station->truck->goods;
                    }
                }
                Show_Cursor(FALSE);  //���ع��
                printf("\n\t\t�������ƣ�%s\t������ж���������֣���",pgoods_find->name);
                Show_Cursor(TRUE);
                scanf("%f",&pgoods->quantity);
                fvolume += pgoods->quantity;
                pgoods->number = goods_find;
                strcpy(pgoods->name ,pgoods_find->name);
                //pgoods->station_num = ptruck->station_num;  //��ȫ·����Ϣ
                strcpy(ptruck->station_id,psta->station_id);
                strcpy(pgoods->station_id,psta->station_id);
                strcpy(pgoods->road, psta->road);
                Show_Cursor(FALSE);  //���ع��
                printf("\t\t�밴���������������밴N\n");
                key = getch();
                //if(key == 'n' || key == 'N') break;
            }
            else printf("����");
        }
        pgoods->next = NULL;
        ptruck->volume = proad->station->truck->volume;
        ptruck->left_volume = fvolume_up + fvolume;
        fvolume_up = ptruck->left_volume;
        Show_Cursor(FALSE);  //���ع��
        printf("\n\t\t�����������¼����һվ�㣬¼���յ�վ�밴N\n");
        key = getch();
    }

    /*       �յ�վ�����嵥 */

    psta->next = pfsta;
    psta=psta->next;
    psta->next = NULL;
    //�յ�վ��Ϣ¼��
    ReFresh(); //����һҳ����
    GotoXY(40,3);
    printf("¼��·����Ϣ\n");
    Show_Cursor(TRUE);

    printf("\n\t\t\t��ֹվ����Ϣ¼��\n");
    station_count++;
    itoa(station_count,stationnum,10);   //վ���������
    strcat(stationnum,plussta);
    strcpy(psta->station_id,stationnum);
    strcpy(psta->road, roadnum);
    psta->next=NULL;
    printf("\n\t\t��ǰվ����ţ�%s",psta->station_id);
    printf("\n\t\t��ʼվ���ţ�%d",psta->station_num);
    printf("\n\t\tվ�����ƣ�%s",psta->station_name);
    printf("\n\t\t����������һ��վ����루km����");
    scanf("%f",&psta->distance_up);
    //��������ʼվ�����
    prun = pista;
    fdistance = 0;
    while(prun)
    {
        fdistance+=prun->distance_up;
        prun=prun->next;
    }
    printf("\n\t\t����ʼվ����루km�����Զ����ɣ���%.2f",fdistance);
    psta->distance_init = fdistance;
    proad->full_distance = fdistance;
    printf("\n\t\t������������һ��վ�㽻ͨ��ʱ��min����");
    scanf("%f",&psta->using_time);
    printf("\n\t\t�������ڴ�ͣ����ʱ�����ӣ���");
    Show_Cursor(TRUE);
    scanf("%f",&psta->stay_time);
    Show_Cursor(FALSE);  //���ع��
    printf("\n\t\t��վ���Ƿ��н���̶�·�߱�ţ������밴Y��û�������������");
    key = getch();
    if(key == 'y' || key == 'Y')
    {
        Show_Cursor(TRUE);
        printf("\n\t\t�������ڴ�վ��Ľ���̶�·�߱�ţ�");
        scanf("%s",psta->across_num);
        Show_Cursor(FALSE);  //���ع��
    }
    else
    {
        psta->across_num[0] ='\0';
    }
    strcpy(psta->road, proad->road);

    ptruck = (TRUCK_DATA*)malloc(sizeof(TRUCK_DATA));
    psta->truck = ptruck;
    strcpy(ptruck->road,roadnum);
    strcpy(ptruck->station_id,stationnum);
    printf("\n\n\t\t�밴���������ж���嵥������");
    key = getch();

    //ж����Ϣ¼��
    ReFresh(); //����һҳ����
    GotoXY(40,3);
    printf("¼��·����Ϣ\n");
    Show_Cursor(TRUE);


    //��ͷ���յ�վ
    fvolume = 0;
    printf("\n\t\t\t%sվж������Ϣ¼�룺\n",psta->station_name);
    pgoods = (GOODS_DATA*)malloc(sizeof(GOODS_DATA));
    ptruck->goods = pgoods;
    printf("\n\t\t��������ţ�");
    Show_Cursor(TRUE);
    scanf("%d",&goods_find);
    if(goods_find<=goods_count)
    {
        pgoods_find = pista->truck->goods;
        while(TRUE)
        {
            if(goods_find == pgoods_find->number) break;
            pgoods_find = pgoods_find->next;
            if(pgoods_find == NULL)
            {
                printf("\t\t��������������\n");
                scanf("%d",&goods_find);
                pgoods_find = proad->station->truck->goods;
            }
        }
        Show_Cursor(FALSE);  //���ع��
        printf("\n\t\t�������ƣ�%s\t������ж���������֣���",pgoods_find->name);
        Show_Cursor(TRUE);
        scanf("%f",&pgoods->quantity);
        fvolume += pgoods->quantity;
        Show_Cursor(FALSE);  //���ع��
        pgoods->number = goods_find;
        strcpy(pgoods->name ,pgoods_find->name);
        //pgoods->station_num = ptruck->station_num;  //��ȫ·����Ϣ
        strcpy(ptruck->station_id,psta->station_id);
        strcpy(pgoods->station_id,psta->station_id);
        strcpy(pgoods->road, psta->road);
        printf("\t\t�밴���������������밴N\n");
        key = getch();
    }
    else printf("����");    //�Ҳ���
    //�ڶ�����ʼ

    while(key != 'n' && key != 'N')
    {
        Show_Cursor(TRUE);
        pgoods->next = (GOODS_DATA*)malloc(sizeof(GOODS_DATA));
        pgoods = pgoods->next;
        printf("\n\t\t��������ţ�");
        scanf("%d",&goods_find);
        if(goods_find<=goods_count)
        {
            pgoods_find = pista->truck->goods;
            while(TRUE)
            {
                if(goods_find == pgoods_find->number) break;
                pgoods_find = pgoods_find->next;
                if(pgoods_find == NULL)
                {
                    printf("\t\t��������������\n");
                    scanf("%d",&goods_find);
                    pgoods_find = proad->station->truck->goods;
                }
            }
            Show_Cursor(FALSE);  //���ع��
            printf("\n\t\t�������ƣ�%s\t������ж���������֣���",pgoods_find->name);
            Show_Cursor(TRUE);
            scanf("%f",&pgoods->quantity);
            fvolume += pgoods->quantity;
            Show_Cursor(FALSE);  //���ع��
            pgoods->number = goods_find;
            strcpy(pgoods->name ,pgoods_find->name);
            //pgoods->station_num = ptruck->station_num;  //��ȫ·����Ϣ
            strcpy(ptruck->station_id,psta->station_id);
            strcpy(pgoods->station_id,psta->station_id);
            strcpy(pgoods->road, psta->road);
            printf("\t\t�밴���������������밴N\n");
            key = getch();
            //if(key == 'n' || key == 'N') break;
        }
        else printf("����");
    }
    pgoods->next = NULL;
    ptruck->volume = proad->station->truck->volume;
    ptruck->left_volume = fvolume_up + fvolume;

    Show_Cursor(FALSE);
    printf("\n\t\t·����Ϣ¼����ɣ������������");
    getch();
    ReFresh();


    //������Ϣ
    ReFresh(); //����һҳ����
    GotoXY(40,3);
    printf("¼��·����Ϣ\n");

    printf("\n\t\t\t·����Ϣһ��\n\n\t");
    psta = pista;
    while(psta)
    {
        printf("%s  ",psta->station_name);
        ftime = psta->using_time + psta->stay_time + ftime;
        psta=psta->next;
    }
    printf("\n\n\t\t·��ȫվ�������ܺ�ʱ��min����%.2f",ftime);
    printf("\n\n\t\t·����վ������%d",station_count);
    proad->full_time = ftime;
    proad->full_station = (short)station_count;


    Show_Cursor(FALSE);
    printf("\n\n\t\t�����������");
    getch();
    ReFresh();

    //��������
    if (PopPrompt(&pCh,&sHot) == 13 && sHot == 1)
    {
        //�������
        if(gp_head != NULL)
        {
            proad->next = gp_head;
        }
        gp_head = proad;
        bRet = SaveRoad();
        SeceletSort(&gp_head);  //��������
    }
    else
    {
        //��������棬�ͷſռ�
        free(proad);
        free(psta);
        free(pgoods);
        free(pista);
        free(pfsta);
        free(prun);
        free(ptruck);
    }
    PopOff();
    ReFresh();

    return bRet;
}

BOOL LookRoad(void)
{
    BOOL bRet = TRUE;
    char *plabel_name = "�鿴��¼���·��";
    ROAD_DATA *proad;
    STATION_DATA *pstation, *phstation;
    TRUCK_DATA *ptruck;
    GOODS_DATA *pgoods;
    int   page, sTag=2, sRet, count=1, flag = 1, station_num, i;
    char fname[6], key;

    GotoXY(20,5);
    printf("��ǰ����·�ߣ�");
    proad = gp_head;
    printf("\n\t\t");
    if(gp_head == NULL)
    {
        printf("��ǰû��·��¼�룬��ǰȥ¼��·�ߣ�");
        getch();
        ReFresh();
        return FALSE;
    }
    while(proad)
    {
        printf("\n\t\t%s--%s  ",proad->road,proad->road_name);
        proad=proad->next;
    }
    loop5:
    printf("\n\n\t\t������Ҫ�鿴��·��(��1����)��");
    Show_Cursor(TRUE);
    scanf("%s",fname);
    Show_Cursor(FALSE);
    proad = gp_head;
    while(strcmp(fname,proad->road) != 0)
    {
        proad=proad->next;
        if(proad == NULL)
        {
            printf("\n\n\t\tû���ҵ���·�ߣ����������룡��E�˳�");
            key = getch();
            if(key == 'e' || key == 'E')
            {
                ReFresh();
                return FALSE;
            }
            goto loop5;
        }
    }
    printf("\n\n\t\t���ҵ�����·���밴�����������");
    getch();
    ReFresh();

    pstation = proad->station;
    phstation = pstation;
    ptruck = phstation->truck;
    page = 2 + proad->full_station;


    GotoXY(40,3);
    printf("·�߻�����Ϣ");
    printf("\n\n\t\t�̶�����·�߱��:%s",proad->road);
    printf("\n\n\t\t�̶�����·������:%s",proad->road_name);
    printf("\n\n\t\t�̶�����·����վ����:%hd",proad->full_station);
    printf("\n\n\t\t�̶�����·���ܹ�����:%.2f",proad->full_distance);
    printf("\n\n\t\tȫվ�������ܺ�ʱ:%.2f�����ӣ�",proad->full_time);
    printf("\n\n\t\t��ʼվ����: %d",proad->init_station);
    printf("\n\n\t\t��ֹվ����: %d",proad->fin_station);
    printf("\n\n\t\t����������:%s",proad->charge_person);
    printf("\n\n\t\t�����˰칫�ҵ绰:%s",proad->call);
    printf("\n\n\t\t�������ƶ��绰:%s",proad->phone);
    printf("\n\n\t\t�����˵�������:%s",proad->email);

    GotoXY(80,1);
    printf("�� %d ҳ���� %d ҳ",count,page);
    flag = 2; //��һҳ���
    sRet = PopTextBox(&plabel_name, flag, &sTag);
    PopOff();
    ReFresh();

    count = 1;   //�ڼ�ҳ
    while(TRUE)
    {
        if(sRet == 13 && sTag ==2 && flag ==2)  //2����һҳ
        {
            count++;
            if(count == page) flag = 4;
            else flag = 3;
        }
        else if(sRet == 13 && sTag ==2 && flag ==3)  //3, ��һҳ
        {
            count++;
            if(count == page) flag = 4;
            else flag = 3;
        }
        else if(sRet == 13 && sTag ==3 && flag ==3) //3,��һҳ
        {
            count--;
            if(count == 1) flag = 2;
            else flag = 3;
        }
        else if(sRet == 13 && sTag ==2 && flag ==4)//4,��һҳ
        {
            count--;
            if(count == 1) flag = 2;
            else flag = 3;
        }
        else
        {
            break;
        }
        PopOff();
        ReFresh();

        switch (count)
        {
        case 1:
            {
                GotoXY(40,3);
                printf("·�߻�����Ϣ");
                printf("\n\n\t\t�̶�����·�߱��:%s",proad->road);
                printf("\n\n\t\t�̶�����·������:%s",proad->road_name);
                printf("\n\n\t\t�̶�����·����վ����:%hd",proad->full_station);
                printf("\n\n\t\t�̶�����·���ܹ�����:%.2f",proad->full_distance);
                printf("\n\n\t\tȫվ�������ܺ�ʱ:%.2f�����ӣ�",proad->full_time);
                printf("\n\n\t\t��ʼվ����: %d",proad->init_station);
                printf("\n\n\t\t��ֹվ����: %d",proad->fin_station);
                printf("\n\n\t\t����������:%s",proad->charge_person);
                printf("\n\n\t\t�����˰칫�ҵ绰:%s",proad->call);
                printf("\n\n\t\t�������ƶ��绰:%s",proad->phone);
                printf("\n\n\t\t�����˵�������:%s",proad->email);
            }
            break;

        case 2:
            {
                GotoXY(40,3);
                printf("����������Ϣ");
                printf("\n\n\tִ������·�߱��:%s",ptruck->road);
                printf("\n\n\t��������:%s",ptruck->number);
                printf("\n\n\t˾������:%s",ptruck->driver);
                printf("\n\n\t˾���ƶ��绰:%s",ptruck->phone);
                printf("\n\n\t����������:%.2f���֣�",ptruck->volume);
                //printf("\n\n\t\:%s",);
            }
            break;

            //�ػ�ҳ
        case 3:
            {
                pstation = proad->station;
                GotoXY(40,3);
                printf("վ����ϸ��Ϣ");
                printf("\n\n\tվ�����:%s",pstation->station_id);
                printf("\n\tվ����:%d",pstation->station_num);
                printf("\n\tվ������:%s",pstation->station_name);
                printf("\n\t����ʼվ�����:%.2f�����",pstation->distance_init);
                printf("\n\t����һ��վ�����:%.2f�����",pstation->distance_up);
                printf("\n\t����һ��վ�㽻ͨ��ʱ:%.2f�����ӣ�",pstation->using_time);
                printf("\n\tͣ����ʱ:%.2f�����ӣ�",pstation->stay_time);
                if(pstation->across_num[0] != '\0') printf("\n\n\t����̶�·�߱��:%s",pstation->across_num);
                printf("\n\n\t\t��վ�ػ�");
                printf("\n\t\t������\t��������\t����");
                ptruck = pstation->truck;
                pgoods = ptruck->goods;
                while(pgoods)
                {
                    printf("\n\t\t%d\t\t%-16s%.2f",pgoods->number,pgoods->name,pgoods->quantity);
                    pgoods = pgoods->next;
                }
                printf("\n\t\t����������%.2f���֣�,ʣ������:%.2f���֣�",ptruck->volume,ptruck->left_volume);

            }
            break;

            //ж��ҳ
        default:
            {
                station_num = count-2;
                pstation = proad->station;
                i=1;
                while(i<station_num)
                {
                    pstation=pstation->next;
                    i++;
                }
                GotoXY(40,3);
                printf("վ����ϸ��Ϣ");
                printf("\n\n\tվ�����:%s",pstation->station_id);
                printf("\n\tվ����:%d",pstation->station_num);
                printf("\n\tվ������:%s",pstation->station_name);
                printf("\n\t����ʼվ�����:%.2f�����",pstation->distance_init);
                printf("\n\t����һ��վ�����:%.2f�����",pstation->distance_up);
                printf("\n\t����һ��վ�㽻ͨ��ʱ:%.2f�����ӣ�",pstation->using_time);
                printf("\n\tͣ����ʱ:%.2f�����ӣ�",pstation->stay_time);
                if(pstation->across_num[0] != '\0') printf("\n\n\t����̶�·�߱��:%s",pstation->across_num);
                ptruck = pstation->truck;
                pgoods = ptruck->goods;
                printf("\n\n\t\t��վж��");
                printf("\n\t\t������\t��������\t����");
                while(pgoods)
                {
                    printf("\n\t\t%d\t\t%-16s%.2f",pgoods->number,pgoods->name,pgoods->quantity);
                    pgoods = pgoods->next;
                }
                printf("\n\t\t����������%.2f���֣�,ʣ������:%.2f���֣�",ptruck->volume,ptruck->left_volume);

            }
            break;
        }
        if(sTag == 3) sTag = 2; //stag����
        GotoXY(80,1);
        printf("�� %d ҳ���� %d ҳ",count,page);
        sRet = PopTextBox(&plabel_name, flag , &sTag);
    }
    PopOff();
    ReFresh();


    return bRet;
}
BOOL EditRoad(void)
{
    BOOL bRet = TRUE;

    char *plabel_name[] = {"�༭·��",
                           "�༭·�߻�����Ϣ",
                           "�༭վ�������Ϣ",
                           "����·��",
                           "���뾭ͣվ��",
                           "ɾ����ͣվ��",
                           "����"
                          };
    int sTag = 1;
    int sRet;

    sRet = PopWindowMenu(plabel_name, 7, 6, &sTag); //��������

    //ѡ�����
    if (sRet== 13 && sTag == 1)
    {
        PopOff();
        EditRoadBase();
    }
    else if (sRet==13 && sTag ==2)
    {
        PopOff();
        EditStationBase();
    }
    else if (sRet==13 && sTag == 3)
    {
        PopOff();
        InsertRoad();
    }
    else if (sRet==13 && sTag == 4)
    {
        PopOff();
        InsertStation();
    }
    else if (sRet==13 && sTag == 5)
    {
        PopOff();
        DeleteStationBase();
    }
    else
    {
        PopOff();
    }

    return bRet;
}
BOOL DeleteRoad(void)
{
    BOOL bRet = TRUE;
    ROAD_DATA *proad, *proad_up = NULL;
    STATION_DATA *pstation, *pstation_up;
    TRUCK_DATA *ptruck;
    GOODS_DATA *pgoods, *pgoods_up;
    char *pCh = "ȷ��ɾ����·����";
    int iHot = 2;
    int sRet, road_count = 1;
    char *plusname="����";
    char roadnum[6], fname[6], key;

    GotoXY(20,5);
    printf("��ǰ����·�ߣ�");
    proad = gp_head;
    printf("\n\t\t");
    if(gp_head == NULL)
    {
        printf("��ǰû��·��¼�룬��ǰȥ¼��·�ߣ�");
        getch();
        ReFresh();
        return FALSE;
    }
    while(proad)
    {
        printf("\n\t\t%s--%s  ",proad->road,proad->road_name);
        proad=proad->next;
    }

    //����·�����
    loop15:
    printf("\n\n\t\t������Ҫɾ����·��(��1����)��");
    Show_Cursor(TRUE);
    scanf("%s",fname);
    Show_Cursor(FALSE);
    proad = gp_head;
    while(strcmp(fname,proad->road) != 0)
    {
        road_count++;
        proad_up = proad;
        proad=proad->next;
        if(proad == NULL)
        {
            printf("\n\n\t\tû���ҵ���·�ߣ����������룡��E�˳�");
            key = getch();
            if(key == 'e' || key == 'E')
            {
                ReFresh();
                return FALSE;
            }
            goto loop15;
        }
    }
    printf("\n\n\t\t���ҵ�����·���밴������鿴��·��\n");
    getch();
    ReFresh();

    GotoXY(40,3);
    printf("ɾ��·��");
    pstation = proad->station;
    printf("\n\n\t\t��ǰ·�߾�ͣվ��\n\n\t\t");
    while(pstation)
    {
        printf("%s\t",pstation->station_name);
        pstation=pstation->next;
    }

    sRet = PopPrompt(&pCh, &iHot);
    if (sRet== 13 && iHot == 1)
    {
        bRet = TRUE;

        //����ͷ�Ĵ���
        if(proad == gp_head)
        {
            gp_head = proad->next;
            //proad_up = gp_head;
        }
        else
        {
        //������·��
        proad_up->next = proad->next;
        }

        //ɾ����Ϣ,�ͷſռ�
        pstation = proad->station;
        ptruck = pstation->truck;
        pgoods = ptruck->goods;

        while(pstation)
        {
            pstation_up = pstation;
            pstation = pstation->next;

            while(pgoods)
            {
                pgoods_up = pgoods;
                pgoods = pgoods->next;
                free(pgoods_up);
            }
            free(ptruck);
            free(pstation_up);
        }
        free(proad);

        //���ĺ����·����Ϣ
        gul_road_count--;

        if(proad_up != NULL) proad = proad_up->next;
        else proad = gp_head;

        while(proad)
        {
            itoa(road_count,roadnum,10);  //����ת��Ϊ�ַ���
            strcat(roadnum,plusname);  //�ַ�������
            strcpy(proad->road, roadnum);
            pstation = proad->station;
            //����
            while(pstation)
            {
                strcpy(pstation->road,roadnum);
                ptruck = pstation->truck;
                strcpy(ptruck->road,roadnum);
                pgoods = ptruck->goods;
                while(pgoods)
                {
                    strcpy(pgoods->road, roadnum);
                    pgoods = pgoods->next;
                }
                pstation = pstation->next;
            }
            road_count++;
            proad = proad->next;
        }

        SaveRoad();
    }
    else
    {
        bRet = FALSE;
    }
    PopOff();
    ReFresh();

    if(bRet == TRUE) printf("\n\n\t\tɾ���ɹ����밴���������"), getch();
    ReFresh();

    return bRet;
}


BOOL EditTruck(void)
{
    BOOL bRet = TRUE;
    ROAD_DATA *proad;
    STATION_DATA *pstation;
    TRUCK_DATA *ptruck;
    float fvolume;
    int key;
    char fname[6];

    GotoXY(40,3);
    printf("�༭������Ϣ");
    GotoXY(20,5);
    printf("��ǰ����·�ߣ�");
    proad = gp_head;
    printf("\n\t\t");
    if(gp_head == NULL)
    {
        printf("��ǰû��·��¼�룬��ǰȥ¼��·�ߣ�");
        getch();
        ReFresh();
        return FALSE;
    }
    while(proad)
    {
        printf("\n\t\t%s--%s  ",proad->road,proad->road_name);
        proad=proad->next;
    }

    //����·�����
    loop15:
    printf("\n\n\t\t������Ҫ���ĵ�·��(��1����)��");
    Show_Cursor(TRUE);
    scanf("%s",fname);
    Show_Cursor(FALSE);
    proad = gp_head;
    while(strcmp(fname,proad->road) != 0)
    {
        proad=proad->next;
        if(proad == NULL)
        {
            printf("\n\n\t\tû���ҵ���·�ߣ����������룡��E�˳�");
            key = getch();
            if(key == 'e' || key == 'E')
            {
                ReFresh();
                return FALSE;
            }
            goto loop15;
        }
    }
    printf("\n\n\t\t���ҵ�����·���밴������鿴��·��\n");
    getch();
    ReFresh();

    GotoXY(40,3);
    printf("�༭������Ϣ");
    pstation = proad->station;
    ptruck = pstation->truck;

    printf("\n\n\tִ������·�߱��:%s",ptruck->road);
    printf("\n\n\t��ѡ��Ҫ���ĵ���Ϣ��");
    printf("\n\n\t1.��������:%s",ptruck->number);
    printf("\n\t2.˾������:%s",ptruck->driver);
    printf("\n\t3.˾���ƶ��绰:%s",ptruck->phone);
    printf("\n\t4.����������:%.2f",ptruck->volume);
    printf("\n\t5.ȫ�����ģ�");
    printf("\n\n\t���������������");
    printf("\n\n\t�������ţ�");

    Show_Cursor(TRUE);
    scanf("%d",&key);

    ReFresh();
    GotoXY(40,3);
    printf("�༭������Ϣ");

    Show_Cursor(TRUE);
    switch (key)
    {
    case 1:
        printf("\n\n\t��ǰ��������:%s",ptruck->number);
        printf("\n\n\t�������µĳ������գ�");
        scanf("%s",ptruck->number);
        break;

    case 2:
        printf("\n\t��ǰ˾������:%s",ptruck->driver);
        printf("\n\n\t�������µ�˾��������");
        scanf("%s",ptruck->driver);
        break;

    case 3:
        printf("\n\t��ǰ˾���ƶ��绰:%s",ptruck->phone);
        printf("\n\n\t�������µ�˾���ƶ��绰��");
        scanf("%s",ptruck->phone);
        break;

    case 4:
        printf("\n\t��ǰ����������:%.2f",ptruck->volume);
        printf("\n\n\t�������µ���������");
        scanf("%f",&ptruck->volume);
        break;

    case 5:
        printf("\n\n\t��ǰ��������:%s",ptruck->number);
        printf("\n\t�������µĳ������գ�");
        scanf("%s",ptruck->number);
        printf("\n\n\t��ǰ˾������:%s",ptruck->driver);
        printf("\n\t�������µ�˾��������");
        scanf("%s",ptruck->driver);
        printf("\n\n\t��ǰ˾���ƶ��绰:%s",ptruck->phone);
        printf("\n\t�������µ�˾���ƶ��绰��");
        scanf("%s",ptruck->phone);
        printf("\n\n\t��ǰ����������:%.2f���֣�",ptruck->volume);
        printf("\n\t�������µ����������֣���");
        scanf("%f",&ptruck->volume);
        break;

    default:
        break;
    }

    //���ĳ���������
    if(key == 4 || key == 5)
    {
        fvolume = ptruck->volume;
        while(pstation)
        {
            ptruck = pstation->truck;
            ptruck->volume = fvolume;
            ptruck->left_volume += fvolume;
            pstation = pstation->next;
        }
    }
    printf("\n\t\t�밴���������...");
    getch();
    ReFresh();
    SaveRoad();  //��������


    return bRet;
}

BOOL EditRoadBase(void)
{
    BOOL bRet = TRUE;
    ROAD_DATA *proad;
    int key;
    char fname[6];

    GotoXY(40,3);
    printf("�༭·����Ϣ");
    GotoXY(20,5);
    printf("��ǰ����·�ߣ�");
    proad = gp_head;
    printf("\n\t\t");
    if(gp_head == NULL)
    {
        printf("��ǰû��·��¼�룬��ǰȥ¼��·�ߣ�");
        getch();
        ReFresh();
        return FALSE;
    }
    while(proad)
    {
        printf("\n\t\t%s--%s  ",proad->road,proad->road_name);
        proad=proad->next;
    }

    //����·�����
    loop6:
    printf("\n\n\t\t������Ҫ���ĵ�·��(��1����)��");
    Show_Cursor(TRUE);
    scanf("%s",fname);
    Show_Cursor(FALSE);
    proad = gp_head;
    while(strcmp(fname,proad->road) != 0)
    {
        proad=proad->next;
        if(proad == NULL)
        {
            printf("\n\n\t\tû���ҵ���·�ߣ����������룡��E�˳�");
            key = getch();
            if(key == 'e' || key == 'E')
            {
                ReFresh();
                return FALSE;
            }
            goto loop6;
        }
    }
    printf("\n\n\t\t���ҵ�����·���밴�����������");
    getch();
    ReFresh();

    GotoXY(40,3);
    printf("��ѡ��Ҫ�༭��·����Ϣ");
    printf("\n\t\t���ɸ��ĵ���Ŀ��");
    printf("\n\t\t�̶�����·�߱��:%s",proad->road);
    printf("\n\t\t�̶�����·����վ����:%hd",proad->full_station);
    printf("\n\t\t�̶�����·���ܹ�����:%.2f",proad->full_distance);
    printf("\n\t\tȫվ�������ܺ�ʱ:%.2f",proad->full_time);
    printf("\n\t\t��ʼվ����: %d",proad->init_station);
    printf("\n\t\t��ֹվ����: %d",proad->fin_station);
    printf("\n\n\t\t1.�̶�����·������:%s",proad->road_name);
    printf("\n\t\t2.����������:%s",proad->charge_person);
    printf("\n\t\t3.�����˰칫�ҵ绰:%s",proad->call);
    printf("\n\t\t4.�������ƶ��绰:%s",proad->phone);
    printf("\n\t\t5.�����˵�������:%s",proad->email);
    printf("\n\t\t6.������Ϣ���޸ģ�");
    printf("\n\n\t\t������Ҫ�޸���Ϣ�ı��,�����������أ�");
    ShowCursor(TRUE);
    scanf("%d",&key);

    ReFresh();
    GotoXY(40,3);
    printf("�༭·����Ϣ");
    Show_Cursor(TRUE);

    switch (key)
    {
    case 1:
        printf("\n\n\t\t��ǰ�̶�����·������:%s",proad->road_name);
        printf("\n\t\t�������µĹ̶�����·�����ƣ�");
        scanf("%s",proad->road_name);
        break;

    case 2:
        printf("\n\t\t��ǰ����������:%s",proad->charge_person);
        printf("\n\t\t�������µĸ�����������");
        scanf("%s",proad->charge_person);
        break;

    case 3:
        printf("\n\t\t��ǰ�����˰칫�ҵ绰:%s",proad->call);
        printf("\n\t\t�������µĸ����˰칫�ҵ绰��");
        scanf("%s",proad->call);
        break;

    case 4:
        printf("\n\t\t��ǰ�������ƶ��绰:%s",proad->phone);
        printf("\n\t\t�������µĸ������ƶ��绰��");
        scanf("%s",proad->phone);
        break;

    case 5:
        printf("\n\t\t��ǰ�����˵�������:%s",proad->email);
        printf("\n\t\t�������µĸ����˵������䣺");
        scanf("%s",proad->email);
        break;

    case 6:
        printf("\n\n\t\t��ǰ�̶�����·������:%s",proad->road_name);
        printf("\n\t\t�������µĹ̶�����·�����ƣ�");
        scanf("%s",proad->road_name);
        printf("\n\t\t��ǰ����������:%s",proad->charge_person);
        printf("\n\t\t�������µĸ�����������");
        scanf("%s",proad->charge_person);
        printf("\n\t\t��ǰ�����˰칫�ҵ绰:%s",proad->call);
        printf("\n\t\t�������µĸ����˰칫�ҵ绰��");
        scanf("%s",proad->call);
        printf("\n\t\t��ǰ�������ƶ��绰:%s",proad->phone);
        printf("\n\t\t�������µĸ������ƶ��绰��");
        scanf("%s",proad->phone);
        printf("\n\t\t��ǰ�����˵�������:%s",proad->email);
        printf("\n\t\t�������µĸ����˵������䣺");
        scanf("%s",proad->email);
        printf("\n\t\t��ǰ�����˵�������:%s",proad->email);
        printf("\n\t\t�������µĸ����˵������䣺");
        scanf("%s",proad->email);
        break;

    default:
        break;
    }
    ShowCursor(FALSE);
    printf("\n\n\t\t�밴���������...");
    getch();
    ReFresh();
    SaveRoad();  //�������ݵ��ļ�


    return bRet;
}

BOOL EditStationBase(void)
{
    BOOL bRet = TRUE;
    ROAD_DATA *proad;
    STATION_DATA *pstation, *psta;
    STATION_CODE *tail;
    char sfind[10];
    int key, station_num;
    float ftime, fdistance;
    char fname[6];

    GotoXY(40,3);
    printf("�༭վ����Ϣ");
    GotoXY(20,5);
    printf("��ǰ����·�ߣ�");
    proad = gp_head;
    printf("\n\t\t");
    if(gp_head == NULL)
    {
        printf("��ǰû��·��¼�룬��ǰȥ¼��·�ߣ�");
        getch();
        ReFresh();
        return FALSE;
    }
    while(proad)
    {
        printf("\n\t\t%s--%s  ",proad->road,proad->road_name);
        proad=proad->next;
    }

    //����·�����
    loop7:
    printf("\n\n\t\t������Ҫ���ĵ�·��(��1����)��");
    Show_Cursor(TRUE);
    scanf("%s",fname);
    Show_Cursor(FALSE);
    proad = gp_head;
    while(strcmp(fname,proad->road) != 0)
    {
        proad=proad->next;
        if(proad == NULL)
        {
            printf("\n\n\t\tû���ҵ���·�ߣ����������룡��E�˳�");
            key = getch();
            if(key == 'e' || key == 'E')
            {
                ReFresh();
                return FALSE;
            }
            goto loop7;
        }
    }
    printf("\n\n\t\t���ҵ�����·���밴������鿴��·��\n");
    getch();
    ReFresh();

    GotoXY(40,3);
    pstation = proad->station;
    printf("\n\t\tվ�����\tվ������");
    while(pstation)
    {
        printf("\n\t\t%s\t%s",pstation->station_id,pstation->station_name);
        pstation=pstation->next;
    }
    loop8:
    printf("\n\n\t\t��������Ҫ���ĵ�վ�㣨��1��վ����");
    scanf("%s",sfind);
    pstation = proad->station;
    while(pstation)
    {
        if(!strcmp(pstation->station_id,sfind)) break;
        pstation = pstation->next;
        if(pstation == NULL)
        {
            printf("û���ҵ�վ�㣬���������룡");
            goto loop8;
        }
    }

    ReFresh();
    GotoXY(40,3);
    printf("��վ����ϸ��Ϣ");
    printf("\n\n\n\tվ�����:%s",pstation->station_id);
    printf("\n\t1.վ����:%d",pstation->station_num);
    printf("\n\tվ������:%s",pstation->station_name);
    printf("\n\t����ʼվ�����:%.2f�����",pstation->distance_init);
    printf("\n\t2.����һ��վ�����:%.2f�����",pstation->distance_up);
    printf("\n\t3.����һ��վ�㽻ͨ��ʱ:%.2f�����ӣ�",pstation->using_time);
    printf("\n\t4.ͣ����ʱ:%.2f�����ӣ�",pstation->stay_time);
    if(pstation->across_num[0] == '\0') printf("\n\n\t5.����̶�·�߱��:��");
    else printf("\n\n\t5.����̶�·�߱��:%s",pstation->across_num);
    printf("\n\n\t6.��������");

    Show_Cursor(TRUE);
    printf("\n\n\t\t������Ҫ���ĵı�ţ����������˳�...");
    scanf("%d",&key);

    ReFresh();
    GotoXY(40,3);
    Show_Cursor(TRUE);
    switch (key)
    {
    case 1:
        loop10:
        printf("\n\t��ǰվ����:%d",pstation->station_num);
        printf("\n\t\t������Ҫ���ĵ�վ���ţ�");
        scanf("%d",&station_num);
        tail = gp_station_code;
        while(tail->station_num != station_num )
        {
            tail = tail->next;
            if(tail == NULL)
            {
                printf("\tδ���ҵ��ñ�ţ������³��ԣ�");
                getch();
                ReFresh();
                goto loop10;
            }
        }
        printf("\t\t��վ����ϢΪ��\n");
        printf("\t\t��ţ�%d\tվ�����ƣ�%s",tail->station_num,tail->station_name);
        printf("\n\t\t�Ƿ���ģ� ȷ���밴Y�����������밴N�������밴�����\n");
        while(TRUE)
        {
            key = getch();
            if(key == 'Y' || key == 'y')
            {
                pstation->station_num = tail->station_num;
                strcpy(pstation->station_name, tail->station_name);
                break;
            }
            else if(key == 'N' || key == 'n')
            {
                break;
            }
            else break;
        }
        break;

    case 2:
        printf("\n\t��ǰ����һ��վ�����:%.2f�����",pstation->distance_up);
        printf("\n\t�������µ�����һ��վ����룺");
        scanf("%f",&pstation->distance_up);
        break;

    case 3:
        printf("\n\t��ǰ����һ��վ�㽻ͨ��ʱ:%.2f�����ӣ�",pstation->using_time);
        printf("\n\t�������µ�����һ��վ�㽻ͨ��ʱ��");
        scanf("%f",&pstation->using_time);
        break;

    case 4:
        printf("\n\t��ǰͣ����ʱ:%.2f�����ӣ�",pstation->stay_time);
        printf("\n\t�������µ�ͣ����ʱ��");
        scanf("%f",&pstation->stay_time);
        break;

    case 5:
        printf("\n\n\t��ǰ����̶�·�߱��:%s",pstation->across_num);
        printf("\n\t�������µĽ���̶�·�߱�ţ�");
        scanf("%s",pstation->across_num);
        break;

    case 6:
        loop9:
        printf("\n\t��ǰվ����:%d",pstation->station_num);
        printf("\n\t\t������Ҫ���ĵ�վ���ţ�");
        scanf("%d",&station_num);
        tail = gp_station_code;
        while(tail->station_num != station_num )
        {
            tail = tail->next;
            if(tail == NULL)
            {
                printf("\tδ���ҵ��ñ�ţ������³��ԣ�");
                getch();
                ReFresh();
                goto loop9;
            }
        }
        printf("\t\t��վ����ϢΪ��\n");
        printf("\t\t��ţ�%d\tվ�����ƣ�%s",tail->station_num,tail->station_name);
        printf("\n\t\t�Ƿ���ģ� ȷ���밴Y�����������밴N�������밴�����\n");
        while(TRUE)
        {
            key = getch();
            if(key == 'Y' || key == 'y')
            {
                pstation->station_num = tail->station_num;
                strcpy(pstation->station_name, tail->station_name);
                break;
            }
            else if(key == 'N' || key == 'n')
            {
                break;
            }
            else break;
        }
        printf("\n\t��ǰ����һ��վ�����:%.2f�����",pstation->distance_up);
        printf("\n\t�������µ�����һ��վ����룺");
        scanf("%f",&pstation->distance_up);
        printf("\n\t��ǰ����һ��վ�㽻ͨ��ʱ:%.2f�����ӣ�",pstation->using_time);
        printf("\n\t�������µ�����һ��վ�㽻ͨ��ʱ��");
        scanf("%f",&pstation->using_time);
        printf("\n\t��ǰͣ����ʱ:%.2f�����ӣ�",pstation->stay_time);
        printf("\n\t�������µ�ͣ����ʱ��");
        scanf("%f",&pstation->stay_time);
        printf("\n\n\t��ǰ����̶�·�߱��:%s",pstation->across_num);
        printf("\n\t�������µĽ���̶�·�߱��,�����밴Y,û���밴�����������");
        key = getch();
        if(key=='y' || key =='Y') scanf("%s",pstation->across_num);

    default:
        ReFresh();
        return FALSE;
        break;
    }

    //����������ɶ�·�߻�����Ϣ�ĸ���
    psta = proad->station;
    while(psta)
    {
        fdistance = psta->distance_up;
        psta->distance_init = fdistance;
        ftime = psta->using_time + psta->stay_time + ftime;
        psta=psta->next;
    }

    proad->full_time = ftime;
    proad->full_distance = fdistance;



    Show_Cursor(FALSE);
    printf("\n\n\t\t�����������");
    getch();
    ReFresh();
    SaveRoad(); // ��������



    return bRet;
}

BOOL InsertRoad(void)
{
    BOOL bRet = TRUE;
    NewRoad();
    return bRet;
}

/**< ����ܾ��� */

BOOL InsertStation(void)
{
    BOOL bRet = TRUE;
    ROAD_DATA *proad;
    STATION_DATA *pstation, *psta, *prun;
    TRUCK_DATA *ptruck;
    GOODS_DATA *pgoods, *pgoods_find;
    STATION_CODE *tail;
    char fname[6], *plussta="��վ" ,stationnum[10], sfind[10];
    int station_count = 0, find, key, goods_find, goods_count=0;
    float  fdistance, fvolume, ftime;

    GotoXY(40,3);
    printf("����վ����Ϣ");
    GotoXY(20,5);
    printf("��ǰ����·�ߣ�");
    proad = gp_head;
    printf("\n\t\t");
    if(gp_head == NULL)
    {
        printf("��ǰû��·��¼�룬��ǰȥ¼��·�ߣ�");
        getch();
        ReFresh();
        return FALSE;
    }
    while(proad)
    {
        printf("\n\t\t%s--%s  ",proad->road,proad->road_name);
        proad=proad->next;
    }

    //����·�����
    loop10:
    printf("\n\n\t\t������Ҫ���ĵ�·��(��1����)��");
    Show_Cursor(TRUE);
    scanf("%s",fname);
    Show_Cursor(FALSE);
    proad = gp_head;
    while(strcmp(fname,proad->road) != 0)
    {
        proad=proad->next;
        if(proad == NULL)
        {
            printf("\n\n\t\tû���ҵ���·�ߣ����������룡��E�˳�");
            key = getch();
            if(key == 'e' || key == 'E')
            {
                ReFresh();
                return FALSE;
            }
            goto loop10;
        }
    }
    printf("\n\n\t\t���ҵ�����·���밴������鿴��·��\n");
    getch();
    ReFresh();

    GotoXY(40,3);
    printf("����վ��");
    pstation = proad->station;
    printf("\n\t\tվ�����\tվ������");
    while(pstation)
    {
        printf("\n\t\t%s\t%s",pstation->station_id,pstation->station_name);
        pstation=pstation->next;
    }
    loop11:
    printf("\n\n\t\t��������Ҫ����վ���ǰһ��վ�����ţ���1��վ����");
    Show_Cursor(TRUE);
    scanf("%s",sfind);
    fdistance = 0;
    pstation = proad->station;
    while(pstation)
    {
        station_count++;
        if(!strcmp(pstation->station_id,sfind)) break;
        pstation = pstation->next;
        if(pstation == NULL)
        {
            printf("\n\t\tû���ҵ�վ�㣬���������룡");
            goto loop11;
        }
    }
    if(pstation->next == NULL)
    {
        printf("\n\t\t���������룬ֻ�ܲ��뾭ͣվ��");
        goto loop11;
    }


    ReFresh();
    //����վ��
    psta = (STATION_DATA*)malloc(sizeof(STATION_DATA));
    printf("\n\t\t\t��ͣվ����Ϣ¼��\n");
    station_count++;
    itoa(station_count,stationnum,10);   //վ���������
    strcat(stationnum,plussta);
    strcpy(psta->station_id,stationnum);
    strcpy(psta->road, proad->road);
    printf("\n\t\t��ǰվ����ţ�%s",psta->station_id);

    loop12:
    printf("\n\t\t������վ���ţ�");
    Show_Cursor(TRUE);
    scanf("%d",&find);
    tail = gp_station_code;

    //վ�����

    while(tail->station_num != find )
    {
        tail = tail->next;
        if(tail == NULL)
        {
            printf("\n\tδ���ҵ��ñ�ţ������³��ԣ�");
            getch();
            goto loop12;
        }
    }
    printf("\n\t\t��վ����ϢΪ��\n");
    printf("\t\t��ţ�%d\tվ�����ƣ�%s",tail->station_num,tail->station_name);
    printf("\n\t\t\tȷ���밴�������ȡ���밴N");
    key = getch();
    if(key == 'N' || key == 'n')
    {
        goto loop12;
    }
    strcpy(psta->road, proad->road);
    psta->station_num = find;
    strcpy(psta->station_name,tail->station_name);
    printf("\n\t\t����������һ��վ����루km����");
    scanf("%f",&psta->distance_up);
    //��������ʼվ�����

    fdistance = pstation->distance_init;
    fdistance += psta->distance_up;
    printf("\n\t\t����ʼվ����루km�����Զ����ɣ���%.2f",fdistance);
    psta->distance_init = fdistance;
    printf("\n\t\t������������һ��վ�㽻ͨ��ʱ��min����");
    scanf("%f",&psta->using_time);
    printf("\n\t\t�������ڴ�ͣ����ʱ�����ӣ���");
    scanf("%f",&psta->stay_time);
    Show_Cursor(FALSE);  //���ع��
    printf("\n\t\t��վ���Ƿ��н���̶�·�߱�ţ������밴Y��û�������������");
    key = getch();
    if(key == 'y' || key == 'Y')
    {
        Show_Cursor(TRUE);
        printf("\n\t\t�������ڴ�վ��Ľ���̶�·�߱�ţ�");
        scanf("%s",psta->across_num);
    }
    else
    {
        psta->across_num[0] ='\0';
    }
    strcpy(psta->road, proad->road);

    ptruck = (TRUCK_DATA*)malloc(sizeof(TRUCK_DATA));
    psta->truck = ptruck;
    strcpy(ptruck->road,proad->road);
    strcpy(ptruck->station_id,stationnum);
    printf("\n\n\t\t�밴���������ж���嵥������");
    key = getch();

    //ж����Ϣ¼��
    ReFresh(); //����һҳ����
    GotoXY(40,3);
    printf("����վ��\n");
    Show_Cursor(TRUE);

    //�Ի�����������
    pgoods_find = proad->station->truck->goods;
    while(pgoods_find)
    {
        goods_count++;
        pgoods_find = pgoods_find->next;
    }
    //��ͷ
    fvolume = 0;
    printf("\n\t\t\t%sվж������Ϣ¼�룺\n",psta->station_name);
    pgoods = (GOODS_DATA*)malloc(sizeof(GOODS_DATA));
    ptruck->goods = pgoods;
    printf("\n\t\t��������ţ�");
    Show_Cursor(TRUE);
    scanf("%d",&goods_find);
    if(goods_find<=goods_count)
    {
        pgoods_find = proad->station->truck->goods;
        while(TRUE)
        {
            if(goods_find == pgoods_find->number) break;
            pgoods_find = pgoods_find->next;
            if(pgoods_find == NULL)
            {
                printf("\t\t��������������\n");
                scanf("%d",&goods_find);
                pgoods_find = proad->station->truck->goods;
            }
        }
        Show_Cursor(FALSE);  //���ع��
        printf("\n\t\t�������ƣ�%s\t������ж��������",pgoods_find->name);
        Show_Cursor(TRUE);
        scanf("%f",&pgoods->quantity);
        fvolume += pgoods->quantity;
        pgoods->number = pgoods_find->number;
        strcpy(pgoods->name ,pgoods_find->name);
        //pgoods->station_num = ptruck->station_num;  //��ȫ·����Ϣ
        strcpy(ptruck->station_id,psta->station_id);
        strcpy(pgoods->station_id,psta->station_id);
        strcpy(pgoods->road, psta->road);
        printf("\t\t�밴���������������밴N\n");
        key = getch();
    }
    else printf("����");    //�Ҳ���
    //�ڶ�����ʼ
    while(key != 'n' && key != 'N')
    {
        Show_Cursor(TRUE);
        pgoods->next = (GOODS_DATA*)malloc(sizeof(GOODS_DATA));
        pgoods = pgoods->next;
        printf("\n\t\t��������ţ�");
        Show_Cursor(TRUE);
        scanf("%d",&goods_find);
        if(goods_find<=goods_count)
        {
            pgoods_find = proad->station->truck->goods;
            while(TRUE)
            {
                if(goods_find == pgoods_find->number) break;
                pgoods_find = pgoods_find->next;
                if(pgoods_find == NULL)
                {
                    printf("\t\t��������������\n");
                    scanf("%d",&goods_find);
                    pgoods_find = proad->station->truck->goods;
                }
            }
            Show_Cursor(FALSE);  //���ع��
            printf("\n\t\t�������ƣ�%s\t������ж��������",pgoods_find->name);
            Show_Cursor(TRUE);
            scanf("%f",&pgoods->quantity);
            fvolume += pgoods->quantity;
            pgoods->number = goods_find;
            strcpy(pgoods->name ,pgoods_find->name);
            //pgoods->station_num = ptruck->station_num;  //��ȫ·����Ϣ
            strcpy(ptruck->station_id,psta->station_id);
            strcpy(pgoods->station_id,psta->station_id);
            strcpy(pgoods->road, psta->road);
            Show_Cursor(FALSE);  //���ع��
            printf("\t\t�밴���������������밴N\n");
            key = getch();
            //if(key == 'n' || key == 'N') break;
        }
        else printf("����");
    }
    pgoods->next = NULL;
    //��ʣ���ػ����ĸ���
    ptruck->volume = proad->station->truck->volume;
    ptruck->left_volume = pstation->truck->left_volume + fvolume;
    Show_Cursor(FALSE);  //���ع��

    //����������
    psta->next = pstation->next;
    pstation->next = psta;

    //������վ��ʣ���ػ����;�����޸�
    prun = psta;
    psta = psta->next;
    while(psta)
    {
        ptruck = psta->truck;
        pgoods = ptruck->goods;
        station_count++;
        itoa(station_count,stationnum,10);   //վ����Ÿ���
        strcat(stationnum,plussta);
        strcpy(psta->station_id,stationnum);
        strcpy(ptruck->station_id,stationnum); //�����޸ĳ�������Ϣ
        while(pgoods)            //�Լ������嵥��Ϣ������
        {
            strcpy(pgoods->station_id,stationnum);
            pgoods = pgoods->next;
        }
        strcpy(psta->road, proad->road);
        psta->distance_init = prun->distance_init + psta->distance_up;  //����
        psta->truck->left_volume += fvolume;  //����
        psta = psta->next;
        prun = prun->next;
    }

    //����������ɶ�·�߻�����Ϣ�ĸ���
    psta = proad->station;
    while(psta)
    {
        fdistance = psta->distance_init;
        ftime = psta->using_time + psta->stay_time + ftime;
        psta=psta->next;
    }

    //����õ�����Ϣ
    proad->full_time = ftime;
    proad->full_distance = fdistance;
    proad->full_station++;

    Show_Cursor(FALSE);
    printf("\n\n\t\t�����������");
    getch();
    ReFresh();
    SaveRoad(); // ��������

    return bRet;
}

BOOL DeleteStationBase(void)
{
    BOOL bRet = TRUE;
    ROAD_DATA *proad;
    STATION_DATA *pstation, *psta, *prun;
    TRUCK_DATA *ptruck;
    GOODS_DATA *pgoods, *pgoods_find;
    char fname[6], *plussta="��վ" ,stationnum[10], sfind[10];
    int station_count = 0, key;
    float  fdistance, fvolume, ftime;
    char *pCh = "ȷ��ɾ����վ����";
    int iHot = 2;
    int sRet;

    GotoXY(40,3);
    printf("ɾ��վ��");
    GotoXY(20,5);
    printf("��ǰ����·�ߣ�");
    proad = gp_head;
    printf("\n\t\t");
    if(gp_head == NULL)
    {
        printf("��ǰû��·��¼�룬��ǰȥ¼��·�ߣ�");
        getch();
        ReFresh();
        return FALSE;
    }
    while(proad)
    {
        printf("\n\t\t%s--%s  ",proad->road,proad->road_name);
        proad=proad->next;
    }

    //����·�����
    loop13:
    printf("\n\n\t\t������Ҫ���ĵ�·��(��1����)��");
    Show_Cursor(TRUE);
    scanf("%s",fname);
    Show_Cursor(FALSE);
    proad = gp_head;
    while(strcmp(fname,proad->road) != 0)
    {
        proad=proad->next;
        if(proad == NULL)
        {
            printf("\n\n\t\tû���ҵ���·�ߣ����������룡��E�˳�");
            key = getch();
            if(key == 'e' || key == 'E')
            {
                ReFresh();
                return FALSE;
            }
            goto loop13;
        }
    }
    printf("\n\n\t\t���ҵ�����·���밴������鿴��·��\n");
    getch();
    ReFresh();

    GotoXY(40,3);
    printf("ɾ����ͣվ��");
    pstation = proad->station;
    printf("\n\t\tվ�����\tվ������");
    while(pstation)
    {
        printf("\n\t\t%s\t%s",pstation->station_id,pstation->station_name);
        pstation=pstation->next;
    }
    loop14:
    printf("\n\n\t\t��������Ҫɾ����վ�㣨��1��վ����");
    Show_Cursor(TRUE);
    scanf("%s",sfind);
    fdistance = 0;
    pstation = proad->station;
    while(pstation)
    {
        station_count++;
        if(!strcmp(pstation->station_id,sfind)) break;
        psta = pstation;
        pstation = pstation->next;
        if(pstation == NULL)
        {
            printf("\n\t\tû���ҵ�վ�㣬���������룡");
            goto loop14;
        }
    }
    if(pstation->next == NULL || pstation == proad->station)
    {
        printf("\n\t\t���������룬ֻ��ɾ����ͣվ��");
        goto loop14;
    }

    ReFresh();
    GotoXY(40,3);
    printf("ɾ����ͣվ��");
    printf("\n\n\t\t��ǰѡ�е�·�ߺ�վ��Ϊ��%s��������%s",pstation->road,pstation->station_id);

    sRet = PopPrompt(&pCh, &iHot);
    if (sRet == 13 && iHot == 1)
    {
        bRet = TRUE;
        //������������
        psta->next = pstation->next;

        ptruck = pstation->truck;
        pgoods = ptruck->goods;
        fvolume = 0;
        //�ͷſռ�
        while(pgoods)
        {
            fvolume += pgoods->quantity; //�Ի�����������
            pgoods_find = pgoods;
            pgoods = pgoods->next;
            free(pgoods_find);
        }
        free(ptruck);
        free(pstation);

        //���ĺ���վ����Ϣ
        prun = psta;
        psta = psta->next;
        station_count--;
        while(psta)
        {
            ptruck = psta->truck;
            pgoods = ptruck->goods;
            station_count++;
            itoa(station_count,stationnum,10);   //վ����Ÿ���
            strcat(stationnum,plussta);
            strcpy(psta->station_id,stationnum);
            strcpy(ptruck->station_id,stationnum); //�����޸ĳ�������Ϣ
            while(pgoods)            //�Լ������嵥��Ϣ������
            {
                strcpy(pgoods->station_id,stationnum);
                pgoods = pgoods->next;
            }
            psta->distance_init = prun->distance_init + psta->distance_up;  //����
            psta->truck->left_volume -= fvolume;  //����
            psta = psta->next;
            prun = prun->next;
        }

        //����������ɶ�·�߻�����Ϣ�ĸ���
        psta = proad->station;
        while(psta)
        {
            fdistance = psta->distance_init;
            ftime = psta->using_time + psta->stay_time + ftime;
            psta=psta->next;
        }

        //����õ�����Ϣ
        proad->full_time = ftime;
        proad->full_distance = fdistance;
        proad->full_station--;

        ReFresh();
        SaveRoad(); // ��������

    }
    else
    {
        bRet = FALSE;
    }
    PopOff();
    ReFresh();

    if(bRet == TRUE) printf("\n\n\t\tɾ���ɹ����밴���������"), getch();
    ReFresh();


    return bRet;

}

BOOL InsertGoods(void)
{
    BOOL bRet = TRUE;
    ROAD_DATA *proad;
    STATION_DATA *pstation;
    TRUCK_DATA *ptruck;
    GOODS_DATA *pgoods, *pgoods_initsta;
    char fname[6] , sfind[10];
    int count, key, find;
    float  fvolume;

    GotoXY(40,3);
    printf("�������");
    GotoXY(20,5);
    printf("��ǰ����·�ߣ�");
    proad = gp_head;
    printf("\n\t\t");
    if(gp_head == NULL)
    {
        printf("��ǰû��·��¼�룬��ǰȥ¼��·�ߣ�");
        getch();
        ReFresh();
        return FALSE;
    }
    while(proad)
    {
        printf("\n\t\t%s--%s  ",proad->road,proad->road_name);
        proad=proad->next;
    }

    //����·�����
    loop16:
    printf("\n\n\t\t������Ҫ���ĵ�·��(��1����)��");
    Show_Cursor(TRUE);
    scanf("%s",fname);
    Show_Cursor(FALSE);
    proad = gp_head;
    while(strcmp(fname,proad->road) != 0)
    {
        proad=proad->next;
        if(proad == NULL)
        {
            printf("\n\n\t\tû���ҵ���·�ߣ����������룡��E�˳�");
            key = getch();
            if(key == 'e' || key == 'E')
            {
                ReFresh();
                return FALSE;
            }
            goto loop16;
        }
    }
    printf("\n\n\t\t���ҵ�����·���밴������鿴��·��\n");
    getch();
    ReFresh();

    GotoXY(40,3);
    printf("�������");
    pstation = proad->station;
    printf("\n\t\tվ�����\tվ������");
    while(pstation)
    {
        printf("\n\t\t%s\t%s",pstation->station_id,pstation->station_name);
        pstation=pstation->next;
    }
    loop17:
    printf("\n\n\t\t��������Ҫ��������վ�㣨��1��վ����");
    Show_Cursor(TRUE);
    scanf("%s",sfind);
    pstation = proad->station;
    while(pstation)
    {
        if(!strcmp(pstation->station_id,sfind)) break;
        pstation = pstation->next;
        if(pstation == NULL)
        {
            printf("\n\t\tû���ҵ�վ�㣬���������룡");
            goto loop17;
        }
    }

    ReFresh();
    GotoXY(40,3);
    printf("�������");
    printf("\n\n\t\t��ǰѡ�е�·�ߺ�վ��Ϊ��%s��������%s",pstation->road,pstation->station_id);
    ptruck = pstation->truck;
    pgoods = ptruck->goods;
    printf("\n\n\t\t������\t����\t�������֣�");
    while(pgoods)
    {
        printf("\n\t\t%d\t\t%s\t%.2f",pgoods->number,pgoods->name,pgoods->quantity);
        count = pgoods->number;
        if(pgoods->next == NULL)
        {
            pgoods->next = (GOODS_DATA*) malloc(sizeof(GOODS_DATA));
            break;
        }
        pgoods = pgoods->next;
    }
    //�����½ڵ�
    pgoods = pgoods->next;
    pgoods->next = NULL;
    if(pstation == proad->station)
    {
        //�����½ڵ�
        printf("\n\n\t\t��������Ҫ����Ļ������ƺ��������֣�");
        Show_Cursor(TRUE);
        scanf("%s%f",pgoods->name,&pgoods->quantity);
        pgoods->number = ++count;
    }
    else
    {
        loop26:
        printf("\n\n\t\t��������Ҫ����Ļ����ţ�");
        Show_Cursor(TRUE);
        scanf("%d",&find);
        pgoods_initsta = proad->station->truck->goods;
        while(find != pgoods_initsta->number)
        {
            pgoods_initsta = pgoods_initsta->next;
            if(pgoods_initsta == NULL)
            {
                printf("\n\t\tû���ҵ��û������������룺");
                goto loop26;
            }
        }
        printf("\n\n\t\t��ǰ�����ţ�%d   �������ƣ�%s",pgoods_initsta->number,pgoods_initsta->name);
        pgoods->number = pgoods_initsta->number;
        strcpy(pgoods->name,pgoods_initsta->name);
        printf("\n\n\t\t������ж���������֣���");
        scanf("%f",&pgoods->quantity);
    }
    //��ȫ��Ϣ
    strcpy(pgoods->road,pstation->road);
    strcpy(pgoods->station_id,pstation->station_id);
    //�������޸�
    fvolume = pgoods->quantity;
    //��ʼվ�㴦��
    if(pstation == proad->station)
    {
        while(pstation)
        {
            ptruck = pstation->truck;
            ptruck->left_volume -= fvolume;
            pstation = pstation->next;
        }
    }
    else
    {
        while(pstation)
        {
            ptruck = pstation->truck;
            ptruck->left_volume += fvolume;
            pstation = pstation->next;
        }
    }

    printf("\n\n\t\t�밴���������");
    getch();
    ReFresh();
    SaveRoad();


    return bRet;
}

BOOL EditGoods(void)
{
    BOOL bRet = TRUE;
    ROAD_DATA *proad;
    STATION_DATA *pstation;
    TRUCK_DATA *ptruck;
    GOODS_DATA *pgoods;
    char fname[6] , sfind[10];
    int  key, find;
    float  fvolume;

    GotoXY(40,3);
    printf("�༭����");
    GotoXY(20,5);
    printf("��ǰ����·�ߣ�");
    proad = gp_head;
    printf("\n\t\t");
    if(gp_head == NULL)
    {
        printf("��ǰû��·��¼�룬��ǰȥ¼��·�ߣ�");
        getch();
        ReFresh();
        return FALSE;
    }
    while(proad)
    {
        printf("\n\t\t%s--%s  ",proad->road,proad->road_name);
        proad=proad->next;
    }

    //����·�����
    loop18:
    printf("\n\n\t\t������Ҫ���ĵ�·��(��1����)��");
    Show_Cursor(TRUE);
    scanf("%s",fname);
    Show_Cursor(FALSE);
    proad = gp_head;
    while(strcmp(fname,proad->road) != 0)
    {
        proad=proad->next;
        if(proad == NULL)
        {
            printf("\n\n\t\tû���ҵ���·�ߣ����������룡��E�˳�");
            key = getch();
            if(key == 'e' || key == 'E')
            {
                ReFresh();
                return FALSE;
            }
            goto loop18;
        }
    }
    printf("\n\n\t\t���ҵ�����·���밴������鿴��·��\n");
    getch();
    ReFresh();

    GotoXY(40,3);
    printf("�༭����");
    pstation = proad->station;
    printf("\n\t\tվ�����\tվ������");
    while(pstation)
    {
        printf("\n\t\t%s\t%s",pstation->station_id,pstation->station_name);
        pstation=pstation->next;
    }
    loop19:
    printf("\n\n\t\t��������Ҫ��������վ�㣨��1��վ����");
    Show_Cursor(TRUE);
    scanf("%s",sfind);
    pstation = proad->station;
    while(pstation)
    {
        if(!strcmp(pstation->station_id,sfind)) break;
        pstation = pstation->next;
        if(pstation == NULL)
        {
            printf("\n\t\tû���ҵ�վ�㣬���������룡");
            goto loop19;
        }
    }

    ReFresh();
    GotoXY(40,3);
    printf("�༭����");
    printf("\n\n\t\t��ǰѡ�е�·�ߺ�վ��Ϊ��%s��������%s",pstation->road,pstation->station_id);
    ptruck = pstation->truck;
    pgoods = ptruck->goods;
    printf("\n\n\t\t������\t����\t�������֣�");
    while(pgoods)
    {
        printf("\n\t\t%d\t\t%s\t%.2f",pgoods->number,pgoods->name,pgoods->quantity);
        pgoods = pgoods->next;
    }

    loop20:
    printf("\n\n\t\t��������Ҫ���ĵĻ����ţ�");
    Show_Cursor(TRUE);
    scanf("%d",&find);
    pgoods = ptruck->goods;
    while(find != pgoods->number)
    {
        pgoods = pgoods->next;
        if(pgoods == NULL)
        {
            printf("\n\t\tû���ҵ��û������������룺");
            goto loop20;
        }
    }
    printf("\n\n\t\t��ǰ�����ţ�%d   �������ƣ�%s  ����������%.2f",pgoods->number,pgoods->name,pgoods->quantity);
    printf("\n\n\t\t�������µĻ������ƣ�");
    scanf("%s",pgoods->name);
    printf("\n\t\t�������µĻ���������");
    scanf("%f",&pgoods->quantity);

    //�Ժ���վ��Ĵ���
    fvolume = pgoods->quantity;
    //��ʼվ�㴦��
    if(pstation == proad->station)
    {
        while(pstation)
        {
            ptruck = pstation->truck;
            ptruck->left_volume -= fvolume;
            pstation = pstation->next;
        }
    }
    else
    {
        while(pstation)
        {
            ptruck = pstation->truck;
            ptruck->left_volume += fvolume;
            pstation = pstation->next;
        }
    }

    printf("\n\n\t\t�밴���������");
    getch();
    ReFresh();
    SaveRoad();

    return bRet;
}

BOOL DeleteGoods(void)
{
    BOOL bRet = TRUE;
    ROAD_DATA *proad;
    STATION_DATA *pstation;
    TRUCK_DATA *ptruck;
    GOODS_DATA *pgoods,*pgoods_up = NULL;
    char fname[6] , sfind[10];
    int  key, find;
    float  fvolume;
    char *pCh = "ȷ��ɾ���û�����";
    int iHot = 2;
    int sRet;

    GotoXY(40,3);
    printf("ɾ������");
    GotoXY(20,5);
    printf("��ǰ����·�ߣ�");
    proad = gp_head;
    printf("\n\t\t");
    if(gp_head == NULL)
    {
        printf("��ǰû��·��¼�룬��ǰȥ¼��·�ߣ�");
        getch();
        ReFresh();
        return FALSE;
    }
    while(proad)
    {
        printf("\n\t\t%s--%s  ",proad->road,proad->road_name);
        proad=proad->next;
    }

    //����·�����
    loop21:
    printf("\n\n\t\t������Ҫ���ĵ�·��(��1����)��");
    Show_Cursor(TRUE);
    scanf("%s",fname);
    Show_Cursor(FALSE);
    proad = gp_head;
    while(strcmp(fname,proad->road) != 0)
    {
        proad=proad->next;
        if(proad == NULL)
        {
            printf("\n\n\t\tû���ҵ���·�ߣ����������룡��E�˳�");
            key = getch();
            if(key == 'e' || key == 'E')
            {
                ReFresh();
                return FALSE;
            }
            goto loop21;
        }
    }
    printf("\n\n\t\t���ҵ�����·���밴������鿴��·��\n");
    getch();
    ReFresh();

    GotoXY(40,3);
    printf("ɾ������");
    pstation = proad->station;
    printf("\n\t\tվ�����\tվ������");
    while(pstation)
    {
        printf("\n\t\t%s\t%s",pstation->station_id,pstation->station_name);
        pstation=pstation->next;
    }
    loop22:
    printf("\n\n\t\t��������Ҫ��������վ�㣨��1��վ����");
    Show_Cursor(TRUE);
    scanf("%s",sfind);
    pstation = proad->station;
    while(pstation)
    {
        if(!strcmp(pstation->station_id,sfind)) break;
        pstation = pstation->next;
        if(pstation == NULL)
        {
            printf("\n\t\tû���ҵ�վ�㣬���������룡");
            goto loop22;
        }
    }

    ReFresh();
    GotoXY(40,3);
    printf("ɾ������");
    printf("\n\n\t\t��ǰѡ�е�·�ߺ�վ��Ϊ��%s��������%s",pstation->road,pstation->station_id);
    ptruck = pstation->truck;
    pgoods = ptruck->goods;
    printf("\n\n\t\t������\t����\t�������֣�");
    while(pgoods)
    {
        printf("\n\t\t%d\t\t%s\t%.2f",pgoods->number,pgoods->name,pgoods->quantity);
        pgoods = pgoods->next;
    }

    loop23:
    printf("\n\n\t\t��������Ҫɾ���Ļ����ţ�");
    Show_Cursor(TRUE);
    scanf("%d",&find);
    pgoods = ptruck->goods;
    while(find != pgoods->number)
    {
        pgoods_up = pgoods;
        pgoods = pgoods->next;
        if(pgoods == NULL)
        {
            printf("\n\t\tû���ҵ��û������������룺");
            goto loop23;
        }
    }

    ReFresh();
    sRet = PopPrompt(&pCh, &iHot);
    if (sRet == 13 && iHot == 1)
    {
        bRet = TRUE;

        //�Ժ���վ��Ĵ���
        fvolume = pgoods->quantity;

        //������ͷ
        if(ptruck->goods == pgoods)
            ptruck->goods = pgoods->next;
        else
            pgoods_up->next = pgoods->next;
        //�ͷſռ�
        free(pgoods);

//        if(pgoods_up != NULL) pgoods = pgoods_up->next;
//        else pgoods = ptruck->goods;
////        while(pgoods)
////        {
////            pgoods->number = count++;
////            pgoods = pgoods->next;
////        }

        //��ʼվ�㴦��
        if(pstation == proad->station)
        {
            while(pstation)
            {
                ptruck = pstation->truck;
                ptruck->left_volume += fvolume;
                pstation = pstation->next;
            }
        }
        else
        {
            while(pstation)
            {
                ptruck = pstation->truck;
                ptruck->left_volume -= fvolume;
                pstation = pstation->next;
            }
        }

    }
    else
    {
        bRet = FALSE;
    }
    PopOff();
    ReFresh();
    if(bRet == TRUE) printf("\n\n\t\tɾ���ɹ�");
    ReFresh();
    printf("\n\t\t�밴���������");
    getch();
    ReFresh();
    SaveRoad();


    return bRet;
}


