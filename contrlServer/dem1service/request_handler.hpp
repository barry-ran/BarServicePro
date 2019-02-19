#ifndef M1_REQUEST_HANDLER_HPP
#define M1_REQUEST_HANDLER_HPP

#include <string>
#include <map>
#include <string>
#include <memory>
#include <vector>
#include <iostream>

#include "APIProtocol.h"
#include "response.hpp"

#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace dem1 {
	namespace server {

		class connection;
		class request_handler {
		public:
			request_handler();

            int start(std::shared_ptr<connection>  dm_conn);
			void stop();

			//���������ն��豸
			int handle_request_client_reboot(protocol_head_t *head, netbuffer *buf);
			int handle_request_client_reboot(boost::property_tree::ptree parser);
			//Զ�̻����ն��豸
			int handle_request_client_remote_wakeup(protocol_head_t *head, netbuffer *buf);
			int handle_request_client_remote_wakeup(boost::property_tree::ptree parser);
			//���Ʋ�������
			int handle_request_boardcast_msg(protocol_head_t *head, netbuffer *buf);
			int handle_request_boardcast_msg(boost::property_tree::ptree parser);
			//����ͻ�ע����Ϣ
			int handle_request_host_register(protocol_head_t *head, netbuffer *buf);
			int handle_request_host_register(boost::property_tree::ptree parser);
			//����ػ�
			int handle_request_client_shutdown(boost::property_tree::ptree parser);
			//ͬ�����з�������
			int handle_request_sync_data(boost::property_tree::ptree parser);
			//����ͻ��������ȡ����������С
			int handle_request_call_voice_value(boost::property_tree::ptree parser);
			//������з�����Ƹı����������С
			int handle_request_control_call_voice(boost::property_tree::ptree parser);
			//ȡ����������
			int handle_request_cancel_boardcast(boost::property_tree::ptree parser);
			//��������ע��
			int handle_request_masterLocker_register(boost::property_tree::ptree parser);

			void handle_json_header(boost::property_tree::ptree header, std::string headTitle, std::string &json_str);

		private:
			std::shared_ptr<connection> curr_conn_;//��ǰ�ӣϣãˣţ�����
		};

	}  // namespace server
}  // namespace dem1

#endif  // M1_REQUEST_HANDLER_HPP
