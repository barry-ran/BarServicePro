#pragma once
enum ServerHttpErrorCode {
	e_connectServerError = -1,
	e_success = 200,
	e_paramError = 1,
};

enum ServerType{
	t_formalServer = 1,    //��ʽ����
	t_testServer = 2,     //���Է���
	t_localServer = 3,     //���ط���
};