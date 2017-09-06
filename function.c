#include"global.h"


/**
 *
 * \brief ���ļ���Ҫ�������ʵ�ַ���ĺ���
 *
 */


/**
 * ��������: InitInterface
 * ��������: ��ʼ������.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void InitInterface()
{
    WORD att = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY
               | BACKGROUND_INTENSITY;  /*��ɫǰ���ͻ�ɫ����*/

    SetConsoleTextAttribute(gh_std_out, att);  /*���ÿ���̨��Ļ�������ַ�����*/

    ClearScreen();  /* ����*/

    /*��������������Ϣ��ջ������ʼ�������Ļ���ڵ�����һ�㵯������*/
    gp_scr_att = (char *)calloc(SCR_COL * SCR_ROW, sizeof(char));//��Ļ�ַ�����,SCR_COL���������൱�ڶ�Ӧ��Ļ�ϵ�ÿһ������
    gp_top_layer = (LAYER_NODE *)malloc(sizeof(LAYER_NODE));  //gp_top_layer��Ļ������Ϣ�������ṹ,��Ļ������Ϣ�������ṹ
    gp_top_layer->LayerNo = 0;      /*�������ڵĲ��Ϊ0*/
    gp_top_layer->rcArea.Left = 0;  /*�������ڵ�����Ϊ������Ļ����*/
    gp_top_layer->rcArea.Top = 0; //����Ǳ߾ࣿ
    gp_top_layer->rcArea.Right = SCR_COL - 1;
    gp_top_layer->rcArea.Bottom = SCR_ROW - 1;
    gp_top_layer->pContent = NULL;  //�������������ַ���Ԫԭ��Ϣ�洢������
    gp_top_layer->pScrAtt = gp_scr_att; //�������������ַ���Ԫԭ����ֵ�洢������,gp_scr_att = �Ѿ���ʼ��
    gp_top_layer->next = NULL;

    ShowMenu();     /*��ʾ�˵���*/

    return;
}

/**
 * ��������: ReFresh
 * ��������: ˢ�½���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */

void ReFresh()
{
    ClearScreen();  /* ����*/
    ShowMenu();     /*��ʾ�˵���*/

    return;
}

/**
 * ��������:
 * ��������: ˢ�½���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void GotoXY(int x, int y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(gh_std_out, pos);
}
/**
 * ��������:
 * ��������: ��ʾ�����ؿ���̨���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */

void Show_Cursor(BOOL boo)
{
    CONSOLE_CURSOR_INFO lpCur; //����̨�����Ϣ

    GetConsoleCursorInfo(gh_std_out, &lpCur); //�����й�ָ���Ŀ���̨��Ļ�������Ĺ��Ŀɼ��Ժʹ�С��Ϣ��
    lpCur.bVisible = boo;
    SetConsoleCursorInfo(gh_std_out, &lpCur);
}

/**
 * ��������: ClearScreen
 * ��������: �����Ļ��Ϣ.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void ClearScreen(void)
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD home = {0, 0}; //COORD��һ���ṹ����ʾ����
    unsigned long size;

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );//����ȡ��Ļ��������Ϣ
    size =  bInfo.dwSize.X * bInfo.dwSize.Y; /*������Ļ�������ַ���Ԫ��*/

    /*����Ļ���������е�Ԫ���ַ���������Ϊ��ǰ��Ļ�������ַ�����*/
    FillConsoleOutputAttribute(gh_std_out, bInfo.wAttributes, size, home, &ul); //API����������������̨�Ĳ���������ɫ��

    /*����Ļ���������е�Ԫ���Ϊ�ո��ַ�*/
    FillConsoleOutputCharacter(gh_std_out, ' ', size, home, &ul);

    return;
}

/**
 * ��������: ShowMenu
 * ��������: ����Ļ����ʾ���˵�, ����������, �����˵���һ������ѡ�б��.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void ShowMenu()
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    CONSOLE_CURSOR_INFO lpCur; //����̨�����Ϣ
    COORD size;
    COORD pos = {0, 0};
    int i, j;
    int PosA = 2, PosB;
    char ch;

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo ); //���ڼ���ָ���Ŀ���̨��Ļ����������Ϣ��
    size.X = bInfo.dwSize.X;
    size.Y = 1;
    SetConsoleCursorPosition(gh_std_out, pos);
    for (i=0; i < 5; i++) /*�ڴ��ڵ�һ�е�һ�д�������˵���*/
    {
        printf("  %s  ", ga_main_menu[i]);//�˵����������
    }

    GetConsoleCursorInfo(gh_std_out, &lpCur); //�����й�ָ���Ŀ���̨��Ļ�������Ĺ��Ŀɼ��Ժʹ�С��Ϣ��
    lpCur.bVisible = FALSE;
    SetConsoleCursorInfo(gh_std_out, &lpCur);  /*���ع��*/

    /*���붯̬�洢����Ϊ��Ų˵�����Ļ���ַ���Ϣ�Ļ�����*/
    gp_buff_menubar_info = (CHAR_INFO *)malloc(size.X * size.Y * sizeof(CHAR_INFO));
    SMALL_RECT rcMenu ={0, 0, size.X-1, 0} ;

    /*�����ڵ�һ�е����ݶ��뵽��Ų˵�����Ļ���ַ���Ϣ�Ļ�������*/
    ReadConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);

    /*����һ����Ӣ����ĸ��Ϊ��ɫ�������ַ���Ԫ��Ϊ�׵׺���*/
//���Ǻ����
    for (i=0; i<size.X; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
                                               | BACKGROUND_RED;
        ch = (char)((gp_buff_menubar_info+i)->Char.AsciiChar);
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            (gp_buff_menubar_info+i)->Attributes |= FOREGROUND_RED;
        }
    }

    /*�޸ĺ�Ĳ˵����ַ���Ϣ��д�����ڵĵ�һ��*/
    WriteConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);
    COORD endPos = {0, 1};
    SetConsoleCursorPosition(gh_std_out, endPos);  /*�����λ�������ڵ�2�е�1��*/

    /*���˵�����Ϊ�������������Ϊ�˵���ţ���������Ϊ0(��ť��)*/
    i = 0;
    do
    {
        PosB = PosA + strlen(ga_main_menu[i]);  /*��λ��i+1�Ų˵������ֹλ��*/
        for (j=PosA; j<PosB; j++)
        {
            gp_scr_att[j] |= (i+1) << 2; //??/*���ò˵��������ַ���Ԫ������ֵ*/
        }
        PosA = PosB + 4;
        i++;
    } while (i<5);

    TagMainMenu(gi_sel_menu);  /*��ѡ�����˵���������ǣ�gi_sel_menu��ֵΪ1*/

    return;
}

/**
 * ��������: ShowState
 * ��������: ��ʾ״̬��.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��: ״̬���ַ�����Ϊ�׵׺���, ��ʼ״̬��״̬��Ϣ.
 */
