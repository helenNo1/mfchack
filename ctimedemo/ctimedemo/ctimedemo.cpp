// ctimedemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "atltime.h"   
#include <iostream>   
using namespace std;

int main()
{
	CString  strTime;

	CTime curTime = CTime::GetCurrentTime();
	
	int nYear = curTime.GetYear();
	int nMonth = curTime.GetMonth();
	int nDay = curTime.GetDay();
	int nHour = curTime.GetHour();
	int nMin = curTime.GetMinute();
	int nSec = curTime.GetSecond();

	// 输出当前时间   
	cout << "当前时间：" << endl;
	cout << nYear << "年" << nMonth << "月" << nDay << "日" << nHour << "时" << nMin << "分" << nSec << "秒" << endl;


	// 为计算时间差，设定一个起始时间并输出   
	CTime startTime = CTime(2010, 7, 3, 10, 20, 30);
	cout << "起始时间：" << endl;
	cout << startTime.GetYear() << "年" << startTime.GetMonth() << "月" << startTime.GetDay() << "日" << startTime.GetHour() << "时" << startTime.GetMinute() << "分" << startTime.GetSecond() << "秒" << endl;


	// 计算时间差   
	CTimeSpan timeSpan;
	timeSpan = curTime - startTime;
	cout << "两时间相差：" << endl;
	cout << timeSpan.GetDays() << "天" << timeSpan.GetHours() << "小时" << timeSpan.GetMinutes() << "分" << timeSpan.GetSeconds() << "秒" << endl;
	cout << "总小时数：" << timeSpan.GetTotalHours() << "小时" << endl;
	cout << "总分钟数：" << timeSpan.GetTotalMinutes() << "分" << endl;
	cout << "总秒数：" << timeSpan.GetTotalSeconds() << "秒" << endl;


	// 将当前时间curTime对象格式化为字符串   
	strTime = curTime.Format(_T("%Y-%m-%d %H:%M:%S"));
	// 输出格式化字符串，由于字符串使用Unicode字符，所以要使用wcout输出   
	wcout << (LPCTSTR)strTime << endl;

	system("pause");


}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件


