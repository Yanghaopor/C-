#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <InTypeSendSQL.h>
#include <vector>
#include <fstream>
#include <map>
#include <regex>

#define RootUser "root"
#define RootPasw "123123"
IntelNet::InteS *Intel=new IntelNet::InteS; //创建公共网络类
bool RunInt = true; //判断运行网络数据库
bool ShowInt = true; //判断是否显示数据
bool exitd = true; //判断是否运行
std::string RecvData; //接收数据

//文件操作公共变量
std::vector<std::string> MenFile; //中心目录文件

//写入中心目录文件
void OpenCinFileMenu() {
	MenFile.clear();
	std::wstring Dir = L".\\MenuData";
	CreateDirectory(Dir.c_str(), NULL);
	std::string line;
	std::ofstream outfr(".\\MenuData\\Strant.txt",std::ios::app);
	if (!outfr.is_open()) {
		std::cout << "文件读取错误" << std::endl;
		outfr.close();
		return;
	}
	outfr.close();
	std::ifstream infile(".\\MenuData\\Strant.txt");
	while (std::getline(infile, line)) {
		MenFile.push_back(line);
	}
	infile.close();

	//循环查看文件是否创建完成
	for(const auto & pair:MenFile) {
		std::ofstream outf;
		outf.open(pair.c_str(),std::ios::app);
		if (!outf.is_open()) {
			std::cout << pair << "测试失败" << std::endl;
			outf.close();
		}
		else {
			outf.close();
		}
	}

	std::wcout << L"初始化成功" << std::endl;
	return;
 }



//开始运行网络数据库
void RunOpenIntel() {
		Intel->OpenIntOP(); //打开对应网络权限
		Intel->MkIntNet(); //创建网络
		while (RunInt) {
			Intel->FluRecSock(); //刷新套口
			*Intel->EMA1024 = NULL;
			Intel->Recv(Intel->EMA1024, 1024);
			//如果开启显示
			if (ShowInt) {
			std::cout << Intel->EMA1024 << std::endl;
			}

			//判断请求类型
			int PndJ = IntelNet::JudgmentHttp(Intel->EMA1024);
			if (PndJ == 1) {
				std::string Mn = IntelNet::URLtoHTTP("http://www.xiaofa520.cn");
				send(Intel->reception, Mn.c_str(), Mn.length(),NULL);
			}


		}
}



