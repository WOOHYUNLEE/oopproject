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
	Admin() {}; // singleton 외부에서 관리자 객체 추가 생성을 막기 위해
	~Admin() {};

	int today = 1; //과제 지우거나 날짜 계산할 때 필요한 오늘 날짜
	// 1월 1일=1,  12월 31일= 365
	int in_to_date(string); //input을 날짜 데이터로 바꿔서 int(today)를 리턴하는 함수
	void tomorrow(); //today 값을 1 증가시는(내일이 되는 함수)

	User* connector = nullptr;

	template <typename T>
	void signup(string& info, map<int, T*>& arr);//텍스트 저장(1)
//교수면 교수랑, 과목을 만들고 자기한테 있는 목록에 추가
//학생이면, 입력한 과목이 있는 확인하고 학생을 만들
	template <typename T>
	void login(string& info, map<int, T*>& arr); //validation based on text(1)

public:
	static Admin& getInst(); // singleton 객체 만들거나 반환하는 함수

	void helper(int& action, int& position, string& info); // signup이나 login을 부름
	bool isconnected() { return connector != nullptr; }
	User& getConnector() { return *connector; } //지금 접속중인 객체 반환

	string getToday() const; //오늘 날짜를 리턴하는 함수


	void remove_user(); //User 객체를 지움(동적할당 해제, 텍스트(1)에서 삭제)
	//교수를 지우면 과목도 지우고 학생들한테 있는 과목 코드에서도 삭제해야 함.
	//delete 쓰느라 힘들 거 같은데 힘들면 함수 빼도 될 듯

	void remove_assignment();//텍스트(2)
	//늦게 제출할 수도 있으니 마감일으로부터 3일이 지나면 지우기
	//날짜가 바뀌면 자동으로 실행
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
	string getPosition() { return "Professor"; }
};

class Student : public User {
	list<string> s_subjects;
public:
	Student(int& id, string& name, string& sub)
		: User(id, name) {
		//s_subjects = sub; @@ 바꿔야해
	}
	void check_sujects() const {
		for (list<string>::const_iterator iter = s_subjects.begin(); iter != s_subjects.end(); iter++) {
			cout << *iter << " ";
		}
	}
	void check_assignment();
	void check_oh();
	//void check_oh(string subject) {
	//	string getsub = for_each(professors.begin(), professors.end(), Professor.getsubject) {
	//		if (getsub == subject) {
	//			cout << Professor.getOH() << endl;
	//		}
	//	}
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

