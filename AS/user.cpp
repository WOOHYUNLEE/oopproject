#include "as.h"
#include <iomanip>

void Professor::assign(Admin& ad) {
	string a_name;
	string deadline;
	string contents;
	int n;
	cin.ignore();
	cout << "Please write a title of Assignment.(please enter no more than 10 characters)\n";//<< "Your subject is subject_name"
	getline(cin, a_name); // 과제 제목을 받음
	cout << "Please write the contents of Assignment.(please enter no more than 50 characters)\n";
	getline(cin, contents); // 과제 내용을 받음
	do {
		n = 0;
		cout << "Please write the deadline of Assignment.(please enter with 0000 format)\n";
		cin >> deadline; // 과제 마감일을 받음
		Assignment A(a_name, deadline, contents);
		warning(deadline, ad);
		int x;
		cout << "Do you want to proceed?\n";
		cout << "1. Yes, keep going.\n2. No\n";
		cin >> x;
		if (x == 1) { // 과제를 추가함
			save(A);
			cout << "Assignment is well assigned.\n";
		}
		else { // 아직 과제를 추가하지 않음
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

int Professor::getMaxNum_period(string date, Admin& ad) const {  //수강하는 학생들 중에 date를 기준으로 7일 이내에 과제 개수의 최댓값
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

string Professor::getbefore_period(string date) const { //주어진 날짜의 3일 전 날짜를 반환
	int day = atoi(date.c_str());
	string rdate;
	if (day < 200) { // 1월달이면
		if (day <= 103) {
			day = 1231 - (103 - day);
			rdate = to_string(day);
		}
		else {
			rdate = to_string(day - 3);
		}
	}
	else  // 1월달이 아니면
		if ((day - (day / 100 * 100)) <= 3) { // 끝의 자리가 3	이하이면
			if (day / 100 <= 8 && (day / 100) % 2 == 0) {      // 8월달이하 짝수달 - 앞의 달이 31일로 끝남 (한계 : 윤년을 고려하지 않음)
				rdate = to_string(day);
			}
			else if (day / 100 > 8 && (day / 100) % 2 == 1) { // 9월달 이상 홀수달 - 앞의 달이 31일로 끝남
				int month = day / 100;
				day = ((month - 1) * 100 + 31) - (month * 100 + 3 - day);
				rdate = to_string(day);
			}
			else {     // 앞의 달이 30로 끝남
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


int Professor::getMaxNum_day(string date) const { //학생들 중 같은 날에 마감인 다른 과제의 개수의 최댓값 
	int stunum{ 0 };
	map<string, list<std::shared_ptr<Assignment>>>::iterator iter;
	for (iter = subjects.begin(); iter != subjects.end(); ++iter) {// iterator를 이용해 map 전체 확인
		list<std::shared_ptr<Assignment>> L = (*iter).second; // 쉽게 보기 위해 list 변수를 만듦
		list<std::shared_ptr<Assignment>>::iterator it;
		for (it = L.begin(); it != L.end(); it++) {
			if ((*(*it)).getDeadline() == date)
				stunum += 1;
		}
	}
	return stunum;
}

void Professor::warning(string date, Admin& ad) const { // b는 deadline을 인자로 받음
	string gbp = getbefore_period(date);
	string gap;
	int num = ad.input_to_date(gbp) + 6;
	if (num > 365)
		num -= 365;
	gap = ad.date_to_output(num);
	int num_p{ getMaxNum_period(date, ad) };
	int num_d{ getMaxNum_day(date) };
	cout << "설정하신 deadline은 " << date << "입니다.\n";
	cout << gbp << "~" << gap << "에 다른 과목의 과제는 " << num_p << "개 있습니다." << endl;
	cout << date << "에 겹치는 다른 과목의 과제는 " << num_d << "개 있습니다." << endl;
	if (num_p > 4 || num_d > 2) {
		cout << "일부 학생들은 이미 과제가 많습니다.\n";
	}
}

void Professor::save(Assignment& ass) {
	subjects[p_subject].push_back(std::make_shared<Assignment>(ass));
	//if (subjects.find(p_subject) == subjects.end()) { // p_subject에 대한 key 가 없다면
	//	list<std::shared_ptr<Assignment>> L;
	//	L.push_back(&ass);
	//	subjects[p_subject] = L;
	//}
	//else { // p_subject에 대한 key 가 있다면
	//	subjects[p_subject].push_back(&ass);
	//}
}

//edit.oh needed;

void Professor::check_assignment() const {
	if (subjects.find(p_subject) == subjects.end()) // 아직 과제가 하나도 없다면
		cout << "There is no assignment in your subject.\n";
	else {
		cout << "Your Assignment list\n";
		int n{ 1 };
		list<std::shared_ptr<Assignment>>::iterator it;
		for (it = (subjects[p_subject]).begin(); it != (subjects[p_subject]).end(); it++) {
			cout << n << ". " << ((*(*it)).getA_name()) << endl;
			n += 1;
		}
	}
}
void Professor::edit_oh() {
	string office;
	cout << "Please write an information of your office hour.\n";
	cin >> office;
	p_oh = office;
};



/////////////////////////////// Student

void Student::check_sujects() const {
	for (list<string>::const_iterator iter = s_subjects.begin(); iter != s_subjects.end(); iter++) {
		cout << *iter << " ";
	} cout << endl;
}

void Student::check_assignment() const {
	if (s_subjects.empty()) // 과목이 없는 경우
		cout << "There is no subject yet.\n";
	else {
		cout << "Your Assignment list\n";
		cout << "Num " << setw(20) << left << "과목명" << " | ";
		cout << setw(10) << left << "과제 제목" << " | ";
		cout << setw(5) << left << "과제 마감일" << " | ";
		cout << setw(50) << left << "과제 내용" << endl;
		int n{ 1 };
		for (list<string>::const_iterator iter = s_subjects.begin(); iter != s_subjects.end(); iter++) {
			list<std::shared_ptr<Assignment>>::iterator it;
			for (it = (subjects[(*iter)]).begin(); it != (subjects[(*iter)]).end(); it++) {
				cout << " " << n << ". " << setw(20) << left << (*iter) << " | "; // 과목명을 정렬해서 표시 (예 : 1. 객체지향프로그래밍), |는 구분선임
				cout << setw(10) << left << (*(*it)).getA_name() << " | ";
				cout << setw(5) << left << (*(*it)).getDeadline() << " | ";
				cout << setw(50) << left << (*(*it)).getContents() << endl;
				n += 1;
			}
		}
		if (n == 1)  // 과목은 있지만 과제는 없음
			cout << "There is no assignment in your subjects.\n";
	}
}


void Student::check_oh(string subject) const {
	if (s_subjects.empty())
		cout << "아직 과목이 없습니다.";
	else {
		cout << "어떤 과목의 교수님 Office hour를 확인하시겠습니까?\n";
		int n{ 1 };
		for (list<string>::const_iterator iter = s_subjects.begin(); iter != s_subjects.end(); iter++) {
			cout << n << ". " << *iter << endl;
			n += 1;
		}
		int subnum;
		cin >> subnum; // 사용자가 보고싶은 과목 선택
		int N{ 1 };
		string sub; // 사용자가 보고싶은 과목 : sub
		for (list<string>::const_iterator iter = s_subjects.begin(); iter != s_subjects.end(); iter++) {
			if (N == subnum) {
				sub = (*iter);
				break;
			}
		}
		//map<int, Professor*> professors
		map<int, Professor*>::iterator it;
		for (it = professors.begin(); it != professors.end(); ++it) {// iterator를 이용해 map 전체 확인
			if ((*((*it).second)).getSubject() == sub) {
				cout << sub << "과목 교수님의 Office hour는 " << (*((*it).second)).getOh() << "입니다." << endl;
			}
		}
	}
}


//자기가 듣는 과목 중 어떤 과목을 확인할지 고르는 작업 필요
//void Student::check_oh(string subject) {
//	for (list<string>::const_iterator iter = professors.begin(); iter != professors.end(); iter++) {
//		if (subject == *iter.getsubjects()) professor p1 = *iter;
//		return *iter.getoh();
//	}
//}


