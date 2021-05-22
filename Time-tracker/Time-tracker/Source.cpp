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

//function prototypes
void menu();
void save_data();
std::wstring StringToWString(const std::string& s);

//structs
struct subj {
	std::string name;
	double total_time{ 0 };
};

struct Timer {
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<double> duration;
	subj* genericSubject;

	Timer(subj& Subj)
		:start(std::chrono::steady_clock::now()), genericSubject(&Subj), duration(0)
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

//Globals
int musicFreq = 1;
bool cntnue = true;
bool toggleMusic = true;
std::vector<subj> Subject;
std::string savefile, audiofile, piechartfile, barchartfile;
const char* configfile = "Config.txt";


// a bunch of functions
void bell_sound() { // fix this
	if (toggleMusic) {
		PlaySound(StringToWString(audiofile).c_str(), NULL, SND_ASYNC);
	}
}

void timer(subj& subject) {
	system("cls");
	cntnue = true;
	Timer timeSubj(subject);
	int block = 0;

	std::cout << Colours::colourString("[underline]" + subject.name + ":[reset] ") << std::endl;
	std::cout << "Time Elapsed: ";

	std::thread secThread([&block]() {

		while (cntnue) {
			std::this_thread::sleep_for(std::chrono::seconds(5)); // much better than sleep()
			if (cntnue) {
				std::cout << Colours::colourString("[cyan]") << char(219) << Colours::colourString("[reset] ");

				block++;

				if (musicFreq > 0) {
					if (block % (12 / musicFreq) == 0) {
						std::cout << " ";
						bell_sound();
					}
				}
			}
			else {
				return;
			}
		}
		
		});
	secThread.detach();
	
	//_getch(); needed conio.h
	auto a = getchar(); //included in iostream
	auto b = getchar();
	cntnue = false;
}

int select_subject() {
	system("cls");
	int choice = 0;
	std::cout << "Select Subject:" << std::endl;
	for (size_t i = 0; i < Subject.size(); i++) {
		std::cout << i + 1 << ". " << Subject[i].name << "," << std::endl;
	}
	std::cout << ">";
	std::cin >> choice;
	return choice - 1;
}

std::wstring StringToWString(const std::string& s){
	std::wstring ws(s.begin(), s.end());

	return ws;
}

void show_totals() {
	system("cls");
	int chart = 0;
	std::cout << Colours::colourString("[underline]Totals per subject:[reset] ") << std::endl << std::endl;

	for (size_t i = 0; i < Subject.size(); i++) {
		std::cout << Subject[i].name << "(" << Subject[i].total_time / 60 << " hrs)" << std::endl;

		for (int counter = 0; counter < int(Subject[i].total_time / 60); counter++) {//each block is an hour 
			std::cout << Colours::colourString("[cyan]") << char(219) << Colours::colourString("[reset] ");
		}
		std::cout << std::endl << std::endl;
	}

	std::cout << "Charts: \n1.Bar Graph,\n2.Pie Chart,\n3.Neither.\n>";
	std::cin >> chart;
	
	if (chart == 1) {
		ShellExecute(NULL, L"open", StringToWString(barchartfile).c_str(),
			NULL, NULL, SW_RESTORE);
	}
	else if (chart == 2) {
		ShellExecute(NULL, L"open", StringToWString(piechartfile).c_str(),
			NULL, NULL, SW_RESTORE);
	}
}

void menu() {
	while (true) {
		int optn = 0;

		system("cls");

		std::cout << Colours::colourString("[underline]Time Tracker[reset]") << std::endl;
		std::cout << "1.New Session," << std::endl;
		std::cout << "2.Show Totals," << std::endl;
		std::cout << "3.Edit Subjects," << std::endl;
		std::cout << "4.Change Settings," << std::endl;
		std::cout << "5.Exit." << std::endl;
		std::cout << ">";
		std::cin >> optn;

		switch (optn)
		{
		case 1:
			timer(Subject[select_subject()]);
			break;

		case 2:
			show_totals();
			break;

		case 3:
			ShellExecute(NULL, L"open", StringToWString(savefile).c_str(), NULL, NULL, SW_RESTORE);
			break;

		case 4:
			ShellExecute(NULL, L"open", StringToWString(configfile).c_str(), NULL, NULL, SW_RESTORE);
			break;

		case 5:
			//exit(0);
			return;

		default:
			std::cout << "Invalid input!" << std::endl;
			std::cin.get();
			break;
		}
	}

}

void loadSaves(std::vector<subj>& Subject) {
	std::ifstream read(savefile.c_str());
	std::string line;
	subj genericSubj;

	while (std::getline(read, line)) {
		//std::cout << line << std::endl;
		genericSubj.name = line.substr(0, line.find(": "));

		try { genericSubj.total_time = std::stod(line.substr(line.find(": ") + 2, line.length())); }
		catch (...) { genericSubj.total_time = 0.0f; }

		Subject.push_back(genericSubj);
	}

	read.close();
}

void loadSettings() {
	std::ifstream rd(configfile);
	std::string line;

	if (rd.is_open()) {
		
		while (std::getline(rd, line)) {
			if (line.find("Save File: ") != std::string::npos) {
				savefile = std::string(line.substr(line.find(": ") + 2, line.length()));
			}
			if (line.find("Audio File: ") != std::string::npos) {
				audiofile = line.substr(line.find(": ") + 2, line.length());
			}
			if (line.find("Toggle Music: ") != std::string::npos) {
				if (line.find("On") != std::string::npos || line.find("on") != std::string::npos) {
					toggleMusic = true;
				}
				else {
					toggleMusic = false;
				}
			}
			if (line.find("Music Freq: ") != std::string::npos) {
				try { musicFreq = std::stoi(line.substr(line.find(": ") + 2, line.length())); }
				catch (...) { musicFreq = 1; }
			}
			if (line.find("Pie Chart File: ") != std::string::npos) {
				piechartfile = line.substr(line.find(": ") + 2, line.length());
			}
			if (line.find("Bar Chart File: ") != std::string::npos) {
				barchartfile = line.substr(line.find(": ") + 2, line.length());
			}
		}
		
		rd.close();
	}
}

void save_data() {//saves time totals for each subject
	std::ofstream write(savefile.c_str());
	if (write.is_open()) {
		for (size_t i = 0; i < Subject.size(); i++) {
			write << Subject[i].name << ": " << Subject[i].total_time << std::endl;
		}
	}

	write.close();
}

int main() {
	loadSettings();

	loadSaves(Subject);

	menu();

	return 0;
}
