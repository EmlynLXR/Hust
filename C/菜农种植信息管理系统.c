#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wincon.h>
#include <conio.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <ctype.h>
#include <time.h>

#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED

#define SCR_ROW 25                                  /*屏幕行数*/
#define SCR_COL 80                                  /*屏幕列数*/

/*菜农种植信息链结点结构*/
typedef struct ve_p_info {
	int n;                                          /*蔬菜种植信息编号*/
	int num;                                        /*蔬菜基本信息中的蔬菜编号*/
	char type;                                      /*蔬菜分类编码*/
	int area;                                       /*种植面积*/
	float h;                                        /*收获重量*/
	char name[20];                                  /*蔬菜名称*/
	char year[5];                                   /*种植年份*/
	struct ve_p_info *next;                         /*指向下一结点的指针*/
}P;

/*蔬菜基本信息链中分支出的营养成分信息链结点结构*/
typedef struct ve_b_nutri_info{
    char type;                                      /*蔬菜分类编码*/
    char n[20];                                     /*营养成分的名称*/
    int num;                                        /*蔬菜基本信息中的蔬菜编号*/
    struct ve_b_nutri_info *next;                   /*指向下一结点的指针*/
}N;

/*蔬菜基本信息链结点结构*/
typedef struct ve_b_info {
	char type;                                      /*蔬菜分类编码*/
	int num;                                        /*蔬菜编号*/
	char name[20];                                  /*蔬菜名称*/
	struct ve_b_info *next;                         /*指向下一结点的指针*/
    struct ve_b_nutri_info *snext;                  /*指向营养成分支链的指针*/
	struct ve_p_info *cnext;                        /*指向种植信息支链的指针*/
}B;

/*蔬菜种类信息链结点结构*/
typedef struct ve_t_info {
	char type;                                      /*分类编码*/
	char name[8];                                   /*分类名称*/
	struct ve_t_info *next;                         /*指向下一结点的指针*/
	struct ve_b_info *snext;                        /*指向基本信息支链的指针*/
}T;

/*某年种植各类蔬菜种植信息链结点结构*/
struct y_p{
    char name[20];                                  /*蔬菜名称*/
	char type;                                      /*分类编码*/
	int area;                                       /*种植面积*/
	float h;                                        /*收获重量*/
	struct y_p *next;                               /*指向下一结点的指针*/
};

/*起止年间各种类蔬菜种植信息*/
struct s_e_t{
    char name[20];                                  /*蔬菜名称*/
	char type;                                      /*分类编码*/
    int area;                                       /*种植面积*/
    float h;                                        /*收获重量*/
    struct s_e_t *next;                             /*指向下一结点的指针*/
};

/*起止年份间蔬菜种植信息链结点结构*/
struct s_e_p {
	char ve_name[20];                               /*蔬菜名称*/
	char t_name[20];                                /*分类名称*/
	int area;                                       /*种植面积*/
	float h;                                        /*收获重量*/
	struct s_e_p *next;                             /*指向下一结点的指针*/
};

/*蔬菜已有数量信息链结点结构*/
struct v_count {
	char name[8];                                   /*分类名称*/
	char type;                                      /*分类编码*/
	float h;                                        /*收获重量*/
	struct v_count *next;                           /*指向下一结点的指针*/
};

/*屏幕窗口信息链结点结点结构*/
typedef struct layer_node {
    char LayerNo;                                   /*弹出窗口层数*/
    SMALL_RECT rcArea;                              /*弹出窗口区域坐标*/
    CHAR_INFO *pContent;                            /*弹出窗口区域字符单元原信息存储缓冲区*/
    char *pScrAtt;                                  /*弹出窗口区域字符单元原属性值存储缓冲区*/
    struct layer_node *next;                        /*指向下一结点的指针*/
} LAYER_NODE;

/*标签束结构*/
typedef struct labe1_bundle {
    char **ppLabel;                                 /*标签字符串数组首地址*/
    COORD *pLoc;                                    /*标签定位数组首地址*/
    int num;                                        /*标签个数*/
} LABEL_BUNDLE;

/*热区结构*/
typedef struct hot_area {
    SMALL_RECT *pArea;                              /*热区定位数组首地址*/
    char *pSort;                                    /*热区类别(按键、文本框、选项框)数组首地址*/
    char *pTag;                                     /*热区序号数组首地址*/
    int num;                                        /*热区个数*/
} HOT_AREA;

LAYER_NODE *gp_top_layer = NULL;                    /*弹出窗口信息链链头*/
T *gp_head = NULL;                                  /*主链头指针*/

char *gp_sys_name = "菜农种植信息管理系统";         /*系统名称*/
char *gp_ve_p_info_filename = "ve_plant.dat";       /*菜农种植信息数据文件*/
char *gp_ve_b_info_filename = "ve_info.dat";        /*蔬菜基本信息数据文件*/
char *gp_ve_b_nutri_info_filename = "ve_nutri.dat"; /*蔬菜基本信息中营养成分信息的数据文件*/
char *gp_ve_t_info_filename = "ve_type.dat";        /*蔬菜种类信息数据文件*/

char *ga_main_menu[] = { "文件(F)",                 /*系统主菜单名*/
                         "数据维护(M)",
                         "数据查询(Q)",
                         "数据统计(S)",
                         "帮助(H)"
                       };

char *ga_sub_menu[] = { "[S] 数据保存",             /*系统子菜单名*/
                        "[B] 数据备份",
                        "[R] 数据恢复",
                        "[X] 退出    Alt+X",

                        "[T] 蔬菜种类信息",
                        "[B] 蔬菜基本信息",
                        "[P] 蔬菜种植信息",

                        "[T] 蔬菜种类信息",
                        "[B] 蔬菜基本信息",
                        "[P] 菜农种植信息",

                        "[Y] 某年各种类蔬菜种植信息",
                        "[S] 起止年间各种类蔬菜种植信息",
                        "[T] 起止年间各蔬菜种植信息",
                        "[C] 蔬菜已有数量",
                        "[V] 含有某种营养的蔬菜",

                        "[H] 帮助主题",
                        "[A] 关于..."
                      };
int ga_sub_menu_count[] = { 4, 3, 3, 5, 2 };        /*各主菜单项下子菜单的个数*/
int gi_sel_menu = 1;                                /*被选中的主菜单项号,初始为1*/
int gi_sel_sub_menu = 0;                            /*被选中的子菜单项号,初始为0,表示未选中*/

CHAR_INFO *gp_buff_menubar_info = NULL;             /*存放菜单条屏幕区字符信息的缓冲区*/

char *gp_scr_att = NULL;                            /*存放屏幕上字符单元属性值的缓冲区*/
char gc_sys_state = '\0';                           /*用来保存系统状态的字符*/

HANDLE gh_std_out;                                  /*标准输出设备句柄*/
HANDLE gh_std_in;                                   /*标准输入设备句柄*/

BOOL LoadData(void);                                /*数据加载*/
int CreatList(T **pphead);                          /*数据链表初始化*/
void InitInterface(void);                           /*系统界面初始化*/
void ClearScreen(void);                             /*清屏*/
void ShowMenu(void);                                /*显示菜单栏*/
void PopMenu(int num);                              /*显示下拉菜单*/
void PopPrompt(int num);                            /*显示弹出窗口*/
void PopUp(SMALL_RECT *, WORD, LABEL_BUNDLE *, HOT_AREA *);  /*弹出窗口屏幕信息维护*/
void PopOff(void);                                  /*关闭顶层弹出窗口*/
void DrawBox(SMALL_RECT *parea);                    /*绘制边框*/
void LocSubMenu(int num, SMALL_RECT *parea);        /*主菜单下拉菜单定位*/
void TagMainMenu(int num);                          /*标记被选中的主菜单项*/
void TagSubMenu(int num);                           /*标记被选中的子菜单项*/
int DealConInput(HOT_AREA *phot_area, int *pihot_num);  /*控制台输入处理*/
int DealInput(HOT_AREA *pHotArea, int *piHot);
void SetHotPoint(HOT_AREA *phot_area, int hot_num); /*设置热区*/
void RunSys(T **pphd);                              /*系统功能模块的选择和运行*/
BOOL ExeFunction(int main_menu_num, int sub_menu_num);  /*功能模块的调用*/
void CloseSys(T *phd);                              /*退出系统*/

BOOL ShowModule(char **pString, int n);             /*设置热区，显示创建窗口*/
int ShowModule2(char **pString, int n);             /*设置热区，并根据返回值调用功能函数*/
int ShowModule3(char **pString, int n);             /*设置热区，并根据返回值调用功能函数*/
int ShowModule4(char **pString, int n);             /*设置热区，并根据返回值调用功能函数*/
int ShowModule5(char **pString, int n);             /*设置热区，并根据返回值调用功能函数*/

void Update(void);                                  /*更新蔬菜编号*/
void UpdateNum(void);                               /*更新种植信息编号*/

BOOL SaveData(void);                                /*显示数据保存窗口*/
BOOL SaveSysData(T *hd);                            /*保存系统数据*/
BOOL BackupData(void);                              /*显示数据备份窗口*/
BOOL BackupSysData(T *hd,char* filename);           /*备份系统数据*/
BOOL RestoreData(void);                             /*显示数据恢复窗口*/
BOOL RestoreSysData(T **hd,char* filename);         /*恢复系统数据*/
BOOL ExitSys(void);                                 /*退出系统*/
BOOL SaveData2(void);                               /*退出时提醒是否保存数据文件*/

BOOL MaintainTypeInfo(void);                        /*对蔬菜种类信息进行数据维护*/
void InsertTypeInfo(T *hd);                         /*录入蔬菜种类信息*/
void ModifTypeInfo(T *hd);                          /*修改蔬菜种类信息*/
void DelTypeInfo(T* hd);                            /*删除蔬菜种类信息*/

BOOL MaintainBasicInfo(void);                       /*对蔬菜基本信息进行数据维护*/
void InsertBasicInfo(T *hd);                        /*录入蔬菜基本信息*/
void ModifBasicInfo(T *hd);                         /*修改蔬菜基本信息*/
BOOL ModifName(T *ptype,B *pbasic);                 /*修改蔬菜名称*/
BOOL ModifType(T *ptype,B *pbasic1,B *pbasic2);     /*修改蔬菜分类码*/
BOOL InsertNutri(T *ptype,B *pbasic);               /*录入新的营养成分*/
BOOL ModifNutri(T *ptype,B *pbasic);                /*修改已有的营养成分*/
BOOL DelNutri(T *ptype,B *pbasic);                  /*删除已有的营养成分*/
void DelBasicInfo(T* hd);                           /*删除蔬菜基本信息*/

BOOL MaintainPlantInfo(void);                       /*对蔬菜种植信息进行数据维护*/
void InsertPlantInfo(T *hd);                        /*录入菜农种植信息*/
void ModifPlantInfo(T *hd);                         /*修改菜农种植信息*/
void DelPlantInfo(T* hd);                           /*删除菜农种植信息*/
void SortPlantInfo(P *head,int len);                /*对蔬菜种植信息按种植年份升序排序*/

BOOL QueryTypeInfo(void);                           /*查找蔬菜种类信息*/

BOOL QueryBasicInfo(void);                          /*查找蔬菜基本信息*/
BOOL QueryBasicInfo1(void);                         /*以蔬菜名称中文字符子串为条件查询*/
BOOL QueryBasicInfo2(void);                         /*以分类码和营养成分为条件查询*/

BOOL QueryPlantInfo(void);                          /*查找蔬菜种植信息*/
BOOL QueryPlantInfo1(void);                         /*以蔬菜部分名称和种植年份为条件查询*/
BOOL QueryPlantInfo2(void);                         /*以蔬菜名称为条件查询*/

BOOL StatVePlant(void);                             /*统计某年各类蔬菜种植情况*/
BOOL SortVePlant(struct y_p* head,int len);         /*对某年蔬菜种植情况的统计结果按收获重量降序排序*/

BOOL StatTypeVePlant(void);                         /*起止年间各种类蔬菜种植信息*/
BOOL SortTypeVePlant(struct s_e_t *head,int len);   /*对起止年间各种类蔬菜种植情况的统计结果按收获重量降序排序*/

BOOL StatVePlantTotal(void);                        /*统计起止年间蔬菜种植情况*/
BOOL SortVePlantTotal(struct s_e_p* head,int len);  /*对起止年间蔬菜种植情况的统计结果按收获重量降序排序*/

BOOL StatCount(void);                               /*统计蔬菜已有数量*/
BOOL SortCount(struct v_count*head,int len);        /*对蔬菜已有数量的统计结果按已有数量降序排序*/

BOOL StatVeNutri(void);                             /*统计含有某种营养成分的蔬菜*/

BOOL HelpTopic(void);                               /*帮助主题*/
BOOL AboutDorm(void);                               /*关于程序*/

void location(int x,int y)                          /*确定光标位置*/
{
    COORD pos;
    pos.X=x-1;
    pos.Y=y-1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
#endif /**< TYPE_H_INCLUDED*/
unsigned long ul;

/********
函数名称：ExeFunction
函数功能：执行由主菜单号和子菜单号确定的功能函数
输入参数：m为主菜单项号，s为子菜单项号
输出参数：无
返 回 值：BOOL类型，TRUE或FALSE
           仅在执行函数ExitSys时，才可能返回FALSE，其他情况下总是返回TRUE
调用说明：为了能够以统一的方式调用各功能函数，将这些功能函数的原形设为一致，
           即无参数且返回值为BOOL。返回值为FALSE时，结束程序运行
********/
BOOL ExeFunction(int m, int s)
{
    BOOL bRet = TRUE;
    /*函数指针数组，用来存放所有功能函数的入口地址*/
    BOOL (*pFunction[ga_sub_menu_count[0]+ga_sub_menu_count[1]+ga_sub_menu_count[2]+ga_sub_menu_count[3]+ga_sub_menu_count[4]])(void);
    int i, loc;

    /*将功能函数入口地址存入与功能函数所在主菜单号和子菜单号对应下标的数组元素*/
    pFunction[0] = SaveData;
    pFunction[1] = BackupData;
    pFunction[2] = RestoreData;
    pFunction[3] = ExitSys;

    pFunction[4] = MaintainTypeInfo;
    pFunction[5] = MaintainBasicInfo;
    pFunction[6] = MaintainPlantInfo;

    pFunction[7] = QueryTypeInfo;
    pFunction[8] = QueryBasicInfo;
    pFunction[9] = QueryPlantInfo;

    pFunction[10] = StatVePlant;
    pFunction[11] = StatTypeVePlant;
    pFunction[12] = StatVePlantTotal;
    pFunction[13] = StatCount;
    pFunction[14] = StatVeNutri;

    pFunction[15] = HelpTopic;
    pFunction[16] = AboutDorm;

    for (i=1,loc=0; i<m; i++)                       /*根据主菜单号和子菜单号计算对应下标*/
    {
        loc += ga_sub_menu_count[i-1];
    }
    loc += s - 1;

    if (pFunction[loc] != NULL)
    {
        bRet = (*pFunction[loc])();                 /*用函数指针调用所指向的功能函数*/
    }

    return bRet;
}

/********
函数名称：SaveData
函数功能：显示数据保存窗口
输入参数：无
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL SaveData(void)
{
    BOOL bRet = TRUE;
    char *plabel_name1[] = {"主菜单项：文件",
                           "子菜单项：数据保存",
                           "确认"
                          };

    ShowModule(plabel_name1, 3);

    SaveSysData(gp_head);                           /*保存系统数据*/

    char *plabel_name2[] = {"数据保存成功！",
                           "确认"
                          };
    ShowModule(plabel_name2, 2);

    return bRet;
}

/********
函数名称：SaveSysData
函数功能：保存系统数据
输入参数：hd为主链头结点指针
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL SaveSysData(T *hd)
{
    T *pType;
    B *pBasic;
    P *pPlant;
    N *pNutri;
    FILE *pfout;

    pfout = fopen(gp_ve_t_info_filename, "wb");
    for(pType = hd; pType!= NULL; pType = pType->next)/*保存蔬菜种类信息*/
    {
        fwrite(pType, sizeof(T), 1, pfout);
    }
    fclose(pfout);

    pfout = fopen(gp_ve_b_info_filename, "wb");
    for(pType = hd; pType != NULL; pType = pType->next)/*保存蔬菜基本信息*/
    {
        pBasic = pType->snext;
        while(pBasic != NULL)
        {
            fwrite(pBasic, sizeof(B), 1, pfout);
            pBasic = pBasic->next;
        }
    }
    fclose(pfout);

    pfout = fopen(gp_ve_b_nutri_info_filename, "wb");
    for(pType = hd; pType != NULL; pType = pType->next)/*保存蔬菜基本信息中的营养成分*/
    {
        pBasic = pType->snext;
        while(pBasic != NULL)
        {
            pNutri=pBasic->snext;
            while(pNutri!=NULL)
            {
                fwrite(pNutri,sizeof(N),1,pfout);
                pNutri=pNutri->next;
            }
            pBasic = pBasic->next;
        }
    }
    fclose(pfout);

    pfout = fopen(gp_ve_p_info_filename, "wb");
    for(pType = hd; pType != NULL; pType = pType->next)/*保存蔬菜种植信息*/
    {
        pBasic = pType->snext;
        while(pBasic != NULL)
        {
            pPlant = pBasic->cnext;
            while(pPlant != NULL)
            {
                fwrite(pPlant, sizeof(P), 1, pfout);
                pPlant = pPlant->next;
            }
            pBasic = pBasic->next;
        }
    }
    fclose(pfout);

    return TRUE;
}

/********
函数名称：BackupData
函数功能：显示数据备份窗口
输入参数：无
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL BackupData(void)
{
    BOOL bRet = TRUE;
    char *plabel_name1[] = {"主菜单项：文件",
                           "子菜单项：数据备份",
                           "确认"
                          };
    ShowModule(plabel_name1, 3);

    BackupSysData(gp_head,"Backup.dat");            /*备份系统数据*/

    char *plabel_name2[] = {"数据备份成功！",
                           "确认"
                          };
    ShowModule(plabel_name2, 2);

    ClearScreen();
    ShowMenu();

    return bRet;
}

