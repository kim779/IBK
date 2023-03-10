// *****************************************************************************
// (C) COPYRIGHT Winix Information Inc. 2000
// All Rights Reserved
// Licensed Materials - Property of WINIX
//
// This program contains proprietary information of Winix Information.
// All embodying confidential information, ideas and expressions can't be
// reproceduced, or transmitted in any form or by any means, electronic, 
// mechanical, or otherwise without the written permission of Winix Information.
//
//  Components   : jmcode.h
//  Rev. History :
//  		  Ver	Date	Description
//		-------	-------	------------------------------------------------
//		 01.00	2000-07	Initial version
// *****************************************************************************
#pragma once

//
//	현물 종목코드
//

#define FENameLen	20
#define	ENameLen	40
#define HNameLen	40
#define	HCodeLen	12
#define	HSymbolLen	7
#pragma pack(1)

struct	hjcodex {			/* 현물종목코드	정보			*/
	char	code[12];		/* 코드(7) : A######			*/
							/* 코드(9) : 신주인수권, 증서	*/
	char	hnam[40];		/* 한글명						*/
	char	enam[40];		/* 영문명						*/
	char	ecng;			/* ECN (1:거래가능)				*/
	char	jsiz;			/* 업종자본금 대중소			*/
							/* 장내(대: 38, 중: 39, 소: 40)	*/
							/* 장외(1: KOSDAQ 100)		 	*/
							/* 장외(2: KOSDAQ MID 300)		*/
							/* 장외(3: KOSDAQ SMALL)		*/
							/* ############################ */
							/* 배당지수 : (jsiz += 41)		*/
							/* 신주인수권종목 FULL코드 용	*/
	char	symb[7];		/* SYMBOL						*/
	char	size;    		/* 시가총액규모(2, 3, 4)		*/
	char	jjug;			/* 제조업 구분(27: 제조업)		*/
							/* KOSDAQ 벤쳐 종합(=2)			*/
	char	kpgb;			/* KOSPI200/KOSDAQ 구분			*/
							/* 0:미포함 1:K200 2:K100 3:K50 */
							/* 0:미포함 1:KQ50				*/
	char	kosd;			/* 종목구분						*/
							/* 0:장내  10:장외  30:제3시장	*/
	char	ssgb;			/* 소속구분						*/
							/* 0:일반						*/
							/* 3:외국인예탁증서				*/
							/* 4:뮤추얼펀드					*/
							/* 5:신주인수권(중권)			*/
							/* 6:리츠						*/
							/* 7:신주인수권(증서)			*/
							/* 8:ETF						*/
							/* 9:하이일드펀드(수익증권)		*/
							/* 10: 선박 11:ELW 12:인프라 	*/
							/* 13: 해외ETF 14:해외원주		*/
	char	ucmd;			/* 우선주구분 0:보통주 5:우선주	*/
	char	itgb;			/* KOSPI-IT/KQ-IT50구분(1:채택)	*/
	char	wsgb;			/* 0:일반 1:지배구조우수기업	*/
	char	jqty;			/* 기본주문단위					*/
	char	star;			/* Star 종목구분				*/
	char	unio;			/* 통합지수종목 구분			*/
							/* 0: 일반, 1:통합지수			*/
							/* 2006.01.12 htsadd			*/
	char	jchk;			/* 종목검색용 구분				*/
							/* 0x01     불성실공시종목   	*/
							/* 0x02     신규상장종목     	*/
							/* 0x04     권리락종목       	*/
							/* 0x08     우선주종목       	*/
							/* 0x10     관리종목         	*/
							/* 0x20     감리종목         	*/
							/* 0x40     거래정지종목     	*/
							/* 0x80     투자유의종목     	*/
	char	elwf;			/* 0: 일반, 1: 기초자산 		*/
	char	sjjs[10];		/* 상장주식수(단위:주)			*/
	char	prmr;			/* 프리미어지수(1:프리미어지수)	*/
							/* 20160523 프리미어 지수 산출 중단 */
							/* 2:조기종료ELW				*/

	char uc10;				/* 건설기계", 0x00
						  조선운송", 0x01 ,
						  철강소재", 0x02
						  에너지화학", 0x03
						  정보통신", 0x04
						  금융", 0x05
						  필수소비재", 0x06
						  자유소비재", 0x07 					*/
	char	uc20;				/*우량기업", 0x00
						   벤처기업", 0x01 ,
						   중견기업", 0x02 ,
						   신성장기업", 0x03 					*/

