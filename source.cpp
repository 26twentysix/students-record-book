#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Zachetka {	
  public:
	  string surname;
	  string firstname;
	  string patronymic;
	  string exam_name[3];
	  string date[3];
	  size_t assessment[3];
};

int main() {
	setlocale(0, "");
	Zachetka my_zachetka;
	const char* zachetka = "zachetka.txt";
	my_zachetka.surname = "Кутас"; my_zachetka.firstname = "Сергей"; my_zachetka.patronymic = "Витальевич";
	my_zachetka.exam_name[0] = "Математический анализ";
	my_zachetka.date[0] = "14.01.2020";
	my_zachetka.assessment[0] = 2;
	my_zachetka.exam_name[1] = "Алгебра";
	my_zachetka.date[1] = "21.01.2020";
	my_zachetka.assessment[1] = 4;
	my_zachetka.exam_name[2] = "Основы программирования";
	my_zachetka.date[2] = "25.01.2020";
	my_zachetka.assessment[2] = 4;
	ofstream file (zachetka, ios::binary);
	file.write((char*)& my_zachetka, sizeof(my_zachetka));
	file.close();
	memset(&my_zachetka, 0, sizeof(Zachetka));
	ifstream read_file(zachetka, ios::binary);
	read_file.read((char*)& my_zachetka, sizeof(my_zachetka));
	read_file.close();
	cout << my_zachetka.surname << ' ' << my_zachetka.firstname << ' ' << my_zachetka.patronymic << '\n';
	for (size_t i = 0; i < 3; i++) {
		cout << my_zachetka.exam_name[i] << ' ' << my_zachetka.date[i] << ' ' << my_zachetka.assessment[i] << '\n';
	}
}
