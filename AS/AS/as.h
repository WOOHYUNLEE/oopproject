#pragma once

#include <iostream>
using namespace std;

class Person {
	string name;
	int id;
};

class Student : public Person {
	vector assignment;

public:
	int getassignnum();

};

class Professor : public Person {

	void assign();

};

class Assignment : public Subject {
	string name;
	string contents;
	string deadline;
	int studnum;
};

class Subject {
	분반없음, 1과목 1교수
		string name;
	string professor;
	Assignment* arr;

};

class Admin {
	Person signup_login(int value);
	Person login();
	void signin();
	void remove();

	//removeassignment();
	//늦게 제출하는 경우도 있을 테니 그냥 안 써도 될 거 같습니다.

};