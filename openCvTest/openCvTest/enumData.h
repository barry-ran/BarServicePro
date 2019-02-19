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

enum LoginType{
	t_login = 1,   //��¼
	t_switch = 2,   //�л��˺�
	t_shift = 3,    //���Ӱ�
};

enum ServerType{
	t_formalServer = 1,    //��ʽ����
	t_testServer = 2,     //���Է���
	t_localServer = 3,     //���ط���
};

//����״̬
enum BookSeatStatus{
	s_unBookSeat = 0,    //δԤ��
	s_bookSeat = 1,       //��Ԥ��
};

//�����״̬
enum PCStatus{
	s_offLine = 1,    //����
	s_onLine = 2,     //����
};

//websocket api
enum WSApi{
	w_sReboot = 10001,     //����
	w_sShutdown = 10002,     //�ػ�
	w_sLockScreen = 10003,    //����
};

//֧������
enum PayType{
	t_wxPay = 1,      //΢��֧��
	t_aliPay = 2,     //֧����֧��
	t_cashPay = 3,   //�ֽ�֧��
    t_yyPay = 4,     //����Ǯ��֧��
};

//֧����������
enum PayDlgType{
	t_payment_success = 101,     //֧���ɹ�
	t_payment_failed = 102,      //֧��ʧ��
	t_paymenting = 103,          //֧����
};

//ҳ��
enum PageType{
	t_salePage = 0,    //����ҳ��
	t_shiftPage = 1,   //���Ӱ�ҳ��
	t_returnPage = 2,   //�˻���ҳ��
	t_orderPage = 3,    //����ҳ��
};

//�ֿ�����
enum Stocktype{
	t_mainStock = 1,     //�����
	t_barStock = 2,      //��̨���
};

//��̨����
enum BarOpearte{
	t_upInventory = 1,      //�ϼ�
	t_downInventory = 2,    //�¼�
};

//������
enum MainOperate{
	t_inInventory = 1,  //����
	t_outInventory = 2,  //�˻�
};

//����֧��״̬
enum OrderPayStatus{
	s_unPay = 1,  //δ֧��
	s_pay = 2,   //��֧��
	s_return = 3,  //���˿�
};
#endif