#include "getuserinfotool.h"
#include "configIni.h"
#include "HttpAgent.h"

#include <QCoreApplication>
#include <QHostInfo>
#include <QMessageBox>
#include "logging.hpp"

GetUserInfoTool::GetUserInfoTool(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	QString ip = getHostIpAddress();
	QString mac = getHostMacAddress().replace(":", "-");
	QString winName = getLocalmachineName();

	QString path = QCoreApplication::applicationDirPath() + "/config/config.ini";
	configIni::setIniPath(path);
	QString user = configIni::getUserName();
	QString passwd = configIni::getPasswd();
	QString barId = configIni::getBarId();
	QString serverIP = configIni::getServerIP();
	QString port = configIni::getServerPort();

	QStringList list;
	list << ip << mac << user << passwd << barId << winName << serverIP << port;
	QString qCode = list.join("|");
	ui.qrWidget->generateString(qCode);

	m_info.nBarId = barId.toInt();
	m_info.sIp = ip;
	m_info.sMac = mac;
	m_info.sPCName = winName;

	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(slotOnReportInfo()));
	connect(HttpAgent::instance(), SIGNAL(sigOnReportPCInfoResult(int, QString)), this, SLOT(slotOnReportPCInfoResult(int, QString)));

	//HttpAgent::instance()->RequestReportPCInfo(m_info);
}

GetUserInfoTool::~GetUserInfoTool()
{

}

void GetUserInfoTool::slotOnReportInfo()
{
	HttpAgent::instance()->RequestReportPCInfo(m_info);
}

void GetUserInfoTool::slotOnReportPCInfoResult(int nCode, QString sMsg)
{
	if (nCode != e_success)
	{
		Log::Info("Request On GetUserInfoTool failed : %s", sMsg.toStdString().c_str());
		QMessageBox::warning(NULL, "warning", QStringLiteral("������������쳣--������:%1, ������Ϣ:%2").arg(nCode).arg(sMsg));
	}
	else
	{
		Log::Info("Request On GetUserInfoTool success");
		QMessageBox::information(NULL, "tips", QStringLiteral("�ϱ��ͻ�����Ϣ�ɹ���"));
	}
}

QString GetUserInfoTool::getHostIpAddress()
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

QString GetUserInfoTool::getHostMacAddress()
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

QString GetUserInfoTool::getLocalmachineName()
{
	QString machineName = QHostInfo::localHostName();
	return machineName;
}
