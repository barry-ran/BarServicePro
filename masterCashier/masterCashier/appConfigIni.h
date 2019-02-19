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
	//��ȡ�û���
	static QString getUserName();
	static void setUserName(QString nUser);
	//��ȡ�û�id
	static QString getUserId();
	static void setUserId(QString nUserId);
	//��ȡparentId
	static QString getParentId();
	static void setParentId(QString parentId);
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
	//���Ͷ˿�
	static QString getWebPort();
	//��ȡ������
	static QString getBarName();
	static void setBarName(QString barName);
};

