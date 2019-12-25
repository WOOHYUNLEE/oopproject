#include "as.h"
#include <iomanip>

void Professor::assign(Admin& ad) {
	string a_name;
	string deadline;
	string contents;
	int n;
	cin.ignore();
	cout << "������ ������ �Է����ּ���.(10 ���� ���Ϸ� �Է����ּ���.)\n";//<< "Your subject is subject_name"
	getline(cin, a_name); // ���� ������ ����
	cout << "������ ������ �Է����ּ���.(50 ���� ���Ϸ� �Է����ּ���.)\n";
	getline(cin, contents); // ���� ������ ����
	do {
		n = 0;
		cout << "������ �������� �Է����ּ���.\n";
		cout << "(����: 0105, 1125)\n";
		cin >> deadline; // ���� �������� ����
		Assignment A(a_name, deadline, contents);
		warning(deadline, ad);
		int x;
		cout << "��� �����Ͻðڽ��ϱ�?\n";
		cout << "1. ��\n2. �ƴϿ�\n";
		cin >> x;
		if (x == 1) { // ������ �߰���
			save(A);
			cout << "���������� ������ �ο��Ǿ����ϴ�.\n\n";
		}
		else { // ���� ������ �߰����� ����
			int y;
			cout << "������ �ٲٽðڽ��ϱ�? Ȥ�� ���� �޴��� ���ư��ðڽ��ϱ�?\n";
			cout << "1. ������ ����\n2. ���� �޴�\n";
			cin >> y;
			cout << endl;
			if (y == 1) {
				n += 1;
			}
		}
	} while (n != 0);
}

