#pragma once

#include <iostream>
#include <vector>
using namespace std;

class Admin {
	User signup_login(int value);
	User login();
	void signup();
	void remove_user(); //User 객체를 지움(동적할당 해제, 텍스트에서 삭제)
	//학생을 지우면 과목 목록에서 학생들을 지우고
	//교수를 지우면 과목도 지우고 학생들한테 있는 과목 리스트에서도 삭제해야 함.
	//delete 쓰느라 힘들 거 같은데 힘들면 안 빼도 될 듯

	void remove_assignment();
	//늦게 제출할 수도 있으니 마감일으로부터 3일이 지나면 지우기

	// void texteditor()
};

class User {
	string name;
	int id;
};

class Student : public User {
	vector<Subject*> st_subjects;

public:
	void check_sujects();
	void check_assignment(); //subject 중에는 assignment가 존재하지 않을 수도 있음을 고려해야 함.
	void check_OH(); //subject의 professor의 oh
	int getNum_assign(int date); //date에 마감인 과제의 개수, getMaxNum 두 함수에서 사용해야 할 함수임.
	friend void remove_user(); //admin이 user를 관리해야 하니까
};

class Professor : public User {
	Subject* p_subject;
	string oh;
public:
	void assign();
	// getmaxnum_period, getmaxnum_day 이용해서 주의창 띄우기
	// subject의 assign()을 이용해서 s_assignments 수정
	void edit_oh();
	friend void remove_user(); //admin이 user를 관리해야 하니까
};

class Subject {
	string s_name;
	Professor* s_professor;
	vector<Assignment*> s_assignments; //더 이상 assignment는 subject를 상속받지 않음.
	vector<Student*> s_students; //각 element는 이 과목을 수강하는 학생을 가리킴
public:
	int getMaxNum_period(int date);
	//수강하는 학생들 중에 date를 기준으로 며칠 이내에 과제 개수의 최댓값
	int getMaxNum_day(int date); //학생들 중 같은 날에 마감인 다른 과제의 개수의 최댓값
	friend void remove_assignment(); //admin이 subject를 관리해야 하니까
};

class Assignment{
	string a_name;
	string contents;
	int deadline; //범위 [1,365]
};