void ShowState()
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD size;
    COORD pos = {0, 0};
    int i;

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );
    size.X = bInfo.dwSize.X;
    size.Y = 2;
    SMALL_RECT rcMenu ={0, bInfo.dwSize.Y-2, size.X-1, bInfo.dwSize.Y-1};

    if (gp_buff_stateBar_info == NULL)
    {
        gp_buff_stateBar_info = (CHAR_INFO *)malloc(size.X * size.Y * sizeof(CHAR_INFO));
        ReadConsoleOutput(gh_std_out, gp_buff_stateBar_info, size, pos, &rcMenu);
    }

    for (i=0; i<size.X*size.Y; i++)
    {
        (gp_buff_stateBar_info+i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
                                                | BACKGROUND_RED;
/*
        ch = (char)((gp_buff_stateBar_info+i)->Char.AsciiChar);
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            (gp_buff_stateBar_info+i)->Attributes |= FOREGROUND_RED;
        }
*/
    }

    WriteConsoleOutput(gh_std_out, gp_buff_stateBar_info, size, pos, &rcMenu);

    return;
}

/**
 * ��������: TagMainMenu
 * ��������: ��ָ�����˵�������ѡ�б�־.
 * �������: num ѡ�е����˵����
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void TagMainMenu(int num)
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD size;
    COORD pos = {0, 0};
    int PosA = 2, PosB;
    char ch;
    int i;

    if (num == 0) /*numΪ0ʱ������ȥ�����˵���ѡ�б��*/
    {
        PosA = 0;
        PosB = 0;
    }
    else  /*���򣬶�λѡ�����˵������ֹλ��: PosAΪ��ʼλ��, PosBΪ��ֹλ��*/
    {
        for (i=1; i<num; i++)
        {
            PosA += strlen(ga_main_menu[i-1]) + 4;
        }
        PosB = PosA + strlen(ga_main_menu[num-1]);
    }

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );
    size.X = bInfo.dwSize.X;
    size.Y = 1;

    /*ȥ��ѡ�в˵���ǰ��Ĳ˵���ѡ�б��*/
    for (i=0; i<PosA; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
                                               | BACKGROUND_RED;
        ch = (gp_buff_menubar_info+i)->Char.AsciiChar;
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            (gp_buff_menubar_info+i)->Attributes |= FOREGROUND_RED;
        }
    }

    /*��ѡ�в˵���������ǣ��ڵװ���*/
    for (i=PosA; i<PosB; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN
                                               | FOREGROUND_RED;
    }

    /*ȥ��ѡ�в˵������Ĳ˵���ѡ�б��*/
    for (i=PosB; i<bInfo.dwSize.X; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
                                               | BACKGROUND_RED;
        ch = (char)((gp_buff_menubar_info+i)->Char.AsciiChar);
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            (gp_buff_menubar_info+i)->Attributes |= FOREGROUND_RED;
        }
    }

    /*�����ñ�ǵĲ˵�����Ϣд�����ڵ�һ��*/
    SMALL_RECT rcMenu ={0, 0, size.X-1, 0};
    WriteConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);

    return;
}


