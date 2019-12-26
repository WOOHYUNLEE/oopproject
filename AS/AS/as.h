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

extern map<int, Professor*> professors; //ID �� ���� ����
extern map<int, Student*> students; //ID �� �л� ����
extern map<string, list<std::shared_ptr<Assignment>>> subjects; //����� �� �������

class Admin final {
private:
	Admin() { setCalendar(); };
	~Admin() {};

	template <typename T>
	void signup(string& info, map<int, T*>& arr); //����
	template <typename T>
	void login(string& info, map<int, T*>& arr); //�α���
	User* connector = nullptr; //���� ���� ���� user

	void convert_signup(string& info, int& id, string& name, string& subject); //������ ���� ������ �и�
	void convert_login(string& info, int& id, string& name); //�α����� ���� ������ �и�

	list<int> calendar; //�޷� ������
	void setCalendar(); //������ ��ĥ���� �ִ��� ����

public:
	static Admin& getInst(); //Admin ��ü ���� �� ��ȯ
	void helper(int& action, int& position, string& info); // ���� or �α���
	bool isconnected() const; //�α��� ���� ����(������ ���� ����)
	User& getConnector() const; //���� ���� ���� user ��ȯ
	void setConnector(User* ptr = nullptr); //������ �ʱ�ȭ �� ����
	void ifexit(int input, string past); //���� ����, �ؽ�Ʈ ���, ����

	string getToday() const;
	int input_to_date(string input); //1231�� 365�� �ٲٴ� �Լ�
	string date_to_output(int date); //365�� 1231�� �ٲٴ� �Լ�

	void remove_assignment(string past); //�������� ���÷κ��� 3�� ���̸� ���� ����

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

	void assign(Admin& ad); //���� �ο�
	int getMaxNum_period(string date, Admin& ad) const;  //�л��� �߿� date�� �������� 7�� �̳��� ���� ������ �ִ�
	static string getbefore_period(string date); //date�� 3�� �� ��¥ ��ȯ
	int getMaxNum_day(string date) const; //�л��� �� ���� ���� ������ �ٸ� ������ ������ �ִ� 
	void warning(string date, Admin& ad) const; //����â ���
	void save(Assignment& ass); //sujects�� ���� ����

	void edit_oh(); //Oh ����
	void check_assignment() const; //���� Ȯ��

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
	void check_sujects() const; //���� Ȯ��
	void check_assignment() const; //���� Ȯ��
	void check_oh() const; //Oh Ȯ��

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
		cout << "�Է��Ͻ� ������ �̹� �����մϴ�." << endl;
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
		T* user = arr.at(id); //���� ���ο��� ����
		if (user->getName() != name) throw 1; //���� ���� �� ����
		setConnector(user);
	}
	catch (...) {
		cout << "�Է��Ͻ� ������ �ٽ� Ȯ�����ּ���." << endl;
	}
}
extern void texttocode();
extern void codetotext();

#endif // !_HEADER_