#ifndef CONSTDATA_H
#define CONSTDATA_H

#include <QString>

const QString c_sAppDownloadUrl = "http://uu.zimonet.com/download/";

// ������Ӧ�쳣
const QString c_sNetError = QStringLiteral("���������쳣");
const QString c_sServerJsonError = QStringLiteral("�����������쳣");

//����У�鷵�ش�����ʾ
const QString c_sBookingExpiredErr = QStringLiteral("����ʧЧ");
const QString c_sBookingCodeErr = QStringLiteral("��֤�����");
const QString c_sBookingUnlockedErr = QStringLiteral("�õ����ѱ�����");

//�������͵�ַ
const QString c_sFormalServerUrl = "https://uu.zimonet.com";
const QString c_sTestServerUrl = "http://202.91.251.122:8050";
const QString c_sLocalServerUrl = "http://jinzehong.s1.natapp.cc";


//��������˵��
const QString c_sHttpGetOrderBookSeatAction = "/qynetbarsystem/api/bookingSeat/findPcSatus?";
const QString c_sHttpGetOrderVerifyUnlockAction = "/qynetbarsystem/api/bookingSeat/unlockPreseat?";
const QString c_sHttpGetOrderOnlineStatusAction = "/qynetbarsystem/api/bookingSeat/upPcstatus?";
const QString c_sHttpGetOrderBarNameAction = "/qynetbarsystem/api/barData/getBarData?";
const QString c_sHttpGetOrderQrCodeAction = "/qydj/common?";

#endif