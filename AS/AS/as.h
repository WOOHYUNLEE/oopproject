#pragma once

#include <iostream>

class Person() {
	string name;
	int id;
};

class Student() : public Person {
	vector assignment;

public:
	int getassignnum();

};

class Professor() : public Person {

	void assign();

};

class Assignment() : public Subject {
	string name;
	string contents;
	string deadline;
	int studnum;
};

class Subject() {
	�йݾ���, 1���� 1����
		string name;
	string professor;
	Assignment* arr;

};

class Admin() {
	Person signinorlogin(int value);
	Person login();
	void signin();

	removeassignment();

};