						/* 섹터지수					*/
	char	sec1;		/*	자동차/반도체/건강/은행					*/
	char	sec2;		/*	정보통신/화학E/철강/필수				*/
	char	sec3;		/*	미디어/건설/금융/증권					*/
	char	sec4;		/*	조선/사회투자/보험/운송					*/
	char	sec5;		/*	소비자/레저/KRX100					*/
	char    acdl[6];       	/* 업종대분류                      <--- 추가			*/
	char    acdm[6];       	/* 업종중분류                      <--- 추가, AS-IS의 ucdm	*/
	char    acds[6];       	/* 업종소분류                     <--- 추가, AS-IS의 ucds	*/
	char	fill[20];		/* reserved	7						*/
};
/*
TO-BE 업종분류 첫 바이트가 '0' 이하는 미분류(현재 '000   ' 혹은 '      '으로 셋팅. 추후 데이터 확인 후 둘중 하나로 통일 예정)



***** ucdm <-> acdm, ucds <-> acds  매핑
           AS-IS   TO-BE  DESCRIPTION
코스피종목 001     KGG01P 코스피                        
코스피종목 002     KGZ01P 코스피 대형주                 
코스피종목 003     KGZ02P 코스피 중형주                 
코스피종목 004     KGZ03P 코스피 소형주                 
코스피종목 005     KGS01P 음식료품                      
코스피종목 006     KGS02P 섬유,의복                     
코스피종목 007     KGS03P 종이,목재                     
코스피종목 008     KGS04P 화학                          
코스피종목 009     KGS05P 의약품                        
코스피종목 010     KGS06P 비금속광물                    
코스피종목 011     KGS07P 철강및금속                    
코스피종목 012     KGS08P 기계                          
코스피종목 013     KGS09P 전기,전자                     
코스피종목 014     KGS19P 의료정밀                      
코스피종목 015     KGS10P 운수장비                      
코스피종목 016     KGS11P 유통업                        
코스피종목 017     KGS20P 전기가스업                    
코스피종목 018     KGS12P 건설업                        
코스피종목 019     KGS13P 운수창고                      
코스피종목 020     KGS21P 통신업                        
코스피종목 021     KGS14P 금융업                        
코스피종목 022     KGS15P 은행                          
코스피종목 024     KGS16P 증권                          
코스피종목 025     KGS17P 보험                          
코스피종목 026     KGS22P 서비스업                      
코스피종목 027     KGS18P 제조업                        
코스피종목 028     K2G14P 한국주가지수 200(특별결제지수)
코스피종목 029     K2G01P 코스피 200                    
코스피종목 035     K2G02P 코스피 100                    
코스피종목 036     K2G03P 코스피 50                     
코스피종목 150     K2S11P KOSPI 200 커뮤니케이션서비스  
코스피종목 151     K2S02P 코스피 200 건설               
코스피종목 152     K2S08P 코스피 200 중공업             
코스피종목 153     K2S09P 코스피 200 철강/소재          
코스피종목 154     K2S05P 코스피 200 에너지/화학        
코스피종목 155     K2S07P 코스피 200 정보기술           
코스피종목 156     K2S03P 코스피 200 금융               
코스피종목 157     K2S10P 코스피 200 생활소비재         
코스피종목 158     K2S06P 코스피 200 경기소비재         
코스피종목 159     K2S04P 코스피 200 산업재             
코스피종목 160     K2S01P 코스피 200 헬스케어           

코스닥종목 001     QGG01P 코스닥               
코스닥종목 002     QGZ01P 코스닥 대형주        
코스닥종목 003     QGZ02P 코스닥 중형주        
코스닥종목 004     QGZ03P 코스닥 소형주   

코스닥종목 007     QGS35P 중소기업지수         
코스닥종목 008     QGS36P 제조        

코스닥종목 009     QGS37P 유통서비스           
코스닥종목 010     QGS38P 건설        **         
코스닥종목 011     QGS39P 금융                 
코스닥종목 012     QGS01P 기타서비스           
코스닥종목 015     QGS32P 코스닥 IT            
코스닥종목 017     QGS42P 오락·문화     **       
코스닥종목 024     QGS02P 제조         **        
코스닥종목 026     QGS03P 건설                 
코스닥종목 027     QGS04P 유통        **         
코스닥종목 029     QGS31P 운송        **         
코스닥종목 031     QGS05P 금융        **            
코스닥종목 033     QGS49P 사업서비스           
코스닥종목 037     QGS34P 오락·문화           
코스닥종목 041     QGS06P 통신방송서비스          **
코스닥종목 042     QGS07P IT S/W & SVC           **
코스닥종목 043     QGS08P IT H/W                 **



코스닥종목 056     QGS09P 음식료·담배         
코스닥종목 058     QGS10P 섬유·의류           
코스닥종목 062     QGS11P 종이·목재           
코스닥종목 063     QGS12P 출판·매체복제       
코스닥종목 065     QGS13P 화학                 
코스닥종목 066     QGS33P 제약                 
코스닥종목 067     QGS14P 비금속               
코스닥종목 068     QGS15P 금속                 
코스닥종목 070     QGS16P 기계·장비           
코스닥종목 072     QGS17P 일반전기전자         
코스닥종목 074     QGS18P 의료·정밀기기       
코스닥종목 075     QGS19P 운송장비·부품       
코스닥종목 077     QGS20P 기타 제조            
코스닥종목 081     QGS65P 종합건설             
코스닥종목 082     QGS66P 전문건설             
코스닥종목 084     QGS68P 도매                 
코스닥종목 092     QGS75P 금융                 
코스닥종목 099     QGS81P 전문기술             
코스닥종목 106     QGS87P 오락·문화           
코스닥종목 151     QGS21P 통신서비스           
코스닥종목 152     QGS22P 방송서비스           
코스닥종목 153     QGS23P 인터넷               
코스닥종목 154     QGS24P 디지털컨텐츠         
코스닥종목 155     QGS25P 소프트웨어           
코스닥종목 156     QGS26P 컴퓨터서비스         
코스닥종목 157     QGS27P 통신장비             
코스닥종목 158     QGS28P 정보기기             
코스닥종목 159     QGS29P 반도체               
코스닥종목 160     QGS30P IT부품               

코스닥종목 181     QGG03P 코스닥 우량기업부    
코스닥종목 182     QGG04P 코스닥 벤처기업부    
코스닥종목 183     QGG05P 코스닥 중견기업부    
코스닥종목 184     QGG06P 코스닥 기술성장기업부
*/







