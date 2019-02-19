#ifndef OPENCVTEST_H
#define OPENCVTEST_H

#include <QtWidgets/QMainWindow>
#include "ui_openCvTest.h"
#include <QTimer>
#include <QImage>
//#include "opencv/cv.h"
//#include "opencv/highgui.h"

#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QCameraInfo>
#include <QButtonGroup>

class openCvTest : public QMainWindow
{
	Q_OBJECT

public:
	openCvTest(QWidget *parent = 0);
	~openCvTest();
private slots:
	void slotOnOpen();
	void slotOnClose();
	void slotOnCut();
	void readFrame();

	void ShowTheCapture();
	void SavePicture();
	void displayImage(int, QImage image);
	void slotOnFunc();
	void slotOnGetFaceDetectionRespond(int nCode, QString sMsg, int nRespondCode);
	void slotOnGetCommitFaceDataRespond(int nCode, QString sMsg, int nRespondCode);
	void slotOnCounter();
private:
	void clearFiles();
private:
	Ui::openCvTestClass ui;
	QTimer    *timer;
	QTimer    *m_counter_timer;
	QImage    *imag;
	//CvCapture *cam;// ��Ƶ��ȡ�ṹ�� ������Ϊ��Ƶ��ȡ������һ������
	//IplImage  *frame;//����IplImage����ָ�룬���������ڴ�ռ������ÿһ֡ͼ��

	QCamera *camera;//����ͷ
	QCameraViewfinder * viewfinder;//����ͷȡ��������
	QCameraImageCapture * imageCapture;//��ͼ����
	QList<QCameraInfo> infoList;
	QButtonGroup *group;
	int m_counter;
};

#endif // OPENCVTEST_H
