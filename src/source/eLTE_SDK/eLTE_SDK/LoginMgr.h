/********************************************************************
filename		: 	LoginMgr.h
author			:	zWX229156
created		    :	2015/1/5
description	    :	用户登录类
copyright		:	Copyright (C) 2015-2017
history			:	2015/1/5 初始版本
*********************************************************************/

#ifndef __LOGIN_MGR_H__
#define __LOGIN_MGR_H__

#include "eLTE_Types.h"
#include "eLTE_Message.h"
#include <string>

#define WAIT_SERVER_RSP() \
	iRet = m_pUserMgr->WaitObject(WAIT_OBJECT_TIME);								\
	if (eLTE_SDK_ERR_SUCCESS != iRet)												\
	{																				\
		CServerMgr& serverMgr = const_cast<CServerMgr&>(m_pUserMgr->GetServerMgr());\
		if(!serverMgr.ServerIsRunning() || 0 != m_pUserMgr->GetServerStatus())		\
		{																			\
			m_pUserMgr->SetServerStatus(0);											\
			return eLTE_SDK_ERR_SERVER_NOT_RUNNING;									\
		}																			\
		return iRet;																\
	}																				\

class CUserMgr;//lint !e763
class CLoginMgr
{
public:
	CLoginMgr();
	~CLoginMgr();

	//登录
	ELTE_INT32 Login(const ELTE_CHAR* pUserId, const ELTE_CHAR* pPasswd, const ELTE_CHAR* pServerIP, const ELTE_CHAR* pLocalIP, const ELTE_UINT32& sipPort) const;

	//注销
	ELTE_INT32 Logout(const ELTE_CHAR* pUserId) const;

	//触发状态上报
	ELTE_INT32 TriggerStatusReport(const ELTE_INT32& iEnableStatusReport) const;

	//设置用户管理类
	ELTE_VOID SetUserMgr(CUserMgr* pUserMgr);

private:
	CUserMgr*    m_pUserMgr;
};

#endif // __LOGIN_MGR_H__
