#pragma once

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <cassert>
#include <sstream>
#include <algorithm>
using namespace std;

class Admin;
class User;
class Student;
class Professor;
class Subject;
class Assignment;

static void codetotext(map<int, Professor*>, map<int, Student*> students, map<string, list<Assignment*>>);

static void texttocode(map<int, Professor*>, map<int, Student*> students, map<string, list<Assignment*>>);


static map<int, Professor*> professors; // id, 교수 객체, text1
static map<int, Student*> students; // id, 학생 객체, text2
static map<string, list<Assignment*>> subjects; // 과목명 및 과제목록, text3

class Admin final{
private:
	Admin() { setCalendar(); }; // singleton 외부에서 관리자 객체 추가 생성을 막기 위해
	~Admin() {};

	template <typename T>
	void signup(string& info, map<int, T*>& arr); //학생이 입력한 과목 있는지 확인
	template <typename T>
	void login(string& info, map<int, T*>& arr);
	User* connector = nullptr;

	list<int> calendar;
	void setCalendar(); //월별로 며칠까지 있는지 저장
	int today = 1;
	int input_to_date(string input); //input을 날짜 데이터로 바꿔서 int(today)를 리턴하는 함수
	string date_to_output(int date);
	void add_date();

public:
	static Admin& getInst();
	void helper(int& action, int& position, string& info);
	bool isconnected() const;
	User& getConnector() const;

	int getToday() const;
	string getDate(int date) const;

	void remove_user();
	void remove_assignment();//텍스트(2)
	//늦게 제출할 수도 있으니 마감일으로부터 3일이 지나면 지우기
	//날짜가 바뀌면 자동으로 실행
	//1일이나 365에 마감일이면 범위 외 값은 고려하지 않기
};

class User {
	int id;
	string name;
public:
	User() {};
	User(int& i_id, string& i_name) {
		id = i_id;
		name = i_name;
	};
	int getId() { return id; }
	string getName() { return name; }
	virtual string getPosition() = 0;
};

class Professor : public User {
	string p_subject;
	string oh;
public:
	Professor(int& id, string& name, string& sub)
		: User(id, name) {
		p_subject = sub;
	}

	void assign();
	// getmaxnum_period, getmaxnum_day 이용해서 주의창 띄우기
	// subject의 assign()을 이용
		//assign 함수에서 구현하는 데에 필요한 3함수?
	int getMaxNum_period(int date) const;
	//수강하는 학생들 중에 date를 기준으로 며칠 이내에 과제 개수의 최댓값
	int getMaxNum_day(int date) const; //학생들 중 같은 날에 마감인 다른 과제의 개수의 최댓값
	int getNum_ass(int date) const; //date에 마감인 과제의 개수, getMaxNum 두 함수에서 사용해야 할 함수임.

	void edit_oh();
	void check_assignment();
	string getPosition() { return "Professor"; }
};

class Student : public User {
	list<string> s_subjects;
public:
	Student(int& id, string& name, string& sub)
		: User(id, name) {
		stringstream ss(sub);
		string str;
		while (ss >> str) {
			s_subjects.push_back(str);
		}
	}
	void check_sujects() const {
		for (list<string>::const_iterator iter = s_subjects.begin(); iter != s_subjects.end(); iter++) {
			cout << *iter << " ";
		} cout << endl;
	}
	//void check_assignment() const {
	//	for (list<string>::const_iterator iter = s_subjects.begin(); iter != s_subjects.end(); iter++) {
	//		list<assignment*> assignment = subjects.find(*iter)->second;
	//		for (list<string>::iterator iter = assignment.begin(); iter != assignment.end(); iter++) {
	//			cout << *iter.getname() << " " << *iter.getcontents() << " " << *iter.getdeadline << endl;
	//		}
	//	}
	//}
	//void check_oh(string subject) {
	//	for (list<string>::const_iterator iter = professors.begin(); iter != professors.end(); iter++) {
	//		if (subject == *iter.getsubjects()) professor p1 = *iter;
	//		return *iter.getoh();
	//	}
	//}
	string getPosition() { return "Student"; }
};


class Assignment {
	string a_name;
	string contents;
	int deadline; //범위 [1,365]
public:
	string getName() { return a_name; }
	string getContents() { return contents; }
	int getDeadline() { return deadline; }

};

//class Subject {
//	string sub_name;
//	list<Assignment*> assignments; //더 이상 assignment는 subject를 상속받지 않음.
//public:
//	Subject() {};
//	void assign(string sub_id); //텍스트(2) //과제 객체를 만들고 자신한테 넣음
//};


void convert_signup(string& info, int& id, string& name, string& subject) {
	stringstream ss(info);
	ss >> id;
	ss >> name;
	ss >> subject;
} // convert 묶을 수는 없나?
void convert_login(string& info, int& id, string& name) {
	stringstream ss(info);
	ss >> id;
	ss >> name;
}

template <typename T>
void Admin::signup(string& info, map<int, T*>& arr) {
	int id;
	string name;
	string subject;
	convert_signup(info, id, name, subject);
	if (arr.find(id) != arr.end()) {
		cout << "Your id already exists" << endl;
		return;
	}
	T* user = new T(id, name, subject);
	arr.insert(pair<int, T*>(id, user));
	//if (typeid(T).name() == "class Professor") {
	//	//cout << "Professor can take only 1 class";
	//	}
}

template <typename T>
void Admin::login(string& info, map<int, T*>& arr) {
	int id;
	string name;
	convert_login(info, id, name);
	try {
		T* user = arr.at(id); //존재 여부에서 에러
		assert(user->getName() == name); //같지 않을 때 에러
		connector = user;
	}
	catch (...) {
		cout << "Error, Please chek your information" << endl;
	}
}