/********
函数名称：BackupSysData
函数功能：备份系统数据
输入参数：hd为主链头结点指针，filename为数据文件名
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL BackupSysData(T *hd,char* filename)
{
    T *pType;
    B *pBasic;
    N *pNutri;
    P *pPlant;
	unsigned long Type_num = 0;
	unsigned long Basic_num = 0;
	unsigned long Nutri_num = 0;
	unsigned long Plant_num = 0;

	/* 遍历十字链表，分别统计四种基础信息的记录总数 */
    for(pType = hd; pType != NULL; pType = pType->next)
    {
        Type_num++;
        pBasic = pType->snext;
        while(pBasic != NULL)
        {
            Basic_num++;

            pNutri=pBasic->snext;
            while(pNutri!=NULL)
            {
                Nutri_num++;
                pNutri=pNutri->next;
            }

            pPlant = pBasic->cnext;
            while(pPlant != NULL)
            {
                Plant_num++;
                pPlant = pPlant->next;
            }
            pBasic = pBasic->next;
        }
    }

    int handle;
    if((handle=open(filename,O_WRONLY|O_BINARY))==-1)
    {

        handle=open(filename,O_CREAT|O_BINARY,S_IWRITE);
    }

    /*保存四类基础数据的记录总数*/
    write(handle, (char *)&Type_num, sizeof(Type_num));
    write(handle, (char *)&Basic_num, sizeof(Basic_num));
    write(handle, (char *)&Nutri_num, sizeof(Nutri_num));
    write(handle, (char *)&Plant_num, sizeof(Plant_num));

    /*保存蔬菜种类信息*/
    for(pType=hd;pType!=NULL;pType=pType->next)
    {
        write(handle,(char*)pType,sizeof(T));
    }

    /*保存蔬菜基本信息*/
    for(pType = hd; pType != NULL; pType = pType->next)
    {
        pBasic = pType->snext;
        while(pBasic != NULL)
        {
            write(handle, (char *)pBasic, sizeof(B));
            pBasic= pBasic->next;
        }
    }

    /*保存蔬菜基本信息中的营养成分以及蔬菜种植信息*/
    for(pType = hd; pType != NULL; pType = pType->next)
    {
        pBasic = pType->snext;
        while(pBasic != NULL)
        {
            pNutri=pBasic->snext;
            while(pNutri!=NULL)
            {
                write(handle,(char*)pNutri,sizeof(N));
                pNutri=pNutri->next;
            }

            pPlant = pBasic->cnext;
            while(pPlant != NULL)
            {
                write(handle, (char*)pPlant, sizeof(P));
                pPlant = pPlant->next;
            }

            pBasic = pBasic->next;
        }
    }
    close(handle);
    return TRUE;
}

/********
函数名称：RestoreData
函数功能：显示数据恢复窗口
输入参数：无
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL RestoreData(void)
{
    char *plabel_name1[] = {"主菜单项：文件",
                           "子菜单项：数据恢复",
                           "确认"
                          };
    ShowModule(plabel_name1, 3);
    char *plabel_name2[] = {"当前数据将被覆盖。继续执行？",
                            "确认","取消"
                           };
    char *plabel_name3[] = {"数据恢复成功！",
                            "确认"
                           };
    int x=ShowModule5(plabel_name2, 3);             /*若选中“确认”返回1，若选中“取消”返回2*/
    switch(x)
    {
        case 1:
            RestoreSysData(&gp_head, "Backup.dat"); /*恢复系统数据*/
            ShowModule(plabel_name3, 2);
            break;
        case 2:
            break;
    }
    return TRUE;
}

/********
函数名称：RestoreSysData
函数功能：从指定数据文件中恢复四类基础数据
输入参数：phead主链头结点指针的地址，filename存放备份数据的数据文件名
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL RestoreSysData(T **phead,CHAR* filename)
{
    T *hd = NULL;
    T *pType;
    B *pBasic;
    N *pNutri;
    P *pPlant;
    unsigned long Type_num = 0;
    unsigned long Basic_num = 0;
    unsigned long Nutri_num = 0;
    unsigned long Plant_num = 0;
    unsigned long ulloop;
    int handle;
    int find;

	if((handle = open(filename,O_CREAT | O_BINARY)) == -1)
	{
		handle = open(filename,O_CREAT | O_BINARY,S_IREAD);
	}

    read(handle, (char *)&Type_num, sizeof(Type_num));
    read(handle, (char *)&Basic_num, sizeof(Basic_num));
    read(handle, (char *)&Nutri_num, sizeof(Nutri_num));
    read(handle, (char *)&Plant_num, sizeof(Plant_num));

    /*读取蔬菜分类信息，建立十字主链*/
    for(ulloop = 1; ulloop <= Type_num; ulloop++)
    {
        pType = (T *)malloc(sizeof(T));
        read(handle, (char *)pType, sizeof(T));
        pType->snext = NULL;
        pType->next = hd;
        hd = pType;
    }
    *phead = hd;

    /*读取蔬菜基本信息，建立蔬菜信息支链*/
    for(ulloop = 1; ulloop <= Basic_num; ulloop++)
    {
        pBasic = (B *)malloc(sizeof(B));
        read(handle, (char *)pBasic, sizeof(B));
        pBasic->snext=NULL;
        pBasic->cnext = NULL;
        pType = hd;
        while(pType != NULL&& (pType->type != pBasic->type))
        {
            pType= pType->next;
        }

        if(pType != NULL)
        {
            pBasic->next = pType->snext;
            pType->snext = pBasic;
        }
        else
        {
            free(pBasic);
        }
    }

    /*读取蔬菜营养成分信息，建立营养成分信息链表*/
    for(ulloop = 1; ulloop <= Nutri_num; ulloop++)
    {
        pNutri = (N *)malloc(sizeof(N));
        read(handle, (char *)pNutri, sizeof(N));
        pType = hd;
        find = 0;

        while(pType != NULL && find == 0)
        {
            pBasic = pType -> snext;
            while(pBasic != NULL && find == 0)
            {
                if(pBasic -> num == pNutri -> num)
                {
                    find = 1;
                    break;
                }
                pBasic = pBasic -> next;
            }
            pType = pType -> next;
        }

        if(find)
        {
            pNutri -> next = pBasic-> snext;
            pBasic -> snext = pNutri;
        }
        else
        {
            free(pNutri);
        }
    }

    /*读取蔬菜种植信息，建立蔬菜种植信息支链链表*/
    for(ulloop = 1; ulloop <= Plant_num; ulloop++)
    {
        pPlant = (P *)malloc(sizeof(P));
        read(handle, (char *)pPlant, sizeof(P));
        pType = hd;
        find = 0;

        while(pType != NULL && find == 0)
        {
            pBasic = pType -> snext;
            while(pBasic != NULL && find == 0)
            {
                if(pBasic -> num == pPlant -> num)
                {
                    find = 1;
                    break;
                }
                pBasic = pBasic -> next;
            }
            pType = pType -> next;
        }

        if(find)
        {
            pPlant -> next = pBasic-> cnext;
            pBasic -> cnext = pPlant;
        }
        else
        {
            free(pPlant);
        }
    }

    close(handle);
    SaveSysData(hd);                                /*将内存中数据保存到数据文件*/

    return TRUE;
}

/********
函数名称：ExitSys
函数功能：退出系统
输入参数：无
输出参数：无
返 回 值：BOOL类型，若是选择退出系统返回FALSE，其余情况下总是返回TRUE
调用说明：无
********/
BOOL ExitSys(void)
{
    char *plabel_name1[] = {"      确认退出系统吗？      ",
                           "确认","取消"
                          };
    char *plabel_name2[] = {"      是否需要保存数据？      ",
                           "确认","取消"
                          };
    int x=ShowModule5(plabel_name1,3);              /*若是选择“确认”返回1,若是选择“取消”返回2*/
    int y;
    switch(x)
    {
        case 1:
            y=ShowModule5(plabel_name2,3);          /*若是选择“确认”返回1,若是选择“取消”返回2*/
            switch(y)
            {
                case 1:
                     SaveData2();                   /*提示数据保存*/
                     break;
                case 2:
                    break;
            }
            return FALSE;
        case 2:
            return TRUE;
    }
}

/********
函数名称：SaveData2
函数功能：在退出系统是提示保存系统数据
输入参数：无
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL SaveData2(void)
{
    char *plabel_name1[] = {"   数据保存   ",
                           "确认"
                          };

    ShowModule(plabel_name1, 2);

    SaveSysData(gp_head);

    char *plabel_name2[] = {"  数据保存成功！ ",
                           "确认"
                          };
    ShowModule(plabel_name2, 2);

    return TRUE;
}

/********
函数名称：MaintainTypeInfo
函数功能：对蔬菜种类信息进行数据维护
输入参数：无
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL MaintainTypeInfo(void)
{
    char *plabel_name[] = {"主菜单项：数据维护",
                           "子菜单项：蔬菜种类信息",
                           "录入","修改","删除"
                          };

    int x=ShowModule2(plabel_name, 5);              /*选择“录入”返回1，选择“修改”返回2，选择“删除”返回3*/
    switch(x)
    {
        case 1:
              InsertTypeInfo(gp_head);              /*录入蔬菜种类信息*/
              break;
        case 2:
              ModifTypeInfo(gp_head);               /*修改蔬菜种类信息*/
              break;
        case 3:
              DelTypeInfo(gp_head);                 /*删除蔬菜种类信息*/
              break;
    }
    Update();                                       /*更新各支链中与蔬菜种类信息对应的信息*/
    return TRUE;
}

/********
函数名称：InsertTypeInfo
函数功能：录入蔬菜种类信息
输入参数：hd为主链头结点指针
输出参数：无
返 回 值：void类型，无返回值
调用说明：无
********/
void InsertTypeInfo(T *hd)
{
    T *pType,*p=hd;
    pType=(T*)malloc(sizeof(T));                    /*新建信息结点*/
    location(25,10);printf("请输入所要录入的蔬菜种类信息：");
    location(30,12);printf("分类编码：");
    location(40,12);scanf("%c",&pType->type);

    if(pType->type=='\n')                           /*判断输入的蔬菜分类编码是否为空*/
    {
            char *notice4[] = {"   未输入分类编码。",
                              "录入蔬菜种类信息失败。",
                              "确认"
                             };

            ClearScreen();
            ShowMenu();
            ShowModule(notice4, 3);
            free(pType);
            return;
    }
    location(30,14);printf("分类名称：");
    location(40,14);scanf("%s",&pType->name);
    getchar();
    ClearScreen();
    ShowMenu();
    if(strlen(pType->name)>8)                       /*判断蔬菜种类名称字符串是否过长*/
    {
        char *notice1[] = {"输入名称过长。",
                            "录入蔬菜种类信息失败。",
                            "确认"
                          };
        ShowModule(notice1, 3);
        free(pType);
        return;
    }

    while(p != NULL)                                /*遍历分类信息链表，检查分类名称或分类编号是否已被使用*/
    {
        if(pType->type == p->type)
        {
            char *notice2[] = {" 此分类编号已被使用。",
                              "录入蔬菜种类信息失败。",
                              "确认"
                             };
            ShowModule(notice2, 3);
            free(pType);
            return;
        }
        else if(strcmp(pType->name,p->name) == 0)
        {
            char *notice3[] = {" 此分类名称已被使用。",
                            "录入蔬菜种类信息失败。",
                            "确认"
                            };
            ShowModule(notice3, 3);
            free(pType);
            return;
        }
        p = p->next;
    }
    /*将新建的信息结点作为新的主链的头结点*/
    pType->snext=NULL;
    pType->next=hd;
    gp_head=pType;
    char *notice[] = {"录入蔬菜种类信息成功。",
                    "确认"
                    };
    ShowModule(notice, 2);
    return;
}

/********
函数名称：ModifTypeInfo
函数功能：修改蔬菜种类信息
输入参数：hd为主链头结点指针
输出参数：无
返 回 值：void类型，无返回值
调用说明：无
********/
void ModifTypeInfo(T *hd)
{
    T *pType=hd,*p=NULL;
    B *pBasic=NULL;
    char type;
    char name[20];
    location(25,6);printf("请输入所要修改的蔬菜分类名称：");
    location(35,8);scanf("%s",name);
    getchar();
    ClearScreen();
    ShowMenu();

    while(pType!=NULL)                              /*遍历分类信息链表，查找是否存在所要修改的分类名称*/
    {
        if(strcmp(name,pType->name)==0)
        {
            break;
        }
        pType=pType->next;
    }
    if(pType==NULL)
    {
        char *notice1[] = {"    该分类不存在!","修改蔬菜种类信息失败!",
                    "确认"
                    };
        ShowModule(notice1, 3);
        free(p);
        return;
    }

    char *pString[] = {"修改分类编号",
                       "修改分类名称",
                       "返回"
                      };
    int x=ShowModule3(pString,3);
    switch(x)
    {
        case 1:
            location(25,10);printf("当前该蔬菜分类详细信息如下：");
            location(30,12);printf("分类编码：");
            location(40,12);printf("%-8c",pType->type);
            location(30,14);printf("分类名称：");
            location(40,14);printf("%-10s",pType->name);
            location(25,16);printf(" 新的分类编码：");
            location(40,16);scanf("%c",&type);
            getchar();
            ClearScreen();
            ShowMenu();

            p=hd;                                   /*遍历分类信息链表，查询该分类编码是否已被使用*/
            while(p!=NULL)
            {
                if(p->type==type)break;
                p=p->next;
            }
            if(p!=NULL)
            {
                char *notice2[] = { " 该分类编号已被使用!",
                                    "修改蔬菜种类信息失败!",
                                    "确认"
                                  };
                ShowModule(notice2, 3);
            }
            else
            {
                pType->type=type;
                for(pBasic=pType->snext;pBasic!=NULL;pBasic=pBasic->next)
                    pBasic->type=type;
                char *notice[] = {"修改蔬菜分类信息成功!",
                                  "确认"
                                 };
                ShowModule(notice, 2);
            }
            break;
        case 2:
            location(25,10);printf("当前该蔬菜分类详细信息如下：");
            location(30,12);printf("分类编码：");
            location(40,12);printf("%-8c",pType->type);
            location(30,14);printf("分类名称：");
            location(40,14);printf("%-10s",pType->name);
            location(25,16);printf("新的分类名称：");
            location(40,16);scanf("%s",name);
            getchar();
            ClearScreen();
            ShowMenu();

            if(strlen(name)>8)                      /*判断输入的分类名称字符串是否过长*/
            {
                char *notice3[] = {"   分类名称过长!",
                                   "修改蔬菜种类信息失败!",
                                   "确认"
                                  };
                ShowModule(notice3, 3);
            }

            p=hd;                                   /*遍历分类信息链表，查询该分类名称是否已被使用*/
            while(p!=NULL)
            {
                if(strcmp(p->name,name)==0)break;
                p=p->next;
            }
            if(p!=NULL)
            {
                char *notice4[] = {"    该分类名称已被使用!",
                                   "修改蔬菜种类信息失败!",
                                   "确认"
                                  };
                ShowModule(notice4, 3);
            }
            else                                    /*修改该分类的分类名称*/
            {
                strcpy(pType->name,name);
                char *notice[] = {"修改蔬菜分类信息成功!",
                                  "确认"
                                 };
                ShowModule(notice, 2);
            }
            break;
        case 3:
            break;
        }
    return;
}

/********
函数名称：DelTypeInfo
函数功能：删除蔬菜种类信息
输入参数：hd为主链头结点指针
输出参数：无
返 回 值：void类型，无返回值
调用说明：无
********/
void DelTypeInfo(T *hd)
{
    T *pType=hd,*p=NULL;
    B *pBasic1,*pBasic2;
    N *pNutri1,*pNutri2;
    P *pPlant1,*pPlant2;
    char name[8];

    location(25,6);printf("请输入所要删除的蔬菜分类名称：");
    location(35,8);scanf("%s",name);
    getchar();
    ClearScreen();
    ShowMenu();
    for(;pType!=NULL&&strcmp(name,pType->name);p=pType,pType=pType->next);
    if(pType==NULL)
    {
        char *notice1[] = {"    该分类不存在!",
                           "删除蔬菜种类信息失败!",
                           "确认"
                          };
        ShowModule(notice1, 3);
        return;
    }
    else if(pType==gp_head)
    {
        gp_head=pType->next;
    }
    else
    {
        p->next=pType->next;
    }

    pBasic1=pType->snext;
    while(pBasic1!=NULL)
    {
        pBasic2=pBasic1->next;
        pNutri1=pBasic1->snext;
        while(pNutri1!=NULL)
        {
            pNutri2=pNutri1->next;
            free(pNutri1);
            pNutri1=pNutri2;
        }
        pPlant1=pBasic1->cnext;
        while(pPlant1!=NULL)
        {
            pPlant2=pPlant1->next;
            free(pPlant1);
            pPlant1=pPlant2;
        }
        free(pBasic1);
        pBasic1=pBasic2;
    }
    free(pType);
    char *notice2[] = {"删除分类信息成功!",
                       "确认"
                      };
    ShowModule(notice2, 2);
    return;
}

/********
函数名称：MaintainBasicInfo
函数功能：对蔬菜基本信息进行数据维护
输入参数：无
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL MaintainBasicInfo(void)
{
    char *plabel_name[] = {"主菜单项：数据维护",
                           "子菜单项：蔬菜基本信息",
                           "录入","修改","删除"
                          };

    int x=ShowModule2(plabel_name, 5);
    switch(x)
    {
        case 1:
              InsertBasicInfo(gp_head);
              break;
        case 2:
              ModifBasicInfo(gp_head);
              break;
        case 3:
              DelBasicInfo(gp_head);
              break;
    }
    Update();                                       /*更新各支链中与蔬菜种类信息对应的信息*/
    return TRUE;
}

