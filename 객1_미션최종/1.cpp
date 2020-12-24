#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;
//�̼�6 : ���̺� ���� + �Ϸ� �� ������ ���� ��¥/�ð��� �̸����� ���� txt ���Ϸ� ����
class Table {
	int tnum;	// ���̺� ��ȣ
	int sales; // �ش� ���̺� �� ����
	vector<string> mname; // �޴���
	vector<int> amt;// ����
	vector<int> mprice;	// �޴� ����
public:
	Table() {
		setTnum(1);
		setSales(0);
		setMname("ȸ��ħ");
		setAmt(1);
		setMprice(0);
	}
	Table(int n) {
		setTnum(n);
		setSales(0);
		setMname("ȸ��ħ");
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
		// ���̺� ������
		cout << endl;
		cout << "* No. " << tnum << " *" << endl << endl;
		cout << "< ������ >" << endl;
		cout << "------------------------------------------" << endl;
		cout << left;
		cout.width(15);
		cout << "ǰ��";
		cout << right;
		cout.width(5);
		cout << "����";
		cout.width(23);
		cout << "�ݾ�\n";
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
				cout << "����" << endl;
			else
				cout << mprice[i] << endl;
		}
		cout << "\n------------------------------------------" << endl;
		cout.width(10);
		cout << " �� �ݾ�";
		cout.width(32);
		cout << sales << endl;
		cout << "------------------------------------------" << endl;
		cout.width(10);
		cout << "�������:";
		cout.width(31);
		cout << "������" << endl;
		cout << "------------------------------------------\n" << endl;
	}
};

class Menu {
	vector<string> name;
	vector<int> price;
public:
	Menu() {
		name.push_back("ȸ��ħ");
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
			tb[i].setMname("ȸ��ħ");
			tb[i].setAmt(1);
			tb[i].setMprice(0);
		}
		total = 0;
		menu.setName("ȸ��ħ");
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
				cout << "** ����" << endl;
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
			cout << "[!] �ܰ� �����մϴ�..[!]\n";
		}
		cout << "\n>> ���� �ܰ� : " << balance << "��" << endl;
		cout << endl;
	}
};

int main() {
	bool done = false;
	int mnum = 0; // ������ �޴� ��ȣ
	int tnum = 0; // ���̺� ��ȣ
	int cmd = 0; // �ֹ�/��� �޴� �Է�
	int cmd2 = 0; // �ֹ����� Ȯ��/�Ѿ�� �޴� �Է� 

	// ���̺� ��ü ����
	vector<Table> table = { Table(1), Table(2), Table(3) };

	// �޴� ��ü ����
	Menu mn;

	// ���� ��ü ����
	Store st(table, 0, mn);

	// �޴� �߰�
	mn.addMenu("��ġ�� �����", 59000);
	mn.addMenu("����ȸ", 35000);
	mn.addMenu("����ȸ", 35000);
	mn.addMenu("�߰���ġ", 30000);
	mn.addMenu("����", 4000);
	mn.addMenu("����", 5000);
	mn.addMenu("�����", 2000);

	// Store ��ü�� �޴� ������� �� ����
	st.setMenu(mn);

	// �߰��� �޴� ���
	st.printMenu();
	cout << endl;

	// �մ� ��ü ���� -> �ֹ��� �ֹ� ������ �ֹ��� ���� �ܰ� ���� Ȯ���� ���� do-while ���� ����
	Customer cst[3] = { 200000, 250000, 300000 };

	// �ֹ� �Ǵ� ���
	do {
		cout << "[1] �ֹ�	 [2] ���  >>> ";
		cin >> cmd;

		if (cmd == 1) {
			cout << endl;
			cout << ">>> ���̺� ��ȣ�� �ֹ��� �޴� ��ȣ �Է�: ";
			cin >> tnum >> mnum;
			cout << endl;
			if ((tnum < 4) && (mnum > 0) && (mnum < 8)) {
				if (cst[tnum - 1].getBalance() >= mn.getPrice(mnum)) {
					cout << "* No. " << tnum << " �ֹ� *\n" << "==============\n"
						<< mn.getName(mnum)
						<< " " << mn.getPrice(mnum) << "��" << endl << endl;

					table[tnum - 1].addSales(mn.getName(mnum), mn.getPrice(mnum));
					st.updateTable(table, tnum - 1);
					cst[tnum - 1].pay(mn.getPrice(mnum));
					
					cout << "[1] �ֹ� ���� Ȯ��	 [2] �Ѿ�� >>> ";
					cin >> cmd2;
					cout << endl;
					// �ֹ� ���� Ȯ�� ��ư �Է½�(cmd2 == 1) ��� ���̺��� �ֹ� ���� ���
					if (cmd2 == 1) {
						st.printReceipt(st.getTable());
					}
				}
				else { // �ܰ��� ���� �޴� �ֹ��� ���
					cout << "\n[!] �ܰ� �����մϴ�..[!]\n";
				}
			}
			else if ((tnum > 3) || (mnum >= 8 || (mnum < 0))) {
				cout << "���̺� ��ȣ�� �޴� ��ȣ�� �ٽ� Ȯ�����ּ���.\n";
			}
		}
		else if (cmd == 2) {
			done = true;
			st.printReceipt(st.getTable());
			cout << "** ���̺� �մ� �ܰ� Ȯ�� **\n\n";
			for (int i = 0; i < 3; i++) {
				cout << "* �մ� " << i + 1 << "�� �ܰ�: " << cst[i].getBalance() << "��\n";
				cout << endl;
			}
			// �̼�6 �߰�!
			// txt ���Ͽ� ���� ����
			string tn, ts, output;
			int tts = 0;
			string fname;
			// ���ϸ��� ��¥�� ����
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
				output = " * " + tn + "�� ���̺� : " + ts + "��\n" + "-------------------------\n";
				tts += table[i].getSales();
				out << output;
			}
			output = "* �� ���� : " + to_string(tts) + "��\n" + "===============";
			out << output;
			out.close();

		}
		else {
			cout << "[!] �ٽ� �Է����ּ���!!\n\n";
		}
	} while (!done);
}