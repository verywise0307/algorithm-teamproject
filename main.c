//콘솔창 이쁘게 지우기 https://blog.naver.com/1hadonghun1/223080002491
//키 입력 받기 https://dev-with-precious-dreams.tistory.com/7
//글씨 색 바꾸기 https://blog.naver.com/broadlg/222587279759
//글씨 색 바꾸기2 https://louky0714.tistory.com/155
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

#define _CRT_SECURE_NO_WARNINGS
#define col 150; //세로줄 개수
#define row 50; // 가로줄 개수
#define gaugey 9
int mainstarttime = 0;
int day = 0;

int currenttime;
int maketime;
int fishnum = 0; //물고기의 생성번호?
int amountoffish; //생성된 물고기 수
int inventory_full; //인벤토리 가득 찼는지.
int inventory_weight = 0; //인벤토리 무게가 얼마나 찼는지 관리
char seaarray[35][150]; //바다 배열. 물고기의 실제 이동칸은 130.
int seaposarray[35][150]; //바다배열에서 물고기 색칠용
char shiparray[5][150]; //바다 배열. 물고기의 실제 이동칸은 130.
int scene = 0;
int money = 0;
int durability = 10; //낚싯대 내구도
int d_stack = 0; //낚싯대 내구도 카운트
int pendulum = 15; //낚싯줄 내려가는 거리
int range = 5; //미끼 범위
int baitcount = 1; //미끼 수
int strength = 800; //근력
int sense = 0; //눈썰미
int repeat = 0; //제거할 연타 횟수 *20%
int inventory_capacity = 10; //인벤토리 칸
int inventory_w_capacity = 4000; //무게 제한

int fishcode[7]; //물고기를 각각 몇개 잡았는지 재기
int wincondition = 0;
int fishcondition = 0;
int moneycondition = 0;

