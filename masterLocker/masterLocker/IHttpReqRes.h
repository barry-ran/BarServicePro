#ifndef IHTTPREQRES_H
#define IHTTPREQRES_H

#include <QObject>
#include <QtNetwork>
#include <QSslConfiguration>
#include "appConfigIni.h"

class IHttpReqRes : public QObject
{
	Q_OBJECT

public:
	IHttpReqRes(QObject *parent = 0);
	~IHttpReqRes();

	void setNetManager(QNetworkAccessManager* pManager);
	void setReqParams(QByteArray byArr);
	void postRequest();
	QString getTestUrl(); // ������
	void setOverTimeLengh(int nOverTimeLengh); // ���ó�ʱʱ��
	bool isOverTime(); // �����Ƿ�ʱ
protected:
	virtual void processResponse(QString strResult) = 0;
	virtual void processError() = 0;
	virtual void setReqUrlAddress(QString urlAddress);
private slots:
	void slot_ReplyFinished();
	void slot_overTimeout();

private:
	void initConnect();
protected:
	QNetworkAccessManager*  m_pManager;
	QNetworkRequest			m_request;
	QNetworkReply*          m_pReply;
	QByteArray				m_reqParams;
	int						m_nReconnectTimes;
	//QString					m_strResult;
	QString m_sUrlAddress;
	QString m_sTestUrl; // ������
	QTimer m_overTimer; // ��ʱ��ʱ��
	int m_nOverTimeLen; // ��ʱʱ��
	bool m_bOverTime; // �Ƿ�ʱ
};

#endif // IHTTPREQRES_H
