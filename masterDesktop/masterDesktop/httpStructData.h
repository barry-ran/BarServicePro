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
		nOrderNum = 0;
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

//�û��ϻ���Ϣ
typedef struct LoginUserInfo
{
	QString sName;    //�û�����
	QString sPhone;    //�û��ֻ���
	QString sIdCard;   //�û����֤��
	double dNetFee;    //���ѽ��
	double dWalletFee;  //Ǯ�����
	QString sUserId;     //�û�ID
	int nDiffTime;       //�ϻ�ʱ��
	LoginUserInfo(){
		dNetFee = 0.00;
		dWalletFee = 0.00;
		nDiffTime = 0;
	}
	int get_size(){
		return sizeof(LoginUserInfo);
	}
}LoginUserInfo_t;
Q_DECLARE_METATYPE(LoginUserInfo)

//���ѳ�ֵ�Żݰ�
typedef struct DiscountPkg
{
	QString sId;     //�Żݰ�id
	double dOriginalPrice;     //ԭ��
	DiscountPkg(){
		dOriginalPrice = 0.00;
	}
	int get_size(){
		return sizeof(DiscountPkg);
	}
	void clear(){
		sId = "";
		dOriginalPrice = 0.00;
	}
}DiscountPkg_t;
Q_DECLARE_METATYPE(DiscountPkg)