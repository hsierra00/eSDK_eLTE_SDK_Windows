/*Copyright 2015 Huawei Technologies Co., Ltd. All rights reserved.
eSDK is licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
		http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/

/********************************************************************
filename    :    Logic_Queue.h
author      :    yubinbin wx200189
created     :    2015/01/12
description :    逻辑队列管理类，负责把回调消息和客户端请求消息按队列的形式进行处理
copyright   :    Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
history     :    2015/01/12 初始版本
*********************************************************************/

#ifndef __LOGIC_QUEUE_H__
#define __LOGIC_QUEUE_H__

#include <queue>
#include "openssl/ssl.h"
#include "eLTE_Message.h"


// 设置逻辑队列数据并放入逻辑队列
#define PUSH_LOGIC_QUEUE(msgType, xmlStr, iRet) {\
	if (xmlStr.empty())\
	{\
	QUEUE_DATA _data;\
	_data.ProtocolVersion = PROTOCOL_VERSION;\
	_data.MsgType = msgType;\
	_data.SeqID = SSL_Socket::Instance().GetSeqNum();\
	eSDK_MEMCPY(_data.SessionID, sizeof(_data.SessionID), SessionMgr::Instance().GetSessionID().c_str(), SESSIONID_LENGTH);\
	_data.RspCode = iRet;\
	_data.Type = XML_CONTEXT_TYPE;\
	_data.PacketLength = PACKET_HEAD_SIZE;\
	_data.ssl = SSL_Socket::Instance().GetOptSSL();\
	_data.Value = NULL;\
	iRet = Logic_Queue::Instance().Push(_data);\
	if (eLTE_SVC_ERR_SUCCESS != iRet)\
		{\
		LOG_RUN_ERROR("Logic_Queue Push failed.");\
		delete[] _data.Value;\
		}\
	}\
	else\
	{\
	QUEUE_DATA _data;\
	_data.ProtocolVersion = PROTOCOL_VERSION;\
	_data.MsgType = msgType;\
	_data.SeqID = SSL_Socket::Instance().GetSeqNum();\
	_data.RspCode = iRet;\
	_data.Type = XML_CONTEXT_TYPE;\
	_data.PacketLength = PACKET_HEAD_SIZE+xmlStr.size();\
	_data.ssl = SSL_Socket::Instance().GetOptSSL();\
	_data.Value = new char[xmlStr.size()+1];\
	if (NULL == _data.Value)\
		{\
		LOG_RUN_DEBUG("New queue data buf failed.");\
		return;\
		}\
		eSDK_MEMSET(_data.Value, 0, xmlStr.size()+1);\
		eSDK_MEMCPY(_data.Value, xmlStr.size()+1, xmlStr.c_str(), xmlStr.size());\
		iRet = Logic_Queue::Instance().Push(_data);\
		if (eLTE_SVC_ERR_SUCCESS != iRet)\
		{\
		LOG_RUN_ERROR("Logic_Queue Push failed.");\
		delete[] _data.Value;\
		}\
	}\
}

#define CONSTRUCT_AND_SEND_MESSAGE() \
	PACKET_BODY body;											\
	size_t _size = xmlStr.size();								\
	body.Value = new char[_size+1];								\
	if (NULL == body.Value)										\
	{															\
		LOG_RUN_ERROR("new memory failed.");					\
		head.RspCode = eLTE_SVC_ERR_MEMORY_APPLY;				\
		SSL_WRITE(_ssl, &head, PACKET_HEAD_SIZE);				\
		return;													\
	}															\
	eSDK_MEMSET(body.Value, 0, _size+1);						\
	eSDK_MEMCPY(body.Value, _size+1, xmlStr.c_str(), _size);	\
	head.RspCode = iRet;										\
	head.PacketLength += _size;									\
	SSL_WRITE_SAFE(_ssl, &head, PACKET_HEAD_SIZE, body.Value);	\
	SSL_WRITE_SAFE(_ssl, body.Value, _size, body.Value);		\
	if(NULL != body.Value)										\
	{															\
		delete [] body.Value;									\
		body.Value = NULL;										\
	}															\