/**
 * ��������: RunSys
 * ��������: ����ϵͳ, ��ϵͳ�������������û���ѡ��Ĺ���ģ��.
 * �������: ��
 * �������: phead ����ͷָ��ĵ�ַ
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void RunSys(ROAD_DATA **phead)
{
    INPUT_RECORD inRec;
    DWORD res;       //double word -> unsigned long
    COORD pos = {0, 0};
    BOOL bRet = TRUE;
    int i, loc, num;
    int cNo, cAtt;      /*cNo:�ַ���Ԫ���, cAtt:�ַ���Ԫ����*/
    char vkc, asc;      /*vkc:���������, asc:�ַ���ASCII��ֵ*/

    while (bRet)
    {
        /*�ӿ���̨���뻺�����ж�һ����¼*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res); //���ڶ����̻�������¼�

        // win10�ڽ���������ʱ����ѿ���̨ѡ���еĿ���ѡ��Ͳ���ر�

        if (inRec.EventType == MOUSE_EVENT) /*�����¼������¼�����*/
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;  /*��ȡ�������λ��*/
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3; //ȡ��λ�õĲ�� 3 -> 0111
            cAtt = gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2;/*ȡ���ַ���Ԫ����*/
            if (cNo == 0) /*���Ϊ0��������λ��δ�������Ӳ˵�����*/
            {
                /* cAtt > 0 ������λ�ô�������(���˵����ַ���Ԫ)
                 * cAtt != gi_sel_menu ������λ�õ����˵���δ��ѡ��
                 * gp_top_layer->LayerNo > 0 ������ǰ���Ӳ˵�����
                 */
                if (cAtt > 0 && cAtt != gi_sel_menu && gp_top_layer->LayerNo > 0)  //������������������Ļ�
                {
                    PopOff();            /*�رյ������Ӳ˵�*/
                    gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/
                    PopMenu(cAtt);       /*��������������˵����Ӧ���Ӳ˵�*/
                }
            }
            else if (cAtt > 0) /*�������λ��Ϊ�����Ӳ˵��Ĳ˵����ַ���Ԫ*/
            {
                TagSubMenu(cAtt); /*�ڸ��Ӳ˵�������ѡ�б��*/
            }

            //���
            if (inRec.Event.MouseEvent.dwButtonState
                == FROM_LEFT_1ST_BUTTON_PRESSED) /*������������ߵ�һ��*/
            {
                if (cNo == 0) /*���Ϊ0��������λ��δ�������Ӳ˵�����*/
                {
                    if (cAtt > 0) /*�����λ�ô�������(���˵����ַ���Ԫ)*/
                    {
                        PopMenu(cAtt);   /*��������������˵����Ӧ���Ӳ˵�*/
                    }
                    /*�����λ�ò��������˵����ַ���Ԫ�������Ӳ˵�����*/
                    else if (gp_top_layer->LayerNo > 0)
                    {
                        PopOff();            /*�رյ������Ӳ˵�*/
                        gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/
                    }
                }
                else /*��Ų�Ϊ0��������λ�ñ������Ӳ˵�����*/
                {
                    if (cAtt > 0) /*�����λ�ô�������(�Ӳ˵����ַ���Ԫ)*/
                    {
                        PopOff(); /*�رյ������Ӳ˵�*/
                        gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/

                        /*ִ�ж�Ӧ���ܺ���:gi_sel_menu���˵����,cAtt�Ӳ˵����*/
                        bRet = ExeFunction(gi_sel_menu, cAtt);
                    }
                }
            }
            else if (inRec.Event.MouseEvent.dwButtonState
                     == RIGHTMOST_BUTTON_PRESSED) /*�����������Ҽ�*/
            {
                if (cNo == 0) /*���Ϊ0��������λ��δ�������Ӳ˵�����*/
                {
                    PopOff();            /*�رյ������Ӳ˵�*/
                    gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT  /*�����¼�ɰ�������*/
                 && inRec.Event.KeyEvent.bKeyDown) /*�Ҽ�������*/
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode; /*��ȡ�������������*/
            asc = inRec.Event.KeyEvent.uChar.AsciiChar; /*��ȡ������ASC��*/

            /*ϵͳ��ݼ��Ĵ���*/
            if (vkc == 112) /*�������F1��*/
            {
                if (gp_top_layer->LayerNo != 0) /*�����ǰ���Ӳ˵�����*/
                {
                    PopOff();            /*�رյ������Ӳ˵�*/
                    gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/
                }
                bRet = ExeFunction(5, 1);  /*���а������⹦�ܺ���*/
            }
            else if (inRec.Event.KeyEvent.dwControlKeyState
                     & (LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED))    //Alt
            { /*������������Alt��*/
                switch (vkc)  /*�ж���ϼ�Alt+��ĸ*/
                {
                    case 88:  /*Alt+X �˳�*/
                        if (gp_top_layer->LayerNo != 0)
                        {
                            PopOff();
                            gi_sel_sub_menu = 0;
                        }
                        bRet = ExeFunction(1,4);
                        break;
                    case 70:  /*Alt+F*/
                        PopMenu(1);
                        break;
                    case 77: /*Alt+M*/
                        PopMenu(2);
                        break;
                    case 81: /*Alt+Q*/
                        PopMenu(3);
                        break;
                    case 83: /*Alt+S*/
                        PopMenu(4);
                        break;
                    case 72: /*Alt+H*/
                        PopMenu(5);
                        break;
                }
            }

            /** \brief �������
             *
             * \param Left Arrow   37  Right Arrow   39
             * \param Up Arrow   38   Down Arrow   40
             * \return
             *
             */

            else if (asc == 0) /*�������Ƽ��Ĵ���*/
            {
                if (gp_top_layer->LayerNo == 0) /*���δ�����Ӳ˵�*/
                {
                    switch (vkc) /*�������(���ҡ���)������Ӧ�������Ƽ�*/
                    {
                        case 37:    //��
                            gi_sel_menu--;
                            if (gi_sel_menu == 0)
                            {
                                gi_sel_menu = 5;
                            }
                            TagMainMenu(gi_sel_menu);
                            break;
                        case 39:   //��
                            gi_sel_menu++;
                            if (gi_sel_menu == 6)
                            {
                                gi_sel_menu = 1;
                            }
                            TagMainMenu(gi_sel_menu);
                            break;
                        case 40://��
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                    }
                }
                else  /*�ѵ����Ӳ˵�ʱ*/
                {
                    for (loc=0,i=1; i<gi_sel_menu; i++)
                    {
                        loc += ga_sub_menu_count[i-1];
                    }  /*������Ӳ˵��еĵ�һ�����Ӳ˵��ַ��������е�λ��(�±�)*/
                    switch (vkc) /*�����(���ҡ��ϡ���)�Ĵ���*/
                    {
                        case 37:
                            gi_sel_menu--;
                            if (gi_sel_menu < 1)
                            {
                                gi_sel_menu = 5;
                            }
                            TagMainMenu(gi_sel_menu);
                            PopOff();
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                        case 38:
                            num = gi_sel_sub_menu - 1;
                            if (num < 1)
                            {
                                num = ga_sub_menu_count[gi_sel_menu-1];
                            }
                            if (strlen(ga_sub_menu[loc+num-1]) == 0)
                            {
                                num--;
                            }
                            TagSubMenu(num);
                            break;
                        case 39:
                            gi_sel_menu++;
                            if (gi_sel_menu > 5)
                            {
                                gi_sel_menu = 1;
                            }
                            TagMainMenu(gi_sel_menu);
                            PopOff();
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                        case 40:
                            num = gi_sel_sub_menu + 1;
                            if (num > ga_sub_menu_count[gi_sel_menu-1])
                            {
                                num = 1;
                            }
                            if (strlen(ga_sub_menu[loc+num-1]) == 0)
                            {
                                num++;
                            }
                            TagSubMenu(num);
                            break;
                    }
                }
            }
            else if ((asc-vkc == 0) || (asc-vkc == 32)){  /*������ͨ��*/
                if (gp_top_layer->LayerNo == 0)  /*���δ�����Ӳ˵�*/
                {
                    switch (vkc)
                    {
                        case 70: /*f��F*/
                            PopMenu(1);
                            break;
                        case 77: /*m��M*/
                            PopMenu(2);
                            break;
                        case 81: /*q��Q*/
                            PopMenu(3);
                            break;
                        case 83: /*s��S*/
                            PopMenu(4);
                            break;
                        case 72: /*h��H*/
                            PopMenu(5);
                            break;
                        case 13: /*�س�*/
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                    }
                }
                else /*�ѵ����Ӳ˵�ʱ�ļ������봦��*/
                {
                    if (vkc == 27) /*�������ESC��*/
                    {
                        PopOff();
                        gi_sel_sub_menu = 0;
                    }
                    else if(vkc == 13) /*������»س���*/
                    {
                        num = gi_sel_sub_menu;
                        PopOff();
                        gi_sel_sub_menu = 0;
                        bRet = ExeFunction(gi_sel_menu, num);
                    }
                    else /*������ͨ���Ĵ���*/
                    {
                        /*������Ӳ˵��еĵ�һ�����Ӳ˵��ַ��������е�λ��(�±�)*/
                        for (loc=0,i=1; i<gi_sel_menu; i++)
                        {
                            loc += ga_sub_menu_count[i-1];
                        }

                        /*�����뵱ǰ�Ӳ˵���ÿһ��Ĵ����ַ����бȽ�*/  //���ڵ������Ӳ˵�����
                        for (i=loc; i<loc+ga_sub_menu_count[gi_sel_menu-1]; i++)
                        {
                            if (strlen(ga_sub_menu[i])>0 && vkc==ga_sub_menu[i][1])
                            { /*���ƥ��ɹ�*/
                                PopOff();
                                gi_sel_sub_menu = 0;
                                bRet = ExeFunction(gi_sel_menu, i-loc+1);
                            }
                        }
                    }
                }
            }
        }
    }
}


/**
 * ��������: PopMenu
 * ��������: ����ָ�����˵����Ӧ���Ӳ˵�.
 * �������: num ָ�������˵����
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void PopMenu(int num)
{
    LABEL_BUNDLE labels;   //���Ƶ�
    HOT_AREA areas;
    SMALL_RECT rcPop; //����
    COORD pos;
    WORD att; //��ɫ
    //char *pCh;
    //int j;
    int i, loc = 0;

    if (num != gi_sel_menu)       /*���ָ�����˵�������ѡ�в˵�*/
    {
        if (gp_top_layer->LayerNo != 0) /*�����ǰ�����Ӳ˵�����*/
        {
            PopOff();
            gi_sel_sub_menu = 0;
        }
    }
    else if (gp_top_layer->LayerNo != 0) /*���ѵ������Ӳ˵����򷵻�*/
    {
        return;
    }

    gi_sel_menu = num;    /*��ѡ�����˵�����Ϊָ�������˵���*/   //��ѡ�е����˵�
    TagMainMenu(gi_sel_menu); /*��ѡ�е����˵����������*/  //zhu
    LocSubMenu(gi_sel_menu, &rcPop); /*���㵯���Ӳ˵�������λ��, �����rcPop��*/

    /*������Ӳ˵��еĵ�һ�����Ӳ˵��ַ��������е�λ��(�±�)*/
    for (i=1; i<gi_sel_menu; i++)
    {
        loc += ga_sub_menu_count[i-1];   //�Ӳ˵�����
    }
    /*�������Ӳ˵������������ǩ���ṹ����*/
    labels.ppLabel = ga_sub_menu + loc;   /*��ǩ����һ����ǩ�ַ����ĵ�ַ*/
    labels.num = ga_sub_menu_count[gi_sel_menu-1]; /*��ǩ���б�ǩ�ַ����ĸ���*/
    COORD aLoc[labels.num];/*����һ���������飬���ÿ����ǩ�ַ������λ�õ�����*/  //λ��
    for (i=0; i<labels.num; i++) /*ȷ����ǩ�ַ��������λ�ã����������������*/
    {
        aLoc[i].X = rcPop.Left + 2;
        aLoc[i].Y = rcPop.Top + i + 1;
    }
    labels.pLoc = aLoc; /*ʹ��ǩ���ṹ����labels�ĳ�ԱpLocָ�������������Ԫ��*/
    /*����������Ϣ*/
    areas.num = labels.num;       /*�����ĸ��������ڱ�ǩ�ĸ��������Ӳ˵�������*/
    SMALL_RECT aArea[areas.num];                    /*������������������λ��*/
    char aSort[areas.num];                      /*��������������������Ӧ���*/
    char aTag[areas.num];                         /*����������ÿ�������ı��*/
    for (i=0; i<areas.num; i++)
    {
        aArea[i].Left = rcPop.Left + 2;  /*������λ*/
        aArea[i].Top = rcPop.Top + i + 1;
        aArea[i].Right = rcPop.Right - 2;
        aArea[i].Bottom = aArea[i].Top;
        aSort[i] = 0;       /*�������Ϊ0(��ť��)*/
        aTag[i] = i + 1;           /*������˳����*/
    }
    areas.pArea = aArea;/*ʹ�����ṹ����areas�ĳ�ԱpAreaָ������λ��������Ԫ��*/
    areas.pSort = aSort;/*ʹ�����ṹ����areas�ĳ�ԱpSortָ���������������Ԫ��*/
    areas.pTag = aTag;   /*ʹ�����ṹ����areas�ĳ�ԱpTagָ���������������Ԫ��*/

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
    PopUp(&rcPop, att, &labels, &areas);
    DrawBox(&rcPop);  /*���������ڻ��߿�*/