struct	hjcode {
	char	code[HCodeLen];		// 코드	(12)
					// 코드(7) : A######
					// 코드(9) : 신주인수권, 증서
	char	hnam[HNameLen];		// 한글명(32)
	char	enam[ENameLen];		/* 영문명			*/
	char	ecng;			// ECN 구분
					// 거래가능:1
	char	jsiz;			// 업종자본금 대중소
					// 장내 (대:38  중:39  소:40)
					// 장외 (1:KOSDAQ 100)
					// 장외 (2:KOSDAQ MID 300)
					// 장외 (3:KOSDAQ SMALL)
					// 배당지수(jsiz += 41)
					// 신주인수권종목 FULL코드용
	char	symb[HSymbolLen];	// SYMBOL
	char	size;			// 자본금 규모
					// KOSPI  (대:2  중:3  소:4)
					// KOSDAQ (기타서비스:3  코스닥IT종합:4)
	char	ucdm;			// 업종중분류
					// KOSDAQ:5~14  미분류:99
	char	ucds;			// 업종소분류
					// KOSDAQ:15~37  벤쳐:7  미분류:99
	char	jjug;			// 제조업 구분
					// KOSPI  (제조업:27)
					// KOSDAQ (벤처지수:2)
	char	kpgb;			// KOSPI, KOSDAQ 구분
					// KOSPI  (0:미포함 1:K200 2:K100 3:K50)
					// KOSDAQ (0:미포함 1:KQ50)
	char	kosd;			// 종목구분
					// 0:장내  10:장외  30:제3시장
	char    ssgb;	// 소속구분
					// 0:일반
                    // 3:외국인예탁증서
                    // 4:뮤추얼펀드
                    // 5:신주인수권(중권)
                    // 6:리츠
                    // 7:신주인수권(증서)
                    // 8:ETF
                    // 9:하이일드펀드(수익증권)
                    // 10: 선박 12:인프라
                    // 13: 해외ETF 14:해외원주
					// 15 : 코넥스 
/*	char	ssgb;	// 소속구분
					// 0:default
					// 3:외국주
					// 4:뮤추얼펀드
					// 5:신주인수권
					// 6:리츠
					// 7:신주인수권증서
					// 8:ETF
					// 9:하이일드펀드
*/
	char	ucmd;			// 우선주구분 (0:보통주  5:우선주)
	char	itgb;			// KOSPI-IT/KQ-IT50구분(1:채택)
	char	wsgb;			// KOSPI 지배구조지수:42 (0:보통주 1:우수)
	char	jqty;			// 기본주문단위
	char	star;			// KOSDAQ 스타지수
	char	unio;			// 통합지수
	char    jchk;			// 종목검색용 구분
					// 0x01     불성실공시종목
					// 0x02     신규상장종목
					// 0x04     권리락종목
					// 0x08     우선주종목
					// 0x10     관리종목
					// 0x20     감리종목
					// 0x40     거래정지종목
					// 0x80     투자유의종목
	char    elwf;			// 0: 일반, 1: 기초자산 20070716 추가
	char	sjjs[10];		// 상장주식수(단위 주)
	char	prmr;			// 프리미어지수
	
