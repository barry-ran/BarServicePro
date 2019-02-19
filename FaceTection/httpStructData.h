#pragma once

#include <QString>
#include <QDateTime>
#include "enumData.h"
#include <QVariant>

//������Ϣ
typedef struct ClassifyGroupInfo
{
	QString id;                            //����id
	QString sName;          //��������
	int sort;                     //����

}ClassifyGroupInfo_t;
Q_DECLARE_METATYPE(ClassifyGroupInfo)


//��ζ����Ϣ
typedef struct TasteGroupInfo
{
	QString id;            //��ζ��id
	QString sName;    //��ζ������
	QString sOpt;     //��ζ��ѡ��
}TasteGroupInfo_t;
Q_DECLARE_METATYPE(TasteGroupInfo)

//��Ʒ�б�
typedef struct GoodsInfo
{
	int nFortId;   //����id
	QString nId;    //��Ʒid
	QString sName;      //��Ʒ����
	int nType;             //��Ʒ����
	double dPrice;       //��Ʒ����
	double dTotalPrice;  //��Ʒ�ܼ�
	QString nClassifyId;    //��Ʒ����id
	QString sClassifyName;   //��Ʒ��������
	QString sCode;   //��Ʒ����
	QString sUnit;     //��λ
	QString sImgUrl;   //ͼƬ��ַ
	int nStockNum;    //��̨�������
	int nMainStockNum;   //�ܿ������
	int nOrderNum;   //�µ�����
	QString nCheckNum;    //�̵�����
	QList<TasteGroupInfo> nTasteGroupList;   //��ζ���б�
	QList<TasteGroupInfo> nSelectedTasteList;  //��ѡ��ζ���б�
	GoodsInfo(){
		nFortId = 0;
		nOrderNum = 1;
		dTotalPrice = 0.00;
	}
}GoodsInfo_t;
Q_DECLARE_METATYPE(GoodsInfo)

//�µ���Ʒ����
typedef struct OrderGoods{
	QString nGoodsId;      //��Ʒid
	int nNum;                   //��Ʒ����
	int nType;                  //��Ʒ����  1:��ͨ��Ʒ 2:������Ʒ
	QList<TasteGroupInfo> nTasteGroupList;     //��ѡ��ζ���б�
	QString sPrice;                 //��Ʒ����
}OrderGoods_t;
Q_DECLARE_METATYPE(OrderGoods)

//֧������
typedef struct PaymentOrder
{
	int nPayType;           //֧������   1:΢��֧��  2:֧����֧��   3:�ֽ�֧��
	int nBarId;               //����id
	QString sFactPay;     //ʵ�����
	QString sChange;     //����
	QString sRemark;     //��ע
	QString sAuthCode;    //�û�������
	QList<OrderGoods_t> orderGoodsList;    //�µ���Ʒ�б�
}PaymentOrder_t;
Q_DECLARE_METATYPE(PaymentOrder)

//��Ʒ�̵�
typedef struct GoodsCheckUpInfo{
	QString nGoodsId;     //��Ʒid
	double dPrice;   //��Ʒ����
	int nMainStock;   //�ܿ��
	int nBarStock;   //��̨���
	int nCheckStock;  //�̵�����
}GoodsCheckUpInfo_t;
Q_DECLARE_METATYPE(GoodsCheckUpInfo)

//��������Ϣ
typedef struct ShifterInfo{
	QString nShiftId;   //������id
	QString nUserName;   //����������
	QString nAccount;    //�������˺�
}ShifterInfo_t;
Q_DECLARE_METATYPE(ShifterInfo)

//���Ӱ���Ϣ
typedef struct ShiftInfo
{
	double dCashSale;     //�ֽ�����
	double dCashReturn;    //�ֽ��˻�
	double dCodeSale;     //�տ�������
	double dTotalSale;     //��������
	double dCash;     //�ֽ�

	double dOperationTotal;   //��������֧
	double dOperationIn;      //�ջ�����
	double dOperationOut;    //����֧��
	double dCheckTotal;      //�̵�����
	double dCheckLoss;      //�̵㱨��
	double dCheckProfit;    //�̵㱨��

	double dOtherIn;      //��������
	double dOtherOut;     //����֧��
	double dCashIn;       //�ֽ�����
	double dCashOut;      //�ֽ�֧��
	double dCashTotal;    //�ֽ�����֧������

	QString nEndTime;      //����ʱ��
	QString nParentId;      //�ش�id
	QList<ShifterInfo_t> nShifterList;  //�������б�
}ShiftInfo_t;
Q_DECLARE_METATYPE(ShiftInfo)

//���Ԥ����Ʒ
typedef struct WarningGoods
{
	QString sGoodsId;
	QString sGoodsName;
	double dPrice;
	int nInventory;
	WarningGoods(){
		dPrice = 0.00;
		nInventory = 0;
	}
	int get_size(){
		return sizeof(WarningGoods);
	}
}WarningGoods_t;
Q_DECLARE_METATYPE(WarningGoods)

//���������б�
typedef struct OrderDetialInfo
{
	QString sGoodsId;       //��Ʒid
	QString sGoodsName;     //��Ʒ����
	int nOrderNum;          //�µ�����
	double dPrice;         //��Ʒ����
	OrderDetialInfo(){
		nOrderNum = 0;
		dPrice = 0.00;
	}
}OrderDetialInfo_t;
Q_DECLARE_METATYPE(OrderDetialInfo)

//�����б�
typedef struct OrderInfo
{
	QString sOrderId;    //����id
	QString sOrderNum;         //������
	int nTradeType;      //��������    1.���� 2.�˿�
	int nPayStatus;       //֧��״̬  1.δ֧�� 2.��֧�� 3.���˿�
	int nPayType;    //֧������/�˿�����  1.΢�� 2.֧���� 3.�ֽ� 4.����Ǯ��
	QString sCreateTime;         //�µ�ʱ��
	QString sFinishTime;         //���ʱ��
	QString sRemark;    //��ע
	double dSum;   //�������
	QString seatNo;  //��λ��
	QList<OrderDetialInfo_t> lOrderDetialList;  //������Ʒ�б�
	OrderInfo(){
		nTradeType = 0;
		nPayStatus = 0;
		nPayType = 0;
	}
}OrderInfo_t;
Q_DECLARE_METATYPE(OrderInfo)