//    pos.X = rcPop.Left + 2;
//    for (pos.Y=rcPop.Top+1; pos.Y<rcPop.Bottom; pos.Y++)
//    { /*��ѭ�������ڿմ��Ӳ���λ�û����γɷָ�����ȡ���˲˵������������*/
//        pCh = ga_sub_menu[loc+pos.Y-rcPop.Top-1];
//        if (strlen(pCh)==0) /*����Ϊ0������Ϊ�մ�*/
//        {   /*���Ȼ�����*/
//            //FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-3, pos, &ul);
//            for (j=rcPop.Left+2; j<rcPop.Right-1; j++)
//            {   /*ȡ���������ַ���Ԫ����������*/
//                gp_scr_att[pos.Y*SCR_COL+j] &= 3; /*��λ��Ľ�������˵���λ*/
//            }
//        }
//
//    }
    /*���Ӳ˵���Ĺ��ܼ���Ϊ�׵׺���*/
    pos.X = rcPop.Left + 3;
    att =  FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
    for (pos.Y=rcPop.Top+1; pos.Y<rcPop.Bottom; pos.Y++)
    {
//        if (strlen(ga_sub_menu[loc+pos.Y-rcPop.Top-1])==0)
//        {
//            continue;  /*�����մ�*/
//        }
        FillConsoleOutputAttribute(gh_std_out, att, 1, pos, &ul);
    }
    return;
}

/**
 * ��������: PopUp
 * ��������: ��ָ�������������������Ϣ, ͬʱ��������, ����������λ����Ϣ��ջ.
 * �������: pRc ��������λ�����ݴ�ŵĵ�ַ
 *           att �������������ַ����� ��ɫ
 *           pLabel ���������б�ǩ����Ϣ��ŵĵ�ַ
             pHotArea ����������������Ϣ��ŵĵ�ַ
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void PopUp(SMALL_RECT *pRc, WORD att, LABEL_BUNDLE *pLabel, HOT_AREA *pHotArea)
{
    LAYER_NODE *nextLayer;
    COORD size;
    COORD pos = {0, 0};
    char *pCh;
    int i, j, row;

    /*������������λ���ַ���Ԫ��Ϣ��ջ*/
    size.X = pRc->Right - pRc->Left + 1;    /*�������ڵĿ��*/
    size.Y = pRc->Bottom - pRc->Top + 1;    /*�������ڵĸ߶�*/
    /*�����ŵ������������Ϣ�Ķ�̬�洢��*/
    nextLayer = (LAYER_NODE *)malloc(sizeof(LAYER_NODE));
    nextLayer->next = gp_top_layer;
    nextLayer->LayerNo = gp_top_layer->LayerNo + 1;
    nextLayer->rcArea = *pRc;
    nextLayer->pContent = (CHAR_INFO *)malloc(size.X*size.Y*sizeof(CHAR_INFO));
    nextLayer->pScrAtt = (char *)malloc(size.X*size.Y*sizeof(char));
    pCh = nextLayer->pScrAtt;
    /*���������ڸ���������ַ���Ϣ���棬�����ڹرյ�������ʱ�ָ�ԭ��*/
    ReadConsoleOutput(gh_std_out, nextLayer->pContent, size, pos, pRc);
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {   /*�˶���ѭ�����������ַ���Ԫ��ԭ������ֵ���붯̬�洢���������Ժ�ָ�*/
        for (j=pRc->Left; j<=pRc->Right; j++)
        {
            *pCh = gp_scr_att[i*SCR_COL+j];
            pCh++;
        }
    }
    gp_top_layer = nextLayer;  /*��ɵ������������Ϣ��ջ����*/
    /*���õ������������ַ���������*/
    pos.X = pRc->Left;
    pos.Y = pRc->Top;
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {
        FillConsoleOutputAttribute(gh_std_out, att, size.X, pos, &ul);
        pos.Y++;
    }
    /*����ǩ���еı�ǩ�ַ������趨��λ�����*/
    for (i=0; i<pLabel->num; i++)
    {
        pCh = pLabel->ppLabel[i];
        if (strlen(pCh) != 0)
        {
            WriteConsoleOutputCharacter(gh_std_out, pCh, strlen(pCh),   // ��ָ��λ�ô�����ָ���������ַ�
                                        pLabel->pLoc[i], &ul);
        }
    }
    /*���õ������������ַ���Ԫ��������*/
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {   /*�˶���ѭ�������ַ���Ԫ�Ĳ��*/
        for (j=pRc->Left; j<=pRc->Right; j++)
        {
            gp_scr_att[i*SCR_COL+j] = gp_top_layer->LayerNo;
        }
    }

    for (i=0; i<pHotArea->num; i++)
    {   /*�˶���ѭ�����������������ַ���Ԫ���������ͺ��������*/
        row = pHotArea->pArea[i].Top;
        for (j=pHotArea->pArea[i].Left; j<=pHotArea->pArea[i].Right; j++)
        {
            gp_scr_att[row*SCR_COL+j] |= (pHotArea->pSort[i] << 6)
                                    | (pHotArea->pTag[i] << 2);
        }
    }
    return;
}

