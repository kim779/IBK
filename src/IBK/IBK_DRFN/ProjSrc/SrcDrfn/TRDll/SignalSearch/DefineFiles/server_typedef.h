#ifndef SERVER_TYPEDEF
#define SERVER_TYPEDEF

/************************************************************/
/*																													*/
/*	  Draw Condition Server =>  STRUCT/DEFINE/TYPEDEF ����	*/
/*																													*/
/*					2008. 1.  			Doori														*/
/*					�ۼ��� : �쵿��																	*/
/************************************************************/

//#define TRNO_DRAW_RESULT		"50011"
//#define TRNO_UNIVERS				"07608"
//#define TRNO_MSTCODE        "50008"

#define	RESULT_MAX_OFFSET		1
#define RESULT_MAX				4000	//3000 -> 4000

#define QUERY_STRJONGMOK_MIN		_T("HKST03010200")

#define LEN_CODE					7
#define LEN_NAME					20

#define	RESULT_FIELD_MAX			30		/* ����ʵ� �ִ� ���� 	*/
#define RESULT_FIELD_MAX_EUGENE     80

#define CNT_DRAW_VAL				120
#define CNT_DRAW_VAL_EUGENE			480

#define DEFAULTCNTATONCE (400)
#define GRDMX			(3000)
#define CHTMX			(5200)
#define CHTMXREQUEST	(5000)
#define BOJO_MSG_LENGTH	(400)


// typedef struct tagMSTCode
// {
//   char    sMarket[1];
//   char    sCode[7];
//   char    sName[20];
//   char    sSetPos[4];
// } MSTCode;

typedef struct tagMSTCode
{
	char    sMarket[1];
	char    sCode[7];
	char    sName[20];
	char    sSetPos[4];
	char    sUsjg[1];               /* �켱��   (0:�ش����,1:�ش�) */
	char    sUnder[1];              /* ��������                     */
	char    sStop[1];               /* �ŷ���������                 */
	char    sDishonest[1];          /* �Ҽ��ǰ�������               */
	char    sConfidencelimit[1];    /* �ſ���������?               */
	char    sJrmm[1];          	    /* �����Ÿ�����                 */
	char    sDrat[3];               /* ���űݺ���                   */
	char    sMrktalrm[1];           /* ����溸
										1:��������, 2:���ڰ��
										3:��������, 4:�������迹��*/
	char	sMonth[2];				/* ���� */
	char	sETF[1];				/* ETF							*/
} MSTCode;


#define COND_MST_VER	1



typedef struct tagDRAW_DATA
{
    long        lAccuVal;               // �ֱ� ����ġ ���뿩��
                                        //  : 1~ 10, ������� 0����.. (0.005)
    long        lDraw_Cnt;              // �׸��� �Ⱓ����(20~120)
    long        lErrRate;               // ������ = 10
    long        lGapRate;               // ���� ���� = 40
    long        lDraw_Value[CNT_DRAW_VAL];       // �׸��� ��ǥ��(0~100)
                                        //  : �׸��� ������� 999�� �Է�
} DRAW_DATA;

typedef struct tagDRAW_IN
{
    long nTrIndex;
    
    long nS_Time;           // ���ð�
														/* 0:�ϰ�, 1:�ְ�, 2:����, 3:1��, 4:3��	*/
														/* 5:5��,  6:10��, 7:15��, 8:30��, 9:60��*/
                            //  : ��/��/�� ��.. ���ǰ˻��� ����
    long lTarget;           // ������� => 4 ����
                            //   : ��,��,��,��,�ŷ���(1,2,3,4,5) 
    long lMoveAvg;          // ����Ⱓ => 1����
                            //   : ���� ������� 1 �Է�
    long lS_Pos;            // �˻� ������ġ
    long lS_Range;          // �˻� ����
    long lSimilar;          // ���絵
    char cBoxFlag;					// Ⱦ�� üũ ���� ( > 5 )
														//  : Ⱦ�� üũ�ÿ� 1�� üũ

    long nFieldEditerCnt;								// �ʵ����� ����   [Fix]
    long nFieldList[RESULT_FIELD_MAX];	// �ʵ����� ��ȣ����Ʈ [Just Fix]
	                       
	char		sTargetBit[RESULT_MAX];  /* �˻� ��� ����		*/
    DRAW_DATA stDrawData;
} DRAW_IN;

