#if !defined(AFX_KB_01230__H_B8898524_2F02_4517_AC5A_E782C176A44F_INCLUDED_)
#define AFX_KB_01230__H_B8898524_2F02_4517_AC5A_E782C176A44F_INCLUDED_

#include "Data_Common.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
//// �ֽ�ȣ��5����ȸ(01230) ( 01230,block,attr,headtype=A )
// �ֽ�ȣ����ȸ(c1002) ( c1002,block,attr,headtype=A )
#pragma pack( push, 1 )

#define NAME_01230     "c1002"

// �⺻�Է�
typedef struct _k01230In1
{
    char    shcode              [   6];    char    _shcode              ;    // [string,    6] �����ڵ�
} k01230In1, *LPk01230In1;
#define NAME_k01230In1     "k01230In1"

// ��� List
typedef struct _k01230Out1
{
//    char    hname               [  20];    char    _hname               ;    // [string,   20] �����
//    char    price               [   8];    char    _price               ;    // [long  ,    8] ���簡
//    char    sign                [   1];    char    _sign                ;    // [string,    1] ��񱸺�
//    char    change              [   8];    char    _change              ;    // [long  ,    8] ���
//    char    rate                [   7];    char    _rate                ;    // [float ,  7.2] �����
//    char    volume              [  12];    char    _volume              ;    // [float ,   12] �ŷ���
//    char    volrate             [   7];    char    _volrate             ;    // [float ,  7.2] ���ϰŷ������
//    char    offerho             [   8];    char    _offerho             ;    // [long  ,    8] �켱�ŵ�ȣ��
//    char    bidho               [   8];    char    _bidho               ;    // [long  ,    8] �켱�ż�ȣ��
//    char    fholdvol            [  12];    char    _fholdvol            ;    // [float ,   12] �ܱ��κ�������
//    char    exhratio            [   6];    char    _exhratio            ;    // [float ,  6.2] �ܱ��κ�������
//    char    hotime              [   6];    char    _hotime              ;    // [string,    6] ȣ�����Žð�
//    char    offerho1            [   8];    char    _offerho1            ;    // [long  ,    8] �ŵ�ȣ��1
//    char    offerrem1           [   8];    char    _offerrem1           ;    // [long  ,    8] �ŵ�ȣ������1
//    char    preoffercha1        [   8];    char    _preoffercha1        ;    // [long  ,    8] �ŵ�����������1
//    char    offerho2            [   8];    char    _offerho2            ;    // [long  ,    8] �ŵ�ȣ��2
//    char    offerrem2           [   8];    char    _offerrem2           ;    // [long  ,    8] �ŵ�ȣ������2
//    char    preoffercha2        [   8];    char    _preoffercha2        ;    // [long  ,    8] �ŵ�����������2
//    char    offerho3            [   8];    char    _offerho3            ;    // [long  ,    8] �ŵ�ȣ��3
//    char    offerrem3           [   8];    char    _offerrem3           ;    // [long  ,    8] �ŵ�ȣ������3
//    char    preoffercha3        [   8];    char    _preoffercha3        ;    // [long  ,    8] �ŵ�����������3
//    char    offerho4            [   8];    char    _offerho4            ;    // [long  ,    8] �ŵ�ȣ��4
//    char    offerrem4           [   8];    char    _offerrem4           ;    // [long  ,    8] �ŵ�ȣ������4
//    char    preoffercha4        [   8];    char    _preoffercha4        ;    // [long  ,    8] �ŵ�����������4
//    char    offerho5            [   8];    char    _offerho5            ;    // [long  ,    8] �ŵ�ȣ��5
//    char    offerrem5           [   8];    char    _offerrem5           ;    // [long  ,    8] �ŵ�ȣ������5
//    char    preoffercha5        [   8];    char    _preoffercha5        ;    // [long  ,    8] �ŵ�����������5
//    char    bidho1              [   8];    char    _bidho1              ;    // [long  ,    8] �ż�ȣ��1
//    char    bidrem1             [   8];    char    _bidrem1             ;    // [long  ,    8] �ż�ȣ������1
//    char    prebidcha1          [   8];    char    _prebidcha1          ;    // [long  ,    8] �ż�����������1
//    char    bidho2              [   8];    char    _bidho2              ;    // [long  ,    8] �ż�ȣ��2
//    char    bidrem2             [   8];    char    _bidrem2             ;    // [long  ,    8] �ż�ȣ������2
//    char    prebidcha2          [   8];    char    _prebidcha2          ;    // [long  ,    8] �ż�����������2
//    char    bidho3              [   8];    char    _bidho3              ;    // [long  ,    8] �ż�ȣ��3
//    char    bidrem3             [   8];    char    _bidrem3             ;    // [long  ,    8] �ż�ȣ������3
//    char    prebidcha3          [   8];    char    _prebidcha3          ;    // [long  ,    8] �ż�����������3
//    char    bidho4              [   8];    char    _bidho4              ;    // [long  ,    8] �ż�ȣ��4
//    char    bidrem4             [   8];    char    _bidrem4             ;    // [long  ,    8] �ż�ȣ������4
//    char    prebidcha4          [   8];    char    _prebidcha4          ;    // [long  ,    8] �ż�����������4
//    char    bidho5              [   8];    char    _bidho5              ;    // [long  ,    8] �ż�ȣ��5
//    char    bidrem5             [   8];    char    _bidrem5             ;    // [long  ,    8] �ż�ȣ������5
//    char    prebidcha5          [   8];    char    _prebidcha5          ;    // [long  ,    8] �ż�����������5
//    char    totofferrem         [   8];    char    _totofferrem         ;    // [long  ,    8] �ŵ�ȣ���Ѽ���
//    char    preoffercha         [   8];    char    _preoffercha         ;    // [long  ,    8] �ŵ�ȣ���Ѽ����������
//    char    totbidrem           [   8];    char    _totbidrem           ;    // [long  ,    8] �ż�ȣ���Ѽ���
//    char    prebidcha           [   8];    char    _prebidcha           ;    // [long  ,    8] �ż�ȣ���Ѽ����������
//    char    yeprice             [   8];    char    _yeprice             ;    // [long  ,    8] ����ü�ᰡ��
//    char    yevolume            [   8];    char    _yevolume            ;    // [long  ,    8] ����ü�����
//    char    jnilysign           [   1];    char    _jnilysign           ;    // [string,    1] ����ü�ᰡ����������񱸺�
//    char    jnilychange         [   8];    char    _jnilychange         ;    // [long  ,    8] ����ü�ᰡ�����������
//    char    yerate              [   6];    char    _yerate              ;    // [float ,  6.2] ��������
//    char    tmofferrem          [   8];    char    _tmofferrem          ;    // [long  ,    8] �ð��ܸŵ��ܷ�
//    char    tmbidrem            [   8];    char    _tmbidrem            ;    // [long  ,    8] �ð��ܸż��ܷ�
//    char    ho_status           [   1];    char    _ho_status           ;    // [long  ,    1] �屸��
//    char    recprice            [   8];    char    _recprice            ;    // [long  ,    8] ���ذ�
//    char    uplmtprice          [   8];    char    _uplmtprice          ;    // [long  ,    8] ���Ѱ�
//    char    dnlmtprice          [   8];    char    _dnlmtprice          ;    // [long  ,    8] ���Ѱ�
//    char    open                [   8];    char    _open                ;    // [long  ,    8] �ð�
//    char    high                [   8];    char    _high                ;    // [long  ,    8] ����
//    char    low                 [   8];    char    _low                 ;    // [long  ,    8] ����
//    char    trade_cost          [   8];    char    _trade_cost          ;    // [long  ,    8] �ŷ����
    char    hname               [  20];    char    _hname               ;    // [string,   20] �����
    char    price               [   8];    char    _price               ;    // [long  ,    8] ���簡
    char    sign                [   1];    char    _sign                ;    // [string,    1] ��񱸺�
    char    change              [   8];    char    _change              ;    // [long  ,    8] ���
    char    rate                [   7];    char    _rate                ;    // [float ,  7.2] �����
    char    volume              [  12];    char    _volume              ;    // [float ,   12] �ŷ���
    char    volrate             [   7];    char    _volrate             ;    // [float ,  7.2] ���ϰŷ������
    char    offerho             [   8];    char    _offerho             ;    // [long  ,    8] �켱�ŵ�ȣ��
    char    bidho               [   8];    char    _bidho               ;    // [long  ,    8] �켱�ż�ȣ��
    char    fholdvol            [  12];    char    _fholdvol            ;    // [float ,   12] �ܱ��κ�������
    char    exhratio            [   6];    char    _exhratio            ;    // [float ,  6.2] �ܱ��κ�������
    char    hotime              [   6];    char    _hotime              ;    // [string,    6] ȣ�����Žð�
    char    offerho1            [   8];    char    _offerho1            ;    // [long  ,    8] �ŵ�ȣ��1
    char    offerrem1           [   8];    char    _offerrem1           ;    // [long  ,    8] �ŵ�ȣ������1
    char    preoffercha1        [   8];    char    _preoffercha1        ;    // [long  ,    8] �ŵ�����������1
    char    offerho2            [   8];    char    _offerho2            ;    // [long  ,    8] �ŵ�ȣ��2
    char    offerrem2           [   8];    char    _offerrem2           ;    // [long  ,    8] �ŵ�ȣ������2
    char    preoffercha2        [   8];    char    _preoffercha2        ;    // [long  ,    8] �ŵ�����������2
    char    offerho3            [   8];    char    _offerho3            ;    // [long  ,    8] �ŵ�ȣ��3
    char    offerrem3           [   8];    char    _offerrem3           ;    // [long  ,    8] �ŵ�ȣ������3
    char    preoffercha3        [   8];    char    _preoffercha3        ;    // [long  ,    8] �ŵ�����������3
    char    offerho4            [   8];    char    _offerho4            ;    // [long  ,    8] �ŵ�ȣ��4
    char    offerrem4           [   8];    char    _offerrem4           ;    // [long  ,    8] �ŵ�ȣ������4
    char    preoffercha4        [   8];    char    _preoffercha4        ;    // [long  ,    8] �ŵ�����������4
    char    offerho5            [   8];    char    _offerho5            ;    // [long  ,    8] �ŵ�ȣ��5
    char    offerrem5           [   8];    char    _offerrem5           ;    // [long  ,    8] �ŵ�ȣ������5
    char    preoffercha5        [   8];    char    _preoffercha5        ;    // [long  ,    8] �ŵ�����������5
    char    offerho6            [   8];    char    _offerho6            ;    // [long  ,    8] �ŵ�ȣ��6
    char    offerrem6           [   8];    char    _offerrem6           ;    // [long  ,    8] �ŵ�ȣ������6
    char    preoffercha6        [   8];    char    _preoffercha6        ;    // [long  ,    8] �ŵ�����������6
    char    offerho7            [   8];    char    _offerho7            ;    // [long  ,    8] �ŵ�ȣ��7
    char    offerrem7           [   8];    char    _offerrem7           ;    // [long  ,    8] �ŵ�ȣ������7
    char    preoffercha7        [   8];    char    _preoffercha7        ;    // [long  ,    8] �ŵ�����������7
    char    offerho8            [   8];    char    _offerho8            ;    // [long  ,    8] �ŵ�ȣ��8
    char    offerrem8           [   8];    char    _offerrem8           ;    // [long  ,    8] �ŵ�ȣ������8
    char    preoffercha8        [   8];    char    _preoffercha8        ;    // [long  ,    8] �ŵ�����������8
    char    offerho9            [   8];    char    _offerho9            ;    // [long  ,    8] �ŵ�ȣ��9
    char    offerrem9           [   8];    char    _offerrem9           ;    // [long  ,    8] �ŵ�ȣ������9
    char    preoffercha9        [   8];    char    _preoffercha9        ;    // [long  ,    8] �ŵ�����������9
    char    offerho10           [   8];    char    _offerho10           ;    // [long  ,    8] �ŵ�ȣ��10
    char    offerrem10          [   8];    char    _offerrem10          ;    // [long  ,    8] �ŵ�ȣ������10
    char    preoffercha10       [   8];    char    _preoffercha10       ;    // [long  ,    8] �ŵ�����������10
    char    bidho1              [   8];    char    _bidho1              ;    // [long  ,    8] �ż�ȣ��1
    char    bidrem1             [   8];    char    _bidrem1             ;    // [long  ,    8] �ż�ȣ������1
    char    prebidcha1          [   8];    char    _prebidcha1          ;    // [long  ,    8] �ż�����������1
    char    bidho2              [   8];    char    _bidho2              ;    // [long  ,    8] �ż�ȣ��2
    char    bidrem2             [   8];    char    _bidrem2             ;    // [long  ,    8] �ż�ȣ������2
    char    prebidcha2          [   8];    char    _prebidcha2          ;    // [long  ,    8] �ż�����������2
    char    bidho3              [   8];    char    _bidho3              ;    // [long  ,    8] �ż�ȣ��3
    char    bidrem3             [   8];    char    _bidrem3             ;    // [long  ,    8] �ż�ȣ������3
    char    prebidcha3          [   8];    char    _prebidcha3          ;    // [long  ,    8] �ż�����������3
    char    bidho4              [   8];    char    _bidho4              ;    // [long  ,    8] �ż�ȣ��4
    char    bidrem4             [   8];    char    _bidrem4             ;    // [long  ,    8] �ż�ȣ������4
    char    prebidcha4          [   8];    char    _prebidcha4          ;    // [long  ,    8] �ż�����������4
    char    bidho5              [   8];    char    _bidho5              ;    // [long  ,    8] �ż�ȣ��5
    char    bidrem5             [   8];    char    _bidrem5             ;    // [long  ,    8] �ż�ȣ������5
    char    prebidcha5          [   8];    char    _prebidcha5          ;    // [long  ,    8] �ż�����������5
    char    bidho6              [   8];    char    _bidho6              ;    // [long  ,    8] �ż�ȣ��6
    char    bidrem6             [   8];    char    _bidrem6             ;    // [long  ,    8] �ż�ȣ������6
    char    prebidcha6          [   8];    char    _prebidcha6          ;    // [long  ,    8] �ż�����������6
    char    bidho7              [   8];    char    _bidho7              ;    // [long  ,    8] �ż�ȣ��7
    char    bidrem7             [   8];    char    _bidrem7             ;    // [long  ,    8] �ż�ȣ������7
    char    prebidcha7          [   8];    char    _prebidcha7          ;    // [long  ,    8] �ż�����������7
    char    bidho8              [   8];    char    _bidho8              ;    // [long  ,    8] �ż�ȣ��8
    char    bidrem8             [   8];    char    _bidrem8             ;    // [long  ,    8] �ż�ȣ������8
    char    prebidcha8          [   8];    char    _prebidcha8          ;    // [long  ,    8] �ż�����������8
    char    bidho9              [   8];    char    _bidho9              ;    // [long  ,    8] �ż�ȣ��9
    char    bidrem9             [   8];    char    _bidrem9             ;    // [long  ,    8] �ż�ȣ������9
    char    prebidcha9          [   8];    char    _prebidcha9          ;    // [long  ,    8] �ż�����������9
    char    bidho10             [   8];    char    _bidho10             ;    // [long  ,    8] �ż�ȣ��10
    char    bidrem10            [   8];    char    _bidrem10            ;    // [long  ,    8] �ż�ȣ������10
    char    prebidcha10         [   8];    char    _prebidcha10         ;    // [long  ,    8] �ż�����������10
    char    totofferrem         [   8];    char    _totofferrem         ;    // [long  ,    8] �ŵ�ȣ���Ѽ���
    char    preoffercha         [   8];    char    _preoffercha         ;    // [long  ,    8] �ŵ�ȣ���Ѽ����������
    char    totbidrem           [   8];    char    _totbidrem           ;    // [long  ,    8] �ż�ȣ���Ѽ���
    char    prebidcha           [   8];    char    _prebidcha           ;    // [long  ,    8] �ż�ȣ���Ѽ����������
    char    yeprice             [   8];    char    _yeprice             ;    // [long  ,    8] ����ü�ᰡ��
    char    yevolume            [   8];    char    _yevolume            ;    // [long  ,    8] ����ü�����
    char    jnilysign           [   1];    char    _jnilysign           ;    // [string,    1] ����ü�ᰡ����������񱸺�
    char    jnilychange         [   8];    char    _jnilychange         ;    // [long  ,    8] ����ü�ᰡ�����������
    char    yerate              [   6];    char    _yerate              ;    // [float ,  6.2] ��������
    char    tmofferrem          [   8];    char    _tmofferrem          ;    // [long  ,    8] �ð��ܸŵ��ܷ�
    char    tmbidrem            [   8];    char    _tmbidrem            ;    // [long  ,    8] �ð��ܸż��ܷ�
    char    ho_status           [   1];    char    _ho_status           ;    // [long  ,    1] �屸��
    char    jnilclose           [   8];    char    _jnilclose           ;    // [long  ,    8] ��������
    char    recprice            [   8];    char    _recprice            ;    // [long  ,    8] ���ذ�
    char    uplmtprice          [   8];    char    _uplmtprice          ;    // [long  ,    8] ���Ѱ�
    char    dnlmtprice          [   8];    char    _dnlmtprice          ;    // [long  ,    8] ���Ѱ�
    char    open                [   8];    char    _open                ;    // [long  ,    8] �ð�
    char    high                [   8];    char    _high                ;    // [long  ,    8] ����
    char    low                 [   8];    char    _low                 ;    // [long  ,    8] ����
    char    trade_cost          [   8];    char    _trade_cost          ;    // [long  ,    8] �ŷ����
    char    pivot               [   8];    char    _pivot               ;    // [long  ,    8] �Ǻ�
    char    recline             [   8];    char    _recline             ;    // [long  ,    8] ���ؼ�
    char    resist1             [   8];    char    _resist1             ;    // [long  ,    8] 1������
    char    resist2             [   8];    char    _resist2             ;    // [long  ,    8] 2������
    char    support1            [   8];    char    _support1            ;    // [long  ,    8] 1������
    char    support2            [   8];    char    _support2            ;    // [long  ,    8] 2������
    char    resist_d            [   8];    char    _resist_d            ;    // [long  ,    8] D����
    char    support_d           [   8];    char    _support_d           ;    // [long  ,    8] D����
    char    parprice            [   8];    char    _parprice            ;    // [long  ,    8] �׸鰡
    char    subprice            [   8];    char    _subprice            ;    // [long  ,    8] ��밡
    char    sigatvalue          [  12];    char    _sigatvalue          ;    // [float ,   12] �ð��Ѿ�
    char    capital             [  12];    char    _capital             ;    // [float ,   12] �ں���
    char    listing             [  12];    char    _listing             ;    // [float ,   12] �����ֽļ�
    char    perx                [   6];    char    _perx                ;    // [float ,  6.2] PER (�ְ����ͺ��� - ����)
    char    pbrx                [   6];    char    _pbrx                ;    // [float ,  6.2] PBR (�ְ����ڻ����)
    char    high52w             [   8];    char    _high52w             ;    // [long  ,    8] 250���ְ���
    char    high52w_rate        [   7];    char    _high52w_rate        ;    // [float ,  7.2] 250���ְ��������
    char    high52wdate         [   8];    char    _high52wdate         ;    // [string,    8] 250���ְ�������
    char    low52w              [   8];    char    _low52w              ;    // [long  ,    8] 250��������
    char    low52w_rate         [   7];    char    _low52w_rate         ;    // [float ,  7.2] 250�������������
    char    low52wdate          [   8];    char    _low52wdate          ;    // [string,    8] 250������������
    char    value               [  15];    char    _value               ;    // [float ,   15] �ŷ����
    char    volro               [   9];    char    _volro               ;    // [float ,  9.2] �ŷ���ȸ����
    char    jnilvolume          [  12];    char    _jnilvolume          ;    // [float ,   12] ���ϰŷ���
} k01230Out1, *LPk01230Out1;
#define NAME_k01230Out1     "k01230Out1"

