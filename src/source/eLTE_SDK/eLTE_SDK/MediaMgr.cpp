#include "stdafx.h"
#include "MediaMgr.h"
#include "eLTE_Log.h"
#include "eLTE_Error.h"
#include "eLTE_Xml.h"
#include "UserMgr.h"
#include "eLTE_Tool.h"
#include "SharedMemoryMgr.h"

CMediaMgr::CMediaMgr()
{
	m_pUserMgr = NULL;
}

CMediaMgr::~CMediaMgr()
{
	m_pUserMgr = NULL;
}

ELTE_VOID CMediaMgr::SetUserMgr(CUserMgr* pUserMgr)
{
	LOG_TRACE();
	if(NULL == pUserMgr)
	{
		LOG_RUN_ERROR("UserMgr is null.");
		return;
	}
	m_pUserMgr = pUserMgr; 
}

ELTE_INT32 CMediaMgr::GetUserRECFileInfoList(const ELTE_CHAR* pQueryXml, ELTE_CHAR** pRspXml) const
{
	LOG_TRACE();
	if(NULL == m_pUserMgr)
	{
		LOG_RUN_ERROR("UserMgr is null.");
		return eLTE_SDK_ERR_NULL_POINTER;
	}
	CXml reqXml;
	if(!reqXml.Parse(pQueryXml))
	{
		LOG_RUN_ERROR("ReqXml parse failed, param is %s.", pQueryXml);
		return eLTE_SDK_ERR_XML_PARSE;
	}

	//发送消息
	SSL_Socket& socket = const_cast<SSL_Socket&>(m_pUserMgr->GetSSLSocket());
	MutexLocker Locker(m_pUserMgr->GetMutexHandle());
	ELTE_INT32 iRet = socket.SendMsg(ELTE_SERVICE_GETUSERRECFILEINFOLIST_REQ, reqXml, TRUE);
	if(eLTE_SDK_ERR_SUCCESS != iRet) 
	{
		return iRet;
	}

	WAIT_SERVER_RSP();
	const PACKET_DATA& packetData = m_pUserMgr->GetPacketData();
	iRet = packetData.RspCode;

	ELTE_UINT32 uiDataLen = packetData.PacketLength - PACKET_HEAD_SIZE;
	if(uiDataLen > 0)
	{
		*pRspXml = new ELTE_CHAR[uiDataLen + 1];
		if(NULL == *pRspXml)
		{
			LOG_RUN_ERROR("New RspXml failed.");
			::ResetEvent(m_pUserMgr->GetEventHandle());
			return eLTE_SDK_ERR_CREATE_OBJECT;
		}
		eSDK_MEMSET(*pRspXml, 0x00, uiDataLen + 1);
		eSDK_MEMCPY(*pRspXml, uiDataLen + 1, packetData.Value, uiDataLen);
	}
	else
	{
		*pRspXml = NULL;
	}
	::ResetEvent(m_pUserMgr->GetEventHandle());
	return iRet;
}

ELTE_INT32 CMediaMgr::StartRealPlay(const ELTE_CHAR* pResourceID, const ELTE_CHAR* pVideoParam) const
{
	LOG_TRACE();
	SET_MEDIA_XML(pVideoParam);

	ELTE_UINT32 xmlLen = 0;
	LOG_RUN_INFO("ReqXml is %s.", reqXml.GetXMLStream(xmlLen));

	//发送消息
	SSL_Socket& socket = const_cast<SSL_Socket&>(m_pUserMgr->GetSSLSocket());
	MutexLocker Locker(m_pUserMgr->GetMutexHandle());
	ELTE_INT32 iRet = socket.SendMsg(ELTE_SERVICE_STARTREALPLAY_REQ, reqXml, TRUE);
	if(eLTE_SDK_ERR_SUCCESS != iRet) 
	{
		return iRet;
	}

	GET_PACKAGE_DATA_MEMORY();
	return iRet;
}

ELTE_INT32 CMediaMgr::RecvVideoPlay(const ELTE_CHAR* pResourceID) const
{
	LOG_TRACE();

	if(NULL == m_pUserMgr)
	{
		LOG_RUN_ERROR("UserMgr is null.");
		return eLTE_SDK_ERR_NULL_POINTER;
	}

	CONSTRUCT_XML("ResourceID",pResourceID);

	ELTE_UINT32 xmlLen = 0;
	LOG_RUN_INFO("ReqXml is %s.", reqXml.GetXMLStream(xmlLen));

	//发送消息
	SSL_Socket& socket = const_cast<SSL_Socket&>(m_pUserMgr->GetSSLSocket());
	MutexLocker Locker(m_pUserMgr->GetMutexHandle());
	ELTE_INT32 iRet = socket.SendMsg(ELTE_SERVICE_RECVVIDEOPLAY_REQ, reqXml, TRUE);
	if(eLTE_SDK_ERR_SUCCESS != iRet) 
	{
		return iRet;
	}

	GET_PACKAGE_DATA_MEMORY();
	return iRet;
}

