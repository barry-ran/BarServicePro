#include "appConfigIni.h"

#include <QSettings>
#include <QFile>
#include <QDir>
#include <QHostInfo>

QString appConfigIni::getServerIP()
{
	QSettings settings(iniPath_, QSettings::IniFormat);
	return settings.value("server/ip", "").toString();
}

void appConfigIni::setServerIP(QString serverIP)
{
	QSettings settings(iniPath_, QSettings::IniFormat);
	settings.setValue("server/ip", serverIP);
}

QString appConfigIni::getServerPort()
{
	QSettings settings(iniPath_, QSettings::IniFormat);
	return settings.value("server/port", "").toString();
}

void appConfigIni::setServerPort(QString serverPort)
{
	QSettings settings(iniPath_, QSettings::IniFormat);
	settings.setValue("server/port", serverPort);
}

void appConfigIni::setIniPath(QString path)
{
	iniPath_ = path;
}

QString appConfigIni::getHostIpAddress()
{
	QString strIpAddress;
	QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
	// ��ȡ��һ����������IPv4��ַ  
	int nListSize = ipAddressesList.size();
	for (int i = 0; i < nListSize; ++i)
	{
		if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
			ipAddressesList.at(i).toIPv4Address()) {
			strIpAddress = ipAddressesList.at(i).toString();
			break;
		}
	}
	// ���û���ҵ������Ա���IP��ַΪIP  
	if (strIpAddress.isEmpty())
		strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
	return strIpAddress;
}

QString appConfigIni::getHostMacAddress()
{
	QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();// ��ȡ��������ӿ��б�  
	int nCnt = nets.count();
	QString strMacAddr = "";
	for (int i = 0; i < nCnt; i++)
	{
		// ���������ӿڱ�������������в��Ҳ��ǻػ���ַ�������������Ҫ�ҵ�Mac��ַ  
		if (nets[i].flags().testFlag(QNetworkInterface::IsUp) && nets[i].flags().testFlag(QNetworkInterface::IsRunning) && !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack))
		{
			strMacAddr = nets[i].hardwareAddress();
			break;
		}
	}
	return strMacAddr;
}

QString appConfigIni::getLocalmachineName()
{
	QString machineName = QHostInfo::localHostName();
	return machineName;
}

QString appConfigIni::getServerType()
{
	QSettings settings(iniPath_, QSettings::IniFormat);
	return settings.value("server/type", "").toString();
}

QString appConfigIni::getBarId()
{
	QSettings settings(iniPath_, QSettings::IniFormat);
	return settings.value("server/barId", "").toString();
}