//正则表达分流
void RegexSwitch(std::string Input) {
	std::regex Help("^help$"); //提供帮助
	std::regex ADD("^add");//增加
	std::regex RM("^rm");//删除
	std::regex INQ("^inq");//查询
	std::regex CLS("^cls$");//清空
	std::regex ShowInte("^ShowInte");//是否开启网络回调显示
	std::regex Rmexit("^rmexit$"); //退出
	std::regex Checkfile("^checkfile$"); //查看所有数据库
	std::regex ShowFile("^ShowFile"); //查看所有数据库
	std::regex Init("^Init$");//初始化
	std::regex CreaMK("^creamk");//创建新数据库
	std::regex ClsMenu("^clsmenu$");//清除中心缓存 
	std::regex ShowFiles("^showfiles");//显示指定数据库
	//ShowInte正则表达式
	std::regex ShowInteON("ShowInte +(on)");
	std::regex ShowInteOFF("ShowInte\\s+(off)");
	//creamk正则表达式
	std::regex CreaMKname("^creamk\\s+(.*)$");
	//add正则表达式 
	std::regex AddFile("^add\\s+([^ ]+)");
	std::regex AddName("^add\\s+[^ ]+\\s+(.+)$");
	//rm正则表达式
	std::regex RmFile("^rm\\s+([^ ]+)");
	std::regex RmName("^rm\\s+[^ ]+\\s+(.+)$");
	//inq正则表达式 
	std::regex InqFile("^inq\\s+([^ ]+)");
	std::regex InqName("^inq\\s+[^ ]+\\s+(.+)$");
	//显示数据库正则表达式
	std::regex ShowFileFiles("^showfiles\\s+([^ ]+)");

	//help
	if (std::regex_search(Input, Help)) {
		std::cout << "help:帮助" << std::endl;
		std::cout << "add 数据库 名称:增加文件" << std::endl;
		std::cout << "rm 数据库 名称:删除" << std::endl;
		std::cout << "inq 数据库 名称:查询" << std::endl;
		std::cout << "cls 数据库 名称:清空页面" << std::endl;
		std::cout << "ShowInte on/off 是否显示网络回调" << std::endl;
		std::cout << "rmexit 退出" << std::endl;
		std::cout << "checkfile 查看有哪些数据库" << std::endl;
		std::cout << "ShowFile 数据库:查看数据库包含内容" << std::endl;
		std::cout << "Init 初始化" << std::endl;
		std::cout << "creamk 名称:创建数据库" << std::endl;
		std::cout << "clsmenu: 清除中心缓存" << std::endl;
		std::cout << "showfiles 数据库:查看数据库内容" << std::endl;
	}

	//清空
	else if (std::regex_search(Input, CLS)) {
		system("cls");
		std::cout << "已进入管理界面" << std::endl;
	}

	//是否开启网络回调显示
	else if (std::regex_search(Input, ShowInte)) {
		if (std::regex_search(Input, ShowInteON)) {
			ShowInt = true; //开启显示网络回调
			std::cout << "开启显示网络回调" << std::endl;
		}
		else if (std::regex_search(Input, ShowInteOFF)) {
			ShowInt = false; //关闭显示网络回调
			std::cout << "关闭显示网络回调" << std::endl;
		}
		else {
			std::cout << "SQL创建成功" << std::endl;
		}
	}

	//退出
	else if (std::regex_search(Input, Rmexit)) {
		exitd = false;
		RunInt = false;
	}

	//初始化
	else if (std::regex_search(Input,Init)) {
		OpenCinFileMenu();//初始化存储中心文件
	}

	//创建数据库
	else if (std::regex_search(Input, CreaMK)) {
		std::smatch math;
		if (std::regex_search(Input, math, CreaMKname)) {
			if (math.size() > 1) {
				std::string save = ".\\MenuData\\";
				save += math[1];
				save += ".txt\n";
				std::ofstream outf(".\\MenuData\\Strant.txt",std::ios::app);
				outf << save;
				outf.close();
				std::ofstream souf(save);
				souf.close();
				std::cout << "SQL创建成功" << std::endl;
			}
			else {
				std::cout << "SQL创建失败" << std::endl;
			}
		}
		else {
			std::cout << "SQL创建成功" << std::endl;
		}
	}

	//查看所有数据库
	else if (std::regex_search(Input, Checkfile)) {
		std::cout << "数据库名与路径" << std::endl;
		for (const auto& pair : MenFile) {
			std::cout << pair << std::endl;
		}
		std::cout << "----->END<-----" << std::endl;
	}

	//清除缓存
	else if (std::regex_search(Input, ClsMenu)) {
		MenFile.clear();
		std::cout << "缓存清除完成" << std::endl;
	}

	//add添加数据
	else if (std::regex_search(Input, ADD)) {
		std::smatch match, match2;
		if (std::regex_search(Input, match, AddFile)) {
			if (match.size() > 1) {
				if (std::regex_search(Input, match2, AddName)) {
					if (match2.size() > 1) {
						std::string LineFile = ".\\MenuData\\";
						LineFile += match[1];
						LineFile += ".txt";
						std::ofstream outsd(LineFile, std::ios::app);
						outsd << match2[1].str() + "\n";
						return;
					}
				}
			}
		}
		std::cout << "缺少参数" << std::endl;
	}

	//RM删除
	else if (std::regex_search(Input,RM)) {
		std::smatch match, match2;
		std::vector<std::string> rmfile;
		if (std::regex_search(Input, match, RmFile)) {
			if (match.size() > 1) {
				if (std::regex_search(Input, match2, RmName)) {
					if (match2.size() > 1) {
						std::string LineFile = ".\\MenuData\\";
						LineFile += match[1];
						LineFile += ".txt";
						std::ifstream iutf(LineFile);
						std::string name;

						while (std::getline(iutf, name)) {
							rmfile.push_back(name);
						}
						iutf.close();
						for (auto fis = rmfile.begin(); fis != rmfile.end();) {
							if (*fis == match2[1]) {
								fis = rmfile.erase(fis);
							}
							else {
								fis++;
							}
						}
						std::ofstream oute(LineFile);
						for (const auto& pair : rmfile) {
							oute << pair + "\n";
						}
						oute.close();
						return;
					}
				}
			}
		}
		std::cout << "错误" << std::endl;
	}
	
	//查
	else if (std::regex_search(Input, INQ)) {
		std::smatch match, match2;
		if (std::regex_search(Input, match, InqFile)) {
			if (match.size() > 1) {
				if (std::regex_search(Input, match2, InqName)) {
					if (match2.size() > 1) {
						std::string file = ".\\MenuData\\"+ match[1].str() + ".txt";
						std::map<int, std::string>Kesays;
						Kesays = IntelNet::inqAll(file, match2[1]);
						if (!Kesays.empty()) {
							std::cout << "行\t" << "数据名" << std::endl;
							for (const auto& pair : Kesays) {
								std::cout << pair.first << "\t" << pair.second << std::endl;
							}
							return;
						}
					}
				}
			}
		}
		std::cout << "参数错误" << std::endl;
	}

	//查看数据库内容
	else if (std::regex_search(Input,ShowFiles)) {
		std::smatch match;
		std::vector<std::string>VC;
		if (std::regex_search(Input, match, ShowFileFiles)) {
			if (match.size() > 1) {
				std::string line;
				std::string file = ".\\MenuData\\" + match[1].str() + ".txt";
				std::ifstream inc(file);
				while (std::getline(inc, line)) {
					VC.push_back(line);
				}
				inc.close();
				std::cout << "文件内容如下" << std::endl;
				for (const auto& pair : VC) {
					std::cout << pair << std::endl;
				}
				return;
			}
		}
		std::cout << "参数错误" << std::endl;
	 }
	
	//未知指令
	else {
		std::cout << "未知指令 " << std::endl;
	}
}

