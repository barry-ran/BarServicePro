#ifndef HANDLEEVENT_H
#define HANDLEEVENT_H

#pragma once
#include <memory>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include <list>
#include <string>

#include "APIProtocol.h"
#include <QList>
#include <QObject>

using namespace std;

namespace dm {
	namespace server {
class handleEvent : public QObject
{
	Q_OBJECT

public:
	static handleEvent* instance();
private:
	explicit handleEvent(QObject *parent = 0);
	~handleEvent();
public:
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
	//��������
	DWORD  MCISetVolume(DWORD dwVol);
	//���ÿ�������
	void appAutoRun(bool bAutoRun);

	//�б����
	void addBoardCastListItem(const api_boardcast_info_t &api_info);
	void removeBoardCastListItem(const api_boardcast_info_t &api_info);
	//
	void boardcastCycleThreadFunc();

	void waitforPlayFinished(int sec = 500);
signals:
	void sigOnChanged();
	private slots:
	void slotOnChanged();
private:
	static handleEvent* m_pInstance;

	UINT wDeviceID_;
	bool is_thread_exit_;
	QList<api_boardcast_info_t> boardCast_list_;
	QList<api_boardcast_info_t> boardCast_list_copy_;
	QList<api_boardcast_info_t> boardCast_list_cancel_;
	boost::mutex ctrl_mutex_;
	boost::mutex cancel_mutex_;
	boost::shared_ptr<boost::thread> list_cycle_thread_;
	std::string curr_play_seatNo;
	int curr_play_boardType;
};
	}  // namespace server
} // namespace dm
#endif // HANDLEEVENT_H