/********
函数名称：InsertBasicInfo
函数功能：录入蔬菜基本信息
输入参数：hd为主链头结点指针
输出参数：无
返 回 值：void类型，无返回值
调用说明：无
********/
void InsertBasicInfo(T *hd)/******************************************************************************************应该还有问题****/
{
    T *pType1=hd,*pType2=hd;
    B *pBasic1,*p=(B*)malloc(sizeof(B)),*p1;
    N *pNutri1,*pNutri2;
    P *pplant;
    int num;
    char name[30];
    char type;
    location(25,6);printf("请输入所要录入的蔬菜基本信息：");
    location(30,8);printf("分类编码：");
    location(40,8);scanf("%c",&type);
    getchar();

    for(;pType1!=NULL&&(type!=pType1->type);pType1=pType1->next);
    if(pType1==NULL)
    {
        char *notice1[] = {"    该分类不存在!",
                           "录入蔬菜基本信息失败!",
                           "确认"
                          };
        ClearScreen();
        ShowMenu();
        free(p);
        ShowModule(notice1, 3);
        return;
    }
    else
    {
        p->type=type;
    }
    location(30,10);printf("蔬菜名称：");
    location(40,10);scanf("%s",name);
    getchar();

    pBasic1=pType1->snext;
    if(strlen(name)>20)
    {
        char *notice2[] = {"   蔬菜名称过长!","录入蔬菜基本信息失败!",
                    "确认"
                    };
        ShowModule(notice2, 3);
        ClearScreen();
        ShowMenu();
        free(p);
        return;
    }
    else
    {
        while(pType2!=NULL)
        {
            pBasic1=pType2->snext;
            while(pBasic1!=NULL)
            {
                if(strcmp(name,pBasic1->name)==0)
                {
                    char *notice3[] = {" 该蔬菜名称已被使用!",
                                       "录入蔬菜基本信息失败!",
                                       "确认"
                                      };
                    ClearScreen();
                    ShowMenu();
                    free(p);
                    ShowModule(notice3, 3);
                    return;
                }
                pBasic1=pBasic1->next;
            }
            pType2=pType2->next;
        }
    }
    strcpy(p->name,name);

    p->cnext=NULL;
    p->snext=NULL;
    pNutri2=(N*)calloc(1,sizeof(N));
    pNutri2->next= NULL;

    location(20,12);printf("营养成分的输入以#为结束符，例如：维生素 铁 #");
    location(30,14);printf("营养成分：");
    location(40,14);
	while(1)                                        /*输入蔬菜基本信息中的营养成分*/
    {
	    pNutri1=(N*)malloc(sizeof(N));
        pNutri1->next=NULL;
	    char nutri[20]={'\0'};
        scanf("%s",nutri);
        if(nutri[0]=='#')
        {
        	pNutri1=NULL;
        	break;
		}
		else
		{
            strcpy(pNutri1->n,nutri);
            pNutri1->next=pNutri2->next;
            pNutri2->next=pNutri1;
		}
    }
    getchar();
    pNutri2=pNutri2->next;
    p->snext=pNutri2;

    p1=pType1->snext;
    int max;                                        /*为新输入的蔬菜基本信息更新蔬菜编号*/
    if(p1==NULL)
    {
        p->num=1;
    }
    else
    {
        max=p1->num;
        while(p1!=NULL)
        {
            if(max<p1->num)max=p1->num;
            p1=p1->next;
        }
        p->num=max+1;
    }
    p->next=pType1->snext;
    pType1->snext=p;
    Update();                                       /*将蔬菜编码同步到到蔬菜种植信息和蔬菜营养成分中*/

    location(30,16);printf("蔬菜编码：");
    location(40,16);printf("%d",p->num);
    printf("\n\n\t\t\t    按任意键继续。。。");
    getchar();

    char *notice[] = {"插入基本信息成功。",
                      "确认"
                     };
    ClearScreen();
    ShowMenu();
    ShowModule(notice, 2);
    return;
}

/********
函数名称：ModifBasicInfo
函数功能：修改蔬菜基本信息
输入参数：hd为主链头结点指针
输出参数：无
返 回 值：void类型，无返回值
调用说明：无
********/
void ModifBasicInfo(T *hd)
{
    T *ptype=hd;
    B *pbasic1,*pbasic2;
    N *pnutri;
    P *pplant;
    char name[30];
    int find=0;
    int i=0,x,y;
    BOOL flag=TRUE;
    location(25,6);printf("请输入所要修改基本信息的蔬菜名称：");
    location(35,8);scanf("%s",name);
    getchar();

    while(ptype!=NULL)
    {
        pbasic1=ptype->snext;
        while(pbasic1!=NULL)
        {
            if(strcmp(name,pbasic1->name)==0)
            {
                find=1;
                break;
            }
            pbasic2=pbasic1;
            pbasic1=pbasic1->next;
        }
        if(find==1)
        {
            break;
        }
        ptype=ptype->next;
    }
    if(ptype==NULL)
    {
        char *notice1[] = {"    该蔬菜不存在!","修改蔬菜基本信息失败!",
                    "确认"
                    };
        ClearScreen();
        ShowMenu();
        ShowModule(notice1, 3);

        return;
    }

    location(25,10);printf("当前该蔬菜基本信息详情如下：");
    location(30,12);printf("蔬菜编号：");
    location(40,12);printf("%d",pbasic1->num);
    location(30,14);printf("蔬菜名称：");
    location(40,14);printf("%s",pbasic1->name);
    location(30,16);printf("分类码：");
    location(40,16);printf("%c",pbasic1->type);
    location(30,18);printf("营养成分：");
    location(40,18);
    pnutri=pbasic1->snext;
    while(pnutri!=NULL)
    {
        printf("%s  ",pnutri->n);
        pnutri=pnutri->next;
        i++;
        if(i%4==0)
        {
            location(40,18+(i/4)*2);
        }
    }
    location(25,20+(i/4)*2);printf("请按任意键继续。。。");
    getchar();
    ClearScreen();
    ShowMenu();

    char *pString1[] = {"修改蔬菜名称",
                        " 修改分类码",
                        "修改营养成分",
                        "返回"
                       };
    x=ShowModule4(pString1, 4);
    char *pString2[] = {" 录入新的营养成分",
                        "修改已有的营养成分",
                        "删除已有的营养成分",
                        "返回"
                        };
    switch(x)
    {
        case 1:
             flag=ModifName(ptype,pbasic1);
             break;
        case 2:
             flag=ModifType(ptype,pbasic1,pbasic2);
             break;
        case 3:
            y=ShowModule4(pString2, 4);
            switch(y)
            {
                case 1:
                    flag=InsertNutri(ptype,pbasic1);
                    break;
                case 2:
                    flag=ModifNutri(ptype,pbasic1);
                    break;
                case 3:
                    flag=DelNutri(ptype,pbasic1);
                    break;
                case 4:
                    return;
            }
            break;
        case 4:
            return;
    }
    if(flag==TRUE)
    {
        char *notice2[] = {"修改蔬菜基本信息成功!",
                           "确认"
                          };
        Update();
        ShowModule(notice2, 2);
    }
    else
    {
        char *notice3[] = {"修改蔬菜基本信息失败!",
                "确认"
                };
        ShowModule(notice3, 2);
    }
}

/********
函数名称：ModifName
函数功能：修改蔬菜名称
输入参数：ptype为所要修改的蔬菜所对应的蔬菜种类信息结点
           pbasic为所要修改的蔬菜所对应的蔬菜基本信息结点
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL ModifName(T *ptype,B *pbasic)
{
    T *pt=gp_head;
    B *pb;
    char name[30];
    int find=0;
    location(25,10);printf("请输入修改后新的分类名称：");
    location(35,12);scanf("%s",name);
    getchar();
    ClearScreen();
    ShowMenu();

    if(strlen(name)>20)
    {
        char *notice1[] = {"输入的新名称过长!"
                           "确认"
                          };
        ShowModule(notice1, 2);
        return FALSE;
    }

    while(pt!=NULL)
    {
        pb=pt->snext;
        while(pb!=NULL)
        {
            if(strcmp(name,pb->name)==0)
            {
                find=1;
                break;
            }
            pb=pb->next;
        }
        if(find==1) break;
        pt=pt->next;
    }
    if(find==1)
    {
        char *notice2[] = {"输入的新名称已存在!",
                           "确认"
                          };
        ShowModule(notice2, 2);
        return FALSE;
    }
    strcpy(pbasic->name,name);
    return TRUE;
}

/********
函数名称：ModifType
函数功能：修改蔬菜对应分类编码
输入参数：ptype为所要修改的蔬菜所对应的蔬菜种类信息结点
           pbasic1为所要修改的蔬菜所对应的蔬菜基本信息结点
           pbasic2为所要修改的蔬菜所对应的蔬菜基本信息的前一个结点
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL ModifType(T *ptype,B *pbasic1,B *pbasic2)
{
    T *pt=gp_head;
    B *pb;
    char type;
    int find=0;
    location(25,10);printf("请输入修改后新的分类编码：");
    location(35,12);scanf("%c",&type);
    getchar();
    ClearScreen();
    ShowMenu();

    while(pt!=NULL)
    {
        if(pt->type==type)
        {
            find=1;
            break;
        }
        pt=pt->next;
    }
    if(find==0)
    {
        char *notice[] = {"输入的新分类码不存在!",
                        "确认"
                        };
        ShowModule(notice, 2);
        return FALSE;
    }

    pb=ptype->snext;
    while(pb!=NULL)                                 /*更新原基本信息支链中的蔬菜编号*/
    {
        if(pb->num>pbasic1->num)pb->num=pb->num-1;
        pb=pb->next;
    }
    pb=pt->snext;
    int max;
    if(pb==NULL)max=0;
    else
    {
        max=pb->num;
        while(pb!=NULL)
        {
            if(pb->num>max)max=pb->num;
            pb=pb->next;
        }
    }
    pbasic1->type=type;
    pbasic1->num=max+1;

    if(ptype->snext==pbasic1)
    {
        ptype->snext=pbasic1->next;
    }
    else
    {
        pbasic2->next=pbasic1->next;
    }
    pbasic1->next=pt->snext;
    pt->snext=pbasic1;
    return TRUE;
}

/********
函数名称：Update
函数功能：更新各支链中与蔬菜种类信息对应的信息
输入参数：无
输出参数：无
返 回 值：void类型，无返回值
调用说明：无
********/
void Update(void)
{
    T *ptype=gp_head;
    B *pbasic;
    N *pnutri;
    P *pplant;

    while(ptype!=NULL)
    {
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            pnutri=pbasic->snext;
            while(pnutri!=NULL)
            {
                pnutri->type=pbasic->type;
                pnutri->num=pbasic->num;
                pnutri=pnutri->next;
            }

            pplant=pbasic->cnext;
            while(pplant!=NULL)
            {
                pplant->type=pbasic->type;
                pplant->num=pbasic->num;
                pplant=pplant->next;
            }
            pbasic=pbasic->next;
        }
        ptype=ptype->next;
    }
}

/********
函数名称：InsertNutri
函数功能：录入新的营养成分
输入参数：ptype为所要修改的蔬菜所对应的蔬菜种类信息结点
           pbasic为所要修改的蔬菜所对应的蔬菜基本信息结点
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL InsertNutri(T *ptype,B *pbasic)
{
    N *p=pbasic->snext,*pnutri;
    char nutri[20];
    int find=0;
    location(25,10);printf("请输入所要录入的新营养成分：");
    location(35,12);scanf("%s",nutri);
    ClearScreen();
    ShowMenu();

    while(p!=NULL)
    {
        if(strcmp(nutri,p->n)==0)
        {
            find=1;
            break;
        }
        p=p->next;
    }
    if(find==1)
    {
        char *notice[] = {"输入的营养成分已存在",
                          "确认"
                          };
        ShowModule(notice, 2);
        return FALSE;
    }
    pnutri=(N*)malloc(sizeof(N));
    strcpy(pnutri->n,nutri);
    pnutri->next=pbasic->snext;
    pbasic->snext=pnutri;
    pnutri->num=pbasic->num;
    return TRUE;
}

/********
函数名称：
函数功能：修改已有的营养成分
输入参数：
输出参数：
返 回 值：BOOL类型，总是返回TRUE
调用说明：
********/
BOOL ModifNutri(T *ptype,B *pbasic)
{
    N *p=pbasic->snext;
    char nutri[20];
    int find=0;
    location(25,10);printf("请输入所要修改的营养成分：");
    location(35,12);scanf("%s",nutri);
    getchar();

    while(p!=NULL)
    {
        if(strcmp(nutri,p->n)==0)
        {
            find=1;
            break;
        }
        p=p->next;
    }
    if(find==0)
    {
        char *notice2[] = {"输入的营养成分不存在",
                        "确认"
                        };
        ClearScreen();
        ShowMenu();
        ShowModule(notice2, 2);
        return FALSE;
    }

    location(25,14);printf("请输入修改后的新营养成分：");
    location(35,16);scanf("%s",p->n);
    getchar();
    return TRUE;
}

/********
函数名称：DelNutri
函数功能：删除已有的营养成分
输入参数：ptype为所要修改的蔬菜所对应的蔬菜种类信息结点
           pbasic为所要修改的蔬菜所对应的蔬菜基本信息结点
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL DelNutri(T *ptype,B *pbasic)
{
    N *p,*pnutri;
    char nutri[20];
    int find=0;
    location(25,10);printf("请输入所要删除的新营养成分：");
    location(35,12);scanf("%s",nutri);
    getchar();
    ClearScreen();
    ShowMenu();

    p=pbasic->snext;
    pnutri=(N*)malloc(sizeof(N));
    while(p!=NULL)
    {
        if(strcmp(nutri,p->n)==0)
        {
            find=1;
            break;
        }
        pnutri=p;
        p=p->next;
    }
    if(find==0)
    {
        char *notice2[] = {"输入的营养成分不存在",
                           "确认"
                          };
        ShowModule(notice2, 2);
        return FALSE;
    }
    if(p==pbasic->snext)
    {
        pbasic->snext=p->next;
    }
    else
    {
        pnutri->next=p->next;
    }
    return TRUE;
}

/********
函数名称：DelBasicInfo
函数功能：删除蔬菜基本信息
输入参数：hd为蔬菜基本信息链头结点指针
输出参数：无
返 回 值：void类型，无返回值
调用说明：无
********/
void DelBasicInfo(T* hd)
{
    T *pType=hd;
    B *pBasic1,*pBasic2=NULL,*pb;
    N *pNutri;
    P *pPlant;
    char name[20];

    location(25,8);printf("请输入所要删除基本信息的名称：");
    location(35,10);scanf("%s",name);getchar();

    while(pType!=NULL)
    {
        pBasic1=pType->snext;
        while(pBasic1!=NULL)
        {
            if(strcmp(name,pBasic1->name)==0)
            {
                if(pBasic1=pType->snext)
                {
                    pType->snext=pBasic1->next;
                }
                else
                {
                    pBasic2->next=pBasic1->next;
                }

                pb=pType->snext;
                while(pb!=NULL)
                {
                    if(pb->num>pBasic1->num)pb->num=pb->num-1;
                    pb=pb->next;
                }

                pNutri=pBasic1->snext;
                while(pNutri!=NULL)
                {
                    free(pNutri);
                    pNutri=pNutri->next;
                }

                pPlant=pBasic1->cnext;
                while(pPlant!=NULL)
                {
                    free(pPlant);
                    pPlant=pPlant->next;
                }

                free(pBasic1);

                ClearScreen();
                ShowMenu();
                char *notice1[] = {"删除基本信息成功!",
                                "确认"
                                };

                ShowModule(notice1,2);
                return;
            }
            pBasic2=pBasic1;
            pBasic1=pBasic1->next;
        }
        pType=pType->next;
    }
    ClearScreen();
    ShowMenu();
    char *notice2[] = {"此蔬菜名称不存在!",
                        "删除基本信息失败!",
                        "确认"
                        };

    ShowModule(notice2, 3);
    Update();                                       /*更新蔬菜编号*/
    return;
}

/********
函数名称：MaintainPlantInfo
函数功能：对蔬菜种植信息进行维护
输入参数：无
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL MaintainPlantInfo(void)
{
    char *plabel_name[] = {"主菜单项：数据维护",
                           "子菜单项：菜农种植信息",
                           "录入","修改","删除"
                          };
    int x=ShowModule2(plabel_name, 5);
    switch(x)
    {
        case 1:
              InsertPlantInfo(gp_head);
              break;
        case 2:
              ModifPlantInfo(gp_head);
              break;
        case 3:
              DelPlantInfo(gp_head);
              break;
    }
    Update();                                       /*更新蔬菜编号*/
    return TRUE;
}

/********
函数名称：InsertPlantInfo
函数功能：录入蔬菜种子信息
输入参数：hd为蔬菜种植信息链的头结点指针
输出参数：无
返 回 值：void类型，无返回值
调用说明：无
********/
void InsertPlantInfo(T *hd)
{
    T *ptype=hd;
    B *pbasic;
    P *pplant,*p=(P*)malloc(sizeof(P));;
    char name[20];
    char year[5];
    int find=0;

    location(25,6);printf("请输入所要录入的蔬菜种植信息：");
    location(30,8);printf("蔬菜名称：");
    location(40,8);scanf("%s",name);
    getchar();

    while(ptype!=NULL)
    {
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            if(strcmp(pbasic->name,name)==0)
            {
                find=1;break;
            }
            pbasic=pbasic->next;
        }
        if(find==1)break;
        ptype=ptype->next;
    }

    if(find==0)
    {
        char *notice1[] = {"   该蔬菜不存在!",
                        "插入蔬菜种植信息失败!",
                        "确认"
                        };
        ClearScreen();
        ShowMenu();
        ShowModule(notice1, 3);

        return;
    }

    location(30,10);
    printf("种植年份：");
    location(40,10);
    scanf("%s",year);
    find=0;
    pplant=pbasic->cnext;
    while(pplant!=NULL)
    {
        if(strcmp(pplant->year,year)==0)
        {
            find=1;
            break;
        }
        pplant=pplant->next;
    }
    if(find==1)
    {
        char *notice2[] = {" 该年份信息已经录入!",
                        "插入蔬菜种植信息失败!",
                        "确认"
                        };
        ClearScreen();
        ShowMenu();
        ShowModule(notice2, 3);
        return;
    }

    strcpy(p->name,name);
    strcpy(p->year,year);
    p->type=ptype->type;
    p->num=pbasic->num;

    location(30,12);printf("种植面积：");
    location(40,12);scanf("%d",&p->area);
    location(30,14);printf("收获重量：");
    location(40,14);scanf("%f",&p->h);
    getchar();
    p->n=1;
    p->next=pbasic->cnext;
    pbasic->cnext=p;
    UpdateNum();                                    /*对蔬菜种植信息按种植年份升序排序并依次编号*/

    location(30,16);printf("蔬菜编号：");
    location(40,16);printf("%d",p->num);
    printf("\n\n\t\t\t    按任意键继续。。。");
    getchar();

    char *notice3[] = {"插入基本信息成功!",
                    "确认"
                    };
    ClearScreen();
    ShowMenu();
    ShowModule(notice3, 2);

    return;
}

