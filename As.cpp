#include "as.h"
#include <fstream>
#include <sstream>

using namespace std;

map<int, Professor*> professors; //ID 및 교수 정보
map<int, Student*> students; //ID 및 학생 정보
map<string, list<std::shared_ptr<Assignment>>> subjects; //과목명 및 과제목록

std::ostream& operator<< (std::ostream& o, Professor& prof) {
	o << left << setw(10) << prof.getId() << setw(10) << prof.getName() << setw(20) << prof.getSubject() << prof.getOh();
	return o;
}
std::ostream& operator<< (std::ostream& o, Student& stu) {
	o << left << setw(10) << stu.getId() << setw(10) << stu.getName();
	list<string> sub = stu.get_subjects();
	for (list<string> ::iterator iter = sub.begin(); iter != sub.end(); iter++) {
		o << setw(20) << *iter;
	}
	return o;
}
std::ostream& operator<< (std::ostream& o, const pair <string, list < std::shared_ptr<Assignment>>>& sub) {
	list<std::shared_ptr<Assignment>> ass = sub.second;
	for (list<std::shared_ptr<Assignment>> ::iterator iter = ass.begin(); iter != ass.end(); iter++) {
		o << left << setw(20) << sub.first << setw(10) << (**iter).getA_name() << setw(8) << (**iter).getDeadline() << (**iter).getContents();
	}
	return o;
}

void texttocode() {
	ifstream txt1("Prof info.txt", ios::in);
	while (!txt1.eof())
	{
		int id;
		string s, name, sub, oh, OH;
		getline(txt1, s);
		stringstream ss(s);     
		ss >> id >> name >> sub;
		while (ss >> oh) {
			OH += oh + " ";
		}
		ss >> OH;
		auto prof = new Professor(id, name, sub, OH);
		professors[prof->getId()] = prof;
		ss.clear();
	}

	ifstream txt2("Stud info.txt", ios::in);
	while (!txt2.eof())
	{
		int id;
		string s, name, subject, sub;
		getline(txt2, s);
		stringstream ss(s);
		ss >> id >> name;
		while (ss >> subject) {
			sub += subject + " ";
		}
		auto stu = new Student(id, name, sub);
		students[stu->getId()] = stu;
		ss.clear();
	}

	ifstream txt3("Subj info.txt", ios::in);
	while (!txt3.eof())
	{
		string s, sub_name, sub_n, as_name, as_n, contents, con, deadline, dead;
		getline(txt3, s);
		stringstream ss(s);
		ss >> sub_name;
		string s1 = s;
		s1.erase(0, 20);
		s1.erase(10, 50);
		stringstream ss1(s1);
		while (ss1 >> as_n)
		{
			if (as_name.length() == 0)
				as_name = as_n;
			else {
				as_name += " " + as_n;
			}
		}
		string s2 = s;
		s2.erase(0, 30);
		s2.erase(8, 40);
		stringstream ss2(s2);
		while (ss2 >> dead)
		{
			if (deadline.length() == 0)
				deadline = dead;
			else {
				deadline += " " + dead;
			}
		}
		string s3 = s;
		s3.erase(0, 38);
		stringstream ss3(s3);
		while (ss3 >> con)
		{
			if (contents.length() == 0)
				contents = con;
			else {
				contents += " " + con;
			}
		}
		auto ass = new Assignment(as_name, deadline, contents);
		subjects[sub_name].push_back(std::make_shared<Assignment>(*ass));
		ss.clear();
	}
	cout << size(professors) << endl;
	cout << size(students) << endl;
	cout << size(subjects) << endl;
}

