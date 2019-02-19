#pragma once
#include "message.h"
#include "logging.hpp"
#include "appconfig.h"
#define API_ARRAY_LEN	(32)
#define  API_URL_LEN   (512)
#define  API_MSG_LEN (1024)

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

			CMD_API_MASTERLOCKER_REGISTER,   //��������ע��
			CMD_API_MASTERLOCKER_REGISTER_RES
        }command_e;

        // ����ֵ
        typedef enum
        {
			RESULT_SUCCESS = 0,		// �ɹ�	
			RESULT_FAILED = -1,     //ʧ��
        }command_result_e;

	    //�ն�����
		typedef enum
		{
			IPAD_CLIENT = 0,            //ipad��
			CSERVER_CLIENT = 1,    //CServer��
			WEB_CLIENT = 2,           //web��
		}client_type_e;

		//������������
		typedef enum
		{
			DEV_ONLINE = 10001,    //�ϻ�
			DEV_OFFLINE = 10002,   //�»�
			OFFER_FOODS = 10003,  //���
			CALL_MANAGEMENT = 10004,  //��������
		}boardcast_type_e;

#pragma pack (1) // ָ����1�ֽڶ���
        // Э��ͷ
        typedef struct protocol_head
        {

            unsigned char	nStartFlags;			// ��ʼ��ʾ:0xAF
            unsigned char	nVersion;				// �汾:0x01
            unsigned short	nCmd;					// ָ��:command_e ö�ٽṹ
            unsigned int	nDataLen;				// ���س���

            short			nResult;				// �����������:command_result_e ö�ٽṹ

            unsigned char	deviceNum;				// Ԥ��
            unsigned char	nEndFlags;				// ������ʾ:oxFA	

            protocol_head(){
                nStartFlags = 0xAF;
                nVersion = 0x01;
                nCmd = 0;
                nDataLen = 0;
                nResult = 0;
                deviceNum = 0;
                nEndFlags = 0xFA;
            }
            int get_size(){

                return sizeof(protocol_head);
            }

            void read(netbuffer_t* rb){

                read_uchar(this->nStartFlags, rb);
                read_uchar(this->nVersion, rb);
                read_ushort(this->nCmd, rb);
                read_uint(this->nDataLen, rb);
                read_short(this->nResult, rb);
                read_uchar(this->deviceNum, rb);
                read_uchar(this->nEndFlags, rb);
            }

            void write(netbuffer_t* wb){

                write_uchar(this->nStartFlags, wb);
                write_uchar(this->nVersion, wb);
                write_ushort(this->nCmd, wb);
                write_uint(this->nDataLen, wb);
                write_short(this->nResult, wb);
                write_uchar(this->deviceNum, wb);
                write_uchar(this->nEndFlags, wb);
            }
        }protocol_head_t;

		// �����ն������Ϣ
		typedef struct api_client_info
		{
			unsigned char nUser[API_ARRAY_LEN];           //�ն��û���
			unsigned char nPassWd[API_ARRAY_LEN];      //�ն˵�¼����
			unsigned char nIPAdress[API_ARRAY_LEN];     //�ն�IP��ַ
			unsigned char nMacAdress[API_ARRAY_LEN];   //�ն�MAC��ַ
			unsigned char nSeatNo[API_ARRAY_LEN];  //��λ��

			api_client_info(){
				memset(&nUser, 0, API_ARRAY_LEN);
				memset(&nPassWd, 0, API_ARRAY_LEN);
				memset(&nIPAdress, 0, API_ARRAY_LEN);
				memset(&nMacAdress, 0, API_ARRAY_LEN);
				memset(&nSeatNo, 0, API_ARRAY_LEN);
			}

			int get_size(){
				return sizeof(api_client_info);
			}

			void read(netbuffer_t* rb){
				readdata(this->nUser, API_ARRAY_LEN, rb);
				readdata(this->nPassWd, API_ARRAY_LEN, rb);
				readdata(this->nIPAdress, API_ARRAY_LEN, rb);
				readdata(this->nMacAdress, API_ARRAY_LEN, rb);
				readdata(this->nSeatNo, API_ARRAY_LEN, rb);
			}

			void write(netbuffer_t* wb){
				writedata(this->nUser, API_ARRAY_LEN, wb);
				writedata(this->nPassWd, API_ARRAY_LEN, wb);
				writedata(this->nIPAdress, API_ARRAY_LEN, wb);
				writedata(this->nMacAdress, API_ARRAY_LEN, wb);
				writedata(this->nSeatNo, API_ARRAY_LEN, wb);
			}
			void read_json(boost::property_tree::ptree parser){
				try
				{
					memcpy(this->nUser, parser.get<std::string>("nUser").c_str(), parser.get<std::string>("nUser").length());
					memcpy(this->nPassWd, parser.get<std::string>("nPassWd").c_str(), parser.get<std::string>("nPassWd").length());
					memcpy(this->nIPAdress, parser.get<std::string>("nIPAdress").c_str(), parser.get<std::string>("nIPAdress").length());
					memcpy(this->nMacAdress, parser.get<std::string>("nMacAdress").c_str(), parser.get<std::string>("nMacAdress").length());
					memcpy(this->nSeatNo, parser.get<std::string>("nSeatNo").c_str(), parser.get<std::string>("nSeatNo").length());
				}
				catch (boost::property_tree::ptree_error const & ec)
				{
					AppConfigHandler.Info("struct api_client_info read_json error : " + string(ec.what()));
				}
			}
			void write_json(boost::property_tree::ptree &parser){
				parser.put<std::string>("nUser", (char*)(this->nUser));
				parser.put<std::string>("nPassWd", (char*)(this->nPassWd));
				parser.put<std::string>("nIPAdress", (char*)(this->nIPAdress));
				parser.put<std::string>("nMacAdress", (char*)(this->nMacAdress));
				parser.put<std::string>("nSeatNo", (char*)(this->nSeatNo));
			}
		}api_client_info_t;

		//������Ϣ
		typedef struct api_pushMsg_info
		{
			unsigned char nPushMsg[API_MSG_LEN];
			api_pushMsg_info(){
				memset(&nPushMsg, 0, API_MSG_LEN);
			}
			int get_size(){
				return sizeof(api_pushMsg_info);
			}
			void read_json(boost::property_tree::ptree parser){
                try
				{
					memcpy(this->nPushMsg, parser.get<std::string>("nPushMsg").c_str(), parser.get<std::string>("nPushMsg").length());
				}
				catch (boost::property_tree::ptree_error const & ec)
				{
					AppConfigHandler.Info("struct api_client_info read_json error : " + string(ec.what()));
				}
			}
			void write_json(boost::property_tree::ptree &parser){
				parser.put<std::string>("nPushMsg", (char*)(this->nPushMsg));
			}
		}api_pushMsg_info_t;

		//������������
		typedef struct api_boardcast_info
		{
			unsigned char nSeatNo[API_ARRAY_LEN];    //��λ��
			unsigned short nBoardCastType;           //������������
			unsigned short nPlayCycleNum;            //������������
			api_boardcast_info(){
				memset(&nSeatNo, 0, API_ARRAY_LEN);
				nBoardCastType = 0;
				nPlayCycleNum = 0;
			}
			int get_size(){
				return sizeof(api_boardcast_info);
			}
			std::string getBoardCastType(){
				return "audiofile_" + to_string(nBoardCastType) + ".mp3";
			}
			void read_json(boost::property_tree::ptree parser){
				try
				{
					memcpy(this->nSeatNo, parser.get<std::string>("nSeatNo").c_str(), parser.get<std::string>("nSeatNo").length());
					this->nBoardCastType = parser.get<short>("nBoardCastType");
					this->nPlayCycleNum = parser.get<short>("nPlayCycleNum");
				}
				catch (boost::property_tree::ptree_error const & ec)
				{
					AppConfigHandler.Info("struct api_boardcast_info read_json error : " + string(ec.what()));
				}
			}
			void write_json(boost::property_tree::ptree &parser){
				parser.put<std::string>("nSeatNo", (char*)(this->nSeatNo));
				parser.put<short>("nBoardCastType", this->nBoardCastType);
				parser.put<short>("nPlayCycleNum", this->nPlayCycleNum);
			}
		}api_boardcast_info_t;

		//ͬ�����ݽӿ�
		typedef struct api_syncdata_info{
			unsigned short nCallVioceValue;
			api_syncdata_info(){
				nCallVioceValue = 0;
			}
			int get_size(){
				return sizeof(api_syncdata_info);
			}
			void read_json(boost::property_tree::ptree parser){
				try
				{
					this->nCallVioceValue = parser.get<short>("nCallVioceValue");
				}
				catch (boost::property_tree::ptree_error const & ec)
				{
					AppConfigHandler.Info("struct api_boardcast_info read_json error : " + string(ec.what()));
				}
			}
			void write_json(boost::property_tree::ptree &parser){
				parser.put<short>("nCallVioceValue", this->nCallVioceValue);
			}
		}api_syncdata_info_t;

		//��������ע����Ϣ
		typedef struct api_masterLocker_register_info
		{
			unsigned char nIP[API_ARRAY_LEN];
			unsigned char nMac[API_ARRAY_LEN];
			unsigned char nName[API_ARRAY_LEN];
			api_masterLocker_register_info(){
				memset(&nIP, 0, API_ARRAY_LEN);
				memset(&nMac, 0, API_ARRAY_LEN);
				memset(&nName, 0, API_ARRAY_LEN);
			}
			int get_size(){
				return sizeof(api_masterLocker_register_info);
			}
			void read_json(boost::property_tree::ptree parser){
				try
				{
					memcpy(this->nIP, parser.get<std::string>("nIP").c_str(), parser.get<std::string>("nIP").length());
					memcpy(this->nMac, parser.get<std::string>("nMac").c_str(), parser.get<std::string>("nMac").length());
					memcpy(this->nName, parser.get<std::string>("nName").c_str(), parser.get<std::string>("nName").length());
				}
				catch (boost::property_tree::ptree_error const & ec)
				{
					AppConfigHandler.Info("struct api_boardcast_info read_json error : " + string(ec.what()));
				}
			}
			void write_json(boost::property_tree::ptree &parser){
				parser.put<std::string>("nIP", (char*)(this->nIP));
				parser.put<std::string>("nMac", (char*)(this->nMac));
				parser.put<std::string>("nName", (char*)(this->nName));
			}
		}api_masterLocker_register_info_t;
    }  // namespace server
}  // namespace dem1