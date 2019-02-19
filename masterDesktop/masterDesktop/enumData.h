#ifndef ENUMDATA_H
#define ENUMDATA_H

enum ServerHttpErrorCode{
	e_connectServerError = -1,
	e_success = 0, // �ɹ�
	e_paramError = 1, // ��������δ�ҵ�����
	e_bookingExpired = 1001,   //����ʧЧ
	e_bookingCodeErr = 1002,  //������֤�����
	e_bookingUnlocked = 1003,  //�ѱ�����
};

enum ServerType{
	t_formalServer = 1,    //��ʽ����
	t_testServer = 2,     //���Է���
	t_localServer = 3,     //���ط���
};

enum ChatType{
	t_admin = 1,    //ϵͳ��Ϣ
	t_local = 2,    //������Ϣ
	t_user = 3,    //�����û���Ϣ
};

//ҳ��
enum RequestPageType{
	t_rechargePage = 0,    //��ֵҳ��
	t_personalCentrePage = 1,    //�������Ľ���
	t_orderPage = 2,
};
#endif