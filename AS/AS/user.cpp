#include "as.h"
#include <iomanip>

void Professor::assign(Admin& ad) {
	string a_name;
	string deadline;
	string contents;
	int n;
	cin.ignore();
	cout << "Please write a title of Assignment.(please enter no more than 10 characters)\n";//<< "Your subject is subject_name"
	getline(cin, a_name); // ���� ������ ����
	cout << "Please write the contents of Assignment.(please enter no more than 50 characters)\n";
	getline(cin, contents); // ���� ������ ����
	do {
		n = 0;
		cout << "Please write the deadline of Assignment.(please enter with 0000 format)\n";
		cin >> deadline; // ���� �������� ����
		Assignment A(a_name, deadline, contents);
		warning(deadline, ad);
		int x;
		cout << "Do you want to proceed?\n";
		cout << "1. Yes, keep going.\n2. No\n";
		cin >> x;
		if (x == 1) { // ������ �߰���
			save(A);
			cout << "Assignment is well assigned.\n";
		}
		else { // ���� ������ �߰����� ����
			int y;
			cout << "Do you want to change deadline? or just go to menu?\n";
			cout << "1. Yes, I want to change deadline.\n2. No, please go to menu.\n";
			cin >> y;
			if (y == 1) {
				n += 1;
			}
		}
	} while (n != 0);
}

int Professor::getMaxNum_period(string date, Admin& ad) const {  //�����ϴ� �л��� �߿� date�� �������� 7�� �̳��� ���� ������ �ִ�
	string gbp = getbefore_period(date);
	int stunum{ 0 };
	for (int i = 0; i < 7; ++i) {
		int num = ad.input_to_date(gbp) + i;
		if (num > 365)
			num -= 365;
		string day = ad.date_to_output(num);
		stunum += getMaxNum_day(day);
	}
	return stunum;
};

string Professor::getbefore_period(string date) const { //�־��� ��¥�� 3�� �� ��¥�� ��ȯ
	int day = atoi(date.c_str());
	string rdate;
	if (day < 200) { // 1�����̸�
		if (day <= 103) {
			day = 1231 - (103 - day);
			rdate = to_string(day);
		}
		else {
			rdate = to_string(day - 3);
		}
	}
	else  // 1������ �ƴϸ�
		if ((day - (day / 100 * 100)) <= 3) { // ���� �ڸ��� 3	�����̸�
			if (day / 100 <= 8 && (day / 100) % 2 == 0) {      // 8�������� ¦���� - ���� ���� 31�Ϸ� ���� (�Ѱ� : ������ ������� ����)
				rdate = to_string(day);
			}
			else if (day / 100 > 8 && (day / 100) % 2 == 1) { // 9���� �̻� Ȧ���� - ���� ���� 31�Ϸ� ����
				int month = day / 100;
				day = ((month - 1) * 100 + 31) - (month * 100 + 3 - day);
				rdate = to_string(day);
			}
			else {     // ���� ���� 30�� ����
				int month = day / 100;
				day = ((month - 1) * 100 + 30) - (month * 100 + 3 - day);
				rdate = to_string(day);
			}
		}
		else {
			rdate = to_string(day - 3);
		}
	if (rdate.length() == 3) {
		rdate.insert(0, "0");
		return rdate;
	}
	else {
		return rdate;
	}
}


int Professor::getMaxNum_day(string date) const { //�л��� �� ���� ���� ������ �ٸ� ������ ������ �ִ� 
	int stunum{ 0 };
	map<string, list<Assignment*>>::iterator iter;
	for (iter = subjects.begin(); iter != subjects.end(); ++iter) {// iterator�� �̿��� map ��ü Ȯ��
		list<Assignment*> L = (*iter).second; // ���� ���� ���� list ������ ����
		list<Assignment*>::iterator it;
		for (it = L.begin(); it != L.end(); it++) {
			if ((*(*it)).getDeadline() == date)
				stunum += 1;
		}
	}
	return stunum;
}

void Professor::warning(string date, Admin& ad) const { // b�� deadline�� ���ڷ� ����
	string gbp = getbefore_period(date);
	string gap;
	int num = ad.input_to_date(gbp) + 6;
	if (num > 365)
		num -= 365;
	gap = ad.date_to_output(num);
	int num_p{ getMaxNum_period(date, ad) };
	int num_d{ getMaxNum_day(date) };
	cout << "�����Ͻ� deadline�� " << date << "�Դϴ�.\n";
	cout << gbp << "~" << gap << "�� �ٸ� ������ ������ " << num_p << "�� �ֽ��ϴ�." << endl;
	cout << date << "�� ��ġ�� �ٸ� ������ ������ " << num_d << "�� �ֽ��ϴ�." << endl;
	if (num_p > 4 || num_d > 2) {
		cout << "�Ϻ� �л����� �̹� ������ �����ϴ�.\n";
	}
}

void Professor::save(Assignment& ass) {
	if (subjects.find(p_subject) == subjects.end()) { // p_subject�� ���� key �� ���ٸ�
		list<Assignment*> L;
		L.push_back(&ass);
		subjects[p_subject] = L;
	}
	else { // p_subject�� ���� key �� �ִٸ�
		subjects[p_subject].push_back(&ass);
	}
}

//edit.oh needed;

void Professor::check_assignment() {
	if (subjects.find(p_subject) == subjects.end()) // ���� ������ �ϳ��� ���ٸ�
		cout << "There is no assignment in your subject.\n";
	else {
		cout << "Your Assignment list\n";
		int n{ 1 };
		list<Assignment*>::iterator it;
		for (it = (subjects[p_subject]).begin(); it != (subjects[p_subject]).end(); it++) {
			cout << n << ". " << (*(*it)).getA_name() << endl;
			n += 1;
		}
	}
}

/////////////////////////////// Student

void Student::check_sujects() const {
	for (list<string>::const_iterator iter = s_subjects.begin(); iter != s_subjects.end(); iter++) {
		cout << *iter << " ";
	} cout << endl;
}

void Student::check_assignment() const {
	if (s_subjects.empty()) // ������ ���� ���
		cout << "There is no subject.\n"; //�߰��� ���� �߰��ϴ� ����� ����?
	else {
		cout << "Your Assignment list\n";
		int n{ 1 };
		for (list<string>::const_iterator iter = s_subjects.begin(); iter != s_subjects.end(); iter++) {
			list<Assignment*>::iterator it;
			for (it = (subjects[(*iter)]).begin(); it != (subjects[(*iter)]).end(); it++) {
				cout << n << ". " << setw(20) << left << (*iter) << " | "; // ������� �����ؼ� ǥ�� (�� : 1. ��ü�������α׷���), |�� ���м���
				cout << setw(10) << left << (*(*it)).getA_name() << " | ";
				cout << setw(5) << left << (*(*it)).getDeadline() << " | ";
				cout << setw(50) << left << (*(*it)).getContents() << endl;
			}
		}
		if (n == 1)  // ������ ������ ������ ����
			cout << "There is no assignment in your subjects.\n";
	}
}

//�ڱⰡ ��� ���� �� � ������ Ȯ������ ���� �۾� �ʿ�
//void Student::check_oh(string subject) {
//	for (list<string>::const_iterator iter = professors.begin(); iter != professors.end(); iter++) {
//		if (subject == *iter.getsubjects()) professor p1 = *iter;
//		return *iter.getoh();
//	}
//}