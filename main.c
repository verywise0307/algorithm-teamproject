//�ܼ�â �̻ڰ� ����� https://blog.naver.com/1hadonghun1/223080002491
//Ű �Է� �ޱ� https://dev-with-precious-dreams.tistory.com/7
//�۾� �� �ٲٱ� https://blog.naver.com/broadlg/222587279759
//�۾� �� �ٲٱ�2 https://louky0714.tistory.com/155
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

#define _CRT_SECURE_NO_WARNINGS
#define col 150; //������ ����
#define row 50; // ������ ����
#define gaugey 9
int mainstarttime = 0;
int day = 0;

int currenttime;
int maketime;
int fishnum = 0; //������� ������ȣ?
int amountoffish; //������ ����� ��
int inventory_full; //�κ��丮 ���� á����.
int inventory_weight = 0; //�κ��丮 ���԰� �󸶳� á���� ����
char seaarray[35][150]; //�ٴ� �迭. ������� ���� �̵�ĭ�� 130.
int seaposarray[35][150]; //�ٴٹ迭���� ����� ��ĥ��
char shiparray[5][150]; //�ٴ� �迭. ������� ���� �̵�ĭ�� 130.
int scene = 0;
int money = 0;
int durability = 10; //���˴� ������
int d_stack = 0; //���˴� ������ ī��Ʈ
int pendulum = 15; //������ �������� �Ÿ�
int range = 5; //�̳� ����
int baitcount = 1; //�̳� ��
int strength = 800; //�ٷ�
int sense = 0; //�����
int repeat = 0; //������ ��Ÿ Ƚ�� *20%
int inventory_capacity = 10; //�κ��丮 ĭ
int inventory_w_capacity = 4000; //���� ����

int fishcode[7]; //����⸦ ���� � ��Ҵ��� ���
int wincondition = 0;
int fishcondition = 0;
int moneycondition = 0;

typedef struct fish { //����� ����ü
    int code; //����
    char name[20];
    int num; //������ȣ
    int size;
    char shape[10];
    int x;
    int y;
    int distance;
    int speed;
    int weight;
    int price;
    struct fish* link;
}fish;

typedef struct player { //�÷��̾� ���� ����ü
    int x; //�̳� ��ġ
    int y; //�̳� ��ġ
    int active;
}player;

typedef struct Inventory { //�κ��丮 1ĭ ����ü
    int code; //����� �ڵ�
    int weight; //����
    int price; //����
}Inventory;

Inventory inventory[35];

//��ųƮ�� ���� 
#define MAX_SKILL 21 //��ų �����Ѱ�(��������)
#define INF 1000000
#define TRUE 1
#define FALSE 0
#define skillx 30
#define skilly 5
typedef struct skilltree {
    int n;
    int weight[MAX_SKILL][MAX_SKILL];
}skilltree;

typedef struct Skillpos {
    int x;
    int y;
    int size;
}Skillpos;

