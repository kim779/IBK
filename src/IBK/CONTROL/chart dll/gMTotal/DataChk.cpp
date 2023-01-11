// DataChk.cpp: implementation of the CDataChk class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "axisGMTotal.h"
#include "DataChk.h"
#include "../../chart_dll/Common/SavedHead.h"
#include "../../h/axisgbinfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

int	pReqCnt[5] = {300,200,100,400,400};
int pDisCnt[5] = {50, 50, 50, 200, 300};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataChk::CDataChk(CWnd *pView, struct _param *param, CString &fname, int mType, bool bMake)
{
	m_pwndMain = pView;
	m_mType = mType;
	m_mKey = param->key;
	m_mGap = 1;
	m_tGap = 1;

	ParseParam(param->options);

	fname.Format("%s", m_strFileName);
	m_iFPoint = param->point;
	m_strFName.Format("%s", param->fonts);
	m_rgbFG = GetPalette(param->tRGB);
	m_rgbBG = GetPalette(param->pRGB);
	
	CString	root = (char *)m_pwndMain->SendMessage(WM_USER, MAKEWPARAM(variantDLL, homeCC), 0);
	CString name = (char *)m_pwndMain->SendMessage(WM_USER, MAKEWPARAM(variantDLL, nameCC), 0);
	m_strTabDir.Format("%s\\%s\\", root, TABDIR);
	m_strGexDir.Format("%s\\%s\\%s\\", root, GEXDIR, name);

	if (bMake)
		CheckData(root, name);
}

CDataChk::~CDataChk()
{
}

void CDataChk::CheckData(CString strRoot, CString strName)
{
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = FindFirstFile(m_strGexDir, &findFileData);
	if (hFind == INVALID_HANDLE_VALUE)
		CreateDirectory(m_strGexDir, NULL);

	MakeData();
}

bool CDataChk::MakeData()
{
	CString	strEnvPath = m_strGexDir + m_strFileName + ENV;
	CString	strGrpPath = m_strGexDir + m_strFileName + GRP;
	CString	strDatPath = m_strGexDir + m_strFileName + DAT;

	CString	strBasicEnvPath = m_strGexDir + m_strFileName + ENV_B;
	CString	strBasicGrpPath = m_strGexDir + m_strFileName + GRP_B;

	DWORD dwReadLen;
	// env
	CSavedHead shEnv;
	char* pcData = shEnv.Read(strEnvPath, dwReadLen);
	if (!pcData || dwReadLen < 1) // New가 없다면
		MakeEnv(strEnvPath, strBasicEnvPath); // New 생성

	// grp
	CSavedHead shGrp;
	pcData = shGrp.Read(strGrpPath, dwReadLen);
	if (!pcData || dwReadLen < 1)	// New가 없다면
		MakeGrp(strGrpPath, strBasicGrpPath); // New 생성

	// dat
	CSavedHead shDat;
	pcData = shDat.Read(strDatPath, dwReadLen);
	if (!pcData || dwReadLen < 1)	// New가 없다면
		MakeDat(strDatPath); // New 생성

	return true;
}

void CDataChk::ReMakeData()
{
	CString	strEnvPath = m_strGexDir + m_strFileName + ENV;
	CString	strGrpPath = m_strGexDir + m_strFileName + GRP;
	CString	strDatPath = m_strGexDir + m_strFileName + DAT;
	CString	strBasicEnvPath = m_strGexDir + m_strFileName + ENV_B;
	CString	strBasicGrpPath = m_strGexDir + m_strFileName + GRP_B;

	DeleteFile(strEnvPath);
	DeleteFile(strGrpPath);
	DeleteFile(strDatPath);
	DeleteFile(strBasicEnvPath);
	DeleteFile(strBasicGrpPath);

	MakeEnv(strEnvPath, strBasicEnvPath);
	MakeGrp(strGrpPath, strBasicGrpPath);
	MakeDat(strDatPath);
}

void CDataChk::MakeDat(CString fname)
{
	struct _cntInfo cntInfo;
	cntInfo.wMainCnt = 20;
	cntInfo.wAidCnt = 60;
	cntInfo.wUserCnt = 0;
	int iDataSize = SZ_CNTINFO + SZ_GRAPH*(cntInfo.wMainCnt + cntInfo.wAidCnt + cntInfo.wUserCnt);
	char* buf = new char[iDataSize];

	ZeroMemory(buf, iDataSize);
	CopyMemory(buf, &cntInfo, SZ_CNTINFO);
	InitInfo(&cntInfo, &buf[SZ_CNTINFO]);

	CSavedHead sh;
	char* pcDat = sh.Make(VERSION_DAT, 1, iDataSize);
	CopyMemory(pcDat, buf, iDataSize);
	sh.Write(fname);

	delete buf;
}