typedef struct _k01230Out1_Ex
{
	char    price               [   8];
	char    uplmtprice          [   8];
	char    dnlmtprice          [   8];
	char    offerho3            [   8];
	char    offerho2            [   8];
	char    offerho1            [   8];
	char    bidho1              [   8];
	char    bidho2              [   8];
	char    bidho3              [   8];
} k01230Out1_Ex, *LPk01230Out1_Ex;

typedef struct _k01230Out2
{
    char    recprice            [   8];    // [long  ,    8] ���ذ�
    char    yeprice             [   8];    // [long  ,    8] ����ü�ᰡ��
    char    yevolume            [   8];    // [long  ,    8] ����ü�����
    char    hname               [  20];    // [string,   20] �����
    char    price               [   8];    // [long  ,    8] ���簡
    char    sign                [   1];    // [string,    1] ��񱸺�
    char    change              [   8];    // [long  ,    8] ���
    char    rate                [   7];    // [float ,  7.2] �����
    char    volume              [  12];    // [float ,   12] �ŷ���
    char    trade_cost          [   8];    // [long  ,    8] �ŷ����
    char    offerho1            [   8];    // [long  ,    8] �ŵ�ȣ��1
    char    offerho2            [   8];    // [long  ,    8] �ŵ�ȣ��2
    char    offerho3            [   8];    // [long  ,    8] �ŵ�ȣ��3
    char    offerho4            [   8];    // [long  ,    8] �ŵ�ȣ��4
    char    offerho5            [   8];    // [long  ,    8] �ŵ�ȣ��5
    char    offerrem1           [   8];    // [long  ,    8] �ŵ�ȣ������1
    char    offerrem2           [   8];    // [long  ,    8] �ŵ�ȣ������2
    char    offerrem3           [   8];    // [long  ,    8] �ŵ�ȣ������3
    char    offerrem4           [   8];    // [long  ,    8] �ŵ�ȣ������4
    char    offerrem5           [   8];    // [long  ,    8] �ŵ�ȣ������5
    char    bidho1              [   8];    // [long  ,    8] �ż�ȣ��1
    char    bidho2              [   8];    // [long  ,    8] �ż�ȣ��2
    char    bidho3              [   8];    // [long  ,    8] �ż�ȣ��3
    char    bidho4              [   8];    // [long  ,    8] �ż�ȣ��4
    char    bidho5              [   8];    // [long  ,    8] �ż�ȣ��5
    char    bidrem1             [   8];    // [long  ,    8] �ż�ȣ������1
    char    bidrem2             [   8];    // [long  ,    8] �ż�ȣ������2
    char    bidrem3             [   8];    // [long  ,    8] �ż�ȣ������3
    char    bidrem4             [   8];    // [long  ,    8] �ż�ȣ������4
    char    bidrem5             [   8];    // [long  ,    8] �ż�ȣ������5
    char    totofferrem         [   8];    // [long  ,    8] �ŵ�ȣ���Ѽ���
    char    totbidrem           [   8];    // [long  ,    8] �ż�ȣ���Ѽ���
    char    tmofferrem          [   8];    // [long  ,    8] �ð��ܸŵ��ܷ�
    char    tmbidrem            [   8];    // [long  ,    8] �ð��ܸż��ܷ�
    char    uplmtprice          [   8];    // [long  ,    8] ���Ѱ�
    char    dnlmtprice          [   8];    // [long  ,    8] ���Ѱ�
    char    yerate              [   6];    // [float ,  6.2] ��������
    char    high                [   8];    // [long  ,    8] ����
    char    low                 [   8];    // [long  ,    8] ����
    char    volrate             [   7];    // [float ,  7.2] ���ϰŷ������
	char	jnilysign			[   1];	   // [string,    1] ����ü�ᰡ����������񱸺�
} k01230Out2, *LPk01230Out2;