/**
 * ��������: PopOff
 * ��������: �رն��㵯������, �ָ���������ԭ��ۺ��ַ���Ԫԭ����.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void PopOff(void)
{
    LAYER_NODE *nextLayer;
    COORD size;
    COORD pos = {0, 0};
    char *pCh;
    int i, j;

    if ((gp_top_layer->next==NULL) || (gp_top_layer->pContent==NULL))
    {   /*ջ�״�ŵ���������Ļ��Ϣ�����ùر�*/
        return;
    }
    nextLayer = gp_top_layer->next;
    /*�ָ�������������ԭ���*/
    size.X = gp_top_layer->rcArea.Right - gp_top_layer->rcArea.Left + 1;
    size.Y = gp_top_layer->rcArea.Bottom - gp_top_layer->rcArea.Top + 1;
    WriteConsoleOutput(gh_std_out, gp_top_layer->pContent, size, pos, &(gp_top_layer->rcArea));
    /*�ָ��ַ���Ԫԭ����*/
    pCh = gp_top_layer->pScrAtt;
    for (i=gp_top_layer->rcArea.Top; i<=gp_top_layer->rcArea.Bottom; i++)
    {
        for (j=gp_top_layer->rcArea.Left; j<=gp_top_layer->rcArea.Right; j++)
        {
            gp_scr_att[i*SCR_COL+j] = *pCh;
            pCh++;
        }
    }
    free(gp_top_layer->pContent);    /*�ͷŶ�̬�洢��*/
    free(gp_top_layer->pScrAtt);
    free(gp_top_layer);
    gp_top_layer = nextLayer;
    gi_sel_sub_menu = 0;
    return;
}

/**
 * ��������: DrawBox
 * ��������: ��ָ�����򻭱߿�.
 * �������: pRc �������λ����Ϣ�ĵ�ַ
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void DrawBox(SMALL_RECT *pRc)
{
    char chBox[] = {'+','-','|'};  /*�����õ��ַ�*/
    COORD pos = {pRc->Left, pRc->Top};  /*��λ����������Ͻ�*/

    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*���߿����Ͻ�*/
    for (pos.X = pRc->Left + 1; pos.X < pRc->Right; pos.X++)
    {   /*��ѭ�����ϱ߿����*/
        WriteConsoleOutputCharacter(gh_std_out, &chBox[1], 1, pos, &ul);
    }
    pos.X = pRc->Right;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*���߿����Ͻ�*/
    for (pos.Y = pRc->Top+1; pos.Y < pRc->Bottom; pos.Y++)
    {   /*��ѭ�����߿�����ߺ��ұ���*/
        pos.X = pRc->Left;
        WriteConsoleOutputCharacter(gh_std_out, &chBox[2], 1, pos, &ul);
        pos.X = pRc->Right;
        WriteConsoleOutputCharacter(gh_std_out, &chBox[2], 1, pos, &ul);
    }
    pos.X = pRc->Left;
    pos.Y = pRc->Bottom;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*���߿����½�*/
    for (pos.X = pRc->Left + 1; pos.X < pRc->Right; pos.X++)
    {   /*���±߿����*/
        WriteConsoleOutputCharacter(gh_std_out, &chBox[1], 1, pos, &ul);
    }
    pos.X = pRc->Right;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*���߿����½�*/
    return;
}

/**
 * ��������: TagSubMenu
 * ��������: ��ָ���Ӳ˵�������ѡ�б��.
 * �������: num ѡ�е��Ӳ˵����
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void TagSubMenu(int num)
{
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int width;

    LocSubMenu(gi_sel_menu, &rcPop);  /*���㵯���Ӳ˵�������λ��, �����rcPop��*/
    if ((num<1) || (num == gi_sel_sub_menu) || (num>rcPop.Bottom-rcPop.Top-1))
    {   /*����Ӳ˵����Խ�磬������Ӳ˵��ѱ�ѡ�У��򷵻�*/
        return;
    }

    pos.X = rcPop.Left + 2;
    width = rcPop.Right - rcPop.Left - 3;
    if (gi_sel_sub_menu != 0) /*����ȡ��ԭѡ���Ӳ˵����ϵı��*/
    {
        pos.Y = rcPop.Top + gi_sel_sub_menu;
        att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
        FillConsoleOutputAttribute(gh_std_out, att, width, pos, &ul);
        pos.X += 1;
        att |=  FOREGROUND_RED;/*�׵׺���*/
        FillConsoleOutputAttribute(gh_std_out, att, 1, pos, &ul);
    }
    /*���ƶ��Ӳ˵�������ѡ�б��*/
    pos.X = rcPop.Left + 2;
    pos.Y = rcPop.Top + num;
    att = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;  /*�ڵװ���*/
    FillConsoleOutputAttribute(gh_std_out, att, width, pos, &ul);
    gi_sel_sub_menu = num;  /*�޸�ѡ���Ӳ˵����*/
    return;
}

/**
 * ��������: LocSubMenu
 * ��������: ���㵯���Ӳ˵��������ϽǺ����½ǵ�λ��.
 * �������: num ѡ�е����˵����
 * �������: rc �������λ����Ϣ�ĵ�ַ
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void LocSubMenu(int num, SMALL_RECT *rc)
{
    int i, len, loc = 0;

    rc->Top = 1; /*������ϱ߶��ڵ�2�У��к�Ϊ1*/
    rc->Left = 1;
    for (i=1; i<num; i++)
    {   /*����������߽�λ��, ͬʱ�����һ���Ӳ˵������Ӳ˵��ַ��������е�λ��*/
        rc->Left += strlen(ga_main_menu[i-1]) + 4;
        loc += ga_sub_menu_count[i-1];
    }
    rc->Right = strlen(ga_sub_menu[loc]);/*��ʱ��ŵ�һ���Ӳ˵����ַ�������*/
    for (i=1; i<ga_sub_menu_count[num-1]; i++)
    {   /*������Ӳ˵��ַ��������䳤�ȴ����rc->Right*/
        len = strlen(ga_sub_menu[loc+i]);
        if (rc->Right < len)
        {
            rc->Right = len;
        }
    }
    rc->Right += rc->Left + 3;  /*����������ұ߽�*/
    rc->Bottom = rc->Top + ga_sub_menu_count[num-1] + 1;/*���������±ߵ��к�*/
    if (rc->Right >= SCR_COL)  /*�ұ߽�Խ��Ĵ���*/
    {
        len = rc->Right - SCR_COL + 1;
        rc->Left -= len;
        rc->Right = SCR_COL - 1;
    }
    return;
}

/**
 * ��������: DealInput
 * ��������: �ڵ�������������������, �ȴ�����Ӧ�û�����.
 * �������: pHotArea
 *           piHot ����������ŵĴ�ŵ�ַ, ��ָ�򽹵�������ŵ�ָ��
 * �������: piHot ����굥�������س���ո�ʱ���ص�ǰ�������
 * �� �� ֵ:
 *
 * ����˵��:
 */
int DealInput(HOT_AREA *pHotArea, int *piHot)
{
    INPUT_RECORD inRec;
    DWORD res;
    COORD pos = {0, 0};
    int num, arrow, iRet = 0;
    int cNo, cTag, cSort,cAtt;/*cNo:���, cTag:�������, cSort: ��������*/
    char vkc, asc;       /*vkc:���������, asc:�ַ���ASCII��ֵ*/

    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    /*ѭ��*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res); //�ӿ���̨���뻺�����ж�һ����¼

        if (inRec.EventType == MOUSE_EVENT) /*�����¼������¼�����*/
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;  /*��ȡ�������λ��*/
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3; /*ȡ��λ�õĲ��*/
            cTag = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2) & 15;
            cSort = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 6) & 3;
            cAtt = gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2;/*ȡ���ַ���Ԫ����*/
            if (cAtt > 0) /*�������λ��Ϊ�����Ӳ˵��Ĳ˵����ַ���Ԫ*/
            {
                SetHotPoint(pHotArea, cTag);
            }
        }

        if ((inRec.EventType == MOUSE_EVENT) &&
            (inRec.Event.MouseEvent.dwButtonState
             == FROM_LEFT_1ST_BUTTON_PRESSED))  //�������
        {
            if ((cNo == gp_top_layer->LayerNo) && cTag > 0)
            {
                *piHot = cTag;
                SetHotPoint(pHotArea, *piHot);
                if (cSort == 0)
                {
                    iRet = 13;
                    break;
                }
            }
        }

