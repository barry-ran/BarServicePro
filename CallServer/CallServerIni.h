#pragma once
#include <QString>

static QString CallServerIniPath_;

class CallServerIni
{
public:
	//��ȡ������IP��ַ
	static QString getServerIP();
	static void setServerIP(QString serverIP);
	//��ȡ�������˿�
	static QString getServerPort();
	static void setServerPort(QString serverPort);
	//���ÿ�������
	static bool getAutoExecFlag();
	static void setAutoExecFlag(bool isAutoExec);
	//���ú�������
	static int getCallVoiceValue();
	static void setCallVoiceValue(int value);
	//���ò�������
	static int getPlayVoiceValue();
	static void setPlayVoiceValue(int value);

	static QString getWebPort();
	//
	static void setIniPath(QString path);
};