class CKB_01230
{
public: //Variable
//    CString		m_szshcode;							/* �����ڵ�(6)                     */
    CString		m_szrecprice;						/* ���ذ�(8)                       */
    CString		m_szyeprice;						/* ����ü�ᰡ��(8)                 */
    CString		m_szyevolume;						/* ����ü�����(8)                 */
    CString		m_szhname;							/* �����(40)                      */
    CString		m_szprice;							/* ���簡(8)                       */
    CString		m_szsign;							/* ���簡���ϴ�񱸺�(1)           */
    CString		m_szchange;							/* ���簡���ϴ��(8)               */
    CString		m_szrate;							/* ���簡���ϴ������(7)         */
    CString		m_szvolume;							/* �ŷ���(12)                      */
    CString		m_sztrade_cost;						/* �ŷ����(15)                    */
    CString		m_szofferho1;						/* �ŵ�ȣ��1(8)                    */
    CString		m_szofferho2;						/* �ŵ�ȣ��2(8)                    */
    CString		m_szofferho3;						/* �ŵ�ȣ��3(8)                    */
    CString		m_szofferho4;						/* �ŵ�ȣ��4(8)                    */
    CString		m_szofferho5;						/* �ŵ�ȣ��5(8)                    */
    CString		m_szofferrem1;						/* �ŵ�ȣ������1(8)                */
    CString		m_szofferrem2;						/* �ŵ�ȣ������2(8)                */
    CString		m_szofferrem3;						/* �ŵ�ȣ������3(8)                */
    CString		m_szofferrem4;						/* �ŵ�ȣ������4(8)                */
    CString		m_szofferrem5;						/* �ŵ�ȣ������5(8)                */
    CString		m_szbidho1;							/* �ż�ȣ��1(8)                    */
    CString		m_szbidho2;							/* �ż�ȣ��2(8)                    */
    CString		m_szbidho3;							/* �ż�ȣ��3(8)                    */
    CString		m_szbidho4;							/* �ż�ȣ��4(8)                    */
    CString		m_szbidho5;							/* �ż�ȣ��5(8)                    */
    CString		m_szbidrem1;						/* �ż�ȣ������1(8)                */
    CString		m_szbidrem2;						/* �ż�ȣ������2(8)                */
    CString		m_szbidrem3;						/* �ż�ȣ������3(8)                */
    CString		m_szbidrem4;						/* �ż�ȣ������4(8)                */
    CString		m_szbidrem5;						/* �ż�ȣ������5(8)                */
    CString		m_sztotofferrem;					/* �ŵ�ȣ���Ѽ���(8)               */
    CString		m_sztotbidrem;						/* �ż�ȣ���Ѽ���(8)               */
    CString		m_sztmofferrem;						/* �ð��ܸŵ��ܷ�(8)               */
    CString		m_sztmbidrem;						/* �ð��ܸż��ܷ�(8)               */
    CString		m_szuplmtprice;						/* ���Ѱ�(8)                       */
    CString		m_szdnlmtprice;						/* ���Ѱ�(8)                       */
    CString		m_szyerate;							/* ����ü�ᰡ�������簡���(8)     */
    CString		m_szhigh;							/* ����(8)                         */
    CString		m_szlow;							/* ����(8)                         */
    CString		m_szvolrate;						/* ���ϰŷ���(12)                  */
	CString		m_szjnilysign;						/* ����ü�ᰡ����������񱸺�(1)   */
//    CString		m_szlisting;						/* �����ֽļ�(12)                  */

public:
	CKB_01230()
	{
	}