/********
函数名称：ModifPlantInfo
函数功能：修改蔬菜种植信息
输入参数：hd为蔬菜种植信息链的头结点指针
输出参数：无
返 回 值：void类型，无返回值
调用说明：无
********/
void ModifPlantInfo(T *hd)
{
    T *ptype=hd;
    B *pbasic;
    N *pnutri;
    P *pplant;
    char name[20];
    char year[5];
    int find=0;
    int n;
    int i=1,j=0;
    location(25,6);printf("请输入所要修改种植信息的蔬菜名称：");
    location(35,8);scanf("%s",name);
    getchar();

    while(ptype!=NULL)
    {
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            if(strcmp(name,pbasic->name)==0)
            {
                find=1;
                break;
            }
            pbasic=pbasic->next;
        }
        if(find==1)
        {
            break;
        }
        ptype=ptype->next;
    }
    if(ptype==NULL)
    {
        char *notice1[] = {"    该蔬菜不存在!","修改蔬菜种植信息失败!",
                    "确认"
                    };
        ClearScreen();
        ShowMenu();
        ShowModule(notice1, 3);
        return;
    }
    ClearScreen();
    ShowMenu();
    UpdateNum();                                    /*对蔬菜种植信息按种植年份升序排序并依次编号*/

    location(25,6);printf("当前该蔬菜种植信息详情如下：");
    location(20,8);printf("蔬菜编号：");
    location(30,8);printf("%d",pbasic->num);
    location(40,8);printf("蔬菜名称：");
    location(50,8);printf("%s",pbasic->name);

    P *p=pbasic->cnext,*p2=pbasic->cnext;
    if(p==NULL)
    {
        ClearScreen();
        ShowMenu();
        char *notice4[] = {"该蔬菜未录入任何种植信息",
                            "确认"
                            };
        ShowModule(notice4, 2);
        return;
    }

    location(15,10);printf("编号");
    location(30,10);printf("种植年份");
    location(40,10);printf("种植面积");
    location(55,10);printf("收获重量");
    while(p!=NULL)
    {
        if(j%7==0&&j!=0)
        {
            printf("\n\n\t\t因本页无法正确显示更多信息，请按回车键翻页!");
            getchar();
            ClearScreen();
            ShowMenu();
            location(15,10);printf("编号");
            location(30,10);printf("种植年份");
            location(40,10);printf("种植面积");
            location(55,10);printf("收获重量");
            i=1;
        }
        j++;
        location(15,10+2*i);printf("%d",p->n);
        location(30,10+2*i);printf("%s",p->year);
        location(43,10+2*i);printf("%d",p->area);
        location(55,10+2*i);printf("%f",p->h);
        i++;
        p=p->next;
    }
    location(10,10+2*i);printf("请输入所要修改的种植信息编号：");
    location(40,10+2*i);scanf("%d",&n);getchar();
    i++;
    p=pbasic->cnext;
    while(p!=NULL)
    {
        if(p->n==n)
        {
            break;
        }
        p=p->next;
    }
    if(p==NULL)
    {
        char *notice2[] = {"    该编号不存在!","修改蔬菜种植信息失败!",
                    "确认"
                    };
        ClearScreen();
        ShowMenu();
        ShowModule(notice2, 3);

        return;
    }
    char *notice3[] = {"修改种植年份","修改种植面积","修改收获重量",
                    "返回"
                    };
    ClearScreen();
    ShowMenu();
    int x=ShowModule4(notice3, 4);
    switch(x)
    {
        case 1:
            location(25,12);printf("请输入修改后的年份：");
            location(40,14);scanf("%s",year);

            while(p2!=NULL)
            {
                if(strcmp(p2->year,year)==0)
                {
                    break;
                }
                p2=p2->next;
            }
            if(p2!=NULL)
            {
                char *notice3[] = {"  该年份信息已存在!",
                                   "修改蔬菜种植信息失败!",
                                   "确认"
                                  };
                ClearScreen();
                ShowMenu();
                ShowModule(notice3, 3);
                return;
            }
            strcpy(p->year,year);
            break;
        case 2:
            location(25,12);printf("请输入修改后的种植面积：");
            location(40,14);scanf("%d",&p->area);
            break;
        case 3:
            location(25,12);printf("请输入修改后的收获重量：");
            location(40,14);scanf("%f",&p->h);
            break;
        case 4:
            ClearScreen();
            ShowMenu();
            return;
    }
    char *notice4[] = {"修改蔬菜种植信息成功!",
                        "确认"
                    };
    ClearScreen();
    ShowMenu();
    ShowModule(notice4, 2);
    return;
}

/********
函数名称：UpdateNum
函数功能：对蔬菜种植信息按种植年份升序排序并依次编号
输入参数：无
输出参数：无
返 回 值：void类型，无返回值
调用说明：无
********/
void UpdateNum(void)
{
    T *ptype=gp_head;
    B *pbasic;
    P *pplant;
    while(ptype!=NULL)
    {
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            pplant=pbasic->cnext;
            int len=0;

            while(pplant!=NULL)
            {
                len++;
                pplant=pplant->next;
            }
            pplant=pbasic->cnext;
            SortPlantInfo(pplant,len);             /*按种植年份降序排序并依次编号*/
            pbasic=pbasic->next;
        }
        ptype=ptype->next;
    }
}

/********
函数名称：SortPlantInfo
函数功能：对输入的蔬菜种植信息按年份递增排序
输入参数：head为蔬菜种植信息链的头结点指针
           len为蔬菜种植信息链的长度
输出参数：无
返 回 值：void类型，无返回值
调用说明：无
********/
void SortPlantInfo(P *head,int len)
{
    P *p=head,*q;
    int i,j;
    for(i=0;i<len-1;i++,p=p->next)
    {
        for(j=i+1,q=p->next;j<len;j++,q=q->next)
        {
            if(strcmp(p->year,q->year)>0)
            {
                int area;
                float h;
                char name[20];
                char year[5];
                area=p->area;p->area=q->area;q->area=area;
                h=p->h;p->h=q->h;q->h=h;
                strcpy(name,p->name);strcpy(p->name,q->name);strcpy(q->name,name);
                strcpy(year,p->year);strcpy(p->year,q->year);strcpy(q->year,year);
            }
        }
    }
    i=1;
    p=head;
    while(p!=NULL)
    {
        p->n=i++;
        p=p->next;
    }
}

/********
函数名称：DelPlantInfo
函数功能：删除蔬菜种植信息
输入参数：hd为蔬菜种植信息链的头结点指针
输出参数：无
返 回 值：void类型，无返回值
调用说明：无
********/
void DelPlantInfo(T* hd)
{
    T *ptype=hd;
    B *pbasic;
    P *pplant1,*pplant2,*p;
    char name[20];
    int n,i=1,j=0;
    int find=0;
    UpdateNum();
    location(25,6);printf("请输入所要删除种植信息的蔬菜名称：");
    location(35,8);scanf("%s",name);
    getchar();
    ClearScreen();
    ShowMenu();

    while(ptype!=NULL)
    {
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            if(strcmp(pbasic->name,name)==0)
            {
                find=1;
                break;
            }
            pbasic=pbasic->next;
        }
        if(find==1)   break;
        ptype=ptype->next;
    }
    if(find==0)
    {
        char *notice1[] = {"    该蔬菜不存在!","删除蔬菜种植信息失败!",
                    "确认"
                    };
        ShowModule(notice1, 3);
        ClearScreen();
        ShowMenu();
        return;
    }
    location(25,6);printf("当前该蔬菜种植信息详情如下：");
    location(20,8);printf("蔬菜编号：");
    location(30,8);printf("%d",pbasic->num);
    location(40,8);printf("蔬菜名称：");
    location(50,8);printf("%s",pbasic->name);

    p=pbasic->cnext;
    if(p==NULL)
    {
        ClearScreen();
        ShowMenu();
        char *notice4[] = {"该蔬菜未录入任何种植信息!",
                            "确认"
                            };
        ShowModule(notice4, 2);
        return;
    }
    location(15,10);printf("编号");
    location(30,10);printf("种植年份");
    location(40,10);printf("种植面积");
    location(55,10);printf("收获重量");
    while(p!=NULL)
    {
        if(j%7==0&&j!=0)
        {
            printf("\n\n\t\t因本页无法正确显示更多信息，请按回车键翻页!");
            getchar();
            ClearScreen();
            ShowMenu();
            location(15,10);printf("编号");
            location(30,10);printf("种植年份");
            location(40,10);printf("种植面积");
            location(55,10);printf("收获重量");
            i=1;
        }
        location(15,10+2*i);printf("%d",p->n);
        location(30,10+2*i);printf("%s",p->year);
        location(43,10+2*i);printf("%d",p->area);
        location(55,10+2*i);printf("%f",p->h);
        i++;
        p=p->next;
    }
    location(10,10+2*i);printf("请输入所要删除种植信息的编号：");
    location(40,10+2*i);scanf("%d",&n);
    find=0;
    pplant1=pbasic->cnext;
    while(pplant1!=NULL)
    {
        if(pplant1->n==n)
        {
            find=1;
            break;
        }
        pplant2=pplant1;
        pplant1=pplant1->next;
    }
    if(find==0)
    {
        char *notice2[] = {"    该编号不存在!","删除蔬菜种植信息失败!",
                    "确认"
                    };
        ClearScreen();
        ShowMenu();
        ShowModule(notice2, 3);
        return;
    }

    if(pplant1==pbasic->cnext)
    {
        pbasic->cnext=pplant1->next;
    }
    else
    {
        pplant2->next=pplant1->next;
    }
    free(pplant1);
    char *notice3[] = {"删除蔬菜种植信息成功!",
                    "确认"
                    };
    ClearScreen();
    ShowMenu();
    ShowModule(notice3, 2);
    UpdateNum();
    return;
}

/********
函数名称：QueryTypeInfo
函数功能：查询蔬菜种类信息
输入参数：无
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL QueryTypeInfo(void)
{
    char *plabel_name[] = {"主菜单项：数据查询",
                           "子菜单项：蔬菜类别信息",
                           "确认"
                          };
    ShowModule(plabel_name, 3);

    char type;
    T *ptype=gp_head;
    B *pbasic;
    N *pnutri;
    int find=0,j=0,i=12;
    location(15,6);printf("请输入所要查找的蔬菜类别编码：");
    location(45,6);scanf("%c",&type);
    getchar();
    while(ptype!=NULL)
    {
        if(ptype->type==type)
        {
            find=1;break;
        }
        ptype=ptype->next;
    }
    if(find==1)
    {
        location(10,8);printf("分类编码：");
        location(20,8);printf("%c",ptype->type);
        location(30,8);printf("分类名称：");
        location(40,8);printf("%s",ptype->name);
        location(10,10);printf("分类编码");
        location(20,10);printf("分类名称");
        location(30,10);printf("蔬菜名称");
        location(40,10);printf("蔬菜编号");
        location(50,10);printf("营养成分");
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            if(j%7==0&&j!=0)
            {
                printf("\n\n\t\t因本页无法正确显示更多信息，请按回车键翻页!");
                getchar();
                ClearScreen();
                ShowMenu();
                location(10,8);printf("分类编码");
                location(20,8);printf("分类名称");
                location(30,8);printf("蔬菜名称");
                location(40,8);printf("蔬菜编号");
                location(50,8);printf("营养成分");
                i=10;
            }
            j++;
            location(13,i);printf("%c",ptype->type);
            location(22,i);printf("%s",ptype->name);
            location(33,i);printf("%s",pbasic->name);
            location(42,i);printf("%d",pbasic->num);
            location(50,i);
            int k=0;
            pnutri=pbasic->snext;
            while(pnutri!=NULL)
            {
                printf("%s  ",pnutri->n);
                pnutri=pnutri->next;
                k++;
                if(k%4==0)
                {
                    i=i+1;
                    location(50,i);
                }
            }
            i=i+2;
            pbasic=pbasic->next;
        }
        printf("\n\n\t\t\t    按任意键继续。。。");
        getchar();
        ClearScreen();
        ShowMenu();
    }
    else
    {
        char *notice1[] = {"  该分类编码不存在!","查询蔬菜种类信息失败!",
                    "确认"
                    };
        ClearScreen();
        ShowMenu();
        ShowModule(notice1, 3);
    }
    return TRUE;
}

/********
函数名称：QueryBasicInfo
函数功能：查找蔬菜基本信息
输入参数：无
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL QueryBasicInfo(void)
{
    char *plabel_name1[] = {"主菜单项：数据查询",
                           "子菜单项：蔬菜基本信息",
                           "确认"
                          };
    ShowModule(plabel_name1, 3);
    char *plabel_name2[] = {"以蔬菜名称中文字符子串查询",
                            "以分类码和营养成分为条件查询",
                            "返回"
                            };
    int x=ShowModule3(plabel_name2, 3);
    BOOL flag=TRUE;
    switch(x)
    {
        case 1:
            flag=QueryBasicInfo1();
            break;
        case 2:
            flag=QueryBasicInfo2();
            break;
        case 3:
            return TRUE;
    }
    if(flag==FALSE)
    {
        char *notice3[] = {"未查询到与查找条件相符的信息!","   查询蔬菜种类信息失败!",
                    "确认"
                    };
        ClearScreen();
        ShowMenu();
        ShowModule(notice3, 3);
    }
    ClearScreen();
    ShowMenu();
    return TRUE;
}

/********
函数名称：QueryBasicInfo1
函数功能：以蔬菜名称中文字符子串查询蔬菜基本信息
输入参数：无
输出参数：无
返 回 值：BOOL类型，查询到结果返回TRUE，否则返回FALSE
调用说明：无
********/
BOOL QueryBasicInfo1(void)
{
    char name[20];
    T *ptype=gp_head;;
    B *pbasic;
    N *pnutri;
    int find=0;
    int i=10,j=0;

    location(15,6);printf("请输入所要查找的名称子串信息：");
    location(45,6);scanf("%s",name);
    getchar();
    location(10,8);printf("分类编码");
    location(20,8);printf("分类名称");
    location(30,8);printf("蔬菜名称");
    location(40,8);printf("蔬菜编号");
    location(50,8);printf("营养成分");

    while(ptype!=NULL)
    {
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            if(strstr(pbasic->name,name)!=NULL)
            {
                if(j%7==0&&j!=0)
                {
                    printf("\n\n\t\t因本页无法正确显示更多信息，请按回车键翻页!");
                    getchar();
                    ClearScreen();
                    ShowMenu();
                    location(10,8);printf("分类编码");
                    location(20,8);printf("分类名称");
                    location(30,8);printf("蔬菜名称");
                    location(40,8);printf("蔬菜编号");
                    location(50,8);printf("营养成分");
                    i=10;
                }
                j++;
                find=1;
                location(13,i);printf("%c",ptype->type);
                location(22,i);printf("%s",ptype->name);
                location(33,i);printf("%s",pbasic->name);
                location(42,i);printf("%d",pbasic->num);
                location(50,i);
                int k=0;
                pnutri=pbasic->snext;
                while(pnutri!=NULL)
                {
                    printf("%s  ",pnutri->n);
                    pnutri=pnutri->next;
                    k++;
                    if(k%4==0)
                    {
                        i=i+1;
                        location(50,i);
                    }
                }
                i=i+2;
            }
            pbasic=pbasic->next;
        }
        ptype=ptype->next;
    }
    if(find==0)return FALSE;
    printf("\n\n\t\t\t    按任意键继续。。。");
    getchar();
    return TRUE;
}

/********
函数名称：QueryBasicInfo2
函数功能：以分类码和营养成分为条件查询蔬菜基本信息
输入参数：无
输出参数：无
返 回 值：BOOL类型，查询到结果返回TRUE，否则返回FALSE
调用说明：无
********/
BOOL QueryBasicInfo2(void)
{
    T *ptype=gp_head;
    B *pbasic;
    N *pnutri;
    int find= 0;
    char type;
    char nutri[20];
    int i=12,j=0;

    location(15,6);printf("请输入所要查找的分类码：");
    location(45,6);scanf("%c",&type);
    location(15,8);printf("请输入所要查找的营养成分：");
    location(45,8);scanf("%s",nutri);
    getchar();

    location(15,10);printf("分类编码");
    location(25,10);printf("分类名称");
    location(35,10);printf("蔬菜名称");
    location(45,10);printf("蔬菜编号");

    while(ptype!=NULL)
    {
        if(ptype->type==type)
        {
            pbasic=ptype->snext;
            while(pbasic!=NULL)
            {
                pnutri=pbasic->snext;
                while(pnutri!=NULL)
                {
                    if(strcmp(pnutri->n,nutri)==0)
                    {
                        if(j%7==0&&j!=0)
                        {
                            printf("\n\n\t\t因本页无法正确显示更多信息，请按回车键翻页!");
                            getchar();
                            ClearScreen();
                            ShowMenu();
                            location(15,10);printf("分类编码");
                            location(25,10);printf("分类名称");
                            location(35,10);printf("蔬菜名称");
                            location(45,10);printf("蔬菜编号");
                            i=12;
                        }
                        j++;
                        find=1;
                        location(18,i);printf("%c",ptype->type);
                        location(27,i);printf("%s",ptype->name);
                        location(38,i);printf("%s",pbasic->name);
                        location(47,i);printf("%d",pbasic->num);
                        i=i+2;
                    }
                    pnutri=pnutri->next;
                }
                pbasic=pbasic->next;
            }
        }
        ptype=ptype->next;
    }
    if(find==0)return FALSE;
    printf("\n\n\t\t\t    按任意键继续。。。");
    getchar();
    return TRUE;
}