void CDataChk::MakeEnv(CString fname, CString bname)
{
	struct	_envInfo envinfo;
	memset(&envinfo, 0x00, SZ_ENVINFO);
	
	envinfo.wVersion = GRP_VERSION;
	sprintf(envinfo.acObjName, "%s", m_strFileName);
	envinfo.wEnvOption = EO_MAP | EO_SAVE;
	if (m_bName)	envinfo.wEnvOption |= EO_JNAME;

	sprintf(envinfo.display.font.acFName, m_strFName);
	envinfo.display.font.btFPoint = m_iFPoint;
	sprintf(envinfo.display.tfont.acFName, m_strFName);
	envinfo.display.tfont.btFPoint = m_iFPoint;
	sprintf(envinfo.display.atick[0].tfont.acFName, m_strFName);
	envinfo.display.atick[0].tfont.btFPoint = m_iFPoint;
	sprintf(envinfo.display.atick[1].tfont.acFName, m_strFName);
	envinfo.display.atick[1].tfont.btFPoint = m_iFPoint;
	sprintf(envinfo.display.atick[2].tfont.acFName, m_strFName);
	envinfo.display.atick[2].tfont.btFPoint = m_iFPoint;

	envinfo.display.rgbBG = RGB(243,249,254);
	envinfo.display.rgbEdge = RGB(192,192,192);
	envinfo.display.rgbChartBG = m_rgbBG;
	envinfo.display.rgbChartEdge = RGB(180,192,203);

	envinfo.display.wLMargin = 2;
	envinfo.display.wRMargin = 10;

	envinfo.display.dwDspOption = 
		DO_SCREEN | DO_DISPRT | 
		DO_TKVGRID | DO_TKHGRID | DO_MOD | DO_LOCK | DO_CURRENT | 
		/*DO_MINMAX  |*/ DO_USEGRID | /**DO_VIEWGRID | DO_NOVIEWTIP |**/
		DO_NOCROSS;

	envinfo.display.dwDspOption |= m_iTickDisplay;

	envinfo.display.toolinfo.rgbLine = DEFCR4;
	envinfo.display.toolinfo.btLineStyle = PS_SOLID;
	envinfo.display.toolinfo.btLineWidth = 1;
	envinfo.display.hline.rgbLColor = RGB(180,192,203);
	envinfo.display.hline.btLStyle = PS_SOLID;
	envinfo.display.hline.btLWidth = 1;
	envinfo.display.vline.rgbLColor = RGB(180,192,203);
	envinfo.display.vline.btLStyle = PS_SOLID;
	envinfo.display.vline.btLWidth = 1;
	envinfo.display.dline.rgbLColor = RGB(251, 133, 133);
	envinfo.display.dline.btLStyle = PS_DOT;
	envinfo.display.dline.btLWidth = 1;
	envinfo.display.cline.rgbLColor = RGB(0, 128, 0);
	envinfo.display.cline.btLStyle = PS_SOLID;
	envinfo.display.cline.btLWidth = 1;

	envinfo.wViewWidth = 800;
	envinfo.wViewHeight = 550;
	
	envinfo.panel[0].btPnID = PN_INPUT;
	envinfo.panel[0].wPnOption = PO_USE|PO_SHOW;

	envinfo.panel[1].btPnID = PN_SISE;
	envinfo.panel[1].wPnOption = 0;

	envinfo.panel[2].btPnID = PN_CTRL;
	envinfo.panel[2].wPnOption = PO_USE|PO_SHOW;

	int	rcnt, gcnt, realGCnt;
	GetCntInfo(rcnt, gcnt, realGCnt);

	for (int ii = 0; ii < MAX_INDEX - 1; ii++)
	{
		envinfo.grpinfo[ii].wRgnCnt = rcnt;
		envinfo.grpinfo[ii].wGrpCnt = gcnt;
	}
	envinfo.grpinfo[MAX_INDEX - 1].wRgnCnt = rcnt;
	envinfo.grpinfo[MAX_INDEX - 1].wGrpCnt = realGCnt;


	char	ulist[10] = {GK_PSY, GK_GAP, GK_BOLB, GK_CCI, GK_MACD, 
		GK_MACDOS, GK_PARB, GK_PIVOT, GK_RSI, GK_STOCHS};
	for (ii = 0; ii < 10; ii++)
		envinfo.ulist[ii] = ulist[ii];

	envinfo.datainfo.btUnit = m_iDtUnit;
	envinfo.datainfo.btIndex = m_iDtIndex;
	envinfo.datainfo.wMGap = m_mGap;
	envinfo.datainfo.wTGap = m_tGap;
	envinfo.datainfo.wMainGrpKind = m_iBongKind;
	envinfo.datainfo.wUpdate = DU_RTM|DU_DUMMY;

	for (ii = 0; ii < 4; ii++)
	{
		for (int jj = 0; jj < MAX_INDEX; jj++)
		{
			envinfo.datainfo.aaDayInfo[ii][jj].dwTotCnt = pReqCnt[jj];
			if (jj == 3)	// minute
			{
				if (m_mGap == 1)
					envinfo.datainfo.aaDayInfo[ii][jj].dwDisCnt = 200;
				else if (m_mGap <= 10)
					envinfo.datainfo.aaDayInfo[ii][jj].dwDisCnt = 100;
				else
					envinfo.datainfo.aaDayInfo[ii][jj].dwDisCnt = 50;
			}
			else
			{
				envinfo.datainfo.aaDayInfo[ii][jj].dwDisCnt = pDisCnt[jj];
			}
		}
	}

	CSavedHead sh;
	char* pcEnv = sh.Make(VERSION_ENV, 1, SZ_ENVINFO);
	CopyMemory(pcEnv, &envinfo, SZ_ENVINFO);
	sh.Write(fname);

	if (!bname.IsEmpty())
		sh.Write(bname);
}

