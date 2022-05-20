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
	unsigned int breakout;                      // 떼탈출 점수
	unsigned int championsLeague;          // 챔피언스리그 점수

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
		cout << setw(15) << left << id << "\t" << rank << "등\t" << "상위" << (float((float(rank) / 50000) * 100)) << "%" << "\t"
			<< "때탈출 : " << breakout << setw(10) << endl;
	}
	void ChampShow(int rank) const {
		cout << setw(15) << left << id << "\t" << rank << "등\t" << "상위" << (float((float(rank) / 50000) * 100)) << "%" << "\t"
			<< "챔피언스리그 : " << championsLeague << setw(10) << endl;
	}
};

void MakeInfo(vector<Player>& v)
{
	for (int i = 0; i < USER / 2; ++i) {
		//때탈출 점수 생성
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
		//챔피언스리그 점수 생성
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
	cout << "찾는 ID를 입력하세요:";
	cin >> myid;
	sort(v.begin(), v.end(), [](const Player& a, const Player& b) {
		return a.GetBout() > b.GetBout();
		});
	for (int i = 0; i < USER / 2; ++i) {
		if (v[i].GetID() == myid) {
			cout << "때탈출" << endl;
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
			cout << "챔피언스리그" << endl;
			v[i - 1].ChampShow(i - 1);
			v[i].ChampShow(i);
			v[i + 1].ChampShow(i + 1);
			cout << endl;
		}
	}
}

void menu(int season)
{
	cout << "--------입력--------" << endl;
	cout << "1. 찾기" << endl;
	cout << "2. 플레이(다음 시즌)" << endl;
	cout << "3. 종료" << endl;
	cout << "| 현재 시즌 :  " << season << "  |" << endl;
	cout << "---------------------" << endl;
}

void myPlayerInit(vector<Player>& v) {
	string myid;

	cout << "플레이어의 ID 입력:";
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
	in.open("STL 과제.txt");
	if (in.is_open() == false)
	{
		cout << "파일에 내용이 없습니다. 플레이어를 생성합니다." << endl;
		in.close();
		FileCheck = false;
	}
	if (FileCheck == true) {
		cout << "파일이 존재합니다. 정보를 불러옵니다." << endl;
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
	ofstream out("STL 과제.txt");
	for (int i = 0; i < USER; ++i) {
		out << v[i].GetID() << "\t" << v[i].GetBout() << "\t" << v[i].GetChamp() << endl;
	}
	cout << "파일이 저장되었습니다." << endl;
}

int main()
{
	int command;
	int season = 0;
	vector<Player> v;
	v.reserve(USER);

	init(v);
	myPlayerInit(v);
	cout << "시즌0 입니다. 먼저 플레이를 해주시기 바랍니다." << endl;
	while (true) {
		menu(season);
		cin >> command;
		if (command == 1) {  //찾기
			Search(v);
		}
		else if (command == 2) { //플레이(다음 시즌)
			season++;
			shuffle(v.begin(), v.end(), default_random_engine(rd()));
			MakeInfo(v);
		}
		else if (command == 3) { // 저장 후 종료
			quit(v);
			break;
		}
	}
}