Skillpos skillpos[21];
int D[MAX_SKILL]; //�ִ� ��� �Ÿ�
int pre[MAX_SKILL]; //������ ��
int active_t[MAX_SKILL]; //Ȱ��ȭ�� ��ų 0, 1�� ����
int amountofskill = 1; //Ȱ��ȭ�� ��ų ��
int active_code[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //�ڵ� �� Ȱ��ȭ ��
int skillcode[MAX_SKILL] = { 0, 1, 5, 3, 2, 4, 8, 5, 6, 6, 7, 4, 7, 1, 3, 5, 4, 8, 2, 3, 0 }; //��ų ������ �ڵ�
//��ųƮ�� ����

void gotoxy() {
    COORD pos = {0, 0};//���⸸ �ٲ�
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void gotoxy1(int x, int y)
{
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void main_art()
{
    printf("����������������������������������������������������������������������������\n");
    printf("                                                                                                                                                      \n");
    printf("                                                        .rsSBP77:                             M7                                                      \n");
    printf("                                                   rDBBBBZgBq  :IQI                   bb                                                              \n");
    printf("                                               7QBQBQv   rJ.      IBr                         rBQ:                                                    \n");
    printf("                                            UQBBBi    .uK:          BQ        bb       .Bq.   BP Bi            .i.                                    \n");
    printf("                                         rBBBU     ijSv.             BQ                BDLQBr.B. vB:         JB1BBBBRj                                \n");
    printf("                                       7BBBi  :rjJv:                  BK         UQ.   B   :QQB   1B.      .BB  Q.  BQBQI                             \n");
    printf("                                     :BBUiSrrrr                       :B         .QXMLBQ          :BB     :B E  P   B  BBBBi                          \n");
    printf("                                    BBB  M                             Q.         dj vg       .EBQBu.     B .QrsMZZPB5:B.:BBB7                        \n");
    printf("                                  rBB:  SX                             B           B:      :QBBB:     :KBBBBBQZZSbbd5gBBBBBBBBBr                      \n");
    printf("                                 QBM   iB                             BB           iB   7QBBM.     UBBer                     rBBBBQr                  \n");
    printf("                                BBr   .B                             7B             RBBBBd.    .dBe          BB          XQ     :QQBBBL               \n");
    printf("                              .BB.    B.                            iB:              bb      JBBB. :Bb      :BB         BQP        .qBBBB.            \n");
    printf("                             .BB     B.                            jB.                     ZQB2   QBB.      BBBBQQ     BB.     gB     .QBBB:          \n");
    printf("                            .BB    iB.                            MB                     KBB7    BBB        BBs       BBB.     ZB        5BBQ         \n");
    printf("                            BBvsiibD                             Ur                    iBBL     QBB   rBB:  QB       BB:BB     BQ    :1I.  QBBr       \n");
    printf("                           BBQ  ri.                                                   QBB       BBBBBBB2.           bBJ .QB    BB   BBBQBB  .BBP      \n");
    printf("         ebb.             BBSQ                 vs                  bbb              iBBE  BBB            rBBBBBB   iBB   BQ   :BD  BB:  .BB   ZBB     \n");
    printf("        gBBBB            DBvjq                 BBv              :BBBBBBB.          5BBi   BBB       BBBQBBB  :BBd  BB.   XBZ  BB:  5Bg  MQu M. uBJ    \n");
    printf("        QBBBBB          rBB Q                  BQB   rbBQ      .BBE   BBB         dBX              BQR: :BB:  BBR  BB    .BQ  BB    LBBBBu :B5  BB    \n");
    printf("        rBBBBBX         BB iB      qBBBBg.     KBBBBBBBBB      iBBI :JBBB        YBB.   eBBBBBBB         BBP  BBr             Bg     :BP   BB   .BQ   \n");
    printf("          QBBB         BBi B      BBBRQBBBj     5BBDv           2BQBBBPi        5BBBQBQBBZ5r:            BB                           BB   BB    BB   \n");
    printf("        sZBBB1        sBQ RS     DBB    qBB          rEBBBBD        ..vPBBBB   bB BB                              PdDZZqXJi       gBBQBBQ  QRIBB .Bj  \n");
    printf("      2BBBBBQBBBs     QB 2b      gBB    sBB.    sBBBBBBBPv.     DBBBBBQBQEu:   BB  XQBBBBB         gRBBBBBrr      QBB     BBBBg:           B5     BB  \n");
    printf("     rBBBBBBBBBBBB:  SBj          BBB77DBBb     7BBr            BBZ5s.          Bg     .7IdMBQBBBBBr    :BB.     B7         iPBBBS    qBBB1       BR  \n");
    printf("     DBBBBBBBBBBBBB  BB:.5:       .BBBBBB:           i5BBBQ1                     gBBEs.                   vBB2   YQ:            ZBBu  BBi BBi     BS  \n");
    printf("     BBBBBBBBBBBBBBQPBEBBQB           PBB          BBBBBM5BB     BBg       iqQi    .2gBBBQq                 7BBBX MBJ             2BB  BB  BB    gB   \n");
    printf("     BBBBBQBBBBBBBBBBB:7BB            .BBv                BBK    gBB7YPBBBBBBBP          igB.                  YQBBBBB.             BB  EBBB     BQ   \n");
    printf("    LBBBBBBBBBBBBBBBBb.                BBQ   LE:     PBBBBBBg     BBBBBQBMU:               Bg                       .SU              BB         BB    \n");
    printf("    vBBBEsQBBBBBBBBBB7                 qBBBBBBBQ    bBBZ                                  dB          KY                              BB       BB.    \n");
    printf("          2BBBBBBBBBBQB2         iBBBBBBBQBQS:       BBU   rBBR                           :          RBBM                             :Br    :BQ.     \n");
    printf("           BBBBBBBBBBBBBBv       XBBBQ5i             .QBBBBBQBB                     BB:      rSZqY   iBBB:                             BS   gBQ       \n");
    printf("           .BBBBBBBBBQBQBQQ                      :     5P5u:                 .BB.  vBQB    QBQBBBQB:  BBBB  .YZBP         L:.         1Q. iQB7        \n");
    printf("             BBBBBQBBBBBBBBB                   vg:                  BB.      JBBQ   BBBd   BBBP7EBBB  .BBBQBBBBBB         BBBBBBBBQBBBBB RBL          \n");
    printf("             .BBBBBBBIBBBBBQb                 iQ                   .BBB       BBBI  gQBB         BBBi  MBBBBBMSr           BBYKgQMZQB7IBBM            \n");
    printf("              iBQBBBB  BBBQBD                 B.                   rBBB       2BQBQBQBBBX       .BBB.   BBBv                QD:ri71L.jBB.             \n");
    printf("               dBQBQB.  BBBB2                UB                    iBBB        BBBBBgdBBB       dBBB    EBBB                BB.rIJrrBBB               \n");
    printf("                BBBBB:  QBBBr                Br                     BBBi       IQBB   BBBI      BBQr     BBBb               QBusr7gBBS                \n");
    printf("                BBBBB  UBBBB.                B.                     BBBR    .51 BBBS  qBBB      2P.      rBBv               BBivRQBM                  \n");
    printf("                uBBBB  BBBBB                 BQ            :        iBBB2:1BBBB7rBBB   BBB.                                KBr5BBE                    \n");
    printf("                .BBQB. QBBBBQBD               BQv       rEBX         2BBBBBBBB5                                           qBBQBU                      \n");
    printf("                 BBBB   BBBBBBBB               igBBBBBBBR1             IMQd1.                                            BBBP:                        \n");
    printf("                 BBBB:                                                                                                  .P                            \n");
    printf("                 QQBBu                                                                                                                                \n");
    printf("                 LBBBQU                                     [ PRESE ANY KEY TO START ]                                                                \n");
    printf("                  BBQBBs                                                                                                                              \n");
    printf("                   rqPX                                                                                                                               \n");
    printf("                                                                                                                                                      \n");
    printf("����������������������������������������������������������������������������");
}

void story()
{
    printf("����������������������������������������������������������������������������\n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                             [ ������ ���� ���ÿ� ]                                                                   \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                      ��� ���ø� ��̷� �ϴ� ȸ����� ���                                                           \n");
    printf("                                                                                                                                                      \n");
    printf("                                                 ���۽����� ���� �ذ�� ��� �ż��� �Ǿ��������                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                        ���� �� �Ҿƹ����� ���� �� �����                                                           \n");
    printf("                                                                                                                                                      \n");
    printf("                                                              �ϼ̴� ������ ���� �ȴ�                                                                 \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                         �������� ��ü�Ҹ��� �ּҿ� �Բ�                                                              \n");
    printf("                                                                                                                                                      \n");
    printf("                                                 ������ ���ÿ��� �Ǿ� ����� �̾߱Ⱑ ���� �־���,                                                    \n");
    printf("                                                                                                                                                      \n");
    printf("                                               ������ ���� ����� ���ÿ��� �Ǳ� ���� ������ �����Ѵ�                                                  \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                              �����÷� �λ�����!                                                                      \n");
    printf("                                                               ������ ���� ���ÿ�!��                                                                  \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                      --->                                                                            \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("����������������������������������������������������������������������������");
}

void condition()
{
    printf("����������������������������������������������������������������������������\n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                         ���������������� ���ÿ�, ���� �̾߱� ����������                                              \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                               ------------ Ư���� �ɷ�, ������ ���� ------------                                                     \n");
    printf("                                                                                                                                                      \n");
    printf("                                                            �������� �̾߱⿡ ������                                                                  \n");
    printf("                                                                                                                                                      \n");
    printf("                                                          ���ÿտ��Դ� ������ �������                                                                \n");
    printf("                                                                                                                                                      \n");
    printf("                                                         Ư���� �ɷ��� �ִٰ� ��������.                                                               \n");
    printf("                                                                                                                                                      \n");
    printf("                                            ������ ���� �ǰ� �ʹٸ�  ������ ������ �ſ� �߿��� ���̴�.                                                \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                ------------ �ٴں��� �ö�� ���ÿ� ------------                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                ���ÿ��� ���� �ſ� ������ ���� ��Ҵٰ� ��������.                                                     \n");
    printf("                                                                                                                                                      \n");
    printf("                                                  ���Ӿ��� ���ø� ����  ������ �θ� �װ� �Ǿ���                                                       \n");
    printf("                                                                                                                                                      \n");
    printf("                                                       �װ� �� ���� ���� ���� ������� �Ѵ�.                                                          \n");
    printf("                                                                                                                                                      \n");
    printf("                          �ּ��� ��� ���� ������ ������ ���ÿ� Ÿ��Ʋ�� �ܴٸ� ���� ���� ��ĥ�� �ϴ� �Ͱ� �ٸ�����.                                \n");
    printf("                                                                                                                                                      \n");
    printf("                                                 ������ ���ÿ��� �Ǿ� ����� �̾߱Ⱑ ���� �־���,                                                    \n");
    printf("                                                                                                                                                      \n");
    printf("                                               ������ ���� ����� ���ÿ��� �Ǳ� ���� ������ �����Ѵ�                                                  \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                  ------------ ������� ��� �� ------------                                                          \n");
    printf("                                                                                                                                                      \n");
    printf("                                                     ���ÿտ��� �𸣴� ����Ⱑ ���ٰ� �Ѵ�.                                                          \n");
    printf("                                                                                                                                                      \n");
    printf("                                                      ������� ��ȣ �̳�, ����, ���� ����                                                             \n");
    printf("                                                                                                                                                      \n");
    printf("                                                           ��� ���� �� �ִ� ������                                                                   \n");
    printf("                                                                                                                                                      \n");
    printf("                                                       ����⸦ ���� ���� ��ұ� �����̴�.                                                            \n");
    printf("                                                                                                                                                      \n");
    printf("                                                       �ּ��� �� ����⸦ 15���� ��ƾ���                                                             \n");
    printf("                                                                                                                                                      \n");
    printf("                                                 �� ����⿡ ���� ��� ���� �� �� ���� ���̴�.                                                        \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                      --->                                                                            \n");
    printf("                                                                                                                                                      \n");
    printf("����������������������������������������������������������������������������");
}

void howtoplay()
{
    printf("����������������������������������������������������������������������������\n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                    ������������� ��� ����������                                                    \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                           ------------ ���� ------------                                                             \n");
    printf("                                                                                                                                                      \n");
    printf("                                                            �踦 �����̱� :  �¿� ����Ű                                                              \n");
    printf("                                                                                                                                                      \n");
    printf("                                                           �������� ������ : �����̽���                                                               \n");
    printf("                                                                                                                                                      \n");
    printf("                                                 ����⸦ ��� : ����Ⱑ ������ ���� �� �����̽���                                                   \n");
    printf("                                                                                                                                                      \n");
    printf("                                                 ����� ���� (�̴ϰ���) : 1�ʾȿ� �¿� ����Ű ��Ÿ                                                    \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                         ------------ ��ȣ�ۿ� ------------                                                           \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                     ���� : s                                                                         \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                   �κ��丮 : i                                                                       \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                         ------------ �ð����� ------------                                                           \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                     �� 15����                                                                        \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                   ���� �� 30��                                                                       \n");
    printf("                                                                                                                                                      \n");
    printf("                                                         15���� �̳��� ���ÿ��� �Ǿ�� ��                                                             \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                          ------------ ��Ÿ ------------                                                              \n");
    printf("                                                                                                                                                      \n");
    printf("                                                            ���� ���̳ʽ��� �Ǹ� �Ļ�                                                                 \n");
    printf("                                                                                                                                                      \n");
    printf("                                                     ���ô븦 �� �� ���� �� ���� ������ ����                                                          \n");
    printf("                                                                                                                                                      \n");
    printf("                                                 ���濡 ����⸦ ���� �� �ִ� ���Կ� �� ���� ����                                                     \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("����������������������������������������������������������������������������");
}

void intro()
{
    main_art(); _getch(); system("cls");
    story(); _getch(); system("cls");
    condition(); _getch(); system("cls");
    howtoplay(); _getch(); system("cls");
    scene = 1;
}

void skill_itd()
{
    gotoxy1(17, 23); printf("���� : ������ ���� �� �ִ� ������� �ִ� ���԰� �����մϴ�. (+1: 9kg) (+2: 20kg)");
    gotoxy1(17, 25); printf("ĭ : ���濡 ���� �� �ִ� ������� �ִ� ���� �����մϴ� (+1: 20) (+2: 30)");
    gotoxy1(17, 27); printf("������ : ���ô��� �������� �����մϴ� (+1: 20) (+2: 30)");
    gotoxy1(17, 29); printf("�̳� : ����⸦ �� ���� ���� ������ ���ų� �̳��� ���� ������ �����մϴ� (+1: ���� 6) (+2: ���� 2) (+3: ���� 7, ���� 3)");
    gotoxy1(17, 31); printf("����� : ������� �⺻ ������ ����մϴ� (+1: +10%%) (+2: +20%%) (+3: +30%%)");
    gotoxy1(17, 33); printf("���߷� : ����⸦ ��� �̴ϰ����� �� �������ϴ� (+1: ��Ÿ Ƚ�� -60%%) (+2: ��Ÿ Ƚ�� -80%%)");
    gotoxy1(17, 35); printf("�ٷ� : Ư�� ����⸦ ��ų� ���� ������ �� ���� ���� �� �ִ� �ٷ��� ������ŵ�ϴ� (+1: 1.2kg) (+2: 2kg) (+3: 3.5kg)");
    gotoxy1(17, 37); printf("�� : �������� �� �Ʒ����� ���� �� �ֽ��ϴ� (+1: 25) (+2: 35)");
    gotoxy1(17, 39); printf("������ ���� : ���ÿ��� ������ �ִ� ������ ����");
}

void victory()
{
    printf("����������������������������������������������������������������������������\n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                         ���������������� ���ÿ�, ���� �̾߱� ����������                                              \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                               ------------ Ư���� �ɷ�, ������ ���� ------------                                                     \n");
    printf("                                                                                                                                                      \n");
    printf("                                                            �������� �̾߱⿡ ������                                                                  \n");
    printf("                                                                                                                                                      \n");
    printf("                                                          ���ÿտ��Դ� ������ �������                                                                \n");
    printf("                                                                                                                                                      \n");
    printf("                                                         Ư���� �ɷ��� �ִٰ� ��������.                                                               \n");
    printf("                                                                                                                                                      \n");
    printf("                                            ������ ���� �ǰ� �ʹٸ�  ������ ������ �ſ� �߿��� ���̴�.                                                \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                ------------ �ٴں��� �ö�� ���ÿ� ------------                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                ���ÿ��� ���� �ſ� ������ ���� ��Ҵٰ� ��������.                                                     \n");
    printf("                                                                                                                                                      \n");
    printf("                                                  ���Ӿ��� ���ø� ����  ������ �θ� �װ� �Ǿ���                                                       \n");
    printf("                                                                                                                                                      \n");
    printf("                                                       �װ� �� ���� ���� ���� ������� �Ѵ�.                                                          \n");
    printf("                                                                                                                                                      \n");
    printf("                               �ּ��� n�� ������ ������ ���ÿ� Ÿ��Ʋ�� �ܴٸ� ���� ���� ��ĥ�� �ϴ� �Ͱ� �ٸ�����.                                 \n");
    printf("                                                                                                                                                      \n");
    printf("                                                 ������ ���ÿ��� �Ǿ� ����� �̾߱Ⱑ ���� �־���,                                                    \n");
    printf("                                                                                                                                                      \n");
    printf("                                               ������ ���� ����� ���ÿ��� �Ǳ� ���� ������ �����Ѵ�                                                  \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                  ------------ ������� ��� �� ------------                                                          \n");
    printf("                                                                                                                                                      \n");
    printf("                                                     ���ÿտ��� �𸣴� ����Ⱑ ���ٰ� �Ѵ�.                                                          \n");
    printf("                                                                                                                                                      \n");
    printf("                                                      ������� ��ȣ �̳�, ����, ���� ����                                                             \n");
    printf("                                                                                                                                                      \n");
    printf("                                                           ��� ���� �� �ִ� ������                                                                   \n");
    printf("                                                                                                                                                      \n");
    printf("                                                       ����⸦ ���� ���� ��ұ� �����̴�.                                                            \n");
    printf("                                                                                                                                                      \n");
    printf("                                                        �ּ��� �� ����⸦ n���� ��ƾ���                                                             \n");
    printf("                                                                                                                                                      \n");
    printf("                                                 �� ����⿡ ���� ��� ���� �� �� ���� ���̴�.                                                        \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                      --->                                                                            \n");
    printf("                                                                                                                                                      \n");
    printf("����������������������������������������������������������������������������");
}

void grandfather_soso()
{
    printf("����������������������������������������������������������������������������\n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                           :sdQBBBQBD5r.                                                                              \n");
    printf("                                                       7BBBBBPU7rr7YKRBBBBg:                                                                          \n");
    printf("                                                    7BBBK:               iqBBP                                                                        \n");
    printf("                                                  dQBI                      iBBB:                                                                     \n");
    printf("                                             .rrSBBi                           MQBr                                                                   \n");
    printf("                                           YBgQBBi                               5BQ:                                                                 \n");
    printf("                                          QBJEBZ                                   JB2                                                                \n");
    printf("                                         BB7.B1                                    :BQBQB.                                                            \n");
    printf("                                        :B  BP   r:v52IqX.           7PDbKuPb:    Bgi   EBB                                                           \n");
    printf("                                        BBsQB  PBK     1BB          BQ.      QB  rB. :vJi.BB:                                                         \n");
    printf("                                        BB Bu  PBRY7rJIQBU          rBBQQBBBDu   iB:      :BQ                                                         \n");
    printf("                                        7BjB                                     BY:rsuU7 .BD                                                         \n");
    printf("                                         7BB    iu7ririr7          .122XqEZRs     BB   ... uBK                                                        \n");
    printf("                                          gB    7PZdDZMQB. 7R      .EPq22Ju2r      BBKr..:rBB                                                         \n");
    printf("                                          BB              vB                        jB5UBUU:                                                          \n");
    printf("                                          BQ          :vurBB  iRBBBBBQ2.               7B                                                             \n");
    printf("                                          BB       jQBQ2riiBBBBB.  .:uQBBB:            BB5QBBBS:                                                      \n");
    printf("                                          BB     rBB7                   .gBB.          BQ   .vQQBBu                                                   \n");
    printf("                                          PB:   KBP                        BBj        bB:        UBBBi                                                \n");
    printf("                                           QB  iBS                          gBi      .BB            DBBr                                              \n");
    printf("                                           .BB dQ  .BBBU   .KBQBBB. vBBBBX. rBB      BQ               XBB.                                            \n");
    printf("                                            .BB7gBBBM.JQBQBQB7  :BBBBS  vBBBBP.    :BB                  BBq                                           \n");
    printf("                                              LBEr      .r.                       MBQ                    vQB                                          \n");
    printf("                                               dBBBr                            DBB:                      :QB                                         \n");
    printf("                                            .BBr  LBBB5.                     1BBQ.                         .BB                                        \n");
    printf("                                           7BQ       LBBBBBj::....    ::rPBBBBr   .:ri:                     rBg                                       \n");
    printf("                                          iBM            :YBBQQBBB   iIBBRr.   KBBQgPPPDQBdr                 BB.                                      \n");
    printf("                                          BB                BB        gBq    gBb.        .YQBZ                BB                                      \n");
    printf("                                         PBi                 UBBBQBBBBZ.    BB              QBEBBQ2:          BB                                      \n");
    printf("                                         QB           7.        :rr:        BB            qBY   .vRQBBr       rBu                                     \n");
    printf("                                         BB           BQ                    iBD        iQBQ:         qBB:      BR                                     \n");
    printf("                                        :Bb           BD                     LBBBDMQBBBZJ              PB      BB                                     \n");
    printf("                                        :B5           BD                     .BBBBBB  QI                       BB                                     \n");
    printf("                                        :Bd           BD                      BBBBBB   BB:                    .BZ                                     \n");
    printf("                                         BB          .BM                      BBBBBB    PBB.                  jBr                                     \n");
    printf("                                         BB           BM                      BBBBBB      BBBr                BB                                      \n");
    printf("                                         QB           BB                      qBQBBB        rBQBui.          .Bg                                      \n");
    printf("����������������������������������������������������������������������������\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("����������������������������������������������������������������������������");
}

void grandfather_angry()
{
    printf("����������������������������������������������������������������������������\n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                     .iY5EZDPSLi.                 q2  .X                                              \n");
    printf("                                                                 :DQBBBBgKXSPDBBBQBQ7             :BB PBu                                             \n");
    printf("                                                              iBBBM7              :SQBB:          .BQ  QBBB.                                          \n");
    printf("                                                            XQBd.                     EBBI      YBBY                                                  \n");
    printf("                                                        ..uBB7                          7BBR             rMQ.                                         \n");
    printf("                                                     7BDBBBi                              :QBg   :KBBB  BBs:                                          \n");
    printf("                                                    BBgSBP                                   BQ.    BB  BB                                            \n");
    printf("                                                   BB.:BY iQQBQv                  .YPS:      .BQBBs                                                   \n");
    printf("                                                  JB rBu  BB  .IQS             .bQu. sBD   :BQY.  QB7                                                 \n");
    printf("                                                  BBvQB    BBr   BB           gQ:   uBR    EB  .r7rvBQ                                                \n");
    printf("                                                  QP B:     :BBBXBQ           BB2ZBBj      dB  .    uBB                                               \n");
    printf("                                                  BBLB   BBi   .r.                  rX     iB.:ivJIv sBi                                              \n");
    printf("                                                   QBB    PBB7                  :DBBBX      Qq  ...  dQ7                                              \n");
    printf("                                                    Bg      1BBB.    v1      1BBB5.         .BBr:...iBB                                               \n");
    printf("                        .S:   BB                    BS        .B:   KB       r.               BBIUPSbi                                                \n");
    printf("                         qBB  BB   :I              .Bj           irrBB  .qQBBZKL:                QB                                                   \n");
    printf("                          YBY .BBBBBB              :BS       7QBBdjvPBQBBB:..ijQBBQu             BBXQBQX:                                             \n");
    printf("                         7BQ                        BB     rBBj       .           jBBP          .B1  .vDBBBP.                                         \n");
    printf("                        YBr       vBBB              BB    EBP                       :BB.        BB        rBBBS                                       \n");
    printf("                           qBP.  BB:                .Bg  jBJ                          BB       :BM           7BQQ                                     \n");
    printf("                          qZ7BBs dBBY              .rBBU BB  .dBD.    JBBBBY  rBBBB:  IBB      BB              :QBP                                   \n");
    printf("                              BQ   i7           rQBBY YBgvBgBBBrBBBDBBB1..XBBBBb .QBBQBQ:    :BB                 iBB.                                 \n");
    printf("                                             .DBBv     .BB5r:     YSr       ..              DBQ                    BBj                                \n");
    printf("                                           iBBb          iBBI                             qBB:                      PBq                               \n");
    printf("                                         7BBr              :BBQD:                      rBBQi                         qQI                              \n");
    printf("                                       iBB:                   rQBBBQ2.            .sQBBBj    ...                      BB:                             \n");
    printf("                                      BB:                         :2DBQBBBBQ   1EBBBI:   YBBBBRQRQQD7                  BB                             \n");
    printf("                                     MB                 i.           :BU        gBU    ZBR:        7MBB:               7BU                            \n");
    printf("                                     BZ              vE5BB             BBBPKPBBBB.    BB             iQBEQD2:           QB                            \n");
    printf("                                     BB            7BS  BB               iu557.       BB            IBr  .vEBBBI        RB.                           \n");
    printf("                                     IB           .B    BB                            MBi        .RBB:        7BBR      7Bv                           \n");
    printf("                                      BQ          .B    BB                             BBBPj2PBBBQZ.            .BB     iB5                           \n");
    printf("                                      rB:          BB   BB                             JBBBBBB.7B.                .     :BI                           \n");
    printf("                                       QB           Br  BB                             :BBBBBB  rBQ                     LB7                           \n");
    printf("                                        BB          :B  BB                              BBBBBB   .BB1                   MB.                           \n");
    printf("                                         BB          7B:BZ                              BBBBBB.    vBBq                 BB                            \n");
    printf("                                          QB.         .BBS                              BBBBBBr      .gBBSi.           iBJ                            \n");
    printf("����������������������������������������������������������������������������\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("����������������������������������������������������������������������������");
}

void grandfather_happy()
{
    printf("����������������������������������������������������������������������������\n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                      :7jKqP51r:                                                                      \n");
    printf("                                                                 .qQBBBBQEdPgQBBBBBDi                               :.                                \n");
    printf("                                                              :BBBBY.             ibBBQ.                          BBBBBB1                             \n");
    printf("                                                            uBBR:                    .RQBY                       BB.   rBB                            \n");
    printf("                                                        . vBBs                          sBBZ                     BB     BB                            \n");
    printf("                                                     rBDBQBv                              iBBP              ibM5..B    bB.                            \n");
    printf("                                                    QBQIBR      ..             .            .BB            BBu7bBBBB  BBBDBBQB7                       \n");
    printf("                                                   BB.:BU   YZd5gBBd         dBSdMgU.        .BBBBL        BB    .BBBBBg:    QBv                      \n");
    printf("                                                  LB rB5  gBr    :BB         BBi   .QBr    :BB1:  BB7       gBBBBBBKBBBBS7iYZBB.                      \n");
    printf("                                                  BBrgB  .BB12gBBB7           :QBBPrrBB    EB   ir7uBB         BBY  DB. 5BBSi                         \n");
    printf("                                                  Bq B:    .:i:.                  .rLr     dB...    1BB       BB    BBB   BB                          \n");
    printf("                                                  BB7B                         eeee        iB..:7Y2Y 1Bi     .BB .gBB.SBBigBs                         \n");
    printf("                                                   BQB   .BBBBBB.           :BBBqdBBBr      BX  ...  PB7      BBBBQ:    7QQP                          \n");
    printf("                                                    Bg  gBB.   BBR   ru     BX      gBD     :BBi:...iBB                                               \n");
    printf("                                                    BS  BX      ..  2B                        BBIjSSZ7                                                \n");
    printf("                                                   .Bj           .i:BB   1gRRQDs.                BB                                                   \n");
    printf("                                                   :QS       rBBQg2sgBBBBBr::7XBBBBv             BB5MBD1:                                             \n");
    printf("                                                    BB     :BQ5       ..          SBB5          .BI  :JQBBBI.                                         \n");
    printf("                           PBBB2      vRS           BB    KBD                       rBB         BB        vBBBJ                                       \n");
    printf("                           dB .BB   :BBYBBi         rBD  LBI                          BB       :BQ           sBBD                                     \n");
    printf("                            QB  BB  BB  :BP          DQs BB   XBP.    7BBBB7  :BBBQ.  UBB      BB              iBB2                                   \n");
    printf("                             BB. QBBB  jBX            SBPvBZBQBYBBBPBBBX:.dBBBBM :BBBBBBi    .BB                 7BQ.                                 \n");
    printf("                       .dBBBBQBBEBBBBBBBB7             .BBLri    .2bv       .:              PBB                    BQv                                \n");
    printf("                      BBP.      qBMBR   :dBB.            BBBY                             UBBr                      DB5                               \n");
    printf("                     iBB   .:JEBQK BBE     BQ          BB7 :QBBq.                      iBBBr                         ZBu                              \n");
    printf("                      .XBBBBBP2BB  gBBBBBIQBq        7BB      7BBBBgs.            .7DBBBS     .                       BQ:                             \n");
    printf("                              PB   BB  :YK1.        rBZ           rPQBQBBBBQ   2ZBBBPr   rQBQBQBQRRPr                  BQ                             \n");
    printf("                              BB:.BB:               BB               iBj        ZBK    KBBr       .LBBB:               vBj                            \n");
    printf("                               PBBP                BB.                .BBQI1SQBBB:    BB.            :BBdMPs.           BB                            \n");
    printf("                                                   BB           :        rXPPJ:       BB            JB7  :uRBBBJ        QB.                           \n");
    printf("                                                  :B5           Br                    BB:        .dBBi        sBBE      vB7                           \n");
    printf("                                                  uBr          .B7                     BBBIvY5QBBQQ:            .BQ     iB5                           \n");
    printf("                                                  IBi          :B7                     jBBBBBB:sB.                .     :B2                           \n");
    printf("                                                  UBr          iB7                     :BBBBBB  vQg                     vBL                           \n");
    printf("                                                  rBY          rQv                      QBBBBB   .BBL                   gB.                           \n");
    printf("                                                  .BM          rBL                      BBBQBB.    JBBU                 BB                            \n");
    printf("                                                   BB          :Bs                      QBBBBBr      :QBB1:            iBU                            \n");
    printf("����������������������������������������������������������������������������\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("����������������������������������������������������������������������������");
}

void bad_art()
{
    printf("����������������������������������������������������������������������������\n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                     i2gRBQM5Y.                                                                       \n");
    printf("                                                                  7QBBBBBBBQBQBBY                                                                     \n");
    printf("                                                                 BBBBBBBBBBBBBBBBB                                                                    \n");
    printf("                                                                BBBBBQBBBBBBBBBBBBB                                                                   \n");
    printf("                                                               rBBBBBBBBQBQBBBQBBBBB                                                                  \n");
    printf("                                                               qBBBBBBBBBBBBBBBBBQBQ                                                                  \n");
    printf("                                                               2BBBBEBBBBBBBBBBBBBBBu                                                                 \n");
    printf("                                                               .BBB7 LBBBBBQBBBBBBBBB                                                                 \n");
    printf("                                                                BBB   BBBBBBBBQBBBQBB                                                                 \n");
    printf("                                                                 BBBbRBBBQBBBQBBBQBQB                                                                 \n");
    printf("                                                                  BBBBBBBBBBBBQBQBBB:                                                                 \n");
    printf("                                                                 .BQBQBBBBBBBBBBBBBBDr.                                                               \n");
    printf("                                                             .:jBBBBBBQBBBBBBBBBBBQBBBBBBBQBBBBQs                                                     \n");
    printf("                                                      7PBBBBBQBBBQBBBBBBBQBQBBBBBBBBBBBBBBBBBBBBBBd                                                   \n");
    printf("                                                   .QBBBBBBBQBBBBBBBBBBBBBQBBBBBQBQBQBQBBBBBBBBBBBBB.                                                 \n");
    printf("                                                  :BBBBBBBBBBQBBBBBQBBBBBQBQBQBBBBBBBQBBBQBBBBBBBBBBB:                   :g5S                         \n");
    printf("                                                  BBBBBBBBBBBBBBBBQBQBQBQBQBBBBBBBBBQBBBBBQBBBQBBBBBBB                   QBBB                         \n");
    printf("                                                 BBBBBBBBBBBBBBBBBBQBBBQBBBQBBBBBBBBBBBBBBBQBBBBBBBBBBB                  BBBB:                        \n");
    printf("                                                gBBBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB:                 BQBBL                        \n");
    printf("                                               YBBBBBBBBBQBBBBBBBBBBBBBBBQBBBBBBBBBBBBBBBQBBBBBBBBBBBBBB                 BBBBb                        \n");
    printf("                                              .BQBBBQBBBBBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQBBBBBBB7                BQBQB                        \n");
    printf("                                              BBBBBBBBBBBBBBBBBQBBBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBBBBBBBQB               YBBBBB                        \n");
    printf("                                             BBBBBBBBBBBBBBBBBBBBBBBQBBBBBQBBBBBQBBBBBQBBBBBBBBBBBBBBBBBBZ             BQBBBBBQr                      \n");
    printf("                                            rBBBBBBBBQBQBBBBBQBBBBBBBBBBBBBQBBBBBBBQBQBBBBBBBBBBBBBQBBBBBB:           .BBBBBBBBB                      \n");
    printf("                                            BBBBBBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBBBQBQBQBBBQ            BBBBBQBBB                      \n");
    printf("                                           iBBBBBBBBBBBQBSBBBBBBBBBQBBBBBBBQBBBQBBBQBBBBBQBBBBBBBBBQBQBBBBBQ           BBBBBBBBQ                      \n");
    printf("                                           KBBBBQBBBBBBB  BBBBBBBBBBQBBBQBBBQBQBBBBBBBQBBBBBQBBBBBBBBBBBQBQB.          BBBBBBBBB                      \n");
    printf("                                            BBBBBBBBBQr   BBBQBBBBBQBBBBBBBQBBBBBBBQBBBBBBBBBBBBBBBBBBBBBBBQM          BBBBBBBBB                      \n");
    printf("                :YJuJYr:YJuJYr:YJuJYr:YJuJYrZBBBBBBBZr:rrRBBQBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQBQBQBQBBBBBBBB7YUu1u1jvvBBBQBBBQBisjUuUuUuUuUjUU:      \n");
    printf("                       DBBBBBBBBBBBQBBBQBY.                      BBQBBBBBB2ZBBBBBQBBBQBBBBBBBBBQBQBBBBBBBQBB           BBQBBBBBB                      \n");
    printf("                      BBBBBBBBBBBBBBBBBBBBBq.                    BBBBBBBQB   iUDQBBBBBBBBBBBQBQBBBBBBBBBBQ1            BBBQBBBQQ                      \n");
    printf("                     ZBBBBBBBBBBBBBBBBBBBQBBBBBBBBBQBB .           ....                   .:ii77vri:.                    ....                         \n");
    printf("                     :BBQBBBBBBBBBBBQBBBQBBBZXYriirrri iB7                                                                                            \n");
    printf("                      vBBQQRQQQQBQQQQQQBB7            rUBBDU                                                                                          \n");
    printf("                                                     iQBBdqMr  gg                                                                                     \n");
    printf("                                                    .QBBQQMqi                                                                                         \n");
    printf("                                                                                                                                                      \n");
    printf("����������������������������������������������������������������������������\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("����������������������������������������������������������������������������");
}

void good_art()
{
    printf("����������������������������������������������������������������������������\n");
    printf("                                                                                                                                                      \n");
    printf("                                                                   u                                                                                  \n");
    printf("                                                                 :IB                                                                                  \n");
    printf("                                                               .7 di                                                                                  \n");
    printf("                                                              :Y  B                                                                                   \n");
    printf("                                                             :J  rE      :i                                                                           \n");
    printf("                                                            .S   Q:    rBBBBq             b                                                           \n");
    printf("                                                            si   B     QQBBBB             BUB                                                         \n");
    printf("                                                            .1. 7K      BBBBP            :BBB                                                         \n");
    printf("                                                              .LB     .7BBB:           rBBS.                                                          \n");
    printf("                                                              ::B   QBBBBBBBQEqUIu1Yr1BBBv                                                            \n");
    printf("                                                            .L 77  BBBBBBBBBBBQBBBBBBBBB:                                                             \n");
    printf("                                                           :s BB  BBBQBQBBBBBQBBBBBBBBR                                                               \n");
    printf("                                                          :1  QB:dBBBBBBQBBBBBBBXr.                                                                   \n");
    printf("                                                         .S   vBBBBBBBBQBBBBBBBQ                                                                      \n");
    printf("                                                         K    M iBB1UBBBBBBBBBBB                                                                      \n");
    printf("                                                        :v   .B     PBBBBBBBBBBB                                                                      \n");
    printf("                                                        ri   bv     QBBBQBQBBBBB                                                                      \n");
    printf("                                                        .u   B      BQBBBBBBBBB7                                                                      \n");
    printf("                                                          :.7Q      BBBBBBBBBBB                                                                       \n");
    printf("                                                            Bi     .BBBBBBBBBBB                                                                       \n");
    printf("                                                          .7B       BBBBQBQBBBq                                                                       \n");
    printf("                                                         i::Z       BBBQBBBQBBR                                                                       \n");
    printf("                                                        v: g:       BBBBBBBBBBB                                                                       \n");
    printf("                                                       j.  B        BBBB5rBBBBB                                                                       \n");
    printf("                                                      U   rD        BBBB: BBBBQ                                                                       \n");
    printf("                                                     U    B.        BBBB  BBBBB                                                                       \n");
    printf("                                                     S    B        .BBBB  BBBBB                                                                       \n");
    printf("                                                      ::.7gvBB.    iBQBB  BQBBB                                                                       \n");
    printf("                                                         B rBB     .BBBB  QBBBQ                                                                       \n");
    printf("                                                        .B          vBBB  BBBBB                                                                       \n");
    printf("                                                        u5          jBBB   BQBBi                                                                      \n");
    printf("                                                                    PQBQ   7RQBs                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                               .:::dBBBBBBBBBQBr.                                                                     \n");
    printf("                                                              :SPDgMEZbDgQBBBBBBB7:ii:                                                                \n");
    printf("                                                            .1ZPbqbKKKqSX5KSq5SIKPEPi                                                                 \n");
    printf("                                                         rUqgRdPSJLsPBQBBBBBQBQBBBBBBBBu:.                                                            \n");
    printf("                                                         .i::.. YBBBBBBBBBBBBRQMQgMi  .                                                               \n");
    printf("                                                                                                                                                      \n");
    printf("����������������������������������������������������������������������������\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("����������������������������������������������������������������������������");
}

void print_store()
{
    printf("����������������������������������������������������������������������������\n");
    printf("��                                                                          ��                                                                        \n");
    printf("��                                                                          ��                                                                        \n");
    printf("��          � ��, ���°� ������ ��� ���� ������ ������ �ѷ���~          ��                                                                        \n");
    printf("��                                                                          ��                                                                        \n");
    printf("��                                                                          ��                         �����ͷ� ���ư��� : ESC                        \n");
    printf("������      ��������������������������������                                                                        \n");
    printf("��       ��   ��                                                            ��                                                                        \n");
    printf("��        �� ��                                        rBbi77.              ��                          ������ ����� �ȱ� : F                        \n");
    printf("��         ��                                         BBBBBBBBv             ��                                                                        \n");
    printf("��                                                  :BBBQBBBBBQu            ��                                                                        \n");
    printf("��                                                  rBBBBBBBBBBB            ��                                                                        \n");
    printf("��                                                   BBBBBQBBBB             ��                                                                        \n");
    printf("��                                                   rBQBBBBBBu             ��                                                                        \n");
    printf("��                                                    BBBBBBBi              ��                             ���˴� ���� : R                            \n");
    printf("��                                                  .uBBBBBQK               ��                              [ 30,000�� ]                              \n");
    printf("��                                           .qBBBBBBBBBBBQBM               ��                                                                        \n");
    printf("��   BBQBBBBBBBBBBB                         2BBBBBBBBBBBBBBBBQB7            ��                                                                        \n");
    printf("��   BBBBBBBBBBBBBB                      .QBQBBBBBBBQBBBBBBBBBBBQQ.         ��                                                                        \n");
    printf("��   5BESBBBBXPbEDB                      QBBBBBBBBBBBBBBBQBBBBBBBBBQ        ��                                                                        \n");
    printf("��       RBBQ                          .BBBBBBBBBBBBBBBBBBBBBBBBBBBBr       ��                              ��ų ���� : S                             \n");
    printf("��       QBBB                         .BBBBBBBBBBBBBBBBBBBBBBBBBBBBBB       ��                        ( ������ ���� : 200���� )                       \n");
    printf("��   BBBBBBBBBBBBBBBBBQB              7BBBBBQjQBBBQBBBBBBBBBBBBBQBBBB       ��                                                                        \n");
    printf("��   QBBBBBQBBBBBBBBBBBB              BBBBBB. BBBBBBBBBBBQBBBBBBBBBBBr      ��                          ��  �� : [ 10,000�� ]                         \n");
    printf("��   BBBBBBBBBBBQBBBBBBB             PBBQBBU .BBBBQBBBBBBBBBBBQBQBQBBBi     ��                            ĭ   : [ 10,000�� ]                         \n");
    printf("��   BBBBQBBBBBBBBBBBBBB             BBBBBP  LBBBBBBBBBBBQBBBQBBBBBBBBB     ��                          ������ : [ 20,000�� ]                         \n");
    printf("��   BBBQBQBBBQBQBBBBBBB            .BBBBB2  QBBBBBBBBQBBBBBBBBBBBBBBBB     ��                          ��  �� : [ 30,000�� ]                         \n");
    printf("��   BBBBBBBBBBBBBBBBBBB             BBBBQBr BBBBBBBBQBBBBBBBBBBBBBBBBB:    ��                          ����� : [ 40,000�� ]                         \n");
    printf("��   BBBBBBBBBBBBBQBBBQB             rBBBBBBsBBBQBQBBBBBQBBBBBBBBBBBQBB     ��                          ���߷� : [ 40,000�� ]                         \n");
    printf("��   BBQBBBBBBBBBBBBBBBB              vBBBBBBBBBBBBBBQBBBQBBBBBBBQBBBBB     ��                          ��  �� : [ 50,000�� ]                         \n");
    printf("��  .BBBBBBBBBBBBBBBBBBB               JBBBBBBBBQBBBQBBBBBQBBBQBBBQBBBB5    ��                                                                        \n");
    printf("����������������������������������������������������������������������������\n");
    printf("��                                                                          ��                                                                        \n");
    printf("��             ����   �����    ����    ����     �����           ��                                                                        \n");
    printf("��            ��           ��      ��    ��   ��   ��    ��                 ��                                                                        \n");
    printf("��            �����     ��     ��      ��  ����     �����           ������ �� : %d ��\n", money);
    printf("��                  ��     ��      ��    ��   ��  ��     ��                 ��                                                                        \n");
    printf("��             ����      ��       ����    ��   ��    �����           ��                                                                        \n");
    printf("��                                                                          ��                                                                        \n");
    printf("����������������������������������������������������������������������������");
}

void good_end()
{
    system("cls"); grandfather_soso();

    gotoxy1(35, 44); printf("ȸ�翡�� �߸��� �� �� �� ���ÿ��� �Ǳ� ���ؼ� �Ͽ����� �޷��Դ�.");
    gotoxy1(35, 45); printf("���� ���� ���� �Ͼ�ٰ� �����ߴ�.");
    gotoxy1(35, 46); printf("�� �ٰ��� �Ŵ��� ���� ����ϴ� �� �ϴÿ��� �Ҿƹ����� ��ȥ�� ��Ÿ����."); _getch();

    gotoxy1(35, 44); printf("                                                                                                                                                      \n");
    gotoxy1(35, 45); printf("                                                                                                                                                      \n");
    gotoxy1(35, 46); printf("                                                                                                                                                      \n");

    gotoxy1(35, 44); printf("�Ҿƹ����� ��ȥ�� ������ ���ߴ�.");
    gotoxy1(35, 45); printf("���ÿ��� ������ �̾�������� ���� ���, �׵��� �� ���Ѻ��Ҵ� ���ھ�.");
    gotoxy1(35, 46); printf("���� ���ÿ��� �� �Ҿֺ� �ʰ� ���ÿ��� ������ �̾���� �ڰ��� �ִ��� �Ǵ��� �ְڴ�."); _getch();

    gotoxy1(35, 44); printf("                                                                                                                                                      \n");
    gotoxy1(35, 45); printf("                                                                                                                                                      \n");
    gotoxy1(35, 46); printf("                                                                                                                                                      \n");

    gotoxy1(35, 44); printf("����....");
    gotoxy1(35, 45); printf("�ƴ� �̰���...??!!"); _getch();

    system("cls"); grandfather_happy();

    gotoxy1(35, 44); printf("�� �Ҿֺ�� �����̴�.");
    gotoxy1(35, 45); printf("���ÿտ� �ɸ´� �θ� ������ ������, ��� ����⸦ ��� �ְ�, ������ �������� ������ �ִٴ�!");
    gotoxy1(35, 46); printf("�ʴ� ���ÿ��� ���� �ڰ��� �ȴ�. �������� ���� �ʴ� ���ÿ��̴�!"); _getch();

    gotoxy1(35, 44); printf("                                                                                                                                                      \n");
    gotoxy1(35, 45); printf("                                                                                                                                                      \n");
    gotoxy1(35, 46); printf("                                                                                                                                                      \n");

    gotoxy1(35, 44); printf("���� �⻵�ϸ� �Ҿ������ ��ȥ���� ���� �ߴ�.");
    gotoxy1(35, 45); printf("���� �����մϴ�!");
    gotoxy1(35, 46); printf("���� ���� ������ �Ҿƹ����� ��ȥ�� �幵�� �̼Ҹ� ������ �������."); _getch();

    system("cls"); good_art();

    gotoxy1(35, 44); printf("�׷��� ���� �Ҿƹ������Լ� ���ÿ��� �ڸ��� �����ް�");
    gotoxy1(35, 45); printf("������ �θ� ������ ���������� ��� �Ǿ���.");
    gotoxy1(35, 46); printf("- good ending -"); _getch();

    system("cls"); main_art(); _getch();
}

void bad_end() {
    system("cls"); grandfather_soso();

    gotoxy1(35, 44); printf("ȸ�翡�� �߸��� �� �� �� ���ÿ��� �Ǳ� ���ؼ� �Ͽ����� �޷��Դ�.");
    gotoxy1(35, 45); printf("���� ���� ���� �Ͼ�ٰ� �����ߴ�.");
    gotoxy1(35, 46); printf("�� �ٰ��� �Ŵ��� ���� ����ϴ� �� �ϴÿ��� �Ҿƹ����� ��ȥ�� ��Ÿ����."); _getch();

    gotoxy1(35, 44); printf("                                                                                                                                                      \n");
    gotoxy1(35, 45); printf("                                                                                                                                                      \n");
    gotoxy1(35, 46); printf("                                                                                                                                                      \n");

    gotoxy1(35, 44); printf("�Ҿƹ����� ��ȥ�� ������ ���ߴ�.");
    gotoxy1(35, 45); printf("���ÿ��� ������ �̾�������� ���� ���, �׵��� �� ���Ѻ��Ҵ� ���ھ�.");
    gotoxy1(35, 46); printf("���� ���ÿ��� �� �Ҿֺ� �ʰ� ���ÿ��� ������ �̾���� �ڰ��� �ִ��� �Ǵ��� �ְڴ�."); _getch();

    gotoxy1(35, 44); printf("                                                                                                                                                      \n");
    gotoxy1(35, 45); printf("                                                                                                                                                      \n");
    gotoxy1(35, 46); printf("                                                                                                                                                      \n");

    gotoxy1(35, 44); printf("����....");
    gotoxy1(35, 45); printf("�ƴ� �̰���...??!!"); _getch();

    system("cls"); grandfather_angry();

    gotoxy1(35, 44); printf("���� �̳�! ���� ����� ���ڸ� �ξ�����!");
    gotoxy1(35, 45); printf("�̰��̰� ���� �� ������, ����⿡ ���� �ƹ��͵� �𸣰�, ������ ������ ������ ���� �ʴٴ�!");
    gotoxy1(35, 46); printf("�ʴ� ���ÿ��� ���� �ڰ��� �ȵȴ�. �ƴ� ���� ���� ���ڵ� �ƴϴ�. �ٽô� ���õ� ���� ���Ŷ�!"); _getch();

    gotoxy1(35, 45); printf("                                                                                                                                                      \n");
    gotoxy1(35, 46); printf("                                                                                                                                                      \n");
    gotoxy1(35, 47); printf("                                                                                                                                                      \n");

    gotoxy1(35, 44); printf("���� ��Ȳ�ϸ� �Ҿ������ ��ȥ���� ���� �ߴ�.");
    gotoxy1(35, 45); printf("�ƴ�, �Ҿ����! ��񸸿�!");
    gotoxy1(35, 46); printf("���� ���� �����⵵ ���� �Ҿƹ����� ��ȥ�� �°� �弳�� �������� �������."); _getch();

    system("cls"); bad_art();

    gotoxy1(35, 44); printf("�׷��� ���� �Ҿƹ������� ������ ���ϰ� ���õ� ���ϰ� �Ǿ���.");
    gotoxy1(35, 45); printf("�ᱹ ���� ���� ��� �汸�� ���� ��Ȱ�� �̾�� �Ǿ���.");
    gotoxy1(35, 46); printf("- bad ending -"); _getch();

    system("cls"); main_art(); _getch();
}

void initplayer(player* player)
{
    player->active = 0;
    player->x = 75;
    player->y = 0;
}

fish* initfish(fish* fishhead)
{
    fish* p = (fish*)malloc(sizeof(fish));
    srand(time(NULL));
    rand();
    p->code = 0;
    p->num = fishnum++;
    strcpy_s(p->name, 15, "\0");
    p->x = 3000;
    p->y = 3000;
    p->speed = 0;
    p->weight = 0;
    p->price = 0;
    p->link = NULL;
    fishhead = p;
    return fishhead;
}

void makefish(fish* fishhead)
{
    fish* p = (fish*)malloc(sizeof(fish));

    int startx = rand() % 2;
    if (startx == 1) startx = 139;
    else startx = 10;
    p->x = startx; //x�� ����, ������ ��������

    if (p->x == 10) p->speed = rand()%3 + 1; //���� ������ ���� �ӵ� ���ϱ�
    else p->speed = -rand() % 3 - 1;

    p->code = rand() % 7 + 1; //����� �ڵ� �����

    p->num = fishnum++;

    amountoffish++; //���� �ٴٿ� �ִ� ����� �� ����

    switch (p->code) //�ڵ忡 ���� ���ݰ� ����, ����� ����
    {
        case 1:
            p->y = rand() % 35;
            p->weight= rand()%5 + 5;
            p->price = p->weight * 30;
            strcpy_s(p->name, 15,"��ġ");
            p->size = 2;
            if (p->speed > 0)
            {
                strcpy_s(p->shape, 10, ">-");
            }
            else
            {
                strcpy_s(p->shape, 10, "-<");
            }
            break;
        case 2:
            p->y = rand() % 15;
            p->weight = rand() % 101 + 400;
            p->price = p->weight * 40;
            strcpy_s(p->name, 15, "�췰");
            p->size = 3;
            if (p->speed > 0)
            {
                strcpy_s(p->shape, 10, ">@>");
            }
            else
            {
                strcpy_s(p->shape, 10, "<@<");
            }
            break;
        case 3:
            p->y = rand() % 25;
            p->weight = rand() % 101 + 200;
            p->price = p->weight * 45;
            strcpy_s(p->name, 15, "���ڹ�");
            p->size = 3;
            if (p->speed > 0)
            {
                strcpy_s(p->shape, 10, "-@>");
            }
            else
            {
                strcpy_s(p->shape, 10, "<@-");
            }
            break;
        case 4:
            p->y = rand() % 25;
            p->weight = rand() % 101 + 300;
            p->price = p->weight * 50;
            strcpy_s(p->name, 15, "����");
            p->size = 3;
            if (p->speed > 0)
            {
                strcpy_s(p->shape, 10, ">=>");
            }
            else
            {
                strcpy_s(p->shape, 10, "<=<");
            }
            break;
        case 5:
            p->y = rand() % 15 + 10;
            p->weight = rand() % 201 + 600;
            p->price = p->weight * 55;
            strcpy_s(p->name, 15, "����");
            p->size = 4;
            if (p->speed > 0)
            {
                strcpy_s(p->shape, 10, "=@@>");
            }
            else
            {
                strcpy_s(p->shape, 10, "<@@=");
            }
            break;
        case 6:
            p->y = rand() % 15 + 20;
            p->weight = rand() % 101 + 700;
            p->price = p->weight * 60;
            strcpy_s(p->name, 15, "���");
            p->size = 4;
            if (p->speed > 0)
            {
                strcpy_s(p->shape, 10, "-==>");
            }
            else
            {
                strcpy_s(p->shape, 10, "<==-");
            }
            break;
        case 7:
            p->y = rand() % 10 + 25;
            p->weight = rand() % 101 + 1000;
            p->price = p->weight * 100;
            strcpy_s(p->name, 15, "��ġ");
            p->size = 5;
            if (p->speed > 0)
            {
                strcpy_s(p->shape, 10, "><+@>");
            }
            else
            {
                strcpy_s(p->shape, 10, "<@+><");
            }
            break;
    }

    p->link = fishhead->link;
    fishhead->link = p;
}

fish* fishdelete(fish* fishhead, fish* pre) //��� ����� ���� ��� ��ȯ
{
    amountoffish--;
    fish* r;
    r = pre->link;
    pre->link = r->link;
    free(r);
    return pre;
}

void updatesea(fish* fishhead, player *player) //�ٴ� �迭 ������Ʈ
{
    fish* pre = fishhead;
    for (int i = 0; i < 35; i++) //�ٴ� �迭 �ʱ�ȭ
    {
        for (int j = 0; j < 150; j++)
        {
            seaposarray[i][j] = 0;
            seaarray[i][j] = ' ';
        }
    }
    for (int i = 0; i < 35; i++)
    {
        seaposarray[i][4] = 8;
        seaarray[i][4] = '|';
    }

    for (int i = 0; i < 35; i++)
    {
        seaposarray[i][144] = 8;
        seaarray[i][144] = '|';
    }

    for (fish* p = fishhead->link; p != NULL; p = p->link) //�迭�� ����� �ֱ�
    {
        if (p->speed > 0) //�迭�� ����� ��ġ ǥ��
        {
            for (int i = -p->size + 1; i <= 0; i++)
            {
                seaposarray[p->y][p->x + i] = p->code;
                seaarray[p->y][p->x + i] = p->shape[i + p->size - 1];
            }
        }
        else
        {
            for (int i = 0; i < p->size; i++)
            {
                seaposarray[p->y][p->x + i] = p->code;
                seaarray[p->y][p->x + i] = p->shape[i];
            }
        }

        p->x += p->speed; //����� �̵�
        p->distance = (int)sqrt(pow((p->x - player->x), 2) / 2 + pow((p->y - player->y), 2)); //�̳��� ����� �Ÿ� ���
        if ((p->x < 10 && p->speed < 0) || (p->x > 139 && p->speed > 0))
        {
            p = fishdelete(fishhead, pre);
        }

        pre = p;
    }

    if (player->active == 1) player->y += 2; //�迭�� ������ �ֱ�
    if (player->y >= pendulum)
    {
        player->active = 0;
        player->y = 0;
    }
    for (int i = 0; i < player->y; i++)
    {
        seaarray[i][player->x] = '|';
    }
    seaarray[player->y][player->x] = '*';

} //�ٴ� �迭 ������Ʈ

void seamove(fish *fishhead, player *player) // �ٴ� ������ �Ѱ�
{

    if (clock() - maketime > 1000) // 1�ʸ��� ����� ����
    {
        makefish(fishhead);
        maketime = clock();
    }

    updatesea(fishhead, player); //�ٴ� �迭 ������Ʈ.

    COORD pos = { 0, 15};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

    for (int i = 0; i < 35; i++) //�ٴ� �迭 �׸���
    {
        for (int j = 0; j < 150; j++)
        {
            if (seaposarray[i][j] == 0)
            {

            }
            else if (seaposarray[i][j] == 1)
            {
                printf("\033[1;33m"); //���
            }
            else if (seaposarray[i][j] == 2)
            {
                printf("\033[0;33m"); //��Ȳ
            }
            else if (seaposarray[i][j] == 3)
            {
                printf("\033[0;32m"); //�ʷ�
            }
            else if (seaposarray[i][j] == 4)
            {
                printf("\033[1;32m"); //���� �ʷ�
            }
            else if (seaposarray[i][j] == 5)
            {
                printf("\033[1;95m"); //����
            }
            else if (seaposarray[i][j] == 6)
            {
                printf("\033[1;36m"); //���� ����
            }
            else if (seaposarray[i][j] == 7)
            {
                printf("\033[0;31m"); //����
            }
            else if (seaposarray[i][j] == 8)
            {
                printf("\033[0;34m"); //�Ķ�
            }
            printf("%c", seaarray[i][j]);
            printf("\033[0m");
        }
    }
} // �ٴ� ������ �Ѱ�

int compare(Inventory* a, Inventory* b) //��
{
    int num1 = a->code; //���� price
    int num2 = b->code; //price

    if (num1 < num2)
    {
        return 1;
    }
    if (num1 > num2)
    {
        return -1;
    }
    return 0;
}

void catchfish(player* player, fish* fishhead) //����� ��ȹ
{
    fish* pre = fishhead;
    int* dist = (int*)malloc(sizeof(int) * amountoffish); //����� �Ÿ� ��������
    int* num = (int*)malloc(sizeof(int) * amountoffish); //�� ����� �ĺ� num ����
    int* weightarray = (int*)malloc(sizeof(int) * amountoffish); //�� ����� ���� ����
    int d_tmp;
    int n_tmp;
    int w_tmp;
    for (int i = 0; i < amountoffish; i++)
    {
        dist[i] = 200;
    }

    for (fish* p = fishhead->link; p != NULL; p = p->link) //�̳��κ��� ����� �Ÿ��� ������ȣ ����
    {
        int d_min = p->distance;
        int n_min = p->num;
        int w_min = p->weight;

        for (int i = 0; i < amountoffish; i++)
        {
            if (d_min < dist[i]) //�迭 ����
            {
                d_tmp = dist[i];
                dist[i] = d_min;
                d_min = d_tmp;

                n_tmp = num[i];
                num[i] = n_min;
                n_min = n_tmp;

                w_tmp = weightarray[i];
                weightarray[i] = w_min;
                w_min = w_tmp;

            }
        }
        pre = p;
    }

    int totalweight = 0;
    int totalcount = 0;
    //���� �� �ִ� ����� ���
    for (int i = 0; i < baitcount; i++) {
        if (dist[i] < range && weightarray[i] + totalweight < strength) { //����Ⱑ ���� ���̰� ���� ���� �ٷ��� ���� �ʴ´ٸ�
            totalcount++;
            totalweight += weightarray[i];
        }
    }

    int hitclear = 0;

    //����Ⱑ ���� ���� �ִٸ� ��Ÿ����.
    if (dist[0] < range) {
        int hitstart = clock();
        int hit = 0;
        int key = 0;
        int prekey = 0;

        COORD pos = { player->x - 3, gaugey };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        int hitratio = 0;

        while (clock() - hitstart < 1000) //1�� ���� ��Ÿ �۾��� ����
        {

            if(hitratio > ((totalweight / 100 + 3) - (totalweight / 100 + 3) / 5 * repeat) / 7)
            {
                printf("=");
                hitratio = 0;
            }
            if (_kbhit())
            {

                key = _getch();
                if (key == 224)
                {
                    key = _getch();
                    if ((key == 75 && prekey == 0) || (key == 75 && prekey == 1)) //����
                    {
                        if (prekey == 0)
                        {
                            hit++;
                            hitratio++;
                            prekey = -1;
                        }
                        else if (prekey == 1)
                        {
                            hit++;
                            hitratio++;
                            prekey = -prekey;
                        }
                    }
                    else if ((key == 77 && prekey == 0) || (key == 77 && prekey == -1)) //������
                    {
                        if (prekey == 0)
                        {
                            hit++;
                            hitratio++;
                            prekey = 1;
                        }
                        else if (prekey == -1)
                        {
                            hit++;
                            hitratio++;
                            prekey = -prekey;
                        }
                    }
                }
            }
            if (((totalweight / 100 + 3) - (totalweight / 100 + 3) / 5 * repeat) < hit)
            {
                hitclear = 1;
                break;
            }
        }


    }

    COORD pos = { 0, gaugey };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    for (int i = 0; i < 150; i++) printf(" ");

    for (int k = 0; k < totalcount; k++) //���� �� �ִ� ����� ����ŭ ���
    {
        pre = fishhead;
        for (fish* p = fishhead->link; p != NULL; p = p->link)
        {
            if (p->num == num[k]) //�����ؾ� �� ����⸦ ã�Ҵٸ�
            {
                if (hitclear == 1)
                {
                    inventory[inventory_full].code = p->code;
                    inventory[inventory_full].weight = p->weight;
                    inventory_weight += inventory[inventory_full].weight;
                    inventory[inventory_full++].price = p->price + (p->price / 100) * sense; // sense% �� ���� ���ʽ�
                    fishcode[p->code-1]++;
                    p = fishdelete(fishhead, pre);
                }


                if (inventory_full > inventory_capacity || inventory_weight > inventory_w_capacity) //��� �賶�� �ְ� ���� ����ġ�� �Ѿ�ݾ�? �賶 ������ �ذ�����. 
                {
                    //�賶���� �Լ� ����! 
                    Inventory bag[36];
                    int tmp_inventory = 0;
                    int tmp_weight = 0;

                    qsort(inventory, inventory_full, sizeof(Inventory), compare);//����Ʈ �Լ�

                    for (int i = 0; i < inventory_full; i++)
                    {
                        if (tmp_inventory > inventory_capacity || tmp_weight > inventory_w_capacity)// ����ġ �Ѿ�� Ż��
                        {
                            break;
                        }

                        if (tmp_weight + inventory[i].weight <= inventory_w_capacity)// �ӽ� �迭�� �׸����ϰ� �ֱ� (��Ʈ����)
                        {
                            bag[tmp_inventory].code = inventory[i].code;
                            bag[tmp_inventory].price = inventory[i].price;
                            bag[tmp_inventory].weight = inventory[i].weight;

                            tmp_weight += inventory[i].weight;
                            tmp_inventory++;
                        }
                    }

                    for (int i = 0; i < tmp_inventory; i++)// �ӽ� ���� �������� ��ü�� �ű��
                    {
                        inventory[i].code = bag[i].code;
                        inventory[i].price = bag[i].price;
                        inventory[i].weight = bag[i].weight;
                    }

                    for (int i = tmp_inventory; i < inventory_capacity; i++) // �� �ű�� �ʱ�ȭ 
                    {
                        inventory[i].code = 0;
                        inventory[i].price = 0;
                        inventory[i].weight = 0;
                    }

                    inventory_full = tmp_inventory;
                    inventory_weight = tmp_weight;
                }
            }
            pre = p;
        }
    }
   

    free(dist);
    free(num);
}

void putkey(player* player, fish* fishhead)
{
    Sleep(10);
    int key = 0;
    if (_kbhit())
    {
        key = _getch();
    }
    if (key == 224 && player->active != 1) //����Ű�� �Է� ���� �� �������� �������� ���� �ƴ� ��
    {
        key = _getch();
        switch (key)
        {
        case 75: // ����
        {
            if (player->x > 10) player->x -= 1;
            break;
        }
        case 77: // ������
        {
            if (player->x < 139) player->x += 1;
            break;
        }
        case 72: // ��
            break;;
        case 80: // �Ʒ�
            break;;
        }
    }
    else if (key == 32) //�����̽� �ٸ� �Է� ���� ��
    {
        if (player->active == 0)
        {
            if (d_stack < durability)
            {   
                player->active = 1; //�̳��� ����
                d_stack++;
            }
        }
        else //�̳��� �ø�
        {
            player->active = 0;
            catchfish(player, fishhead);
            player->y = 0;
        }
    }
    else if (key == 83 || key == 115) //����(S)�� �Է��� ��� ����â���� �̵�
    {
        fish* pre = fishhead;
        for (fish* p = fishhead->link; p != NULL; p = p->link) //����� ���Ḯ��Ʈ ����
        {
            p = fishdelete(fishhead, pre);
            pre = p;
        }
        free(fishhead);
        system("cls");
        scene = 2;
    }
    else if (key == 73 || key == 105) //����â
    {
        system("cls");
        scene = 4;
    }
    else
    {

    }
}

void shipmove(player* player) // �� ������ �Ѱ�
{
    for (int i = 0; i < 5; i++) //�迭 �ʱ�ȭ
    {
        for (int j = 0; j < 150; j++)
        {
            shiparray[i][j] = ' ';
        }
    }

    for (int i = 2; i < 4; i++) //�迭�� �� ��� �ֱ�
    {
        shiparray[i][player->x] = '@';
        shiparray[i][player->x - 1] = '@';
        shiparray[i][player->x + 1] = '@';
        shiparray[i][player->x + 2] = '@';
        shiparray[i][player->x - 2] = '@';
    }
    shiparray[2][player->x + 3] = '@';
    shiparray[2][player->x - 3] = '@';
    shiparray[1][player->x + 1] = '|';
    shiparray[0][player->x + 1] = '|';
    shiparray[0][player->x + 2] = '>';

    for (int i = 4; i < 145; i++)
    {
        if (i % 2 == 1)
        {
            shiparray[4][i] = '^';
        }
        if (i % 2 == 0)
        {
            shiparray[4][i] = '-';
        }
    }

    COORD pos = { 0, 10 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

    for (int i = 0; i < 5; i++) //�� ���
    {
        for (int j = 0; j < 150; j++)
        {
            if (i == 4)
            {
                printf("\033[0;34m"); //�Ķ�
            }
            printf("%c", shiparray[i][j]);
            printf("\033[0m");
        }
        printf("\n");
    }
}

void showinventory()
{
    printf("             ���� : S   ����â : I\n");
  //  for (int i = 0; i < 25; i++)
  //  {
  //      printf("%d ", inventory[i].code);
  //  }
    printf("             ���� �� : %d      ���˴� ������ : %2d      ���� : %2d\n", money, durability - d_stack, day);
 //   for (int i = 0; i < 25; i++)
 //   {
 //       printf("%d ", inventory[i].weight);
  //  }
 //   printf("\n");
  //  for (int i = 0; i < 25; i++)
  //  {
  //      printf("%d ", inventory[i].price);
  //  }
}


int s_putkey()
{
    Sleep(10);
    int key = 0;
    if (_kbhit())
    {
        key = _getch();
    }
    if (key == 27) //ESCŰ�� ���� ��� ���� ���� â���� �Ѿ.
    {
        system("cls");
        scene = 1;
        return 0;
    }
    else if (key == 70 || key == 102) // FŰ�� ���� ��� �κ��丮�� �������� �ȾƼ� ������ ȯ��.
    {
        system("cls");
        for (int i = 0; i < inventory_capacity; i++)
        {
            money += inventory[i].price;
            inventory[i].price = 0;
            inventory[i].code = 0;
            inventory[i].weight = 0;
        }
        
        inventory_full = 0;
        return 1;
    }
    else if (key == 32 || key == 114) //RŰ�� ���� ��� ���˴� ����
    {   
        system("cls");
        if (money >= 30000 && d_stack > 0) {
            money -= 30000;
            d_stack = 0;
        }

        if (d_stack == durability && money < 30000) //���� �������� ������ ���� ���ٸ� �й�
        {
            scene = 6;
            return 0;
        }
    }
    else if (key == 83 || key == 115) // SŰ�� ���� ��� ��ų â���� �Ѿ��.
    {
        system("cls");
        scene = 3;
        return 0;
    }
    else
    {

    }
    if (money > 3000000 && moneycondition == 0)
    {
        moneycondition = 1;
        wincondition++;
    }
    if (wincondition == 3) {
        scene = 5;
        return 0;
    }
}

void initskillpos() //��ų ���� ��ġ �ʱ�ȭ
{
    skillpos[0].x = 0;
    skillpos[0].y = 4;
    skillpos[0].size = 5;

    skillpos[1].x = 13;
    skillpos[1].y = 2;
    skillpos[1].size = 6;

    skillpos[2].x = 13;
    skillpos[2].y = 6;
    skillpos[2].size = 6;

    skillpos[3].x = 27;
    skillpos[3].y = 1;
    skillpos[3].size = 4;

    skillpos[4].x = 28;
    skillpos[4].y = 3;
    skillpos[4].size = 2;

    skillpos[5].x = 27;
    skillpos[5].y = 5;
    skillpos[5].size = 4;

    skillpos[6].x = 27;
    skillpos[6].y = 8;
    skillpos[6].size = 4;

    skillpos[7].x = 39;
    skillpos[7].y = 1;
    skillpos[7].size = 6;

    skillpos[8].x = 39;
    skillpos[8].y = 4;
    skillpos[8].size = 6;

    skillpos[9].x = 39;
    skillpos[9].y = 7;
    skillpos[9].size = 6;

    skillpos[10].x = 41;
    skillpos[10].y = 10;
    skillpos[10].size = 2;

    skillpos[11].x = 53;
    skillpos[11].y = 0;
    skillpos[11].size = 4;

    skillpos[12].x = 53;
    skillpos[12].y = 2;
    skillpos[12].size = 2;

    skillpos[13].x = 50;
    skillpos[13].y = 4;
    skillpos[13].size = 6;

    skillpos[14].x = 51;
    skillpos[14].y = 7;
    skillpos[14].size = 4;

    skillpos[15].x = 51;
    skillpos[15].y = 9;
    skillpos[15].size = 6;

    skillpos[16].x = 51;
    skillpos[16].y = 11;
    skillpos[16].size = 4;

    skillpos[17].x = 65;
    skillpos[17].y = 2;
    skillpos[17].size = 4;

    skillpos[18].x = 66;
    skillpos[18].y = 5;
    skillpos[18].size = 2;

    skillpos[19].x = 65;
    skillpos[19].y = 9;
    skillpos[19].size = 4;

    skillpos[20].x = 77;
    skillpos[20].y = 5;
    skillpos[20].size = 11;
}

int choose(int n, int found[]) //���� ����� ���� ã��
{
    int i, min, minpos;
    min = INF;
    minpos = -1;
    for (i = 0; i < n; i++)
        if (D[i] < min && !found[i]) {
            min = D[i];
            minpos = i;
        }
    return minpos;
}

void print_status2()
{
    char skillUI[12][100] =
    {
        "                                                 --- �ٷ�          ",
        "                       --- �̳� -----  ����� ---|             ",
        "         --- ������ ---|                         --- ĭ  ------- ���� ---",
        "         |             ---  ��  ---                                     |",
        "start ---|                        |--- ���߷� --- ������ ---            |",
        "         |             --- �ٷ� ---                        |----- �� ---|--- ������ ����",
        "         --- ����� ---|                                   |            |",
        "                       |           --- ���߷� ---  �̳� ----            |",
        "                       --- ���� ---|                                    |",
        "                                   |           --- �����  ----- �̳� ---",
        "                                   ---   ĭ ---|                         ",
        "                                               --- �ٷ�" };
    for (int i = 0; i < 12; i++) //�켱 ��ųƮ���� �׸���
    {
        COORD pos = { skillx, skilly + i }; //Ŀ�� ��ǥ �̵� ��
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        for (int j = 0; j < 100; j++)
        {
            printf("%c", skillUI[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < MAX_SKILL; i++) //��ų�� Ȱ��ȭ �Ǿ� �ִ��� Ȯ��
    {
        if (active_t[i] == 1) //Ȱ��ȭ �Ǿ��ٸ�
        {
            COORD pos = { skillx + skillpos[i].x , skilly + skillpos[i].y}; //Ŀ�� ��ǥ �̵� ��
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
            printf("\033[0;33m"); //���������
            for (int j = skillpos[i].x; j < skillpos[i].size + skillpos[i].x; j++)
            {
                printf("%c", skillUI[skillpos[i].y][j]);
            }
            printf("\033[0m\n"); //�������
        }
    }

    skill_itd();

}

void shortest_path(skilltree* t, int start)
{
    int found[MAX_SKILL]; //ã�� ����
    int min, w;

    for (int i = 0; i < t->n; i++)  //�Ÿ��� ������ D �迭 �ʱ�ȭ
    {
        if (active_t[i] == 1) //���� ��ų �Ÿ� 0����
        {
            t->weight[0][i] = 0;
        }
        D[i] = t->weight[start][i];
        pre[i] = 0;
        found[i] = FALSE;
    }

    found[start] = TRUE; //���� ǥ��
    D[start] = 0;
    for (int i = 0; i < t->n - 1; i++) {
        min = choose(t->n, found);
        found[min] = TRUE;
        for (w = 0; w < t->n; w++) //���� ����ġ ��ȭ
        {
            if (!found[w])
            {
                if (D[min] + t->weight[min][w] < D[w]) //���� �Ÿ����� ���� ã�� �Ÿ��� �� ���� ��
                {

                    D[w] = D[min] + t->weight[min][w]; //������ȭ
                    pre[w] = min; //���� ���� ���� ���
                }
            }
        }

    }
    print_status2(found);
 //   print_status(found);
}

int skillinput() //��ų�� �Ӽ��� ���� ���ڿ��� �Է� �� ������ ����. 
{
    COORD pos = { 60, 43 }; //Ŀ�� ��ǥ �̵� ��
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    char skill_answer[20]; //��ų�� �Է¹��� ���ڿ�
    printf("�Է� : ");
    fgets(skill_answer, sizeof(skill_answer), stdin);
    system("cls");
    char s1[] = "������\n";
    char s2[] = "��\n";
    char s3[] = "�̳�\n";
    char s4[] = "�ٷ�\n";
    char s5[] = "�����\n";
    char s6[] = "���߷�\n";
    char s7[] = "ĭ\n";
    char s8[] = "����\n";
    char s9[] = "������ ����\n";
    char s10[] = "������\n";
    if (skill_answer[0] == '?')
    {

    }

    if (!strcmp(skill_answer, s1))
    {
        return 1;
    }
    else if (!strcmp(skill_answer, s2))
    {
        return 2;
    }
    else if (!strcmp(skill_answer, s3))
    {
        return 3;
    }
    else if (!strcmp(skill_answer, s4))
    {
        return 4;
    }
    else if (!strcmp(skill_answer, s5))
    {
        return 5;
    }
    else if (!strcmp(skill_answer, s6))
    {
        return 6;
    }
    else if (!strcmp(skill_answer, s7))
    {
        return 7;
    }
    else if (!strcmp(skill_answer, s8))
    {
        return 8;
    }
    else if (!strcmp(skill_answer, s9))
    {
        return 9;
    }
    else if (!strcmp(skill_answer, s10))
    {
        return 0;
    }
    else
    {
        printf("%d\n", 1);
        printf("�ٽ�\n");
        return 0;
    }
}

int setskill() //���� ��ų�� ���� ����.
{
    if (active_code[0] == 1) //������ +1
    {
        durability = 20;
    }
    else if (active_code[0] == 2) //������ +2
    {
        durability = 30;
    }

    if (active_code[1] == 1) //�� +1
    {
        pendulum = 25;
    }
    else if (active_code[1] == 2)
    {
        pendulum = 35;
    }

    if (active_code[2] >= 1) //�̳� +1 �̳����� Ȯ��
    {
        range = 6;
    }
    if (active_code[2] >= 2) //�̳� +2 �̳� ���� 2��
    {
        baitcount = 2;
    }
    if (active_code[2] == 3) //�̳� +3 ���� ���� ����
    {
        range = 7;
        baitcount = 3;
    }

    if (active_code[3] == 1) //�ٷ� +1
    {
        strength = 1200;
    }
    else if (active_code[3] == 2) //�ٷ� +2
    {
        strength = 2000;
    }
    else if (active_code[3] == 3) //�ٷ� +3
    {
        strength = 3500;
    }

    if (active_code[4] == 1) //����� +1
    {
        sense = 10;
    }
    else if (active_code[4] == 2) //����� +2
    {
        sense = 20;
    }
    else if (active_code[4] == 3) //����� +3
    {
        sense = 30;
    }

    if (active_code[5] == 1) // ���߷� +1 ��Ÿ Ƚ�� ����
    {
        repeat = 3;
    }
    else if (active_code[5] == 2) //���߷� +2
    {
        repeat = 4;
    }
    
    if (active_code[6] == 1) // ĭ +1
    {
        inventory_capacity = 20;
    }
    else if(active_code[6] == 2) //ĭ +2
    {
        inventory_capacity = 30;
    }

    if (active_code[7] == 1) // ���� +1
    {
        inventory_w_capacity = 9000;
    }
    if (active_code[7] == 2) // ���� +2
    {
        inventory_w_capacity = 20000;
    }
}

void findskill(int code) //�ش� ��α����� ��ų ���
{
    int min;
    int path[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //ã�� ������ ������ �� ���
    if (code == 0) //�������� ������
    {
        system("cls");
        setskill();
        scene = 2;
    }
    else if (code == 1) //�Է��� �������� ���@
    {
        if (active_code[0] < 2) //��ų�� ������ �������� Ȯ��. ���� �� �����ٸ� �Ÿ��� ���� ª�� ��ų ã��. �̹� ���� ��ų ���� ����@
        {
            min = 20; //�Ÿ��� ���� ���� ���� �ʱ�ȭ. �ڵ忡 ���� �ٸ���. @
            for (int i = 0; i < MAX_SKILL; i++) //skillcode�� ��ȸ�ϸ鼭 ��ų�ڵ尡 �´� ���� ã�� 
            {
                if ((skillcode[i] == 1 && D[i] < D[min]) && active_t[i] == 0) //��ų�ڵ尡 �����鼭 �Ÿ��� �� ª���鼭 Ȱ��ȭ �Ǿ����� �ʴٸ� @
                {
                    min = i;
                }
            }
            if (money - D[min] * 10000 > 0) //���� �ش� ������ �Ÿ������� ���� ����ϴٸ�
            {
                //pre �迭���� min ���������� �� Ȱ��ȭ
                int p = 0; // Ȱ��ȭ ���Ѿ��� ���� ����
                for (int i = min; i != 0; i = pre[i]) //min �������� ���� �� Ȯ��.
                {
                    if (active_t[i] == 0) //�ش� ������ Ȱ��ȭ �Ǿ��ִ��� Ȯ��
                    {
                        path[p++] = i;
                    }
                    else
                    {
                        break;
                    }
                }

                for (int i = 0; i < p; i++)
                {
                    active_t[path[i]] = 1; // ������ Ȱ��ȭ.

                    active_code[skillcode[path[i]] - 1]++; //�ڵ� �� Ȱ��ȭ �� ����.
                }
                money -= D[min] * 10000;
            }

        }
        else //��ų�� ������ �����ٸ� ��ų�� �ٽ� �����ϼ���
        {

        }
    }
    else if (code == 2) //�Է��� ���� ��� @ 
    {
        if (active_code[1] < 2) //��ų�� ������ �������� Ȯ��. ���� �� �����ٸ� �Ÿ��� ���� ª�� ��ų ã��. �̹� ���� ��ų ���� ����@
        {
            min = 20; //�Ÿ��� ���� ���� ���� �ʱ�ȭ. �ڵ忡 ���� �ٸ���. @
            for (int i = 0; i < MAX_SKILL; i++) //skillcode�� ��ȸ�ϸ鼭 ��ų�ڵ尡 �´� ���� ã�� 
            {
                if ((skillcode[i] == 2 && D[i] < D[min]) && active_t[i] == 0) //��ų�ڵ尡 �����鼭 �Ÿ��� �� ª���鼭 Ȱ��ȭ �Ǿ����� �ʴٸ� @
                {
                    min = i;
                }
            }

            if (money - D[min] * 10000 > 0) //���� �ش� ������ �Ÿ������� ���� ����ϴٸ�
            {
                //pre �迭���� min ���������� �� Ȱ��ȭ
                int p = 0; // Ȱ��ȭ ���Ѿ��� ���� ����
                for (int i = min; i != 0; i = pre[i]) //min �������� ���� �� Ȯ��.
                {
                    if (active_t[i] == 0) //�ش� ������ Ȱ��ȭ �Ǿ��ִ��� Ȯ��
                    {
                        path[p++] = i;
                    }
                    else
                    {
                        break;
                    }
                }

                for (int i = 0; i < p; i++)
                {
                    active_t[path[i]] = 1; // ������ Ȱ��ȭ.

                    active_code[skillcode[path[i]] - 1]++; //�ڵ� �� Ȱ��ȭ �� ����.
                }
                money -= D[min] * 10000;
            }

        }
        else //��ų�� ������ �����ٸ� ��ų�� �ٽ� �����ϼ���
        {

        }
    }
    else if (code == 3) //�Է��� �̳��� ���
    {
        if (active_code[2] < 3) //��ų�� ������ �������� Ȯ��. ���� �� �����ٸ� �Ÿ��� ���� ª�� ��ų ã��. �̹� ���� ��ų ���� ����@
        {
            min = 20; //�Ÿ��� ���� ���� ���� �ʱ�ȭ. �ڵ忡 ���� �ٸ���. @
            for (int i = 0; i < MAX_SKILL; i++) //skillcode�� ��ȸ�ϸ鼭 ��ų�ڵ尡 �´� ���� ã�� 
            {
                if ((skillcode[i] == 3 && D[i] < D[min]) && active_t[i] == 0) //��ų�ڵ尡 �����鼭 �Ÿ��� �� ª���鼭 Ȱ��ȭ �Ǿ����� �ʴٸ� @
                {
                    min = i;
                }
            }

            if (money - D[min] * 10000 > 0) //���� �ش� ������ �Ÿ������� ���� ����ϴٸ�
            {
                //pre �迭���� min ���������� �� Ȱ��ȭ
                int p = 0; // Ȱ��ȭ ���Ѿ��� ���� ����
                for (int i = min; i != 0; i = pre[i]) //min �������� ���� �� Ȯ��.
                {
                    if (active_t[i] == 0) //�ش� ������ Ȱ��ȭ �Ǿ��ִ��� Ȯ��
                    {
                        path[p++] = i;
                    }
                    else
                    {
                        break;
                    }
                }

                for (int i = 0; i < p; i++)
                {
                    active_t[path[i]] = 1; // ������ Ȱ��ȭ.

                    active_code[skillcode[path[i]] - 1]++; //�ڵ� �� Ȱ��ȭ �� ����.
                }
                money -= D[min] * 10000;
            }

        }
        else //��ų�� ������ �����ٸ� ��ų�� �ٽ� �����ϼ���
        {

        }
    }
    else if (code == 4) //�Է��� �ٷ��� ���
    {
        if (active_code[3] < 3) //��ų�� ������ �������� Ȯ��. ���� �� �����ٸ� �Ÿ��� ���� ª�� ��ų ã��. �̹� ���� ��ų ���� ���� @
        {
            min = 20; //�Ÿ��� ���� ���� ���� �ʱ�ȭ. �ڵ忡 ���� �ٸ���. @
            for (int i = 0; i < MAX_SKILL; i++) //skillcode�� ��ȸ�ϸ鼭 ��ų�ڵ尡 �´� ���� ã�� 
            {
                if ((skillcode[i] == 4 && D[i] < D[min]) && active_t[i] == 0) //��ų�ڵ尡 �����鼭 �Ÿ��� �� ª���鼭 Ȱ��ȭ �Ǿ����� �ʴٸ� @
                {
                    min = i;
                }
            }

            if (money - D[min] * 10000 > 0) //���� �ش� ������ �Ÿ������� ���� ����ϴٸ�
            {
                //pre �迭���� min ���������� �� Ȱ��ȭ
                int p = 0; // Ȱ��ȭ ���Ѿ��� ���� ����
                for (int i = min; i != 0; i = pre[i]) //min �������� ���� �� Ȯ��.
                {
                    if (active_t[i] == 0) //�ش� ������ Ȱ��ȭ �Ǿ��ִ��� Ȯ��
                    {
                        path[p++] = i;
                    }
                    else
                    {
                        break;
                    }
                }

                for (int i = 0; i < p; i++)
                {
                    active_t[path[i]] = 1; // ������ Ȱ��ȭ.

                    active_code[skillcode[path[i]] - 1]++; //�ڵ� �� Ȱ��ȭ �� ����.
                }
                money -= D[min] * 10000;
            }

        }
        else //��ų�� ������ �����ٸ� ��ų�� �ٽ� �����ϼ���
        {

        }
    }
    else if (code == 5) //�Է��� ������� ��� @
    {
        if (active_code[4] < 2) //��ų�� ������ �������� Ȯ��. ���� �� �����ٸ� �Ÿ��� ���� ª�� ��ų ã��. �̹� ���� ��ų ���� ����@
        {
            min = 20; //�Ÿ��� ���� ���� ���� �ʱ�ȭ. �ڵ忡 ���� �ٸ���. @
            for (int i = 0; i < MAX_SKILL; i++) //skillcode�� ��ȸ�ϸ鼭 ��ų�ڵ尡 �´� ���� ã�� 
            {
                if ((skillcode[i] == 5 && D[i] < D[min]) && active_t[i] == 0) //��ų�ڵ尡 �����鼭 �Ÿ��� �� ª���鼭 Ȱ��ȭ �Ǿ����� �ʴٸ� @
                {
                    min = i;
                }
            }

            if (money - D[min] * 10000 > 0) //���� �ش� ������ �Ÿ������� ���� ����ϴٸ�
            {
                //pre �迭���� min ���������� �� Ȱ��ȭ
                int p = 0; // Ȱ��ȭ ���Ѿ��� ���� ����
                for (int i = min; i != 0; i = pre[i]) //min �������� ���� �� Ȯ��.
                {
                    if (active_t[i] == 0) //�ش� ������ Ȱ��ȭ �Ǿ��ִ��� Ȯ��
                    {
                        path[p++] = i;
                    }
                    else
                    {
                        break;
                    }
                }

                for (int i = 0; i < p; i++)
                {
                    active_t[path[i]] = 1; // ������ Ȱ��ȭ.

                    active_code[skillcode[path[i]] - 1]++; //�ڵ� �� Ȱ��ȭ �� ����.
                }
                money -= D[min] * 10000;
            }

        }
        else //��ų�� ������ �����ٸ� ��ų�� �ٽ� �����ϼ���
        {

        }
    }
    else if (code == 6) //�Է��� ���߷��� ��� @
    {
        if (active_code[5] < 2) //��ų�� ������ �������� Ȯ��. ���� �� �����ٸ� �Ÿ��� ���� ª�� ��ų ã��. �̹� ���� ��ų ���� ����@
        {
            min = 20; //�Ÿ��� ���� ���� ���� �ʱ�ȭ. �ڵ忡 ���� �ٸ���. @
            for (int i = 0; i < MAX_SKILL; i++) //skillcode�� ��ȸ�ϸ鼭 ��ų�ڵ尡 �´� ���� ã�� 
            {
                if ((skillcode[i] == 6 && D[i] < D[min]) && active_t[i] == 0) //��ų�ڵ尡 �����鼭 �Ÿ��� �� ª���鼭 Ȱ��ȭ �Ǿ����� �ʴٸ� @
                {
                    min = i;
                }
            }

            if (money - D[min] * 10000 > 0) //���� �ش� ������ �Ÿ������� ���� ����ϴٸ�
            {
                //pre �迭���� min ���������� �� Ȱ��ȭ
                int p = 0; // Ȱ��ȭ ���Ѿ��� ���� ����
                for (int i = min; i != 0; i = pre[i]) //min �������� ���� �� Ȯ��.
                {
                    if (active_t[i] == 0) //�ش� ������ Ȱ��ȭ �Ǿ��ִ��� Ȯ��
                    {
                        path[p++] = i;
                    }
                    else
                    {
                        break;
                    }
                }

                for (int i = 0; i < p; i++)
                {
                    active_t[path[i]] = 1; // ������ Ȱ��ȭ.

                    active_code[skillcode[path[i]] - 1]++; //�ڵ� �� Ȱ��ȭ �� ����.
                }
                money -= D[min] * 10000;
            }

        }
        else //��ų�� ������ �����ٸ� ��ų�� �ٽ� �����ϼ���
        {

        }
    }
    else if (code == 7) //�Է��� ĭ�� ��� @
    {
        if (active_code[6] < 2) //��ų�� ������ �������� Ȯ��. ���� �� �����ٸ� �Ÿ��� ���� ª�� ��ų ã��. �̹� ���� ��ų ���� ����@
        {
            min = 20; //�Ÿ��� ���� ���� ���� �ʱ�ȭ. �ڵ忡 ���� �ٸ���. @
            for (int i = 0; i < MAX_SKILL; i++) //skillcode�� ��ȸ�ϸ鼭 ��ų�ڵ尡 �´� ���� ã�� 
            {
                if ((skillcode[i] == 7 && D[i] < D[min]) && active_t[i] == 0) //��ų�ڵ尡 �����鼭 �Ÿ��� �� ª���鼭 Ȱ��ȭ �Ǿ����� �ʴٸ� @
                {
                    min = i;
                }
            }

            if (money - D[min] * 10000 > 0) //���� �ش� ������ �Ÿ������� ���� ����ϴٸ�
            {
                //pre �迭���� min ���������� �� Ȱ��ȭ
                int p = 0; // Ȱ��ȭ ���Ѿ��� ���� ����
                for (int i = min; i != 0; i = pre[i]) //min �������� ���� �� Ȯ��.
                {
                    if (active_t[i] == 0) //�ش� ������ Ȱ��ȭ �Ǿ��ִ��� Ȯ��
                    {
                        path[p++] = i;
                    }
                    else
                    {
                        break;
                    }
                }

                for (int i = 0; i < p; i++)
                {
                    active_t[path[i]] = 1; // ������ Ȱ��ȭ.

                    active_code[skillcode[path[i]] - 1]++; //�ڵ� �� Ȱ��ȭ �� ����.
                }
                money -= D[min] * 10000;
            }

        }
        else //��ų�� ������ �����ٸ� ��ų�� �ٽ� �����ϼ���
        {

        }
    }
    else if (code == 8) //�Է��� ������ ��� @
    {
        if (active_code[7] < 2) //��ų�� ������ �������� Ȯ��. ���� �� �����ٸ� �Ÿ��� ���� ª�� ��ų ã��. �̹� ���� ��ų ���� ����@
        {
            min = 20; //�Ÿ��� ���� ���� ���� �ʱ�ȭ. �ڵ忡 ���� �ٸ���. @
            for (int i = 0; i < MAX_SKILL; i++) //skillcode�� ��ȸ�ϸ鼭 ��ų�ڵ尡 �´� ���� ã�� 
            {
                if ((skillcode[i] == 8 && D[i] < D[min]) && active_t[i] == 0) //��ų�ڵ尡 �����鼭 �Ÿ��� �� ª���鼭 Ȱ��ȭ �Ǿ����� �ʴٸ� @
                {
                    min = i;
                }
            }

            if (money - D[min] * 10000 > 0) //���� �ش� ������ �Ÿ������� ���� ����ϴٸ�
            {
                //pre �迭���� min ���������� �� Ȱ��ȭ
                int p = 0; // Ȱ��ȭ ���Ѿ��� ���� ����
                for (int i = min; i != 0; i = pre[i]) //min �������� ���� �� Ȯ��.
                {
                    if (active_t[i] == 0) //�ش� ������ Ȱ��ȭ �Ǿ��ִ��� Ȯ��
                    {
                        path[p++] = i;
                    }
                    else
                    {
                        break;
                    }
                }

                for (int i = 0; i < p; i++)
                {
                    active_t[path[i]] = 1; // ������ Ȱ��ȭ.

                    active_code[skillcode[path[i]] - 1]++; //�ڵ� �� Ȱ��ȭ �� ����.
                }
                money -= D[min] * 10000;
            }

        }
        else //��ų�� ������ �����ٸ� ��ų�� �ٽ� �����ϼ���
        {

        }
    }
    else if (code == 9)
    {
        if (active_code[8] < 1) //��ų�� ������ �������� Ȯ��. ���� �� �����ٸ� �Ÿ��� ���� ª�� ��ų ã��. �̹� ���� ��ų ���� ����@
        {
            min = 20; //�Ÿ��� ���� ���� ���� �ʱ�ȭ. �ڵ忡 ���� �ٸ���. @
            for (int i = 0; i < MAX_SKILL; i++) //skillcode�� ��ȸ�ϸ鼭 ��ų�ڵ尡 �´� ���� ã�� 
            {
                if ((skillcode[i] == 9 && D[i] < D[min]) && active_t[i] == 0) //��ų�ڵ尡 �����鼭 �Ÿ��� �� ª���鼭 Ȱ��ȭ �Ǿ����� �ʴٸ� @
                {
                    min = i;
                }
            }

            if (money - D[min] * 10000 > 0) //���� �ش� ������ �Ÿ������� ���� ����ϴٸ�
            {
                //pre �迭���� min ���������� �� Ȱ��ȭ
                int p = 0; // Ȱ��ȭ ���Ѿ��� ���� ����
                for (int i = min; i != 0; i = pre[i]) //min �������� ���� �� Ȯ��.
                {
                    if (active_t[i] == 0) //�ش� ������ Ȱ��ȭ �Ǿ��ִ��� Ȯ��
                    {
                        path[p++] = i;
                    }
                    else
                    {
                        break;
                    }
                }

                for (int i = 0; i < p; i++)
                {
                    active_t[path[i]] = 1; // ������ Ȱ��ȭ.

                    active_code[skillcode[path[i]] - 1]++; //�ڵ� �� Ȱ��ȭ �� ����.
                }
                money -= 2000000;
                wincondition++;
                if (wincondition == 3)
                {
                    scene = 5;
                }
            }
        }
        else //��ų�� ������ �����ٸ� ��ų�� �ٽ� �����ϼ���
        {

        }
    }

}

int skill_putkey()
{
    int key = 0;
    Sleep(10);
    if (_kbhit())
    {
        key = _getch();
    }
    if (key == 32) //���͸� �Է��� ��� ��ų���
    {
        findskill(skillinput());
        return 1;
    }
    if (key == 27) //ESCŰ�� ���� ��� ���� â���� �Ѿ.
    {
        system("cls");
        scene = 2;
        return 0;
    }
}

int main()
{
	system("mode con cols=150 lines=50");
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.bVisible = 0;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    for (int i = 0; i < 25; i++)
    {
        inventory[i].code = 0;
        inventory[i].weight = 0;
        inventory[i].price = 0;
    }
    inventory_full = 0;

    for (int i = 0; i < 7; i++)
    {
        fishcode[i] = 0;
    }

    //��ųƮ�� �迭 �ʱ�ȭ
    skilltree t = { 21,
       {{ 0, 2, 4, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
        { 0, 0, INF, 3, 5, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
        { 0, INF, 0, INF, INF, 5, 1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
        { INF, 2, INF, 0, INF, INF, INF, 4, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
        { INF, 2, INF, INF, 0, INF, INF, INF, 4, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
        { INF, INF, 4, INF, INF, 0, INF, INF, 4, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
        { INF, INF, 4, INF, INF, INF, 0, INF, INF, 4, 1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
        { INF, INF, INF, 3, INF, INF, INF, 0, INF, INF, INF, 5, 1, INF, INF, INF, INF, INF, INF, INF, INF},
        { INF, INF, INF, INF, 5, 5, INF, INF, 0, INF, INF, INF, INF, 2, INF, INF, INF, INF, INF, INF, INF},
        { INF, INF, INF, INF, INF, INF, 1, INF, INF, 0, INF, INF, INF, INF, 3, INF, INF, INF, INF, INF, INF},
        { INF, INF, INF, INF, INF, INF, 1, INF, INF, INF, 0, INF, INF, INF, INF, 4, 5, INF, INF, INF, INF},
        { INF, INF, INF, INF, INF, INF, INF, 4, INF, INF, INF, 0, INF, INF, INF, INF, INF, INF, INF, INF, INF},
        { INF, INF, INF, INF, INF, INF, INF, 4, INF, INF, INF, INF, 0, INF, INF, INF, INF, 1, INF, INF, INF},
        { INF, INF, INF, INF, INF, INF, INF, INF, 4, INF, INF, INF, INF, 0, INF, INF, INF, INF, 5, INF, INF},
        { INF, INF, INF, INF, INF, INF, INF, INF, INF, 4, INF, INF, INF, INF, 0, INF, INF, INF, 5, INF, INF},
        { INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1, INF, INF, INF, INF, 0, INF, INF, INF, 3, INF},
        { INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1, INF, INF, INF, INF, INF, 0, INF, INF, INF, INF},
        { INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1, INF, INF, INF, INF, 0, INF, INF, 200},
        { INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 2, 3, INF, INF, INF, 0, INF, 200},
        { INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 4, INF, INF, INF, 0, 200},
        { INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1, 5, 3, 0}}
    };

    initskillpos(); //��ų ���� ��ġ �ʱ�ȭ


    for (int i = 0; i < MAX_SKILL; i++) //Ȱ��ȭ�� ��ų ����� �ʱ�ȭ
    {
        active_t[i] = 0;
    }

    active_t[0] = 1; //���� ������ Ȱ��ȭ.

    while (1)
    {
        if (scene == 0)
        {
            intro();
        }
        else if (scene == 1) // ���� ���� ��.
        {
            for (int i = 0; i < 35; i++) //�ٴ� �迭 �ʱ�ȭ
            {
                for (int j = 0; j < 150; j++)
                {
                    seaarray[i][j] = ' ';
                }
            }
            currenttime = clock();
            mainstarttime = clock();
            player player;
            initplayer(&player); //�÷��̾� ���� �ʱ�ȭ

            fish* fishhead = NULL; //����� ��� ����. ���Ḯ��Ʈ�� ����.
            fishhead = initfish(fishhead); //����� ���Ḯ��Ʈ �ʱ�ȭ

            while (scene == 1)
            {
                putkey(&player, fishhead);
                if (fishcode[0] > 14 && fishcode[1] > 14 && fishcode[2] > 14 && fishcode[3] > 14 && fishcode[4] > 14 && fishcode[5] > 14 && fishcode[6] > 14 && fishcondition == 0)
                {
                    fishcondition = 1;
                    wincondition++;
                }
                if (wincondition == 3)
                {
                    scene = 5;
                }
                
                if ((clock() - currenttime > 100) && scene == 1) //��� ��Ȳ�� 0.1�ʸ��� ������
                {
                    gotoxy();
                    showinventory();
                    shipmove(&player);
                    seamove(fishhead, &player);
                    currenttime = clock();
                }
                if (clock() - mainstarttime > 30000)
                {
                    day++;
                    mainstarttime = clock();
                }
                if (day > 15)
                {
                    scene = 6;
                }
            }
        }
        else if (scene == 2) //���� â
        {
            gotoxy();
            print_store();
            while (1)
            {   
                int a = s_putkey();
                if (a == 0)
                {
                    break;
                }
            }
        }
        else if (scene == 3) //��ų â
        {
            shortest_path(&t, 0);
            findskill(skillinput());
        }
        else if (scene == 4) //�κ��丮 â
        {
            system("cls");
            gotoxy();
            printf("����������������������������������������������������������������������������\n");
            printf("\n\n");
            int fishcount = 0;
            printf("    �κ��丮 : \n\n");
            for (int i = 0; i < inventory_capacity; i++)
            {
                if (inventory[i].code == 1) {
                    fishcount++;
                }
            }
            printf("        -<    ��ġ   : %2d����\n", fishcount);

            fishcount = 0;
            for (int i = 0; i < inventory_capacity; i++)
            {
                if (inventory[i].code == 2) {
                    fishcount++;
                }
            }
            printf("        <@<   �췰   : %2d����\n", fishcount);

            fishcount = 0;
            for (int i = 0; i < inventory_capacity; i++)
            {
                if (inventory[i].code == 3) {
                    fishcount++;
                }
            }
            printf("        <@-   ���ڹ� : %2d����\n", fishcount);

            fishcount = 0;
            for (int i = 0; i < inventory_capacity; i++)
            {
                if (inventory[i].code == 4) {
                    fishcount++;
                }
            }
            printf("        <=<   ���� : %2d����\n", fishcount);

            fishcount = 0;
            for (int i = 0; i < inventory_capacity; i++)
            {
                if (inventory[i].code == 5) {
                    fishcount++;
                }
            }
            printf("        <@@=  ����   : %2d����\n", fishcount);

            fishcount = 0;
            for (int i = 0; i < inventory_capacity; i++)
            {
                if (inventory[i].code == 6) {
                    fishcount++;
                }
            }
            printf("        <==-  ���   : %2d����\n", fishcount);

            fishcount = 0;
            for (int i = 0; i < inventory_capacity; i++)
            {
                if (inventory[i].code == 6) {
                    fishcount++;
                }
            }
            printf("        <@+>< ��ġ   : %2d����\n\n\n", fishcount);

            printf("����������������������������������������������������������������������������\n\n\n");
            printf("    ���ݱ��� ���� ����� �� : \n\n");
            printf("        -<    ��ġ   : %2d����\n", fishcode[0]);
            printf("        <@<   �췰   : %2d����\n", fishcode[1]);
            printf("        <@-   ���ڹ� : %2d����\n", fishcode[2]);
            printf("        <=<   ���� : %2d����\n", fishcode[3]);
            printf("        <@@=  ����   : %2d����\n", fishcode[4]);
            printf("        <==-  ���   : %2d����\n", fishcode[5]);
            printf("        <@+>< ��ġ   : %2d����\n\n\n", fishcode[6]);

            printf("����������������������������������������������������������������������������\n\n\n");
            printf("        ���� ���� ���� : %d\n\n", inventory_w_capacity);
            printf("        ���� ũ�� ���� : %d\n\n", inventory_capacity);
            printf("        ���� ������ ���� : %d\n\n", pendulum);
            printf("        �̳� ���� : %d\n\n", range);
            printf("        �̳� ���� : %d\n\n", baitcount);
            printf("        ������ : %d\n\n", durability);
            printf("        ���� ���ʽ� : +%d%%\n\n", sense);
            printf("        ��Ÿ ���� : -%d%%\n\n", repeat * 20);
            char anykey[10];
            while (!_kbhit())
            {

            }
            system("cls");
            scene = 1;
        }
        else if (scene == 5) //���� Ŭ����
        {
            system("cls");
            good_end();
            return 0;
        }
        else if (scene == 6) //���� �й�
        {
            system("cls");
            bad_end();
            return 0;
        }
    }
    
}