#include "as.h"

//static void texttocode() {
//	ifstream txt1("text1.txt", ios::in);
//	static int numline1 = 0;
//	while (!txt1.eof()) {
//		string line;
//		getline(txt1, line);
//		numline1++;
//	}
//	while (txt1) {
//		for (int i = 0; i < numline1; i++) {
//			char ID[10], name[10], subject[20];
//			string OH;
//			txt1.get(ID, 10);
//			int p_ID = atoi(ID);
//			txt1.get(name, 10);
//			string p_Name(name);
//			txt1.get(subject, 20);
//			string p_subject(subject);
//			getline(txt1, OH);
//			Professor* p1 = new Professor(p_ID, p_Name, p_subject, OH);
//			professors[p_ID] = p1;
//		}
//	}
//
//	ifstream txt2("text2.txt", ios::in);
//	static int numline2 = 0;
//	while (!txt2.eof()) {
//		string line;
//		getline(txt2, line);
//		numline2++;
//	}
//	while (txt2) {
//		for (int i = 0; i < numline2; i++) {
//			char ID[10], name[10], subject[20];
//			txt2.get(ID, 10);
//			int s_ID = atoi(ID);
//			txt2.get(name, 10);
//			string s_Name(name);
//			txt2.get(subject, 20);
//			string s_subject(subject);
//			Student* s1 = new Student(s_ID, s_Name, s_subject);
//			students[s_ID] = s1;
//		}
//		ifstream txt3("text3.txt", ios::in);
//
//		static int numline3 = 0;
//		while (!txt3.eof()) {
//			string line;
//			getline(txt3, line);
//			numline3++;
//		}
//		while (txt3) {
//			for (int i = 0; i < numline3; i++) {
//				char subject[20], assignment[10], deadline[5];
//				string contents;
//				txt3.get(subject, 20);
//				string Subject(subject);
//				txt3.get(assignment, 10);
//				string Assignment(assignment);
//				txt3.get(deadline, 5);
//				string Deadline(deadline);
//				getline(txt3, contents);
//				Assignment* A = new Assignment(Subject, Assignment, Deadline, contents);
//				subjects[subject] = A;
//			}
//		}
//	}


int main() {
	Admin& admin = Admin::getInst();
	admin.getToday();

	while (1) {
		do { //input validation 없음
			int action;
			int position;
			string info;
			cout << "sign up or log in?\n";
			cout << "1. sign up \n2. log in\n0. exit\n";
			cin >> action;
			admin.ifexit(action);
			cout << "professor or student?\n";
			cout << "1. professor \n2. student\n0. exit\n";
			cin >> position;
			admin.ifexit(position);
			cin.ignore();

			switch (action) {
			case 1: //가입
				switch (position) {
				case 1: //교수
					cout << "write your information (id name subject)\n";
					break;
				case 2: //학생
					cout << "write your information (id name subjects)\n";
					break;
				}
				break;
			case 2: //로그인
				cout << "write your information (id name)\n";
				break;
			}
			getline(cin, info);
			admin.helper(action, position, info);
		} while (!admin.isconnected()); //가입 혹은 로그인하는 구간

		User& connector = admin.getConnector();
		cout << connector.getPosition() << " " << connector.getName() << ", welcome to the scheduler!\n";

		while (connector.getPosition() == "Professor") {
			Professor& p_connector = dynamic_cast<Professor&>(connector);
			int action;
			cout << "what do you want to do?\n";
			cout << "1. add assignment \n2. post office hour \n3. check students' assignment \n4. log out \n0. exit\n";
			cin >> action;
			admin.ifexit(action);
			if (action == 4) break;

			switch (action) {
			case 1: // 과제 부여
				p_connector.assign(admin);
				break;
			case 2: // oh 수정
				//p_connector.edit_oh();
				break;
			case 3: //학생들 과제 확인
				//p_connector.check_assignment();
				break;
			}

			while (connector.getPosition() == "Student") {
				Student& s_connector = dynamic_cast<Student&>(connector);
				int action;
				cout << "what do you want to do?\n";
				cout << "1. check my subjects \n2. check my assignment list \n3. check professors' office hour \n4. log out \n0. exit\n";
				cin >> action;
				admin.ifexit(action);
				if (action == 4) break;

				switch (action) {
				case 1: // 과목 확인
					s_connector.check_sujects();
					break;
				case 2: // 과제 확인
					//s_connector.check_assignment();
					break;
				case 3: // oh 확인
					//s_connector.check_oh(subject);
					break;
				}
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

