#include "as.h"
#include <iterator>

//가입 및 로그인 관련
Admin& Admin::getInst() {
	static Admin instance;
	return instance;
}

void Admin::helper(int& action, int& position, string& info) {
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

//날짜 관련
void Admin::setCalendar() {
	for (int month = 1; month<13; month++)
		switch (month) {
		case 2:
			calendar.push_back(28);
			break;
		case 1:	case 3:	case 5: case 7: case 8: case 10: case 12:
			calendar.push_back(31);
		case 4:	case 6:	case 9: case 11:
			calendar.push_back(30);
	}
}

int Admin::input_to_date(string input) { //validation
	int month = stoi(input.substr(0, 2));
	int date = stoi(input.substr(2, 2));
	int result = 0;
	for (int val = 1; val != month; val++) {
		result += val;
	}
	return result + date;
}

string Admin::date_to_output(int date) { //validation
	for (list<int>::iterator iter = calendar.begin(); *iter < date; iter++) {
		

	}
	//return result + date;
}

void Admin::add_date() { today++; remove_assignment(); }

int Admin::getToday() const { return today; }

string Admin::getDate(int date) const {
	string str = to_string(date);
	cout << str;
	str.insert(2, "/");
	return str;
}

//데이터 관리
void Admin::remove_user() {
}

void Admin::remove_assignment() {
}


void ifexit(int input) { if (input == 0) exit(-1); }

int main() {

	list<int> lt;


	list<int>::iterator iter;
	for (iter = lt.begin(); iter != lt.end(); ++iter) {
		cout << *iter << ' ';
	}
	cout << endl;

출처: https://hyeonstorage.tistory.com/326 [개발이 하고 싶어요]
	Admin& admin = Admin::getInst();
	while (1) {
		do { //input validation 없음
			int action;
			int position;
			string info;
			cout << "Sign up or Log in?\n";
			cout << "1. sign up \n2. log in\n0. exit\n";
			cin >> action;
			ifexit(action);
			cout << "Professor or Student?\n";
			cout << "1. professor \n2. student\n0. exit\n";
			cin >> position;
			ifexit(position);
			cin.ignore();

			switch (action) {
			case 1: //가입
				switch (position) {
				case 1: //교수
					cout << "Write your information (id name subject)\n";
					break;
				case 2: //학생
					cout << "Write your information (id name subjects)\n";
					break;
				}
				break;
			case 2: //로그인
				cout << "Write your information (id name)\n";
				break;
			}
			getline(cin, info);
			admin.helper(action, position, info);
		} while (!admin.isconnected()); //가입 혹은 로그인하는 구간

		User& connector = admin.getConnector();
		cout << connector.getPosition() << " " << connector.getName() << ", Welcome to the Scheduler!\n";

		while (connector.getPosition() == "Professor") {
			Professor& p_connector = dynamic_cast<Professor&>(connector);
			int action;
			cout << "What do you want to do?\n";
			//cout << "(Today is " << admin.getDate(admin.getToday()) << ".)" << endl;
			cout << "1. Add assignment \n2. Post office hour \n3. Check students' assignment \n4. Log out \n0. exit\n";
			cin >> action;
			ifexit(action);
			if (action == 4) break;

			//switch (action) {
			//case 1: // 과제 부여
			//	p_connector.assign();
			//	break;
			//case 2: // oh 수정
			//	p_connector.edit_oh();
			//	break;
			//case 3: //학생들 과제 확인
			//	p_connector.check_assignment();
			//	break;
		}

		while (connector.getPosition() == "Student") {
			Student& s_connector = dynamic_cast<Student&>(connector);
			int action;
			cout << "What do you want to do?\n";
			//cout << "(Today is " << admin.getDate(admin.getToday()) << ".)" << endl;
			cout << "1. Check my subjects \n2. Check my assignment list \n3. Check Professors' office hour \n4. Log out \n0. exit\n";
			cin >> action;
			ifexit(action);
			if (action == 4) break;

			switch (action) {
			case 1: // 과목 확인
				s_connector.check_sujects();
				break;
			case 2: // 과제 확인
			//	s_connector.check_assignment();
				break;
			case 3: // oh 확인
			//	s_connector.check_oh(string);
				break;
			}
		}
	}
}

	/*
	cout << "please write information of assignment\n       subject      :   name    :    contents    : due date\n";
	cout << " 객체지향프로그래밍 :assignment2: making ivector : 20191212\n";
	cout << "warning! some of the students have too many assginments!";

	cout << "       Subject      :   Name    :    Contents    : Due date\n";
	cout << " 객체지향프로그래밍 :Assignment2: Making IVector : 20191212\n";
	cout << "      전기역학      :12주차 과제: Solve problems : 20191213\n";*/