//        if ((inRec.EventType == MOUSE_EVENT) &&
//            (inRec.Event.MouseEvent.dwButtonState
//             == FROM_LEFT_1ST_BUTTON_PRESSED))  //�������
//        {
//            pos = inRec.Event.MouseEvent.dwMousePosition;
//            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3;
//            cTag = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2) & 15;
//            cSort = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 6) & 3;
//
//            if ((cNo == gp_top_layer->LayerNo) && cTag > 0)
//            {
//                *piHot = cTag;
//                SetHotPoint(pHotArea, *piHot);
//                if (cSort == 0)
//                {
//                    iRet = 13;
//                    break;
//                }
//            }
//        }
        else if (inRec.EventType == KEY_EVENT && inRec.Event.KeyEvent.bKeyDown)
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode;
            asc = inRec.Event.KeyEvent.uChar.AsciiChar;;
            if (asc == 0)
            {
                arrow = 0;
                switch (vkc)
                {  /*�����(���ϡ��ҡ���)�Ĵ���*/
                    case 37: arrow = 1; break;
                    case 38: arrow = 2; break;
                    case 39: arrow = 3; break;
                    case 40: arrow = 4; break;
                }
                if (arrow > 0)
                {
                    num = *piHot;
                    while (TRUE)
                    {
                        if (arrow < 3)
                        {
                            num--;
                        }
                        else
                        {
                            num++;
                        }
                        if ((num < 1) || (num > pHotArea->num) ||
                            ((arrow % 2) && (pHotArea->pArea[num-1].Top
                            == pHotArea->pArea[*piHot-1].Top)) || ((!(arrow % 2))
                            && (pHotArea->pArea[num-1].Top
                            != pHotArea->pArea[*piHot-1].Top)))
                        {
                            break;
                        }
                    }
                    if (num > 0 && num <= pHotArea->num)
                    {
                        *piHot = num;
                        SetHotPoint(pHotArea, *piHot);
                    }
                }
            }
            else if (vkc == 27)
            {  /*ESC��*/
                iRet = 27;
                break;
            }
            else if (vkc == 13 || vkc == 32)
            {  /*�س�����ո��ʾ���µ�ǰ��ť*/
                iRet = 13;
                break;
            }
        }
    }
    return iRet;
}

void SetHotPoint(HOT_AREA *pHotArea, int iHot)
{
    CONSOLE_CURSOR_INFO lpCur;
    COORD pos = {0, 0};
    WORD att1, att2;
    int i, width;

    att1 = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;  /*�ڵװ���*/
    att2 = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
    for (i=0; i<pHotArea->num; i++)
    {  /*����ť��������Ϊ�׵׺���*/
        pos.X = pHotArea->pArea[i].Left;
        pos.Y = pHotArea->pArea[i].Top;
        width = pHotArea->pArea[i].Right - pHotArea->pArea[i].Left + 1;
        if (pHotArea->pSort[i] == 0)
        {  /*�����ǰ�ť��*/
            FillConsoleOutputAttribute(gh_std_out, att2, width, pos, &ul);
        }
    }

    pos.X = pHotArea->pArea[iHot-1].Left;
    pos.Y = pHotArea->pArea[iHot-1].Top;
    width = pHotArea->pArea[iHot-1].Right - pHotArea->pArea[iHot-1].Left + 1;
    if (pHotArea->pSort[iHot-1] == 0)
    {  /*�����������ǰ�ť��*/
        FillConsoleOutputAttribute(gh_std_out, att1, width, pos, &ul);
    }
    else if (pHotArea->pSort[iHot-1] == 1)
    {  /*�������������ı�����*/
        SetConsoleCursorPosition(gh_std_out, pos);
        GetConsoleCursorInfo(gh_std_out, &lpCur);
        lpCur.bVisible = TRUE;
        SetConsoleCursorInfo(gh_std_out, &lpCur);   //��������������ʼλ��
    }
}

/**
 * ��������: ShowModule
 * ��������: ����˵������
 * �������: pString �ַ���
 *           n n���ַ�������
 * �������: bRet BOOLֵ
 * �� �� ֵ:
 *
 * ����˵��:
 */

BOOL ShowModule(char **pString, int n)   //n���ַ�������
{
    LABEL_BUNDLE labels; //��ǩ��
    HOT_AREA areas;   //����
    BOOL bRet = TRUE;
    SMALL_RECT rcPop;  //���������ϽǺ����½ǵ������һ�����Ρ�
    COORD pos;  //COORD�Ƕ��������е�����ṹ
    WORD att;  //WORD����unsigned short�������ֽڣ�DWORD����unsigned long���ĸ��ֽڡ� �˴�att���ڱ�ʾ��ɫ
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {       //ȷ���ַ�����󳤶�
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;    //x+6 ����߾�+3 �ұ߾�+3
    pos.Y = n + 6;  //n������
    rcPop.Left = (SCR_COL - pos.X) / 2;  //SCR_COLΪ80 ��LeftΪ�������Ͻǵ�x����
    rcPop.Right = rcPop.Left + pos.X - 1;  //RightΪ�������½�x����
    rcPop.Top = (SCR_ROW - pos.Y) / 2;  //���Ͻǵ�y����
    rcPop.Bottom = rcPop.Top + pos.Y - 1; //���½ǵ�y����

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];   //����ÿ���ַ����ı߾�

    //����λ��
    aLoc[0].X = rcPop.Left + 3;
    aLoc[0].Y = rcPop.Top + 1;

    for (i=1; i<n; i++) {
        aLoc[i].X = rcPop.Left + 3; //�ַ��߾�
        aLoc[i].Y = rcPop.Top + 3 + i; //��λ������һ��
    }

    str_len = strlen(pString[0]);        //�������þ���
    aLoc[0].X = rcPop.Left + 3 + (maxlen-str_len)/2;

    str_len = strlen(pString[n-1]);
    aLoc[n-1].X = rcPop.Left + 3 + (maxlen-str_len)/2;  //����ȷ�����þ���
    aLoc[n-1].Y = aLoc[n-1].Y + 2;  //+2Ϊ���ƿո�ͷָ�������

    labels.pLoc = aLoc;  //��ǩ��λ��

    areas.num = 1;   //��������
    SMALL_RECT aArea[] = {{aLoc[n-1].X, aLoc[n-1].Y,                //ȷ������λ�ã���������С
                           aLoc[n-1].X + 3, aLoc[n-1].Y}};

    char aSort[] = {0};   //���
    char aTag[] = {1};    //���

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;

    //��������
    PopUp(&rcPop, att, &labels, &areas);

    //���������
    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul); //�������������ַ�����

    //�����������
    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 3 + n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul); //�������������ַ�����

    DealInput(&areas, &iHot);
    PopOff();

    return bRet;

}


