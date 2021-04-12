#include <iostream>
#include <vector>
#include <windows.h> // allows us to use "PlaySound()"
#include <ShellAPI.h> // shell execute
#include <thread>
#include <fstream>
#include <string>
#include <chrono>
#include "Colours.h"

#pragma comment (lib, "Winmm.lib")

struct subj {
	std::string name;
	double total_time;
};

std::vector<subj> Subject;

void save_data();
void menu();
bool cntnue = true;

struct Timer {
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<double> duration;
	subj* genericSubject;

	Timer(subj& Subj)
		:start(std::chrono::steady_clock::now()), genericSubject(&Subj), duration(0)//member initalizer list
	{
	}

	~Timer() {
		end = std::chrono::steady_clock::now();
		duration = end - start;
		genericSubject->total_time += duration.count() / 60;

		std::cout << "\n\nSession time (in minutes): " << duration.count() / 60 << "\n";
		std::cout << "Total time (in minutes): " << genericSubject->total_time << "\n";
		system("pause");
		save_data();
	}
};


void bell_sound() {
	PlaySound(TEXT("clock-chimes-daniel_simon.wav"), NULL, SND_ASYNC);
}

void timer(subj& subject) {
	system("cls");
	Timer timeSubj(subject);
	int block = 0;

	std::cout << Colours::colourString("[underline]" + subject.name + ":[reset] ") << std::endl;
	std::cout << "Time Elapsed: ";

	std::thread secThread([&block]() {
		while (cntnue) {
			std::this_thread::sleep_for(std::chrono::minutes(5)); // much better than sleep()
			if (cntnue) {
				std::cout << Colours::colourString("[cyan]") << char(219) << Colours::colourString("[reset] ");

				block++;

				if (block % 6 == 0) {
					std::cout << " ";
					bell_sound();
				}
			}
		}
		
		});
	secThread.detach();
	
	//_getch(); needed conio.h
	getchar(); //included in iostream
	getchar();
	cntnue = false;

	timeSubj.~Timer();
	cntnue = true;
	menu();
}

int select_subject() {
	system("cls");
	int choice = 0;
	std::cout << "Select Subject:" << std::endl;
	for (int i = 0; i < Subject.size(); i++) {
		std::cout << i + 1 << ". " << Subject[i].name << "," << std::endl;
	}
	std::cout << ">";
	std::cin >> choice;
	return choice - 1;
}

void show_totals() {
	system("cls");
	std::cout << Colours::colourString("[underline]Totals per subject:[reset] ") << std::endl << std::endl;

	for (int i = 0; i < Subject.size(); i++) {
		std::cout << Subject[i].name << "(" << Subject[i].total_time / 60 << " hrs)" << std::endl;

		for (int counter = 0; counter < int(Subject[i].total_time / 60); counter++) {//each block is an hour 
			std::cout << Colours::colourString("[cyan]") << char(219) << Colours::colourString("[reset] ");
		}
		std::cout << std::endl << std::endl;
	}

	
	ShellExecute(NULL, L"open", L"Time_subj_tracker_graphs.py",
				 NULL, NULL, SW_RESTORE); 

	std::cout << std::endl << std::endl;
	system("pause");
}

void menu() {
	int optn = 0;

	system("cls");

	std::cout << Colours::colourString("[underline]Time Tracker[reset]") << std::endl;
	std::cout << "1.New Session," << std::endl;
	std::cout << "2.Show Totals," << std::endl;
	std::cout << "3.Exit." << std::endl;
	std::cout << ">";
	std::cin >> optn;

	switch (optn)
	{
	case 1:
		timer(Subject[select_subject()]);
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

void loadSaves(std::vector<subj>& Subject) {
	std::ifstream read("Saves.txt");
	std::string line;
	subj genericSubj;

	while (std::getline(read, line)) {
		genericSubj.name = line.substr(0, line.find(": "));

		try { genericSubj.total_time = std::stod(line.substr(line.find(": ") + 1, line.length())); }
		catch (...) { genericSubj.total_time = 0.0f; }

		Subject.push_back(genericSubj);
	}

	read.close();
}

void save_data() {//saves time totals for each subject
	std::ofstream write("Saves.txt");
	if (write.is_open()) {
		for (int i = 0; i < Subject.size(); i++) {
			write << Subject[i].name << ": " << Subject[i].total_time << std::endl;
		}
	}

	write.close();
}

int main() {

	loadSaves(Subject);

	menu();

	return 0;
}