ELTE_INT32 CMediaMgr::PTZControl(const ELTE_CHAR* pResourceID, ELTE_UINT32 iPTZControlCode, ELTE_UINT32 iPTZControlValue) const
{
	LOG_TRACE();
	if(NULL == m_pUserMgr)
	{
		LOG_RUN_ERROR("UserMgr is null.");
		return eLTE_SDK_ERR_NULL_POINTER;
	}

	CXml reqXml;
	(void)reqXml.AddElem("Content");
	(void)reqXml.AddChildElem("ResourceID");
	(void)reqXml.IntoElem();
	(void)reqXml.SetElemValue(pResourceID);
	(void)reqXml.AddElem("PTZControlCode");
	(void)reqXml.SetElemValue(eLTE_Tool::UInt2String(iPTZControlCode).c_str());
	(void)reqXml.AddElem("PTZControlValue");
	(void)reqXml.SetElemValue(eLTE_Tool::UInt2String(iPTZControlValue).c_str());

	//发送消息
	SSL_Socket& socket = const_cast<SSL_Socket&>(m_pUserMgr->GetSSLSocket());
	MutexLocker Locker(m_pUserMgr->GetMutexHandle());
	ELTE_INT32 iRet = socket.SendMsg(ELTE_SERVICE_PTZCONTROL_REQ, reqXml, TRUE);
	if(eLTE_SDK_ERR_SUCCESS != iRet) 
	{
		return iRet;
	}
	WAIT_SERVER_RSP();

	iRet = m_pUserMgr->GetPacketData().RspCode;
	::ResetEvent(m_pUserMgr->GetEventHandle());
	return iRet;
}

ELTE_INT32 CMediaMgr::StopRealPlay(const ELTE_CHAR* pResourceID) const
{
	LOG_TRACE();
	if(NULL == m_pUserMgr)
	{
		LOG_RUN_ERROR("UserMgr is null.");
		return eLTE_SDK_ERR_NULL_POINTER;
	}

	CXml reqXml;
	(void)reqXml.AddElem("Content");
	(void)reqXml.AddChildElem("ResourceID");
	(void)reqXml.IntoElem();
	(void)reqXml.SetElemValue(pResourceID);

	//发送消息
	SSL_Socket& socket = const_cast<SSL_Socket&>(m_pUserMgr->GetSSLSocket());
	MutexLocker Locker(m_pUserMgr->GetMutexHandle());
	ELTE_INT32 iRet = socket.SendMsg(ELTE_SERVICE_STOPREALPLAY_REQ, reqXml, TRUE);
	if(eLTE_SDK_ERR_SUCCESS != iRet) 
	{
		return iRet;
	}
	WAIT_SERVER_RSP();
	iRet = m_pUserMgr->GetPacketData().RspCode;
	::ResetEvent(m_pUserMgr->GetEventHandle());
	if(eLTE_SDK_ERR_SUCCESS == iRet && !CUserMgr::m_iBypass)
	{
		SharedMemoryMgr::Instance().DeleteSharedMemory(pResourceID);
	}
	return iRet;
}

ELTE_INT32 CMediaMgr::StartVideoDispatch(const ELTE_CHAR* pResourceID, const ELTE_CHAR* pVideoDispatchParam) const
{
	LOG_TRACE();
	SET_MEDIA_XML(pVideoDispatchParam);

	ELTE_UINT32 xmlLen = 0;
	LOG_RUN_INFO("ReqXml is %s.", reqXml.GetXMLStream(xmlLen));

	//发送消息
	SSL_Socket& socket = const_cast<SSL_Socket&>(m_pUserMgr->GetSSLSocket());
	MutexLocker Locker(m_pUserMgr->GetMutexHandle());
	ELTE_INT32 iRet = socket.SendMsg(ELTE_SERVICE_STARTDISPATCHVIDEO_REQ, reqXml, TRUE);
	if(eLTE_SDK_ERR_SUCCESS != iRet) 
	{
		return iRet;
	}
	WAIT_SERVER_RSP();

	iRet = m_pUserMgr->GetPacketData().RspCode;
	::ResetEvent(m_pUserMgr->GetEventHandle());
	return iRet;
}