/********
函数名称：QueryPlantInfo
函数功能：查询蔬菜种植信息
输入参数：无
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL QueryPlantInfo(void)
{
    char *plabel_name1[] = {"主菜单项：数据查询",
                           "子菜单项：蔬菜种植信息",
                           "确认"
                          };
    ShowModule(plabel_name1, 3);
    char *plabel_name2[] = {"以蔬菜部分名称和种植年份为条件查询",
                            "     以蔬菜名称为条件查询",
                            "返回"
                            };
    int x=ShowModule3(plabel_name2, 3);
    BOOL flag=TRUE;
    switch(x)
    {
        case 1:
            flag=QueryPlantInfo1();
            break;
        case 2:
            flag=QueryPlantInfo2();
            break;
        case 3:
            return TRUE;
    }
    if(flag==FALSE)
    {
        char *notice3[] = {"未查询到与查找条件相符的信息!","   查询蔬菜种类信息失败!",
                    "确认"
                    };
        ClearScreen();
        ShowMenu();
        ShowModule(notice3, 3);
    }
    ClearScreen();
    ShowMenu();
    return TRUE;
}

/********
函数名称：QueryPlantInfo1
函数功能：以蔬菜部分名称和种植年份为条件查询蔬菜种植信息
输入参数：无
输出参数：无
返 回 值：BOOL类型，查询到结果返回TRUE，否则返回FALSE
调用说明：无
********/
BOOL QueryPlantInfo1(void)
{
    T *ptype=gp_head;
    B *pbasic;
    P *pplant;
    int find= 0;
    char name[20];
    char year[5];
    int i=12,j=0;

    location(10,6);printf("请输入所要查找的蔬菜的部分名称：");
    location(45,6);scanf("%s",name);
    location(15,8);printf("请输入所要查找的年份：");
    location(45,8);scanf("%s",year);
    getchar();

    location(10,10);printf("分类码");
    location(20,10);printf("分类名称");
    location(30,10);printf("蔬菜名称");
    location(40,10);printf("种植年份");
    location(50,10);printf("种植面积");
    location(60,10);printf("收获重量");

    ptype=gp_head;
    while(ptype!=NULL)
    {
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            if(strstr(pbasic->name,name)!=NULL)
            {
                pplant=pbasic->cnext;
                if(pplant==NULL)
                {
                    ClearScreen();
                    ShowMenu();
                    char *notice3[] = {"该蔬菜未录入任何种植信息",
                                        "确认"
                                        };
                    ShowModule(notice3, 2);
                    return FALSE;
                }
                while(pplant!=NULL)
                {
                    if(strcmp(pplant->year,year)==0)
                    {
                        if(j%7==0&&j!=0)
                        {
                            printf("\n\n\t\t因本页无法正确显示更多信息，请按回车键翻页!");
                            getchar();
                            ClearScreen();
                            ShowMenu();
                            location(10,10);printf("分类码");
                            location(20,10);printf("分类名称");
                            location(30,10);printf("蔬菜名称");
                            location(40,10);printf("种植年份");
                            location(50,10);printf("种植面积");
                            location(60,10);printf("收获重量");
                            i=12;
                        }
                        j++;
                        find=1;
                        location(13,i);printf("%c",ptype->type);
                        location(22,i);printf("%s",ptype->name);
                        location(32,i);printf("%s",pbasic->name);
                        location(41,i);printf("%s",pplant->year);
                        location(53,i);printf("%d",pplant->area);
                        location(60,i);printf("%f",pplant->h);
                        i=i+2;
                    }
                    pplant=pplant->next;
                }
            }
            pbasic=pbasic->next;
        }
        ptype=ptype->next;
    }
    if(find==0)return FALSE;
    printf("\n\n\t\t\t    按任意键继续。。。");
    getchar();
    return TRUE;
}

/********
函数名称：QueryPlantInfo2
函数功能：以蔬菜名称为条件查询蔬菜种植信息
输入参数：无
输出参数：无
返 回 值：BOOL类型，查询到结果返回TRUE，否则返回FALSE
调用说明：无
********/
BOOL QueryPlantInfo2(void)
{
    T *ptype=gp_head;
    B *pbasic;
    P *pplant;
    int find= 0;
    char name[20];
    int i=12;
    UpdateNum();

    location(10,6);printf("请输入所要查找的蔬菜的名称：");
    location(45,6);scanf("%s",name);
    getchar();
    location(10,8);printf("分类码：");
    location(30,8);printf("分类名称：");
    location(50,8);printf("蔬菜名称：");
    location(15,10);printf("编号");
    location(25,10);printf("种植年份");
    location(40,10);printf("种植面积");
    location(55,10);printf("收获重量");

    while(ptype!=NULL)
    {
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            if(strcmp(pbasic->name,name)==0)
            {
                find=1;
                location(20,8);printf("%c",ptype->type);
                location(40,8);printf("%s",ptype->name);
                location(60,8);printf("%s",pbasic->name);
                pplant=pbasic->cnext;
                if(pplant==NULL)
                {
                    ClearScreen();
                    ShowMenu();
                    char *notice3[] = {"该蔬菜未录入任何种植信息",
                                        "确认"
                                        };
                    ShowModule(notice3, 2);
                    return FALSE;
                }
                int j=0;
                while(pplant!=NULL)
                {
                    if(j%7==0&&j!=0&&pplant->next!=NULL)
                    {
                        printf("\n\n\t\t因本页无法正确显示更多信息，请按回车键翻页!");
                        getchar();
                        ClearScreen();
                        ShowMenu();
                        location(10,8);printf("分类码：");location(20,8);printf("%c",ptype->type);
                        location(30,8);printf("分类名称：");location(40,8);printf("%s",ptype->name);
                        location(50,8);printf("蔬菜名称：");location(60,8);printf("%s",pbasic->name);
                        location(15,10);printf("编号");
                        location(25,10);printf("种植年份");
                        location(40,10);printf("种植面积");
                        location(55,10);printf("收获重量");
                        i=12;
                    }
                    j++;
                    location(16,i);printf("%d",pplant->n);
                    location(26,i);printf("%s",pplant->year);
                    location(43,i);printf("%d",pplant->area);
                    location(55,i);printf("%f",pplant->h);
                    i=i+2;
                    pplant=pplant->next;
                }
                break;
            }
            pbasic=pbasic->next;
        }
        if(find==1)break;
        ptype=ptype->next;
    }
    if(find==0)return FALSE;
    printf("\n\n\t\t\t    按任意键继续。。。");
    getchar();
    return TRUE;
}

/********
函数名称：StatVePlant
函数功能：统计某年各种类蔬菜种植情况
输入参数：无
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL StatVePlant(void)
{
    char *plabel_name[] = {"主菜单项：数据统计",
                           "子菜单项：某年各种类蔬菜种植信息",
                           "确认"
                          };
    ShowModule(plabel_name, 3);

    int find= 0;
    char year[5];
    int i=10;
    int len=0;
    T *ptype=gp_head;
    B *pbasic;
    P *pplant;
    struct y_p *head,*p;
    head=(struct y_p*)malloc(sizeof(struct y_p));
    head->next=NULL;

    location(15,6);printf("请输入所要查找的年份：");
    location(45,6);scanf("%s",year);
    getchar();

    p=head;
    while(ptype!=NULL)
    {
        p->type=ptype->type;
        strcpy(p->name,ptype->name);
        p->area=0;p->h=0;
        p->next=NULL;

        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            pplant=pbasic->cnext;
            while(pplant!=NULL)
            {
                if(strcmp(pplant->year,year)==0)
                {
                    find=1;
                    p->area=p->area+pplant->area;
                    p->h=p->h+pplant->h;
                    break;
                }
                pplant=pplant->next;
            }
            pbasic=pbasic->next;
        }
        ptype=ptype->next;
        if(ptype!=NULL)
        {
            p->next=(struct y_p*)malloc(sizeof(struct y_p));
            p=p->next;
        }
        len++;
    }
    if(find==0)
    {
        char *notice1[] = {"未查询到与查找条件相符的信息!","统计某一年各种类蔬菜种植信息失败!",
                    "确认"
                    };
        ClearScreen();
        ShowMenu();
        ShowModule(notice1, 3);
        return TRUE;
    }
    SortVePlant(head,len);
    location(15,8);printf("分类编码");
    location(27,8);printf("分类名称");
    location(40,8);printf("种植总面积");
    location(55,8);printf("收获总重量");
    p=head;
    int j=0;
    while(p!=NULL)
    {
        if(j%7==0&&j!=0&&p->next!=NULL)
        {
            printf("\n\n\t\t因本页无法正确显示更多信息，请按回车键翻页!");
            getchar();
            ClearScreen();
            ShowMenu();
            location(15,6);printf("分类编码");
            location(28,6);printf("分类名称");
            location(40,6);printf("种植总面积");
            location(55,6);printf("收获总重量");
            i=8;
        }
        j++;
        location(17,i);printf("%c",p->type);
        location(30,i);printf("%s",p->name);
        location(43,i);printf("%d",p->area);
        location(55,i);printf("%f",p->h);
        i=i+2;
        p=p->next;
    }
    printf("\n\n\t\t\t    按任意键继续。。。");
    getchar();
    ClearScreen();
    ShowMenu();
    return TRUE;
}

/********
函数名称：SortVePlant
函数功能：对StatVePlant函数的统计结果按总收获重量降序排序
输入参数：head为StatVePlant函数的统计结果链的头结点指针
           len为StatVePlant函数的统计结果链的长度
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL SortVePlant(struct y_p* head,int len)
{
    struct y_p *p=head,*q;
    int i,j;
    for(i=0;i<len-1;i++,p=p->next)                  /*通过数据域交换进行排序*/
    {
        for(j=i+1,q=p->next;j<len;j++,q=q->next)
        {
            if(p->h<q->h)
            {
                int area;
                float h;
                char type;
                char name[20];
                area=p->area;p->area=q->area;q->area=area;
                h=p->h;p->h=q->h;q->h=h;
                type=p->type;p->type=q->type;q->type=type;
                strcpy(name,p->name);strcpy(p->name,q->name);strcpy(q->name,name);
            }
        }
    }
}

/********
函数名称：StatTypeVePlant
函数功能：统计起止年间各种类蔬菜种植信息
输入参数：无
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL StatTypeVePlant(void)
{
    char *plabel_name[] = {"主菜单项：数据统计",
                           "子菜单项：起止年间各种类蔬菜种植信息",
                           "确认"
                          };
    ShowModule(plabel_name, 3);

    int find= 0;
    char year1[5];
    char year2[5];
    int i=10;
    int len=0;
    location(20,4);printf("请输入起始年份：");
    location(40,4);scanf("%s",year1);
    location(20,6);printf("请输入终止年份：");
    location(40,6);scanf("%s",year2);
    getchar();

    T *ptype=gp_head;
    B *pbasic;
    P *pplant;
    struct s_e_t *head,*p;
    head=(struct s_e_t*)malloc(sizeof(struct s_e_t));
    head->next=NULL;
    p=head;
    while(ptype!=NULL)                              /*遍历链表，建立新的统计链表同时记录统计链表的长度*/
    {
        strcpy(p->name,ptype->name);
        p->type=ptype->type;
        p->area=0;p->h=0;
        p->next=NULL;
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            pplant=pbasic->cnext;
            while(pplant!=NULL)
            {
                if(strcmp(pplant->year,year1)>=0&&strcmp(pplant->year,year2)<=0)
                {
                    find=1;
                    p->area=p->area+pplant->area;
                    p->h=p->h+pplant->h;
                }
                pplant=pplant->next;
            }
            pbasic=pbasic->next;
        }
        ptype=ptype->next;
        if(ptype!=NULL)
        {
            p->next=(struct s_e_t*)malloc(sizeof(struct s_e_t));
            p=p->next;
        }
        len++;
    }
    if(find==0)
    {
        char *notice1[] = {"未查询到与查找条件相符的信息!","统计起止年间各种类蔬菜种植信息失败!",
                    "确认"
                    };
        ClearScreen();
        ShowMenu();
        ShowModule(notice1, 3);
        return TRUE;
    }
    SortTypeVePlant(head,len);
    location(15,8);printf("分类编码");
    location(27,8);printf("分类名称");
    location(40,8);printf("种植总面积");
    location(55,8);printf("收获总重量");
    p=head;
    int j=0;
    while(p!=NULL)
    {
        if(j%7==0&&j!=0&&p->next!=NULL)
        {
            printf("\n\n\t\t因本页无法正确显示更多信息，请按回车键翻页！");
            getchar();
            ClearScreen();
            ShowMenu();
            location(15,6);printf("分类编码");
            location(27,6);printf("分类名称");
            location(40,6);printf("种植总面积");
            location(55,6);printf("收获总重量");
            i=8;
        }
        j++;
        location(18,i);printf("%c",p->type);
        location(30,i);printf("%s",p->name);
        location(43,i);printf("%d",p->area);
        location(55,i);printf("%f",p->h);
        i=i+2;
        p=p->next;
    }
    printf("\n\n\t\t\t    按任意键继续。。。");
    getchar();
    ClearScreen();
    ShowMenu();
    return TRUE;
}
/********
函数名称：SortVePlant
函数功能：对StatTypeVePlant函数的统计结果按收获重量降序排序
输入参数：head为StatVePlant函数的统计结果链的头结点指针
           len为StatVePlant函数的统计结果链的长度
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL SortTypeVePlant(struct s_e_t *head,int len)
{
    struct s_e_t *p=head,*q;
    int i,j;
    for(i=0;i<len-1;i++,p=p->next)                  /*通过数据域交换进行排序*/
    {
        for(j=i+1,q=p->next;j<len;j++,q=q->next)
        {
            if(p->h<q->h)
            {
                int area;
                float h;
                char type;
                char name[20];
                area=p->area;p->area=q->area;q->area=area;
                h=p->h;p->h=q->h;q->h=h;
                type=p->type;p->type=q->type;q->type=type;
                strcpy(name,p->name);strcpy(p->name,q->name);strcpy(q->name,name);
            }
        }
    }
}

/********
函数名称：StatVePlantTotal
函数功能：统计起止年间各蔬菜种植情况
输入参数：无
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL StatVePlantTotal(void)
{
    char *plabel_name[] = {"主菜单项：数据统计",
                           "子菜单项：起止年间各蔬菜种植信息",
                           "确认"
                          };
    ShowModule(plabel_name, 3);

    int find= 0;
    char year1[5];
    char year2[5];
    int i=10;
    int len=0;
    location(20,4);printf("请输入起始年份：");
    location(40,4);scanf("%s",year1);
    location(20,6);printf("请输入终止年份：");
    location(40,6);scanf("%s",year2);
    getchar();

    T *ptype=gp_head;
    B *pbasic;
    P *pplant;
    struct s_e_p *head,*p;
    head=(struct s_e_p*)malloc(sizeof(struct s_e_p));
    head->next=NULL;
    p=head;
    while(ptype!=NULL)                              /*遍历链表，建立新的统计链表同时记录统计链表的长度*/
    {
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            strcpy(p->t_name,ptype->name);
            strcpy(p->ve_name,pbasic->name);
            p->area=0;p->h=0;
            p->next=NULL;
            pplant=pbasic->cnext;
            while(pplant!=NULL)
            {
                if(strcmp(pplant->year,year1)>=0&&strcmp(pplant->year,year2)<=0)
                {
                    find=1;
                    p->area=p->area+pplant->area;
                    p->h=p->h+pplant->h;
                }
                pplant=pplant->next;
            }
            if(pbasic->next!=NULL||ptype->next!=NULL)
            {
                p->next=(struct s_e_p*)malloc(sizeof(struct s_e_p));
                p=p->next;
            }
            len++;
            pbasic=pbasic->next;
        }
        ptype=ptype->next;
    }
    if(find==0)
    {
        char *notice1[] = {"未查询到与查找条件相符的信息!","统计起止年间各种类蔬菜种植信息失败!",
                    "确认"
                    };
        ClearScreen();
        ShowMenu();
        ShowModule(notice1, 3);
        return TRUE;
    }
    SortVePlantTotal(head,len);
    location(15,8);printf("蔬菜名称");
    location(27,8);printf("分类名称");
    location(40,8);printf("种植总面积");
    location(55,8);printf("收获总重量");
    p=head;
    int j=0;
    while(p!=NULL)
    {
        if(j%7==0&&j!=0&&p->next!=NULL)
        {
            printf("\n\n\t\t因本页无法正确显示更多信息，请按回车键翻页！");
            getchar();
            ClearScreen();
            ShowMenu();
            location(15,6);printf("蔬菜名称");
            location(27,6);printf("分类名称");
            location(40,6);printf("种植总面积");
            location(55,6);printf("收获总重量");
            i=8;
        }
        j++;
        location(18,i);printf("%s",p->ve_name);
        location(30,i);printf("%s",p->t_name);
        location(43,i);printf("%d",p->area);
        location(55,i);printf("%f",p->h);
        i=i+2;
        p=p->next;
    }
    printf("\n\n\t\t\t    按任意键继续。。。");
    getchar();
    ClearScreen();
    ShowMenu();
    return TRUE;
}

/********
函数名称：SortVePlantTotal
函数功能：对StatVePlantTotal函数的统计结果按总收获重量降序排序
输入参数：head为StatVePlantTotal函数的统计结果链的头结点指针
           len为StatVePlantTotal函数的统计结果链的长度
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL SortVePlantTotal(struct s_e_p* head,int len)
{
    struct s_e_p *p=head,*q;
    int i,j;
    for(i=0;i<len-1;i++,p=p->next)                  /*通过数据域交换进行排序*/
    {
        for(j=i+1,q=p->next;j<len;j++,q=q->next)
        {
            if(p->h<q->h)
            {
                int area;
                float h;
                char name1[20];
                char name2[20];
                area=p->area;p->area=q->area;q->area=area;
                h=p->h;p->h=q->h;q->h=h;
                strcpy(name1,p->ve_name);strcpy(p->ve_name,q->ve_name);strcpy(q->ve_name,name1);
                strcpy(name2,p->t_name);strcpy(p->t_name,q->t_name);strcpy(q->t_name,name2);
            }
        }
    }
}

