#pragma once

#pragma once
#include <memory>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include <list>

#include "APIProtocol.h"
#include <QList>

using namespace std;

// ʹ�ú��������ʵ��
#define EventHandler Event_Handler::GetInstance()

namespace dm {
	namespace server {
		class connection;
		class Event_Handler
		{
		private:
			friend class auto_ptr<Event_Handler>;				/// ʹ������ָ��
			/// ��ʹ��δ������Ҳ�ᱻ����(����);�������ʹ��static ���Σ���˼��ֻ��һ������ᱻ����������
			/// ���캯������Ϊ private �����Է�ֹ����Ĳ�����(auto_ptr need #include <memory>)
			static auto_ptr<Event_Handler> auto_ptr_instance;	/// Ωһʵ��

		private:
			Event_Handler();	/// ���캯��(ע��:���췽��˽��)
			~Event_Handler(void);							/// ��������
		public:
			static Event_Handler& GetInstance(void);		/// ʵ��(��������)

			//������Ƶ�ļ�
			bool playBoardcastMsg(const api_client_info_t &api_info, std::string name);
			//��ȡ������ʱ��
			DWORD MCIStatus_music_length();
			//��ȡ��ǰ����ʱ��
			DWORD MCIStatus_music_pos();
			//�رղ���
			void close_mci();
			//����
			DWORD MCIPlay();

			//�б����
			void addBoardCastListItem(const api_boardcast_info_t &api_info);
			void removeBoardCastListItem(const api_boardcast_info_t &api_info);
			//
			void boardcastCycleThreadFunc();

			void waitforPlayFinished(int sec = 500);
		private:
			UINT wDeviceID_;
			bool is_thread_exit_;
			QList<api_boardcast_info_t> boardCast_list_;
			QList<api_boardcast_info_t> boardCast_list_copy_;
			boost::mutex ctrl_mutex_;
			boost::shared_ptr<boost::thread> list_cycle_thread_;
		};
	}  // namespace server
} // namespace dm


