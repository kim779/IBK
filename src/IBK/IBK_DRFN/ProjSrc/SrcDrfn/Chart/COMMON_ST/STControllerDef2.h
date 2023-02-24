
#ifndef __STDLLOPERATOR_DEF__BYVSR
#define __STDLLOPERATOR_DEF__BYVSR

// 강제청산에 대한 매크로 추가
// 기존의 STControllerDef.h 에 추가하지 않은 이유는
// 수정할 수 없는 DLL(STDllOperator.dll)에서 참조하고 있기 때문

// 매수진입에 대한 강제청산
//#define FL_BUY_LOSSRATE				(0x00000300L)
//#define FL_BUY_TARGETBENEFIT		(0x00000400L)
//#define FL_BUY_HPRICECPBEAR			(0x00000500L)
//#define FL_BUY_LPRICECPBULL			(0x00000600L)
//#define FL_BUY_TARGETVALUEPRESERVE	(0x00000700L)
//#define FL_BUY_BENEFITPRESERVE		(0x00000800L)
//#define FL_BUY_MINIPRICE			(0x00000900L)
//#define FL_BUY_DAYLIQUIDATION		(0x00000A00L)

#define FL_BUY_LOSSRATE				(0x00000100L)
#define FL_BUY_TARGETBENEFIT		(0x00000200L)
#define FL_BUY_HPRICECPBEAR			(0x00000400L)
#define FL_BUY_LPRICECPBULL			(0x00000800L)
#define FL_BUY_TARGETVALUEPRESERVE	(0x00001000L)
#define FL_BUY_BENEFITPRESERVE		(0x00002000L)
#define FL_BUY_MINIPRICE			(0x00004000L)
#define FL_BUY_DAYLIQUIDATION		(0x00008000L)

// 매도진입에 대한 강제청산
//#define FL_SELL_LOSSRATE			(0x00003000L)
//#define FL_SELL_TARGETBENEFIT		(0x00004000L)
//#define FL_SELL_HPRICECPBEAR		(0x00005000L)
//#define FL_SELL_LPRICECPBULL		(0x00006000L)
//#define FL_SELL_TARGETVALUEPRESERVE	(0x00007000L)
//#define FL_SELL_BENEFITPRESERVE		(0x00008000L)
//#define FL_SELL_MINIPRICE			(0x00009000L)
//#define FL_SELL_DAYLIQUIDATION		(0x0000A000L)

#define FL_SELL_LOSSRATE			(0x00010000L)
#define FL_SELL_TARGETBENEFIT		(0x00020000L)
#define FL_SELL_HPRICECPBEAR		(0x00040000L)
#define FL_SELL_LPRICECPBULL		(0x00080000L)
#define FL_SELL_TARGETVALUEPRESERVE	(0x00100000L)
#define FL_SELL_BENEFITPRESERVE		(0x00200000L)
#define FL_SELL_MINIPRICE			(0x00400000L)
#define FL_SELL_DAYLIQUIDATION		(0x00800000L)

#endif // __STDLLOPERATOR_DEF__BYVSR