ELTE_INT32 CMediaMgr::StopVideoDispatch(const ELTE_CHAR* pResourceID, const ELTE_CHAR* pVideoDispatchParam) const
{
	LOG_TRACE();
	SET_MEDIA_XML(pVideoDispatchParam);

	ELTE_UINT32 xmlLen = 0;
	LOG_RUN_INFO("ReqXml is %s.", reqXml.GetXMLStream(xmlLen));

	//发送消息
	SSL_Socket& socket = const_cast<SSL_Socket&>(m_pUserMgr->GetSSLSocket());
	MutexLocker Locker(m_pUserMgr->GetMutexHandle());
	ELTE_INT32 iRet = socket.SendMsg(ELTE_SERVICE_STOPDISPATCHVIDEO_REQ, reqXml, TRUE);
	if(eLTE_SDK_ERR_SUCCESS != iRet) 
	{
		return iRet;
	}
	WAIT_SERVER_RSP();

	iRet = m_pUserMgr->GetPacketData().RspCode;
	::ResetEvent(m_pUserMgr->GetEventHandle());
	return iRet;
}

//发起视频上墙
ELTE_INT32 CMediaMgr::VWallStart(const ELTE_CHAR* pResourceID, const ELTE_CHAR* pVideoParam) const
{
	LOG_TRACE();
	SET_MEDIA_XML(pVideoParam);

	ELTE_UINT32 xmlLen = 0;
	LOG_RUN_INFO("ReqXml is %s.", reqXml.GetXMLStream(xmlLen));

	//发送消息
	SSL_Socket& socket = const_cast<SSL_Socket&>(m_pUserMgr->GetSSLSocket());
	MutexLocker Locker(m_pUserMgr->GetMutexHandle());
	ELTE_INT32 iRet = socket.SendMsg(ELTE_SERVICE_VWALLSTART_REQ, reqXml, TRUE);
	if(eLTE_SDK_ERR_SUCCESS != iRet) 
	{
		return iRet;
	}

	WAIT_SERVER_RSP();
	const PACKET_DATA& packetData = m_pUserMgr->GetPacketData();
	iRet = packetData.RspCode;

	::ResetEvent(m_pUserMgr->GetEventHandle());

	if (eLTE_SDK_ERR_SUCCESS != iRet)
	{
		LOG_RUN_ERROR("GetPacketData failed.");
	}
	return iRet;
}

//终止视频上墙
ELTE_INT32 CMediaMgr::VWallStop(const ELTE_CHAR* pResourceID, const ELTE_CHAR* pVWallStopParam) const
{
	LOG_TRACE();
	SET_MEDIA_XML(pVWallStopParam);

	ELTE_UINT32 xmlLen = 0;
	LOG_RUN_INFO("ReqXml is %s.", reqXml.GetXMLStream(xmlLen));

	//发送消息
	SSL_Socket& socket = const_cast<SSL_Socket&>(m_pUserMgr->GetSSLSocket());
	MutexLocker Locker(m_pUserMgr->GetMutexHandle());
	ELTE_INT32 iRet = socket.SendMsg(ELTE_SERVICE_VWALLSTOP_REQ, reqXml, TRUE);
	if(eLTE_SDK_ERR_SUCCESS != iRet) 
	{
		return iRet;
	}
	WAIT_SERVER_RSP();

	iRet = m_pUserMgr->GetPacketData().RspCode;
	::ResetEvent(m_pUserMgr->GetEventHandle());
	return iRet;
}
// 
// ELTE_INT32 CMediaMgr::TelephoneDial(const ELTE_CHAR* pTelNumber) const
// {
// 	LOG_TRACE();
// 	if(NULL == m_pUserMgr)
// 	{
// 		LOG_RUN_ERROR("UserMgr is null.");
// 		return eLTE_SDK_ERR_NULL_POINTER;
// 	}
// 
// 	//构造xml
// 	CONSTRUCT_XML("TelNumber",pTelNumber);
// 
// 	ELTE_UINT32 xmlLen = 0;
// 	LOG_RUN_INFO("ReqXml is %s.", reqXml.GetXMLStream(xmlLen));
// 
// 	//发送消息
// 	SSL_Socket& socket = const_cast<SSL_Socket&>(m_pUserMgr->GetSSLSocket());
// 	MutexLocker Locker(m_pUserMgr->GetMutexHandle());
// 	ELTE_INT32 iRet = socket.SendMsg(ELTE_SERVICE_TELEPHONEDIAL_REQ, reqXml, TRUE);
// 	if(eLTE_SDK_ERR_SUCCESS != iRet) 
// 	{
// 		return iRet;
// 	}
// 
// 	WAIT_SERVER_RSP();
// 	const PACKET_DATA& packetData = m_pUserMgr->GetPacketData();
// 	iRet = packetData.RspCode;
// 
// 	::ResetEvent(m_pUserMgr->GetEventHandle());
// 
// 	if (eLTE_SDK_ERR_SUCCESS != iRet)
// 	{
// 		LOG_RUN_ERROR("GetPacketData failed.");
// 	}
// 	return iRet;
// }
// 
// ELTE_INT32 CMediaMgr::TelephoneHangup(const ELTE_CHAR* pTelNumber) const
// {
// 	LOG_TRACE();
// 	if(NULL == m_pUserMgr)
// 	{
// 		LOG_RUN_ERROR("UserMgr is null.");
// 		return eLTE_SDK_ERR_NULL_POINTER;
// 	}
// 
// 	CONSTRUCT_XML("TelNumber",pTelNumber);
// 
// 	ELTE_UINT32 xmlLen = 0;
// 	LOG_RUN_INFO("ReqXml is %s.", reqXml.GetXMLStream(xmlLen));
// 
// 	//发送消息
// 	SSL_Socket& socket = const_cast<SSL_Socket&>(m_pUserMgr->GetSSLSocket());
// 	MutexLocker Locker(m_pUserMgr->GetMutexHandle());
// 	ELTE_INT32 iRet = socket.SendMsg(ELTE_SERVICE_TELEPHONEHANGUP_REQ, reqXml, TRUE);
// 	if(eLTE_SDK_ERR_SUCCESS != iRet) 
// 	{
// 		return iRet;
// 	}
// 
// 	WAIT_SERVER_RSP();
// 	const PACKET_DATA& packetData = m_pUserMgr->GetPacketData();
// 	iRet = packetData.RspCode;
// 
// 	::ResetEvent(m_pUserMgr->GetEventHandle());
// 
// 	if (eLTE_SDK_ERR_SUCCESS != iRet)
// 	{
// 		LOG_RUN_ERROR("GetPacketData failed.");
// 	}
// 	return iRet;
// }

