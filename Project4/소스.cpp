#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<random>
#include<iomanip>
using namespace std;

//dddd
bool FileCheck = true;
#define USER 100000
random_device rd;
default_random_engine dre{ rd() };

uniform_int_distribution<> uidName('a', 'z');
uniform_int_distribution<> uidNameLen(5, 15);

normal_distribution<> nd{ 0.0,1.0 };
normal_distribution<> nd2{ 0.0,1.0 };
class Player {
	string id;
	unsigned int breakout;                      // ��Ż�� ����
	unsigned int championsLeague;          // è�Ǿ𽺸��� ����

public:
	Player() {
		for (int i = 0; i < uidNameLen(dre); ++i)
			id += uidName(dre);
		breakout = 0;
		championsLeague = 0;
	}
	Player(string id, unsigned int breakout, unsigned int championsLeague) : id{ id }, breakout{ breakout }, championsLeague{ championsLeague }{}
	string GetID() const {
		return id;
	}
	void SetBout(unsigned int n) {
		breakout = n;
	}
	void SetChamp(unsigned int n) {
		championsLeague = n;
	}
	unsigned int GetBout() const {
		return breakout;
	}
	unsigned int GetChamp() const {
		return championsLeague;
	}

	void BoutShow(int rank) const {
		cout << setw(15) << left << id << "\t" << rank << "��\t" << "����" << (float((float(rank) / 50000) * 100)) << "%" << "\t"
			<< "��Ż�� : " << breakout << setw(10) << endl;
	}
	void ChampShow(int rank) const {
		cout << setw(15) << left << id << "\t" << rank << "��\t" << "����" << (float((float(rank) / 50000) * 100)) << "%" << "\t"
			<< "è�Ǿ𽺸��� : " << championsLeague << setw(10) << endl;
	}
};

void MakeInfo(vector<Player>& v)
{
	for (int i = 0; i < USER / 2; ++i) {
		//��Ż�� ���� ����
		double val = nd(dre);
		val = clamp(val, -5.0, 5.0);
		val += 5.0;
		val *= 2'905'887'02.6;

		unsigned int highScore = (int)val;
		if (highScore > v[i].GetBout()) {
			v[i].SetBout(highScore);
		}
	}
	for (int i = USER / 2; i < USER; ++i) {
		//è�Ǿ𽺸��� ���� ����
		double val2 = nd2(dre);
		val2 = clamp(val2, -5.0, 5.0);
		val2 += 5.0;
		val2 *= 1'112'670'38.4;

		unsigned int highScore2 = (int)val2;
		if (highScore2 > v[i].GetChamp()) {
			v[i].SetChamp(highScore2);
		}
	}
}

void Search(vector<Player>& v)
{
	string myid;
	cout << "ã�� ID�� �Է��ϼ���:";
	cin >> myid;
	sort(v.begin(), v.end(), [](const Player& a, const Player& b) {
		return a.GetBout() > b.GetBout();
		});
	for (int i = 0; i < USER / 2; ++i) {
		if (v[i].GetID() == myid) {
			cout << "��Ż��" << endl;
			v[i - 1].BoutShow(i - 1);
			v[i].BoutShow(i);
			v[i + 1].BoutShow(i + 1);
			cout << endl;
		}
	}
	sort(v.begin(), v.end(), [](const Player& a, const Player& b) {
		return a.GetChamp() > b.GetChamp();
		});
	for (int i = 0; i < USER / 2; ++i) {
		if (v[i].GetID() == myid) {
			cout << "è�Ǿ𽺸���" << endl;
			v[i - 1].ChampShow(i - 1);
			v[i].ChampShow(i);
			v[i + 1].ChampShow(i + 1);
			cout << endl;
		}
	}
}

void menu(int season)
{
	cout << "--------�Է�--------" << endl;
	cout << "1. ã��" << endl;
	cout << "2. �÷���(���� ����)" << endl;
	cout << "3. ����" << endl;
	cout << "| ���� ���� :  " << season << "  |" << endl;
	cout << "---------------------" << endl;
}

void myPlayerInit(vector<Player>& v) {
	string myid;

	cout << "�÷��̾��� ID �Է�:";
	cin >> myid;
	double val = nd(dre);
	val = clamp(val, -5.0, 5.0);
	val += 5.0;
	val *= 2'905'887'02.6;

	double val2 = nd(dre);
	val2 = clamp(val2, -5.0, 5.0);
	val2 += 5.0;
	val2 *= 1'112'670'38.4;

	v.emplace_back(myid, (int)val, (int)val2);
}

void init(vector<Player>& v) {
	ifstream in;
	in.open("STL ����.txt");
	if (in.is_open() == false)
	{
		cout << "���Ͽ� ������ �����ϴ�. �÷��̾ �����մϴ�." << endl;
		in.close();
		FileCheck = false;
	}
	if (FileCheck == true) {
		cout << "������ �����մϴ�. ������ �ҷ��ɴϴ�." << endl;
		string id;
		unsigned int breakout;
		unsigned int championsLeague;

		while (in >> id >> breakout >> championsLeague) {
			v.emplace_back(id, breakout, championsLeague);
		}
	}
	else if (FileCheck == false) {
		for (int i = 0; i < USER - 1; ++i) {
			Player p;
			v.push_back(p);
		}
	}
}

void quit(vector<Player>& v)
{
	ofstream out("STL ����.txt");
	for (int i = 0; i < USER; ++i) {
		out << v[i].GetID() << "\t" << v[i].GetBout() << "\t" << v[i].GetChamp() << endl;
	}
	cout << "������ ����Ǿ����ϴ�." << endl;
}

int main()
{
	int command;
	int season = 0;
	vector<Player> v;
	v.reserve(USER);

	init(v);
	myPlayerInit(v);
	cout << "����0 �Դϴ�. ���� �÷��̸� ���ֽñ� �ٶ��ϴ�." << endl;
	while (true) {
		menu(season);
		cin >> command;
		if (command == 1) {  //ã��
			Search(v);
		}
		else if (command == 2) { //�÷���(���� ����)
			season++;
			shuffle(v.begin(), v.end(), default_random_engine(rd()));
			MakeInfo(v);
		}
		else if (command == 3) { // ���� �� ����
			quit(v);
			break;
		}
	}
}