#define SZ_DRAW_IN  sizeof(DRAW_IN)

typedef struct tagDRAW_OUT_HEAD
{
    long nTrIndex;
    
    long  lTotalCnt;			/* �˻��� ���� ���� ��      */
    long  lOutFieldCnt;				/* Out Field Count          */
    long  lOutListPacketSize;	/* ��� List ������(������) */
    long  lFindTime;					/* �˻��ð�									*/
} DRAW_OUT_HEAD;


typedef struct tagDRAW_OUT_LIST
{
	char        sJmcode     [LEN_CODE];
 // char        Filler1     [ 1];

  char        sHname      [20];
  char        sSign       [ 1];
  char        sMarket     [ 1];
//  char        Filler2     [ 2];

  long        iTarget;    /* ���ֿ���     */
  char        sDateTime_Start [14];/* �˻������ ��������¥ YYYYMMDDhhmmss */
  char        sDateTime_End   [14];/* �˻������ ���۳�¥  */

  double      dFieldData[RESULT_FIELD_MAX];
} DRAW_OUT_LIST;
#define SZ_DRAW_OUT_LIST  sizeof(DRAW_OUT_LIST)


typedef struct _S03010_I
{
//����	char    shcode		[ 7];  /* �����ڵ�        */
	char    shcode		[ 15];  /* �����ڵ�        */
	char	date		[ 8];  /* �˻� ������       */
	char	num			[ 4];  /* �˻��� ������ ����     */
	char	unit		[ 3];  /* ƽ/��/�� ��ȸ���ݴ���    *///<========2005.08.11
	char    button		[ 1];  /* ƽ(0)/��(1)/��(2)/��(3)/��(4)/��(5) */
	char    modGb		[ 1];  /* �����ְ� ���� 1:�����ְ��ݿ�   */ 
	char	nflag		[ 1];  /* ����(1) / ��ȸ(0) ������    */
	char	nkey		[21];  /* ���� / ���� Fetch Key    */
	char	nDataGubun	[ 1];  /* '0': ����, '1':����     */
	char    ImgRgb		[ 1];  /* '0':����� '1':�Ǻ�     */
	char    Irecordgb	[ 1];  /* ���� ���а�(1)      *///<========2005.08.11
	char    nDayBefore	[ 2];  /* ���� ���� n����       *///<========2005.10.14
	char    Itime		[ 6];  /* ����ð� (hhmmss)     *///<========2005.08.11  
	char        nowData[1]; /* ������ȸ(1:������ȸ) */
	/// don't sent to server..
 	char chNull;
	

} S03010_I;
#define S03010_I_SIZE	sizeof(S03010_I)
//--------------------------------[OUTPUT�ݺ� ]---------------------------------------//

// Chart Equity History Info Structure(In Server)
typedef struct _S_03010_S
{
	char    date		[ 8];   /* ��¥       */
	char    open		[10];   /* �ð�       */
	char    high		[10];   /* ����       */
	char    low			[10];   /* ����       */
	char    close		[10];   /* ����      */
	char    volume		[10];   /* �ŷ���     */
	char    value		[12];   /* �ŷ����    20030205 �������߰�     */
	char	rights		[ 1];   /* ����, �Ǹ���.. */
	char	rightrate	[ 6]; 
} S03010_S;


// Chart Equity History Info Structure (In Client)
typedef struct _S03010_CHART
{
	char		tmp		[ 5];				/* Chart Count      */
	char		bojomsg	[BOJO_MSG_LENGTH];  /* Chart Bojo Data  */
	S03010_S	chart	[CHTMX];
} S03010_CHART;

