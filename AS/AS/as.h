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
	�йݾ���, 1���� 1����
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
	//�ʰ� �����ϴ� ��쵵 ���� �״� �׳� �� �ᵵ �� �� �����ϴ�.

};