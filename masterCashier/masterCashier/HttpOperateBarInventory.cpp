#include "HttpOperateBarInventory.h"
#include <QScriptEngine>
#include <QScriptValue>

#include "appconfig.h"
#include "enumData.h"
#include "constData.h"
#include "HttpSignal.h"
#include "commonFun.h"

using namespace dm::server;

HttpOperateBarInventory::HttpOperateBarInventory(int nType, QString sRemarks, QList<ReturnGoodsInfo_t> lReturnGoodsInfoList)
{
	QString goodsArray = createReturnGoodsListJson(lReturnGoodsInfoList);
	setReqUrlAddress(commonFun::getRequestUrl() + c_sHttpOperateBarInventoryAction);
	QString allParam = QString("type=%1&mark=%2&datas=%3").arg(nType).arg(sRemarks).arg(goodsArray);
	QByteArray array;
	array.append(allParam);
	setReqParams(array);
}

HttpOperateBarInventory::~HttpOperateBarInventory()
{

}

void HttpOperateBarInventory::processResponse(QString strResult)
{
	QScriptEngine engine;
	QScriptValue sc = engine.evaluate("value=" + strResult);
	int nCode = sc.property("code").toInt32();
	QString sMsg = sc.property("desc").toString();
	if (!sc.property("code").isValid())
	{
		AppConfigHandler.Info(QStringLiteral("HttpOperateBarInventory ���ز���json��ʽ����").toStdString());
		nCode = e_connectServerError;
		sMsg = c_sServerJsonError;
	}
	if (nCode != e_success)
	{
		AppConfigHandler.Info(this->getTestUrl().toStdString());
	}

	AppConfigHandler.Info("HttpOperateBarInventory" + strResult.toStdString());
	HttpSignal::instance()->sigOnRespondBarInventory(nCode, sMsg);
	this->deleteLater();
}

void HttpOperateBarInventory::processError()
{
	HttpSignal::instance()->sigOnRespondBarInventory(e_connectServerError, c_sNetError);
	this->deleteLater();
}

QString HttpOperateBarInventory::createReturnGoodsListJson(const QList<ReturnGoodsInfo_t> &returnGoodsInfoList)
{
	QJsonArray jsonArray;
	int nLen = returnGoodsInfoList.length();
	ReturnGoodsInfo_t pGoodsInfo;
	for (int i = 0; i < nLen; i++)
	{
		pGoodsInfo = returnGoodsInfoList[i];
		QJsonObject dataJson;
		dataJson.insert("goodsId", pGoodsInfo.sGoodsId);
		dataJson.insert("operInventory", pGoodsInfo.nNum);
		dataJson.insert("operPrice", pGoodsInfo.dPrice);
		jsonArray.insert(i, dataJson); //
	}

	QJsonDocument document;
	document.setArray(jsonArray);
	QByteArray byte_array = document.toJson(QJsonDocument::Compact);
	return QString(byte_array);
}
