#ifndef CONSTDATA_H
#define CONSTDATA_H

#include <QString>

// ������Ӧ�쳣
const QString c_sNetError = QStringLiteral("���������쳣");
const QString c_sServerJsonError = QStringLiteral("�����������쳣");

//�������͵�ַ
const QString c_sFormalServerUrl = "http://ddn.quanyoudianjing.com";
const QString c_sTestServerUrl = "http://202.91.251.122:8081";
const QString c_sLocalServerUrl = "http://steven.nat300.top";


/*��������˵��*/
//�������ӿ�
const QString c_sHttpFaceTectionOrderAction = "/faceRecog/face/faceDetect";
//�ύ��������
const QString c_sHttpCommitFaceDataOrderAction = "/faceRecog/face/facePerson";
//�ύip�˿�����
const QString c_sHttpCommitDataOrderAction = "/faceRecog/thirdBack/registerIP";

#endif