void CDataChk::MakeGrp(CString fname, CString bname)
{
	COLORREF	MC5 = RGB(255,144,0);
	COLORREF	MC6 = RGB(220,2,2);
	COLORREF	MC7 = RGB(165,111,227);
	COLORREF	MC8 = RGB(10,10,10);

	int	iRCnt, iGCnt, iRealGCnt;
	GetCntInfo(iRCnt, iGCnt, iRealGCnt);

	int iLen = SZ_REGION * iRCnt + SZ_GRAPH * iGCnt;
	char* pcBuf = new char[iLen * MAX_INDEX];
	ZeroMemory(pcBuf, iLen);

	struct _region *region;
	if (iRCnt == 2)
	{
		region = (struct _region *)pcBuf;
		region->btRKey = 1;
		region->wRLeft = 0;
		region->wRRight = 10000;
		region->wRTop = 0;
		region->wRBottom = 7000;
		region = (struct _region *)&pcBuf[SZ_REGION];
		region->btRKey = 2;
		region->wRLeft = 0;
		region->wRRight = 10000;
		region->wRTop = 7000;
		region->wRBottom = 10000;
	}
	else
	{
		region = (struct _region *)pcBuf;
		region->btRKey = 1;
		region->wRLeft = 0;
		region->wRRight = 10000;
		region->wRTop = 0;
		region->wRBottom = 10000;
	}

///////////////////////////////////////////////////
	int	pmaFlag = 0;
	switch (m_iPMACnt)
	{
	case 1:	pmaFlag = 0x01;	break;
	case 2:	pmaFlag = 0x01 | 0x02;	break;
	case 3:	pmaFlag = 0x01 | 0x02 | 0x04;	break;
	case 4:	pmaFlag = 0x01 | 0x02 | 0x04 | 0x08;	break;
	}

	int	vmaFlag = 0;
	switch (m_iVMACnt)
	{
	case 1:	vmaFlag = 0x01;	break;
	case 2:	vmaFlag = 0x01 | 0x02;	break;
	case 3:	vmaFlag = 0x01 | 0x02 | 0x04;	break;
	case 4:	vmaFlag = 0x01 | 0x02 | 0x04 | 0x08;	break;
	}
///////////////////////////////////////////////////
	struct _graph *graph;
	graph = (struct _graph *)&pcBuf[SZ_REGION*iRCnt];
	graph->wKey = 1;
	graph->btRgnKey = 1;
	graph->btDataKey = 1;
	graph->btGType = GT_BONG;
	graph->wGKind = m_iBongKind;
	graph->wSKind = 1;
	graph->wCalOption = 0;
	graph->dwDraOption = GO_FIILUPBONG|GO_FIILDNBONG;
	graph->rgbLabel = LINCR;

	graph->cInfo.aline[0].rgbLColor = LINCR;
	graph->cInfo.aline[0].btLStyle = PS_SOLID;
	graph->cInfo.aline[0].btLWidth = 1;
	graph->cInfo.aline[1].rgbLColor = BUPCR;
	graph->cInfo.aline[1].btLStyle = PS_SOLID;
	graph->cInfo.aline[1].btLWidth = 1;
	graph->cInfo.aline[2].rgbLColor = BDNCR;
	graph->cInfo.aline[2].btLStyle = PS_SOLID;
	graph->cInfo.aline[2].btLWidth = 1;

///////////////////////////////////////////////////
	int	ii;
	switch (iGCnt)
	{
	case 2:
		if (m_bVol)	// bong, vol
		{
			graph = (struct _graph *)&pcBuf[SZ_REGION*iRCnt + SZ_GRAPH];
			graph->wKey = 2;
			graph->btRgnKey = 2;
			graph->btDataKey = 1;
			graph->btGType = GT_BONG;
			graph->wGKind = GK_VOL;
			graph->wSKind = 1;
			graph->wCalOption = GC_VOLVOL;
			graph->rgbLabel = LINCR;

			graph->cInfo.aline[0].rgbLColor = VOLCR;
			graph->cInfo.aline[0].btLStyle = PS_SOLID;
			graph->cInfo.aline[0].btLWidth = 1;
			graph->cInfo.aline[1].rgbLColor = BUPCR;
			graph->cInfo.aline[1].btLStyle = PS_SOLID;
			graph->cInfo.aline[1].btLWidth = 1;
			graph->cInfo.aline[2].rgbLColor = BDNCR;
			graph->cInfo.aline[2].btLStyle = PS_SOLID;
			graph->cInfo.aline[2].btLWidth = 1;
		}
		else	// bong, pma
		{
			graph = (struct _graph *)&pcBuf[SZ_REGION*iRCnt + SZ_GRAPH];
			graph->wKey = 2;
			graph->btRgnKey = 1;
			graph->btDataKey = 1;
			graph->btGType = GT_BONG;
			graph->wGKind = GK_PMA;
			graph->wSKind = 1;
			graph->wCalOption = 0;
			graph->rgbLabel = LINCR;

			graph->cInfo.wCOption = pmaFlag;
			graph->cInfo.aline[0].rgbLColor = DEFCR8;
			graph->cInfo.aline[0].btLStyle = PS_SOLID;
			graph->cInfo.aline[0].btLWidth = 1;
			graph->cInfo.aline[1].rgbLColor = DEFCR15;
			graph->cInfo.aline[1].btLStyle = PS_SOLID;
			graph->cInfo.aline[1].btLWidth = 1;
			graph->cInfo.aline[2].rgbLColor = DEFCR14;
			graph->cInfo.aline[2].btLStyle = PS_SOLID;
			graph->cInfo.aline[2].btLWidth = 1;
			graph->cInfo.aline[3].rgbLColor = DEFCR4;
			graph->cInfo.aline[3].btLStyle = PS_SOLID;
			graph->cInfo.aline[3].btLWidth = 1;
			graph->cInfo.aline[4].rgbLColor = MC5;
			graph->cInfo.aline[4].btLStyle = PS_SOLID;
			graph->cInfo.aline[4].btLWidth = 1;
			graph->cInfo.aline[5].rgbLColor = MC6;
			graph->cInfo.aline[5].btLStyle = PS_SOLID;
			graph->cInfo.aline[5].btLWidth = 1;
			graph->cInfo.aline[6].rgbLColor = MC7;
			graph->cInfo.aline[6].btLStyle = PS_SOLID;
			graph->cInfo.aline[6].btLWidth = 1;
			graph->cInfo.aline[7].rgbLColor = MC8;
			graph->cInfo.aline[7].btLStyle = PS_SOLID;
			graph->cInfo.aline[7].btLWidth = 1;

			for (ii = 0; ii < 4; ii++)
			{
				if (m_aiPMA[ii])
					graph->cInfo.awValue[ii] = m_aiPMA[ii];
			}
		}
		break;
	case 3:
		if (m_iPMACnt)	// bong, pma, vol
		{
			graph = (struct _graph *)&pcBuf[SZ_REGION*iRCnt + SZ_GRAPH];
			graph->wKey = 2;
			graph->btRgnKey = 1;
			graph->btDataKey = 1;
			graph->btGType = GT_BONG;
			graph->wGKind = GK_PMA;
			graph->wSKind = 1;
			graph->wCalOption = 0;
			graph->rgbLabel = LINCR;

			graph->cInfo.wCOption = pmaFlag;
			graph->cInfo.aline[0].rgbLColor = DEFCR8;
			graph->cInfo.aline[0].btLStyle = PS_SOLID;
			graph->cInfo.aline[0].btLWidth = 1;
			graph->cInfo.aline[1].rgbLColor = DEFCR15;
			graph->cInfo.aline[1].btLStyle = PS_SOLID;
			graph->cInfo.aline[1].btLWidth = 1;
			graph->cInfo.aline[2].rgbLColor = DEFCR14;
			graph->cInfo.aline[2].btLStyle = PS_SOLID;
			graph->cInfo.aline[2].btLWidth = 1;
			graph->cInfo.aline[3].rgbLColor = DEFCR4;
			graph->cInfo.aline[3].btLStyle = PS_SOLID;
			graph->cInfo.aline[3].btLWidth = 1;
			graph->cInfo.aline[4].rgbLColor = MC5;
			graph->cInfo.aline[4].btLStyle = PS_SOLID;
			graph->cInfo.aline[4].btLWidth = 1;
			graph->cInfo.aline[5].rgbLColor = MC6;
			graph->cInfo.aline[5].btLStyle = PS_SOLID;
			graph->cInfo.aline[5].btLWidth = 1;
			graph->cInfo.aline[6].rgbLColor = MC7;
			graph->cInfo.aline[6].btLStyle = PS_SOLID;
			graph->cInfo.aline[6].btLWidth = 1;
			graph->cInfo.aline[7].rgbLColor = MC8;
			graph->cInfo.aline[7].btLStyle = PS_SOLID;
			graph->cInfo.aline[7].btLWidth = 1;

			for (ii = 0; ii < 4; ii++)
			{
				if (m_aiPMA[ii])
					graph->cInfo.awValue[ii] = m_aiPMA[ii];
			}
			///////////////////////////////////////////////////////////
			graph = (struct _graph *)&pcBuf[SZ_REGION*iRCnt + SZ_GRAPH*2];
			graph->wKey = 3;
			graph->btRgnKey = 2;
			graph->btDataKey = 1;
			graph->btGType = GT_BONG;
			graph->wGKind = GK_VOL;
			graph->wSKind = 1;
			graph->wCalOption = GC_VOLVOL;
			graph->rgbLabel = LINCR;

			graph->cInfo.aline[0].rgbLColor = VOLCR;
			graph->cInfo.aline[0].btLStyle = PS_SOLID;
			graph->cInfo.aline[0].btLWidth = 1;
			graph->cInfo.aline[1].rgbLColor = BUPCR;
			graph->cInfo.aline[1].btLStyle = PS_SOLID;
			graph->cInfo.aline[1].btLWidth = 1;
			graph->cInfo.aline[2].rgbLColor = BDNCR;
			graph->cInfo.aline[2].btLStyle = PS_SOLID;
			graph->cInfo.aline[2].btLWidth = 1;
		}
		else		// bong, vol, vma
		{
			graph = (struct _graph *)&pcBuf[SZ_REGION*iRCnt + SZ_GRAPH];
			graph->wKey = 2;
			graph->btRgnKey = 2;
			graph->btDataKey = 1;
			graph->btGType = GT_BONG;
			graph->wGKind = GK_VOL;
			graph->wSKind = 1;
			graph->wCalOption = GC_VOLVOL;
			graph->rgbLabel = LINCR;

			graph->cInfo.aline[0].rgbLColor = VOLCR;
			graph->cInfo.aline[0].btLStyle = PS_SOLID;
			graph->cInfo.aline[0].btLWidth = 1;
			graph->cInfo.aline[1].rgbLColor = BUPCR;
			graph->cInfo.aline[1].btLStyle = PS_SOLID;
			graph->cInfo.aline[1].btLWidth = 1;
			graph->cInfo.aline[2].rgbLColor = BDNCR;
			graph->cInfo.aline[2].btLStyle = PS_SOLID;
			graph->cInfo.aline[2].btLWidth = 1;
			///////////////////////////////////////
			graph = (struct _graph *)&pcBuf[SZ_REGION*iRCnt + SZ_GRAPH*2];
			graph->wKey = 3;
			graph->btRgnKey = 2;
			graph->btDataKey = 1;
			graph->btGType = GT_BONG;
			graph->wGKind = GK_VMA;
			graph->wSKind = 1;
			graph->wCalOption = 0;
			graph->rgbLabel = LINCR;

			graph->cInfo.wCOption = vmaFlag;
			graph->cInfo.aline[0].rgbLColor = DEFCR8;
			graph->cInfo.aline[0].btLStyle = PS_SOLID;
			graph->cInfo.aline[0].btLWidth = 1;
			graph->cInfo.aline[1].rgbLColor = DEFCR15;
			graph->cInfo.aline[1].btLStyle = PS_SOLID;
			graph->cInfo.aline[1].btLWidth = 1;
			graph->cInfo.aline[2].rgbLColor = DEFCR14;
			graph->cInfo.aline[2].btLStyle = PS_SOLID;
			graph->cInfo.aline[2].btLWidth = 1;
			graph->cInfo.aline[3].rgbLColor = DEFCR4;
			graph->cInfo.aline[3].btLStyle = PS_SOLID;
			graph->cInfo.aline[3].btLWidth = 1;
			graph->cInfo.aline[4].rgbLColor = MC5;
			graph->cInfo.aline[4].btLStyle = PS_SOLID;
			graph->cInfo.aline[4].btLWidth = 1;
			graph->cInfo.aline[5].rgbLColor = MC6;
			graph->cInfo.aline[5].btLStyle = PS_SOLID;
			graph->cInfo.aline[5].btLWidth = 1;
			graph->cInfo.aline[6].rgbLColor = MC7;
			graph->cInfo.aline[6].btLStyle = PS_SOLID;
			graph->cInfo.aline[6].btLWidth = 1;
			graph->cInfo.aline[7].rgbLColor = MC8;
			graph->cInfo.aline[7].btLStyle = PS_SOLID;
			graph->cInfo.aline[7].btLWidth = 1;

			for (int ii = 0; ii < 4; ii++)
			{
				if (m_aiVMA[ii])
					graph->cInfo.awValue[ii] = m_aiVMA[ii];
			}
		}
		break;
	case 4:	// bong, pma, vol, vma
		graph = (struct _graph *)&pcBuf[SZ_REGION*iRCnt + SZ_GRAPH];
		graph->wKey = 2;
		graph->btRgnKey = 1;
		graph->btDataKey = 1;
		graph->btGType = GT_BONG;
		graph->wGKind = GK_PMA;
		graph->wSKind = 1;
		graph->wCalOption = 0;
		graph->rgbLabel = LINCR;

		graph->cInfo.wCOption = pmaFlag;
		graph->cInfo.aline[0].rgbLColor = DEFCR8;
		graph->cInfo.aline[0].btLStyle = PS_SOLID;
		graph->cInfo.aline[0].btLWidth = 1;
		graph->cInfo.aline[1].rgbLColor = DEFCR15;
		graph->cInfo.aline[1].btLStyle = PS_SOLID;
		graph->cInfo.aline[1].btLWidth = 1;
		graph->cInfo.aline[2].rgbLColor = DEFCR14;
		graph->cInfo.aline[2].btLStyle = PS_SOLID;
		graph->cInfo.aline[2].btLWidth = 1;
		graph->cInfo.aline[3].rgbLColor = DEFCR4;
		graph->cInfo.aline[3].btLStyle = PS_SOLID;
		graph->cInfo.aline[3].btLWidth = 1;
		graph->cInfo.aline[4].rgbLColor = MC5;
		graph->cInfo.aline[4].btLStyle = PS_SOLID;
		graph->cInfo.aline[4].btLWidth = 1;
		graph->cInfo.aline[5].rgbLColor = MC6;
		graph->cInfo.aline[5].btLStyle = PS_SOLID;
		graph->cInfo.aline[5].btLWidth = 1;
		graph->cInfo.aline[6].rgbLColor = MC7;
		graph->cInfo.aline[6].btLStyle = PS_SOLID;
		graph->cInfo.aline[6].btLWidth = 1;
		graph->cInfo.aline[7].rgbLColor = MC8;
		graph->cInfo.aline[7].btLStyle = PS_SOLID;
		graph->cInfo.aline[7].btLWidth = 1;

		for (ii = 0; ii < 4; ii++)
		{
			if (m_aiPMA[ii])
				graph->cInfo.awValue[ii] = m_aiPMA[ii];
		}
		////////////////////////////////////////////////////////////////
		graph = (struct _graph *)&pcBuf[SZ_REGION*iRCnt + SZ_GRAPH*2];
		graph->wKey = 3;
		graph->btRgnKey = 2;
		graph->btDataKey = 1;
		graph->btGType = GT_BONG;
		graph->wGKind = GK_VOL;
		graph->wSKind = 1;
		graph->wCalOption = GC_VOLVOL;
		graph->rgbLabel = LINCR;

		graph->cInfo.aline[0].rgbLColor = VOLCR;
		graph->cInfo.aline[0].btLStyle = PS_SOLID;
		graph->cInfo.aline[0].btLWidth = 1;
		graph->cInfo.aline[1].rgbLColor = BUPCR;
		graph->cInfo.aline[1].btLStyle = PS_SOLID;
		graph->cInfo.aline[1].btLWidth = 1;
		graph->cInfo.aline[2].rgbLColor = BDNCR;
		graph->cInfo.aline[2].btLStyle = PS_SOLID;
		graph->cInfo.aline[2].btLWidth = 1;
		///////////////////////////////////////////////////////////////
		graph = (struct _graph *)&pcBuf[SZ_REGION*iRCnt + SZ_GRAPH*3];
		graph->wKey = 4;
		graph->btRgnKey = 2;
		graph->btDataKey = 1;
		graph->btGType = GT_BONG;
		graph->wGKind = GK_VMA;
		graph->wSKind = 1;
		graph->wCalOption = 0;
		graph->rgbLabel = LINCR;

		graph->cInfo.wCOption = vmaFlag;
		graph->cInfo.aline[0].rgbLColor = DEFCR8;
		graph->cInfo.aline[0].btLStyle = PS_SOLID;
		graph->cInfo.aline[0].btLWidth = 1;
		graph->cInfo.aline[1].rgbLColor = DEFCR15;
		graph->cInfo.aline[1].btLStyle = PS_SOLID;
		graph->cInfo.aline[1].btLWidth = 1;
		graph->cInfo.aline[2].rgbLColor = DEFCR14;
		graph->cInfo.aline[2].btLStyle = PS_SOLID;
		graph->cInfo.aline[2].btLWidth = 1;
		graph->cInfo.aline[3].rgbLColor = DEFCR4;
		graph->cInfo.aline[3].btLStyle = PS_SOLID;
		graph->cInfo.aline[3].btLWidth = 1;
		graph->cInfo.aline[4].rgbLColor = MC5;
		graph->cInfo.aline[4].btLStyle = PS_SOLID;
		graph->cInfo.aline[4].btLWidth = 1;
		graph->cInfo.aline[5].rgbLColor = MC6;
		graph->cInfo.aline[5].btLStyle = PS_SOLID;
		graph->cInfo.aline[5].btLWidth = 1;
		graph->cInfo.aline[6].rgbLColor = MC7;
		graph->cInfo.aline[6].btLStyle = PS_SOLID;
		graph->cInfo.aline[6].btLWidth = 1;
		graph->cInfo.aline[7].rgbLColor = MC8;
		graph->cInfo.aline[7].btLStyle = PS_SOLID;
		graph->cInfo.aline[7].btLWidth = 1;

		for (ii = 0; ii < 4; ii++)
		{
			if (m_aiVMA[ii])
				graph->cInfo.awValue[ii] = m_aiVMA[ii];
		}
		break;
	default:
		break;
	}

	for (ii = 1; ii < MAX_INDEX - 1; ii++)
		CopyMemory(&pcBuf[iLen*ii], pcBuf, iLen);
	CopyMemory(&pcBuf[iLen * (MAX_INDEX-1)], pcBuf, SZ_REGION*iRCnt);

	// 틱차트에서 ma제거
	int	iRealIdx = 0;
	for (int jj = 0; jj < iGCnt; jj++)
	{
		graph = (struct _graph *)&pcBuf[SZ_REGION*iRCnt + SZ_GRAPH*jj];
		if (graph->wGKind == GK_PMA || graph->wGKind == GK_VMA)
			continue;
		
		CopyMemory(&pcBuf[iLen * (MAX_INDEX-1) + SZ_REGION*iRCnt + iRealIdx*SZ_GRAPH],
			graph, SZ_GRAPH);
		iRealIdx++;
	}	
	

	int iDataSize = iLen * (MAX_INDEX - 1) + SZ_REGION * iRCnt + iRealIdx * SZ_GRAPH;
	CSavedHead sh;
	char* pcGrp = sh.Make(VERSION_GRP, 1, iDataSize);
	CopyMemory(pcGrp, pcBuf, iDataSize);
	sh.Write(fname);

	if (!bname.IsEmpty())
		sh.Write(bname);

	delete pcBuf;
}

