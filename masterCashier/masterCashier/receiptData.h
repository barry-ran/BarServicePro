#pragma once

#include <QString>
#include <QMap>
#include <QList>
#include <QVariant>

typedef struct ProductInfo
{
	QString nProductName;            //��Ʒ����
	QString nProductNum;             //��Ʒ����
	QString nPrice;                        //��Ʒ����
	QString sTasteGroup;        //��ζ��
}ProductInfo_t;
Q_DECLARE_METATYPE(ProductInfo)

typedef struct ReceiptInfo
{
	QString sBarName;         //������
	QString nSeatNo;              //��λ��
	QString nPaymentNo;        //�������
	QString nAccount;            //�û���
	QString strSum;               //�������
	QList<ProductInfo> nProductList;       //������Ʒ�б�
}ReceiptInfo_t;
Q_DECLARE_METATYPE(ReceiptInfo)