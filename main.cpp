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
IntelNet::InteS *Intel=new IntelNet::InteS; //��������������
bool RunInt = true; //�ж������������ݿ�
bool ShowInt = true; //�ж��Ƿ���ʾ����
bool exitd = true; //�ж��Ƿ�����
std::string RecvData; //��������

//�ļ�������������
std::vector<std::string> MenFile; //����Ŀ¼�ļ�

//д������Ŀ¼�ļ�
void OpenCinFileMenu() {
	MenFile.clear();
	std::wstring Dir = L".\\MenuData";
	CreateDirectory(Dir.c_str(), NULL);
	std::string line;
	std::ofstream outfr(".\\MenuData\\Strant.txt",std::ios::app);
	if (!outfr.is_open()) {
		std::cout << "�ļ���ȡ����" << std::endl;
		outfr.close();
		return;
	}
	outfr.close();
	std::ifstream infile(".\\MenuData\\Strant.txt");
	while (std::getline(infile, line)) {
		MenFile.push_back(line);
	}
	infile.close();

	//ѭ���鿴�ļ��Ƿ񴴽����
	for(const auto & pair:MenFile) {
		std::ofstream outf;
		outf.open(pair.c_str(),std::ios::app);
		if (!outf.is_open()) {
			std::cout << pair << "����ʧ��" << std::endl;
			outf.close();
		}
		else {
			outf.close();
		}
	}

	std::wcout << L"��ʼ���ɹ�" << std::endl;
	return;
 }



//��ʼ�����������ݿ�
void RunOpenIntel() {
		Intel->OpenIntOP(); //�򿪶�Ӧ����Ȩ��
		Intel->MkIntNet(); //��������
		while (RunInt) {
			Intel->FluRecSock(); //ˢ���׿�
			*Intel->EMA1024 = NULL;
			Intel->Recv(Intel->EMA1024, 1024);
			//���������ʾ
			if (ShowInt) {
			std::cout << Intel->EMA1024 << std::endl;
			}

			//�ж���������
			int PndJ = IntelNet::JudgmentHttp(Intel->EMA1024);
			if (PndJ == 1) {
				std::string Mn = IntelNet::URLtoHTTP("http://www.xiaofa520.cn");
				send(Intel->reception, Mn.c_str(), Mn.length(),NULL);
			}


		}
}



