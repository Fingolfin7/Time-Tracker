#include <iostream>
#include <vector>
#include <windows.h> // allows us to use "PlaySound()"
#include <fstream>
#include <string>
#include <chrono>
#include <conio.h>

#pragma comment (lib, "Winmm.lib")

struct subj {
	std::string name;
	double total_time;

	subj()
		:name(""), total_time(0)
	{}

	subj(std::string subjectName)
		:name(subjectName), total_time(0)
	{}

	void setName(std::string Sname) {
		this->name = Sname;
	}
};

std::vector<subj> Subject;

int choice;
void save_data();
void load_data();
void menu();

struct Timer {
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<double> duration;
	subj* genericSubject;

	Timer(subj& Subj)
		:start(std::chrono::high_resolution_clock::now()), genericSubject(&Subj), duration(0)//member initalizer list
	{
	}

	~Timer() {
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		genericSubject->total_time += duration.count() / 60;

		std::cout << "\n\nSession time (in minutes): " << duration.count() / 60 << "\n";
		std::cout << "Total time (in minutes): " << genericSubject->total_time << "\n";
		system("pause");
		save_data();
	}
};

void save_data() {//saves time totals for each subject
	std::ofstream write("LogTime.txt");
	if (write.is_open()) {
		for (int i = 0; i < Subject.size(); i++) {
			write << Subject[i].total_time << std::endl;
		}
	}
}

void load_data() {// reads in time totals for each subject
	std::ifstream read("LogTime.txt");
	std::string str;
	if (read.is_open()) {
		for (int i = 0; i < Subject.size(); i++) {
			read >> str;
			Subject[i].total_time = std::stod(str);
		}
	}

	read.close();
}

void bell_sound() {
	PlaySound(TEXT("clock-chimes-daniel_simon.wav"), NULL, SND_ASYNC);
}

void timer(subj& subject) {
	system("cls");
	Timer timeSubj(subject);
	double sessionLength;

	std::cout << "Enter seesion length (in hours)" << std::endl;
	std::cout << ">";
	std::cin >> sessionLength;

	sessionLength *= 60;
	system("cls");

	std::cout << subject.name << ": " << std::endl;
	std::cout << "Time Elapsed: ";

	std::chrono::time_point<std::chrono::steady_clock> sessTime = std::chrono::steady_clock::now() + std::chrono::minutes(int(sessionLength));

	while (std::chrono::steady_clock::now() < sessTime) {
		for (int i = 0; i < 6; i++) {//30 minutes

			std::chrono::time_point<std::chrono::steady_clock> block = std::chrono::steady_clock::now() + std::chrono::minutes(5);

			while (std::chrono::steady_clock::now() < block) {
				//do nothing
				if (_kbhit()) {
					std::cin.get();
					timeSubj.~Timer();
					menu();
				}
			}

			std::cout << char(219) << " ";
		}

		std::cout << "  ";

		bell_sound();
	}

}

void select_subject() {
	system("cls");
	std::cout << "Select Subject:" << std::endl;
	for (int i = 0; i < Subject.size(); i++) {
		std::cout << i + 1 << ". " << Subject[i].name << "," << std::endl;
	}
	std::cout << ">";
	std::cin >> choice;
}

void show_totals() {
	system("cls");
	int choice;
	std::cout << "Totals per subject: " << std::endl << std::endl;

	for (int i = 0; i < Subject.size(); i++) {
		std::cout << Subject[i].name << "(" << Subject[i].total_time / 60 << " hrs)" << std::endl;

		for (int counter = 0; counter < int(Subject[i].total_time / 60); counter++) {//each block is an hour 
			std::cout << char(219) << " ";
		}
		std::cout << std::endl << std::endl;
	}

	std::cout << std::endl << std::endl;
	system("pause");
}

void menu() {
	int optn = 0;

	system("cls");

	std::cout << "Time Tracker" << std::endl;
	std::cout << "1.New Session," << std::endl;
	std::cout << "2.Show Totals," << std::endl;
	std::cout << "3.Exit." << std::endl;
	std::cout << ">";
	std::cin >> optn;

	switch (optn)
	{
	case 1:
		select_subject();
		timer(Subject[choice - 1]);
		break;

	case 2:
		show_totals();
		system("cls");
		menu();
		break;

	case 3:
		exit(0);
		break;

	default:
		std::cout << "Invalid input!" << std::endl;
		std::cin.get();
		menu();
		break;
	}

}

void getSubjNames(std::vector<subj>& Subject) {
	std::ifstream read("Subject Names.txt");
	std::string line;
	int lineCount{ 0 };
	subj genericSubj;

	while (std::getline(read, line)) {
		lineCount++;
		Subject.push_back(genericSubj);
	}

	read.close();

	std::ifstream readNames("Subject Names.txt");

	line = " ";

	for (int i = 0; i < Subject.size(); i++) {
		std::getline(readNames, line);
		Subject[i].setName(line);
	}
}

int main() {

	getSubjNames(Subject);

	load_data();

	menu();

	return 0;
}