	virtual void  Convert(LPk01230Out2 pInput)
	{
		CString sTemp1 ;
		char sTmp[50+1];

//		DATA_MEMCOPY(sTmp, pInput, shcode);			/* �����(20)                      */
		DATA_MEMCOPY(sTmp, pInput, recprice);		/* ���ذ�(8)                       */
		DATA_MEMCOPY(sTmp, pInput, yeprice);		/* ����ü�ᰡ��(8)                 */
		DATA_MEMCOPY(sTmp, pInput, yevolume);		/* ����ü�����(8)                 */
		DATA_MEMCOPY(sTmp, pInput, hname);			/* �����(40)                      */
		DATA_MEMCOPY(sTmp, pInput, price);			/* ���簡(8)                       */
		DATA_MEMCOPY(sTmp, pInput, sign);			/* ���簡���ϴ�񱸺�(1)           */
		DATA_MEMCOPY(sTmp, pInput, change);			/* ���簡���ϴ��(8)               */
		DATA_MEMCOPY(sTmp, pInput, rate);			/* ���簡���ϴ������(7)         */
		DATA_MEMCOPY(sTmp, pInput, volume);			/* �ŷ���(12)                      */
		DATA_MEMCOPY(sTmp, pInput, trade_cost);		/* �ŷ����(15)                    */
		DATA_MEMCOPY(sTmp, pInput, offerho1);		/* �ŵ�ȣ��1(8)                    */
		DATA_MEMCOPY(sTmp, pInput, offerho2);		/* �ŵ�ȣ��2(8)                    */
		DATA_MEMCOPY(sTmp, pInput, offerho3);		/* �ŵ�ȣ��3(8)                    */
		DATA_MEMCOPY(sTmp, pInput, offerho4);		/* �ŵ�ȣ��4(8)                    */
		DATA_MEMCOPY(sTmp, pInput, offerho5);		/* �ŵ�ȣ��5(8)                    */
		DATA_MEMCOPY(sTmp, pInput, offerrem1);		/* �ŵ�ȣ������1(8)                */
		DATA_MEMCOPY(sTmp, pInput, offerrem2);		/* �ŵ�ȣ������2(8)                */
		DATA_MEMCOPY(sTmp, pInput, offerrem3);		/* �ŵ�ȣ������3(8)                */
		DATA_MEMCOPY(sTmp, pInput, offerrem4);		/* �ŵ�ȣ������4(8)                */
		DATA_MEMCOPY(sTmp, pInput, offerrem5);		/* �ŵ�ȣ������5(8)                */
		DATA_MEMCOPY(sTmp, pInput, bidho1);			/* �ż�ȣ��1(8)                    */
		DATA_MEMCOPY(sTmp, pInput, bidho2);			/* �ż�ȣ��2(8)                    */
		DATA_MEMCOPY(sTmp, pInput, bidho3);			/* �ż�ȣ��3(8)                    */
		DATA_MEMCOPY(sTmp, pInput, bidho4);			/* �ż�ȣ��4(8)                    */
		DATA_MEMCOPY(sTmp, pInput, bidho5);			/* �ż�ȣ��5(8)                    */
		DATA_MEMCOPY(sTmp, pInput, bidrem1);		/* �ż�ȣ������1(8)                */
		DATA_MEMCOPY(sTmp, pInput, bidrem2);		/* �ż�ȣ������2(8)                */
		DATA_MEMCOPY(sTmp, pInput, bidrem3);		/* �ż�ȣ������3(8)                */
		DATA_MEMCOPY(sTmp, pInput, bidrem4);		/* �ż�ȣ������4(8)                */
		DATA_MEMCOPY(sTmp, pInput, bidrem5);		/* �ż�ȣ������5(8)                */
		DATA_MEMCOPY(sTmp, pInput, totofferrem);	/* �ŵ�ȣ���Ѽ���(8)               */
		DATA_MEMCOPY(sTmp, pInput, totbidrem);		/* �ż�ȣ���Ѽ���(8)               */
		DATA_MEMCOPY(sTmp, pInput, tmofferrem);		/* �ð��ܸŵ��ܷ�(8)               */
		DATA_MEMCOPY(sTmp, pInput, tmbidrem);		/* �ð��ܸż��ܷ�(8)               */
		DATA_MEMCOPY(sTmp, pInput, uplmtprice);		/* ���Ѱ�(8)                       */
		DATA_MEMCOPY(sTmp, pInput, dnlmtprice);		/* ���Ѱ�(8)                       */
		DATA_MEMCOPY(sTmp, pInput, yerate);			/* ����ü�ᰡ�������簡���(8)     */
		DATA_MEMCOPY(sTmp, pInput, high);			/* ����(8)                         */
		DATA_MEMCOPY(sTmp, pInput, low);			/* ����(8)                         */
		DATA_MEMCOPY(sTmp, pInput, volrate);		/* ���ϰŷ���(12)                  */
		DATA_MEMCOPY(sTmp, pInput, jnilysign);		/* ����ü�ᰡ����������񱸺�(1)   */
//		DATA_MEMCOPY(sTmp, pInput, listing);		/* �����ֽļ�(12)                  */
	}
};

#pragma pack( pop )
///////////////////////////////////////////////////////////////////////////////////////////////////

#endif // AFX_KB_01230__H_B8898524_2F02_4517_AC5A_E782C176A44F_INCLUDED_