typedef struct fish { //물고기 구조체
    int code; //종류
    char name[20];
    int num; //생성번호
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

typedef struct player { //플레이어 정보 구조체
    int x; //미끼 위치
    int y; //미끼 위치
    int active;
}player;

typedef struct Inventory { //인벤토리 1칸 구조체
    int code; //물고기 코드
    int weight; //무게
    int price; //가격
}Inventory;

Inventory inventory[35];

//스킬트리 관련 
#define MAX_SKILL 21 //스킬 스물한개(원점포함)
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
int D[MAX_SKILL]; //최단 경로 거리
int pre[MAX_SKILL]; //지나온 길
int active_t[MAX_SKILL]; //활성화된 스킬 0, 1로 구분
int amountofskill = 1; //활성화된 스킬 수
int active_code[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //코드 별 활성화 수
int skillcode[MAX_SKILL] = { 0, 1, 5, 3, 2, 4, 8, 5, 6, 6, 7, 4, 7, 1, 3, 5, 4, 8, 2, 3, 0 }; //스킬 정점별 코드
//스킬트리 관련

void gotoxy() {
    COORD pos = {0, 0};//여기만 바뀜
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void gotoxy1(int x, int y)
{
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void main_art()
{
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
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
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
}

void story()
{
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
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
    printf("                                                             [ 오늘은 내가 낚시왕 ]                                                                   \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                      평소 낚시를 취미로 하던 회사원인 당신                                                           \n");
    printf("                                                                                                                                                      \n");
    printf("                                                 갑작스러운 정리 해고로 백수 신세가 되어버렸지만                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                        오래 전 할아버지가 힘들 때 열어보라                                                           \n");
    printf("                                                                                                                                                      \n");
    printf("                                                              하셨던 편지를 열게 된다                                                                 \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                         편지에는 정체불명의 주소와 함께                                                              \n");
    printf("                                                                                                                                                      \n");
    printf("                                                 전설의 낚시왕이 되어 보라는 이야기가 적혀 있었고,                                                    \n");
    printf("                                                                                                                                                      \n");
    printf("                                               감명을 받은 당신은 낚시왕이 되기 위한 도전을 시작한다                                                  \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                              “낚시로 인생역전!                                                                      \n");
    printf("                                                               오늘은 내가 낚시왕!”                                                                  \n");
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
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
}

void condition()
{
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                         ■■■■■■■■■전설의 낚시왕, 그의 이야기 ■■■■■■■■■                                              \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                               ------------ 특별한 능력, 낚시의 정수 ------------                                                     \n");
    printf("                                                                                                                                                      \n");
    printf("                                                            전해지는 이야기에 따르면                                                                  \n");
    printf("                                                                                                                                                      \n");
    printf("                                                          낚시왕에게는 낚시의 정수라는                                                                \n");
    printf("                                                                                                                                                      \n");
    printf("                                                         특별한 능력이 있다고 전해진다.                                                               \n");
    printf("                                                                                                                                                      \n");
    printf("                                            낚시의 왕이 되고 싶다면  낚시의 정수가 매우 중요할 것이다.                                                \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                ------------ 바닥부터 올라온 낚시왕 ------------                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                낚시왕은 원래 매우 가난한 삶을 살았다고 전해진다.                                                     \n");
    printf("                                                                                                                                                      \n");
    printf("                                                  끊임없는 낚시를 통해  막대한 부를 쌓게 되었고                                                       \n");
    printf("                                                                                                                                                      \n");
    printf("                                                       그가 번 돈은 끝도 없을 정도라고 한다.                                                          \n");
    printf("                                                                                                                                                      \n");
    printf("                          최소한 삼백 만원 정도는 가지고 낚시왕 타이틀을 단다면 그의 명예에 먹칠을 하는 것과 다름없다.                                \n");
    printf("                                                                                                                                                      \n");
    printf("                                                 전설의 낚시왕이 되어 보라는 이야기가 적혀 있었고,                                                    \n");
    printf("                                                                                                                                                      \n");
    printf("                                               감명을 받은 당신은 낚시왕이 되기 위한 도전을 시작한다                                                  \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                  ------------ 물고기의 모든 것 ------------                                                          \n");
    printf("                                                                                                                                                      \n");
    printf("                                                     낚시왕에겐 모르는 물고기가 없다고 한다.                                                          \n");
    printf("                                                                                                                                                      \n");
    printf("                                                      물고기의 선호 미끼, 무게, 습성 등을                                                             \n");
    printf("                                                                                                                                                      \n");
    printf("                                                           꿰고 있을 수 있던 이유는                                                                   \n");
    printf("                                                                                                                                                      \n");
    printf("                                                       물고기를 수도 없이 잡았기 때문이다.                                                            \n");
    printf("                                                                                                                                                      \n");
    printf("                                                       최소한 각 물고기를 15번은 잡아야지                                                             \n");
    printf("                                                                                                                                                      \n");
    printf("                                                 그 물고기에 대한 모든 것을 알 수 있을 것이다.                                                        \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                      --->                                                                            \n");
    printf("                                                                                                                                                      \n");
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
}

void howtoplay()
{
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                    ■■■■■■■■■게임 방법 ■■■■■■■■■                                                    \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                           ------------ 낚시 ------------                                                             \n");
    printf("                                                                                                                                                      \n");
    printf("                                                            배를 움직이기 :  좌우 방향키                                                              \n");
    printf("                                                                                                                                                      \n");
    printf("                                                           낚시줄을 내리기 : 스페이스바                                                               \n");
    printf("                                                                                                                                                      \n");
    printf("                                                 물고기를 잡기 : 물고기가 가까이 왔을 때 스페이스바                                                   \n");
    printf("                                                                                                                                                      \n");
    printf("                                                 물고기 낚기 (미니게임) : 1초안에 좌우 방향키 연타                                                    \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                         ------------ 상호작용 ------------                                                           \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                     상점 : s                                                                         \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                   인벤토리 : i                                                                       \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                         ------------ 시간제한 ------------                                                           \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                     총 15일차                                                                        \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                   일차 당 30초                                                                       \n");
    printf("                                                                                                                                                      \n");
    printf("                                                         15일차 이내에 낚시왕이 되어야 함                                                             \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                          ------------ 기타 ------------                                                              \n");
    printf("                                                                                                                                                      \n");
    printf("                                                            돈이 마이너스가 되면 파산                                                                 \n");
    printf("                                                                                                                                                      \n");
    printf("                                                     낚시대를 한 번 내릴 떄 마다 내구도 감소                                                          \n");
    printf("                                                                                                                                                      \n");
    printf("                                                 가방에 물고기를 넣을 수 있는 무게와 수 제한 존재                                                     \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
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
    gotoxy1(17, 23); printf("무게 : 가방의 담을 수 있는 물고기의 최대 무게가 증가합니다. (+1: 9kg) (+2: 20kg)");
    gotoxy1(17, 25); printf("칸 : 가방에 담을 수 있는 물고기의 최대 양이 증가합니다 (+1: 20) (+2: 30)");
    gotoxy1(17, 27); printf("내구도 : 낚시대의 내구도가 증가합니다 (+1: 20) (+2: 30)");
    gotoxy1(17, 29); printf("미끼 : 물고기를 한 번에 여러 마리를 낚거나 미끼의 영향 범위가 증가합니다 (+1: 범위 6) (+2: 개수 2) (+3: 범위 7, 개수 3)");
    gotoxy1(17, 31); printf("눈썰미 : 물고기의 기본 가격이 상승합니다 (+1: +10%%) (+2: +20%%) (+3: +30%%)");
    gotoxy1(17, 33); printf("순발력 : 물고기를 잡는 미니게임이 더 쉬워집니다 (+1: 연타 횟수 -60%%) (+2: 연타 횟수 -80%%)");
    gotoxy1(17, 35); printf("근력 : 특정 물고기를 잡거나 여러 마리를 한 번에 잡을 수 있는 근력을 증가시킵니다 (+1: 1.2kg) (+2: 2kg) (+3: 3.5kg)");
    gotoxy1(17, 37); printf("추 : 낚싯줄을 더 아래까지 내릴 수 있습니다 (+1: 25) (+2: 35)");
    gotoxy1(17, 39); printf("낚시의 정수 : 낚시왕이 가지고 있던 전설의 정수");
}

void victory()
{
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                         ■■■■■■■■■전설의 낚시왕, 그의 이야기 ■■■■■■■■■                                              \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                               ------------ 특별한 능력, 낚시의 정수 ------------                                                     \n");
    printf("                                                                                                                                                      \n");
    printf("                                                            전해지는 이야기에 따르면                                                                  \n");
    printf("                                                                                                                                                      \n");
    printf("                                                          낚시왕에게는 낚시의 정수라는                                                                \n");
    printf("                                                                                                                                                      \n");
    printf("                                                         특별한 능력이 있다고 전해진다.                                                               \n");
    printf("                                                                                                                                                      \n");
    printf("                                            낚시의 왕이 되고 싶다면  낚시의 정수가 매우 중요할 것이다.                                                \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                ------------ 바닥부터 올라온 낚시왕 ------------                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                낚시왕은 원래 매우 가난한 삶을 살았다고 전해진다.                                                     \n");
    printf("                                                                                                                                                      \n");
    printf("                                                  끊임없는 낚시를 통해  막대한 부를 쌓게 되었고                                                       \n");
    printf("                                                                                                                                                      \n");
    printf("                                                       그가 번 돈은 끝도 없을 정도라고 한다.                                                          \n");
    printf("                                                                                                                                                      \n");
    printf("                               최소한 n원 정도는 가지고 낚시왕 타이틀을 단다면 그의 명예에 먹칠을 하는 것과 다름없다.                                 \n");
    printf("                                                                                                                                                      \n");
    printf("                                                 전설의 낚시왕이 되어 보라는 이야기가 적혀 있었고,                                                    \n");
    printf("                                                                                                                                                      \n");
    printf("                                               감명을 받은 당신은 낚시왕이 되기 위한 도전을 시작한다                                                  \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                                                                                                      \n");
    printf("                                                  ------------ 물고기의 모든 것 ------------                                                          \n");
    printf("                                                                                                                                                      \n");
    printf("                                                     낚시왕에겐 모르는 물고기가 없다고 한다.                                                          \n");
    printf("                                                                                                                                                      \n");
    printf("                                                      물고기의 선호 미끼, 무게, 습성 등을                                                             \n");
    printf("                                                                                                                                                      \n");
    printf("                                                           꿰고 있을 수 있던 이유는                                                                   \n");
    printf("                                                                                                                                                      \n");
    printf("                                                       물고기를 수도 없이 잡았기 때문이다.                                                            \n");
    printf("                                                                                                                                                      \n");
    printf("                                                        최소한 각 물고기를 n번은 잡아야지                                                             \n");
    printf("                                                                                                                                                      \n");
    printf("                                                 그 물고기에 대한 모든 것을 알 수 있을 것이다.                                                        \n");
    printf("                                                                                                                                                      \n");
    printf("                                                                      --->                                                                            \n");
    printf("                                                                                                                                                      \n");
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
}

void grandfather_soso()
{
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
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
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
}

void grandfather_angry()
{
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
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
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
}

void grandfather_happy()
{
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
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
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
}

void bad_art()
{
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
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
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
}

void good_art()
{
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
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
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
}

void print_store()
{
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
    printf("■                                                                          ■                                                                        \n");
    printf("■                                                                          ■                                                                        \n");
    printf("■          어서 와, 없는게 없으니 사고 싶은 물건이 있으면 둘러봐~          ■                                                                        \n");
    printf("■                                                                          ■                                                                        \n");
    printf("■                                                                          ■                         낚시터로 돌아가기 : ESC                        \n");
    printf("■■■■■      ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■                                                                        \n");
    printf("■       ■   ■                                                            ■                                                                        \n");
    printf("■        ■ ■                                        rBbi77.              ■                          상점에 물고기 팔기 : F                        \n");
    printf("■         ■                                         BBBBBBBBv             ■                                                                        \n");
    printf("■                                                  :BBBQBBBBBQu            ■                                                                        \n");
    printf("■                                                  rBBBBBBBBBBB            ■                                                                        \n");
    printf("■                                                   BBBBBQBBBB             ■                                                                        \n");
    printf("■                                                   rBQBBBBBBu             ■                                                                        \n");
    printf("■                                                    BBBBBBBi              ■                             낚싯대 수리 : R                            \n");
    printf("■                                                  .uBBBBBQK               ■                              [ 30,000원 ]                              \n");
    printf("■                                           .qBBBBBBBBBBBQBM               ■                                                                        \n");
    printf("■   BBQBBBBBBBBBBB                         2BBBBBBBBBBBBBBBBQB7            ■                                                                        \n");
    printf("■   BBBBBBBBBBBBBB                      .QBQBBBBBBBQBBBBBBBBBBBQQ.         ■                                                                        \n");
    printf("■   5BESBBBBXPbEDB                      QBBBBBBBBBBBBBBBQBBBBBBBBBQ        ■                                                                        \n");
    printf("■       RBBQ                          .BBBBBBBBBBBBBBBBBBBBBBBBBBBBr       ■                              스킬 구매 : S                             \n");
    printf("■       QBBB                         .BBBBBBBBBBBBBBBBBBBBBBBBBBBBBB       ■                        ( 낚시의 정수 : 200만원 )                       \n");
    printf("■   BBBBBBBBBBBBBBBBBQB              7BBBBBQjQBBBQBBBBBBBBBBBBBQBBBB       ■                                                                        \n");
    printf("■   QBBBBBQBBBBBBBBBBBB              BBBBBB. BBBBBBBBBBBQBBBBBBBBBBBr      ■                          무  게 : [ 10,000원 ]                         \n");
    printf("■   BBBBBBBBBBBQBBBBBBB             PBBQBBU .BBBBQBBBBBBBBBBBQBQBQBBBi     ■                            칸   : [ 10,000원 ]                         \n");
    printf("■   BBBBQBBBBBBBBBBBBBB             BBBBBP  LBBBBBBBBBBBQBBBQBBBBBBBBB     ■                          내구도 : [ 20,000원 ]                         \n");
    printf("■   BBBQBQBBBQBQBBBBBBB            .BBBBB2  QBBBBBBBBQBBBBBBBBBBBBBBBB     ■                          미  끼 : [ 30,000원 ]                         \n");
    printf("■   BBBBBBBBBBBBBBBBBBB             BBBBQBr BBBBBBBBQBBBBBBBBBBBBBBBBB:    ■                          눈썰미 : [ 40,000원 ]                         \n");
    printf("■   BBBBBBBBBBBBBQBBBQB             rBBBBBBsBBBQBQBBBBBQBBBBBBBBBBBQBB     ■                          순발력 : [ 40,000원 ]                         \n");
    printf("■   BBQBBBBBBBBBBBBBBBB              vBBBBBBBBBBBBBBQBBBQBBBBBBBQBBBBB     ■                          근  력 : [ 50,000원 ]                         \n");
    printf("■  .BBBBBBBBBBBBBBBBBBB               JBBBBBBBBQBBBQBBBBBQBBBQBBBQBBBB5    ■                                                                        \n");
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
    printf("■                                                                          ■                                                                        \n");
    printf("■             ■■■   ■■■■    ■■■    ■■■     ■■■■           ■                                                                        \n");
    printf("■            ■           ■      ■    ■   ■   ■    ■                 ■                                                                        \n");
    printf("■            ■■■■     ■     ■      ■  ■■■     ■■■■           ■현재 돈 : %d 원\n", money);
    printf("■                  ■     ■      ■    ■   ■  ■     ■                 ■                                                                        \n");
    printf("■             ■■■      ■       ■■■    ■   ■    ■■■■           ■                                                                        \n");
    printf("■                                                                          ■                                                                        \n");
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
}

void good_end()
{
    system("cls"); grandfather_soso();

    gotoxy1(35, 44); printf("회사에서 잘리고 난 후 난 낚시왕이 되기 위해서 하염없이 달려왔다.");
    gotoxy1(35, 45); printf("나는 오늘 무언가 일어난다고 직감했다.");
    gotoxy1(35, 46); printf("곧 다가올 거대한 일을 대비하던 중 하늘에서 할아버지의 영혼이 나타났다."); _getch();

    gotoxy1(35, 44); printf("                                                                                                                                                      \n");
    gotoxy1(35, 45); printf("                                                                                                                                                      \n");
    gotoxy1(35, 46); printf("                                                                                                                                                      \n");

    gotoxy1(35, 44); printf("할아버지의 영혼이 나에게 말했다.");
    gotoxy1(35, 45); printf("낚시왕의 정신을 이어받으려는 너의 노력, 그동안 잘 지켜보았다 손자야.");
    gotoxy1(35, 46); printf("전직 낚시왕인 이 할애비가 너가 낚시왕의 정신을 이어받을 자격이 있는지 판단해 주겠다."); _getch();

    gotoxy1(35, 44); printf("                                                                                                                                                      \n");
    gotoxy1(35, 45); printf("                                                                                                                                                      \n");
    gotoxy1(35, 46); printf("                                                                                                                                                      \n");

    gotoxy1(35, 44); printf("흐음....");
    gotoxy1(35, 45); printf("아니 이것은...??!!"); _getch();

    system("cls"); grandfather_happy();

    gotoxy1(35, 44); printf("이 할애비는 감동이다.");
    gotoxy1(35, 45); printf("낚시왕에 걸맞는 부를 가지고 있으며, 모든 물고기를 꿰고 있고, 낚시의 정수까지 가지고 있다니!");
    gotoxy1(35, 46); printf("너는 낚시왕을 이을 자격이 된다. 이제부터 손자 너는 낚시왕이다!"); _getch();

    gotoxy1(35, 44); printf("                                                                                                                                                      \n");
    gotoxy1(35, 45); printf("                                                                                                                                                      \n");
    gotoxy1(35, 46); printf("                                                                                                                                                      \n");

    gotoxy1(35, 44); printf("나는 기뻐하며 할어버지의 영혼에게 말을 했다.");
    gotoxy1(35, 45); printf("정말 감사합니다!");
    gotoxy1(35, 46); printf("나의 말이 끝나자 할아버지의 영혼은 흐뭇한 미소를 지으며 사라졌다."); _getch();

    system("cls"); good_art();

    gotoxy1(35, 44); printf("그렇게 나는 할아버지에게서 낚시왕의 자리를 물려받고");
    gotoxy1(35, 45); printf("막대한 부를 쌓으며 유유자적히 살게 되었다.");
    gotoxy1(35, 46); printf("- good ending -"); _getch();

    system("cls"); main_art(); _getch();
}

void bad_end() {
    system("cls"); grandfather_soso();

    gotoxy1(35, 44); printf("회사에서 잘리고 난 후 난 낚시왕이 되기 위해서 하염없이 달려왔다.");
    gotoxy1(35, 45); printf("나는 오늘 무언가 일어난다고 직감했다.");
    gotoxy1(35, 46); printf("곧 다가올 거대한 일을 대비하던 중 하늘에서 할아버지의 영혼이 나타났다."); _getch();

    gotoxy1(35, 44); printf("                                                                                                                                                      \n");
    gotoxy1(35, 45); printf("                                                                                                                                                      \n");
    gotoxy1(35, 46); printf("                                                                                                                                                      \n");

    gotoxy1(35, 44); printf("할아버지의 영혼이 나에게 말했다.");
    gotoxy1(35, 45); printf("낚시왕의 정신을 이어받으려는 너의 노력, 그동안 잘 지켜보았다 손자야.");
    gotoxy1(35, 46); printf("전직 낚시왕인 이 할애비가 너가 낚시왕의 정신을 이어받을 자격이 있는지 판단해 주겠다."); _getch();

    gotoxy1(35, 44); printf("                                                                                                                                                      \n");
    gotoxy1(35, 45); printf("                                                                                                                                                      \n");
    gotoxy1(35, 46); printf("                                                                                                                                                      \n");

    gotoxy1(35, 44); printf("흐음....");
    gotoxy1(35, 45); printf("아니 이것은...??!!"); _getch();

    system("cls"); grandfather_angry();

    gotoxy1(35, 44); printf("예끼 이놈! 내가 상놈의 손자를 두었구나!");
    gotoxy1(35, 45); printf("이거이거 완전 생 그지에, 물고기에 대해 아무것도 모르고, 낚시의 정수도 가지고 있지 않다니!");
    gotoxy1(35, 46); printf("너는 낚시왕을 이을 자격이 안된다. 아니 이제 나의 손자도 아니다. 다시는 낚시도 하지 말거라!"); _getch();

    gotoxy1(35, 45); printf("                                                                                                                                                      \n");
    gotoxy1(35, 46); printf("                                                                                                                                                      \n");
    gotoxy1(35, 47); printf("                                                                                                                                                      \n");

    gotoxy1(35, 44); printf("나는 당황하며 할어버지의 영혼에게 말을 했다.");
    gotoxy1(35, 45); printf("아니, 할어버지! 잠깐만요!");
    gotoxy1(35, 46); printf("나의 말이 끝나기도 전에 할아버지의 영혼은 온갖 욕설을 내뱉으며 사라졌다."); _getch();

    system("cls"); bad_art();

    gotoxy1(35, 44); printf("그렇게 나는 할아버지에게 절연을 당하고 낚시도 못하게 되었다.");
    gotoxy1(35, 45); printf("결국 나는 술에 찌든 방구석 폐인 생활을 이어가게 되었다.");
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
    p->x = startx; //x를 왼쪽, 오른쪽 랜덤으로

    if (p->x == 10) p->speed = rand()%3 + 1; //시작 지점에 따라 속도 정하기
    else p->speed = -rand() % 3 - 1;

    p->code = rand() % 7 + 1; //물고기 코드 만들기

    p->num = fishnum++;

    amountoffish++; //현재 바다에 있는 물고기 수 증가

    switch (p->code) //코드에 따라 가격과 무게, 모양을 설정
    {
        case 1:
            p->y = rand() % 35;
            p->weight= rand()%5 + 5;
            p->price = p->weight * 30;
            strcpy_s(p->name, 15,"멸치");
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
            strcpy_s(p->name, 15, "우럭");
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
            strcpy_s(p->name, 15, "가자미");
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
            strcpy_s(p->name, 15, "고등어");
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
            strcpy_s(p->name, 15, "광어");
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
            strcpy_s(p->name, 15, "장어");
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
            strcpy_s(p->name, 15, "참치");
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

fish* fishdelete(fish* fishhead, fish* pre) //노드 지우고 이전 노드 반환
{
    amountoffish--;
    fish* r;
    r = pre->link;
    pre->link = r->link;
    free(r);
    return pre;
}

void updatesea(fish* fishhead, player *player) //바다 배열 업데이트
{
    fish* pre = fishhead;
    for (int i = 0; i < 35; i++) //바다 배열 초기화
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

    for (fish* p = fishhead->link; p != NULL; p = p->link) //배열에 물고기 넣기
    {
        if (p->speed > 0) //배열에 물고기 위치 표시
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

        p->x += p->speed; //물고기 이동
        p->distance = (int)sqrt(pow((p->x - player->x), 2) / 2 + pow((p->y - player->y), 2)); //미끼와 물고기 거리 계산
        if ((p->x < 10 && p->speed < 0) || (p->x > 139 && p->speed > 0))
        {
            p = fishdelete(fishhead, pre);
        }

        pre = p;
    }

    if (player->active == 1) player->y += 2; //배열에 낚싯줄 넣기
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

} //바다 배열 업데이트

void seamove(fish *fishhead, player *player) // 바다 움직임 총괄
{

    if (clock() - maketime > 1000) // 1초마다 물고기 생성
    {
        makefish(fishhead);
        maketime = clock();
    }

    updatesea(fishhead, player); //바다 배열 업데이트.

    COORD pos = { 0, 15};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

    for (int i = 0; i < 35; i++) //바다 배열 그리기
    {
        for (int j = 0; j < 150; j++)
        {
            if (seaposarray[i][j] == 0)
            {

            }
            else if (seaposarray[i][j] == 1)
            {
                printf("\033[1;33m"); //노랑
            }
            else if (seaposarray[i][j] == 2)
            {
                printf("\033[0;33m"); //주황
            }
            else if (seaposarray[i][j] == 3)
            {
                printf("\033[0;32m"); //초록
            }
            else if (seaposarray[i][j] == 4)
            {
                printf("\033[1;32m"); //진한 초록
            }
            else if (seaposarray[i][j] == 5)
            {
                printf("\033[1;95m"); //보라
            }
            else if (seaposarray[i][j] == 6)
            {
                printf("\033[1;36m"); //밝은 빨강
            }
            else if (seaposarray[i][j] == 7)
            {
                printf("\033[0;31m"); //빨강
            }
            else if (seaposarray[i][j] == 8)
            {
                printf("\033[0;34m"); //파랑
            }
            printf("%c", seaarray[i][j]);
            printf("\033[0m");
        }
    }
} // 바다 움직임 총괄

int compare(Inventory* a, Inventory* b) //비교
{
    int num1 = a->code; //원래 price
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

void catchfish(player* player, fish* fishhead) //물고기 포획
{
    fish* pre = fishhead;
    int* dist = (int*)malloc(sizeof(int) * amountoffish); //물고기 거리 정렬저장
    int* num = (int*)malloc(sizeof(int) * amountoffish); //그 물고기 식별 num 저장
    int* weightarray = (int*)malloc(sizeof(int) * amountoffish); //그 물고기 무게 저장
    int d_tmp;
    int n_tmp;
    int w_tmp;
    for (int i = 0; i < amountoffish; i++)
    {
        dist[i] = 200;
    }

    for (fish* p = fishhead->link; p != NULL; p = p->link) //미끼로부터 물고기 거리와 생성번호 정렬
    {
        int d_min = p->distance;
        int n_min = p->num;
        int w_min = p->weight;

        for (int i = 0; i < amountoffish; i++)
        {
            if (d_min < dist[i]) //배열 정렬
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
    //잡을 수 있는 물고기 계산
    for (int i = 0; i < baitcount; i++) {
        if (dist[i] < range && weightarray[i] + totalweight < strength) { //물고기가 범위 안이고 무게 합이 근력을 넘지 않는다면
            totalcount++;
            totalweight += weightarray[i];
        }
    }

    int hitclear = 0;

    //물고기가 범위 내에 있다면 연타수행.
    if (dist[0] < range) {
        int hitstart = clock();
        int hit = 0;
        int key = 0;
        int prekey = 0;

        COORD pos = { player->x - 3, gaugey };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        int hitratio = 0;

        while (clock() - hitstart < 1000) //1초 동안 연타 작업을 수행
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
                    if ((key == 75 && prekey == 0) || (key == 75 && prekey == 1)) //왼쪽
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
                    else if ((key == 77 && prekey == 0) || (key == 77 && prekey == -1)) //오른쪽
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

    for (int k = 0; k < totalcount; k++) //잡을 수 있는 물고기 수만큼 잡기
    {
        pre = fishhead;
        for (fish* p = fishhead->link; p != NULL; p = p->link)
        {
            if (p->num == num[k]) //삭제해야 할 물고기를 찾았다면
            {
                if (hitclear == 1)
                {
                    inventory[inventory_full].code = p->code;
                    inventory[inventory_full].weight = p->weight;
                    inventory_weight += inventory[inventory_full].weight;
                    inventory[inventory_full++].price = p->price + (p->price / 100) * sense; // sense% 씩 가격 보너스
                    fishcode[p->code-1]++;
                    p = fishdelete(fishhead, pre);
                }


                if (inventory_full > inventory_capacity || inventory_weight > inventory_w_capacity) //허걱 배낭에 넣고 보니 기준치를 넘어가잖아? 배낭 문제로 해결하자. 
                {
                    //배낭문제 함수 등장! 
                    Inventory bag[36];
                    int tmp_inventory = 0;
                    int tmp_weight = 0;

                    qsort(inventory, inventory_full, sizeof(Inventory), compare);//퀵소트 함수

                    for (int i = 0; i < inventory_full; i++)
                    {
                        if (tmp_inventory > inventory_capacity || tmp_weight > inventory_w_capacity)// 기준치 넘어가면 탈출
                        {
                            break;
                        }

                        if (tmp_weight + inventory[i].weight <= inventory_w_capacity)// 임시 배열에 그리디하게 넣기 (테트리스)
                        {
                            bag[tmp_inventory].code = inventory[i].code;
                            bag[tmp_inventory].price = inventory[i].price;
                            bag[tmp_inventory].weight = inventory[i].weight;

                            tmp_weight += inventory[i].weight;
                            tmp_inventory++;
                        }
                    }

                    for (int i = 0; i < tmp_inventory; i++)// 임시 변수 템프에서 본체로 옮기기
                    {
                        inventory[i].code = bag[i].code;
                        inventory[i].price = bag[i].price;
                        inventory[i].weight = bag[i].weight;
                    }

                    for (int i = tmp_inventory; i < inventory_capacity; i++) // 못 옮기면 초기화 
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
    if (key == 224 && player->active != 1) //방향키를 입력 했을 때 낚싯줄이 내려가는 중이 아닐 때
    {
        key = _getch();
        switch (key)
        {
        case 75: // 왼쪽
        {
            if (player->x > 10) player->x -= 1;
            break;
        }
        case 77: // 오른쪽
        {
            if (player->x < 139) player->x += 1;
            break;
        }
        case 72: // 위
            break;;
        case 80: // 아래
            break;;
        }
    }
    else if (key == 32) //스페이스 바를 입력 했을 때
    {
        if (player->active == 0)
        {
            if (d_stack < durability)
            {   
                player->active = 1; //미끼를 내림
                d_stack++;
            }
        }
        else //미끼를 올림
        {
            player->active = 0;
            catchfish(player, fishhead);
            player->y = 0;
        }
    }
    else if (key == 83 || key == 115) //상점(S)을 입력할 경우 상점창으로 이동
    {
        fish* pre = fishhead;
        for (fish* p = fishhead->link; p != NULL; p = p->link) //물고기 연결리스트 삭제
        {
            p = fishdelete(fishhead, pre);
            pre = p;
        }
        free(fishhead);
        system("cls");
        scene = 2;
    }
    else if (key == 73 || key == 105) //상태창
    {
        system("cls");
        scene = 4;
    }
    else
    {

    }
}

void shipmove(player* player) // 배 움직임 총괄
{
    for (int i = 0; i < 5; i++) //배열 초기화
    {
        for (int j = 0; j < 150; j++)
        {
            shiparray[i][j] = ' ';
        }
    }

    for (int i = 2; i < 4; i++) //배열에 배 모양 넣기
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

    for (int i = 0; i < 5; i++) //배 출력
    {
        for (int j = 0; j < 150; j++)
        {
            if (i == 4)
            {
                printf("\033[0;34m"); //파랑
            }
            printf("%c", shiparray[i][j]);
            printf("\033[0m");
        }
        printf("\n");
    }
}

void showinventory()
{
    printf("             상점 : S   상태창 : I\n");
  //  for (int i = 0; i < 25; i++)
  //  {
  //      printf("%d ", inventory[i].code);
  //  }
    printf("             현재 돈 : %d      낚싯대 내구도 : %2d      일차 : %2d\n", money, durability - d_stack, day);
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
    if (key == 27) //ESC키를 누를 경우 메인 게임 창으로 넘어감.
    {
        system("cls");
        scene = 1;
        return 0;
    }
    else if (key == 70 || key == 102) // F키를 누를 경우 인벤토리의 물고기들을 팔아서 돈으로 환산.
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
    else if (key == 32 || key == 114) //R키를 누를 경우 낚싯대 수리
    {   
        system("cls");
        if (money >= 30000 && d_stack > 0) {
            money -= 30000;
            d_stack = 0;
        }

        if (d_stack == durability && money < 30000) //만약 내구도를 복구할 돈이 없다면 패배
        {
            scene = 6;
            return 0;
        }
    }
    else if (key == 83 || key == 115) // S키를 누를 경우 스킬 창으로 넘어가기.
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

void initskillpos() //스킬 정점 위치 초기화
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

int choose(int n, int found[]) //가장 가까운 정점 찾기
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
        "                                                 --- 근력          ",
        "                       --- 미끼 -----  눈썰미 ---|             ",
        "         --- 내구도 ---|                         --- 칸  ------- 무게 ---",
        "         |             ---  추  ---                                     |",
        "start ---|                        |--- 순발력 --- 내구도 ---            |",
        "         |             --- 근력 ---                        |----- 추 ---|--- 낚시의 정수",
        "         --- 눈썰미 ---|                                   |            |",
        "                       |           --- 순발력 ---  미끼 ----            |",
        "                       --- 무게 ---|                                    |",
        "                                   |           --- 눈썰미  ----- 미끼 ---",
        "                                   ---   칸 ---|                         ",
        "                                               --- 근력" };
    for (int i = 0; i < 12; i++) //우선 스킬트리를 그리고
    {
        COORD pos = { skillx, skilly + i }; //커서 좌표 이동 후
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        for (int j = 0; j < 100; j++)
        {
            printf("%c", skillUI[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < MAX_SKILL; i++) //스킬이 활성화 되어 있는지 확인
    {
        if (active_t[i] == 1) //활성화 되었다면
        {
            COORD pos = { skillx + skillpos[i].x , skilly + skillpos[i].y}; //커서 좌표 이동 후
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
            printf("\033[0;33m"); //노란색으로
            for (int j = skillpos[i].x; j < skillpos[i].size + skillpos[i].x; j++)
            {
                printf("%c", skillUI[skillpos[i].y][j]);
            }
            printf("\033[0m\n"); //흰색으로
        }
    }

    skill_itd();

}

void shortest_path(skilltree* t, int start)
{
    int found[MAX_SKILL]; //찾은 정점
    int min, w;

    for (int i = 0; i < t->n; i++)  //거리를 저장할 D 배열 초기화
    {
        if (active_t[i] == 1) //찍은 스킬 거리 0으로
        {
            t->weight[0][i] = 0;
        }
        D[i] = t->weight[start][i];
        pre[i] = 0;
        found[i] = FALSE;
    }

    found[start] = TRUE; //시작 표시
    D[start] = 0;
    for (int i = 0; i < t->n - 1; i++) {
        min = choose(t->n, found);
        found[min] = TRUE;
        for (w = 0; w < t->n; w++) //간선 가중치 완화
        {
            if (!found[w])
            {
                if (D[min] + t->weight[min][w] < D[w]) //이전 거리보다 새로 찾은 거리가 더 적을 때
                {

                    D[w] = D[min] + t->weight[min][w]; //간선완화
                    pre[w] = min; //본인 이전 정점 기록
                }
            }
        }

    }
    print_status2(found);
 //   print_status(found);
}

int skillinput() //스킬을 속성에 따라 문자열로 입력 후 정수로 리턴. 
{
    COORD pos = { 60, 43 }; //커서 좌표 이동 후
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    char skill_answer[20]; //스킬을 입력받을 문자열
    printf("입력 : ");
    fgets(skill_answer, sizeof(skill_answer), stdin);
    system("cls");
    char s1[] = "내구도\n";
    char s2[] = "추\n";
    char s3[] = "미끼\n";
    char s4[] = "근력\n";
    char s5[] = "눈썰미\n";
    char s6[] = "순발력\n";
    char s7[] = "칸\n";
    char s8[] = "무게\n";
    char s9[] = "낚시의 정수\n";
    char s10[] = "나가기\n";
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
        printf("다시\n");
        return 0;
    }
}

int setskill() //찍힌 스킬에 따라 세팅.
{
    if (active_code[0] == 1) //내구도 +1
    {
        durability = 20;
    }
    else if (active_code[0] == 2) //내구도 +2
    {
        durability = 30;
    }

    if (active_code[1] == 1) //추 +1
    {
        pendulum = 25;
    }
    else if (active_code[1] == 2)
    {
        pendulum = 35;
    }

    if (active_code[2] >= 1) //미끼 +1 미끼범위 확장
    {
        range = 6;
    }
    if (active_code[2] >= 2) //미끼 +2 미끼 개수 2개
    {
        baitcount = 2;
    }
    if (active_code[2] == 3) //미끼 +3 범위 개수 증가
    {
        range = 7;
        baitcount = 3;
    }

    if (active_code[3] == 1) //근력 +1
    {
        strength = 1200;
    }
    else if (active_code[3] == 2) //근력 +2
    {
        strength = 2000;
    }
    else if (active_code[3] == 3) //근력 +3
    {
        strength = 3500;
    }

    if (active_code[4] == 1) //눈썰미 +1
    {
        sense = 10;
    }
    else if (active_code[4] == 2) //눈썰미 +2
    {
        sense = 20;
    }
    else if (active_code[4] == 3) //눈썰미 +3
    {
        sense = 30;
    }

    if (active_code[5] == 1) // 순발력 +1 연타 횟수 제거
    {
        repeat = 3;
    }
    else if (active_code[5] == 2) //순발력 +2
    {
        repeat = 4;
    }
    
    if (active_code[6] == 1) // 칸 +1
    {
        inventory_capacity = 20;
    }
    else if(active_code[6] == 2) //칸 +2
    {
        inventory_capacity = 30;
    }

    if (active_code[7] == 1) // 무게 +1
    {
        inventory_w_capacity = 9000;
    }
    if (active_code[7] == 2) // 무게 +2
    {
        inventory_w_capacity = 20000;
    }
}

void findskill(int code) //해당 경로까지의 스킬 찍기
{
    int min;
    int path[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //찾은 정점이 지나온 길 기억
    if (code == 0) //상점으로 나가기
    {
        system("cls");
        setskill();
        scene = 2;
    }
    else if (code == 1) //입력이 내구도일 경우@
    {
        if (active_code[0] < 2) //스킬이 끝까지 찍혔는지 확인. 아직 덜 찍혔다면 거리가 가장 짧은 스킬 찾기. 이미 찍은 스킬 지목 주의@
        {
            min = 20; //거리가 가장 작은 정점 초기화. 코드에 따라 다르게. @
            for (int i = 0; i < MAX_SKILL; i++) //skillcode를 순회하면서 스킬코드가 맞는 정점 찾기 
            {
                if ((skillcode[i] == 1 && D[i] < D[min]) && active_t[i] == 0) //스킬코드가 맞으면서 거리가 더 짧으면서 활성화 되어있지 않다면 @
                {
                    min = i;
                }
            }
            if (money - D[min] * 10000 > 0) //만약 해당 정점의 거리까지의 돈이 충분하다면
            {
                //pre 배열에서 min 정점까지의 길 활성화
                int p = 0; // 활성화 시켜야할 정점 갯수
                for (int i = min; i != 0; i = pre[i]) //min 정점으로 가는 길 확인.
                {
                    if (active_t[i] == 0) //해당 정점이 활성화 되어있는지 확인
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
                    active_t[path[i]] = 1; // 정점들 활성화.

                    active_code[skillcode[path[i]] - 1]++; //코드 별 활성화 수 증가.
                }
                money -= D[min] * 10000;
            }

        }
        else //스킬이 끝까지 찍혔다면 스킬을 다시 선택하세요
        {

        }
    }
    else if (code == 2) //입력이 추일 경우 @ 
    {
        if (active_code[1] < 2) //스킬이 끝까지 찍혔는지 확인. 아직 덜 찍혔다면 거리가 가장 짧은 스킬 찾기. 이미 찍은 스킬 지목 주의@
        {
            min = 20; //거리가 가장 작은 정점 초기화. 코드에 따라 다르게. @
            for (int i = 0; i < MAX_SKILL; i++) //skillcode를 순회하면서 스킬코드가 맞는 정점 찾기 
            {
                if ((skillcode[i] == 2 && D[i] < D[min]) && active_t[i] == 0) //스킬코드가 맞으면서 거리가 더 짧으면서 활성화 되어있지 않다면 @
                {
                    min = i;
                }
            }

            if (money - D[min] * 10000 > 0) //만약 해당 정점의 거리까지의 돈이 충분하다면
            {
                //pre 배열에서 min 정점까지의 길 활성화
                int p = 0; // 활성화 시켜야할 정점 갯수
                for (int i = min; i != 0; i = pre[i]) //min 정점으로 가는 길 확인.
                {
                    if (active_t[i] == 0) //해당 정점이 활성화 되어있는지 확인
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
                    active_t[path[i]] = 1; // 정점들 활성화.

                    active_code[skillcode[path[i]] - 1]++; //코드 별 활성화 수 증가.
                }
                money -= D[min] * 10000;
            }

        }
        else //스킬이 끝까지 찍혔다면 스킬을 다시 선택하세요
        {

        }
    }
    else if (code == 3) //입력이 미끼일 경우
    {
        if (active_code[2] < 3) //스킬이 끝까지 찍혔는지 확인. 아직 덜 찍혔다면 거리가 가장 짧은 스킬 찾기. 이미 찍은 스킬 지목 주의@
        {
            min = 20; //거리가 가장 작은 정점 초기화. 코드에 따라 다르게. @
            for (int i = 0; i < MAX_SKILL; i++) //skillcode를 순회하면서 스킬코드가 맞는 정점 찾기 
            {
                if ((skillcode[i] == 3 && D[i] < D[min]) && active_t[i] == 0) //스킬코드가 맞으면서 거리가 더 짧으면서 활성화 되어있지 않다면 @
                {
                    min = i;
                }
            }

            if (money - D[min] * 10000 > 0) //만약 해당 정점의 거리까지의 돈이 충분하다면
            {
                //pre 배열에서 min 정점까지의 길 활성화
                int p = 0; // 활성화 시켜야할 정점 갯수
                for (int i = min; i != 0; i = pre[i]) //min 정점으로 가는 길 확인.
                {
                    if (active_t[i] == 0) //해당 정점이 활성화 되어있는지 확인
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
                    active_t[path[i]] = 1; // 정점들 활성화.

                    active_code[skillcode[path[i]] - 1]++; //코드 별 활성화 수 증가.
                }
                money -= D[min] * 10000;
            }

        }
        else //스킬이 끝까지 찍혔다면 스킬을 다시 선택하세요
        {

        }
    }
    else if (code == 4) //입력이 근력일 경우
    {
        if (active_code[3] < 3) //스킬이 끝까지 찍혔는지 확인. 아직 덜 찍혔다면 거리가 가장 짧은 스킬 찾기. 이미 찍은 스킬 지목 주의 @
        {
            min = 20; //거리가 가장 작은 정점 초기화. 코드에 따라 다르게. @
            for (int i = 0; i < MAX_SKILL; i++) //skillcode를 순회하면서 스킬코드가 맞는 정점 찾기 
            {
                if ((skillcode[i] == 4 && D[i] < D[min]) && active_t[i] == 0) //스킬코드가 맞으면서 거리가 더 짧으면서 활성화 되어있지 않다면 @
                {
                    min = i;
                }
            }

            if (money - D[min] * 10000 > 0) //만약 해당 정점의 거리까지의 돈이 충분하다면
            {
                //pre 배열에서 min 정점까지의 길 활성화
                int p = 0; // 활성화 시켜야할 정점 갯수
                for (int i = min; i != 0; i = pre[i]) //min 정점으로 가는 길 확인.
                {
                    if (active_t[i] == 0) //해당 정점이 활성화 되어있는지 확인
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
                    active_t[path[i]] = 1; // 정점들 활성화.

                    active_code[skillcode[path[i]] - 1]++; //코드 별 활성화 수 증가.
                }
                money -= D[min] * 10000;
            }

        }
        else //스킬이 끝까지 찍혔다면 스킬을 다시 선택하세요
        {

        }
    }
    else if (code == 5) //입력이 눈썰미일 경우 @
    {
        if (active_code[4] < 2) //스킬이 끝까지 찍혔는지 확인. 아직 덜 찍혔다면 거리가 가장 짧은 스킬 찾기. 이미 찍은 스킬 지목 주의@
        {
            min = 20; //거리가 가장 작은 정점 초기화. 코드에 따라 다르게. @
            for (int i = 0; i < MAX_SKILL; i++) //skillcode를 순회하면서 스킬코드가 맞는 정점 찾기 
            {
                if ((skillcode[i] == 5 && D[i] < D[min]) && active_t[i] == 0) //스킬코드가 맞으면서 거리가 더 짧으면서 활성화 되어있지 않다면 @
                {
                    min = i;
                }
            }

            if (money - D[min] * 10000 > 0) //만약 해당 정점의 거리까지의 돈이 충분하다면
            {
                //pre 배열에서 min 정점까지의 길 활성화
                int p = 0; // 활성화 시켜야할 정점 갯수
                for (int i = min; i != 0; i = pre[i]) //min 정점으로 가는 길 확인.
                {
                    if (active_t[i] == 0) //해당 정점이 활성화 되어있는지 확인
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
                    active_t[path[i]] = 1; // 정점들 활성화.

                    active_code[skillcode[path[i]] - 1]++; //코드 별 활성화 수 증가.
                }
                money -= D[min] * 10000;
            }

        }
        else //스킬이 끝까지 찍혔다면 스킬을 다시 선택하세요
        {

        }
    }
    else if (code == 6) //입력이 순발력일 경우 @
    {
        if (active_code[5] < 2) //스킬이 끝까지 찍혔는지 확인. 아직 덜 찍혔다면 거리가 가장 짧은 스킬 찾기. 이미 찍은 스킬 지목 주의@
        {
            min = 20; //거리가 가장 작은 정점 초기화. 코드에 따라 다르게. @
            for (int i = 0; i < MAX_SKILL; i++) //skillcode를 순회하면서 스킬코드가 맞는 정점 찾기 
            {
                if ((skillcode[i] == 6 && D[i] < D[min]) && active_t[i] == 0) //스킬코드가 맞으면서 거리가 더 짧으면서 활성화 되어있지 않다면 @
                {
                    min = i;
                }
            }

            if (money - D[min] * 10000 > 0) //만약 해당 정점의 거리까지의 돈이 충분하다면
            {
                //pre 배열에서 min 정점까지의 길 활성화
                int p = 0; // 활성화 시켜야할 정점 갯수
                for (int i = min; i != 0; i = pre[i]) //min 정점으로 가는 길 확인.
                {
                    if (active_t[i] == 0) //해당 정점이 활성화 되어있는지 확인
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
                    active_t[path[i]] = 1; // 정점들 활성화.

                    active_code[skillcode[path[i]] - 1]++; //코드 별 활성화 수 증가.
                }
                money -= D[min] * 10000;
            }

        }
        else //스킬이 끝까지 찍혔다면 스킬을 다시 선택하세요
        {

        }
    }
    else if (code == 7) //입력이 칸일 경우 @
    {
        if (active_code[6] < 2) //스킬이 끝까지 찍혔는지 확인. 아직 덜 찍혔다면 거리가 가장 짧은 스킬 찾기. 이미 찍은 스킬 지목 주의@
        {
            min = 20; //거리가 가장 작은 정점 초기화. 코드에 따라 다르게. @
            for (int i = 0; i < MAX_SKILL; i++) //skillcode를 순회하면서 스킬코드가 맞는 정점 찾기 
            {
                if ((skillcode[i] == 7 && D[i] < D[min]) && active_t[i] == 0) //스킬코드가 맞으면서 거리가 더 짧으면서 활성화 되어있지 않다면 @
                {
                    min = i;
                }
            }

            if (money - D[min] * 10000 > 0) //만약 해당 정점의 거리까지의 돈이 충분하다면
            {
                //pre 배열에서 min 정점까지의 길 활성화
                int p = 0; // 활성화 시켜야할 정점 갯수
                for (int i = min; i != 0; i = pre[i]) //min 정점으로 가는 길 확인.
                {
                    if (active_t[i] == 0) //해당 정점이 활성화 되어있는지 확인
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
                    active_t[path[i]] = 1; // 정점들 활성화.

                    active_code[skillcode[path[i]] - 1]++; //코드 별 활성화 수 증가.
                }
                money -= D[min] * 10000;
            }

        }
        else //스킬이 끝까지 찍혔다면 스킬을 다시 선택하세요
        {

        }
    }
    else if (code == 8) //입력이 무게일 경우 @
    {
        if (active_code[7] < 2) //스킬이 끝까지 찍혔는지 확인. 아직 덜 찍혔다면 거리가 가장 짧은 스킬 찾기. 이미 찍은 스킬 지목 주의@
        {
            min = 20; //거리가 가장 작은 정점 초기화. 코드에 따라 다르게. @
            for (int i = 0; i < MAX_SKILL; i++) //skillcode를 순회하면서 스킬코드가 맞는 정점 찾기 
            {
                if ((skillcode[i] == 8 && D[i] < D[min]) && active_t[i] == 0) //스킬코드가 맞으면서 거리가 더 짧으면서 활성화 되어있지 않다면 @
                {
                    min = i;
                }
            }

            if (money - D[min] * 10000 > 0) //만약 해당 정점의 거리까지의 돈이 충분하다면
            {
                //pre 배열에서 min 정점까지의 길 활성화
                int p = 0; // 활성화 시켜야할 정점 갯수
                for (int i = min; i != 0; i = pre[i]) //min 정점으로 가는 길 확인.
                {
                    if (active_t[i] == 0) //해당 정점이 활성화 되어있는지 확인
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
                    active_t[path[i]] = 1; // 정점들 활성화.

                    active_code[skillcode[path[i]] - 1]++; //코드 별 활성화 수 증가.
                }
                money -= D[min] * 10000;
            }

        }
        else //스킬이 끝까지 찍혔다면 스킬을 다시 선택하세요
        {

        }
    }
    else if (code == 9)
    {
        if (active_code[8] < 1) //스킬이 끝까지 찍혔는지 확인. 아직 덜 찍혔다면 거리가 가장 짧은 스킬 찾기. 이미 찍은 스킬 지목 주의@
        {
            min = 20; //거리가 가장 작은 정점 초기화. 코드에 따라 다르게. @
            for (int i = 0; i < MAX_SKILL; i++) //skillcode를 순회하면서 스킬코드가 맞는 정점 찾기 
            {
                if ((skillcode[i] == 9 && D[i] < D[min]) && active_t[i] == 0) //스킬코드가 맞으면서 거리가 더 짧으면서 활성화 되어있지 않다면 @
                {
                    min = i;
                }
            }

            if (money - D[min] * 10000 > 0) //만약 해당 정점의 거리까지의 돈이 충분하다면
            {
                //pre 배열에서 min 정점까지의 길 활성화
                int p = 0; // 활성화 시켜야할 정점 갯수
                for (int i = min; i != 0; i = pre[i]) //min 정정으로 가는 길 확인.
                {
                    if (active_t[i] == 0) //해당 정점이 활성화 되어있는지 확인
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
                    active_t[path[i]] = 1; // 정점들 활성화.

                    active_code[skillcode[path[i]] - 1]++; //코드 별 활성화 수 증가.
                }
                money -= 2000000;
                wincondition++;
                if (wincondition == 3)
                {
                    scene = 5;
                }
            }
        }
        else //스킬이 끝까지 찍혔다면 스킬을 다시 선택하세요
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
    if (key == 32) //엔터를 입력할 경우 스킬찍기
    {
        findskill(skillinput());
        return 1;
    }
    if (key == 27) //ESC키를 누를 경우 상점 창으로 넘어감.
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

    //스킬트리 배열 초기화
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

    initskillpos(); //스킬 정점 위치 초기화


    for (int i = 0; i < MAX_SKILL; i++) //활성화된 스킬 목록을 초기화
    {
        active_t[i] = 0;
    }

    active_t[0] = 1; //시작 지점은 활성화.

    while (1)
    {
        if (scene == 0)
        {
            intro();
        }
        else if (scene == 1) // 메인 씬일 때.
        {
            for (int i = 0; i < 35; i++) //바다 배열 초기화
            {
                for (int j = 0; j < 150; j++)
                {
                    seaarray[i][j] = ' ';
                }
            }
            currenttime = clock();
            mainstarttime = clock();
            player player;
            initplayer(&player); //플레이어 정보 초기화

            fish* fishhead = NULL; //물고기 헤드 생성. 연결리스트로 관리.
            fishhead = initfish(fishhead); //물고기 연결리스트 초기화

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
                
                if ((clock() - currenttime > 100) && scene == 1) //모든 상황을 0.1초마다 재정의
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
        else if (scene == 2) //상점 창
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
        else if (scene == 3) //스킬 창
        {
            shortest_path(&t, 0);
            findskill(skillinput());
        }
        else if (scene == 4) //인벤토리 창
        {
            system("cls");
            gotoxy();
            printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
            printf("\n\n");
            int fishcount = 0;
            printf("    인벤토리 : \n\n");
            for (int i = 0; i < inventory_capacity; i++)
            {
                if (inventory[i].code == 1) {
                    fishcount++;
                }
            }
            printf("        -<    멸치   : %2d마리\n", fishcount);

            fishcount = 0;
            for (int i = 0; i < inventory_capacity; i++)
            {
                if (inventory[i].code == 2) {
                    fishcount++;
                }
            }
            printf("        <@<   우럭   : %2d마리\n", fishcount);

            fishcount = 0;
            for (int i = 0; i < inventory_capacity; i++)
            {
                if (inventory[i].code == 3) {
                    fishcount++;
                }
            }
            printf("        <@-   가자미 : %2d마리\n", fishcount);

            fishcount = 0;
            for (int i = 0; i < inventory_capacity; i++)
            {
                if (inventory[i].code == 4) {
                    fishcount++;
                }
            }
            printf("        <=<   고등어 : %2d마리\n", fishcount);

            fishcount = 0;
            for (int i = 0; i < inventory_capacity; i++)
            {
                if (inventory[i].code == 5) {
                    fishcount++;
                }
            }
            printf("        <@@=  광어   : %2d마리\n", fishcount);

            fishcount = 0;
            for (int i = 0; i < inventory_capacity; i++)
            {
                if (inventory[i].code == 6) {
                    fishcount++;
                }
            }
            printf("        <==-  장어   : %2d마리\n", fishcount);

            fishcount = 0;
            for (int i = 0; i < inventory_capacity; i++)
            {
                if (inventory[i].code == 6) {
                    fishcount++;
                }
            }
            printf("        <@+>< 참치   : %2d마리\n\n\n", fishcount);

            printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n\n\n");
            printf("    지금까지 잡은 물고기 수 : \n\n");
            printf("        -<    멸치   : %2d마리\n", fishcode[0]);
            printf("        <@<   우럭   : %2d마리\n", fishcode[1]);
            printf("        <@-   가자미 : %2d마리\n", fishcode[2]);
            printf("        <=<   고등어 : %2d마리\n", fishcode[3]);
            printf("        <@@=  광어   : %2d마리\n", fishcode[4]);
            printf("        <==-  장어   : %2d마리\n", fishcode[5]);
            printf("        <@+>< 참치   : %2d마리\n\n\n", fishcode[6]);

            printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n\n\n");
            printf("        가방 무게 제한 : %d\n\n", inventory_w_capacity);
            printf("        가방 크기 제한 : %d\n\n", inventory_capacity);
            printf("        낚시 가능한 깊이 : %d\n\n", pendulum);
            printf("        미끼 범위 : %d\n\n", range);
            printf("        미끼 개수 : %d\n\n", baitcount);
            printf("        내구도 : %d\n\n", durability);
            printf("        가격 보너스 : +%d%%\n\n", sense);
            printf("        연타 감소 : -%d%%\n\n", repeat * 20);
            char anykey[10];
            while (!_kbhit())
            {

            }
            system("cls");
            scene = 1;
        }
        else if (scene == 5) //게임 클리어
        {
            system("cls");
            good_end();
            return 0;
        }
        else if (scene == 6) //게임 패배
        {
            system("cls");
            bad_end();
            return 0;
        }
    }
    
}