	//2011.11.22 KSJ
	char	uc10;
						/* 건설기계", 0x01   
                          조선운송", 0x02 , 
                          철강소재", 0x03   
                          에너지화학", 0x04     
                          정보통신", 0x05   
                          금융", 0x06   
                          필수소비재", 0x07     
                          자유소비재", 0x08     */

	char	uc20;
						/*우량기업", 0x01   
                           벤처기업", 0x02 ,  
                           중견기업", 0x03 ,    
                           신성장기업", 0x04    */      

	char	fill[7];		// reserved
	// KSJ
//	char	fill[9];		// reserved
};	
	
//
//	hjcode.kosd : 종목구분
//
#define	jmKOSPI		0		// KOSPI 종목
#define jmKOSDAQ	10		// 코스닥
#define	jm3RD		30		// 제3시장

//
//	hjcode.ssgb : 소속구분
//
#define	jmDEF		0		// default
#define jmMUFND		4		// 뮤추얼펀드
#define jmSINJU		5		// 신주인수권
#define jmREITS		6		// 리츠
#define jmSINJS		7		// 신주인수권증서
#define jmETF		8		// ETF
#define	jmHYFND		9		// 하이일드펀드
#define	jmELW		11		// ELW
#define	jmFOREIGN	3		// 외국주 20070327
#define jmSHIP		10		// 선박
#define jmINFRA		12		// 인프라
#define jmKONEX		15		// KDK 2013.05.14 KONEX 
#define jmETN		16		// KSJ 2014.10.28 ETN 추가
#define jmSPAC		17		// KSJ 2015.11.03 spac 추가
#define jmKOSDAQ150	18		// KSJ 2016.08.22 KOSDAQ 150 추가

//
//	hjcode.ucmd : 보통주, 우선주
//
#define stockCom	0		// 보통주
#define stockPre	5		// 우선주

/*
 *	상품선물 코드 
 */
struct	ccode	{			/* 상품선물 종목코드 정보	*/
	char	codx[8]{};		/* 종목코드(8)			*/
	char	hnam[50]{};		/* 한글명			*/
	char	enam[50]{};		/* 영문명			*/
        char    mchk{};       /* 매매유형허용                 */
                            /* 0x01:시장가허용              */
                            /* 0x02:조건부지정가허용        */
                            /* 0x04:최유리지정가허용        */
	char	tjgb[2]{};		/* 거래대상 종목구분		*/
	char	jcod[12]{};		/* 기초자산 종목코드		*/
	char	jnam[40]{};		/* 기초자산 종목명		*/
	char	fill[20]{};		/* filler			*/
};

//
//	선물종목코드
//

#define FNameLen	20
#define FCodeLen	8

struct	fjcode {
	char	cod2[FCodeLen]{};		// 단축코드
	char	hnam[FNameLen]{};		// 한글명
	char	enam[FENameLen]{};	// 영문명
	char	mchk{};			// 매매유형허용
					// 0x01:시장가허용
					// 0x02:조건부지정가허용
					// 0x04:최유리지정가허용
};

struct  sfcode {            /* 주식선물 종목코드 정보       */
	char    codx[8]{};        /* 단축코드(8)                  */
	char    hnam[50]{};       /* 한글명                       */
	char    enam[50]{};       /* 영문명                       */
	char    mchk{};           /* 매매유형허용                 */
	/* 0x01:시장가허용              */
	/* 0x02:조건부지정가허용        */
	/* 0x04:최유리지정가허용        */
	char    tjgb[2]{};        /* 거래대상 종목구분            */
	char    gcod[12]{};       /* 기초자산종목코드             */
	char    gnam[32]{};       /* 기초자산 종목명              */
	char	gdan[18]{};		/* 거래단위						*/
	char    mgub[1]{};        /* 마켓구분 코스피[K], 코스닥[Q]         */
	char    fill[29]{};       /* reserved                     */
};

