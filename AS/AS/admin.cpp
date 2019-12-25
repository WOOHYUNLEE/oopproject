#include "as.h"
#include <time.h>


//가입 및 로그인 관련
void Admin::convert_signup(string& info, int& id, string& name, string& subject) {
	stringstream ss(info);
	string sub;
	ss >> id;
	ss >> name;
	while (ss >> sub) {
		subject += sub + " ";
	}
	subject.erase(subject.end() - 1);
}
void Admin::convert_login(string& info, int& id, string& name) {
	stringstream ss(info);
	ss >> id;
	ss >> name;
}

Admin& Admin::getInst() { //Admin 객체 생성 및 반환
	static Admin instance;
	return instance;
}

void Admin::helper(int& action, int& position, string& info) { //가입 혹은 로그인
	switch (action) {
	case 1:
		switch (position) {
		case 1:
			signup<Professor>(info, professors);
			break;
		case 2:
			signup<Student>(info, students);
			break;
		}
		break;
	case 2:
		switch (position) {
		case 1:
			login<Professor>(info, professors);
			break;
		case 2:
			login<Student>(info, students);
			break;
		}
		break;
	}
}

bool Admin::isconnected() const { return connector != nullptr; }

User& Admin::getConnector() const { return *connector; }

void Admin::setConnector(User* ptr) { connector = ptr; } 

//날짜 관련
void Admin::setCalendar() { //월별로 며칠까지 있는지 저장
	for (int month = 1; month < 13; month++)
		switch (month) {
		case 2:
			calendar.push_back(28);
			break;
		case 1:	case 3:	case 5: case 7: case 8: case 10: case 12:
			calendar.push_back(31);
			break;
		case 4:	case 6:	case 9: case 11:
			calendar.push_back(30);
			break;
		}
}

int Admin::input_to_date(string input) {
	int month = stoi(input.substr(0, 2));
	int date = stoi(input.substr(2, 2));
	int result = 0;
	for (list<int>::iterator iter = calendar.begin(); month > 1; month--, iter++) {
		result += *iter;
	}
	return result + date;
}

string Admin::date_to_output(int date) {
	int month = 0;
	for (list<int>::iterator iter = calendar.begin(); *iter < date; iter++) {
		date -= *iter;
		month++;
	}
	string month_str = to_string(month + 1);
	string date_str = to_string(date);
	if (month_str.length() == 1)  month_str = "0" + month_str;
	if (date_str.length() == 1) date_str = "0" + date_str;
	return month_str + date_str;
}

string Admin::getToday() const {
	struct tm date;
	time_t timer;
	timer = time(NULL);
	localtime_s(&date, &timer);
	string month_str = to_string(date.tm_mon + 1);
	string date_str = to_string(date.tm_mday);
	if (month_str.length() == 1)  month_str = "0" + month_str;
	if (date_str.length() == 1) date_str = "0" + date_str;
	return month_str + date_str;
}

//데이터 관리
void Admin::remove_assignment(string past) { //마감일이 오늘로부터 3일 전이면 과제 삭제
	map<string, list<std::shared_ptr<Assignment>>>::iterator iter;
	for (iter = subjects.begin(); iter != subjects.end(); iter++) {
		list<std::shared_ptr<Assignment>>& asslist = iter->second;
		for (list<std::shared_ptr<Assignment>>::iterator iterr = asslist.begin(); iterr != asslist.end();) {
			string dead = (*iterr)->getDeadline();
			if (dead == past) { asslist.erase(iterr++); }
			else iterr++;
		}
	}
}

void Admin::ifexit(int input, string past) {
	if (input == 0) {
		remove_assignment(past);
		codetotext();
		_CrtDumpMemoryLeaks();
		exit(-1);
	}
}

void Admin::showProfessors() {
	cout << "@PROFESSOR" << endl;
	map<int, Professor*>::const_iterator it;
	for (it = professors.begin(); it != professors.end(); it++) {
		Professor* ob = it->second;
		cout << "id :" << it->first << "// 이름, 과목, OH :" << ob->getName() << "/" << ob->getSubject() << "/" << ob->getOh() << endl;
	}
}
void Admin::showStudents() {
	cout << "@STUDENT" << endl;
	map<int, Student*>::const_iterator it;
	for (it = students.begin(); it != students.end(); it++) {
		Student* ob = it->second;
		cout << "id :" << it->first << "// 이름, 과목 :" << ob->getName() << "/";
		ob->check_sujects();
	}
}
void Admin::showSubjects() {
	cout << "@SUBJECT" << endl;
	map<string, list<std::shared_ptr<Assignment>>>::const_iterator it;
	for (it = subjects.begin(); it != subjects.end(); it++) {
		list<std::shared_ptr<Assignment>> ob = it->second;
		for (list<std::shared_ptr<Assignment>>::const_iterator itt = ob.begin(); itt != ob.end(); itt++)
		{
			cout << "sub_name :" << it->first << " //";
			cout << " 이름, 마감일, 내용 :" << (*(*itt)).getA_name() << "/" << (*(*itt)).getDeadline() << "/" << (*(*itt)).getContents() << endl;
		}
	}cout << endl;
}