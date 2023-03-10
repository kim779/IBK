#pragma once

#define MYFD_MAXFUND	100
#define MYFD_MAXGROUP	100
#define MYFD_MAXCNT		100
#define MYFD_DEFMAXCNT	200

struct __mid2
{
	char	gubn[1];			/*구분('i': 신규그룹, 'u': 수정, 'd': 삭제)*/
	char	grcd[4];			/*그룹코드*/
};

/************************************************************************/
/*  그룹 펀드데이터 출력			                                    */
/************************************************************************/

struct item3
{
	char	fdcd[12];		/*펀드코드		*/
	char	fdnm[40];		/*펀드명		*/
	char	sprc[10];		/*기준가		*/
	char	dtrt[9];		/*1일수익률		*/
	char	wkrt[9];		/*1주수익률		*/
	char	rt01[9];		/*1개월수익률	*/
	char	rt03[9];		/*3개월수익률	*/
	char	rt06[9];		/*6개월수익률	*/
	char	rt12[9];		/*12개월수익률	*/
	char	rt36[9];		/*36개월수익률	*/
	char	yrat[9];		/*해당년도 수익률*/
	char	rate[9];		/*기간수익률	*/
	char	idnm[40];		/*간접투자유형	*/
	char	term[4];		/*기간(일)		*/
	char	stdt[8];		/*설정일		*/
	char	strt[7];		/*주식편입비율	*/
	char	ivnm[40];		/*투자등급명	*/   
	char	cfName[100];	/*클래스 상세	*/   //test 
};

struct _mod3
{
	char	nrce[4];
	struct	item3	list[MYFD_MAXCNT];
};



/************************************************************************/
/*  그룹별 펀드목록 입력/수정/삭제                                      */
/************************************************************************/
struct _4mid1
{
	char	gubn[1];			/*구분('U': 입력/수정, 'D':삭제)*/

};

struct _mid1
{
	char	gubn[1];			/*구분('U': 입력/수정, 'D':삭제)*/
	char	nrec[3];			/*펀드코드 갯수*/ 
	char	grcd[4];			/*그룹코드*/

	char	afcd[MYFD_MAXFUND][12];		/*펀트코드 리스트*/
};

/************************************************************************/
/*  그룹별 펀드 출력 목록		                                        */
/************************************************************************/

struct _mod1
{
	char	rest[1];			/*처리 결과(Y/N)*/
	char	ercd[3];			/*에러코드(0: 정상, 9XX: WARNING, 그외:에러)*/
};


/************************************************************************/
/*  그룹편집(신규그룹 입력)	                                            */
/************************************************************************/

struct _mid2
{
	char	gubn[1];			/*구분('i': 신규그룹, 'u': 수정, 'd': 삭제)*/
	char	grnm[20];			/*그룹명*/
};

/************************************************************************/
/*  그룹편집(그룹수정)											        */
/************************************************************************/

struct _item1
{
	char	ngrd[4];			/*신규 그룹코드*/
	char	ogrd[4];			/*기존 그룹코드*/
	char	grnm[20];			/*그룹명*/
};

struct _mid3
{
	char	gubn[1];			/*구분('i': 신규그룹, 'u': 수정, 'd': 삭제)*/
	char	nrce[3];			/*그룹갯수*/

	struct	_item1	list[MYFD_MAXFUND];		/*그룹코드 리스트*/
};

/************************************************************************/
/*  그룹편집(그룹 삭제)	                                                */
/************************************************************************/

struct _mid4
{
	char	gubn[1];			/*구분('i': 신규그룹, 'u': 수정, 'd': 삭제)*/
	char	nrce[3];			/*그룹갯수*/
	
	char	agcd[MYFD_MAXGROUP][4];		/*그룹코드 리스트*/
};

/************************************************************************/
/*  그룹편집(공통출력)	                                                */
/************************************************************************/

struct _item2
{
	char	ngrd[4];			/*신규 그룹코드*/
	char	ogrd[4];			/*기존 그룹코드*/
	char	grnm[20];			/*그룹명*/
};

struct _mod2
{
	char	rest[1];			/*처리 결과(Y/N)*/
	char	ercd[3];			/*에러코드(0: 정상, 9XX: WARNING, 그외:에러)*/
	char	nrec[4];			/*그룹갯수*/

	struct	_item2	list[MYFD_MAXGROUP];	/*그룹코드 리스트*/ 
	
};


/************************************************************************/
/*  pihbund(코드파일) : fdcode.dat                                      */
/************************************************************************/

typedef struct  
{
	char	code[12];			/*펀드코드*/
	char	name[40];			/*펀드명*/
	char	rt06[9];			/*6개월 수익률*/
	char	rate[9];			/*누적 수익률*/
	char	idtp[20];			/*간접투자유형*/
	char	sdat[8];			/*설정일*/
	char	rknm[20];			/*투자등급명*/
	char	shgb[1];			/*조회구분*/
								/*'1': 인터넷거래가능*/
								/*'0': 인터넷거래불가능*/
	char	lnfd[1];			/*라인피드*/
}_ITEM01;

/************************************************************************/
/*  백업 요청/원복요청				                                    */
/************************************************************************/

struct _mid5
{
	char	gubn[1];		/*백업요청('b':  백업, 'r'  : 원복)*/
};


/************************************************************************/
/*  백업 요청/원복 결과				                                    */
/************************************************************************/

struct _modB3
{
	char rest[1];			/*처리결과*/
	char ercd[3];			/*에러코드*/
};

