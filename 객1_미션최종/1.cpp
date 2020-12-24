#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;
//미션6 : 테이블별 매출 + 하루 총 매출을 오늘 날짜/시간을 이름으로 갖는 txt 파일로 저장
class Table {
	int tnum;	// 테이블 번호
	int sales; // 해당 테이블 총 매출
	vector<string> mname; // 메뉴명
	vector<int> amt;// 수량
	vector<int> mprice;	// 메뉴 가격
public:
	Table() {
		setTnum(1);
		setSales(0);
		setMname("회무침");
		setAmt(1);
		setMprice(0);
	}
	Table(int n) {
		setTnum(n);
		setSales(0);
		setMname("회무침");
		setAmt(1);
		setMprice(0);
	}
	void setTnum(int n) {
		tnum = n;
	}
	void setSales(int n) {
		sales = n;
	}
	void setMname(string s) {
		mname.push_back(s);
	}
	void setAmt(int n) {
		amt.push_back(n);
	}
	void setMprice(int n) {
		mprice.push_back(n);
	}

	int getTnum() {
		return tnum;
	}
	int getSales() {
		return sales;
	}
	vector<string> getMname() {
		return mname;
	}
	vector<int> getAmt() {
		return amt;
	}
	vector<int> getMprice() {
		return mprice;
	}
	void addSales(string n, int p) {
		bool check = false;
		int cn = 0;

		for (int i = 0; i < mname.size(); i++) {
			if (mname[i] == n) {
				check = true;
				cn = i;
			}
		}
		if (check) {
			amt[cn] += 1;
			mprice[cn] = p * amt[cn];
		}
		else {
			mname.push_back(n);
			amt.push_back(1);
			mprice.push_back(p);
		}
		sales += p;
	}
	void tableDisp() {
		// 테이블 영수증
		cout << endl;
		cout << "* No. " << tnum << " *" << endl << endl;
		cout << "< 영수증 >" << endl;
		cout << "------------------------------------------" << endl;
		cout << left;
		cout.width(15);
		cout << "품명";
		cout << right;
		cout.width(5);
		cout << "수량";
		cout.width(23);
		cout << "금액\n";
		cout << "------------------------------------------\n" << endl;

		for (int i = 0; i < mname.size(); i++) {
			cout << left;
			cout.width(13);
			cout << mname[i];
			cout << right;
			cout.width(5);
			cout << amt[i];
			cout.width(24);
			if (mprice[i] == 0)
				cout << "서비스" << endl;
			else
				cout << mprice[i] << endl;
		}
		cout << "\n------------------------------------------" << endl;
		cout.width(10);
		cout << " 총 금액";
		cout.width(32);
		cout << sales << endl;
		cout << "------------------------------------------" << endl;
		cout.width(10);
		cout << "계산담당자:";
		cout.width(31);
		cout << "관리자" << endl;
		cout << "------------------------------------------\n" << endl;
	}
};

class Menu {
	vector<string> name;
	vector<int> price;
public:
	Menu() {
		name.push_back("회무침");
		price.push_back(0);
	}
	Menu(string n, int p) {
		name.push_back(n);
		price.push_back(p);
	}
	void setName(string n) {
		name[0] = n;
	}
	void setPrice(int p) {
		price[0] = p;
	}
	Menu getMenu() {
		return *this;
	}
	string getName(int n) {
		return name[n];
	}
	int getPrice(int n) {
		return price[n];
	}
	void addMenu(string n, int p) {
		name.push_back(n);
		price.push_back(p);
	}
	int getCountMenu() {
		return name.size();
	}
};

class Store {
	vector<Table> tb;
	int total;
	Menu menu;
public:
	Store() {
		tb.resize(3);
		for (int i = 0; i < 3; i++) {
			tb[i].setTnum(i);
			tb[i].setSales(0);
			tb[i].setMname("회무침");
			tb[i].setAmt(1);
			tb[i].setMprice(0);
		}
		total = 0;
		menu.setName("회무침");
		menu.setPrice(0);
	}
	Store(vector<Table> tbl, int t, Menu mn) {
		tb.resize(3);
		for (int i = 0; i < 3; i++) {
			tb[i] = tbl[i];
		}
		total = t;
		menu = mn;
	}
	void sales(int n) {
		total += n;
	}
	int getSales() {
		for (int i = 0; i < 3; i++) {
			total += tb[i].getSales();
		}
		return total;
	}
	vector<Table> getTable() {
		return tb;
	}
	void updateTable(vector<Table> tbl, int i) {
		tb[i] = tbl[i];
	}

	void setMenu(Menu m) {
		menu = m;
	}
	void printMenu() {
		cout << "\n================ Menu ===============\n\n";
		for (int i = 0; i < menu.getCountMenu(); i++) {
			if (i == 0)
				cout << "** ";
			else
				cout << "[" << i << "]";
			cout.width(5);
			cout << " ";
			cout << left;
			cout.width(19);
			cout << menu.getName(i);
			cout << right;
			cout.width(10);
			if (menu.getPrice(i) == 0)
				cout << "** 서비스" << endl;
			else
				cout << menu.getPrice(i) << endl;
		}
		cout << "\n=====================================\n" << endl;
	}
	void printReceipt(vector<Table> tbl) {
		for (int i = 0; i < 3; i++) {
			tb[i] = tbl[i];
			tb[i].tableDisp();
		}
	}
};

