#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <iostream>
#include <conio.h>
#include <string>
#include <stack> //栈
#include <map>
#include <math.h>
#include <thread>
#include <Windows.h>
#include <time.h>
#include <regex>
#include <vector>
#include <fstream>

namespace ICSQL{

class Var {
private:
	std::stack<std::string>T_DEX;//进制存储栈
	std::stack<int>T_DEXC;//进制存储栈s

public:
	//类型定义
	int Int;
	double Double;
	bool Bool;
	std::wstring Wstring;
	std::string String;
	char Char;

	//指针类型
	int *Int_f;
	double *Double_f;
	bool *Bool_f;
	std::wstring *Wstring_f;
	std::string *String_f;
	char* Char_f;

public:
	//指针类型指向自己
	void Fpont_Self() { 
		this->Int_f = &this->Int;
		this->Double_f = &this->Double;
		this->Bool_f = &this->Bool;
		this->String_f = &this->String;
		this->Wstring_f = &this->Wstring;
		this->Char_f = &this->Char;
	}

	//初始化;
	void InitVar() { 
		this->Int = NULL;
		this->Int_f = NULL;
		this->Double = NULL;
		this->Double_f = NULL;
		this->Bool = NULL;
		this->Bool_f = NULL;
		this->Wstring = L"";
		this->Wstring_f = NULL;
		this->String = "";
		this->String_f = NULL;
		this->Char = NULL;
		this->Char_f = NULL;
	}

	//查看所有设置
	void D_bug() {

		Var *myP  = this; //获取当前地址
		double Menu = sizeof(this);//获取类型大小
		std::cout << "address:	" << myP << std::endl;
		std::cout << "storage:	" << Menu << std::endl;
		std::cout << std::endl;
		std::cout << "Data ALL Data To Ther" << std::endl;
		if (this->Int != NULL) {
			std::cout << "Int:" << "\t\t" << this->Int << std::endl;
		}
		else { std::cout << "Int:" << "\t\t" << "NULL" << std::endl; }

		if (this->Double != NULL) {
			std::cout << "Double:" << "\t\t" << this->Double << std::endl;
		}
		else { std::cout << "Double:" << "\t\t" << "NULL" << std::endl; }

		if (this->Bool != NULL) {
			std::cout << "Bool:" << "\t\t" << this->Bool << std::endl;
		}
		else { std::cout << "Bool:" << "\t\t" << "NULL" << std::endl; }

		if (this->Wstring != L"") {
			std::wcout << "Wstring:" << "\t" << this->Wstring << std::endl;
		}
		else { std::wcout << "Wstring:" << "\t" << "NULL" << std::endl; }

		if (this->String != "") {
			std::cout << "String:" << "\t\t" << this->String << std::endl;
		}
		else { std::cout << "String:" << "\t\t" << "NULL" << std::endl; }

		if (this->Char != NULL) {
			std::cout << "Char:" << "\t\t" << this->Char << std::endl;
		}
		else { std::cout << "Char:" << "\t\t" << "NULL" << std::endl; }

		std::cout << std::endl; //地址显示
		
		std::cout << "Data address" << std::endl;

		if (this->Int_f != NULL) {
			std::cout << "Int_f:" << "\t\t" << this->Int_f << std::endl;
		}
		else { std::cout << "Int_f:" << "\t\t" << "NULL" << std::endl; }

		if (this->Double_f != NULL) {
			std::cout << "Double_f:" << "\t" << this->Double_f << std::endl;
		}
		else { std::cout << "Double_f:" << "\t" << "NULL" << std::endl; }

		if (this->Bool_f != NULL) {
			std::cout << "Bool_f:" << "\t\t" << this->Bool_f << std::endl;
		}
		else { std::cout << "Bool_f:" << "\t\t" << "NULL" << std::endl; }

		if (this->Wstring_f != NULL) {
			std::wcout << "Wstring:" << "\t" << this->Wstring_f << std::endl;
		}
		else { std::wcout << "Wstring_f:" << "\t" << "NULL" << std::endl; }

		if (this->String_f != NULL) {
			std::cout << "String_f:" << "\t" << this->String_f << std::endl;
		}
		else { std::cout << "String_f:" << "\t" << "NULL" << std::endl; }

		if (this->Char_f != NULL) {
			std::cout << "Char_f:" << "\t" << this->Char_f << std::endl;
		}
		else { std::cout << "Char_f:" << "\t" << "NULL" << std::endl; }

	}