//
//	옵션코드 
//

#define OPriceLen	5
#define ONameLen	20
#define OCodeLen	9

//
//	옵션종목코드 HEADER
//
struct	ojcodh {
	char	cjym[11][6]{};		// CALL 옵션 종목 타이틀
	char	pjym[11][6]{};		// PUT  옵션 종목 타이틀
};

//
//	옵션종목코드
//
struct	ojcode {
	char	price[OPriceLen]{};	// 행사가격 (999.99)
	char	atmg{};			// ATM 구분
	struct	{
		char	yorn{};		// 종목	코드 유무
		char	cod2[OCodeLen]{};	// 단축종목코드
		char	hnam[ONameLen]{};	// 한글종목명
		char	enam[FENameLen]{};	// 영문명
		char	mchk{};		// 매매유형허용
					// 0x01:시장가허용
					// 0x02:조건부지정가허용
					// 0x04:최유리지정가허용
	} call[11]{}; 
	struct	{
		char	yorn{};		// 종목	코드 유무
		char	cod2[OCodeLen]{};	// 단축종목코드
		char	hnam[ONameLen]{};	// 한글종목명
		char	enam[FENameLen]{};	// 영문명
		char	mchk{};		// 매매유형허용
					// 0x01:시장가허용
					// 0x02:조건부지정가허용
					// 0x04:최유리지정가허용
	} put[11]{}; 
};


//
//	채권코드
//

#define	CCodeLen	12
#define	CNameLen	40

struct	cjcode	{
	char	code[CCodeLen]{};
	char	cgub{};			// 채권구분
					// 1:국민주택1종 당월분
					// 2:국민주택1종 전월분
					// 3:서울도시철도 당월분
					// 4:서울도시철도 전월분
					// 5:지역개발채권 당월분
					// 6:지역개발채권 전월분
					// 7:지방도시철도 당월분
					// 8:지방도시철도 전월분
					// 99:전환사채
	char	hnam[CNameLen]{};		// 채권이름
	char    ngub{};			// 구분 0: 전체, 1:최근종목
};

//
//	cjcode : 채권구분
//
#define	cjSo	1			// 소액채권
#define	cjCh	2			// 전환사채


//
//	업종코드
//

#define	UNameLen	20

struct	upcode	{
	char	jgub{};			// 장구분
					// 0:장내 1:장외
					// 1: KOSPI200
					// 3: KOSDAQ50(1), KQ-IT 50(2)
					// 4: K100P(1), K50(2), IT(3
					// 6: SECTOR, 7:프리보드 
	char	ucod{};			// 업종코드
	char	hnam[UNameLen]{};	// 한글명
};

//
//	upcode.jgup : 장구분 : 신한변경
//
#define	upKOSPI		0		// 1~41
#define upKOSPI200	1		// 1~6
#define	upKOSDAQ	2		// 1~40
#define upKOSDAQ50	3		// KOSDAQ50   : ucod = 1
					// KOSDAQIT50 : ucod = 2
#define upKOSPIx	4		// KOSPI100   : ucod = 1
					// KOSPI50    : ucod = 2
					// KOSPIIT    : ucod = 3
#define	upSECTOR	6		// 섹터지수
#define upFREEBOARD	7		// 프리보드   
#define	upINTEGRATE	9		// 통합지수

#define	upNOT		10		// not
#define	upOTHER		11		// KOSPI IT, KOSPI200
					// KOSPI100, KOSDAQ50
#define	upKONEX		15		// KONEX
#define	upETN		16		// KONEX
#define	upETC		17		// 기타지수

//
//	KOFEX
//

//
//	미래에셋
//

#define KCodeLen        15
#define KNameLen        30

struct	kfcode	{
	char	kcod[2]{};		// Commodity Code
					// 01 :	USD Currency Futures
					// 02 : USD Currency Call Option
					// 03 : USD Currency Put Option
					// 04 : GOLD Currency Futures
					// 05 : CD Futures
					// 06 : KTB Futures
					// 07 : KOSDAQ50 Futures
	char	codx[KCodeLen]{};	// 종목코드
	char	hnam[KNameLen]{};	// 한글명
};

