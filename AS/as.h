
#ifndef _HEADER_
#define _HEADER_

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iomanip>
#include <memory>

using namespace std;

class Admin;
class User;
class Student;
class Professor;
class Subject;
class Assignment;

extern map<int, Professor*> professors; // id, ���� ��ü, text1
extern map<int, Student*> students; // id, �л� ��ü, text2
extern map<string, list<std::shared_ptr<Assignment>>> subjects; // ����� �� �������, text3

class Admin final {
private:
	Admin() { setCalendar(); }; // singleton �ܺο��� ������ ��ü �߰� ������ ���� ����
	~Admin() {};

	template <typename T>
	void signup(string& info, map<int, T*>& arr); //�л��� �Է��� ���� �ִ��� Ȯ��
	template <typename T>
	void login(string& info, map<int, T*>& arr);
	User* connector = nullptr;

	list<int> calendar;
	void setCalendar(); //������ ��ĥ���� �ִ��� ����

public:

	static Admin& getInst();
	void helper(int& action, int& position, string& info);
	bool isconnected() const;
	User& getConnector() const;
	void setConnector(User* ptr = nullptr);
	void ifexit(int input);

	void getToday() const;
	int input_to_date(string input); //1231�� 365�� �ٲٴ� �Լ�
	string date_to_output(int date); //365�� 1231�� �ٲٴ� �Լ�

	void remove_assignment();

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
	int getId() { return id; } //��� ����?
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

	void assign(Admin& ad);
	int getMaxNum_period(string date, Admin& ad) const;
	string getbefore_period(string date) const;
	int getMaxNum_day(string date) const;
	void warning(string date, Admin& ad) const;
	void save(Assignment& ass);

	void edit_oh();
	void check_assignment() const;
	string getP_subject() { return p_subject; }
	string getP_oh() { return p_oh; }
	string getPosition() { return "Professor"; }
	string getSubject() { return p_subject; }
	string getOh() { return p_oh; }
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
	void check_sujects() const;
	void check_assignment() const;
	void check_oh(string subject) const;
	list<string> getS_subjects() const { return s_subjects; } // 
	list<string> get_subjects() { return s_subjects; }; // 
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



//class Subject {
//	string sub_name;
//	list<std::shared_ptr<Assignment>> assignments; //�� �̻� assignment�� subject�� ��ӹ��� ����.
//public:
//	Subject() {};
//	void assign(string sub_id); //�ؽ�Ʈ(2) //���� ��ü�� ����� �ڽ����� ����
//};

void convert_signup(string& info, int& id, string& name, string& subject);
void convert_login(string& info, int& id, string& name);


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
		T* user = arr.at(id); //���� ���ο��� ����
		if (user->getName() != name) throw 1; //���� ���� �� ����
		setConnector(user);
	}
	catch (...) {
		cout << "Error, Please chek your information" << endl;
	}
}
extern void texttocode();
extern void codetotext();

#endif // !_HEADER_


