#pragma once

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <iterator>
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

public:
	static Admin& getInst();
	void helper(int& action, int& position, string& info);
	bool isconnected() const;
	User& getConnector() const;
	void ifexit(int input);

	void getToday() const;
	int input_to_date(string input); //1231을 365로 바꾸는 함수
	string date_to_output(int date); //365를 1231로 바꾸는 함수

	void remove_assignment();
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
	int getId() { return id; } //어디에 쓰임?
	string getName() { return name; }
	virtual string getPosition() = 0;
};

class Professor : public User {
	string p_subject;
	string p_oh;
public:
	Professor(int& id, string& name, string& sub)
		: User(id, name) {
		p_subject = sub;
	}
	Professor(int& id, string& name, string& sub, string& oh)
		: Professor(id, name, sub) {
		p_oh = oh;
	}

	void assign(Admin & ad);
	int getMaxNum_period(string date, Admin& ad) const;
	string getbefore_period(string date) const;
	int getMaxNum_day(string date) const; 
	void warning(string date, Admin& ad) const;
	void save(Assignment& ass);

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
	void check_sujects() const;
	void check_assignment() const;
	void check_oh(string subject) const;
	string getPosition() { return "Student"; }
};


class Assignment {
	string a_name;
	string deadline;
	string contents;

public:
	Assignment() {};
	Assignment(string na, string dead, string con) {
		a_name = na;
		deadline = dead;
		contents = con;
	}
	//string getName() { return a_name; }
	//string getContents() { return contents; }
	string getDeadline() { return deadline; }

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