	//算法优化
	private:
		//栈初始化
		void InitStack() {

			while (!this->T_DEX.empty()) {
				this->T_DEX.pop();
			}
		}

		void InitStackC() {

			while (!this->T_DEXC.empty()) {
				this->T_DEXC.pop();
			}
		}

	public:
		//二进制转换（转换数，存储数）不包含小数
		void Turn_binary(int tobe,std::string *Mube) {
			this->InitStack();//栈初始化


			while (true) {
				this->T_DEX.push(std::to_string(tobe % 2)); //整数类型的二进制转换
				tobe = tobe / 2;
				if (tobe == 1) {
					this->T_DEX.push(std::to_string(1));
					break;
				}
			}
			while (!this->T_DEX.empty()) {
				*Mube = *Mube + this->T_DEX.top();
				this->T_DEX.pop();
			}
			this->InitStack();//栈初始化
		}

		//二进制转10进制(需要转换的值,与长度)
		int BinToDEX(std::string Bin,int Leng) {
			this->InitStackC(); //初始化栈
			for (int i = 0; i<Leng; i++) {
				this->T_DEXC.push(Bin[i]-'0');
			}
			int ENDC=0;//阶乘
			int MEN=0; //和
			while (!this->T_DEXC.empty()) {
				MEN = (pow(2,ENDC)*T_DEXC.top()) + MEN;
				this->T_DEXC.pop();
				ENDC++;
			}
			return MEN;
		}

		//自动排序（需要排序的数，trun正序false倒序,大小）仅支持数字类型
		void Automatic_sorting(double A[],bool Be,int Nme) {
			int LinesMin = 0;//内部赋予
			int LinesMax = Nme-1;

			std::map<double,std::string>MAsp; //使用红黑数
			for (int i = 0; i < Nme; i++) {		//进行排序
				MAsp.insert(std::pair<double, std::string>(A[i], ""));
			}

			//确认倒序
			if (Be) {
				for (const auto & pair:MAsp) {
					A[LinesMin] = pair.first;
					LinesMin++;

				}
			}
			else
			{
				for (const auto& pair : MAsp) {
					A[LinesMax] = pair.first;
					LinesMax--;
				}
			}
			MAsp.clear();
		}
	
		///第二部分
		//十进制转八进制(转换数)
		std::string DexTOoct(int Dex) {
			this->InitStack();//初始化栈
			std::string MEN;//存储
			while (true) {
				this->T_DEX.push(std::to_string(Dex % 8));
				Dex = Dex / 8;
				if (Dex == 0) {
					break;
				}
			}
			while (!this->T_DEX.empty()) {
				MEN = MEN + this->T_DEX.top();
				this->T_DEX.pop();
			}
			return MEN;
		}

		//八进制转10进制
		int OoctToDex(std::string Bin, int Leng) {
			this->InitStackC(); //初始化栈
			for (int i = 0; i < Leng; i++) {
				this->T_DEXC.push(Bin[i] - '0');
			}
			int ENDC = 0;//阶乘
			int MEN = 0; //和
			while (!this->T_DEXC.empty()) {
				MEN = (pow(8, ENDC) * T_DEXC.top()) + MEN;
				this->T_DEXC.pop();
				ENDC++;
			}
			return MEN;
		}

		//十进制转16进制(转数)
		void DexToHex(int DEX, std::string *HEX) {
			this->InitStack();//栈初始化;

			while (true) {
				if (DEX % 16 > 9) {
					switch (DEX % 16) {
					case 10:
						this->T_DEX.push("A");
						break;
					case 11:
						this->T_DEX.push("B");
						break;
					case 12:
						this->T_DEX.push("C");
						break;
					case 13:
						this->T_DEX.push("D");
						break;
					case 14:
						this->T_DEX.push("E");
						break;
					case 15:
						this->T_DEX.push("F");
						break;
					}
				}
				else {
					this->T_DEX.push(std::to_string(DEX % 16));
				}
				DEX = DEX / 16;
				if (DEX == 0) {
					break;
				}
			}

			while (!this->T_DEX.empty()) {
				*HEX = *HEX + this->T_DEX.top();
				this->T_DEX.pop();
			}
		}

