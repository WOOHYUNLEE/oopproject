// AS.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

class Stud {
	수강 과목 확인
		현재 과제 확인(제출 및 미제출 확인)
		교수님 office hour 확인 및 예약

		과제 어레이 = vector 활용 //#include <Vector>
};

class Prof {
	과목 확인
		과제 추가(과목, 마감일, 제목, 내용, 경고창)
		office hour 추가 및 수정
};

class Admin {
	int signinorlogin(int value) {
		switch (value == 0)
			login();
		signin();
	}

	int login() {
		check valid != txt에서 존재하는지 확인
			- invalid : signinorlogin()으로
			- valid : return stud or profess
	}

	int signin() {
		직책 학번 이름 듣는과목들 과목들의과제
			학생 교수 모두 해당되는 과목 입력(선택지 중에 선택)
			객체를 만듦 = txt 파일에 저장
			return signinorlogin()
	}

	void delete() {
		객체 지우기
	}
}

? ? textreader(feiwfsdf) {
	사람따로 과목따로

}

int main() {

	교수님이 가입하면서 과목들을 모두 만든 후
		학생이 과목 입력 가능하다고 가정

		Admin a;
	while (1) {
		cout << "어떤 활동을 하시겠습니까?" << endl;
		cout << "1.sign in\n2.login\n0.exit";
		cin >> value;
		user = a.signinorlogin(value);

	};