#pragma once
#include "message.h"
#include "appconfig.h"
#include "logging.hpp"
#include <QList>
#include <string.h>
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
namespace dm {
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
			DEV_OFFLINE = 10002,   //�»�����
			OFFER_FOODS = 10003,  //���
			CALL_MANAGEMENT = 10004,  //��������
			CAREFOR_EYES = 10005,   //�����۾�
			CALL_SERVICE = 10006,  //���з���Ա
			CALL_SEAT = 10007,   //��������
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
			unsigned char nSeatNo[API_ARRAY_LEN];  //���������ļ���  

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
					//AppConfigHandler.Info("struct api_register read_json error : " + string(ec.what()));
					Log::Info("struct api_register read_json error : %s", ec.what());
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

		//��Ƶϸ��
		typedef struct api_audio_info
		{
			std::string mAudioFileName;
			bool isNum;
			api_audio_info(){
				mAudioFileName = "";
				isNum = false;
			}
		}api_audio_info_t;

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
			QList<api_audio_info> getBoardCastType(){
				QList<api_audio_info> list_;
				api_audio_info audioInfo_t;
				switch (nBoardCastType)
				{
				case CALL_MANAGEMENT:
				{
										audioInfo_t.mAudioFileName = "����/��������_ǰ.mp3";
										audioInfo_t.isNum = false;								
										list_.append(audioInfo_t);

										std::string groupNam = (char*)nSeatNo;
										for (int i = 0; i < groupNam.size(); ++i)
										{
											audioInfo_t.mAudioFileName = "����/" + groupNam.substr(i, 1) + ".mp3";
											audioInfo_t.isNum = true;
											list_.append(audioInfo_t);
										}

										audioInfo_t.mAudioFileName = "����/�Ż���������.mp3";
										audioInfo_t.isNum = false;
										list_.append(audioInfo_t);
										break;
				}
				case CALL_SERVICE:
				{
									 audioInfo_t.mAudioFileName = "����/��������_ǰ.mp3";
									 audioInfo_t.isNum = false;
									 list_.append(audioInfo_t);

									 std::string groupNam = (char*)nSeatNo;
									 for (int i = 0; i < groupNam.size(); ++i)
									 {
										 audioInfo_t.mAudioFileName = "����/" + groupNam.substr(i, 1) + ".mp3";
										 audioInfo_t.isNum = true;
										 list_.append(audioInfo_t);
									 }

									 audioInfo_t.mAudioFileName = "����/���з���Ա_��.mp3";
									 audioInfo_t.isNum = false;
									 list_.append(audioInfo_t);
									 break;
				}
				case DEV_OFFLINE:
				{
									 audioInfo_t.mAudioFileName = "����/�»���ɨ_ǰ.mp3";
									 audioInfo_t.isNum = false;
									 list_.append(audioInfo_t);

									 std::string groupNam = (char*)nSeatNo;
									 for (int i = 0; i < groupNam.size(); ++i)
									 {
										 audioInfo_t.mAudioFileName = "����/" + groupNam.substr(i, 1) + ".mp3";
										 audioInfo_t.isNum = true;
										 list_.append(audioInfo_t);
									 }

									 audioInfo_t.mAudioFileName = "����/�»���ɨ_��.mp3";
									 audioInfo_t.isNum = false;
									 list_.append(audioInfo_t);
									 break;
				}
				case OFFER_FOODS:
				{
									audioInfo_t.mAudioFileName = "����/�������_ǰ.mp3";
									audioInfo_t.isNum = false;
									list_.append(audioInfo_t);

									audioInfo_t.mAudioFileName = "����/order.mp3";
									audioInfo_t.isNum = false;
									list_.append(audioInfo_t);
									break;
				}
				case CALL_SEAT:
				{
									audioInfo_t.mAudioFileName = "����/�������_ǰ.mp3";
									audioInfo_t.isNum = false;
									list_.append(audioInfo_t);

									audioInfo_t.mAudioFileName = "����/seat.mp3";
									audioInfo_t.isNum = false;
									list_.append(audioInfo_t);
									break;
				}
				default:
					break;
				}

				return list_;
			}
			std::string getSeatNo(){
				std::string seatNo = (char*)nSeatNo;
				return "audiofile_" + seatNo + ".mp3";
			}
			void read_json(boost::property_tree::ptree parser){
				try
				{
					memcpy(this->nSeatNo, parser.get<std::string>("nSeatNo").c_str(), parser.get<std::string>("nSeatNo").length());
					this->nBoardCastType = parser.get<short>("nBoardCastType");
					this->nPlayCycleNum = parser.get<short>("nBoardCastType");
				}
				catch (boost::property_tree::ptree_error const & ec)
				{
					//AppConfigHandler.Info("struct api_boardcast_info read_json error : " + string(ec.what()));
					Log::Info("struct api_boardcast_info read_json error : ", ec.what());
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
					//AppConfigHandler.Info("struct api_boardcast_info read_json error : " + string(ec.what()));
					Log::Info("struct api_boardcast_info read_json error : ", ec.what());
				}
			}
			void write_json(boost::property_tree::ptree &parser){
				parser.put<short>("nCallVioceValue", this->nCallVioceValue);
			}
		}api_syncdata_info_t;
    }  // namespace server
}  // namespace dm