		//16进制转10进制(需要转的数值)
		int HexToDex(std::string Hex,int Len) {
			this->InitStackC();
			for (int i = 0; i < Len; i++) {
				if (Hex[i] > 64 && Hex[i] < 71) {
					switch (Hex[i])
					{
					case 'A':
						this->T_DEXC.push(10);
						break;
					case 'B':
						this->T_DEXC.push(11);
						break;
					case 'C':
						this->T_DEXC.push(12);
						break;
					case 'D':
						this->T_DEXC.push(13);
						break;
					case 'E':
						this->T_DEXC.push(14);
						break;
					case 'F':
						this->T_DEXC.push(15);
						break;
					}
				}
				else
				{
					this->T_DEXC.push(Hex[i] - '0');
				}
			}

			int MIN=0; //幂
			int EMN=0;
			while (!this->T_DEXC.empty()) {
				EMN = EMN + (pow(16, MIN) * this->T_DEXC.top());
				this->T_DEXC.pop();
				MIN++;
			}
			return EMN;
		}
};
}
//其它支持的额外功能
namespace EXTF {

	class Extm {
	private:
		static bool GetKeyBool;//控制监听键盘
		static bool GetUndGetKey; //控制线程段性监听
		//线程获取输入监听
		static void ThreadGetKey(char* c);
		//线程段性监听
		static void ThreadUndGetKey(char* c);
	public:
		//运行多线程段性监听
		static void OpenThreadUndGetKey(char* c);

		//运行多线程监听
		static void OpenThreadGetKey(char* c);

		//关闭线程监听
		static void OffGetKey() {
			GetKeyBool = false;
		}

		//开启多线程监听
		static void OpenGetKey() {
			GetKeyBool = true;
		}

		//关闭段性线程监听
		static void OffUndGetKey() {
			GetUndGetKey = false;
		}

		//开启段性线程监听
		static void OpenUndGetKey() {
			GetUndGetKey = true;
		}
	};
     bool Extm::GetKeyBool = true;
	 bool Extm::GetUndGetKey = true;

	 //阶段性线程监听(建设中)
	 void Extm::ThreadUndGetKey(char* c) {
		 while (Extm::GetUndGetKey) {
			 
		 }
	 }

	//线程获取输入
	void Extm::ThreadGetKey(char* c){
		while (GetKeyBool)
		{
			if (_kbhit()) {
				*c = _getch();
			}
		}
	}
	//运行多线程监听键盘（需要更改的数，目标数）
	void Extm::OpenThreadGetKey(char* c) {
		std::thread MoreThreadGetKey(ThreadGetKey,c);
		MoreThreadGetKey.detach();
		return;
	}

	//运行多线程段性监听
	void Extm::OpenThreadUndGetKey(char* c) {
		std::thread MoreThreadUndGetKey(ThreadUndGetKey, c);
		MoreThreadUndGetKey.detach();
		return;
	}



	//计时器
	class TimeData {

	private:
		//秒计时器
		static void TimerS(int* a,int s);
		//毫秒计时器
		static void TimermS(int* a, int ms);
		
		//秒计时器开关
		static bool TimerS_Butten;

		//公共时间获取
		SYSTEMTIME SysTime;

		//毫秒计时器开关
		static bool TimerMS_Butten;
	public:
		//创建以秒计时的计时器(需要计时的数，延迟时间)
		static void MkTimerS(int* a,int s);

		//创建以毫秒计时的计时器(需要计时的数，延迟时间)
		static void MkTimerMS(int* a, int ms);

		//关闭秒计时器
		static void DeletTimr_s();

		//关闭毫秒计时器
		static void DeletTimr_Ms();

		//开启秒计时器
		static void OpenTimr_s();

		//开启毫秒计时器
		static void OpenTimr_Ms();

		//获取当前时间-年
		int GetNowYear() {
			GetSystemTime(&this->SysTime);
			return this->SysTime.wYear;
		}

		//获取当前时间-月
		int GetNowMonth() {
			GetSystemTime(&this->SysTime);
			return this->SysTime.wMonth;
		}

