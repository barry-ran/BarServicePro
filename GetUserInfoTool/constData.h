#ifndef CONSTDATA_H
#define CONSTDATA_H

#include <QString>

// ������Ӧ�쳣
const QString c_sNetError = QStringLiteral("���������쳣");
const QString c_sServerJsonError = QStringLiteral("�����������쳣");

//����У�鷵�ش�����ʾ
const QString c_sBookingExpiredErr = QStringLiteral("����ʧЧ");
const QString c_sBookingCodeErr = QStringLiteral("��֤�����");
const QString c_sBookingUnlockedErr = QStringLiteral("�õ����ѱ�����");

//�������͵�ַ
const QString c_sFormalServerUrl = "http://ddn.quanyoudianjing.com";
const QString c_sTestServerUrl = "http://202.91.251.122:8050";
const QString c_sLocalServerUrl = "http://jinzehong.s1.natapp.cc";
const QString c_sServerUrl = "http://cuizhihu.s1.natapp.cc";


/*��������˵��*/
//��ȡ����״̬
const QString c_sHttpGetOrderBookSeatAction = "/qynetbarsystem/api/bookingSeat/findPcSatus?";
//У�������
const QString c_sHttpGetOrderVerifyUnlockAction = "/qynetbarsystem/api/bookingSeat/unlockPreseat?";
//�ϱ�PC����״̬
const QString c_sHttpGetOrderOnlineStatusAction = "/qynetbarsystem/api/bookingSeat/upPcstatus?";
//��ȡBarId
const QString c_sHttpGetOrderBarNameAction = "/qynetbarsystem/api/barData/getBarData?";
//��ȡ��ά��
const QString c_sHttpGetOrderQrCodeAction = "/qydj/common?";
//��¼�ӿ�
const QString c_sHttpOrderLoginAction = "/qynetbarsystem/api/login/loginCashierDesk?";
//�ǳ��ӿ�
const QString c_sHttpOrderLogoutAction = "/qynetbarsystem/api/login/logoutCashierDesk?";
//��ȡ��Ʒ����
const QString c_sHttpGetOrderClassifyGroupAction = "/qynetbarsystem/api/goodsClassify/useList?";
//��ȡ��Ʒ�б�
const QString c_sHttpGetOrderGoodsListAction = "/qynetbarsystem/api/goods/useList?";
//�����µ�
const QString c_sHttpOrderGoodsDetialAction = "/qynetbarsystem/api/zmDeal/GeneratePayDealToPaymentCode?";
//�������޸Ŀͻ�����Ϣ
const QString c_sHttpReportPCInfoAction = "/qynetbarsystem/api/computerInfo/addorUpdateComputerInfo?";

#endif