//���������
void RegexSwitch(std::string Input) {
	std::regex Help("^help$"); //�ṩ����
	std::regex ADD("^add");//����
	std::regex RM("^rm");//ɾ��
	std::regex INQ("^inq");//��ѯ
	std::regex CLS("^cls$");//���
	std::regex ShowInte("^ShowInte");//�Ƿ�������ص���ʾ
	std::regex Rmexit("^rmexit$"); //�˳�
	std::regex Checkfile("^checkfile$"); //�鿴�������ݿ�
	std::regex ShowFile("^ShowFile"); //�鿴�������ݿ�
	std::regex Init("^Init$");//��ʼ��
	std::regex CreaMK("^creamk");//���������ݿ�
	std::regex ClsMenu("^clsmenu$");//������Ļ��� 
	std::regex ShowFiles("^showfiles");//��ʾָ�����ݿ�
	//ShowInte������ʽ
	std::regex ShowInteON("ShowInte +(on)");
	std::regex ShowInteOFF("ShowInte\\s+(off)");
	//creamk������ʽ
	std::regex CreaMKname("^creamk\\s+(.*)$");
	//add������ʽ 
	std::regex AddFile("^add\\s+([^ ]+)");
	std::regex AddName("^add\\s+[^ ]+\\s+(.+)$");
	//rm������ʽ
	std::regex RmFile("^rm\\s+([^ ]+)");
	std::regex RmName("^rm\\s+[^ ]+\\s+(.+)$");
	//inq������ʽ 
	std::regex InqFile("^inq\\s+([^ ]+)");
	std::regex InqName("^inq\\s+[^ ]+\\s+(.+)$");
	//��ʾ���ݿ�������ʽ
	std::regex ShowFileFiles("^showfiles\\s+([^ ]+)");

	//help
	if (std::regex_search(Input, Help)) {
		std::cout << "help:����" << std::endl;
		std::cout << "add ���ݿ� ����:�����ļ�" << std::endl;
		std::cout << "rm ���ݿ� ����:ɾ��" << std::endl;
		std::cout << "inq ���ݿ� ����:��ѯ" << std::endl;
		std::cout << "cls ���ݿ� ����:���ҳ��" << std::endl;
		std::cout << "ShowInte on/off �Ƿ���ʾ����ص�" << std::endl;
		std::cout << "rmexit �˳�" << std::endl;
		std::cout << "checkfile �鿴����Щ���ݿ�" << std::endl;
		std::cout << "ShowFile ���ݿ�:�鿴���ݿ��������" << std::endl;
		std::cout << "Init ��ʼ��" << std::endl;
		std::cout << "creamk ����:�������ݿ�" << std::endl;
		std::cout << "clsmenu: ������Ļ���" << std::endl;
		std::cout << "showfiles ���ݿ�:�鿴���ݿ�����" << std::endl;
	}

	//���
	else if (std::regex_search(Input, CLS)) {
		system("cls");
		std::cout << "�ѽ���������" << std::endl;
	}

	//�Ƿ�������ص���ʾ
	else if (std::regex_search(Input, ShowInte)) {
		if (std::regex_search(Input, ShowInteON)) {
			ShowInt = true; //������ʾ����ص�
			std::cout << "������ʾ����ص�" << std::endl;
		}
		else if (std::regex_search(Input, ShowInteOFF)) {
			ShowInt = false; //�ر���ʾ����ص�
			std::cout << "�ر���ʾ����ص�" << std::endl;
		}
		else {
			std::cout << "SQL�����ɹ�" << std::endl;
		}
	}

	//�˳�
	else if (std::regex_search(Input, Rmexit)) {
		exitd = false;
		RunInt = false;
	}

	//��ʼ��
	else if (std::regex_search(Input,Init)) {
		OpenCinFileMenu();//��ʼ���洢�����ļ�
	}

	//�������ݿ�
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
				std::cout << "SQL�����ɹ�" << std::endl;
			}
			else {
				std::cout << "SQL����ʧ��" << std::endl;
			}
		}
		else {
			std::cout << "SQL�����ɹ�" << std::endl;
		}
	}

	//�鿴�������ݿ�
	else if (std::regex_search(Input, Checkfile)) {
		std::cout << "���ݿ�����·��" << std::endl;
		for (const auto& pair : MenFile) {
			std::cout << pair << std::endl;
		}
		std::cout << "----->END<-----" << std::endl;
	}

	//�������
	else if (std::regex_search(Input, ClsMenu)) {
		MenFile.clear();
		std::cout << "����������" << std::endl;
	}

	//add�������
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
		std::cout << "ȱ�ٲ���" << std::endl;
	}

	//RMɾ��
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
		std::cout << "����" << std::endl;
	}
	
	//��
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
							std::cout << "��\t" << "������" << std::endl;
							for (const auto& pair : Kesays) {
								std::cout << pair.first << "\t" << pair.second << std::endl;
							}
							return;
						}
					}
				}
			}
		}
		std::cout << "��������" << std::endl;
	}

	//�鿴���ݿ�����
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
				std::cout << "�ļ���������" << std::endl;
				for (const auto& pair : VC) {
					std::cout << pair << std::endl;
				}
				return;
			}
		}
		std::cout << "��������" << std::endl;
	 }
	
	//δָ֪��
	else {
		std::cout << "δָ֪�� " << std::endl;
	}
}

//�û�����
void UserMenu() {
	system("cls");
	std::cout << "�ѽ���������" << std::endl;
	while (exitd)
	{
		std::string Input; //���������ַ�
		std::cout << "CinToOut>>";
		std::getline(std::cin, Input);
		RegexSwitch(Input);
	}
	delete(Intel);
	return;
}



//������������
void RunIntelSet(){
	std::string TUCP; //�ж�UCP����TCP��
	system("cls");
	std::cout << "��������Ҫ�����ģ�IP��ַ��˿ڣ�����������������������" << std::endl;
	std::cin >> Intel->OSset.IPCL >> Intel->OSset.port >> Intel->OSset.Namber;
SetTCP://�����������ñ�ǩ
	std::cout << "trueΪTCP���ͣ�falseΪUTP����" << std::endl;
	std::cin >> TUCP;
	if (TUCP == "true" || TUCP == "True" || TUCP == "TRUE" || TUCP == "1") {
		Intel->OSset.agreement = true;

	}
	else if (TUCP == "false" || TUCP == "False" || TUCP == "FALSE" || TUCP == "0") {
		Intel->OSset.agreement = false;
	}
	else { std::cout << "��Ч���ͣ�����������" << std::endl; goto SetTCP; }
	std::thread OpenInt(RunOpenIntel);
	OpenInt.detach();
	UserMenu(); //�����û�����
}


//���
int main() {
	std::string User, Pasw; //�û�����
	std::cout << "\twelcome Using InTypeSendSQL" << std::endl;
	std::cout << "\t��ӭʹ��InTypeSend���ݿ�" << std::endl;
	std::cout << "���������Ա�˻�������(ROOT)" << std::endl;
	std::cout << "�˻�:";
	std::cin >> User;
	std::cout << "����:";
	std::cin >> Pasw;

	//������֤�ɹ�
	if (User == RootUser && Pasw == RootPasw) {
		RunIntelSet();
	}
	else {
		std::cout << "\t��������˻�����,ϵͳ�˳�" << std::endl;
		return 0;
	}
	return 0;
}