#define kfTOTAL		0
#define	kfUSDFUTURE	1
#define kfUSDCALL	2
#define kfUSDPUT	3
#define kfGOLD		4
#define kfCD		5
#define kfKTB		6
#define kfKOSDAQ	7


//
//	신한
//

#define KFOCodeLen      15
#define KFONameLen      30
#define KFOPriceLen	5
#define KFOMonthLen	4

struct	kfocode	{		
	char	codx[KFOCodeLen]{};	// 단축코드
					// 선물보통: 6자리
					// 선물복합: 8자리
					// 옵션보통: 9자리
					// 옵션복합:11자리
					// 나머지 NULL
	char	hnam[KFONameLen]{};	// 한글명
	char	flag{};			// 선물옵션 구분 FLAG
					// 1:선물
					// 2:CALL 옵션
					// 3:PUT  옵션
	char	mont[KFOMonthLen]{};	// 1-12 월물
	char	comb{};			// 정형복합구분
					// 1:Time  Spread
					// 2:Price Spread
					// 0:복합 비해당
	char	atmf{};			// ATM 해당여부
					// 1   :ATM
					// else:비해당
	char	hsga[KFOPriceLen]{};	// 행사가격 (옵션에만 해당)
};


//
//	현물옵션
//

#define PCodeLen	8

struct pjcode {
	char	gubn{};		// 1:KOSPI, 2:KOSDAQ
	char	tjgb[2]{};	// 거래대상종목구분
	char	snam[20]{};	// 거래대상종목명

	char	codx[8]{};	// 단축코드
	char	hnam[30]{};	// 한글명
	char	enam[30]{};	// 영문명
	char	gcod[12]{};	// 기초자산종목코드
	char	mont[4]{};	// 월물
	char	atmx{};		// ATM종목여부 1:ATM종목
	char	hsga[PCodeLen]{};	// 행사가
	char	mchk{};		// 매매유형허용
				// 0x01:시장가허용
				// 0x02:조건부지정가허용
				// 0x04:최유리지정가허용
};

#define	L_pjcode	sizeof(struct pjcode)


//
//	ELW
//

#define	ELWCodeLen	12
#define	ELWHNameLen	32
#define	ELWENameLen	20

struct elwcode {
	char	codx[ELWCodeLen]{};	// ELW종목코드(6) J######
	char	hnam[ELWHNameLen]{};	// 한글명
	char	enam[ELWENameLen]{};	// 형문명
	char	symb[7]{};		// SYMBOL
	char	lphn[5][3]{};		// ELW - LP 회원번호 1~5
	char	lpse[5]{};		// ELW 스프레드 (999V99)
	char	hbge[ELWENameLen]{};	// ELW 한글발행기관명
	char	ebge[ELWENameLen]{};	// ELW 영문발행기관명
	char	bgce[12]{};		// ELW 발행기관코드
	char	gcjs[5][12]{};		// ELW 기초자산 1~5
	char	grat[5][5]{};		// ELW 기초자산구성비율 1~5 (999V99)
	char	gcge[10]{};		// ELW 기초가격 (99999999V99)
	char	hsge[10]{};		// ELW 행사가격 (99999999V99)
	char	krye[2]{};		// ELW 권리유형 01:CALL, 02:PUT, 03:기타
	char	khbe[2]{};		// ELW 권리행사방식 01:유럽형, 02:미국형, 03:기타
	char	mjmt[8]{};		// ELW 만기월 (YYYYMMDD)
	char	koba[1]{};		// 조기종료ELW 여부
	char	fill[39]{};		// reserved
};

#define L_elwcode	sizeof(struct elwcode)


// 소매채권(sjcode.dat)
#define	SCodeLen	12
#define	SNameLen	20

struct	sjcode	{
	char	code[SCodeLen]{};
	char	cgub{};			// 채권구분
					// 1: 국채
					// 2: 통안채
					// 3: 금융채
					// 4: 비금융특수채
					// 5: 최사채
					// 6: 기타
	char	hnam[SNameLen]{};	// 채권이름
	char    ngub{};			// 구분 0: 전체, 1:최근종목
};

//
//	sjcode : 소매채권구분
//
#define	sjKC	1			// 국채
#define	sjTA	2			// 통안채
#define	sjKY	3			// 금융채
#define	sjNK	4			// 비금융특수채
#define	sjCS	5			// 최사채
#define	sjET	6			// 기타

#pragma pack()