int PopWindowMenu(char **pString, int n,int areanum, int *tag)
{
    LABEL_BUNDLE labels; //��ǩ��
    HOT_AREA areas;   //����
    SMALL_RECT rcPop;  //���������ϽǺ����½ǵ������һ�����Ρ�
    COORD pos;  //COORD�Ƕ��������е�����ṹ
    WORD att;  //WORD����unsigned short�������ֽڣ�DWORD����unsigned long���ĸ��ֽڡ� �˴�att���ڱ�ʾ��ɫ
    int iRet; //������Ϣ

    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {       //ȷ���ַ�����󳤶�
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;    //x+6 ����߾�+3 �ұ߾�+3
    pos.Y = n + 6;  //n������
    rcPop.Left = (SCR_COL - pos.X) / 2;  //SCR_COLΪ80 ��LeftΪ�������Ͻǵ�x����
    rcPop.Right = rcPop.Left + pos.X - 1;  //RightΪ�������½�x����
    rcPop.Top = (SCR_ROW - pos.Y) / 2;  //���Ͻǵ�y����
    rcPop.Bottom = rcPop.Top + pos.Y - 1; //���½ǵ�y����

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];   //����ÿ���ַ����ı߾�

    //����λ��
    aLoc[0].X = rcPop.Left + 3;
    aLoc[0].Y = rcPop.Top + 1;

    for (i=1; i<n; i++) {
        aLoc[i].X = rcPop.Left + 3; //�ַ��߾�
        aLoc[i].Y = rcPop.Top + 3 + i; //��λ������һ��
    }

    str_len = strlen(pString[0]);        //�������þ���
    aLoc[0].X = rcPop.Left + 3 + (maxlen-str_len)/2;

    str_len = strlen(pString[n-1]);
    aLoc[n-1].X = rcPop.Left + 3 + (maxlen-str_len)/2;  //����ȷ�����þ���
    aLoc[n-1].Y = aLoc[n-1].Y + 2;  //+2Ϊ���ƿո�ͷָ�������

    labels.pLoc = aLoc;  //��ǩ��λ��

    //������Ϣ
    areas.num = areanum ;   //�����ĸ���
    SMALL_RECT aArea[areas.num];                    /*������������������λ��*/
    char aSort[areas.num];                      /*��������������������Ӧ���*/
    char aTag[areas.num];                         /*����������ÿ�������ı��*/
    for (i=0; i<areas.num-1; i++)
    {
        aArea[i].Left = rcPop.Left + 3;  /*������λ*/
        aArea[i].Top = rcPop.Top + i + 4;
        aArea[i].Right = rcPop.Right - 3;
        aArea[i].Bottom = aArea[i].Top;
        aSort[i] = 0;       /*�������Ϊ0(��ť��)*/
        aTag[i] = i + 1;           /*������˳����*/
    }
    aArea[areas.num-1].Left = rcPop.Left + 3 + (maxlen-str_len)/2;;  /*������λ*/
    aArea[areas.num-1].Top = aLoc[n-1].Y ;
    aArea[areas.num-1].Right = aArea[areas.num-1].Left+ strlen(pString[n-1])-1;
    aArea[areas.num-1].Bottom = aArea[areas.num-1].Top;
    aSort[areas.num-1] = 0;       /*�������Ϊ0(��ť��)*/
    aTag[areas.num-1] = areas.num;           /*������˳����*/

    areas.pArea = aArea;/*ʹ�����ṹ����areas�ĳ�ԱpAreaָ������λ��������Ԫ��*/
    areas.pSort = aSort;/*ʹ�����ṹ����areas�ĳ�ԱpSortָ���������������Ԫ��*/
    areas.pTag = aTag;   /*ʹ�����ṹ����areas�ĳ�ԱpTagָ���������������Ԫ��*/
        //��������
    PopUp(&rcPop, att, &labels, &areas);

    //���������
    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul); //�������������ַ�����

    //�����������
    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 3 + n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul); //�������������ַ�����

    iRet = DealInput(&areas, tag);

    return iRet;
}

/**
 * ��������: PopTextBox
 * ��������: �����ı���.
 * �������: hot ����ǰ״̬
 *          1 ֻ��ȷ��
 *          2 ֻ��ȷ�� ��һҳ
 *          3 ����
 *          4 ȷ�� ��һҳ
 * �������: ��
 * �� �� ֵ: ����iRet�ǰ���ֵ��tag�Ǳ�ǩλ��
 *
 * ����˵��: �ܹ���24��
 */

int PopTextBox(char **ppstring, int hot, int *tag)
{
    HOT_AREA areas;   //����
    SMALL_RECT rcPop;  //���������ϽǺ����½ǵ������һ�����Ρ�
    COORD pos;  //COORD�Ƕ��������е�����ṹ
    int iRet; //������Ϣ
    WORD att;  //WORD����unsigned short�������ֽڣ�DWORD����unsigned long���ĸ��ֽڡ� �˴�att���ڱ�ʾ��ɫ
    LABEL_BUNDLE labels; //��ǩ��
    int i;

    char *str[] = {"ȷ��","��һҳ","��һҳ" };
    att =   BACKGROUND_BLUE |
            FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;  /*���׻���*/

    rcPop.Left =0;
    rcPop.Top = 2;
    rcPop.Right = SCR_COL-1;
    rcPop.Bottom = SCR_ROW-3;

    GotoXY(40,1);   //�ƶ���ǩλ��
    printf("%s",*ppstring);

    COORD aLoc[3];   //��λ��ǩ��λ��
    for(i=0;i<3;i++)
    {
        aLoc[i].X = 40 + i*10;
        aLoc[i].Y = SCR_ROW - 2;
    }

    pos.X=40;
    pos.Y=SCR_ROW-2;

    labels.num = 4;
    labels.ppLabel = str;
    labels.pLoc = aLoc;

    DrawBox(&rcPop);

    switch (hot)   //��������
    {
    case 1:
        areas.num = 1;
        SMALL_RECT aArea1[]={{pos.X, pos.Y, pos.X+3, pos.Y}};
        char aSort1[] = {0};
        char aTag1[] = {1};
        areas.pArea = aArea1;
        areas.pSort = aSort1;
        areas.pTag = aTag1;
        break;
    case 2:
        areas.num = 2;
        SMALL_RECT aArea2[]= {{pos.X, pos.Y, pos.X+3, pos.Y},
                              {pos.X+10, pos.Y, pos.X+10+5, pos.Y}};
        char aSort2[] = {0, 0};
        char aTag2[] = {1, 2};
        areas.pArea = aArea2;
        areas.pSort = aSort2;
        areas.pTag = aTag2;
        break;
    case 3:
        areas.num = 3;
        SMALL_RECT aArea3[]= {{pos.X, pos.Y, pos.X+3, pos.Y},
                                {pos.X+10, pos.Y, pos.X+10+5, pos.Y},
                                {pos.X+20, pos.Y, pos.X+20+5, pos.Y}};
        char aSort3[] = {0, 0, 0};
        char aTag3[] = {1, 2, 3};
        areas.pArea = aArea3;
        areas.pSort = aSort3;
        areas.pTag = aTag3;
        break;
    default:
        areas.num = 2;
        SMALL_RECT aArea4[]= {{pos.X, pos.Y, pos.X+3, pos.Y},
                                {pos.X+20, pos.Y, pos.X+20+5, pos.Y}};
        char aSort4[] = {0, 0};
        char aTag4[] = {1, 2};
        areas.pArea = aArea4;
        areas.pSort = aSort4;
        areas.pTag = aTag4;
        break;
    }

    rcPop.Bottom = SCR_ROW-1;
    PopUp(&rcPop,att,&labels,&areas);
    ShowState();
    iRet = DealInput(&areas,tag);   //������Ϣ

    return iRet;
}


