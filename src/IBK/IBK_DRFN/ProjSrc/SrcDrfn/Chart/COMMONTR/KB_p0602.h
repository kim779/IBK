/*************************************************************************************/
/*  1. 프로그램ID : KB_p0602                                                         */
/*  2. 프로그램명 : 차트 조회(주식)                                                  */
/*  3. 서비스명   : KB_p0602                                                         */
/*  4. 사용테이블 :                                                                  */
/*  5. 작성자     : drfn                                                             */
/*  6. 입력항목   :                                                                  */
/*  7. 출력항목   :                                                                  */
/*************************************************************************************/
#ifndef __KB_TRAN_KB_p0602_H__
#define __KB_TRAN_KB_p0602_H__

/*************************************************************************************/
/* include file                                                                      */
/*************************************************************************************/

/*************************************************************************************/
/* define constant                                                                   */
/*************************************************************************************/
//#define KB_TRAN                       "KB_p0602"
//#define LLONG                         long long


/*************************************************************************************/
/* Input structure                                                                   */
/*************************************************************************************/

#ifndef ChartKeySize
#define		ChartKeySize		28//KHD : YYYYMMDDHHMMSS : 최초조회요청시 : "99999999999999" 데이터 없으면 "99999999999999"로 받는다.
#endif


/* InRec1:                                                                           */
typedef struct
{
    char    shcode[15];                           /* 종목코드(15)                    */
    char    date[8];                              /* 검색시작일(8)                   */
    char    num[4];                               /* 조회건수(4)                     */
    char    unit[3];                              /* 조회단위(3)                     */
    char    button[1];                            /* 조회구분(1)                     */
    char    modGb[1];                             /* 수정주가(1)                     */
    char    nflag[1];                             /* 조회모드(1)                     */
//	char    nkey[21];                             /* 검색키(21)                      */
	char    nkey[ChartKeySize];			  /* 검색키(ChartKeySize)        */
    char    nDataGubun[1];                        /* 가격구분(1) (0:가격, 1:비율,2:달러) */
    char    ImgRgb[1];                            /* 봉구분(1)                       */
    char    Irecordgb[1];                         /* 복기구분값(1)(1)                */
    char    nDayBefore[2];                        /* 복기시작n일전(2)                */
    char    Itime[6];                             /* 복기시간(hhmmss)(6)             */
	char	nowData[1];							  /*  [당일조회]     */
	char	usRate[10];							  /* US Dollar 환율     */
} KB_p0602_InRec1;


/*************************************************************************************/
/* Output structure                                                                  */
/*************************************************************************************/

/* OutRec1:                                                                          */
// 사용하지 않는 Field 주석처리
typedef struct
{
    char	name[30];                           /* 종목명(20)                      */
	char	jang[10];                           /* 장구분(10)                      */
    char	price[10];                          /* 현재가(10)                      */
    char	sign[1];                            /* 등락부호(1)                     */
    char	change[10];                         /* 대비(10)                        */
    char	chrate[6];                          /* 대비율(6)                       */
    char	volume[10];                         /* 거래량(10)                      */
    char	offer[10];                          /* 매도호가(10)                    */
    char	bid[10];                            /* 매수호가(10)                    */
    char	preprice[10];                       /* 기준가(10)                      */
    //char	nkey[21];                           /* 이전키(21)                      */
	char	nkey[ChartKeySize];
    char	cntsz[6];                           /* 차트사이즈(6)                   */
    char	fcnt[5];                            /* 차트카운트(5)                   */
    char	bojomsg[500];                       /* 보조메시지(400)                 */
} KB_p0602_OutRec1;

typedef struct
{
    char    name[30];                             /* 종목명(20)                      */
//    char    jang[10];                             /* 장구분(10)                      */
    char    price[10];                            /* 현재가(10)                      */
    char    sign[1];                              /* 등락부호(1)                     */
    char    change[10];                           /* 대비(10)                        */
    char    chrate[6];                            /* 대비율(6)                       */
    char    volume[10];                           /* 거래량(10)                      */
//    char    offer[10];                            /* 매도호가(10)                    */
//    char    bid[10];                              /* 매수호가(10)                    */
    char    preprice[10];                         /* 기준가(10)                      */
//	char	openinterest[18];					// 미결제약정 //KHD
    //char    nkey[21];                             /* 이전키(21)                      */
	char	nkey[ChartKeySize];
//    char    cntsz[6];                             /* 차트사이즈(6)                   */
    char    fcnt[5];                              /* 차트카운트(5)                   */
    char    bojomsg[500];                         /* 보조메시지(300)                 */
} KB_p0602_OutRec1_EX;

typedef struct
{
    char	name[30];                         /* 종목명(20)                      */
    char	price[10];                         /* 현재가(10)                      */
    char	sign[1];                         /* 등락부호(1)                     */
    char	change[10];                         /* 대비(10)                        */
    char	chrate[6];                         /* 대비율(6)                       */
    char	preprice[10];                         /* 기준가(10)                      */
    //char	nkey[21];                         /* 이전키(21)                      */
	char	nkey[ChartKeySize];
    char	fcnt[5];                         /* 차트카운트(5)                   */
    char	bojomsg[500];                         /* 보조메시지(400)                 */
} KB_p0602_OutRec1_COMP;

/* OutRec2:                                                                          */
// 사용하지 않는 Field 주석처리
//char KB_p0602_OutRec2_count[4];
typedef struct
{
    char    date[8];                              /* 날짜(8)                         */
    char    open[10];                             /* 시가(10)                        */
    char    high[10];                             /* 고가(10)                        */
    char    low[10];                              /* 저가(10)                        */
    char    close[10];                            /* 종가(10)                        */
    char    volume[10];                           /* 거래량(10)                      */
	//[A00000408]거래대금 12 -> 18.
    //char    value[12];                          /* 거래대금(12)                    */
	char    value[18];                            /* 거래대금(18)                    */
    char    rights[1];                            /* 권리락(1)                       */
    char    sign[1];                              /* 전일대비부호(1)                 */
} KB_p0602_OutRec2;

typedef struct
{
    char    date[8];                              /* 날짜(8)                         */
    char    open[10];                             /* 시가(10)                        */
    char    high[10];                             /* 고가(10)                        */
    char    low[10];                              /* 저가(10)                        */
    char    close[10];                            /* 종가(10)                        */
} KB_p0602_OutRec2_COMP;

/* Chart Data:																		 */
typedef struct _KB_p0602_CHART
{
	char    fcnt[5];         			/* 차트카운트(5)                   */
	char    bojomsg[500];				/* 보조메시지(300)                 */
	//KB_p0602_OutRec2  chart[50000];
	KB_p0602_OutRec2  chart[1];			// 동적크기임.
} KB_p0602_CHART;

typedef struct _KB_p0602_CHART_COMP
{
	char    fcnt[5];         			/* 차트카운트(5)                   */
	char    bojomsg[500];				/* 보조메시지(300)                 */
	//KB_p0602_OutRec2_COMP  chart[50000];
	KB_p0602_OutRec2_COMP  chart[1];
} KB_p0602_CHART_COMP;

/*************************************************************************************/

#endif

