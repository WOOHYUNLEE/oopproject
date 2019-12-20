

#include "as.h"
#include <cassert>
#include <sstream>


Admin& Admin::getInst() {
	static Admin instance;
	return instance;
}

//template <typename T>
//void convert<T>(string& info, int& id, string& name, T& subject) {
//
//	stringstream ss(info);
//	ss >> id;
//	ss >> name;
//}	

void Admin::helper(int& action, int& position, string& info) {
	switch (action) {
	case 1:
		switch (position) { //외부 데이터에 저장
		case 1:
			signup<Professor>(info, professors);
			break;
		case 2:
			signup<Student>(info, students);
			break;
		}
	case 2:
		switch (position) {
		case 1:
			login<Professor>(info, professors);
			break;
		case 2:
			login<Student>(info, students);
			break;
		}
	}
}

template <typename T>
void Admin::signup<T>(string& info, map<int, T*> arr) {
	int id;
	string name;

	list<string> p_subject;
	convert(info, id, name, p_subject);
	T* user = new T(id, name, p_subject);
	arr.insert(pair<int, Student*>(id, user));
}

template <typename T>
void Admin::login(string& info, map<int, T*> arr) {
	try {
		User* obj = nullptr;
		switch (position) {
		case 1:
			obj = professors.at(id);
			break;
		case 2:
			obj = students.at(id);
			break;
		}
		assert(obj->getName() == name);
		connector = obj;
	}
	catch (...) {
		cout << "Error, Please chek your information";
		return;
	}
}


string Admin::getToday() const {

	return "string";
}

void Admin::assign() {
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

void ifexit(int input) { if (input == 0) exit(-1); }

int main() {
	Admin& admin = Admin::getInst();
	Admin& kk = Admin::getInst();
	cout << (admin == kk) << endl; //admin은 1개!

	do { //input validation 없음
		int action;
		int position;
		string info;
		cout << "sign up or login?\n";
		cout << "1. sign up \n2. login\n0. exit\n";
		cin >> action;
		ifexit(action);
		cout << "professor or student?\n";
		cout << "1. professor \n2. student\n0. exit\n";
		cin >> position;
		ifexit(position);
		cin.ignore();

		switch (action) {
		case 1: //가입
			switch (position) {
			case 1:
				cout << "write your information(id name id_subject subject)\n";
				getline(cin, info);
				break;
			case 2:
				cout << "write your information(id name subject)\n";
				getline(cin, info);
				break;
			}
			break;
		case 2: //로그인
			cout << "write your information(id / name)\n";
			getline(cin, info);
			break;
		}
		admin.helper(action, position, info);
	} while (!admin.isconnected()); //가입 혹은 로그인하는 구간

	User& connector = admin.getConnector();
	cout << connector.getPosition() << " " << connector.getName() << ", Welcome to the Scheduler!\n";


	//cout << "professor " << 23 << ", welcome to the scheduler!\n";
	//cout << "what do you want to do?\n";
	//cout << "1. add assignment \n2. post office hour \n3. check students' assignment \n0. exit\n";
	//cout << "1\n";
	//cout << "please write information of assignment\n       subject      :   name    :    contents    : due date\n";
	//cout << " 객체지향프로그래밍 :assignment2: making ivector : 20191212\n";
	//cout << "warning! some of the students have too many assginments!";


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