int PopPrompt(char** ppString, int* iHot)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    char *pCh[2];
    char Ch[]="ȷ��    ȡ��";
    pCh[0]=*ppString;
    pCh[1]= Ch;
    int iRet;

    pos.X = strlen(pCh[0]) + 6;
    pos.Y = 7;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
    labels.num = 2;
    labels.ppLabel = pCh;
    COORD aLoc[] = {{rcPop.Left+3, rcPop.Top+2},
                    {rcPop.Left+5, rcPop.Top+5}};
    labels.pLoc = aLoc;

    areas.num = 2;
    SMALL_RECT aArea[] = {{rcPop.Left + 5, rcPop.Top + 5,
                           rcPop.Left + 8, rcPop.Top + 5},
                          {rcPop.Left + 13, rcPop.Top + 5,
                           rcPop.Left + 16, rcPop.Top + 5}};
    char aSort[] = {0, 0};
    char aTag[] = {1, 2};
    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 4;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    iRet = DealInput(&areas, iHot);

    return iRet;
}








BOOL ExeFunction(int m, int s)
{
    BOOL bRet = TRUE;
    /*����ָ�����飬����������й��ܺ�������ڵ�ַ*/
    BOOL (*pFunction[ga_sub_menu_count[0]+ga_sub_menu_count[1]+ga_sub_menu_count[2]+ga_sub_menu_count[3]+ga_sub_menu_count[4]])(void);
    int i, loc;

    /*�����ܺ�����ڵ�ַ�����빦�ܺ����������˵��ź��Ӳ˵��Ŷ�Ӧ�±������Ԫ��*/
    pFunction[0] = SaveData;
    pFunction[1] = BackupData;
    pFunction[2] = RestoreData;
    pFunction[3] = ExitSys;

    pFunction[4] = StationCode;
    pFunction[5] = RoodCoad;
    pFunction[6] = TruckCode;

    pFunction[7] = FindStationRoad;
    pFunction[8] = FindRoadTime;
    pFunction[9] = FindRoadDistance;
    pFunction[10] = FindRoad;
    pFunction[11] = FindWeight;
    pFunction[12] = FindDriverGoods;
    pFunction[13] = FindDriverPhone;
    pFunction[14] = FindTruck;

    pFunction[15] = FormCreate;
    pFunction[16] = TransportMap;

    pFunction[17] = HelpTopic;
    pFunction[18] = About;

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
        /////
        bRet = TRUE;
    }
    else
    {
        bRet = TRUE;
    }
    PopOff();


    return bRet;
}

BOOL BackupData(void)
{
    char *pCh = "ȷ�ϱ���������";
    int iHot = 1;
    int sRet;
    BOOL bRet;

    sRet = PopPrompt(&pCh, &iHot);
    if (sRet == 13 && iHot == 1)
    {
        /////
        bRet = TRUE;
    }
    else
    {
        bRet = TRUE;
    }
    PopOff();
    return bRet;
}

BOOL RestoreData(void)
{
    char *pCh= "ȷ�ϻָ�������";
    int iHot = 1;
    int sRet;
    BOOL bRet;

    sRet = PopPrompt(&pCh, &iHot);
    if (sRet == 13 && iHot == 1)
    {
        /////
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
                           "����"
                          };

    int sTag = 1;
    int sRet;

    sRet = PopWindowMenu(plabel_name, 3, 2, &sTag); //��������
    if(sRet == 13 && sTag==1)
    {
        PopOff();
        EditTruck();
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
    char plabel_name[20] ;

    printf("\n\n\t\tdsfsdfdfs");
    getch();
    scanf("%s",plabel_name);
    printf("\n%s",plabel_name);
    getch();
    ReFresh();

    return bRet;
}

BOOL FindRoadTime(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵��ѧ��������Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    return bRet;
}

BOOL FindRoadDistance(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵��ס�޽ɷ���Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    return bRet;
}

BOOL FindRoad(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵���Ա����",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    return bRet;
}

BOOL FindWeight(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵��ѧ��������",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    return bRet;
}

BOOL FindDriverGoods(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵��ѧ��������",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    return bRet;
}

BOOL FindDriverPhone(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵������¥��Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    return bRet;
}

BOOL FindTruck(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵��ѧ��������Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    return bRet;
}

BOOL FormCreate(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵��ס�޽ɷ���Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    return bRet;
}

BOOL TransportMap(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵������¥��ס��",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    return bRet;
}

BOOL StatStuType(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵����סѧ������",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    return bRet;
}

BOOL StatCharge(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵��ס�޷ѽ������",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    return bRet;
}

BOOL StatUncharge(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵��ס�޷�Ƿ�����",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

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
                           "",
                           "Attention: ��������ʱ��ע�⽫����̨�����е� ����ѡ�� �رգ�",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 8);

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
    printf("\n\t\t������ó���������");
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
    printf("\n\t\t�밴��ʽ �������� ���� ���룡\n\n");
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
        ptruck->volume = proad->station->truck->volume;
        ptruck->left_volume = fvolume_up + fvolume;
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
        printf("\n\t\t�������ƣ�%s\t������ж��������",pgoods_find->name);
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
            printf("\n\t\t�������ƣ�%s\t������ж��������",pgoods_find->name);
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
    printf("\n\n\t\t·��ȫվ�������ܺ�ʱ��%.2f",ftime);
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
    printf("\n\n\t\tȫվ�������ܺ�ʱ:%.2f",proad->full_time);
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
                printf("\n\n\t\tȫվ�������ܺ�ʱ:%.2f",proad->full_time);
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
                printf("\n\n\t����������:%.2f",ptruck->volume);
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
                    printf("\n\t\t%d\t\t%s\t\t%.2f",pgoods->number,pgoods->name,pgoods->quantity);
                    pgoods = pgoods->next;
                }
                printf("\n\t\t����������%.2f,ʣ������:%.2f",ptruck->volume,ptruck->left_volume);

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
                    printf("\n\t\t%d\t\t%s\t\t%.2f",pgoods->number,pgoods->name,pgoods->quantity);
                    pgoods = pgoods->next;
                }
                printf("\n\t\t����������%.2f,ʣ������:%.2f",ptruck->volume,ptruck->left_volume);

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
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵��ס�޷�Ƿ�����",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    return bRet;
}


BOOL EditTruck(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵��ס�޷�Ƿ�����",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    return bRet;
}

BOOL EditRoadBase(void)
{
    BOOL bRet = TRUE;
    ROAD_DATA *proad;
    int key;
    char fname[6];

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

    Show_Cursor(FALSE);
    printf("\n\n\t\tɾ���ɹ��� �����������");
    getch();
    ReFresh();


    return bRet;

}

BOOL InsertGoods(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵��ס�޷�Ƿ�����",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    return bRet;
}