int Professor::getMaxNum_period(string date, Admin& ad) const { //�л��� �߿� date�� �������� 7�� �̳��� ���� ������ �ִ�
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

string Professor::getbefore_period(string date) { //date�� 3�� �� ��¥ ��ȯ
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
	else if (day > 300 && day < 400) {
		if (day <= 303) {
			day = 228 - (303 - day);
			rdate = to_string(day);
		}
		else {
			rdate = to_string(day - 3);
		}
	}
	else  // 1������ �ƴϸ�
		if ((day - (day / 100 * 100)) <= 3) { // ���� �ڸ��� 3   �����̸�
			if (day / 100 <= 8 && (day / 100) % 2 == 0) {      // 8�������� ¦���� - ���� ���� 31�Ϸ� ���� (�Ѱ� : ������ ������� ����)
				int month = day / 100;
				day = ((month - 1) * 100 + 31) - (month * 100 + 3 - day);
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
	map<string, list<std::shared_ptr<Assignment>>>::iterator iter;
	for (iter = subjects.begin(); iter != subjects.end(); ++iter) {// iterator�� �̿��� map ��ü Ȯ��
		list<std::shared_ptr<Assignment>> L = (*iter).second; // ���� ���� ���� list ������ ����
		list<std::shared_ptr<Assignment>>::iterator it;
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
	cout << "�����Ͻ� �������� " << date << "�Դϴ�.\n";
	cout << gbp << "~" << gap << "�� ������ " << num_p << "�� �ֽ��ϴ�." << endl;
	cout << date << "�� ��ġ�� ������ " << num_d << "�� �ֽ��ϴ�." << endl;
	if (num_p > 4 || num_d > 2) {
		cout << "�Ϻ� �л����� �̹� ������ �����ϴ�.\n";
	}
}

void Professor::save(Assignment& ass) {
	subjects[p_subject].push_back(std::make_shared<Assignment>(ass));
	//if (subjects.find(p_subject) == subjects.end()) { // p_subject�� ���� key �� ���ٸ�
	//	list<std::shared_ptr<Assignment>> L;
	//	L.push_back(&ass);
	//	subjects[p_subject] = L;
	//}
	//else { // p_subject�� ���� key �� �ִٸ�
	//	subjects[p_subject].push_back(&ass);
	//}
}

void Professor::edit_oh() {
	string office;
	cout << "Office hour ������ �Է����ּ���.\n";
	cout << "(���� ��:14-16/��:13-18)\n";
	cin.ignore();
	getline(cin, office);
	p_oh = office;
	cout << endl;
};

void Professor::check_assignment() const {
	if (subjects.find(p_subject) == subjects.end()) // ���� ������ �ϳ��� ���ٸ�
		cout << "�ο��Ͻ� ������ �����ϴ�.\n\n";
	else {
		cout << "< ���� ��� >\n";
		int n{ 1 };
		list<std::shared_ptr<Assignment>>::iterator it;
		for (it = (subjects[p_subject]).begin(); it != (subjects[p_subject]).end(); it++) {
			cout << n << ". " << ((*(*it)).getA_name()) << endl;
			n += 1;
		}cout << endl;
	}
}


/////////////////////////////// Student

void Student::check_sujects() const {
	for (list<string>::const_iterator iter = s_subjects.begin(); iter != s_subjects.end(); iter++) {
		cout << *iter << " ";
	} cout << endl << endl;
}

void Student::check_assignment() const {
	if (s_subjects.empty()) // ������ ���� ���
		cout << "���� ���� ������ �����ϴ�.\n\n";
	else {
		cout << "< ���� ��� >\n";
		cout << "��ȣ " << setw(20) << left << "�����" << " | ";
		cout << setw(10) << left << "���� ����" << " | ";
		cout << setw(5) << left << "���� ������" << " | ";
		cout << setw(50) << left << "���� ����" << endl;
		int n{ 1 };
		for (list<string>::const_iterator iter = s_subjects.begin(); iter != s_subjects.end(); iter++) {
			list<std::shared_ptr<Assignment>>::iterator it;
			for (it = (subjects[(*iter)]).begin(); it != (subjects[(*iter)]).end(); it++) {
				cout << " " << n << ". " << setw(20) << left << (*iter) << " | "; // ������� �����ؼ� ǥ�� (�� : 1. ��ü�������α׷���), |�� ���м���
				cout << setw(10) << left << (*(*it)).getA_name() << " | ";
				cout << setw(5) << left << (*(*it)).getDeadline() << " | ";
				cout << setw(50) << left << (*(*it)).getContents() << endl;
				n += 1;
			}
		}cout << endl;
		if (n == 1)  // ������ ������ ������ ����
			cout << "���� ���� ���� ������ �����ϴ�.\n\n";
	}
}


void Student::check_oh() const {
	if (s_subjects.empty())
		cout << "�������� ������ �����ϴ�.";
	else {
		cout << "� ������ ������ Office hour�� Ȯ���Ͻðڽ��ϱ�?\n";
		int n{ 1 };
		for (list<string>::const_iterator iter = s_subjects.begin(); iter != s_subjects.end(); iter++) {
			cout << n << ". " << *iter << endl;
			n += 1;
		}
		int subnum;
		cin >> subnum; // ����ڰ� ������� ���� ����
		int N{ 1 };
		string sub; // ����ڰ� ������� ���� : sub
		for (list<string>::const_iterator iter = s_subjects.begin(); iter != s_subjects.end(); iter++) {
			if (N == subnum) {
				sub = (*iter);
				break;
			}
			N++;
		}
		map<int, Professor*>::iterator it;
		int print{ 0 };
		for (it = professors.begin(); it != professors.end(); ++it) {// iterator�� �̿��� map ��ü Ȯ��
			if ((*((*it).second)).getSubject() == sub && (*((*it).second)).getOh().length() > 1) {
				print = 1;
				cout << sub << " ���� �������� Office hour�� " << (*((*it).second)).getOh() << "�Դϴ�.\n\n";
			}
		}
		if (print == 0) cout << "�ش� ������ Office hour�� �������� �ʽ��ϴ�.\n\n";
	}
}