//--------------------------------[OUTPUT     ]-----------------------------------//
// Chart Equity  Info Structure (In Server's Output )
typedef struct _S03010_O 
{
	char	name		[20];   /* �����		*/
//	char	jang		[10];   /* �屸�� : 'KOSPI', 'KOSDAQ', 'KOSPI200' */	//--->
	char	price		[10];   /* ���簡     */
	char	sign		[ 1];   /* �����ȣ   */
	char	change		[10];   /* ���       */
	char	chrate		[ 6];   /* �����     */
//	char	volume		[10];   /* �ŷ���     */		//--->
//	char	offer		[10];   /* �ŵ�ȣ��   */		//--->
//	char    bid			[10];   /* �ż�ȣ��   */		//--->
	char    preprice	[10];   /* ���ذ�     */
	char    nkey		[21];   /* ����Ű           */
//	char    Cchtsize	[ 6];   /* Chart Size       */	//--->
	//------------- PosForChart
	char    tmp			[ 5];   /* Chart Count      */
	char    bojomsg		[BOJO_MSG_LENGTH];     /* Chart Bojo Data  90->256���� �ٲ� 05.05.06*/
	S03010_S  chart		[CHTMX];
} S03010_O;

typedef struct
{
	char    name[20];                             /* �����(20)                      */
	char    price[10];                            /* ���簡(10)                      */
	char    sign[1];                              /* �����ȣ(1)                     */
	char    change[10];                           /* ���(10)                        */
	char    chrate[6];                            /* �����(6)                       */
	char    volume[10];                           /* �ŷ���(10)                      */
	char    preprice[10];                         /* ���ذ�(10)                      */
	char    nkey[14];                             /* ����Ű(14)                      */
	char    fcnt[5];                              /* ��Ʈī��Ʈ(5)                   */
	char    bojomsg[400];                         /* �����޽���(400)                 */
	S03010_S  chart[CHTMX];
} EU_p0602_OutRec1_EX;

typedef struct stD1010
{
	char	name		[20];   /* �����		*/
	char	jang		[10];   /* �屸�� : 'KOSPI', 'KOSDAQ', 'KOSPI200' */
	char	price		[10];   /* ���簡     */
	char	sign		[ 1];   /* �����ȣ   */
	char	change		[10];   /* ���       */
	char	chrate		[ 6];   /* �����     */
	char	volume		[10];   /* �ŷ���     */
	char	offer		[10];   /* �ŵ�ȣ��   */
	char    bid			[10];   /* �ż�ȣ��   */
	char    preprice	[10];   /* ���ذ�     */
	char    nkey		[21];   /* ����Ű           */
	char    Cchtsize	[ 6];   /* Chart Size       */
	//------------- PosForChart
	char    tmp			[ 5];   /* Chart Count      */
	char    bojomsg		[BOJO_MSG_LENGTH];     /* Chart Bojo Data  90->256���� �ٲ� 05.05.06*/
	S03010_S  chart		[CHTMX];
}ST_D1010;

#define SIZE_D1010_HEADER	529		// hidden

typedef struct    
{
	char	shcode		[15];	/* �����ڵ�			*/
	char	date		[8];	/* �˻�������		*/
	char	num			[4];	/* ��ȸ�Ǽ�			*/
	char	unit		[3];	/* ��ȸ����(ƽ/��/��)								*/	
	char	button		[1];	/* ��ȸ����(ƽ(0)/��(1)/��(2)/��(3)/��(4)/��(5))	*/
	char	modGb		[1];	/* �����ְ�(1:�����ְ��ݿ�)							*/
	char	nflag		[1];	/* ��ȸ���(����(1) / ��ȸ(0) ������)				*/
	char	nkey		[21];	/* �˻�Ű(���� / ���� Fetch Key)					*/
	char	nDataGubun	[1];	/* ���ݱ���('0': ����, '1':����)					*/
	char	ImgRgb		[1];	/* ������('0':����� '1':�Ǻ�)						*/
	char	Irecordgb	[1];	/* ���ⱸ�а�(1)	*/
	char	nDayBefore	[2];	/* �������n����	*/
	char	Itime		[6];	/* ����ð�(hhmmss) */
	char        nowData[1]; /* ������ȸ(1:������ȸ) */
	// don't sent to server..
	char	chNull;


}p0602InBlock;

