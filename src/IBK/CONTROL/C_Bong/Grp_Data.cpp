// Grp_Data.cpp: implementation of the CGrp_Data class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "C_Bong.h"
#include "Grp_Data.h"
#include "GrpWnd.h"
#include "../../h/axiscgrp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGrp_Data::CGrp_Data(class CGrpWnd *pGrpWnd, int dKind, int dKey, int dIndex)
{
	m_pGrpWnd = pGrpWnd;
	m_dKind = dKind;
	m_dKey = dKey;
	m_dIndex = dIndex;
	m_szFrame = sz_cgBong;
}

CGrp_Data::~CGrp_Data()
{
	_vData.clear();
}

int CGrp_Data::AttachGraphData(char* data, int count, int mgap)
{
	m_dGap = mgap;
	const gsl::span<struct _cdBong> spanData((struct _cdBong*)data, count);
	for_each(spanData.begin(), spanData.end(), [&](const auto cdBong) {	
		auto& cgBong = _vData.emplace_back(std::make_unique<struct _cgBong>());
		cgBong->epr = CharToInt(cdBong.epr, sizeof(cdBong.epr));
		cgBong->fpr = CharToInt(cdBong.fpr, sizeof(cdBong.fpr));
		cgBong->hpr = CharToInt(cdBong.hpr, sizeof(cdBong.hpr));
		cgBong->lpr = CharToInt(cdBong.lpr, sizeof(cdBong.lpr));
		cgBong->trn = CharToDouble(cdBong.trn, sizeof(cdBong.trn));
		cgBong->index.date.yy = short(CharToInt(&cdBong.date[0], 4));
		cgBong->index.date.mm = unsigned char(CharToInt(&cdBong.date[4], 2));
		cgBong->index.date.dd = unsigned char(CharToInt(&cdBong.date[6], 2));
		cgBong->index.time.hh = unsigned char(CharToInt(&cdBong.date[8], 2));
		cgBong->index.time.mm = unsigned char(CharToInt(&cdBong.date[10], 2));
		cgBong->index.time.ss = unsigned char(CharToInt(&cdBong.date[12], 2));	
	});
	return sz_cdBong;
}

