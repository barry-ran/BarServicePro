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
const QString c_sFormalServerUrl = "https://uu.zimonet.com";
const QString c_sTestServerUrl = "http://202.91.251.122:8050";
const QString c_sLocalServerUrl = "http://jinzehong.s1.natapp.cc";


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
//��ȡȫ����Ʒ�б�
const QString c_sHttpGetOrderAllGoodsListAction = "/qynetbarsystem/api/goods/getAll?";
//�����µ�
const QString c_sHttpOrderGoodsDetialAction = "/qynetbarsystem/api/zmDeal/GeneratePayDealToPaymentCode?";
//��Ʒ�̵�
const QString c_sHttpOrderGoodsCheckUpAction = "/qynetbarsystem/api/goodsCheckup/checkInventory?";
//��ѯ���Ӱ���Ϣ
const QString c_sHttpOrderGetShiftInfoAction = "/qynetbarsystem/api/handover/query?";
//�ύ���Ӱ���Ϣ
const QString c_sHttpOrderCommitShiftInfoAction = "/qynetbarsystem/api/handover/save?";
//У��Ӱ��˵�¼��Ϣ
const QString c_sHttpOrderCheckAcceptor = "/qynetbarsystem/api/zmSysAdmin/checkPwd?";
//��Ʒ���¼�
const QString c_sHttpOperateBarInventoryAction = "/qynetbarsystem/api/goodsOperation/operBarInventory?";
//��Ʒ���˻�
const QString c_sHttpOperateMainInventoryAction = "/qynetbarsystem/api/goodsOperation/operMainInventory?";
//��ȡ�û��ϻ���Ϣ
const QString c_sHttpGetLoginUserInfoAction = "/qynetbarsystem/api/computerInfo/loginPc?";
//��ȡwifi��Ϣ
const QString c_sHttpGetWifiInfoAction = "/qynetbarsystem/api/barData/getWifi?";
//��������
const QString c_sHttpCallServiceAction = "/qynetbarsystem/api/netAdminAppNotify/insert?";
//��ȡǩ���б�
const QString c_sHttpGetSignInListAction = "/qynetbarsystem/api/ipadUser/getSignInList?";
//ǩ��
const QString c_sHttpSignInAction = "/qynetbarsystem/api/ipadUser/signIn?";
//��ȡ�����Żݰ��б�
const QString c_SHttpGetNetBagListAction = "/qynetbarsystem/api/fullReduce/selectFullReduceList?";
//���ѳ�ֵ
const QString c_sHttpNetFeeRechargeAction = "/qynetbarsystem/api/ipadUser/createNetCode?";
#endif