

#include "as.h"



int main() {
	int value{ 0 };
	string a{ "Shin" };
	cout << "signup or login?\n";
	cout << "1. signup \n2. login\n0. exit\n";
	cin >> value;
	cout << "Professor or Student?\n";
	cout << "1. Professor \n2. Student\n0. exit\n";
	cin >> value;
	cout << "Write your information(id / name)\n";
	cin >> value;
	cout << "Professor " << a << ", Welcome to the Scheduler!\n";
	cout << "What do you want to do?\n";
	cout << "1. Add assignment \n2. Post office hour \n3. Check Students' assignment \n0. exit\n";
	cout << "1\n";
	cout << "Please write information of assignment\n       Subject      :   Name    :    Contents    : Due date\n";
	cout << " 객체지향프로그래밍 :Assignment2: Making IVector : 20191212\n";
	cout << "Warning! Some of the students have too many assginments!";


	/*   int value{ 0 };
	   string a{ "LEE" };
	   cout << "signup or login?\n";
	   cout << "1. signup \n2. login\n0. exit\n";
	   cin >> value;
	   cout << "Professor or Student?\n";
	   cout << "1. Professor \n2. Student\n0. exit\n";
	   cin >> value;
	   cout << "Write your information(id / name)\n";
	   cin >> value;
	   cout << "Student " << a << ", Welcome to the Scheduler!\n";
	   cout << "What do you want to do?\n";
	   cout << "1. Check my subjects \n2. Check my assignment list \n3. Check Professors' office hour\n0. exit\n";
	   cout << "2\n";
	   cout << "       Subject      :   Name    :    Contents    : Due date\n";
	   cout << " 객체지향프로그래밍 :Assignment2: Making IVector : 20191212\n";
	   cout << "      전기역학      :12주차 과제: Solve problems : 20191213\n";*/

}