/********
函数名称：StatCount
函数功能：统计某种类蔬菜已有数量
输入参数：无
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL StatCount(void)
{
    char *plabel_name[] = {"主菜单项：数据统计",
                           "子菜单项：某蔬菜已有数量",
                           "确认"
                          };
    ShowModule(plabel_name, 3);

    int find= 0;
    int len=0;
    T *ptype=gp_head;
    B *pbasic;
    P *pplant;
    struct v_count *head,*p;
    head=(struct v_count*)malloc(sizeof(struct v_count));
    head->next=NULL;
    p=head;

    while(ptype!=NULL)
    {
        p->type=ptype->type;
        strcpy(p->name,ptype->name);
        p->h=0;
        p->next=NULL;
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            pplant=pbasic->cnext;
            while(pplant!=NULL)
            {
                find=1;
                p->h=p->h+pplant->h;
                pplant=pplant->next;
            }

            pbasic=pbasic->next;
        }
        ptype=ptype->next;
        if(ptype!=NULL)
        {
            p->next=(struct v_count*)malloc(sizeof(struct v_count));
            p=p->next;
        }
        len++;
    }
    if(find==0)
    {
        char *notice1[] = {"未输入任何蔬菜种植信息!","统计各种类蔬菜总数量失败!",
                    "确认"
                    };
        ShowModule(notice1, 3);
        return TRUE;
    }
    SortCount(head,len);
    location(15,6);printf("分类编码");
    location(35,6);printf("分类名称");
    location(55,6);printf("收获总重量");
    p=head;
    int j=0;
    int i=8;
    while(p!=NULL)                                  /*遍历链表，输出链表中信息*/
    {
        if(j%7==0&&j!=0&&p->next!=NULL)             /*考虑到屏幕行数较少，提示换页操作*/
        {
            printf("\n\n\t\t因本页无法正确显示更多信息，请按回车键翻页!");
            getchar();
            ClearScreen();
            ShowMenu();
            location(15,6);printf("分类编码");
            location(35,6);printf("分类名称");
            location(55,6);printf("收获总重量");
            i=8;
        }
        j++;
        location(17,i);printf("%c",p->type);
        location(37,i);printf("%s",p->name);
        location(55,i);printf("%f",p->h);
        i=i+2;
        p=p->next;
    }
    printf("\n\n\t\t\t    按任意键继续。。。");
    getchar();
    ClearScreen();
    ShowMenu();
    return TRUE;
}

/********
函数名称：SortCount
函数功能：对StatCount函数的统计结果按总数量降序排序
输入参数：head为StatCount函数的统计结果链的头结点指针
           len为StatCount函数的统计结果链的长度
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL SortCount(struct v_count*head,int len)
{
    struct v_count *p=head,*q;
    int i,j;
    for(i=0;i<len-1;i++,p=p->next)                  /*通过数据域交换进行排序*/
    {
        for(j=i+1,q=p->next;j<len;j++,q=q->next)
        {
            if(p->h<q->h)
            {
                float h;
                char type;
                char name[20];
                h=p->h;p->h=q->h;q->h=h;
                type=p->type;p->type=q->type;q->type=type;
                strcpy(name,p->name);strcpy(p->name,q->name);strcpy(q->name,name);
            }
        }
    }
}

/********
函数名称：StatVeNutri
函数功能：统计含有某种营养成分的蔬菜，并输出其有关信息
输入参数：无
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL StatVeNutri(void)
{
    char *plabel_name[] = {"主菜单项：数据统计",
                           "子菜单项：含有某营养成分的蔬菜",
                           "确认"
                          };
    ShowModule(plabel_name, 3);

    T *ptype=gp_head;
    B *pbasic;
    N *pnutri;
    int find= 0;
    char nutri[20];
    int i=12,j=0;

    location(15,6);printf("请输入所要查找的营养成分：");
    location(45,6);scanf("%s",nutri);
    getchar();
    location(15,10);printf("分类编码");
    location(25,10);printf("分类名称");
    location(35,10);printf("蔬菜名称");
    location(45,10);printf("蔬菜编号");

    while(ptype!=NULL)                              /*遍历链表，查询到符合条件的则按格式输出其相关信息*/
    {
        pbasic=ptype->snext;
        while(pbasic!=NULL)
        {
            pnutri=pbasic->snext;
            while(pnutri!=NULL)
            {
                if(strcmp(pnutri->n,nutri)==0)
                {
                    find=1;
                    if(j%5==0&&j!=0)                /*考虑到屏幕行数较少，提示换页操作*/
                    {
                        printf("\n\n\t\t因本页无法正确显示更多信息，请按回车键翻页!");
                        getchar();
                        ClearScreen();
                        ShowMenu();
                        location(15,6);printf("分类编码");
                        location(25,6);printf("分类名称");
                        location(35,6);printf("蔬菜名称");
                        location(45,6);printf("蔬菜编号");
                        i=8;
                    }
                    j++;
                    location(18,i);printf("%c",ptype->type);
                    location(27,i);printf("%s",ptype->name);
                    location(38,i);printf("%s",pbasic->name);
                    location(48,i);printf("%d",pbasic->num);
                    i=i+2;
                }
                pnutri=pnutri->next;
            }
            pbasic=pbasic->next;
        }
        ptype=ptype->next;
    }
    if(find==0)
    {
        char *notice1[] = {"未查询到与查找条件相符的信息!","   查询蔬菜种类信息失败!",
                    "确认"
                    };
        ClearScreen();
        ShowMenu();
        ShowModule(notice1, 3);
        return TRUE;
    }
    printf("\n\n\t\t\t    按任意键继续。。。");
    getchar();
    ClearScreen();
    ShowMenu();
    return TRUE;
}

/********
函数名称：HelpTopic
函数功能：帮助主题显示
输入参数：无
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL HelpTopic(void)
{
    char *plabel_name[] = {"主菜单项：帮助",
                           "子菜单项：帮助主题",
                           "确认"
                          };
    ShowModule(plabel_name, 3);
    printf("\n\n\n\n\n\t\t\t本程序支持中文输入，鼠标和键盘操作。\n\n");
    printf("\t\t\t按ALT+字母可以快捷选择主菜单。\n\n");
    printf("\t\t本程序因制作者技术不精，在许多地方的输入格式有严格要求。\n\n");
    printf("\t\t\t请务必严格遵守输入格式>");
    printf("\n\n\t\t\t按任意键继续。。。");
    getchar();
    ClearScreen();
    ShowMenu();
    return TRUE;
}

/********
函数名称：AboutDorm
函数功能：显示一些关于本程序的信息
输入参数：无
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL AboutDorm(void)
{
    char *plabel_name[] = {"主菜单项：帮助",
                           "子菜单项：关于...",
                           "确认"
                          };

    ShowModule(plabel_name, 3);

    printf("\n\n\n\n\n\n\t\t\t本程序由CSIE1601班李星儒制作。\n\n");
    printf("\t\t在此对在编写程序时提供帮助的同学们表示感谢!");
    printf("\n\n\t\t\t按任意键继续。。。");
    getchar();
    ClearScreen();
    ShowMenu();
    return TRUE;
}

/********
函数名称：ShowModule
函数功能：将一个“确认”字符串的标签束设置成热区并等待用户输入
输入参数：pString为指针，n为标签个数
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL ShowModule(char **pString, int n)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    BOOL bRet = TRUE;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;
    pos.Y = n + 5;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<n; i++) {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i;

    }
    str_len = strlen(pString[n-1]);
    aLoc[n-1].X = rcPop.Left + 3 + (maxlen-str_len)/2;
    aLoc[n-1].Y = aLoc[n-1].Y + 2;

    labels.pLoc = aLoc;

    areas.num = 1;
    SMALL_RECT aArea[] = {{aLoc[n-1].X, aLoc[n-1].Y,
                           aLoc[n-1].X + 3, aLoc[n-1].Y}};

    char aSort[] = {0};
    char aTag[] = {1};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    DealInput(&areas, &iHot);
    PopOff();

    return bRet;

}

/********
函数名称：ShowModule2
函数功能：将“录入”、“修改”、“删除”三个字符串的标签束设置成热区并等待用户输入
输入参数：pString为指针，n为标签个数
输出参数：无
返 回 值：用鼠标单击、按回车或空格时返回当前热区编号
调用说明：无
********/
int ShowModule2(char **pString, int n)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }
    if(maxlen<(strlen(pString[2])+strlen(pString[3])+strlen(pString[4])+7+7))
    {
        maxlen=(strlen(pString[2])+strlen(pString[3])+strlen(pString[4])+7+7);
    }

    pos.X = maxlen + 6;
    pos.Y = n - 2 + 5;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<n-2-1; i++) {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i;

    }
    for(i=n-2-1;i<n;i++)
    {
        aLoc[i].Y=rcPop.Top + 2 + n - 2 + 1;
    }
    str_len = strlen(pString[3]);
    aLoc[3].X = rcPop.Left + 3 + (maxlen-str_len)/2;
    aLoc[2].X=aLoc[3].X - 7;
    aLoc[4].X=aLoc[3].X + 7;


    labels.pLoc = aLoc;

    areas.num = 3;
    SMALL_RECT aArea[] = {{aLoc[2].X, aLoc[2].Y,aLoc[2].X + 3, aLoc[2].Y},
						  {aLoc[3].X, aLoc[3].Y,aLoc[3].X + 3, aLoc[3].Y},
						  {aLoc[4].X, aLoc[4].Y,aLoc[4].X + 3, aLoc[4].Y}
						  };

    char aSort[] = {0,0,0};
    char aTag[] = {1,2,3};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n-2;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    int x;
    x=DealInput(&areas, &iHot);
    PopOff();

    return x;
}

/********
函数名称：ShowModule3
函数功能：将两个字符串和一个“返回”字符串的标签束设置成热区并等待用户输入
输入参数：pString为指针，n为标签个数
输出参数：无
返 回 值：用鼠标单击、按回车或空格时返回当前热区编号
调用说明：无
********/
int ShowModule3(char **pString, int n)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len,x;

    for (i=0, maxlen=0; i<n; i++)
    {
        str_len = strlen(pString[i]);
        if (maxlen < str_len)
        {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;
    pos.Y = n + 5;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<n-1; i++)
    {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i*2;
    }
    aLoc[n-1].Y = rcPop.Top + 2 + n-1;

    str_len = strlen(pString[n-1]);
    aLoc[n-1].X = rcPop.Left + 3 + (maxlen-str_len)/2;
    aLoc[n-1].Y = aLoc[n-1].Y + 2;

    labels.pLoc = aLoc;

    areas.num = 3;
    SMALL_RECT aArea[] = {{aLoc[0].X, aLoc[0].Y,
                        aLoc[0].X + maxlen - 1, aLoc[0].Y},
                        {aLoc[1].X, aLoc[1].Y,
                        aLoc[1].X + maxlen - 1, aLoc[1].Y},
                        {aLoc[2].X, aLoc[2].Y,
                        aLoc[2].X + 3, aLoc[2].Y}
                        };

    char aSort[] = {0, 0, 0};
    char aTag[] = {1, 2, 3};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);
    x = DealInput(&areas, &iHot);
    PopOff();
    return x;
}

/********
函数名称：ShowModule4
函数功能：将三个字符串和一个“返回”字符串的标签束设置成热区并等待用户输入
输入参数：pString为指针，n为标签个数
输出参数：无
返 回 值：用鼠标单击、按回车或空格时返回当前热区编号
调用说明：无
********/
int ShowModule4(char **pString, int n)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len,x;

    for (i=0, maxlen=0; i<n; i++)
    {
        str_len = strlen(pString[i]);
        if (maxlen < str_len)
        {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;
    pos.Y = n + 5;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<n; i++)
    {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i;
    }

    str_len = strlen(pString[n-1]);
    aLoc[n-1].X = rcPop.Left + 3 + (maxlen-str_len)/2;
    aLoc[n-1].Y = aLoc[n-1].Y + 2;

    labels.pLoc = aLoc;

    areas.num = 4;
    SMALL_RECT aArea[] = {{aLoc[0].X, aLoc[0].Y,
                        aLoc[0].X + maxlen - 1, aLoc[0].Y},
                        {aLoc[1].X, aLoc[1].Y,
                        aLoc[1].X + maxlen - 1, aLoc[1].Y},
                        {aLoc[2].X, aLoc[2].Y,
                        aLoc[2].X + maxlen - 1, aLoc[2].Y},
                        {aLoc[3].X, aLoc[3].Y,
                        aLoc[3].X + 3, aLoc[3].Y}
                        };

    char aSort[] = {0, 0, 0, 0};
    char aTag[] = {1, 2, 3, 4};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 +n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);
    x = DealInput(&areas, &iHot);
	PopOff();
    return x;
}

/********
函数名称：ShowModule5
函数功能：将“确认”和“取消”两个字符串的标签束设置成热区并等待用户输入
输入参数：pString为指针，n为标签个数
输出参数：无
返 回 值：用鼠标单击、按回车或空格时返回当前热区编号
调用说明：无
********/
int ShowModule5(char **pString, int n)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    BOOL bRet = TRUE;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;
    pos.Y = n + 5;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 2;

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<n-2; i++) {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i;
    }
    aLoc[1].X = rcPop.Left + 10;aLoc[1].Y = aLoc[0].Y + 3;
    aLoc[2].X = rcPop.Left + 20;aLoc[2].Y = aLoc[0].Y + 3;
    labels.pLoc = aLoc;

    areas.num = 2;
    SMALL_RECT aArea[] = {{aLoc[1].X, aLoc[1].Y,aLoc[1].X + 3, aLoc[1].Y},
                          {aLoc[2].X, aLoc[2].Y,aLoc[2].X + 3, aLoc[2].Y}
                         };

    char aSort[] = {0,0};
    char aTag[] = {1,2};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n - 1;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    int x=DealInput(&areas, &iHot);
    PopOff();
    return x;
}

int main()
{
    COORD size = {SCR_COL, SCR_ROW};                /*窗口缓冲区大小*/

    gh_std_out = GetStdHandle(STD_OUTPUT_HANDLE);   /* 获取标准输出设备句柄*/
    gh_std_in = GetStdHandle(STD_INPUT_HANDLE);     /* 获取标准输入设备句柄*/

    SetConsoleTitle(gp_sys_name);                   /*设置窗口标题*/
    SetConsoleScreenBufferSize(gh_std_out, size);   /*设置窗口缓冲区大小80*25*/

    LoadData();                                     /*数据加载*/
    InitInterface();                                /*界面初始化*/
    RunSys(&gp_head);                               /*系统功能模块的选择及运行*/
    CloseSys(gp_head);                              /*退出系统*/

    return 0;
}

/********
函数名称：LoadData
函数功能：将四类基础数据从数据文件载入到内存缓冲区和十字链表中
输入参数：无
输出参数：无
返 回 值：BOOL类型，总是返回TRUE
调用说明：无
********/
BOOL LoadData()
{
	int Re = 0;

	Re = CreatList(&gp_head);
	if (Re < (1 | 2 | 4 | 8))
	{
		printf("\n系统基础数据不完整!\n");
	}
    printf("\n按任意键继续...\n");
    getchar();
	return TRUE;
}

/********
函数名称：CreatList
函数功能：从数据文件读取基础数据，并存在到所创建的十字链表中
输入参数：无
输出参数：phead为主链头指针的地址，用来返回所创建的十字链
返 回 值：int类型数值，表示链表创建的情况
           0 空链，无数据
           1 已加载蔬菜种类信息，无蔬菜基本信息、蔬菜营养成分和蔬菜种植信息
           3 已加载蔬菜种类信息和蔬菜基本信息，无蔬菜营养成分和蔬菜种植信息
           7 已加载蔬菜种类信息、蔬菜基本信息和蔬菜营养成分，无蔬菜种植信息
           15 四类基础数据都已加载
调用说明：无
********/
int CreatList(T **phead)
{
	T *hd = NULL, *pType, tmp1;
	B *pBasic,tmp2;
    N *pNutri,tmp3;
	P *pPlant, tmp4;
	FILE *pFile;
	int find;
	int re = 0;

	if ((pFile = fopen(gp_ve_t_info_filename, "rb")) == NULL)
	{
		printf("蔬菜种类信息数据文件打开失败!\n");
		return re;
	}
	printf("蔬菜种类信息数据文件打开成功!\n");

	/*从数据文件中读蔬菜种类信息数据，存入以后进先出方式建立的主链中*/
	while (fread(&tmp1, sizeof(T), 1, pFile) == 1)
	{
		pType = (T *)malloc(sizeof(T));
		*pType = tmp1;
		pType->snext = NULL;
		pType->next = hd;
		hd = pType;
	}
	fclose(pFile);

	if (hd == NULL)
	{
		printf("蔬菜种类信息数据文件加载失败!\n");
		return re;
	}
	printf("蔬菜种类信息数据文件加载成功!\n");
	*phead = hd;
	re += 1;

	if ((pFile = fopen(gp_ve_b_info_filename, "rb")) == NULL)
	{
		printf("蔬菜基本信息数据文件打开失败!\n");
		return re;
	}
	printf("蔬菜基本信息数据文件打开成功!\n");
	re += 2;

	/*从数据文件中读取蔬菜基本信息数据，存入主链对应结点的蔬菜基本信息支链中*/
	while (fread(&tmp2, sizeof(B), 1, pFile) == 1)
	{
		/*创建结点，存放从数据文件中读出的蔬菜基本信息*/
		pBasic = (B *)malloc(sizeof(B));
		*pBasic = tmp2;
		pBasic->cnext = NULL;
		pBasic->snext=NULL;

		/*在主链上查找该蔬菜所属的类别的主链结点*/
		pType = hd;
		while (pType != NULL && (pType->type) != (pBasic->type))
		{
			pType = pType->next;
		}

		if (pType != NULL)                          /*如果找到，则将结点以后进先出方式插入蔬菜基本信息支链*/
		{
			pBasic->next = pType->snext;
			pType->snext = pBasic;
		}
		else                                        /*如果未找到，则释放所创建结点的内存空间*/
		{
			free(pBasic);
		}
	}
	fclose(pFile);

	if ((pFile = fopen(gp_ve_b_nutri_info_filename, "rb")) == NULL)
	{
		printf("菜农基本信息中的营养成分信息数据文件打开失败!\n");
		return re;
	}
	printf("菜农基本信息中的营养成分信息数据文件打开成功!\n");
	re += 4;

	/*从数据文件中读取营养成分信息数据，存入蔬菜基本信息支链对应结点的营养成分支链中*/
	while (fread(&tmp3, sizeof(N), 1, pFile) == 1)
	{
		/*创建结点，存放从数据文件中读取的菜农种植信息*/
		pNutri = (N *)malloc(sizeof(N));
		*pNutri = tmp3;

		/*查找蔬菜基本信息支链上对应蔬菜基本信息结点*/
		pType = hd;
		find = 0;
		while (pType != NULL&&find == 0)
		{
		    if(pType->type==pNutri->type)
		    {
                pBasic = pType->snext;
                while (pBasic != NULL&&find == 0)
                {
                    if ((pBasic->num) == (pNutri->num))
                    {
                        find = 1;
                        break;
                    }
                    pBasic = pBasic->next;
                }
		    }
			pType = pType->next;
		}
		if (find)                                   /*如果找到，则将结点一后进先出方式插入菜农种植信息支链中*/
		{
			pNutri->next = pBasic->snext;
			pBasic->snext = pNutri;
		}
		else   free(pNutri);
	}
	fclose(pFile);

	if ((pFile = fopen(gp_ve_p_info_filename, "rb")) == NULL)
	{
		printf("菜农种植信息数据文件打开失败!\n");
		return re;
	}
	printf("菜农种植信息数据文件打开成功!\n");
	re += 8;

	/*从数据文件中读取菜农种植信息数据，存入蔬菜基本信息支链对应结点的种植支链中*/
	while (fread(&tmp4, sizeof(P), 1, pFile) == 1)
	{
		/*创建结点，存放从数据文件中读取的菜农种植信息*/
		pPlant = (P *)malloc(sizeof(P));
		*pPlant = tmp4;

		/*查找蔬菜基本信息支链上对应蔬菜基本信息结点*/
		pType = hd;
		find = 0;
		while (pType != NULL&&find == 0)
		{
		    if(pType->type==pPlant->type)
		    {
                pBasic = pType->snext;
                while (pBasic != NULL&&find == 0)
                {
                    if ((pBasic->num) == (pPlant->num))
                    {
                        find = 1;
                        break;
                    }
                    pBasic = pBasic->next;
                }
		    }
            pType = pType->next;
		}
		if (find)                                   /*如果找到，则将结点一后进先出方式插入菜农种植信息支链中*/
		{
			pPlant->next = pBasic->cnext;
			pBasic->cnext = pPlant;
		}
		else   free(pPlant);
	}
	fclose(pFile);

	return re;
}