/*****/
// n : file name
// r : request count
// d : display count
// t : draw tick - 0x100(256):left, 0x200(512):right
// j : bong type - JPN:1, BAR:2, LIN:3, POLE:4
// v : volume chart
// o : outline
// i : data index - 1:일, 2:주, 3:월, 4:분, 5:틱
// u : data unit - 1:종목, 2:업종, 3:선물, 4:업종, 5:해외
// y : chart useage - 1:일반, 2:시간선택
// p : pma
// g : vma
// k : map link
/*****/

void  CDataChk::GetCntInfo(int &rcnt, int &gcnt, int &realGCnt)
{
	if (m_bVol)
	{
		rcnt = 2;
		realGCnt = 2;
		if (m_iPMACnt && m_iVMACnt)		gcnt = 4;
		else if (!m_iPMACnt && !m_iVMACnt)	gcnt = 2;
		else					gcnt = 3;
	}
	else
	{
		rcnt = 1;
		realGCnt = 1;
		if (m_iPMACnt)	gcnt = 2;
		else		gcnt = 1;
	}
}

void  CDataChk::ParseParam(CString options)
{
	CString	sParam;
	sParam.Format("%s", options);

	CString	sTmp, sToken;
	int	nPos = 0;

	// file name
	sToken = "/n";	nPos = sParam.Find(sToken, 0);
	if (nPos >= 0)
	{
		int index = sParam.Find("/", nPos+1);
		sTmp = sParam.Mid(nPos+2, index - nPos - 2);
		m_strFileName.Format("%s", sTmp);
	}
	if (m_strFileName.IsEmpty())	m_strFileName = _T("C_Total");

	// request data count
	m_iTickDisplay = DO_DISPRT;
	m_iBongKind = GK_JPN;
	m_bVol = true;

	CheckType();

	m_iPMACnt = m_iVMACnt = 0;
	ZeroMemory(m_aiPMA, sizeof(m_aiPMA));
	ZeroMemory(m_aiVMA, sizeof(m_aiVMA));
	for (int ii = 0; ii < 4; ii++)
	{
		sToken.Format("/m%d", ii+1);
		nPos = sParam.Find(sToken, 0);
		if (nPos < 0)	
			continue;

		sTmp= sParam.Mid(nPos + 3);
		int mVal = atoi(sTmp);

		if (mVal > 0)
			m_aiPMA[m_iPMACnt++] = mVal;

		sToken.Format("/g%d", ii+1);
		nPos = sParam.Find(sToken, 0);
		if (nPos < 0)	
			continue;

		sTmp= sParam.Mid(nPos + 3);
		mVal = atoi(sTmp);

		if (mVal > 0)
			m_aiVMA[m_iVMACnt++] = mVal;
	}

}