class Customer {
	int balance;
public:
	Customer() {
		balance = 0;
	}
	Customer(int b) {
		balance = b;
	}
	int getBalance() {
		return balance;
	}
	void pay(int t) {
		cout << balance << " - " << t << " = " << balance - t << endl;

		if (balance >= t) {
			balance -= t;
		}

		else {
			cout << "[!] 잔고가 부족합니다..[!]\n";
		}
		cout << "\n>> 남은 잔고 : " << balance << "원" << endl;
		cout << endl;
	}
};

int main() {
	bool done = false;
	int mnum = 0; // 선택한 메뉴 번호
	int tnum = 0; // 테이블 번호
	int cmd = 0; // 주문/계산 메뉴 입력
	int cmd2 = 0; // 주문내역 확인/넘어가기 메뉴 입력 

	// 테이블 객체 생성
	vector<Table> table = { Table(1), Table(2), Table(3) };

	// 메뉴 객체 생성
	Menu mn;

	// 가게 객체 생성
	Store st(table, 0, mn);

	// 메뉴 추가
	mn.addMenu("참치애 스페셜", 59000);
	mn.addMenu("연어회", 35000);
	mn.addMenu("광어회", 35000);
	mn.addMenu("추가참치", 30000);
	mn.addMenu("소주", 4000);
	mn.addMenu("맥주", 5000);
	mn.addMenu("음료수", 2000);

	// Store 객체의 메뉴 멤버변수 값 갱신
	st.setMenu(mn);

	// 추가된 메뉴 출력
	st.printMenu();
	cout << endl;

	// 손님 객체 생성 -> 주문시 주문 내역과 주문에 따른 잔고 변동 확인을 위해 do-while 전에 생성
	Customer cst[3] = { 200000, 250000, 300000 };

	// 주문 또는 계산
	do {
		cout << "[1] 주문	 [2] 계산  >>> ";
		cin >> cmd;

		if (cmd == 1) {
			cout << endl;
			cout << ">>> 테이블 번호와 주문할 메뉴 번호 입력: ";
			cin >> tnum >> mnum;
			cout << endl;
			if ((tnum < 4) && (mnum > 0) && (mnum < 8)) {
				if (cst[tnum - 1].getBalance() >= mn.getPrice(mnum)) {
					cout << "* No. " << tnum << " 주문 *\n" << "==============\n"
						<< mn.getName(mnum)
						<< " " << mn.getPrice(mnum) << "원" << endl << endl;

					table[tnum - 1].addSales(mn.getName(mnum), mn.getPrice(mnum));
					st.updateTable(table, tnum - 1);
					cst[tnum - 1].pay(mn.getPrice(mnum));
					
					cout << "[1] 주문 내역 확인	 [2] 넘어가기 >>> ";
					cin >> cmd2;
					cout << endl;
					// 주문 내역 확인 버튼 입력시(cmd2 == 1) 모든 테이블을 주문 내역 출력
					if (cmd2 == 1) {
						st.printReceipt(st.getTable());
					}
				}
				else { // 잔고보다 높은 메뉴 주문시 출력
					cout << "\n[!] 잔고가 부족합니다..[!]\n";
				}
			}
			else if ((tnum > 3) || (mnum >= 8 || (mnum < 0))) {
				cout << "테이블 번호나 메뉴 번호를 다시 확인해주세요.\n";
			}
		}
		else if (cmd == 2) {
			done = true;
			st.printReceipt(st.getTable());
			cout << "** 테이블별 손님 잔고 확인 **\n\n";
			for (int i = 0; i < 3; i++) {
				cout << "* 손님 " << i + 1 << "의 잔고: " << cst[i].getBalance() << "원\n";
				cout << endl;
			}
			// 미션6 추가!
			// txt 파일에 매출 저장
			string tn, ts, output;
			int tts = 0;
			string fname;
			// 파일명을 날짜로 지정
			tm* datetime;
			time_t now = time(NULL);
			datetime = localtime(&now);
			fname = to_string(datetime->tm_year+1900) + "_" + to_string(datetime->tm_mon+1) +
				"_" + to_string(datetime->tm_mday) + "_" + to_string(datetime->tm_hour) + 
				"_" + to_string(datetime->tm_min) + "_" + to_string(datetime->tm_sec) + ".txt";

			ofstream out(fname);
			out << "===============\n";
			for (int i = 0; i < 3; i++) {
				tn = to_string(i + 1);
				ts = to_string(table[i].getSales());
				output = " * " + tn + "번 테이블 : " + ts + "원\n" + "-------------------------\n";
				tts += table[i].getSales();
				out << output;
			}
			output = "* 총 매출 : " + to_string(tts) + "원\n" + "===============";
			out << output;
			out.close();

		}
		else {
			cout << "[!] 다시 입력해주세요!!\n\n";
		}
	} while (!done);
}