/********
函数名称：CloseSys
函数功能：关闭系统
输入参数：hd为主链头指针
输出参数：无
返 回 值：void类型，无返回值
调用说明：无
********/
void CloseSys(T *hd)
{
	T *pType1 = hd, *pType2;
	B *pBasic1, *pBasic2;
	P *pPlant1, *pPlant2;
	N *pNutri1,*pNutri2;

	while (pType1 != NULL)                          /*释放十字交叉链表的动态存储区*/
	{
		pType2 = pType1->next;
		pBasic1 = pType1->snext;
		while (pBasic1 != NULL)                     /*释放蔬菜基本信息支链的动态存储区*/
		{
			pBasic2 = pBasic1->next;

			pNutri1=pBasic1->snext;
			while(pNutri1!=NULL)
			{
			    pNutri2=pNutri1->next;
			    free(pNutri1);
			    pNutri1=pNutri2;
			}

			pPlant1 = pBasic1->cnext;
			while (pPlant1 != NULL)                 /*释放菜农种植信息支链的动态存储区*/
			{
				pPlant2 = pPlant1->next;
				free(pPlant1);
				pPlant1 = pPlant2;
			}
			free(pBasic1);
			pBasic1 = pBasic2;
		}
		free(pType1);                               /*释放主链结点的动态存储区*/
		pType1 = pType2;
	}
	ClearScreen();                                  /*清屏*/
	free(gp_buff_menubar_info);                     /*释放存放菜单条信息动态存储区*/
	CloseHandle(gh_std_out);                        /*关闭标准输入设备句柄*/
	CloseHandle(gh_std_in);                         /*关闭标准输出设备句柄*/
	SetConsoleTitle("运行结束");                    /*将窗口标题栏置为运行结束*/
	return;
}

/********
函数名称：PopMenu
函数功能：弹出指定主菜单项对应的子菜单
输入参数：num为指定的主菜单项号
输出参数：无
返 回 值：void类型，无返回值
调用说明：无
********/
void PopMenu(int num)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    char *pCh;
    int i, j, loc = 0;

    if (num != gi_sel_menu)                         /*如果指定主菜单不是已选中菜单*/
    {
        if (gp_top_layer->LayerNo != 0)             /*如果此前已有子菜单弹出*/
        {
            PopOff();
            gi_sel_sub_menu = 0;
        }
    }
    else if (gp_top_layer->LayerNo != 0)            /*若已弹出该子菜单，则返回*/
    {
        return;
    }

    gi_sel_menu = num;                              /*将选中主菜单项置为指定的主菜单项*/
    TagMainMenu(gi_sel_menu);                       /*在选中的主菜单项上做标记*/
    LocSubMenu(gi_sel_menu, &rcPop);                /*计算弹出子菜单的区域位置, 存放在rcPop中*/

    /*计算该子菜单中的第一项在子菜单字符串数组中的位置(下标)*/
    for (i=1; i<gi_sel_menu; i++)
    {
        loc += ga_sub_menu_count[i-1];
    }
    /*将该组子菜单项项名存入标签束结构变量*/
    labels.ppLabel = ga_sub_menu + loc;             /*标签束第一个标签字符串的地址*/
    labels.num = ga_sub_menu_count[gi_sel_menu-1];  /*标签束中标签字符串的个数*/
    COORD aLoc[labels.num];                         /*定义一个坐标数组，存放每个标签字符串输出位置的坐标*/
    for (i=0; i<labels.num; i++)                    /*确定标签字符串的输出位置，存放在坐标数组中*/
    {
        aLoc[i].X = rcPop.Left + 2;
        aLoc[i].Y = rcPop.Top + i + 1;
    }
    labels.pLoc = aLoc;                             /*使标签束结构变量labels的成员pLoc指向坐标数组的首元素*/
    /*设置热区信息*/
    areas.num = labels.num;                         /*热区的个数，等于标签的个数，即子菜单的项数*/
    SMALL_RECT aArea[areas.num];                    /*定义数组存放所有热区位置*/
    char aSort[areas.num];                          /*定义数组存放所有热区对应类别*/
    char aTag[areas.num];                           /*定义数组存放每个热区的编号*/
    for (i=0; i<areas.num; i++)
    {
        aArea[i].Left = rcPop.Left + 2;             /*热区定位*/
        aArea[i].Top = rcPop.Top + i + 1;
        aArea[i].Right = rcPop.Right - 2;
        aArea[i].Bottom = aArea[i].Top;
        aSort[i] = 0;                               /*热区类别都为0(按钮型)*/
        aTag[i] = i + 1;                            /*热区按顺序编号*/
    }
    areas.pArea = aArea;                            /*使热区结构变量areas的成员pArea指向热区位置数组首元素*/
    areas.pSort = aSort;                            /*使热区结构变量areas的成员pSort指向热区类别数组首元素*/
    areas.pTag = aTag;                              /*使热区结构变量areas的成员pTag指向热区编号数组首元素*/

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
    PopUp(&rcPop, att, &labels, &areas);
    DrawBox(&rcPop);                                /*给弹出窗口画边框*/
    pos.X = rcPop.Left + 2;
    for (pos.Y=rcPop.Top+1; pos.Y<rcPop.Bottom; pos.Y++)
    {                                               /*此循环用来在空串子菜项位置画线形成分隔，并取消此菜单项的热区属性*/
        pCh = ga_sub_menu[loc+pos.Y-rcPop.Top-1];
        if (strlen(pCh)==0)                         /*串长为0，表明为空串*/
        {                                           /*首先画横线*/
            FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-3, pos, &ul);
            for (j=rcPop.Left+2; j<rcPop.Right-1; j++)
            {                                       /*取消该区域字符单元的热区属性*/
                gp_scr_att[pos.Y*SCR_COL+j] &= 3;   /*按位与的结果保留了低两位*/
            }
        }

    }
    /*将子菜单项的功能键设为白底红字*/
    pos.X = rcPop.Left + 3;
    att =  FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
    for (pos.Y=rcPop.Top+1; pos.Y<rcPop.Bottom; pos.Y++)
    {
        if (strlen(ga_sub_menu[loc+pos.Y-rcPop.Top-1])==0)
        {
            continue;                               /*跳过空串*/
        }
        FillConsoleOutputAttribute(gh_std_out, att, 1, pos, &ul);
    }
    return;
}

/********
函数名称：PopUp
函数功能：在指定区域输入弹出窗口信息并设置热区，将弹出窗口信息位置入栈
输入参数：pRc为弹出窗口位置数据存放的地址
           att为弹出窗口区域字符属性
           pLabel为弹出窗口中标签束信息存放的地址
           pHotArea为弹出窗口中热区信息存放的地址
输出参数：无
返 回 值：void类型，无返回值
调用说明：无
********/
void PopUp(SMALL_RECT *pRc, WORD att, LABEL_BUNDLE *pLabel, HOT_AREA *pHotArea)
{
    LAYER_NODE *nextLayer;
    COORD size;
    COORD pos = {0, 0};
    char *pCh;
    int i, j, row;

    /*弹出窗口所在位置字符单元信息入栈*/
    size.X = pRc->Right - pRc->Left + 1;            /*弹出窗口的宽度*/
    size.Y = pRc->Bottom - pRc->Top + 1;            /*弹出窗口的高度*/
    /*申请存放弹出窗口相关信息的动态存储区*/
    nextLayer = (LAYER_NODE *)malloc(sizeof(LAYER_NODE));
    nextLayer->next = gp_top_layer;
    nextLayer->LayerNo = gp_top_layer->LayerNo + 1;
    nextLayer->rcArea = *pRc;
    nextLayer->pContent = (CHAR_INFO *)malloc(size.X*size.Y*sizeof(CHAR_INFO));
    nextLayer->pScrAtt = (char *)malloc(size.X*size.Y*sizeof(char));
    pCh = nextLayer->pScrAtt;
    /*将弹出窗口覆盖区域的字符信息保存，用于在关闭弹出窗口时恢复原样*/
    ReadConsoleOutput(gh_std_out, nextLayer->pContent, size, pos, pRc);
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {                                               /*此二重循环将所覆盖字符单元的原先属性值存入动态存储区，便于以后恢复*/
        for (j=pRc->Left; j<=pRc->Right; j++)
        {
            *pCh = gp_scr_att[i*SCR_COL+j];
            pCh++;
        }
    }
    gp_top_layer = nextLayer;                       /*完成弹出窗口相关信息入栈操作*/
    /*设置弹出窗口区域字符的新属性*/
    pos.X = pRc->Left;
    pos.Y = pRc->Top;
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {
        FillConsoleOutputAttribute(gh_std_out, att, size.X, pos, &ul);
        pos.Y++;
    }
    /*将标签束中的标签字符串在设定的位置输出*/
    for (i=0; i<pLabel->num; i++)
    {
        pCh = pLabel->ppLabel[i];
        if (strlen(pCh) != 0)
        {
            WriteConsoleOutputCharacter(gh_std_out, pCh, strlen(pCh),
                                        pLabel->pLoc[i], &ul);
        }
    }
    /*设置弹出窗口区域字符单元的新属性*/
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {                                               /*此二重循环设置字符单元的层号*/
        for (j=pRc->Left; j<=pRc->Right; j++)
        {
            gp_scr_att[i*SCR_COL+j] = gp_top_layer->LayerNo;
        }
    }

    for (i=0; i<pHotArea->num; i++)
    {                                               /*此二重循环设置所有热区中字符单元的热区类型和热区编号*/
        row = pHotArea->pArea[i].Top;
        for (j=pHotArea->pArea[i].Left; j<=pHotArea->pArea[i].Right; j++)
        {
            gp_scr_att[row*SCR_COL+j] |= (pHotArea->pSort[i] << 6)
                                    | (pHotArea->pTag[i] << 2);
        }
    }
    return;
}

/********
函数名称：PopOff
函数功能：关闭顶层弹出窗口，恢复覆盖区域原外观和字符单元原属性
输入参数：无
输出参数：无
返 回 值：void类型，无返回值
调用说明：无
********/
void PopOff(void)
{
    LAYER_NODE *nextLayer;
    COORD size;
    COORD pos = {0, 0};
    char *pCh;
    int i, j;

    if ((gp_top_layer->next==NULL) || (gp_top_layer->pContent==NULL))
    {   /*栈底存放的主界面屏幕信息，不用关闭*/
        return;
    }
    nextLayer = gp_top_layer->next;
    /*恢复弹出窗口区域原外观*/
    size.X = gp_top_layer->rcArea.Right - gp_top_layer->rcArea.Left + 1;
    size.Y = gp_top_layer->rcArea.Bottom - gp_top_layer->rcArea.Top + 1;
    WriteConsoleOutput(gh_std_out, gp_top_layer->pContent, size, pos, &(gp_top_layer->rcArea));
    /*恢复字符单元原属性*/
    pCh = gp_top_layer->pScrAtt;
    for (i=gp_top_layer->rcArea.Top; i<=gp_top_layer->rcArea.Bottom; i++)
    {
        for (j=gp_top_layer->rcArea.Left; j<=gp_top_layer->rcArea.Right; j++)
        {
            gp_scr_att[i*SCR_COL+j] = *pCh;
            pCh++;
        }
    }
    free(gp_top_layer->pContent);    /*释放动态存储区*/
    free(gp_top_layer->pScrAtt);
    free(gp_top_layer);
    gp_top_layer = nextLayer;
    gi_sel_sub_menu = 0;
    return;
}

/********
函数名称：DrawBox
函数功能：子菜单打开时，在指定区域画边框
输入参数：pRc为存放区域位置信息的地址
输出参数：无
返 回 值：void类型，无返回值
调用说明：无
********/
void DrawBox(SMALL_RECT *pRc)
{
    char chBox[] = {'+','-'};                       /*画框用的字符*/
    COORD pos = {pRc->Left, pRc->Top};              /*定位在区域的左上角*/

    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*画边框左上角*/
    for (pos.X = pRc->Left + 1; pos.X < pRc->Right; pos.X++)
    {                                               /*此循环画上边框横线*/
        WriteConsoleOutputCharacter(gh_std_out, &chBox[1], 1, pos, &ul);
    }
    pos.X = pRc->Right;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*画边框右上角*/
    pos.X = pRc->Left;
    pos.Y = pRc->Bottom;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*画边框左下角*/
    for (pos.X = pRc->Left + 1; pos.X < pRc->Right; pos.X++)
    {                                               /*此循环画下边框横线*/
        WriteConsoleOutputCharacter(gh_std_out, &chBox[1], 1, pos, &ul);
    }
    pos.X = pRc->Right;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*画边框右下角*/
    return;
}

/********
函数名称：TagSubMenu
函数功能：在制定子菜单项上做选中标记
输入参数：num为选中的子菜单项号
输出参数：无
返 回 值：void类型，无返回值
调用说明：无
********/
void TagSubMenu(int num)
{
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int width;

    LocSubMenu(gi_sel_menu, &rcPop);                /*计算弹出子菜单的区域位置, 存放在rcPop中*/
    if ((num<1) || (num == gi_sel_sub_menu) || (num>rcPop.Bottom-rcPop.Top-1))
    {                                               /*如果子菜单项号越界，或该项子菜单已被选中，则返回*/
        return;
    }

    pos.X = rcPop.Left + 2;
    width = rcPop.Right - rcPop.Left - 3;
    if (gi_sel_sub_menu != 0)                       /*首先取消原选中子菜单项上的标记*/
    {
        pos.Y = rcPop.Top + gi_sel_sub_menu;
        att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
        FillConsoleOutputAttribute(gh_std_out, att, width, pos, &ul);
        pos.X += 1;
        att |=  FOREGROUND_RED;                     /*白底红字*/
        FillConsoleOutputAttribute(gh_std_out, att, 1, pos, &ul);
    }
    /*在制定子菜单项上做选中标记*/
    pos.X = rcPop.Left + 2;
    pos.Y = rcPop.Top + num;
    att = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;  /*黑底白字*/
    FillConsoleOutputAttribute(gh_std_out, att, width, pos, &ul);
    gi_sel_sub_menu = num;                          /*修改选中子菜单项号*/
    return;
}

/********
函数名称：LocSubMenu
函数功能：计算弹出子菜单区域左上角和右下角的位置
输入参数：num选中的主菜单项号
输出参数：rc存放区域位置信息的地址
返 回 值：void类型，无返回值
调用说明：无
********/
void LocSubMenu(int num, SMALL_RECT *rc)
{
    int i, len, loc = 0;

    rc->Top = 1;                                    /*区域的上边定在第2行，行号为1*/
    rc->Left = 1;
    for (i=1; i<num; i++)
    {                                               /*计算区域左边界位置, 同时计算第一个子菜单项在子菜单字符串数组中的位置*/
        rc->Left += strlen(ga_main_menu[i-1]) + 4;
        loc += ga_sub_menu_count[i-1];
    }
    rc->Right = strlen(ga_sub_menu[loc]);           /*暂时存放第一个子菜单项字符串长度*/
    for (i=1; i<ga_sub_menu_count[num-1]; i++)
    {                                               /*查找最长子菜单字符串，将其长度存放在rc->Right*/
        len = strlen(ga_sub_menu[loc+i]);
        if (rc->Right < len)
        {
            rc->Right = len;
        }
    }
    rc->Right += rc->Left + 3;                      /*计算区域的右边界*/
    rc->Bottom = rc->Top + ga_sub_menu_count[num-1] + 1;/*计算区域下边的行号*/
    if (rc->Right >= SCR_COL)                       /*右边界越界的处理*/
    {
        len = rc->Right - SCR_COL + 1;
        rc->Left -= len;
        rc->Right = SCR_COL - 1;
    }
    return;
}

