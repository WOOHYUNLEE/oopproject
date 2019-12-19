

#include "as.h"
#include <cassert>


Admin& Admin::getInst() {
	static Admin instance;
	return instance;
}

void Admin::helper(int& action, string& info, int& position) {
	int id =0;
	string name="ㅎㅎ";
	list<string> subjects;
	subjects.push_back("d");
	switch (action) {
	case 1:
		//info를 id, name, subjects로 나눔
		signup(position, id, name, subjects);
		break;
	case 2:
		//info를 id, name으로 나눔
		login(position, id, name);
		break;
	}
}

void Admin::signup(int& position, int& id, string& name, list<string>& subjects) {
	switch (position) { //외부 데이터에 저장
	case 1: {
		Professor* prof = new Professor(id, name, subjects);
		professors.insert(pair<int, Professor*>(id, prof));
		break;}
	case 2: {
		Student* stud = new Student(id, name, subjects);
		students.insert(pair<int, Student*>(id, stud));
		break; }
	}
}

void Admin::login(int position, int id, string name) {
	try {
		switch (position) {
		case 1:
			connector = professors.at(id);
			break;
		case 2:
			connector = students.at(id);
			break;
		}
	}
	catch(...) {
		cout << "Error, Please chek your information";
		return;
	}
}

string Admin::getToday() const {

	return "string";
}

void Admin::assign(Assignment*) {
}

int Admin::getMaxNum_period(int date) const {
	return 0;
}

int Admin::getMaxNum_day(int date) const {
	return 0;
}

int Admin::getNum_ass(int date) const {
	return 0;
}

void Admin::remove_user() {
}

void Admin::remove_assignment() {
}

bool Admin::operator==(const Admin& other) {
	return this == &other;
}

void exit(int input) { if (input == 0) exit(-1); }

int main() {
	Admin& admin = Admin::getInst();
	Admin& kk = Admin::getInst();
	cout << (admin == kk) << endl; //admin은 1개!

	do{ //input validation 없음
		int action;
		int position;
		string info;
		cout << "sign up or login?\n";
		cout << "1. sign up \n2. login\n0. exit\n";
		cin >> action;
		exit(action);
		cout << "professor or student?\n";
		cout << "1. professor \n2. student\n0. exit\n";
		cin >> position;
		exit(position);
		switch (action) {
		case 1:
			cout << "write your information(id / name / subject)\n";
			cin.ignore();
			getline(cin, info);
			break;
		case 2:
			cout << "write your information(id / name)\n";
			cin.ignore();
			getline(cin, info);
			break;
		}
		admin.helper(action, info, position);
	} while (!admin.isconnected()); //가입 혹은 로그인하는 구간

	cout << "professor " << 23 << ", welcome to the scheduler!\n";
	cout << "what do you want to do?\n";
	cout << "1. add assignment \n2. post office hour \n3. check students' assignment \n0. exit\n";
	cout << "1\n";
	cout << "please write information of assignment\n       subject      :   name    :    contents    : due date\n";
	cout << " 객체지향프로그래밍 :assignment2: making ivector : 20191212\n";
	cout << "warning! some of the students have too many assginments!";


	/*   int value{ 0 };
	   string a{ "LEE" };
	   cout << "signup or login?\n";
	   cout << "1. signup \n2. login\n0. exit\n";
	   cin >> value;
	   cout << "Professor or Student?\n";
	   cout << "1. Professor \n2. Student\n0. exit\n";
	   cin >> value;
	   cout << "Write your information(id / name)\n";
	   cin >> value;
	   cout << "Student " << a << ", Welcome to the Scheduler!\n";
	   cout << "What do you want to do?\n";
	   cout << "1. Check my subjects \n2. Check my assignment list \n3. Check Professors' office hour\n0. exit\n";
	   cout << "2\n";
	   cout << "       Subject      :   Name    :    Contents    : Due date\n";
	   cout << " 객체지향프로그래밍 :Assignment2: Making IVector : 20191212\n";
	   cout << "      전기역학      :12주차 과제: Solve problems : 20191213\n";*/

}