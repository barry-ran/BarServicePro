#ifndef RECEIPTPRINTERMAKER_H
#define RECEIPTPRINTERMAKER_H

#include <QObject>
#include <QPainter>
#include "receiptData.h"

class ReceiptPrinterMaker : public QObject
{
	Q_OBJECT

public:
	static ReceiptPrinterMaker* instance();

	void printOrderDetialFunc(const ReceiptInfo &info);
	void saveImageDetialFunc();
private:
	explicit ReceiptPrinterMaker();
	~ReceiptPrinterMaker();
private:
	static ReceiptPrinterMaker* m_pInstance;
	ReceiptInfo m_receiptInfo;
	QPainter* m_pPainter;
	QPixmap* m_pPixmap;
	int m_nPictureMaxHeight; // ͼƬ���߶�
	int m_nZoomWidth; // ��ӡ�������ſ�ȣ� ��ӡ����dll�Ὣ450��ͼƬ���ŵ�174��С
};

#endif // RECEIPTPRINTERMAKER_H