/********
函数名称：DealInput
函数功能：在弹出窗口区域设置热区, 等待并相应用户输入
输入参数：pHotArea为热区范围
           piHot 焦点热区编号的存放地址, 即指向焦点热区编号的指针
输出参数：piHot 用鼠标单击、按回车或空格时返回当前热区编号
返 回 值：无
调用说明：无
********/
int DealInput(HOT_AREA *pHotArea, int *piHot)
{
    INPUT_RECORD inRec;
    CONSOLE_CURSOR_INFO lpCur;
    DWORD res;
    COORD pos = {0, 0};
    int num, arrow, iRet = 0;
    int cNo, cTag, cSort;                           /*cNo为层号, cTag为热区编号, cSort为热区类型*/
    char vkc, asc;                                  /*vkc为虚拟键代码, asc为字符的ASCII码值*/

    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    /*循环*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);
        if ((inRec.EventType == MOUSE_EVENT) &&
            (inRec.Event.MouseEvent.dwButtonState
             == FROM_LEFT_1ST_BUTTON_PRESSED))
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3;
            cTag = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2) & 15;
            cSort = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 6) & 3;

            if ((cNo == gp_top_layer->LayerNo) && cTag > 0)
            {
                *piHot = cTag;
                SetHotPoint(pHotArea, *piHot);
                if (cSort == 0)
                {
                    iRet = cTag;
                    return iRet;
                }
                else if(cTag == 0)
                {                                   /*如果点在非热点区域*/
                    GetConsoleCursorInfo(gh_std_out, &lpCur);
                    lpCur.bVisible = FALSE;
                    SetConsoleCursorInfo(gh_std_out, &lpCur);    /*隐藏光标*/
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT && inRec.Event.KeyEvent.bKeyDown)
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode;

            switch(vkc)
            {

            case 37 :                               /*处理上、左键*/
            case 38 :
                -- *piHot;
                if(*piHot < 1)
                {
                    *piHot = pHotArea->num;
                }
                SetHotPoint(pHotArea, *piHot);
                GetConsoleCursorInfo(gh_std_out, &lpCur);
                break;
            case 13 :                               /*回车键或空格表示按下当前按钮*/
            case 32 :
                if(pHotArea->pSort[*piHot-1] == 0)
                {                                   /*若为按钮*/
                    GetConsoleCursorInfo(gh_std_out, &lpCur);
                    lpCur.bVisible = FALSE;
                    SetConsoleCursorInfo(gh_std_out, &lpCur);    /*隐藏光标*/
                    iRet = *piHot;
                    return iRet;
                }
            case 39 :                               /*处理右、下键*/
            case 40 :
                ++ *piHot;
                if(*piHot > pHotArea->num)
                {
                    *piHot = 1;
                }
                SetHotPoint(pHotArea, *piHot);
                GetConsoleCursorInfo(gh_std_out, &lpCur);
                break;
            case 27 :                               /*按ESC键*/
                GetConsoleCursorInfo(gh_std_out, &lpCur);
                lpCur.bVisible = FALSE;
                SetConsoleCursorInfo(gh_std_out, &lpCur);       /*隐藏光标*/
                iRet = 27;
                return iRet;
            }
        }
    }
    return iRet;
}

/********
函数名称：SetHotPoint
函数功能：设置热区
输入参数：pHotArea为热区范围
           iHot为焦点热区编号
输出参数：无
返 回 值：void类型，无返回值
调用说明：无
********/
void SetHotPoint(HOT_AREA *pHotArea, int iHot)
{
    CONSOLE_CURSOR_INFO lpCur;
    COORD pos = {0, 0};
    WORD att1, att2;
    int i, width;

    att1 = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;  /*黑底白字*/
    att2 = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
    for (i=0; i<pHotArea->num; i++)
    {                                               /*将按钮类热区置为白底黑字*/
        pos.X = pHotArea->pArea[i].Left;
        pos.Y = pHotArea->pArea[i].Top;
        width = pHotArea->pArea[i].Right - pHotArea->pArea[i].Left + 1;
        if (pHotArea->pSort[i] == 0)
        {                                           /*热区是按钮类*/
            FillConsoleOutputAttribute(gh_std_out, att2, width, pos, &ul);
        }
    }

    pos.X = pHotArea->pArea[iHot-1].Left;
    pos.Y = pHotArea->pArea[iHot-1].Top;
    width = pHotArea->pArea[iHot-1].Right - pHotArea->pArea[iHot-1].Left + 1;
    if (pHotArea->pSort[iHot-1] == 0)
    {                                               /*被激活热区是按钮类*/
        FillConsoleOutputAttribute(gh_std_out, att1, width, pos, &ul);
    }
    else if (pHotArea->pSort[iHot-1] == 1)
    {                                               /*被激活热区是文本框类*/
        SetConsoleCursorPosition(gh_std_out, pos);
        GetConsoleCursorInfo(gh_std_out, &lpCur);
        lpCur.bVisible = TRUE;
        SetConsoleCursorInfo(gh_std_out, &lpCur);
    }
}

/********
函数名称：RunSys
函数功能：运行系统，在系统主界面下运行用户所选择的功能模块
输入参数：无
输出参数：phead为主链头指针的地址
返 回 值：void类型，无返回值
调用说明：无
********/
void RunSys(T **phead)
{
    INPUT_RECORD inRec;
    DWORD res;
    COORD pos = {0, 0};
    BOOL bRet = TRUE;
    int i, loc, num;
    int cNo, cAtt;                                  /*cNo为字符单元层号, cAtt为字符单元属性*/
    char vkc, asc;                                  /*vkc为虚拟键代码, asc为字符的ASCII码值*/

    while (bRet)
    {
        /*从控制台输入缓冲区中读一条记录*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);

        if (inRec.EventType == MOUSE_EVENT)         /*如果记录由鼠标事件产生*/
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;  /*获取鼠标坐标位置*/
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3; /*取该位置的层号*/
            cAtt = gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2;/*取该字符单元属性*/
            if (cNo == 0)                           /*层号为0，表明该位置未被弹出子菜单覆盖*/
            {
                /*cAtt > 0 表明该位置处于热区(主菜单项字符单元)
                  cAtt != gi_sel_menu 表明该位置的主菜单项未被选中
                  gp_top_layer->LayerNo > 0 表明当前有子菜单弹出*/
                if (cAtt > 0 && cAtt != gi_sel_menu && gp_top_layer->LayerNo > 0)
                {
                    PopOff();                       /*关闭弹出的子菜单*/
                    gi_sel_sub_menu = 0;            /*将选中子菜单项的项号置为0*/
                    PopMenu(cAtt);                  /*弹出鼠标所在主菜单项对应的子菜单*/
                }
            }
            else if (cAtt > 0)                      /*鼠标所在位置为弹出子菜单的菜单项字符单元*/
            {
                TagSubMenu(cAtt);                   /*在该子菜单项上做选中标记*/
            }

            if (inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)/*如果按下鼠标左边第一键*/
            {
                if (cNo == 0)                       /*层号为0，表明该位置未被弹出子菜单覆盖*/
                {
                    if (cAtt > 0)                   /*如果该位置处于热区(主菜单项字符单元)*/
                    {
                        PopMenu(cAtt);              /*弹出鼠标所在主菜单项对应的子菜单*/
                    }
                    /*如果该位置不属于主菜单项字符单元，且有子菜单弹出*/
                    else if (gp_top_layer->LayerNo > 0)
                    {
                        PopOff();                   /*关闭弹出的子菜单*/
                        gi_sel_sub_menu = 0;        /*将选中子菜单项的项号置为0*/
                    }
                }
                else                                /*层号不为0，表明该位置被弹出子菜单覆盖*/
                {
                    if (cAtt > 0)                   /*如果该位置处于热区(子菜单项字符单元)*/
                    {
                        PopOff();                   /*关闭弹出的子菜单*/
                        gi_sel_sub_menu = 0;        /*将选中子菜单项的项号置为0*/

                        /*执行对应功能函数:gi_sel_menu主菜单项号,cAtt子菜单项号*/
                        bRet = ExeFunction(gi_sel_menu, cAtt);
                    }
                }
            }
            else if (inRec.Event.MouseEvent.dwButtonState
                     == RIGHTMOST_BUTTON_PRESSED)   /*如果按下鼠标右键*/
            {
                if (cNo == 0)                       /*层号为0，表明该位置未被弹出子菜单覆盖*/
                {
                    PopOff();                       /*关闭弹出的子菜单*/
                    gi_sel_sub_menu = 0;            /*将选中子菜单项的项号置为0*/
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT       /*如果记录由按键产生*/
                 && inRec.Event.KeyEvent.bKeyDown)  /*且键被按下*/
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode;/*获取按键的虚拟键码*/
            asc = inRec.Event.KeyEvent.uChar.AsciiChar;/*获取按键的ASC码*/

            /*系统快捷键的处理*/
            if (vkc == 112)                         /*如果按下F1键*/
            {
                if (gp_top_layer->LayerNo != 0)     /*如果当前有子菜单弹出*/
                {
                    PopOff();                       /*关闭弹出的子菜单*/
                    gi_sel_sub_menu = 0;            /*将选中子菜单项的项号置为0*/
                }
                bRet = ExeFunction(5, 1);           /*运行帮助主题功能函数*/
            }
            else if (inRec.Event.KeyEvent.dwControlKeyState
                     & (LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED))
            {                                       /*如果按下左或右Alt键*/
                switch (vkc)                        /*判断组合键Alt+字母*/
                {
                    case 88:                        /*Alt+X 退出*/
                        if (gp_top_layer->LayerNo != 0)
                        {
                            PopOff();
                            gi_sel_sub_menu = 0;
                        }
                        bRet = ExeFunction(1,4);
                        break;
                    case 70:                        /*Alt+F*/
                        PopMenu(1);
                        break;
                    case 77:                        /*Alt+M*/
                        PopMenu(2);
                        break;
                    case 81:                        /*Alt+Q*/
                        PopMenu(3);
                        break;
                    case 83:                        /*Alt+S*/
                        PopMenu(4);
                        break;
                    case 72:                        /*Alt+H*/
                        PopMenu(5);
                        break;
                }
            }
            else if (asc == 0)                      /*其他控制键的处理*/
            {
                if (gp_top_layer->LayerNo == 0)     /*如果未弹出子菜单*/
                {
                    switch (vkc)                    /*处理方向键(左、右、下)，不响应其他控制键*/
                    {
                        case 37:
                            gi_sel_menu--;
                            if (gi_sel_menu == 0)
                            {
                                gi_sel_menu = 5;
                            }
                            TagMainMenu(gi_sel_menu);
                            break;
                        case 39:
                            gi_sel_menu++;
                            if (gi_sel_menu == 6)
                            {
                                gi_sel_menu = 1;
                            }
                            TagMainMenu(gi_sel_menu);
                            break;
                        case 40:
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                    }
                }
                else                                /*已弹出子菜单时*/
                {
                    for (loc=0,i=1; i<gi_sel_menu; i++)
                    {
                        loc += ga_sub_menu_count[i-1];
                    }                               /*计算该子菜单中的第一项在子菜单字符串数组中的位置(下标)*/
                    switch (vkc)                    /*方向键(左、右、上、下)的处理*/
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
            else if ((asc-vkc == 0) || (asc-vkc == 32)){  /*按下普通键*/
                if (gp_top_layer->LayerNo == 0)     /*如果未弹出子菜单*/
                {
                    switch (vkc)
                    {
                        case 70:                    /*f或F*/
                            PopMenu(1);
                            break;
                        case 77:                    /*m或M*/
                            PopMenu(2);
                            break;
                        case 81:                    /*q或Q*/
                            PopMenu(3);
                            break;
                        case 83:                    /*s或S*/
                            PopMenu(4);
                            break;
                        case 72:                    /*h或H*/
                            PopMenu(5);
                            break;
                        case 13:                    /*回车*/
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                    }
                }
                else                                /*已弹出子菜单时的键盘输入处理*/
                {
                    if (vkc == 27)                  /*如果按下ESC键*/
                    {
                        PopOff();
                        gi_sel_sub_menu = 0;
                    }
                    else if(vkc == 13)              /*如果按下回车键*/
                    {
                        num = gi_sel_sub_menu;
                        PopOff();
                        gi_sel_sub_menu = 0;
                        bRet = ExeFunction(gi_sel_menu, num);
                    }
                    else                            /*其他普通键的处理*/
                    {
                        /*计算该子菜单中的第一项在子菜单字符串数组中的位置(下标)*/
                        for (loc=0,i=1; i<gi_sel_menu; i++)
                        {
                            loc += ga_sub_menu_count[i-1];
                        }

                        /*依次与当前子菜单中每一项的代表字符进行比较*/
                        for (i=loc; i<loc+ga_sub_menu_count[gi_sel_menu-1]; i++)
                        {
                            if (strlen(ga_sub_menu[i])>0 && vkc==ga_sub_menu[i][1])
                            {                       /*如果匹配成功*/
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

/********
函数名称：InitInterface
函数功能：初始化界面
输入参数：无
输出参数：无
返 回 值：void类型，无返回值
调用说明：无
********/
void InitInterface()
{
    WORD att = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY ;

    SetConsoleTextAttribute(gh_std_out, att);       /*设置控制台屏幕缓冲区字符属性*/

    ClearScreen();                                  /* 清屏*/

    /*创建弹出窗口信息堆栈，将初始化后的屏幕窗口当作第一层弹出窗口*/
    gp_scr_att = (char *)calloc(SCR_COL * SCR_ROW, sizeof(char));/*屏幕字符属性*/
    gp_top_layer = (LAYER_NODE *)malloc(sizeof(LAYER_NODE));
    gp_top_layer->LayerNo = 0;                      /*弹出窗口的层号为0*/
    gp_top_layer->rcArea.Left = 0;                  /*弹出窗口的区域为整个屏幕窗口*/
    gp_top_layer->rcArea.Top = 0;
    gp_top_layer->rcArea.Right = SCR_COL - 1;
    gp_top_layer->rcArea.Bottom = SCR_ROW - 1;
    gp_top_layer->pContent = NULL;
    gp_top_layer->pScrAtt = gp_scr_att;
    gp_top_layer->next = NULL;

    ShowMenu();                                     /*显示菜单栏*/
    return;
}

/********
函数名称：ClearScreen
函数功能：清屏
输入参数：无
输出参数：无
返 回 值：void类型，无返回值
调用说明：无
********/
void ClearScreen(void)
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD home = {0, 0};
    unsigned long size;

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );/*取屏幕缓冲区信息*/
    size =  bInfo.dwSize.X * bInfo.dwSize.Y;        /*计算屏幕缓冲区字符单元数*/

    /*将屏幕缓冲区所有单元的字符属性设置为当前屏幕缓冲区字符属性*/
    FillConsoleOutputAttribute(gh_std_out, bInfo.wAttributes, size, home, &ul);

    /*将屏幕缓冲区所有单元填充为空格字符*/
    FillConsoleOutputCharacter(gh_std_out, ' ', size, home, &ul);
    return;
}

/********
函数名称：ShowMenu
函数功能：在屏幕上显示主菜单，并设置热区，在主菜单第一项上置选中标记
输入参数：无
输出参数：void类型，无返回值
返 回 值：无
调用说明：无
********/
void ShowMenu()
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    CONSOLE_CURSOR_INFO lpCur;
    COORD size;
    COORD pos = {0, 0};
    int i, j;
    int PosA = 2, PosB;
    char ch;

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );
    size.X = bInfo.dwSize.X;
    size.Y = 1;
    SetConsoleCursorPosition(gh_std_out, pos);
    for (i=0; i < 5; i++)                           /*在窗口第一行第一列处输出主菜单项*/
    {
        printf("  %s  ", ga_main_menu[i]);
    }

    GetConsoleCursorInfo(gh_std_out, &lpCur);
    lpCur.bVisible = FALSE;
    SetConsoleCursorInfo(gh_std_out, &lpCur);       /*隐藏光标*/

    /*申请动态存储区作为存放菜单条屏幕区字符信息的缓冲区*/
    gp_buff_menubar_info = (CHAR_INFO *)malloc(size.X * size.Y * sizeof(CHAR_INFO));
    SMALL_RECT rcMenu ={0, 0, size.X-1, 0} ;

    /*将窗口第一行的内容读入到存放菜单条屏幕区字符信息的缓冲区中*/
    ReadConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);

    /*将这一行中英文字母置为红色，其他字符单元置为白底黑字*/
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

    /*修改后的菜单条字符信息回写到窗口的第一行*/
    WriteConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);
    COORD endPos = {0, 1};
    SetConsoleCursorPosition(gh_std_out, endPos);   /*将光标位置设置在第2行第1列*/

    /*将菜单项置为热区，热区编号为菜单项号，热区类型为0(按钮型)*/
    i = 0;
    do
    {
        PosB = PosA + strlen(ga_main_menu[i]);      /*定位第i+1号菜单项的起止位置*/
        for (j=PosA; j<PosB; j++)
        {
            gp_scr_att[j] |= (i+1) << 2;            /*设置菜单项所在字符单元的属性值*/
        }
        PosA = PosB + 4;
        i++;
    } while (i<5);

    TagMainMenu(gi_sel_menu);                       /*在选中主菜单项上做标记，gi_sel_menu初值为1*/
    return;
}

/********
函数名称：TagMainMenu
函数功能：在指定主菜单项上置选中标记
输入参数：num为选中的主菜单项号
输出参数：无
返 回 值：void类型，无返回值
调用说明：无
********/
void TagMainMenu(int num)
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD size;
    COORD pos = {0, 0};
    int PosA = 2, PosB;
    char ch;
    int i;

    if (num == 0)                                   /*num为0时，将会去除主菜单项选中标记*/
    {
        PosA = 0;
        PosB = 0;
    }
    else                                            /*否则，定位选中主菜单项的起止位置: PosA为起始位置, PosB为截止位置*/
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

    /*去除选中菜单项前面的菜单项选中标记*/
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

    /*在选中菜单项上做标记，黑底白字*/
    for (i=PosA; i<PosB; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN
                                               | FOREGROUND_RED;
    }

    /*去除选中菜单项后面的菜单项选中标记*/
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

    /*将做好标记的菜单条信息写到窗口第一行*/
    SMALL_RECT rcMenu ={0, 0, size.X-1, 0};
    WriteConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);
    return;
}
