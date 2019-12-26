#pragma once
#ifndef _HEADER_
#define _HEADER_

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <memory>
#include <sys/stat.h>

using namespace std;

class Admin;
class User;
class Student;
class Professor;
class Subject;
class Assignment;

extern map<int, Professor*> professors; //ID 및 교수 정보
extern map<int, Student*> students; //ID 및 학생 정보
extern map<string, list<std::shared_ptr<Assignment>>> subjects; //과목명 및 과제목록

class Admin final {
private:
	Admin() { setCalendar(); };
	~Admin() {};

	template <typename T>
	void signup(string& info, map<int, T*>& arr); //가입
	template <typename T>
	void login(string& info, map<int, T*>& arr); //로그인
	User* connector = nullptr; //현재 접속 중인 user

	void convert_signup(string& info, int& id, string& name, string& subject); //가입을 위한 데이터 분리
	void convert_login(string& info, int& id, string& name); //로그인을 위한 데이터 분리

	list<int> calendar; //달력 데이터
	void setCalendar(); //월별로 며칠까지 있는지 저장

public:
	static Admin& getInst(); //Admin 객체 생성 및 반환
	void helper(int& action, int& position, string& info); // 가입 or 로그인
	bool isconnected() const; //로그인 성공 여부(접속자 존재 여부)
	User& getConnector() const; //현재 접속 중인 user 반환
	void setConnector(User* ptr = nullptr); //접속자 초기화 및 변경
	void ifexit(int input, string past); //과제 제거, 텍스트 출력, 종료

	string getToday() const;
	int input_to_date(string input); //1231을 365로 바꾸는 함수
	string date_to_output(int date); //365를 1231로 바꾸는 함수

	void remove_assignment(string past); //마감일이 오늘로부터 3일 전이면 과제 삭제

	void showProfessors();
	void showStudents();
	void showSubjects();
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
	string p_oh;
public:
	Professor()
		: User() {}
	Professor(int& id, string& name, string& sub)
		: User(id, name) {
		p_subject = sub;
	}
	Professor(int& id, string& name, string& sub, string& oh)
		: Professor(id, name, sub) {
		p_oh = oh;
	}

	void assign(Admin& ad); //과제 부여
	int getMaxNum_period(string date, Admin& ad) const;  //학생들 중에 date를 기준으로 7일 이내에 과제 개수의 최댓값
	static string getbefore_period(string date); //date의 3일 전 날짜 반환
	int getMaxNum_day(string date) const; //학생들 중 같은 날에 마감인 다른 과제의 개수의 최댓값 
	void warning(string date, Admin& ad) const; //주의창 출력
	void save(Assignment& ass); //sujects에 과제 저장

	void edit_oh(); //Oh 편집
	void check_assignment() const; //과제 확인

	string getSubject() { return p_subject; }
	string getOh() { return p_oh; }
	string getPosition() { return "Professor"; }
};

class Student : public User {
	list<string> s_subjects;
public:
	Student()
		:User() {}
	Student(int& id, string& name, string& sub)
		: User(id, name) {
		stringstream ss(sub);
		string str;
		while (ss >> str) {
			s_subjects.push_back(str);
		}
	}
	void check_sujects() const; //과목 확인
	void check_assignment() const; //과제 확인
	void check_oh() const; //Oh 확인

	list<string> get_subjects() { return s_subjects; };
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
	string getA_name() { return a_name; }
	string getContents() { return contents; }
	string getDeadline() { return deadline; }
};


template <typename T>
void Admin::signup(string& info, map<int, T*>& arr) {
	int id;
	string name;
	string subject;
	convert_signup(info, id, name, subject);
	if (arr.find(id) != arr.end()) {
		cout << "입력하신 정보가 이미 존재합니다." << endl;
		return;
	}
	T* user = new T(id, name, subject);
	arr.insert(pair<int, T*>(id, user));
}

template <typename T>
void Admin::login(string& info, map<int, T*>& arr) {
	int id;
	string name;
	convert_login(info, id, name);
	try {
		T* user = arr.at(id); //존재 여부에서 에러
		if (user->getName() != name) throw 1; //같지 않을 때 에러
		setConnector(user);
	}
	catch (...) {
		cout << "입력하신 정보를 다시 확인해주세요." << endl;
	}
}
extern void texttocode();
extern void codetotext();

#endif // !_HEADER_