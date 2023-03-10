/*************************************************************************************/
/*  1. 프로그램ID : KB_d1013                                                         */
/*  2. 프로그램명 : 차트 조회(주식선물옵션)                                          */
/*  3. 서비스명   : KB_d1013                                                         */
/*  4. 사용테이블 :                                                                  */
/*  5. 작성자     : drfn                                                             */
/*  6. 입력항목   :                                                                  */
/*  7. 출력항목   :                                                                  */
/*************************************************************************************/
#ifndef __KB_TRAN_KB_d1013_H__
#define __KB_TRAN_KB_d1013_H__

/*************************************************************************************/
/* include file                                                                      */
/*************************************************************************************/

/*************************************************************************************/
/* define constant                                                                   */
/*************************************************************************************/
//#define KB_TRAN                       "KB_d1013"
//#define LLONG                         long long

#ifndef ChartKeySize
#define		ChartKeySize		28//KHD
#endif

/*************************************************************************************/
/* Input structure                                                                   */
/*************************************************************************************/

/* InRec1:                                                                           */
typedef struct
{
    char    Scode[15];                            /* 종목코드(15)                    */
    char    Sdate[8];                             /* 검색시작일(8)                   */
    char    Smaxbong[4];                          /* 검색할데이터갯수(4)             */
    char    Sunit[3];                             /* N봉(틱분시일)(3)                */
    char    Sbtngb[1];                            /* 구분(틱분일주월)(1)             */
    char    Snextgb[1];                           /* 조회구분(다음조회)(1)           */
    char    Snextkey[ChartKeySize];               /* 검색키(21)                      */
	char    SdataType[1];						  /* 차트구분 (0:가격, 1:비율,2:달러)*/
    char    Simgrgb[1];                           /* 봉구분(허수실봉)(1)             */
    char    Srecordgb[1];                         /* 복기구분값(1)                   */
    char    Sredate[2];                           /* 복기시작n일전(2)                */
    char    Stime[6];                             /* 복기시간(hhmmss)(6)             */
	char	nowData[1];							  /* 당일조회(1)					 */
	char	SgapRev[1];							  /* 월물간 갭보정(1)				 *///(Issue No : 0006572)
}KB_d1013_InRec1;


/*************************************************************************************/
/* Output structure                                                                  */
/*************************************************************************************/

/* OutRec1:                                                                          */
// 사용하지 않는 Field 주석처리
typedef struct
{
    char    name[50];                             /* 종목명(50)                      */
    char    jang[10];                             /* 장구분(10)                      */
    char    price[10];                            /* 현재가(10)                      */
    char    sign[1];                              /* 등락부호(1)                     */
    char    change[10];                           /* 대비(10)                        */
    char    chrate[6];                            /* 대비율(6)                       */
    char    volume[10];                           /* 거래량(10)                      */
    char    offer[10];                            /* 매도호가(10)                    */
    char    bid[10];                              /* 매수호가(10)                    */
    char    preprice[10];                         /* 기준가(10)                      */
    //char    nkey[21];                             /* 이전키(21)                      */
	char    nkey[ChartKeySize];
    char    cntsz[6];                             /* 차트사이즈(6)                   */
    char    fcnt[5];                              /* 차트카운트(5)                   */
    char    bojomsg[400];                         /* 보조메시지(256)                 */
}KB_d1013_OutRec1;

typedef struct
{
    char    name[50];                             /* 종목명(50)                      */
//    char    jang[10];                             /* 장구분(10)                      */
    char    price[10];                            /* 현재가(10)                      */
    char    sign[1];                              /* 등락부호(1)                     */
    char    change[10];                           /* 대비(10)                        */
    char    chrate[6];                            /* 대비율(6)                       */
    char    volume[10];                           /* 거래량(10)                      */
//    char    offer[10];                            /* 매도호가(10)                    */
//    char    bid[10];                              /* 매수호가(10)                    */
    char    preprice[10];                         /* 기준가(10)                      */
	char	openinterest[18];					// 미결제약정 //KHD
    //char    nkey[21];                             /* 이전키(21)                      */
	char    nkey[ChartKeySize];
//    char    cntsz[6];                             /* 차트사이즈(6)                   */
    char    fcnt[5];                              /* 차트카운트(5)                   */
    char    bojomsg[400];                         /* 보조메시지(256)                 */
}KB_d1013_OutRec1_EX;

typedef struct
{
    char	name[20];                         /* 종목명(20)                      */
    char	price[10];                         /* 현재가(10)                      */
    char	sign[1];                         /* 등락부호(1)                     */
    char	change[10];                         /* 대비(10)                        */
    char	chrate[6];                         /* 대비율(6)                       */
    char	preprice[10];                         /* 기준가(10)                      */
    //char	nkey[21];                         /* 이전키(21)                      */
	char    nkey[ChartKeySize];
    char	fcnt[5];                         /* 차트카운트(5)                   */
    char	bojomsg[400];                         /* 보조메시지(400)                 */
} KB_d1013_OutRec1_COMP;

/* OutRec2:                                                                          */
// 사용하지 않는 Field 주석처리
typedef struct
{
    char    date[8];                              /* 날짜(8)                         */
    char    open[10];                             /* 시가(10)                        */
    char    high[10];                             /* 고가(10)                        */
    char    low[10];                              /* 저가(10)                        */
    char    close[10];                            /* 종가(10)                        */
    char    volume[10];                           /* 거래량(10)                      */

	//[A00000408]거래대금 12 -> 18.
    //char    value[12];                            /* 거래대금(12)                    */
	char    value[18];                            /* 거래대금(18)                    */
	char    rights[1];                            /* 권리락(1)                       */
	char    openinterest[10];					  /* 미결제약정(10)					KHD */
}KB_d1013_OutRec2;

typedef struct
{
    char    date[8];                              /* 날짜(8)                         */
    char    open[10];                             /* 시가(10)                        */
    char    high[10];                             /* 고가(10)                        */
    char    low[10];                              /* 저가(10)                        */
    char    close[10];                            /* 종가(10)                        */
}KB_d1013_OutRec2_COMP;

/* Chart Data:																		 */
typedef struct _KB_d1013_CHART
{
	char    fcnt[5];         			/* 차트카운트(5)                   */
	char    bojomsg[400];				/* 보조메시지(300)                 */
	//KB_d1013_OutRec2  chart[50000];
	KB_d1013_OutRec2  chart[1];						// 동적크기임.
} KB_d1013_CHART;

typedef struct _KB_d1013_CHART_COMP
{
	char    fcnt[5];         			/* 차트카운트(5)                   */
	char    bojomsg[400];				/* 보조메시지(300)                 */
	//KB_d1013_OutRec2  chart[50000];
	KB_d1013_OutRec2  chart[1];
} KB_d1013_CHART_COMP;
/*************************************************************************************/

#endif