typedef struct
{
	char	name		[20];	/* �����		0	*/
	char	jang		[10];	/* �屸��		1	*/
	char	price		[10];	/* ���簡		2	*/
	char	sign		[1];	/* �����ȣ		3	*/
	char	change		[10];	/* ���			4	*/
	char	chrate		[6];	/* �����		5	*/
	char	volume		[10];	/* �ŷ���		6	*/
	char	offer		[10];	/* �ŵ�ȣ��		7	*/
	char	bid			[10];	/* �ż�ȣ��		8	*/
	char	preprice	[10];	/* ���ذ�		9	*/
	char	nkey		[21];	/* ����Ű		10	*/
	char	cntsz		[6];	/* ��Ʈ������	11	*/
	char	fcnt		[5];	/* ��Ʈī��Ʈ	12	*/
	char	bojomsg		[400];	/* �����޽���	13	*/
}p0602OutBlock1;

typedef struct
{
	char	date		[8];	/* ��¥				*/
	char	open		[10];	/* �ð�				*/
	char	high		[10];	/* ����				*/
	char	low			[10];	/* ����				*/
	char	close		[10];	/* ����				*/
	char	volume		[10];	/* �ŷ���			*/
	char	value		[12];	/* �ŷ����			*/
	char	rights		[1];	/* �Ǹ���			*/
	char	rightrate	[ 6];
}p0602OutBlock2;


//////////////////////////////
typedef struct
{
	char		nTrIndex[4];
	char		iS_Time[4];
	char		iTarget[4];
	char		iMoveAvg[4]; 
	char		iS_Pos[4];
	char		iS_Range[4];
	char		iSimilar[4];
	char		sBoxFlag[1];
	char		FieldEditerCnt[4];
	char		FieldList[RESULT_FIELD_MAX_EUGENE];
	char		sTargetBit[RESULT_MAX];
	char		iAccuVal[4];
	char		iDraw_Cnt[4];
	char		iErrRate[4];
	char		iGapRate[4];
	char		iDraw_Value[CNT_DRAW_VAL_EUGENE];	

}p0624InBlock;
#define SZ_p0624InBlock sizeof(p0624InBlock)

typedef struct
{
	char		nTrIndex[4];
	char		lTotalJongCnt[4];
	char		lOutFieldCnt[4];
	char		lOutListPacketSize[4];
	char		lFindTime[6];
}p0624OutBlock1;
#define SZ_p0624OutBlock1	sizeof(p0624OutBlock1)

typedef struct 
{
	char		sJmcode[7];
	char		sHname[20];
	char		sSign[1];
	char		sMarket[1];
	char		iTarget[4];
	char		sDateTime_Start[14];
	char		sDateTime_End[14];
	char		dFieldData[320];
}p0624OutBlock2;
#define SZ_p0624OutBlock2	sizeof(p0624OutBlock2)
///////////////////////////////////////////////////////////


typedef struct
{
	char		giCallIndex[4];
	char		gsCode[6];
	char		gsFilterGubun[1];
}p0628InBlock;
#define SZ_p0628InBlock sizeof(p0628InBlock)

typedef struct
{
	char		giCallIndex[4];
	char		ThemeCnt[4];
}p0628OutBlock1;
#define SZ_p0628OutBlock1 sizeof(p0628OutBlock1)

typedef struct
{
	char		gsThemeCode[4];
	char		gsThemeName[36];
}p0628OutBlock2;
#define SZ_p0628OutBlock2 sizeof(p0628OutBlock2)


typedef struct
{
	char		giCallIndex[4];
	char		giThemeCode[4];
}p0630InBlock;
#define SZ_p0630InBlock sizeof(p0630InBlock)

typedef struct
{
	char		giCallIndex[4];
	char		giCnt[4];
}p0630OutBlock1;
#define SZ_p0630OutBlock1 sizeof(p0630OutBlock1)

typedef struct
{
	char		gsItemCode[6];
	char		gsMarketFlag[1];
}p0630OutBlock2;
#define SZ_p0630OutBlock2 sizeof(p0630OutBlock2)



#endif // SERVER_TYPEDEF
