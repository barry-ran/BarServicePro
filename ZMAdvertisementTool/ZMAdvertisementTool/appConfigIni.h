#pragma once
#include <QString>
#include <QNetworkInterface>
#include <QList>

static QString iniPath_;

class appConfigIni
{
public:
	//
	static void setIniPath(QString path);
	//��ȡ�豸�����Ϣ
	static QString getHostIpAddress();
	static QString getHostMacAddress();
	static QString getLocalmachineName();
	//��ȡ���񻷾�����
	static QString getServerType();
};

