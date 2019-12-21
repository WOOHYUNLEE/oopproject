#include "as.h"

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

int Admin::in_to_date(string input) { //input을 날짜 데이터로 바꿔서 int(today)를 리턴하는 함수
	return stoi(input);
}


string Admin::getToday() const {
	return "string";
}

void Admin::remove_user() {
}

void Admin::remove_assignment() {
}


void ifexit(int input) { if (input == 0) exit(-1); }

int main() {
	Admin& admin = Admin::getInst();

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
				cout << "Srite your information (id name subjects)\n";
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
	cout << "What do you want to do?\n";

	while (connector.getPosition() == "Professor") {
		Professor& p_connector = dynamic_cast<Professor&>(connector);
		int action;
		cout << "1. add assignment \n2. post office hour \n3. check students' assignment \n0. exit\n";
		cin >> action;
		ifexit(action);

		switch (action) {
		case 1: // 과제 부여
			p_connector.assign();
			break;
		case 2: // oh 수정
			p_connector.edit_oh();
			break;
		case 3: //학생들 과제 확인
			p_connector.edit_oh();
			break;
		}

		while (connector.getPosition() == "Student") {
			Student& s_connector = dynamic_cast<Student&>(connector);
			int action;
			cout << "1. Check my subjects \n2. Check my assignment list \n3. Check Professors' office hour\n0. exit\n";
			cin >> action;
			ifexit(action);

			//switch (action) {
			//case 1: // 과목 확인
			//	s_connector.check_sujects();
			//	break;
			//case 2: // 과제 확인
			//	s_connector.check_assignment();
			//	break;
			//case 3: // oh 확인
			//	s_connector.check_oh();
			//	break;
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