		//获取当前时间星期
		int GetNowDayOfWeek() {
			GetSystemTime(&this->SysTime);
			return this->SysTime.wDayOfWeek;
		}

		//获取当前时间-日
		int GetNowDay() {
			GetSystemTime(&this->SysTime);
			return this->SysTime.wDay;
		}

		//获取当前时间-时
		int GetNowHour() {
			GetSystemTime(&this->SysTime);
			return this->SysTime.wHour;
		}

		//获取当前时间-分
		int GetNowMinute() {
			GetSystemTime(&this->SysTime);
			return this->SysTime.wMinute;
		}

		//获取当前时间-秒
		int GetNowSecond() {
			GetSystemTime(&this->SysTime);
			return this->SysTime.wSecond;
		}
		//获取当前时间-好-毫秒
		int GetNowMilliseconds() {
			GetSystemTime(&this->SysTime);
			return this->SysTime.wMilliseconds;
		}
	};

	bool TimeData::TimerMS_Butten = true;
	bool TimeData::TimerS_Butten = true;

	//计时器线程开启与关闭

	//关闭秒计时器
	void TimeData::DeletTimr_s() {
		TimeData::TimerS_Butten = false;
	}

	//关闭毫秒计时器
	void TimeData::DeletTimr_Ms() {
		TimeData::TimerMS_Butten = false;
	}

	//开启秒计时器
	void TimeData::OpenTimr_s() {
		TimeData::TimerS_Butten = true;
	}

	//开启毫秒计时器
	void TimeData::OpenTimr_Ms() {
		TimeData::TimerMS_Butten = true;
	}

	//1
	void TimeData::TimerS(int* a,int s) {
		//秒计时器
		while (TimeData::TimerS_Butten) {
			Sleep(s*1000);
			*a= *a+1;
		}
	}

	//创建以秒计时的计时器(需要计时的数，延迟时间)
	void TimeData::MkTimerS(int* a, int s) {
		std::thread MkTimrToS(TimeData::TimerS, a, s);
		MkTimrToS.detach();
	};

	//2
	//毫秒计时器
	void TimeData::TimermS(int* a, int ms) {
		//毫秒计时器
		while (TimeData::TimerMS_Butten) {
			Sleep(ms);
			*a = *a + 1;
		}
	}

	//创建以毫秒计时的计时器(需要计时的数，延迟时间)
	void TimeData::MkTimerMS(int* a, int ms) {
		std::thread MkTimerToMS(TimeData::TimermS, a, ms);
		MkTimerToMS.detach();
	}
}

// 网络功能设置 
namespace IntelNet {

	//网络设置类
	class InteS
	 {
	 private:
		 //创建网络安全类
		WSADATA Wser;
		//网络套口
		SOCKET sock;
		//链接套口
		sockaddr_in AddSock;

		struct OnlineSet {
			//端口设置
			int port;

			//网络协议 true为TCP，false为UCP
			bool agreement;

			//IP地址存储
			std::string IPCL;

			//接收人数
			int Namber = NULL;
		};

	 public:
		 //打开网络权限
		 void OpenIntOP() {
			 WSAStartup(MAKEWORD(2, 2),&Wser);
		 }
		 
		 //1024-4096标准接收字符
		 char EMA1024[1024] = { 0 };  
		 char EMA2048[2048] = { 0 };
		 char EMA4096[4096] = { 0 };

		 //网络参数
		 OnlineSet OSset;

		 //接收套
		 SOCKET reception;

		 // 开始创建网络
		 void MkIntNet() {
			 //创建TCP/UCP网络协议
			 if (this->OSset.agreement) {
				 this->sock = socket(AF_INET, SOCK_STREAM, 0);
			 }else{ sock = socket(AF_INET,SOCK_DGRAM, 0); }
			 this->AddSock.sin_family = AF_INET;
			 this->AddSock.sin_port = htons(this->OSset.port);
			 this->AddSock.sin_addr.S_un.S_addr = inet_addr(this->OSset.IPCL.c_str());
			 if (-1 == bind(this->sock, (struct sockaddr*)&this->AddSock, sizeof(this->AddSock))) {
				 std::cout << "端口与IP绑定错误error" << std::endl;
				 return;}
			 listen(sock, this->OSset.Namber);
		 }

		 //刷新套口
		 void FluRecSock() {
			 this->reception = accept(this->sock, NULL, NULL);
		 }

