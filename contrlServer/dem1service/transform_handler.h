#pragma once
#include <memory>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include <list>
#include <map>

#include "APIProtocol.h"

using namespace std;

// ʹ�ú��������ʵ��
#define TransformHandler transform_handler::GetInstance()

namespace dem1 {
	namespace server {
		class connection;
class transform_handler
{
private:
	friend class auto_ptr<transform_handler>;				/// ʹ������ָ��
	/// ��ʹ��δ������Ҳ�ᱻ����(����);�������ʹ��static ���Σ���˼��ֻ��һ������ᱻ����������
	/// ���캯������Ϊ private �����Է�ֹ����Ĳ�����(auto_ptr need #include <memory>)
	static auto_ptr<transform_handler> auto_ptr_instance;	/// Ωһʵ��

private:
	transform_handler();	/// ���캯��(ע��:���췽��˽��)
	~transform_handler(void);							/// ��������

public:
	static transform_handler& GetInstance(void);		/// ʵ��(��������)

	bool rebootClientHandler(const api_client_info_t &api_info);   //���������ն��豸
	bool shutdownClientHandler(const api_client_info_t &api_info);  //����ػ�����
	bool remoteWakeUpClientHandler(const api_client_info_t &api_info);   //����Զ�̻����ն��豸

	void updateHostSession(std::string sessionId);
	std::string getHostSession();

	void syncData(const api_syncdata_info_t &api_reg);
	short getSyncData();

	//��������
	void addMapList(api_masterLocker_register_info api_info, std::string sessionId);
	void removeSessionID(std::string sessionId);
	std::string getSessionIdByIP(std::string ip);
	void HttpHandleOffLineStatus(string pcName, string barId, string mac);
private:
	std::string host_sessionId;
	boost::mutex mutex_ctrl;

	short callVoice_value;
	boost::mutex mutex_call;

	boost::mutex mutex_map;
	std::map<std::string, api_masterLocker_register_info> mapList_;
};
	}  // namespace server
} // namespace dem1
