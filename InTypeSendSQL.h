#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <iostream>
#include <conio.h>
#include <string>
#include <stack> //ջ
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
	std::stack<std::string>T_DEX;//���ƴ洢ջ
	std::stack<int>T_DEXC;//���ƴ洢ջs

public:
	//���Ͷ���
	int Int;
	double Double;
	bool Bool;
	std::wstring Wstring;
	std::string String;
	char Char;

	//ָ������
	int *Int_f;
	double *Double_f;
	bool *Bool_f;
	std::wstring *Wstring_f;
	std::string *String_f;
	char* Char_f;

public:
	//ָ������ָ���Լ�
	void Fpont_Self() { 
		this->Int_f = &this->Int;
		this->Double_f = &this->Double;
		this->Bool_f = &this->Bool;
		this->String_f = &this->String;
		this->Wstring_f = &this->Wstring;
		this->Char_f = &this->Char;
	}

	//��ʼ��;
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

	//�鿴��������
	void D_bug() {

		Var *myP  = this; //��ȡ��ǰ��ַ
		double Menu = sizeof(this);//��ȡ���ʹ�С
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

		std::cout << std::endl; //��ַ��ʾ
		
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

	//�㷨�Ż�
	private:
		//ջ��ʼ��
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
		//������ת����ת�������洢����������С��
		void Turn_binary(int tobe,std::string *Mube) {
			this->InitStack();//ջ��ʼ��


			while (true) {
				this->T_DEX.push(std::to_string(tobe % 2)); //�������͵Ķ�����ת��
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
			this->InitStack();//ջ��ʼ��
		}

		//������ת10����(��Ҫת����ֵ,�볤��)
		int BinToDEX(std::string Bin,int Leng) {
			this->InitStackC(); //��ʼ��ջ
			for (int i = 0; i<Leng; i++) {
				this->T_DEXC.push(Bin[i]-'0');
			}
			int ENDC=0;//�׳�
			int MEN=0; //��
			while (!this->T_DEXC.empty()) {
				MEN = (pow(2,ENDC)*T_DEXC.top()) + MEN;
				this->T_DEXC.pop();
				ENDC++;
			}
			return MEN;
		}

		//�Զ�������Ҫ���������trun����false����,��С����֧����������
		void Automatic_sorting(double A[],bool Be,int Nme) {
			int LinesMin = 0;//�ڲ�����
			int LinesMax = Nme-1;

			std::map<double,std::string>MAsp; //ʹ�ú����
			for (int i = 0; i < Nme; i++) {		//��������
				MAsp.insert(std::pair<double, std::string>(A[i], ""));
			}

			//ȷ�ϵ���
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
	
		///�ڶ�����
		//ʮ����ת�˽���(ת����)
		std::string DexTOoct(int Dex) {
			this->InitStack();//��ʼ��ջ
			std::string MEN;//�洢
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

		//�˽���ת10����
		int OoctToDex(std::string Bin, int Leng) {
			this->InitStackC(); //��ʼ��ջ
			for (int i = 0; i < Leng; i++) {
				this->T_DEXC.push(Bin[i] - '0');
			}
			int ENDC = 0;//�׳�
			int MEN = 0; //��
			while (!this->T_DEXC.empty()) {
				MEN = (pow(8, ENDC) * T_DEXC.top()) + MEN;
				this->T_DEXC.pop();
				ENDC++;
			}
			return MEN;
		}

		//ʮ����ת16����(ת��)
		void DexToHex(int DEX, std::string *HEX) {
			this->InitStack();//ջ��ʼ��;

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

		//16����ת10����(��Ҫת����ֵ)
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

			int MIN=0; //��
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
//����֧�ֵĶ��⹦��
namespace EXTF {

	class Extm {
	private:
		static bool GetKeyBool;//���Ƽ�������
		static bool GetUndGetKey; //�����̶߳��Լ���
		//�̻߳�ȡ�������
		static void ThreadGetKey(char* c);
		//�̶߳��Լ���
		static void ThreadUndGetKey(char* c);
	public:
		//���ж��̶߳��Լ���
		static void OpenThreadUndGetKey(char* c);

		//���ж��̼߳���
		static void OpenThreadGetKey(char* c);

		//�ر��̼߳���
		static void OffGetKey() {
			GetKeyBool = false;
		}

		//�������̼߳���
		static void OpenGetKey() {
			GetKeyBool = true;
		}

		//�رն����̼߳���
		static void OffUndGetKey() {
			GetUndGetKey = false;
		}

		//���������̼߳���
		static void OpenUndGetKey() {
			GetUndGetKey = true;
		}
	};
     bool Extm::GetKeyBool = true;
	 bool Extm::GetUndGetKey = true;

	 //�׶����̼߳���(������)
	 void Extm::ThreadUndGetKey(char* c) {
		 while (Extm::GetUndGetKey) {
			 
		 }
	 }

	//�̻߳�ȡ����
	void Extm::ThreadGetKey(char* c){
		while (GetKeyBool)
		{
			if (_kbhit()) {
				*c = _getch();
			}
		}
	}
	//���ж��̼߳������̣���Ҫ���ĵ�����Ŀ������
	void Extm::OpenThreadGetKey(char* c) {
		std::thread MoreThreadGetKey(ThreadGetKey,c);
		MoreThreadGetKey.detach();
		return;
	}

	//���ж��̶߳��Լ���
	void Extm::OpenThreadUndGetKey(char* c) {
		std::thread MoreThreadUndGetKey(ThreadUndGetKey, c);
		MoreThreadUndGetKey.detach();
		return;
	}



	//��ʱ��
	class TimeData {

	private:
		//���ʱ��
		static void TimerS(int* a,int s);
		//�����ʱ��
		static void TimermS(int* a, int ms);
		
		//���ʱ������
		static bool TimerS_Butten;

		//����ʱ���ȡ
		SYSTEMTIME SysTime;

		//�����ʱ������
		static bool TimerMS_Butten;
	public:
		//���������ʱ�ļ�ʱ��(��Ҫ��ʱ�������ӳ�ʱ��)
		static void MkTimerS(int* a,int s);

		//�����Ժ����ʱ�ļ�ʱ��(��Ҫ��ʱ�������ӳ�ʱ��)
		static void MkTimerMS(int* a, int ms);

		//�ر����ʱ��
		static void DeletTimr_s();

		//�رպ����ʱ��
		static void DeletTimr_Ms();

		//�������ʱ��
		static void OpenTimr_s();

		//���������ʱ��
		static void OpenTimr_Ms();

		//��ȡ��ǰʱ��-��
		int GetNowYear() {
			GetSystemTime(&this->SysTime);
			return this->SysTime.wYear;
		}

		//��ȡ��ǰʱ��-��
		int GetNowMonth() {
			GetSystemTime(&this->SysTime);
			return this->SysTime.wMonth;
		}

		//��ȡ��ǰʱ������
		int GetNowDayOfWeek() {
			GetSystemTime(&this->SysTime);
			return this->SysTime.wDayOfWeek;
		}

		//��ȡ��ǰʱ��-��
		int GetNowDay() {
			GetSystemTime(&this->SysTime);
			return this->SysTime.wDay;
		}

		//��ȡ��ǰʱ��-ʱ
		int GetNowHour() {
			GetSystemTime(&this->SysTime);
			return this->SysTime.wHour;
		}

		//��ȡ��ǰʱ��-��
		int GetNowMinute() {
			GetSystemTime(&this->SysTime);
			return this->SysTime.wMinute;
		}

		//��ȡ��ǰʱ��-��
		int GetNowSecond() {
			GetSystemTime(&this->SysTime);
			return this->SysTime.wSecond;
		}
		//��ȡ��ǰʱ��-��-����
		int GetNowMilliseconds() {
			GetSystemTime(&this->SysTime);
			return this->SysTime.wMilliseconds;
		}
	};

	bool TimeData::TimerMS_Butten = true;
	bool TimeData::TimerS_Butten = true;

	//��ʱ���߳̿�����ر�

	//�ر����ʱ��
	void TimeData::DeletTimr_s() {
		TimeData::TimerS_Butten = false;
	}

	//�رպ����ʱ��
	void TimeData::DeletTimr_Ms() {
		TimeData::TimerMS_Butten = false;
	}

	//�������ʱ��
	void TimeData::OpenTimr_s() {
		TimeData::TimerS_Butten = true;
	}

	//���������ʱ��
	void TimeData::OpenTimr_Ms() {
		TimeData::TimerMS_Butten = true;
	}

	//1
	void TimeData::TimerS(int* a,int s) {
		//���ʱ��
		while (TimeData::TimerS_Butten) {
			Sleep(s*1000);
			*a= *a+1;
		}
	}

	//���������ʱ�ļ�ʱ��(��Ҫ��ʱ�������ӳ�ʱ��)
	void TimeData::MkTimerS(int* a, int s) {
		std::thread MkTimrToS(TimeData::TimerS, a, s);
		MkTimrToS.detach();
	};

	//2
	//�����ʱ��
	void TimeData::TimermS(int* a, int ms) {
		//�����ʱ��
		while (TimeData::TimerMS_Butten) {
			Sleep(ms);
			*a = *a + 1;
		}
	}

	//�����Ժ����ʱ�ļ�ʱ��(��Ҫ��ʱ�������ӳ�ʱ��)
	void TimeData::MkTimerMS(int* a, int ms) {
		std::thread MkTimerToMS(TimeData::TimermS, a, ms);
		MkTimerToMS.detach();
	}
}

// ���繦������ 
namespace IntelNet {

	//����������
	class InteS
	 {
	 private:
		 //�������簲ȫ��
		WSADATA Wser;
		//�����׿�
		SOCKET sock;
		//�����׿�
		sockaddr_in AddSock;

		struct OnlineSet {
			//�˿�����
			int port;

			//����Э�� trueΪTCP��falseΪUCP
			bool agreement;

			//IP��ַ�洢
			std::string IPCL;

			//��������
			int Namber = NULL;
		};

	 public:
		 //������Ȩ��
		 void OpenIntOP() {
			 WSAStartup(MAKEWORD(2, 2),&Wser);
		 }
		 
		 //1024-4096��׼�����ַ�
		 char EMA1024[1024] = { 0 };  
		 char EMA2048[2048] = { 0 };
		 char EMA4096[4096] = { 0 };

		 //�������
		 OnlineSet OSset;

		 //������
		 SOCKET reception;

		 // ��ʼ��������
		 void MkIntNet() {
			 //����TCP/UCP����Э��
			 if (this->OSset.agreement) {
				 this->sock = socket(AF_INET, SOCK_STREAM, 0);
			 }else{ sock = socket(AF_INET,SOCK_DGRAM, 0); }
			 this->AddSock.sin_family = AF_INET;
			 this->AddSock.sin_port = htons(this->OSset.port);
			 this->AddSock.sin_addr.S_un.S_addr = inet_addr(this->OSset.IPCL.c_str());
			 if (-1 == bind(this->sock, (struct sockaddr*)&this->AddSock, sizeof(this->AddSock))) {
				 std::cout << "�˿���IP�󶨴���error" << std::endl;
				 return;}
			 listen(sock, this->OSset.Namber);
		 }

		 //ˢ���׿�
		 void FluRecSock() {
			 this->reception = accept(this->sock, NULL, NULL);
		 }

		 //��������(�����ַ�������)
		 void Recv(char c[],int Len) {
			 recv(this->reception, c, Len,0);
		 }

		 //��������(�����ַ�������)
		 void Send(char c[], int Len) {
			 send(this->reception, c, Len, 0);
		 }
	};

	//תΪ�����ļ�(�������ͣ����ݣ�����)
		std::string CreaPost(std::string Type,std::string Send,int len){
			std::string Head = "HTTP/1.1 200 OK\r\n";
			Head += "Content-Type: " + Type + ";" + " charset=utf-8\r\n";
			Head += "Content-Length: "+ std::to_string(len) + "\r\n";
			Head += "\r\n";
			Head += Send;
			return Head;
		}
	//���¶������󣨶�����ַ��
		std::string URLtoHTTP(std::string URL) {
			std::string TUR = "HTTP/1.1 302 Found\r\n";
			TUR += "Location: " + URL + "\r\n";
			TUR+= "Content-Length: 0\r\n";
			TUR+= "\r\n";
			return TUR;
		}

	//�ж���������
		int JudgmentHttp(const char* HTTP) {
			std::regex GetGet("^(GET)"); //�ж�GIT��������
			std::regex GetPost("^(POST)");//�ж�POST����
			std::regex GetHEAD("^(HEAD)");//�ж�HEAD
			std::regex GetPUT("^(PUT)");//�ж�put
			std::regex GetDELETE("^(DELETE)"); //�ж�delete
			std::regex GetTRACE("^(TRACE)"); //�ж�TRACE
			std::regex GetOPTIONS("^(OPTIONS)");//�ж�OPTIONS
			
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

		//��ȡname(����Э�飬����NAME)
		std::vector<std::string> GetNAME(const char * HTTP,std::string Head) {
			
			std::vector<std::string>KeyGet; //�洢����
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

		//��ȡdata(����Э�飬����NAME)
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

		//��Ѱ����(�����ļ���,������ʽ)
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