		 //接收数据(传入字符，长度)
		 void Recv(char c[],int Len) {
			 recv(this->reception, c, Len,0);
		 }

		 //发送数据(传入字符，长度)
		 void Send(char c[], int Len) {
			 send(this->reception, c, Len, 0);
		 }
	};

	//转为请求文件(传输类型，数据，长度)
		std::string CreaPost(std::string Type,std::string Send,int len){
			std::string Head = "HTTP/1.1 200 OK\r\n";
			Head += "Content-Type: " + Type + ";" + " charset=utf-8\r\n";
			Head += "Content-Length: "+ std::to_string(len) + "\r\n";
			Head += "\r\n";
			Head += Send;
			return Head;
		}
	//重新定向请求（定向网址）
		std::string URLtoHTTP(std::string URL) {
			std::string TUR = "HTTP/1.1 302 Found\r\n";
			TUR += "Location: " + URL + "\r\n";
			TUR+= "Content-Length: 0\r\n";
			TUR+= "\r\n";
			return TUR;
		}

	//判断请求内容
		int JudgmentHttp(const char* HTTP) {
			std::regex GetGet("^(GET)"); //判断GIT类型请求
			std::regex GetPost("^(POST)");//判断POST类型
			std::regex GetHEAD("^(HEAD)");//判断HEAD
			std::regex GetPUT("^(PUT)");//判断put
			std::regex GetDELETE("^(DELETE)"); //判断delete
			std::regex GetTRACE("^(TRACE)"); //判断TRACE
			std::regex GetOPTIONS("^(OPTIONS)");//判断OPTIONS
			
			std::cout << HTTP << std::endl;

			if (std::regex_search(HTTP, GetGet)) {
				return 1;
			}
			else if (std::regex_search(HTTP, GetPost)) {
				return 2;
			}
			else if (std::regex_search(HTTP, GetGet)) {
				return 3;
			}
			else if (std::regex_search(HTTP, GetHEAD)) {
				return 4;
			}
			else if (std::regex_search(HTTP, GetDELETE)) {
				return 5;
			}
			else if (std::regex_search(HTTP, GetTRACE)) {
				return 6;
			}
			else if (std::regex_search(HTTP, GetOPTIONS)) {
				return 7;
			}
			else{
				return 0;
			}
		}

		//获取name(检测的协议，检测的NAME)
		std::vector<std::string> GetNAME(const char * HTTP,std::string Head) {
			
			std::vector<std::string>KeyGet; //存储向量
			std::string Gopse(HTTP);
			std::regex GetID(Head+"(\\w+)=");
			std::smatch math;
			std::string::const_iterator CreaString(Gopse.cbegin());
			while (std::regex_search(CreaString,Gopse.cend(),math,GetID)) {
				if (math.size() > 1) {
					KeyGet.push_back(math[1].str());
					CreaString = math.suffix().first;
				}
				else { break; }
			}
			return KeyGet;
		}

		//获取data(检测的协议，检测的NAME)
		std::vector<std::string>GetData(const char* HTTP,std::string Head) {
			std::vector<std::string>GetVdata;
			std::string Gopse(HTTP);
			std::regex GetDATA(Head+"[^&]*=(.*?)(?=&|$)");
			std::smatch math;
			std::string::const_iterator CreaString(Gopse.cbegin());
			while(std::regex_search(CreaString,Gopse.cend(),math,GetDATA)) {
				if (math.size() > 1) {
					GetVdata.push_back(math[1].str());
					CreaString = math.suffix().first;
				}
				else { break; }
			}
			return GetVdata;
		}

		//搜寻检索(输入文件名,正则表达式)
		std::map<int,std::string> inqAll(std::string File, std::string regexA) {
			std::vector<std::string>Data;
			std::map<int, std::string>Scrd;
			std::string line;
			std::ifstream iutf(File);
			std::regex InqSer(regexA);
			while (std::getline(iutf, line)) {
				Data.push_back(line);
			}
			iutf.close();
			int i = 0;
			for (const auto& pair : Data) {
				i++;
				if (std::regex_search(pair, InqSer)) {
					Scrd.insert(std::pair<int, std::string>(i,pair));
				}
			}

			return Scrd;
		}
}