#pragma once
#include <QString>

// ������Ӧ�쳣
const QString c_sNetError = QStringLiteral("���������쳣");
const QString c_sServerJsonError = QStringLiteral("�����������쳣");

//�������͵�ַ
const QString c_sFormalServerUrl = "http://202.91.251.125:8084";
const QString c_sTestServerUrl = "http://202.91.251.122:8085";
const QString c_sLocalServerUrl = "http://192.168.180.102:8080";

/*�ӿ�APi*/
//��ȡ����б�
const QString c_sHttpGetAdvertisementListAction = "/qynetad/api/ad/list";
//�ϱ�ͳ������
const QString c_sHttpCommitStatisticalDataAction = "/qynetad/api/adstatistics/save";