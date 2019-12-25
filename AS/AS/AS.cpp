#include "as.h"
#include <fstream>

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
		o << left << setw(20) << sub.first << setw(10) << (**iter).getA_name() << setw(8) << (**iter).getDeadline() << (**iter).getContents() << endl;
	}
	return o;
}

std::istream& operator>> (std::istream& i, Professor& prof) {
	int id;
	std::string name, subject, oh;
	i >> id >> name >> subject >> oh;
	prof = Professor(id, name, subject, oh);
	return i;
}
std::istream& operator>> (std::istream& i, Student& stu) {
	int id;
	std::string name, sub;
	i >> id >> name >> sub;
	stu = Student(id, name, sub);
	return i;
}
void texttocode() {
	ifstream txt1("Prof info.txt", ios::in);
	for (auto const& prof : professors)
	{

	}
	//int numline1 = 0;
	//txt1 >> numline1;
	//for (int i = 0; i < numline1; ++i)
	//{
	//	auto prof = new Professor();
	//	txt1 >> *prof;
	//	professors[prof->getId()] = prof;
	//}
	//ifstream txt2("text2.txt", ios::in);
	//int numline2 = 0;
	//txt2 >> numline2;
	//for (int i = 0; i < numline2; ++i)
	//{
	//	auto stu = new Student();
	//	txt2 >> *stu;
	//	students[stu->getId()] = stu;
	//}
	//ifstream txt3("text1.txt", ios::in);
	//int numline1 = 0;
	//txt1 >> numline1;
	//for (int i = 0; i < numline1; ++i)
	//{
	//	auto prof = new Professor();
	//	txt1 >> *prof;
	//	professors[prof->getId()] = prof;
	//}
	//return;
	///*static int numline1 = 0;
 //  while (!txt1.eof()) {
	//  string line;
	//  getline(txt1, line);
	//  numline1++;
 //  }
 //  while (txt1) {
	//  for (int i = 0; i < numline1; i++) {
	//	 char ID[10], name[10], subject[20];
	//	 string OH;
	//	 txt1.get(ID, 10);
	//	 int p_ID = atoi(ID);
	//	 txt1.get(name, 10);
	//	 string p_Name(name);
	//	 txt1.get(subject, 20);
	//	 string p_subject(subject);
	//	 getline(txt1, OH);
	//	 Professor* p1 = new Professor(p_ID, p_Name, p_subject, OH);
	//	 professors[p_ID] = p1;
	//  }
 //  }*/

	//ifstream txt2("text2.txt", ios::in);
	//static int numline2 = 0;
	//while (!txt2.eof()) {
	//	string line;
	//	getline(txt2, line);
	//	numline2++;
	//}
	//while (txt2) {
	//	for (int i = 0; i < numline2; i++) {
	//		char ID[10], name[10], subject[20];
	//		txt2.get(ID, 10);
	//		int s_ID = atoi(ID);
	//		txt2.get(name, 10);
	//		string s_Name(name);
	//		txt2.get(subject, 20);
	//		string s_subject(subject);
	//		Student* s1 = new Student(s_ID, s_Name, s_subject);
	//		students[s_ID] = s1;
	//	}
	//}
	//ifstream txt3("text3.txt", ios::in);

	//static int numline3 = 0;
	//while (!txt3.eof()) {
	//	string line;
	//	getline(txt3, line);
	//	numline3++;
	//}
	//while (txt3) {
	//	list<std::shared_ptr<Assignment>> li;
	//	char subject[20], assignment[10], deadline[5];
	//	string contents;
	//	for (int i = 0; i < numline3; i++) {
	//		txt3.get(subject, 20);
	//		string Subject(subject);
	//		txt3.get(assignment, 10);
	//		string Assign(assignment);
	//		txt3.get(deadline, 5);
	//		string Deadline(deadline);
	//		getline(txt3, contents);
	//		Assignment* A1 = new Assignment(Assign, Deadline, contents);
	//		li.push_back(std::shared_ptr<Assignment>(A1));
	//	}
	//	subjects.insert(make_pair(subject, li));
	//}
}

void codetotext() {
	ofstream txt1("Prof info.txt", ios::trunc);
	for (auto const& prof : professors){
		txt1 << *(prof.second) << endl;
		delete prof.second;
	}

	ofstream txt2("Stud info.txt", ios::trunc);
	for (auto const& stud : students) {
		txt2 << *(stud.second) << endl;
		delete stud.second;
	}
	ofstream txt3("Subj info.txt", ios::trunc);
	for (auto const& sub : subjects) {
		txt3 << sub << endl; //contain deallocate
	}
}

int main() {
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


/*
cout << "please write information of assignment\n       subject      :   name    :    contents    : due date\n";
cout << " 객체지향프로그래밍 :assignment2: making ivector : 20191212\n";
cout << "warning! some of the students have too many assginments!";

cout << "       Subject      :   Name    :    Contents    : Due date\n";
cout << " 객체지향프로그래밍 :Assignment2: Making IVector : 20191212\n";
cout << "      전기역학      :12주차 과제: Solve problems : 20191213\n";*/