//用户界面
void UserMenu() {
	system("cls");
	std::cout << "已进入管理界面" << std::endl;
	while (exitd)
	{
		std::string Input; //接收输入字符
		std::cout << "CinToOut>>";
		std::getline(std::cin, Input);
		RegexSwitch(Input);
	}
	delete(Intel);
	return;
}



//运行网络设置
void RunIntelSet(){
	std::string TUCP; //判断UCP还是TCP；
	system("cls");
	std::cout << "请输入需要监听的，IP地址与端口，还有链接人数，依次输入" << std::endl;
	std::cin >> Intel->OSset.IPCL >> Intel->OSset.port >> Intel->OSset.Namber;
SetTCP://网络类型设置标签
	std::cout << "true为TCP类型，false为UTP类型" << std::endl;
	std::cin >> TUCP;
	if (TUCP == "true" || TUCP == "True" || TUCP == "TRUE" || TUCP == "1") {
		Intel->OSset.agreement = true;

	}
	else if (TUCP == "false" || TUCP == "False" || TUCP == "FALSE" || TUCP == "0") {
		Intel->OSset.agreement = false;
	}
	else { std::cout << "无效类型，请重新输入" << std::endl; goto SetTCP; }
	std::thread OpenInt(RunOpenIntel);
	OpenInt.detach();
	UserMenu(); //进入用户界面
}


//入口
int main() {
	std::string User, Pasw; //用户密码
	std::cout << "\twelcome Using InTypeSendSQL" << std::endl;
	std::cout << "\t欢迎使用InTypeSend数据库" << std::endl;
	std::cout << "请输入管理员账户与密码(ROOT)" << std::endl;
	std::cout << "账户:";
	std::cin >> User;
	std::cout << "密码:";
	std::cin >> Pasw;

	//密码验证成功
	if (User == RootUser && Pasw == RootPasw) {
		RunIntelSet();
	}
	else {
		std::cout << "\t密码或者账户错误,系统退出" << std::endl;
		return 0;
	}
	return 0;
}