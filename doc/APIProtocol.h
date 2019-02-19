#pragma once
#include "message.h"
#include "logging.hpp"
#define API_ARRAY_LEN	(32)
#define  API_URL_LEN   (512)

#define  HTTP_CRLF "\r\n"
#define  HTTP_CRLFCRLF "\r\n\r\n"
/********************************************
1�����ǿ���չ��
2������ת��ʱ����unsigned

********************************************/

/*********************************************************************************************
APIClient����(NVR)��
1��ʵ����ע�ᡢʵʱ��Ƶ������Ӧ������������
1���������������a)ϵͳ����ʱ b����Ϣ���� c���������������� d������ע������ʧ��
2��ÿ10s���������a������socketʧ�� b������ʧ��  c��ע��ʧ��
APIServer(��Ҫ����)���ṩ��3�����Գ������APIClient�����ץ������������㿪��
**********************************************************************************************/
namespace dem1 {
    namespace server {
		// �����
		typedef enum
		{
			CMD_API_CLIENT_REBOOT = 1,   //�����ն��豸
			CMD_API_CLIENT_REBOOT_RES,

			CMD_API_CLIENT_REMOTE_WAKEUP,      //Զ�̻���
			CMD_API_CLIENT_REMOTE_WAKEUP_RES,

			CMD_API_CLIENT_BOARDCAST_MSG,    //��������
			CMD_API_CLIENT_BOARDCAST_MSG_RES,

			CMD_API_CLIENT_HOST_REGISTER,  //�ͻ���ע��
			CMD_API_CLIENT_HOST_REGISTER_RES,
			
			CMD_API_CLIENT_SHUTDOWN = 11,  //�رռ����
			CMD_API_CLIENT_SHUTDOWN_RES,

			CMD_API_CLIENT_CANCEL_BOARDCAST,  //ȡ����������
			CMD_API_CLIENT_CANCEL_BOARDCAST_RES,

			CMD_API_CLIENT_CONTROL_CALLVOICE_VALUE,   //���ƿͻ��˺���������С
			CMD_API_CLIENT_CONTROL_CALLVOICE_VALUE_RES,

			CMD_API_CLIENT_REQUEST_CALLVOICE_VALUE,   //�ͻ����������������С
			CMD_API_CLIENT_REQUEST_CALLVOICE_VALUE_RES,

			CMD_API_SYNC_DATA,       //ͬ������
			CMD_API_SYNC_DATA_RES,
        }command_e;

        // ����ֵ
        typedef enum
        {
			RESULT_SUCCESS = 0,		// �ɹ�	
			RESULT_FAILED = -1,     //ʧ��
        }command_result_e;

			//������������
		typedef enum
		{
			DEV_ONLINE = 10001,    //�ϻ�
			DEV_OFFLINE = 10002,   //�»�
			OFFER_FOODS = 10003,  //���
			CALL_MANAGEMENT = 10004,  //��������
			CAREFOR_EYES = 10005,   //�����۾�
		}boardcast_type_e;
		
			    //�ն�����
		typedef enum
		{
			IPAD_CLIENT = 0,            //ipad��
			CSERVER_CLIENT = 1,    //CServer��
			WEB_CLIENT = 2,           //web��
		}client_type_e;
  

#pragma pack (1) // ָ����1�ֽڶ���
        // Э��ͷ��װ data = �ն���Ϣ���json��
		//ע��json�ֶ����ݶ�Ҫ������ ����C�˽���
        	std::stringstream title;
			title << headTitle << " " << "ServerMessage/1.0" << HTTP_CRLF;

			int sessionId = -1;
			std::stringstream ss;
			ss << "Host: " << "localhost" << HTTP_CRLF
				<< "User-Agent: " << "server agent" << HTTP_CRLF
				<< "Connection: Keep-Alive" << HTTP_CRLF
				<< "Content-Length: " << std::dec << data.length() << HTTP_CRLF
				<< "Session-Id: " << std::dec << sessionId << HTTP_CRLF
				<< "Content-Type: application/json" << HTTP_CRLFCRLF;

			title << "Header-Length: " << std::dec << ss.str().length() << HTTP_CRLF;
			title << ss.str() << data;
			
		//��װ��ʵ����
		CMD_API_CLIENT_REBOOT ServerMessage/1.0

        Header-Length: 138

        Host: localhost

        User-Agent: server agent

        Connection: Keep-Alive

        Content-Length: 190

        Session-Id: -1

        Content-Type: application/json



        {
            "CmdType": "1",
            "ErrorCode": "0",
            "ServerType": "0",
            "nUser": "ycl",
            "nPassWd": "123456",
            "nIPAdress": "192.168.2.46",
            "nMacAdress": "FF-FF-FF-FF-FF-FF",
            "nSeatNo": "010"
        }
			


		// �����ն������Ϣ
		typedef struct api_client_info
		{
			unsigned char nUser[API_ARRAY_LEN];           //�ն��û���
			unsigned char nPassWd[API_ARRAY_LEN];      //�ն˵�¼����
			unsigned char nIPAdress[API_ARRAY_LEN];     //�ն�IP��ַ
			unsigned char nMacAdress[API_ARRAY_LEN];   //�ն�MAC��ַ
			unsigned char nSeatNo[API_ARRAY_LEN];  //��λ��
		}api_client_info_t;

		//������������
		typedef struct api_boardcast_info
		{
			unsigned char nSeatNo[API_ARRAY_LEN];    //��λ��
			unsigned short nBoardCastType;           //������������
			unsigned short nPlayCycleNum;            //������������
		}api_boardcast_info_t;

		//ͬ�����ݽӿ�
		typedef struct api_syncdata_info{
			unsigned short nCallVioceValue;
		}api_syncdata_info_t;
    }  // namespace server
}  // namespace dem1