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

#pragma once

#include "ConfigMgr.h"
#include "OperationMgr.h"
#include "ProvisionMgr.h"
#include "MediaPlayer.h"
#include "VideoPane.h"

// eLTE_PlayerCtrl.h : Declaration of the CeLTE_PlayerCtrl ActiveX Control class.


// CeLTE_PlayerCtrl : See eLTE_PlayerCtrl.cpp for implementation.

class CeLTE_PlayerCtrl : public COleControl
{
	DECLARE_DYNCREATE(CeLTE_PlayerCtrl)

// Constructor
public:
	CeLTE_PlayerCtrl();

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// Implementation
protected:
	~CeLTE_PlayerCtrl();

	//lint -e1768
	DECLARE_OLECREATE_EX(CeLTE_PlayerCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CeLTE_PlayerCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CeLTE_PlayerCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CeLTE_PlayerCtrl)		// Type name and misc status
	//lint -e1768
// Message maps
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMsgExitFullScreen(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMsgPostEvent(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMsgPostPlayerEvent(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMsgStopVideoPlay(WPARAM wparam, LPARAM lparam);

// Dispatch maps
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
		dispidELTE_OCX_StopRecord = 91L,
		dispidELTE_OCX_StartRecord = 90L,
		dispidELTE_OCX_TempUserJoinGroup = 89L,
		dispidELTE_OCX_P2PHalfDpxRelease = 88L,
		dispidELTE_OCX_P2PHalfDpxDial = 87L,
		dispidELTE_OCX_ModifyDynamicGroup = 86L,
		dispidELTE_OCX_GetGisSubscription = 85L,
		dispidELTE_OCX_SetGisParam = 84L,
		dispidELTE_OCX_GetUserSpecificGISCfg = 83L,
		dispidELTE_OCX_PTZControl = 82L,
		dispidELTE_OCX_GetPatchGroupInfo = 81L,
		dispidELTE_OCX_GetGroupMemberByPatchId = 80L,
		dispidELTE_OCX_GetPatchGroups = 79L,
		dispidELTE_OCX_DeletePatchGroupMember = 78L,
		dispidELTE_OCX_AddPatchGroupMember = 77L,
		dispidELTE_OCX_CancelPatchGroup = 76L,
		dispidELTE_OCX_CreatePatchGroup = 75L,
		dispidELTE_OCX_P2PTransfer = 74L,
		dispidELTE_OCX_StartEnvironmentListen = 73L,
		dispidELTE_OCX_StopDiscreetListen = 72L,
		dispidELTE_OCX_StartDiscreetListen = 71L,
		dispidELTE_OCX_TelephoneHangup = 70L,
		dispidELTE_OCX_TelephoneDial = 69L,
		dispidELTE_OCX_VWallStop = 68L,
		dispidELTE_OCX_VWallStart = 67L,
		dispidELTE_OCX_GetDcVWallIDList = 66L,
		dispidELTE_OCX_RecvVideoPlay = 65L,
		dispidELTE_OCX_StopVideoDispatch = 64L,
		dispidELTE_OCX_StartVideoDispatch = 63L,
		dispidELTE_OCX_SDSSendMessage = 62L,
		dispidELTE_OCX_ProvisionManagerInitMRS = 61L,
		dispidELTE_OCX_SetBypassBuildMedia = 60L,
		dispidELTE_OCX_GISSubscribe = 59L,
		//dispidELTE_OCX_MuteControl = 58L,
		dispidELTE_OCX_VolUnMute = 57L,
		dispidELTE_OCX_VolMute = 56L,
		dispidELTE_OCX_P2PBreakoff = 55L,
		dispidELTE_OCX_P2PBreakin = 54L,
		dispidELTE_OCX_GroupBreakoff = 53L,
		dispidELTE_OCX_PTTEmergency = 52L,
		dispidELTE_OCX_PTTHangup = 51L,
		dispidELTE_OCX_PTTRelease = 50L,
		dispidELTE_OCX_PTTDial = 49L,
		dispidELTE_OCX_SubJoinGroup = 48L,
		//dispidELTE_OCX_JoinGroup = 47L,
		dispidELTE_OCX_P2PHangup = 46L,
		dispidELTE_OCX_P2PReject = 45L,
		dispidELTE_OCX_P2PRecv = 44L,
		dispidELTE_OCX_P2PDial = 43L,
		dispidELTE_OCX_GetNextTempGroupID = 42L,
		dispidELTE_OCX_CreateTempGroup = 41L,
		dispidELTE_OCX_CancelDynamicGroup = 40L,
		dispidELTE_OCX_CreateDynamicGroup = 39L,
		dispidELTE_OCX_SetTitleText = 38L,
		dispidELTE_OCX_NormalScreenDisplay = 37L,
		dispidELTE_OCX_FullScreenDisplay = 36L,
		dispidELTE_OCX_SetVideoWindowPos = 35L,
		dispidELTE_OCX_StopSound = 34L,
		dispidELTE_OCX_PlaySound = 33L,
		dispidELTE_OCX_HideRealPlay = 31L,
		dispidELTE_OCX_Snapshot = 30L,
		dispidELTE_OCX_ShowRealPlay = 29L,
		dispidELTE_OCX_StopRealPlay = 25L,
		dispidELTE_OCX_ReverseRealPlay = 24L,
		dispidELTE_OCX_StartRealPlay = 23L,
		dispidELTE_OCX_GetUserRECFileInfoList = 22L,
		dispidELTE_OCX_UnSubscribeGroup = 21L,
		dispidELTE_OCX_GetDcInfo = 20L,
		dispidELTE_OCX_GetUserInfo = 19L,
		dispidELTE_OCX_GetGroupInfo = 18L,
		dispidELTE_OCX_GetGroupUsers = 17L,
		dispidELTE_OCX_GetDcUsers = 16L,
		dispidELTE_OCX_GetDcGroups = 15L,
		//dispidELTE_OCX_ProvisionManagerExit = 14L,
		//dispidELTE_OCX_ProvisionManagerInit = 13L,
		dispidELTE_OCX_TriggerStatusReport = 12L,
		dispidELTE_OCX_Logout = 11L,
		dispidELTE_OCX_Login = 10L,
		dispidELTE_OCX_UnLoad = 8L,
		dispidELTE_OCX_Load = 7L,
		dispidELTE_OCX_ShowToolbar = 6L,
		dispidELTE_OCX_SetLanguage = 5L,
		dispidELTE_OCX_GetVersion = 4L,
		dispidELTE_OCX_UploadLogo = 3L,
		dispidELTE_OCX_SetLogLevel = 2L,
		dispidELTE_OCX_SetLogPath = 1L
	};//lint -e726

	enum {
		eventidELTE_OCX_Event = 50L,
		eventidELTE_OCX_PlayerEvent = 51L,
	};//lint -e726

protected:

	/**
	 *设置日志文件生成路径
	 * 
	 *该函数用于设置日志文件生成路径
	 *
	 *@param[in] 	pLogFilePath	日志生成路径，不包括文件名
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	ELTE_OCX_Load前调用。请使用绝对路径(不建议使用相对路径，相对路径以不能'\'开头)
	 *@par 			无
	**/
	BSTR ELTE_OCX_SetLogPath(LPCTSTR pLogFilePath);

	/**
	 *设置日志级别
	 * 
	 *该函数用于设置日志级别
	 *
	 *@param[in] 	ulLogLevel		日志级别
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	ELTE_OCX_Load前调用。四个级别0 debug、1 info、2 warn、3 error
	 *@par 			无
	**/
	BSTR ELTE_OCX_SetLogLevel(ULONG ulLogLevel);

	/**
	 *设置背景图片
	 * 
	 *该函数用于设置背景图片
	 *
	 *@param[in] 	pLogoFilePath	图片路径
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	ELTE_OCX_Load前调用。会拷贝设置的图片到ocx所在目录/Skin下面，并设置其为默认的背景图片
	 *@par 			无
	**/
	BSTR ELTE_OCX_UploadLogo(LPCTSTR pLogoFilePath);

	/**
	 *获取版本
	 * 
	 *该函数用于获取版本
	 *
	 *@param[in] 	ulVersion		版本ID。1-获取ocx插件版本号，2-获取sdk版本号(暂不支持)
	 *@return 		XML格式，成功(Version=版本字符串)，其他失败(Version=空字符串)参考错误码
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_GetVersion(ULONG ulVersion);

	/**
	 *设置OCX语言
	 * 
	 *该函数用于设置OCX语言
	 *
	 *@param[in] 	ulLanguage		语言ID。1-中文 2-英语 3-西班牙语
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	用于工具栏界面显示
	 *@par 			无
	**/
	BSTR ELTE_OCX_SetLanguage(ULONG ulLanguage);

	/**
	 *显示/隐藏工具栏
	 * 
	 *该函数用于显示/隐藏工具栏
	 *
	 *@param[in] 	ulToolbar		1-显示，0-隐藏
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_ShowToolbar(LONG ulToolbar);

	/**
	 *加载OCX插件
	 * 
	 *该函数用于加载OCX插件
	 *
	 *@param[in] 	ulType			1-加载播放器和业务，2-只加载播放器
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	只能调用一次
	 *@par 			无
	**/
	BSTR ELTE_OCX_Load(ULONG ulType);

	/**
	 *退出OCX插件
	 * 
	 *该函数用于退出OCX插件
	 *
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	只能调用一次
	 *@par 			无
	**/
	BSTR ELTE_OCX_UnLoad(void);

	/**
	 *登陆eLTE调度机
	 * 
	 *该函数用于登陆eLTE调度机
	 *
	 *@param[in] 	pUserID			调度员账号
	 *@param[in] 	pPWD			密码
	 *@param[in] 	pServerIP		服务器IP
	 *@param[in] 	pLocalIP		本地IP
	 *@param[in] 	pServerSIPPort	服务器端口
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	ELTE_OCX_Load type为1时才能使用eLTE功能
	 *@par 			无
	**/
	BSTR ELTE_OCX_Login(LPCTSTR pUserID, LPCTSTR pPWD, LPCTSTR pServerIP, LPCTSTR pLocalIP, LPCTSTR pServerSIPPort);

	/**
	 *登出eLTE调度机
	 * 
	 *该函数用于登出eLTE调度机
	 *
	 *@param[in] 	pUserID			调度员账号
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	ELTE_OCX_Load type为1时才能使用eLTE功能
	 *@par 			无
	**/
	BSTR ELTE_OCX_Logout(LPCTSTR pUserID);

	/**
	 *触发状态上报
	 * 
	 *该函数用于触发状态上报
	 *
	 *@param[in] 	ulEnableStatusReport	1-开始状态上报，0-关闭状态上报
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_TriggerStatusReport(ULONG ulEnableStatusReport);

	/**
	 *获取调度台群组列表
	 * 
	 *该函数用于获取调度台群组列表
	 *
	 *@param[in] 	pUserID			调度员账号
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。列表按XML格式解析
	 *@attention	等待配置管理下载成功
	 *@par 			无
	**/
	BSTR ELTE_OCX_GetDcGroups(LPCTSTR pUserID);

	/**
	 *获取调度台用户列表
	 * 
	 *该函数用于获取调度台用户列表
	 *
	 *@param[in] 	pUserID			调度员账号
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。列表按XML格式解析
	 *@attention	等待配置管理下载成功
	 *@par 			无
	**/
	BSTR ELTE_OCX_GetDcUsers(LPCTSTR pUserID);

	/**
	 *获取一个群组成员列表
	 * 
	 *该函数用于获取一个群组成员列表
	 *
	 *@param[in] 	pGroupID		群组ID
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。列表按XML格式解析
	 *@attention	等待配置管理下载成功
	 *@par 			无
	**/
	BSTR ELTE_OCX_GetGroupUsers(LPCTSTR pGroupID);

	/**
	 *获取一个群组详细信息
	 * 
	 *该函数用于获取一个群组详细信息
	 *
	 *@param[in] 	pGroupID		群组ID
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。详细信息按XML格式解析
	 *@attention	等待配置管理下载成功
	 *@par 			无
	**/
	BSTR ELTE_OCX_GetGroupInfo(LPCTSTR pGroupID);

	/**
	 *获取一个用户详细信息
	 * 
	 *该函数用于获取一个用户详细信息
	 *
	 *@param[in] 	pUserID			用户账号
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。详细信息按XML格式解析
	 *@attention	等待配置管理下载成功
	 *@par 			无
	**/
	BSTR ELTE_OCX_GetUserInfo(LPCTSTR pUserID);

	/**
	 *获取一个调度台详细信息
	 * 
	 *该函数用于获取一个调度台详细信息
	 *
	 *@param[in] 	pUserID			调度台账号
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。详细信息按XML格式解析
	 *@attention	等待配置管理下载成功
	 *@par 			无
	**/
	BSTR ELTE_OCX_GetDcInfo(LPCTSTR pUserID);

	/**
	 *取消订阅群组
	 * 
	 *该函数用于取消订阅群组
	 *
	 *@param[in] 	pGroupID				群组ID
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_UnSubscribeGroup(LPCTSTR pGroupID);

	/**
	 *获取录像文件列表
	 * 
	 *该函数用于获取录像文件列表
	 *
	 *@param[in] 	pQueryXml		查询条件，按XML格式定义
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。列表信息按XML格式解析
	 *@attention	等待配置管理下载成功
	 *@par 			无
	**/
	BSTR ELTE_OCX_GetUserRECFileInfoList(LPCTSTR pQueryXml);

	/**
	 *开启视频回传
	 * 
	 *该函数用于开启视频回传
	 *
	 *@param[in] 	pResourceID		资源ID
	 *@param[in] 	pVideoParam		媒体参数，按XML格式定义
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	从视频回调事件中获取音视频端口信息，然后使用ELTE_OCX_ShowRealPlay显示视频，ELTE_OCX_PlaySound播放伴音
	 *@par 			无
	**/
	BSTR ELTE_OCX_StartRealPlay(LPCTSTR pResourceID, LPCTSTR pVideoParam);

	/**
	 *切换前后置摄像头
	 * 
	 *该函数用于切换前后置摄像头
	 *
	 *@param[in] 	pResourceID		资源ID
	 *@param[in] 	pVideoParam		媒体参数，按XML格式定义
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	从视频回调事件中获取音视频端口信息，然后使用ELTE_OCX_ShowRealPlay显示视频，ELTE_OCX_PlaySound播放伴音
	 *@par 			无
	**/
	BSTR ELTE_OCX_ReverseRealPlay(LPCTSTR pResourceID, LPCTSTR pVideoParam);

	/**
	 *停止播放实时视频
	 * 
	 *该函数用于停止播放实时视频
	 *
	 *@param[in] 	pResourceID		资源ID
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_StopRealPlay(LPCTSTR pResourceID);

	/**
	 *播放器开始播放视频
	 * 
	 *该函数用于播放器开始播放视频
	 *
	 *@param[in] 	pResourceID		资源ID
	 *@param[in] 	pLocalMediaAddr	本地流媒体参数，按XML格式定义
	 *@param[in] 	pRemoteMediaAddr远端流媒体参数，按XML格式定义
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	流媒体参数从视频回调事件中获取
	 *@par 			无
	**/
	BSTR ELTE_OCX_ShowRealPlay(LPCTSTR pResourceID, LPCTSTR pLocalMediaAddr, LPCTSTR pRemoteMediaAddr);

	/**
	 *抓拍视频画面
	 * 
	 *该函数用于抓拍视频画面
	 *
	 *@param[in] 	pResourceID		资源ID
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	截图保存格式和路径在eLTE_Player.ini配置文件中。文件名“pResourceID_实时时间字符串”
	 *@par 			无
	**/
	BSTR ELTE_OCX_Snapshot(LPCTSTR pResourceID);

	/**
	 *播放器停止播放视频
	 * 
	 *该函数用于播放器停止播放视频
	 *
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_HideRealPlay(void);

	/**
	 *播放器开始播放音频
	 * 
	 *该函数用于播放器开始播放音频
	 *
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	ELTE_OCX_StartRealPlay媒体参数需要设置“有伴音”
	 *@par 			无
	**/
	BSTR ELTE_OCX_PlaySound(void);

	/**
	 *播放器停止播放音频
	 * 
	 *该函数用于播放器停止播放音频
	 *
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_StopSound(void);

	/**
	 *设置播放器窗体坐标
	 * 
	 *该函数用于设置播放器窗体坐标
	 *
	 *@param[in] 	ulLeft			左坐标
	 *@param[in] 	ulTop			上坐标
	 *@param[in] 	ulWidth			宽度
	 *@param[in] 	ulHeight		高度
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_SetVideoWindowPos(ULONG ulLeft, ULONG ulTop, ULONG ulWidth, ULONG ulHeight);

	/**
	 *全屏幕显示播放画面
	 * 
	 *该函数用于全屏幕显示播放画面
	 *
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_FullScreenDisplay(void);

	/**
	 *退出全屏幕播放
	 * 
	 *该函数用于退出全屏幕播放
	 *
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_NormalScreenDisplay(void);

	/**
	 *设置播放窗体标题文本
	 * 
	 *该函数用于设置播放窗体文本
	 *
	 *@param[in] 	pTitleText		标题文本
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_SetTitleText(LPCTSTR pTitleText);

	/**
	 *创建动态重组
	 * 
	 *该函数用于创建动态重组
	 *
	 *@param[in] 	pDGNAParam		动态组参数信息
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_CreateDynamicGroup(LPCTSTR pDGNAParam);

	/**
	 *删除动态重组
	 * 
	 *该函数用于删除动态重组
	 *
	 *@param[in] 	pResourceID		动态组组号
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_CancelDynamicGroup(LPCTSTR pResourceID);

	/**
	 *创建临时组
	 * 
	 *该函数用于创建临时组
	 *
	 *@param[in] 	pTEMPGParam		临时组参数信息
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_CreateTempGroup(LPCTSTR pTEMPGParam);

	/**
	 *向调度机申请一个临时组号
	 * 
	 *该函数用于向调度机申请一个临时组号
	 *
	 *@return 		XML格式，成功(NextTempGroupID=版本字符串)，其他失败(NextTempGroupID=0)参考错误码
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_GetNextTempGroupID(void);

	/**
	 *发起语音点呼
	 * 
	 *该函数用于发起语音点呼
	 *
	 *@param[in] 	pResourceID		资源ID
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_P2PDial(LPCTSTR pResourceID);

	/**
	 *接收语音点呼
	 * 
	 *该函数用于接收语音点呼
	 *
	 *@param[in] 	pResourceID		资源ID
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_P2PRecv(LPCTSTR pResourceID);

	/**
	 *拒接语音点呼
	 * 
	 *该函数用于拒接语音点呼
	 *
	 *@param[in] 	pResourceID		资源ID
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_P2PReject(LPCTSTR pResourceID);

	/**
	 *挂断语音点呼
	 * 
	 *该函数用于挂断语音点呼
	 *
	 *@param[in] 	pResourceID		资源ID
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_P2PHangup(LPCTSTR pResourceID);

	/**
	 *订阅并自动加入群组
	 * 
	 *该函数用于订阅并自动加入群组
	 *
	 *@param[in] 	pGroupID		群组ID
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_SubJoinGroup(LPCTSTR pGroupID);

	/**
	 *发起组呼（固定和临时组呼）或抢权
	 * 
	 *该函数用于发起组呼（固定和临时组呼）或抢权
	 *
	 *@param[in] 	pGroupID		群组ID
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_PTTDial(LPCTSTR pGroupID);

	/**
	 *释放话权
	 * 
	 *该函数用于释放话权
	 *
	 *@param[in] 	pGroupID		群组ID
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_PTTRelease(LPCTSTR pGroupID);

	/**
	 *退出组呼
	 * 
	 *该函数用于退出组呼
	 *
	 *@param[in] 	pGroupID		群组ID
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_PTTHangup(LPCTSTR pGroupID);

	/**
	 *发起紧急组呼
	 * 
	 *该函数用于发起紧急组呼
	 *
	 *@param[in] 	pGroupID		群组ID
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_PTTEmergency(LPCTSTR pGroupID);

	/**
	 *强拆组呼
	 * 
	 *该函数用于强拆组呼
	 *
	 *@param[in] 	pGroupID		群组ID
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_GroupBreakoff(LPCTSTR pGroupID);

	/**
	 *抢话（强拆点呼+发起新点呼）
	 * 
	 *该函数用于抢话（强拆点呼+发起新点呼）
	 *
	 *@param[in] 	pResourceID		资源ID
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_P2PBreakin(LPCTSTR pResourceID);

	/**
	 *强拆点呼
	 * 
	 *该函数用于强拆点呼
	 *
	 *@param[in] 	pResourceID		资源ID
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_P2PBreakoff(LPCTSTR pResourceID);

	/**
	 *执行静音（点呼、组呼、视频回传）
	 * 
	 *该函数用于执行静音
	 *
	 *@param[in] 	pResourceID		资源ID
	 *@param[in] 	pMuteParam		    静音操作参数
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_VolMute(LPCTSTR pResourceID, LPCTSTR pMuteParam);

	/**
	 *取消静音（点呼、组呼、视频回传）
	 * 
	 *该函数用于取消静音
	 *
	 *@param[in] 	pResourceID		资源ID
	 *@param[in] 	pMuteParam		    静音操作参数
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_VolUnMute(LPCTSTR pResourceID, LPCTSTR pMuteParam);

	/**
	 *订阅/去订阅GIS终端
	 * 
	 *该函数用于订阅/去订阅GIS终端
	 *
	 *@param[in] 	pResourceID		资源ID
	 *@param[in] 	pGISParam		    GIS操作参数
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_GISSubscribe(LPCTSTR pResourceID, LPCTSTR pGISParam);

	/**
	 *发送短数据
	 * 
	 *该函数用于发送短数据
	 *
	 *@param[in] 	pResourceID		资源ID
	 *@param[in] 	pSDSParam		短信操作参数
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_SDSSendMessage(LPCTSTR pResourceID, LPCTSTR pSDSParam);

	/**
	 *设置使用eLTE SDK媒体面
	 * 
	 *该函数用于设置使用eLTE SDK媒体面
	 *
	 *@param[in] 	ulBypass		是否使用eLTE SDK处理音视频
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码。
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_SetBypassBuildMedia(ULONG ulBypass);

	/**
	 *媒体服务器初始化
	 * 
	 *该函数用于媒体服务器初始化
	 *
	 *@param[in] 	pServerIP		服务器IP
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_ProvisionManagerInitMRS(LPCTSTR pServerIP);

	/**
	 *开启视频分发
	 * 
	 *该函数用于开启视频分发
	 *
	 *@param[in] 	pResourceID		        资源ID
	 *@param[in] 	pVideoDispatchParam		视频分发参数
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_StartVideoDispatch(LPCTSTR pResourceID, LPCTSTR pVideoDispatchParam);

	/**
	 *停止视频分发
	 * 
	 *该函数用于停止视频分发
	 *
	 *@param[in] 	pResourceID		        资源ID
	 *@param[in] 	pVideoDispatchParam		视频停止分发参数
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_StopVideoDispatch(LPCTSTR pResourceID, LPCTSTR pVideoDispatchParam);

	/**
	 *接受视频回传
	 * 
	 *该函数用于接受视频回传
	 *
	 *@param[in] 	pResourceID		资源ID
	 *@param[in] 	pMuteType		静音参数
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_RecvVideoPlay(LPCTSTR pResourceID, LPCTSTR pMuteType);

	/**
	 *获取视频墙信息
	 * 
	 *该函数用于获取视频墙信息
	 *
	 *@param[in] 	无
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_GetDcVWallIDList(void);

	/**
	 *开启视频上墙
	 * 
	 *该函数用于开启视频上墙
	 *
	 *@param[in] 	pResVWallID		上墙通道
	 *@param[in] 	pResVWallID		上墙参数
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_VWallStart(LPCTSTR pResVWallID, LPCTSTR pVWallStartParam);

	/**
	 *停止视频上墙
	 * 
	 *该函数用于停止视频上墙
	 *
	 *@param[in] 	pResVWallID		视频所上墙的通道
	 *@param[in] 	pResVWallID		下墙参数
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_VWallStop(LPCTSTR pResVWallID, LPCTSTR pVWallStopParam);

	/**
	 *调度台发起缜密侦听
	 * 
	 *该函数用于调度台发起缜密侦听
	 *
	 *@param[in] 	pResourceID		资源ID(群组或者用户)
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_StartDiscreetListen(LPCTSTR pResourceID);

	/**
	 *调度台停止缜密侦听
	 * 
	 *该函数用于调度台停止缜密侦听
	 *
	 *@param[in] 	pResourceID		资源ID(群组或者用户)
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_StopDiscreetListen(LPCTSTR pResourceID);

	/**
	 *调度台发起环境侦听
	 * 
	 *该函数用于调度台发起环境侦听
	 *
	 *@param[in] 	pResourceID		资源ID(终端用户)
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_StartEnvironmentListen(LPCTSTR pResourceID);

	/**
	 *调度台发起人工转接
	 * 
	 *该函数用于调度台发起人工转接
	 *
	 *@param[in] 	pResourceID		转接的资源ID
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_P2PTransfer(LPCTSTR pResourceID, LPCTSTR pP2PTransferParam);

	/**
	 *创建派接组
	 * 
	 *该函数用于创建派接组
	 *
	 *@param[in] 	pP2PTransferParam 派接组参数
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_CreatePatchGroup(LPCTSTR pPatchGroupParam);

	/**
	 *删除派接组
	 * 
	 *该函数用于删除派接组
	 *
	 *@param[in] 	pPatchGroupID 资源对象，一般是创建派接组的组号。
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_CancelPatchGroup(BSTR pPatchGroupID);

	/**
	 *增加派接组成员
	 * 
	 *该函数用于增加派接组成员
	 *
	 *@param[in] 	pPatchGroupParam 派接组参数。
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_AddPatchGroupMember(LPCTSTR pPatchGroupParam);

	/**
	 *删除派接组成员
	 * 
	 *该函数用于删除派接组成员
	 *
	 *@param[in] 	pPatchGroupParam 派接组参数。
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	无
	 *@par 			无
	**/
	BSTR ELTE_OCX_DeletePatchGroupMember(LPCTSTR pPatchGroupParam);

	/**
	 *获取指定调度台的所有派接组列表
	 * 
	 *该函数用于获取指定调度台的所有派接组列表
	 *
	 *@param[in] 	pDcUser 调度台用户ID。
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	等待配置管理下载成功
	 *@par 			无
	**/
	BSTR ELTE_OCX_GetPatchGroups(LPCTSTR pDcUser);

	/**
	 *获取指定派接组管理的成员列表
	 * 
	 *该函数用于获取指定派接组管理的成员列表
	 *
	 *@param[in] 	pPatchGroupID 派接组ID。
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	等待配置管理下载成功
	 *@par 			无
	**/
	BSTR ELTE_OCX_GetGroupMemberByPatchId(LPCTSTR pPatchGroupId);

	/**
	 *获取指定派接组属性信息
	 * 
	 *该函数用于获取指定派接组属性信息
	 *
	 *@param[in] 	pPatchGroupID 派接组ID。
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	等待配置管理下载成功
	 *@par 			无
	**/
	BSTR ELTE_OCX_GetPatchGroupInfo(LPCTSTR pPatchGroupId);

	/**
	 *获取调度台订阅GIS上报的终端列表
	 * 
	 *该函数用于获取调度台订阅GIS上报的终端列表
	 *
	 *@param[in] 	pDcUser 调度台ID
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	等待配置管理下载成功
	 *@par 			无
	**/
	BSTR ELTE_OCX_GetGisSubscription(LPCTSTR pUserID);


	/**
	 *修改动态群组
	 * 
	 *该函数用于修改动态群组
	 *
	 *@param[in] 	pUserID 创建动态组的调度台 ID
					pDynamicGroupInfo 动态组修改信息
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	等待配置管理下载成功
	 *@par 			无
	**/
	BSTR ELTE_OCX_ModifyDynamicGroup(LPCTSTR pUserID, LPCTSTR pDynamicGroupInfo);

	/**
	 *开始云台控制
	 * 
	 *该函数用于开始云台控制
	 *
	 *@param[in] 	pResourceID 带云台的摄像机资源ID
					ulPTZControlCode  云台控制命令
					ulPTZControlValue 云台控制命令对应的参数
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	等待配置管理下载成功
	 *@par 			无
	**/
	BSTR ELTE_OCX_PTZControl(LPCTSTR pResourceID, ULONG ulPTZControlCode, ULONG ulPTZControlValue);

	/**
	 *发起半双工点呼
	 * 
	 *该函数用于发起半双工点呼
	 *
	 *@param[in] 	pResourceID 点呼的对端资源ID。
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	等待配置管理下载成功
	 *@par 			无
	**/
	BSTR ELTE_OCX_P2PHalfDpxDial(LPCTSTR pResourceID);

	/**
	 *释放半双工点呼
	 * 
	 *该函数用于释放半双工点呼
	 *
	 *@param[in] 	pResourceID 点呼的对端资源ID。
	 *@return 		XML格式，ResultCode=0成功，其他失败参考错误码
	 *@attention	等待配置管理下载成功
	 *@par 			无
	**/
	BSTR ELTE_OCX_P2PHalfDpxRelease(LPCTSTR pResourceID);

	/**
	 *OCX消息事件
	 * 
	 *该函数用于OCX消息事件
	 *
	 *@param[in] 	ulEventType		事件类型。参考eLTE_EVENT_ID_E枚举定义
	 *@param[in] 	pEventDataXml	事件数据。按XML格式解析
	 *@attention	无
	 *@par 			无
	**/
	void ELTE_OCX_Event(ULONG ulEventType, LPCTSTR pEventDataXml)
	{
		FireEvent(eventidELTE_OCX_Event, EVENT_PARAM(VTS_UI4 VTS_BSTR), ulEventType, pEventDataXml);//lint !e1773
	}

	/**
	 *OCX播放器消息事件
	 * 
	 *该函数用于OCX播放器消息事件，播放窗体显示/隐藏。
	 *
	 *@param[in] 	ulEventType		事件类型。参考eLTE_PLAYER_EVENT_ID_E枚举定义
	 *@param[in] 	pEventDataXml	事件数据。按XML格式解析
	 *@attention	无
	 *@par 			无
	**/
	void ELTE_OCX_PlayerEvent(ULONG ulEventType, LPCTSTR pEventDataXml)
	{
		FireEvent(eventidELTE_OCX_PlayerEvent, EVENT_PARAM(VTS_UI4 VTS_BSTR), ulEventType, pEventDataXml);
	}

	/**
	 *OCX开启音视频录制
	 * 
	 *该函数用于OCX音视频录制的发起。
	 *
	 *@param[in] 	pResourceID		目标resourceID。参考eLTE_PLAYER_EVENT_ID_E枚举定义
	 *@param[in] 	pRecordParam	音视频录制参数。按XML格式解析
	 *@attention	无
	 *@par 			无
	**/
//	BSTR ELTE_OCX_StartRecord(LPCTSTR pResourceID, LPCTSTR pRecordParam);

	/**
	 *OCX终止音视频录制
	 * 
	 *该函数用于OCX音视频录制的发起。
	 *
	 *@param[in] 	pResourceID		目标resourceID。参考eLTE_PLAYER_EVENT_ID_E枚举定义
	 *@param[in] 	pRecordParam	音视频录制参数。按XML格式解析
	 *@attention	无
	 *@par 			无
	**/
//	BSTR ELTE_OCX_StopRecord(LPCTSTR pResourceID, LPCTSTR pRecordParam);

	
	// 工具栏操作接口
public:
	// 抓图
	int ToolBarSnapshot();
	// 切换前后置摄像头
	int ToolBarReversePlayer();
	// 开启关闭伴音
	int ToolBarPlayAudio(BOOL bEnable);
	// 异步播放视频
	static std::map<int, CeLTE_PlayerCtrl*> m_WaitPlayVideoList;
	// 获取媒体实例
	const MediaPlayer& GetMediaPlayer() const {return m_MediaPlayer;};
	// 获取媒体播放实例
	const CVideoPane& GetVideoPane() const {return m_VideoPane;};

public:
	// 键盘钩子
	static HHOOK s_KeyboardHook;
	// 键盘钩子处理函数
	static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
	// 鼠标钩子
	static HHOOK s_MouseHook;
	// 鼠标钩子处理函数
	static LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);

public:
	// 事件回调函数
	static ELTE_VOID __SDK_CALL ELTE_EventCallBack(ELTE_INT32 iEventType, ELTE_VOID* pEventBuf, ELTE_UINT32 uiBufSize, ELTE_VOID* pUserData);

	// GDI+
private:
	Gdiplus::GdiplusStartupInput m_GdiplusStartupInput;
	ULONG_PTR m_GdiplusToken;

private:
	// Load OCX类型
	ULONG m_ulType;
	// Load OCX标识
	BOOL m_bHaveLoaded;

private:
	ConfigMgr m_ConfigMgr;
	MediaPlayer m_MediaPlayer;
	CVideoPane m_VideoPane;
	//ULONG m_ulByMediaPass1;

public:
	// 控件列表
	static std::set<CeLTE_PlayerCtrl*> m_eLTE_PlayerList;
	static BOOL m_bLogInited;
};//lint !e1712 !e1773 !e1768
