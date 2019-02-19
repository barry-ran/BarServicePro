#pragma once

#include <QString>
#include <QDateTime>
#include "enumData.h"
#include <QVariant>

//�ϱ��ͻ�����Ϣ
typedef struct ReportPCInfo
{
	int nBarId;   //����id
	QString sIp;   //ip��ַ
	QString sMac;   //mac��ַ
	QString sPCName;    //������
}ReportPCInfo_t;
Q_DECLARE_METATYPE(ReportPCInfo)


//������Ϣ
typedef struct ClassifyGroupInfo
{
	int id;                            //����id
	QString sName;          //��������
	int sort;                     //����

}ClassifyGroupInfo_t;
Q_DECLARE_METATYPE(ClassifyGroupInfo)


//��ζ����Ϣ
typedef struct TasteGroupInfo
{
	int id;            //��ζ��id
	QString sName;    //��ζ������
	QString sOpt;     //��ζ��ѡ��
}TasteGroupInfo_t;
Q_DECLARE_METATYPE(TasteGroupInfo)

//��Ʒ�б�
typedef struct GoodsInfo
{
	int nId;    //��Ʒid
	QString sName;      //��Ʒ����
	int nType;             //��Ʒ����
	double dPrice;       //��Ʒ����
	double dTotalPrice;  //��Ʒ�ܼ�
	int nClassifyId;    //��Ʒ����id
	QString sCode;   //��Ʒ����
	QString sUnit;     //��λ
	QString sImgUrl;   //ͼƬ��ַ
	int nStockNum;    //�������
	int nOrderNum;   //�µ�����
	QList<TasteGroupInfo> nTasteGroupList;   //��ζ���б�
	QList<TasteGroupInfo> nSelectedTasteList;  //��ѡ��ζ���б�
	GoodsInfo(){
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
	int nPayType;           //֧������   1:֧����֧��   3:�ֽ�֧��
	int nBarId;               //����id
	QString sFactPay;     //ʵ�����
	QString sChange;     //����
	QString sRemark;     //��ע
	QString sAuthCode;    //�û�������
	QList<OrderGoods_t> orderGoodsList;    //�µ���Ʒ�б�
}PaymentOrder_t;
Q_DECLARE_METATYPE(PaymentOrder)