ELTE_INT32 CMediaMgr::StartDiscreetListen(const ELTE_CHAR* pResourceID) const
{
	LOG_TRACE();
	if(NULL == m_pUserMgr)
	{
		LOG_RUN_ERROR("UserMgr is null.");
		return eLTE_SDK_ERR_NULL_POINTER;
	}

	CONSTRUCT_XML("ResourceID",pResourceID);
	
	ELTE_UINT32 xmlLen = 0;
	LOG_RUN_INFO("ReqXml is %s.", reqXml.GetXMLStream(xmlLen));

	//发送消息
	SSL_Socket& socket = const_cast<SSL_Socket&>(m_pUserMgr->GetSSLSocket());
	MutexLocker Locker(m_pUserMgr->GetMutexHandle());
	ELTE_INT32 iRet = socket.SendMsg(ELTE_SERVICE_STARTDISCREETLISTEN_REQ, reqXml, TRUE);
	if(eLTE_SDK_ERR_SUCCESS != iRet) 
	{
		return iRet;
	}

	WAIT_SERVER_RSP();
	const PACKET_DATA& packetData = m_pUserMgr->GetPacketData();
	iRet = packetData.RspCode;

	::ResetEvent(m_pUserMgr->GetEventHandle());

	if (eLTE_SDK_ERR_SUCCESS != iRet)
	{
		LOG_RUN_ERROR("GetPacketData failed.");
	}
	return iRet;
}

ELTE_INT32 CMediaMgr::StopDiscreetListen(const ELTE_CHAR* pResourceID) const
{
	LOG_TRACE();
	if(NULL == m_pUserMgr)
	{
		LOG_RUN_ERROR("UserMgr is null.");
		return eLTE_SDK_ERR_NULL_POINTER;
	}

	CONSTRUCT_XML("ResourceID",pResourceID);

	ELTE_UINT32 xmlLen = 0;
	LOG_RUN_INFO("ReqXml is %s.", reqXml.GetXMLStream(xmlLen));

	//发送消息
	SSL_Socket& socket = const_cast<SSL_Socket&>(m_pUserMgr->GetSSLSocket());
	MutexLocker Locker(m_pUserMgr->GetMutexHandle());
	ELTE_INT32 iRet = socket.SendMsg(ELTE_SERVICE_STOPDISCREETLISTEN_REQ, reqXml, TRUE);
	if(eLTE_SDK_ERR_SUCCESS != iRet) 
	{
		return iRet;
	}

	WAIT_SERVER_RSP();
	const PACKET_DATA& packetData = m_pUserMgr->GetPacketData();
	iRet = packetData.RspCode;

	::ResetEvent(m_pUserMgr->GetEventHandle());

	if (eLTE_SDK_ERR_SUCCESS != iRet)
	{
		LOG_RUN_ERROR("GetPacketData failed.");
	}
	return iRet;
}

