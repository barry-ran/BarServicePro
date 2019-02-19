#pragma once
#include <QString>
#include <QNetworkInterface>  
#include <QList>  

static QString iniPath_;

class appConfigIni
{
public:
	//��ȡ������IP��ַ
	static QString getServerIP();
	static void setServerIP(QString serverIP);
	//��ȡ�������˿�
	static QString getServerPort();
	static void setServerPort(QString serverPort);
	//
	static void setIniPath(QString path);
	//��ȡ�豸�����Ϣ
	static QString getHostIpAddress();
	static QString getHostMacAddress();
	static QString getLocalmachineName();
	//��ȡ���񻷾�����
	static QString getServerType();
	//��ȡbarId
	static QString getBarId();
};