void CDataChk::CheckType()
{
	m_iBongKind = GK_JPN;
	switch (m_mType)
	{
	case MT_SINGLE:
		m_iDtUnit = GU_CODE;
		m_iBongKind = GK_JPN;
		switch (m_mKey)
		{
		case 1:
			m_iDtIndex = GI_DAY;
			break;
		case 2:
			m_iDtIndex = GI_WEEK;
			break;
		case 3:
			m_iDtIndex = GI_MONTH;
			break;
		case 7:
			m_iDtIndex = GI_TICK;
			break;
		case 8:
			m_iDtIndex = GI_MINUTE;
			m_mGap = 1;
			break;
		case 9:
			m_iDtIndex = GI_MINUTE;
			m_mGap = 5;
			break;
		case 13:
			m_iDtIndex = GI_MINUTE;
			m_mGap = 10;
			break;
		case 14:
			m_iDtIndex = GI_MINUTE;
			m_mGap = 30;
			break;
		case 15:
			m_iDtIndex = GI_MINUTE;
			m_mGap = 60;
			break;
		default:
			m_iDtIndex = GI_DAY;
			break;
		}
		break;
	case MT_MULTI:
		m_iDtIndex = GI_DAY;
		m_iDtUnit = GU_CODE;
		break;
	case MT_MONITOR:
		m_iDtIndex = GI_DAY;
		switch (m_mKey)
		{
		case 1:
			m_iDtIndex = GI_MINUTE;
			m_iDtUnit = GU_CODE;
			break;
		case 2:
			m_iDtIndex = GI_DAY;
			m_iDtUnit = GU_CODE;
			break;
		case 3:
			m_iDtIndex = GI_MONTH;
			m_iDtUnit = GU_CODE;
			break;
		case 7:
		case 8:
			m_iDtUnit = GU_INDEX;	
			break;
		case 9:
			m_iDtUnit = GU_FUTURE;	
			break;
		case 13:
			m_iDtUnit = GU_INDEX;	
			break;
		case 14:	case 15:	// 테마, 투자자별
			break;
		}
		break;
	case MT_FOREIGN:
		m_iDtIndex = GI_DAY;
		switch (m_mKey)
		{
		case 1:	
		case 2:
			m_iDtUnit = GU_INDEX;	
			break;
		case 3:
			m_iDtUnit = GU_FUTURE;	
			break;
		case 7:
		case 8:
		case 9:
		case 13:
		case 14:
		case 15:
			m_iDtUnit = GU_FOREIGN;	
			break;
		}
		break;
	}
}

int CDataChk::GetPalette(int index)
{
	return m_pwndMain->SendMessage(WM_USER, MAKEWORD(getPALETTE, 0), (LPARAM)index);
}

void CDataChk::InitInfo(struct _cntInfo *cntInfo, char *pData)
{
	int	count = sizeof(basicInfo)/sizeof(basicInfo[0]);
	struct _graph	*graph;
	struct _basicInfo	*bInfo;
	for (int ii = 0; ii < count; ii++)
	{
		bInfo = (struct _basicInfo*)&basicInfo[ii];
		graph = (struct _graph*)&pData[SZ_GRAPH*ii];

		graph->wKey = 1;
		graph->btDataKey = 1;
		graph->btGType = bInfo->btType;
		graph->wGKind = bInfo->wGrpKind;
		graph->wSKind = 1;
		graph->wCalOption = bInfo->wCOption;
		graph->dwDraOption = bInfo->dwDOption;
		graph->rgbLabel = LINCR;
		CopyMemory(&graph->cInfo, &bInfo->chartInfo, SZ_CHARTINFO);
		CopyMemory(&graph->tInfo, &bInfo->tickInfo, SZ_TICKINFO);
	}
}