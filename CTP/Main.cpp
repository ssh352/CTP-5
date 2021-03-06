// CTP.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
//#include <iostream>
#include "Ctp-api/ThostFtdcMdApi.h"
#include "Ctp-api/ThostFtdcUserApiDataType.h"
#include "Ctp-api/ThostFtdcTraderApi.h"
#include "Ctp-api/ThostFtdcUserApiStruct.h"

#include "CustomMdSpi.h"
#include "CustomTradeSpi.h"
#include "TickToKlineHelper.h"


TThostFtdcBrokerIDType gBrokerID = "9999";								// 模拟经纪商代码
TThostFtdcInvestorIDType gInvesterID = "";								// 投资者账户名
TThostFtdcPasswordType gInvesterPassword = "";							// 投资者密码

// 行情参数
CThostFtdcMdApi *g_pMdUserApi = nullptr;								// 行情指针
char gMdFrontAddr[] = "tcp://180.168.146.187:10010";					// 模拟行情前置地址
//char gMdFrontAddr[] = "tcp://180.168.146.187:10031";					// 模拟行情前置地址
//char *g_pInstrumentID[] = { (char*)"TF1906", (char*)"zn1810", (char*)"cs1810", (char*)"CF1810" };	// 行情合约代码列表，中、上、大、郑交易所各选一种
char *g_pInstrumentID[] = { (char*)"zn1810"};	// 行情合约代码列表，中、上、大、郑交易所各选一种
//int instrumentNum = 4;													// 行情合约订阅数量
int instrumentNum = 1;													// 行情合约订阅数量
unordered_map<string, TickToKlineHelper> g_KlineHash;					// 不同合约的k线存储表


// 交易参数
CThostFtdcTraderApi *g_pTradeUserApi = nullptr;							// 交易指针
char gTradeFrontAddr[] = "tcp://180.168.146.187:10001";					// 模拟交易前置地址
TThostFtdcInstrumentIDType g_pTradeInstrumentID = "zn1905";				// 所交易的合约代码
TThostFtdcDirectionType gTradeDirection = THOST_FTDC_D_Sell;			// 买卖方向
TThostFtdcPriceType gLimitPrice = 22735;								// 交易价格

int main()
{
	/*cout << "请输入账号： ";
	scanf("%s", gInvesterID);
	cout << "请输入密码： ";
	scanf("%s", gInvesterPassword);*/

	// 初始化行情线程
	cout << "初始化行情..." << endl;
	g_pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi(".\\test\\");					// 创建行情实例
	CThostFtdcMdSpi *pMdUserSpi = new CustomMdSpi();					// 创建行情回调实例
	g_pMdUserApi->RegisterSpi(pMdUserSpi);								// 注册事件类
	g_pMdUserApi->RegisterFront(gMdFrontAddr);							// 设置行情前置地址
	g_pMdUserApi->Init();												// 连接运行

	//// 初始化交易线程
	//cout << "初始化交易..." << endl;
	//g_pTradeUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi();		// 创建交易实例
	//CustomTradeSpi *pTradeSpi = new CustomTradeSpi();						// 创建交易回调实例
	//g_pTradeUserApi->RegisterSpi(pTradeSpi);							// 注册事件类
	//g_pTradeUserApi->SubscribePublicTopic(THOST_TERT_RESTART);			// 订阅公共流
	//g_pTradeUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);			// 订阅私有流
	//g_pTradeUserApi->RegisterFront(gTradeFrontAddr);					// 设置交易前置地址
	//g_pTradeUserApi->Init();

	g_pMdUserApi->Join();
	delete pMdUserSpi;
	g_pMdUserApi->Release();

	/*g_pTradeUserApi->Join();
	delete pTradeSpi;
	g_pTradeUserApi->Release();*/

	getchar();
	return 0;

	

}