ELTE_INT32 CMediaMgr::StartEnvironmentListen(const ELTE_CHAR* pResourceID) const
{
	LOG_TRACE();
	if(NULL == m_pUserMgr)
	{
		LOG_RUN_ERROR("UserMgr is null.");
		return eLTE_SDK_ERR_NULL_POINTER;
	}

	CONSTRUCT_XML("ResourceID",pResourceID);

	ELTE_UINT32 xmlLen = 0;
	LOG_RUN_INFO("ReqXml is %s.", reqXml.GetXMLStream(xmlLen));

	//发送消息
	SSL_Socket& socket = const_cast<SSL_Socket&>(m_pUserMgr->GetSSLSocket());
	MutexLocker Locker(m_pUserMgr->GetMutexHandle());
	ELTE_INT32 iRet = socket.SendMsg(ELTE_SERVICE_STARTENVIRLISTEN_REQ, reqXml, TRUE);
	if(eLTE_SDK_ERR_SUCCESS != iRet)
	{
		return iRet;
	}

	WAIT_SERVER_RSP();
	const PACKET_DATA& packetData = m_pUserMgr->GetPacketData();
	iRet = packetData.RspCode;

	::ResetEvent(m_pUserMgr->GetEventHandle());

	if (eLTE_SDK_ERR_SUCCESS != iRet)
	{
		LOG_RUN_ERROR("GetPacketData failed.");
	}
	return iRet;
}

// ELTE_INT32 CMediaMgr::startRecord(const ELTE_CHAR* pResourceID, const ELTE_CHAR* pTypeParam) const
// {
// 	LOG_TRACE();
// 	SET_MEDIA_XML(pTypeParam);
// 
// 	ELTE_UINT32 xmlLen = 0;
// 	LOG_RUN_INFO("ReqXml is %s.", reqXml.GetXMLStream(xmlLen));
// 
// 	//发送消息
// 	SSL_Socket& socket = const_cast<SSL_Socket&>(m_pUserMgr->GetSSLSocket());
// 	MutexLocker Locker(m_pUserMgr->GetMutexHandle());
// 	ELTE_INT32 iRet = socket.SendMsg(ELTE_SERVICE_STARTRECORD_REQ, reqXml, TRUE);
// 	if(eLTE_SDK_ERR_SUCCESS != iRet) 
// 	{
// 		return iRet;
// 	}
// 
// 	WAIT_SERVER_RSP();
// 	const PACKET_DATA& packetData = m_pUserMgr->GetPacketData();
// 	iRet = packetData.RspCode;
// 
// 	::ResetEvent(m_pUserMgr->GetEventHandle());
// 
// 	if (eLTE_SDK_ERR_SUCCESS != iRet)
// 	{
// 		LOG_RUN_ERROR("GetPacketData failed.");
// 	}
// 	return iRet;
// }

// ELTE_INT32 CMediaMgr::stopRecord(const ELTE_CHAR* pResourceID, const ELTE_CHAR* pTypeParam) const
// {
// 	LOG_TRACE();
// 	SET_MEDIA_XML(pTypeParam);
// 
// 	ELTE_UINT32 xmlLen = 0;
// 	LOG_RUN_INFO("ReqXml is %s.", reqXml.GetXMLStream(xmlLen));
// 
// 	//发送消息
// 	SSL_Socket& socket = const_cast<SSL_Socket&>(m_pUserMgr->GetSSLSocket());
// 	MutexLocker Locker(m_pUserMgr->GetMutexHandle());
// 	ELTE_INT32 iRet = socket.SendMsg(ELTE_SERVICE_STOPRECORD_REQ, reqXml, TRUE);
// 	if(eLTE_SDK_ERR_SUCCESS != iRet) 
// 	{
// 		return iRet;
// 	}
// 
// 	WAIT_SERVER_RSP();
// 	const PACKET_DATA& packetData = m_pUserMgr->GetPacketData();
// 	iRet = packetData.RspCode;
// 
// 	::ResetEvent(m_pUserMgr->GetEventHandle());
// 
// 	if (eLTE_SDK_ERR_SUCCESS != iRet)
// 	{
// 		LOG_RUN_ERROR("GetPacketData failed.");
// 	}
// 	return iRet;
// }