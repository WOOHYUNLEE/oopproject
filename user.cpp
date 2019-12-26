#include "as.h"
#include <iomanip>

void Professor::assign(Admin& ad) {
	string a_name;
	string deadline;
	string contents;
	int n;
	cin.ignore();
	cout << "과제의 제목을 입력해주세요.(10 글자 이하로 입력해주세요.)\n";//<< "Your subject is subject_name"
	getline(cin, a_name); // 과제 제목을 받음
	cout << "과제의 내용을 입력해주세요.(50 글자 이하로 입력해주세요.)\n";
	getline(cin, contents); // 과제 내용을 받음
	do {
		n = 0;
		cout << "과제의 마감일을 입력해주세요.\n";
		cout << "(예시: 0105, 1125)\n";
		cin >> deadline; // 과제 마감일을 받음
		Assignment A(a_name, deadline, contents);
		warning(deadline, ad);
		int x;
		cout << "계속 진행하시겠습니까?\n";
		cout << "1. 네\n2. 아니오\n";
		cin >> x;
		if (x == 1) { // 과제를 추가함
			save(A);
			cout << "성공적으로 과제가 부여되었습니다.\n\n";
		}
		else { // 아직 과제를 추가하지 않음
			int y;
			cout << "마감일 바꾸시겠습니까? 혹은 메인 메뉴로 돌아가시겠습니까?\n";
			cout << "1. 마감일 변경\n2. 메인 메뉴\n";
			cin >> y;
			cout << endl;
			if (y == 1) {
				n += 1;
			}
		}
	} while (n != 0);
}

int Professor::getMaxNum_period(string date, Admin& ad) const { //학생들 중에 date를 기준으로 7일 이내에 과제 개수의 최댓값
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

string Professor::getbefore_period(string date) { //date의 3일 전 날짜 반환
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
	else if (day > 300 && day < 400) {
		if (day <= 303) {
			day = 228 - (303 - day);
			rdate = to_string(day);
		}
		else {
			rdate = to_string(day - 3);
		}
	}
	else  // 1월달이 아니면
		if ((day - (day / 100 * 100)) <= 3) { // 끝의 자리가 3   이하이면
			if (day / 100 <= 8 && (day / 100) % 2 == 0) {      // 8월달이하 짝수달 - 앞의 달이 31일로 끝남 (한계 : 윤년을 고려하지 않음)
				int month = day / 100;
				day = ((month - 1) * 100 + 31) - (month * 100 + 3 - day);
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
	cout << "설정하신 마감일은 " << date << "입니다.\n";
	cout << gbp << "~" << gap << "에 과제는 " << num_p << "개 있습니다." << endl;
	cout << date << "에 겹치는 과제는 " << num_d << "개 있습니다." << endl;
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

void Professor::edit_oh() {
	string office;
	cout << "Office hour 정보를 입력해주세요.\n";
	cout << "(예시 월:14-16/수:13-18)\n";
	cin.ignore();
	getline(cin, office);
	p_oh = office;
	cout << endl;
};

void Professor::check_assignment() const {
	if (subjects.find(p_subject) == subjects.end()) // 아직 과제가 하나도 없다면
		cout << "부여하신 과제가 없습니다.\n\n";
	else {
		cout << "< 과제 목록 >\n";
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
	if (s_subjects.empty()) // 과목이 없는 경우
		cout << "수강 중인 과목이 없습니다.\n\n";
	else {
		cout << "< 과제 목록 >\n";
		cout << "번호 " << setw(20) << left << "과목명" << " | ";
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
		}cout << endl;
		if (n == 1)  // 과목은 있지만 과제는 없음
			cout << "수강 중인 과목에 과제가 없습니다.\n\n";
	}
}


void Student::check_oh() const {
	if (s_subjects.empty())
		cout << "수강중인 과목이 없습니다.";
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
			N++;
		}
		map<int, Professor*>::iterator it;
		int print{ 0 };
		for (it = professors.begin(); it != professors.end(); ++it) {// iterator를 이용해 map 전체 확인
			if ((*((*it).second)).getSubject() == sub && (*((*it).second)).getOh().length() > 1) {
				print = 1;
				cout << sub << " 과목 교수님의 Office hour는 " << (*((*it).second)).getOh() << "입니다.\n\n";
			}
		}
		if (print == 0) cout << "해당 과목의 Office hour가 존재하지 않습니다.\n\n";
	}
}