#define CONSTRUCT_AND_WRITE_GROUPUSERS_REQ() \
	PACKET_HEAD head(data);	\
	head.MsgType |= RSP_MSG_FLAG;	\
	head.PacketLength = PACKET_HEAD_SIZE;	\
	int groupId;	\
	int iRet = XMLProcess::GetXml_GetGroupUsers_Req(data.Value, groupId);	\
	if (eLTE_SVC_ERR_SUCCESS != iRet)	\
	{	\
		LOG_RUN_ERROR("GetXml_GetGroupUsers_Req failed.");	\
		head.RspCode = iRet;	\
		SSL_WRITE(_ssl, &head, PACKET_HEAD_SIZE);	\
		return;	\
	}	\

#define CONSTRUCT_AND_WRITE_RESOURCEID_REQ() \
	PACKET_HEAD head(data);	\
	head.MsgType |= RSP_MSG_FLAG;	\
	head.PacketLength = PACKET_HEAD_SIZE;	\
	std::string ResourceID;	\
	VWallStop_parameter param;	\
	int iRet = XMLProcess::GetXml_GetResourceID_Req(data.Value, ResourceID);	\
	if (eLTE_SVC_ERR_SUCCESS != iRet)	\
	{	\
		LOG_RUN_ERROR("GetXml_StartDiscreetListen_Req failed.");	\
		head.RspCode = iRet;	\
		SSL_WRITE(_ssl, &head, PACKET_HEAD_SIZE);	\
		return;	\
	}	\

#define CONSTRUCT_AND_WRITE_VOL_HEAD() \
	PACKET_HEAD head(data);	\
	head.MsgType |= RSP_MSG_FLAG;	\
	head.PacketLength = PACKET_HEAD_SIZE;	\
	int resId;	\
	int callType;	\
	int iRet = XMLProcess::GetXml_VolControl_Req(data.Value, resId, callType);	\
	if (eLTE_SVC_ERR_SUCCESS != iRet)	\
	{	\
		LOG_RUN_ERROR("GetXml_VolControl_Req failed.");	\
		head.RspCode = iRet;	\
		SSL_WRITE(_ssl, &head, PACKET_HEAD_SIZE);	\
		return;	\
	}	\

#define CONSTRUCT_AND_WRITE_RESOURCE_HEAD() \
	PACKET_HEAD head(data);	\
	head.MsgType |= RSP_MSG_FLAG;	\
	head.PacketLength = PACKET_HEAD_SIZE;	\
	int resId;	\
	int iRet = XMLProcess::Common_GetResourceID(data.Value, resId);	\
	if (eLTE_SVC_ERR_SUCCESS != iRet)	\
	{	\
		LOG_RUN_ERROR("Common_GetResourceID failed.");	\
		head.RspCode = iRet;	\
		SSL_WRITE(_ssl, &head, PACKET_HEAD_SIZE);	\
		return;	\
	}	\

#define CONSTRUCT_AND_WRITE_GROUP_HEAD() \
	PACKET_HEAD head(data);	\
	head.MsgType |= RSP_MSG_FLAG;	\
	head.PacketLength = PACKET_HEAD_SIZE;	\
	int groupId;	\
	int iRet = XMLProcess::Common_GetGroupID(data.Value, groupId);	\
	if (eLTE_SVC_ERR_SUCCESS != iRet)	\
	{	\
	LOG_RUN_ERROR("Common_GetGroupID failed.");	\
	head.RspCode = iRet;	\
	SSL_WRITE(_ssl, &head, PACKET_HEAD_SIZE);	\
	return;	\
	}	\

#define CONSTRUCT_AND_WRITE_DCGROUPS_HEAD() \
	PACKET_HEAD head(data);	\
	head.MsgType |= RSP_MSG_FLAG;	\
	head.PacketLength = PACKET_HEAD_SIZE;	\
	int userId;	\
	int iRet = XMLProcess::GetXml_GetDcGroups_Req(data.Value, userId);	\
	if (eLTE_SVC_ERR_SUCCESS != iRet)	\
	{	\
	LOG_RUN_ERROR("GetXml_GetDcGroups_Req failed.");	\
	head.RspCode = iRet;	\
	SSL_WRITE(_ssl, &head, PACKET_HEAD_SIZE);	\
	return;	\
	}	\

