/*************************************************************************************/
/*  1. 프로그램ID : EU_p0627                                                         */
/*  2. 프로그램명 : 종목리스트 조회                                                  */
/*  3. 서비스명   : EU_p0627                                                         */
/*  4. 사용테이블 :                                                                  */
/*  5. 작성자     : drfn                                                             */
/*  6. 입력항목   :                                                                  */
/*  7. 출력항목   :                                                                  */
/*************************************************************************************/
#ifndef __EU_TRAN_EU_p0627_H__
#define __EU_TRAN_EU_p0627_H__

/*************************************************************************************/
/* include file                                                                      */
/*************************************************************************************/

/*************************************************************************************/
/* define constant                                                                   */
/*************************************************************************************/
#define EU_TRAN0627                       "EU_p0627"
#define LLONG                         long long



/*************************************************************************************/
/* Output structure                                                                  */
/*************************************************************************************/

/* OutRec1:                                                                          */
char EU_p0627_OutRec1_count[4];
typedef struct
{
    char    sMflag[1];                            /* 마켓구분(1)                     */
    char    sShcode[7];                           /* 종목코드(7)                     */
    char    sHname[20];                           /* 종목명(20)                      */
    char    sIndex[4];                            /* 인덱스(4)                       */
}EU_p0627_OutRec1;

/*************************************************************************************/

#endif