void codetotext() {
	ofstream txt1("Prof info.txt", ios::trunc);
	map<int, Professor*>::iterator iter1;
	for (iter1 = professors.begin(); iter1 != professors.end(); iter1++) {
		if ((*iter1) == (*professors.rbegin())) {
			txt1 << *((*iter1).second);
			delete ((*iter1).second);;
		}
		else {
			txt1 << *((*iter1).second) << endl;
			delete ((*iter1).second);
		}
	}


	//for (auto const& prof : professors) {
	//	txt1 << *(prof.second) << endl;
	//	delete prof.second;
	//}

	ofstream txt2("Stud info.txt", ios::trunc);
	map<int, Student*>::iterator iter2;
	for (iter2 = students.begin(); iter2 != students.end(); iter2++) {
		if ((*iter2) == (*students.rbegin())) {
			txt2 << *((*iter2).second);
			delete ((*iter2).second);;
		}
		else {
			txt2 << *((*iter2).second) << endl;
			delete ((*iter2).second);
		}
	}
	ofstream txt3("Subj info.txt", ios::trunc);
	map<string, list<std::shared_ptr<Assignment>>>::iterator iter3;
	for (iter3 = subjects.begin(); iter3 != subjects.end(); iter3++) {
		if ((*iter3) == (*subjects.rbegin())) {
			txt3 << (*iter3);
		}
		else {
			txt3 << (*iter3) << endl;
		}
	}
}

inline bool exists(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}
int main() {
	if (exists("Prof info.txt") && exists("Stud info.txt") && exists("Subj info.txt"))
	{
		texttocode();
	}
	Admin& admin = Admin::getInst();
	string today = admin.getToday();
	string past = Professor::getbefore_period(today); //exit할 때 과제 제거을 위해
	while (1) {
		do { //input validation 없음
		START:
			int action;
			int position;
			string info;
			std::cout << "원하는 활동을 선택해주세요.\n";
			cout << "1. 가입 \n2. 로그인\n0. 종료\n";
			cin >> action;
			if (action == 1234) {
				cout << endl;
				admin.showProfessors();
				admin.showStudents();
				admin.showSubjects();
				goto START;
			}
			admin.ifexit(action, past);
			cout << "해당하는 직책을 선택해주세요.\n";
			cout << "1. 교수 \n2. 학생\n0. 종료\n";
			cin >> position;
			admin.ifexit(position, past);

			switch (action) {
			case 1: //가입
				switch (position) {
				case 1: //교수
					cout << "정보를 입력해주세요. (ID 이름 과목(1개))\n";
					break;
				case 2: //학생
					cout << "정보를 입력해주세요. (ID 이름 과목)\n";
					break;
				}
				break;
			case 2: //로그인
				cout << "정보를 입력해주세요. (ID 이름)\n";
				break;
			}
			cin.ignore();
			getline(cin, info);
			admin.helper(action, position, info);
		} while (!admin.isconnected()); //가입 혹은 로그인하는 구간

		User& connector = admin.getConnector();
		cout << endl << connector.getPosition() << " " << connector.getName() << ", 과제 스케줄러에 오신 것을 환영합니다.\n\n";

		while (connector.getPosition() == "Professor") {
			Professor& p_connector = dynamic_cast<Professor&>(connector);
			int action;
			cout << "어떤 활동을 하시겠습니까?\n";
			cout << "1. 과제 부여\n2. Office hour 편집\n3. 부여한 과제 확인\n4. 로그아웃\n0. 종료\n";
			cin >> action;
			admin.ifexit(action, past);
			if (action == 4) break;

			switch (action) {
			case 1: // 과제 부여
				p_connector.assign(admin);
				break;
			case 2: // oh 수정
				p_connector.edit_oh();
				break;
			case 3: // 학생들 과제 확인
				p_connector.check_assignment();
				break;
			}
		}

		while (connector.getPosition() == "Student") {
			Student& s_connector = dynamic_cast<Student&>(connector);
			int action;
			cout << "어떤 활동을 하시겠습니까?\n";
			cout << "1. 수강 중인 과목 확인\n2. 과제 목록 확인\n3. 교수님 Office hour 확인\n4. 로그아웃\n0. 종료\n";
			cin >> action;	
			admin.ifexit(action, past);
			if (action == 4) break;

			switch (action) {
			case 1: // 과목 확인
				s_connector.check_sujects();
				break;
			case 2: // 과제 확인
				s_connector.check_assignment();
				break;
			case 3: // oh 확인
				s_connector.check_oh();
				break;
			}
		}

		admin.setConnector();
	}
}