// 逻辑队列数据
typedef PACKET_DATA QUEUE_DATA;

class Logic_Queue
{
private:
	Logic_Queue(void);
	~Logic_Queue(void);

public:
	static Logic_Queue& Instance();
	int Init();
	void Uninit();
	int Push(const QUEUE_DATA& data);
	
private:
	void Clean();
	static unsigned __stdcall Run(void* param);
	// 操作消息逻辑处理
	void OperationMsg(const QUEUE_DATA& data) const;
	// 回调消息逻辑处理
	void CallBackMsg(const QUEUE_DATA& data) const;
	// 回调消息Respond逻辑处理
	void RespondMsg(const QUEUE_DATA& data) const;

private:
	// 通用接口
	void InterfaceUniversal(const QUEUE_DATA& data) const;
	// 用户管理接口
	void InterfaceUserMgr(const QUEUE_DATA& data) const;
	// 设备管理接口
	void InterfaceDeviceMgr(const QUEUE_DATA& data) const;
	// 媒体接口
	void InterfaceMediaMgr(const QUEUE_DATA& data) const;

	// 业务处理接口
private:
	// 连接服务
	void Connect(const QUEUE_DATA& data) const;
	// 断开服务
	void Disconnect(const QUEUE_DATA& data) const;
	// 保活
	void KeepAlive(const QUEUE_DATA& data) const;
	// 登录
	void Login(const QUEUE_DATA& data) const;
	// 注销
	void Logout(const QUEUE_DATA& data) const;
	// 触发状态上报
	void TriggerStatusReport(const QUEUE_DATA& data) const;
	// 配置管理初始化
	void ProvisionInit(const QUEUE_DATA& data) const;
	// 媒体服务器初始化
	void ProvisionInitMRS(const QUEUE_DATA& data) const;
	// 退出配置管理
	void ProvisionExit(const QUEUE_DATA& data) const;
	// 获取调度台群组列表
	void GetDcGroups(const QUEUE_DATA& data) const;
	// 获取调度台用户列表
	void GetDcUsers(const QUEUE_DATA& data) const;
	// 获取一个群组成员列表
	void GetGroupUsers(const QUEUE_DATA& data) const;
	// 获取一个群组详细信息
	void GetGroupInfo(const QUEUE_DATA& data) const;
	// 获取一个用户详细信息
	void GetUserInfo(const QUEUE_DATA& data) const;
	// 获取一个调度台详细信息
	void GetDcInfo(const QUEUE_DATA& data) const;
	// 订阅群组
	void SubscribeGroup(const QUEUE_DATA& data) const;
	// 获取录像文件列表
	void GetUserRECFileInfoList(const QUEUE_DATA& data) const;
	// 创建动态重组
	void CreateDynamicGroup(const QUEUE_DATA& data) const;
	// 删除动态重组
	void CancelDynamicGroup(const QUEUE_DATA& data) const;
	// 创建派接组、增加派接组成员、删除派接组成员
	void OperatePatchGroup(const QUEUE_DATA& data) const;
	// 删除派接组
	void CancelPatchGroup(const QUEUE_DATA& data) const;
	// 获取调度台派接组列表
	void GetPatchGroups(const QUEUE_DATA& data) const;
	// 获取派接组的成员列表
	void GetGroupMemberByPatchId(const QUEUE_DATA& data) const;
	// 获取派接组属性信息
	void GetPatchGroupInfo(const QUEUE_DATA& data) const;
	// 获取临时组号
	void GetTempGroupID(const QUEUE_DATA& data) const;
	// 创建临时组
	void CreateTempGroup(const QUEUE_DATA& data) const;
	// 开始播放实时视频
	void StartRealPlay(const QUEUE_DATA& data) const;	
	// 开始云台控制
	void PTZControl(const QUEUE_DATA& data) const;
	// 停止播放实时视频
	void StopRealPlay(const QUEUE_DATA& data) const;
	// 发起语音点呼
	void P2PDial(const QUEUE_DATA& data) const;
	// 发起半双工点呼
	void P2PHalfDpxDial(const QUEUE_DATA& data) const;
	// 释放半双工点呼
	void P2PHalfDpxRelease(const QUEUE_DATA& data) const;
	// 接收语音点呼
	void P2PRecv(const QUEUE_DATA& data) const;
	// 拒接语音点呼
	void P2PReject(const QUEUE_DATA& data) const;
	// 挂断语音点呼
	void P2PHangup(const QUEUE_DATA& data) const;
	// 抢话（强拆点呼+发起新点呼）
	void P2PBreakin(const QUEUE_DATA& data) const;
	// 强拆点呼
	void P2PBreakoff(const QUEUE_DATA& data) const;
	// 订阅并自动加入群组
	void SubJoinGroup(const QUEUE_DATA& data) const;
	// 发起组呼（固定和临时组呼）或抢权
	void PTTDial(const QUEUE_DATA& data) const;
	// 释放话权
	void PTTRelease(const QUEUE_DATA& data) const;
	// 退出组呼
	void PTTHangup(const QUEUE_DATA& data) const;
	// 发起紧急组呼
	void PTTEmergency(const QUEUE_DATA& data) const;
	// 强拆组呼
	void GroupBreakoff(const QUEUE_DATA& data) const;
	// 执行静音（点呼、组呼、视频回传）
	void VolMute(const QUEUE_DATA& data) const;
	// 取消静音（点呼、组呼、视频回传）
	void VolUnMute(const QUEUE_DATA& data) const;
	// 订阅/去订阅GIS终端
	void GISSubscribe(const QUEUE_DATA& data) const;
	// 发送短/彩信
	void SDSSendMessage(const QUEUE_DATA& data) const;
	// 开始视频分发
	void StartVideoDispatch(const QUEUE_DATA& data) const;
	// 停止视频分发
	void StopVideoDispatch(const QUEUE_DATA& data) const;
	// 接受视频回传
	void RecvVideoPlay(const QUEUE_DATA& data) const;
	// 开始视频上墙
	void StartVWall(const QUEUE_DATA& data) const;
	//停止视频上墙
	void StopVWall(const QUEUE_DATA& data) const;
	//获取视频上墙ID列表
	void GetDcVWallIDList(const QUEUE_DATA& data) const;
	//查询终端的GIS配置信息
	void GetUserSpecificGISCfg(const QUEUE_DATA& data) const;
	//设置终端的GIS配置信息
	void SetUserSpecificGISCfg(const QUEUE_DATA& data) const;
	//获取调度台订阅的终端列表
	void GetGisSubscription(const QUEUE_DATA& data) const;
	//修改动态重组
	void ModifyDynamicGroup(const QUEUE_DATA& data) const;

	// 组呼添加临时用户
//	void TempUserJoinGroup(const QUEUE_DATA& data) const;

	//发起PSTN/PLMN电话呼叫
//	void TelephoneDial(const QUEUE_DATA& data) const;
	//挂断PSTN/PLMN电话呼叫
//	void TelephoneHangup(const QUEUE_DATA& data) const;
	//发起缜密监听
	void StartDiscreetListen(const QUEUE_DATA& data) const;
	//停止缜密监听
	void StopDiscreetListen(const QUEUE_DATA& data) const;
	//停止环境监听
	void StartEnvironmentListen(const QUEUE_DATA& data) const;
	//发起人工转接
	void P2PTransfer(const QUEUE_DATA& data) const;

	// 开始音视频录制
	void StartRecord(const QUEUE_DATA& data) const;
	//停止音视频录制
	void StopRecord(const QUEUE_DATA& data) const;
private:
	std::queue<QUEUE_DATA> m_logicQueue;
	HANDLE m_hRun;
	HANDLE m_hMutex;

};

#endif
