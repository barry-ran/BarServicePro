#pragma once
#include <QString>

static QString iniPath_;

class configIni
{
public:
	//��ȡ�û���
	static QString getUserName();
	static void setUserName(QString user);
	//��ȡ����
	static QString getPasswd();
	static void setPasswd(QString passwd);
	//��ȡ����id
	static QString getBarId();
	static void setBarId(QString barId);
    //��ȡ����ip
	static QString getServerIP();
	static void setServerIP(QString barId);
	//��ȡ�˿�
	static QString getServerPort();
	static void setServerPort(QString barId);
	//
	static void setIniPath(QString path);
	//��ȡ���񻷾�����
	static QString getServerType();
};