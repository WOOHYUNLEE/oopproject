#pragma once

#include <iostream>
#include <string>
#include <list>
#include <map>
using namespace std;

void texteditor();

class Admin;
class User;
class Student;
class Professor;
class Subject;
class Assignment;


class Admin final{
private:
	Admin() {}; // singleton 외부에서 관리자 객체 추가 생성을 막기 위해
	~Admin() {};

	int today = 1; //과제 지우거나 날짜 계산할 때 필요한 오늘 날짜
	// 1월 1일=1,  12월 31일= 365
	int in_to_today(); //input을 날짜 데이터로 바꿔서 int(today)를 리턴하는 함수
	void tomorrow(); //today 값을 1 증가시는(내일이 되는 함수)

	User* connector = nullptr;
	map<string, Subject*> subjects; // 과목 고유 코드 및 과목 객체
	map<int, Professor*> professors; // id, 교수 객체
	map<int, Student*> students; // id, 학생 객체

	void signup(int& position, int& id, string& name, list<string>& subjects);//객체를 생성하고 동적할당 하고 텍스트 저장(1)
//교수면 교수랑, 과목을 만들고 자기한테 있는 목록에 추가
//학생이면, 입력한 과목이 있는 확인하고 학생을 만들고 과목 객체 목록에 자신을 추가하고 자신이 갖고 있는 목록에 과목을 추가한다.
	void login(int position, int id, string name); //validation based on text(1)

public:
	void helper(int& action, string& info, int& position); //input을 id, name, subject로 변환하고 signup이나 login을 부름
	bool isconnected() { return connector != nullptr; }
	User& getConnector() { return *connector; } //지금 접속중인 객체 반환

	static Admin& getInst(); // singleton 객체 만들거나 반환하는 함수

	string getToday() const; //오늘 날짜를 리턴하는 함수

	void assign(Assignment*); //과제에 있는 과목코드로 과목을 찾고 그 안에 과제를 넣어줌

	//assign 함수에서 구현하는 데에 필요한 3함수?
	int getMaxNum_period(int date) const;
	//수강하는 학생들 중에 date를 기준으로 며칠 이내에 과제 개수의 최댓값
	int getMaxNum_day(int date) const; //학생들 중 같은 날에 마감인 다른 과제의 개수의 최댓값
	int getNum_ass(int date) const; //date에 마감인 과제의 개수, getMaxNum 두 함수에서 사용해야 할 함수임.

	void remove_user(); //User 객체를 지움(동적할당 해제, 텍스트(1)에서 삭제)
	//교수를 지우면 과목도 지우고 학생들한테 있는 과목 코드에서도 삭제해야 함.
	//delete 쓰느라 힘들 거 같은데 힘들면 함수 빼도 될 듯

	void remove_assignment();//텍스트(2)
	//늦게 제출할 수도 있으니 마감일으로부터 3일이 지나면 지우기
	//날짜가 바뀌면 자동으로 실행

	bool operator==(const Admin& other); //must be removed
};

class User {
	int id;
	string name;
	list<string> sub_id; //과목 고유 코드
public:
	User() {};
	User(int& i_id, string& i_name, list<string>& i_sub_id) {
		id = i_id;
		name = i_name;
		sub_id = i_sub_id;
	};
	int getId() { return id; }
	string getName() { return name; }
	virtual string getPosition() = 0;
};

class Professor : public User {
	string oh;
public:
	Professor(int& id, string& name, list<string>& sub_id)
		: User(id, name, sub_id) {}
	void assign();
	// getmaxnum_period, getmaxnum_day 이용해서 주의창 띄우기
	// subject의 assign()을 이용
	void edit_oh();
	string getPosition() { return "Professor"; }
};

class Student : public User {
public:
	Student(int& id, string& name, list<string>& sub_id)
		: User(id, name, sub_id) {}
	void check_sujects() const;
	void check_assignment() const; //subject 중에는 assignment가 존재하지 않을 수도 있음을 고려해야 함.
	void check_oh(); //subject의 professor의 oh
	void remove_subject(); //과목이 지워질때 id_subjects를 중 지워진 과목 코드를 삭제하는 함수
	string getPosition() { return "Student"; }
};


class Subject {
	string sub_id; //과목 고유 코드
	string sub_name;
	list<Assignment*> assignments; //더 이상 assignment는 subject를 상속받지 않음.
public:
	Subject() {};
	void assign(string id); //텍스트(2) //과제 객체를 만들어 admin에 파라미터로 주면 거기서 처리해줌
};

class Assignment {
	string a_name;
	string contents;
	int deadline; //범위 [1,365]
};