bool CGrp_Data::UpdateRTM()
{
	if (_vData.size() < 1)
		return false;

	bool	bResponse = false;
	char	indexRTM[16]{};
	int	checkGAP{};
	int	hhRTM{}, mmRTM{}, ssRTM{};

	const int endIDX = gsl::narrow_cast<int>(_vData.size() - 1);

	bool	bCreate = false;
	sprintf(indexRTM, "%s", m_pGrpWnd->m_ctim.GetString());
	switch (m_dIndex)
	{
	case CDI_DAY:
	case CDI_WEEK:
	case CDI_MON:
		if (strlen(indexRTM) != 6)
			return bResponse;
		break;
	case CDI_MIN:
	{
		if (strlen(indexRTM) != 6)
			return bResponse;

		hhRTM = unsigned char(CharToInt(&indexRTM[0], 2));
		mmRTM = unsigned char(CharToInt(&indexRTM[2], 2));
		ssRTM = unsigned char(CharToInt(&indexRTM[4], 2));

		//gBong = (struct _cgBong *)m_DataQue.GetAt(endIDX);
		auto& gBong = _vData.at(endIDX);
		checkGAP = (hhRTM - gBong->index.time.hh) * 3600;
		checkGAP += (mmRTM - gBong->index.time.mm) * 60;
		checkGAP += (ssRTM - gBong->index.time.ss);

		if (checkGAP < 0 || m_dGap <= checkGAP)
			bCreate = true;
	}
		break;
	case CDI_TICK:
		hhRTM = unsigned char(CharToInt(&indexRTM[0], 2));
		mmRTM = unsigned char(CharToInt(&indexRTM[2], 2));
		ssRTM = unsigned char(CharToInt(&indexRTM[4], 2));

		bCreate = true;
		break;
	default:
		return bResponse;
	}

	char*	pData = (char *) 0;

	auto& gBong = bCreate ? _vData.emplace_back(std::make_unique<struct _cgBong>()) : *(_vData.rbegin());
	auto& gLastBong = *(_vData.rbegin());


	switch (m_dIndex)
	{
	case CDI_TICK:
		gBong->fpr = gBong->hpr = gBong->lpr = gBong->epr = atoi(m_pGrpWnd->m_jgga);
		gBong->trn = atoi(m_pGrpWnd->m_gvol);
		gBong->index.date.yy = m_yy;
		gBong->index.date.mm = m_mm;
		gBong->index.date.dd = m_dd;
		gBong->index.time.hh = hhRTM;
		gBong->index.time.mm = mmRTM;
		gBong->index.time.ss = ssRTM;

		bResponse = true;
		break;
	case CDI_MIN:
		if (bCreate)
		{
			gBong->fpr = gBong->hpr = gBong->lpr = gBong->epr = atoi(m_pGrpWnd->m_jgga);
			gBong->trn = atoi(m_pGrpWnd->m_gvol);
			gBong->index.date.yy = m_yy;
			gBong->index.date.mm = m_mm;
			gBong->index.date.dd = m_dd;
			
			int	hh{}, mm{};
			GetTime(m_dGap, gLastBong->index.time.hh, gLastBong->index.time.mm,
				hhRTM, mmRTM, hh, mm);
			gBong->index.time.hh = hh;
			gBong->index.time.mm = mm;
			if (m_dGap >= 60 || ssRTM < 30)
				gBong->index.time.ss = 0;
			else
				gBong->index.time.ss = 30;
		}
		else
		{
			const int	jgga = atoi(m_pGrpWnd->m_jgga);
			gLastBong->epr = jgga;
			if (gLastBong->lpr > jgga)	gLastBong->lpr = jgga;
			if (gLastBong->hpr < jgga)	gLastBong->hpr = jgga;
			gLastBong->trn += atof(m_pGrpWnd->m_gvol);
		}
		break;
	case CDI_DAY:
		if (m_pGrpWnd->m_siga.IsEmpty())
		{
			const int	jgga = atoi(m_pGrpWnd->m_jgga);
			if (gLastBong->lpr > jgga)	gLastBong->lpr = jgga;
			if (gLastBong->hpr < jgga)	gLastBong->hpr = jgga;
		}
		else
		{
			gLastBong->fpr = atoi(m_pGrpWnd->m_siga);
			gLastBong->lpr = atoi(m_pGrpWnd->m_jega);
			gLastBong->hpr = atoi(m_pGrpWnd->m_koga);
		}
		gLastBong->epr = atoi(m_pGrpWnd->m_jgga);
		gLastBong->trn = atof(m_pGrpWnd->m_gvol);
		break;
	default:
		{
		const int	jgga = atoi(m_pGrpWnd->m_jgga);
			gLastBong->epr = jgga;
			if (gLastBong->lpr > jgga)	gLastBong->lpr = jgga;
			if (gLastBong->hpr < jgga)	gLastBong->hpr = jgga;
			gLastBong->trn += atof(m_pGrpWnd->m_gvol);
		}
		break;
	}

	// insert new data at last index
	if (bCreate)
	{
		_vData.erase(_vData.begin());
		bResponse = true;
	}

	return bResponse;
}


struct _cgBong* CGrp_Data::GetGraphData(int index)
{
	if (index < 0 || index > gsl::narrow_cast<int>(_vData.size() - 1) )
		return nullptr;

	return _vData.at(index).get();
}

void CGrp_Data::SetDate(char* pDate)
{
	m_yy = short(CharToInt(&pDate[0], 4));
	m_mm = unsigned char(CharToInt(&pDate[4], 2));
	m_dd = unsigned char(CharToInt(&pDate[6], 2));
}

int CGrp_Data::CharToInt(const char* cnvB, int cnvL)
{
	return atoi(CString(cnvB, cnvL));
}

double CGrp_Data::CharToDouble(const char* cnvB, int cnvL)
{
	return atof(CString(cnvB, cnvL));
}

void CGrp_Data::GetTime(int sec, int pHH, int pMM, int cHH, int cMM, int &nHH, int &nMM)
{
	if (sec <= 30)	// 30초봉
	{
		nHH = cHH;
		nMM = cMM;
		return;
	}
	const int	min = sec/60;

	const int	pTime = pHH*60 + pMM;
	const int	cTime = cHH*60 + cMM;
	const int	Gap = cTime - pTime;

	if (Gap <= 0)	// 마지막 데이터가 하루전 데이터
	{
		nHH = cHH;
		nMM = cMM;
		return;	
	}

	const int	nTerm = Gap / min;
	pMM += nTerm * min;

	nHH = pHH + pMM / 60;
	nMM = pMM % 60;
}
