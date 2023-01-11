// Grp_Data.h: interface for the CGrp_Data class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include <afxtempl.h>

class CGrp_Data  
{
public:
	CGrp_Data(class CGrpWnd *pGrpWnd, int dKind, int dKey, int dIndex);
	virtual ~CGrp_Data();

public:
	int	AttachGraphData(char* data, int count, int mgap);
	bool	UpdateRTM();
	struct _cgBong*	GetGraphData(int index);
	int	GetDataGap() { return m_dGap; }
	size_t	GetDataCount() { return _vData.size(); }
	void	SetDate(char* pDate);
	static int	CharToInt(const char* cnvB, int cnvL);

public:
	int	m_dKind{};
	int	m_dKey{};
	int	m_dIndex{};
	int	m_dGap{};
	int	m_szFrame{};			// Frame Size (1 Que Size)

private:
	inline	double	CharToDouble(const char* cnvB, int cnvL);
	void	GetTime(int min, int pHH, int pMM, int cHH, int cMM, int &nHH, int &nMM);

private:
	class CGrpWnd* m_pGrpWnd{};
	std::vector<std::unique_ptr<struct _cgBong>> _vData;


	short		m_yy{};	// year
	unsigned char	m_mm{};	// month
	unsigned char	m_dd{};	// day
};
