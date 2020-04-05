#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Group {	
public:
	class Student {
	public:
		string student_name;
		void set_name(string name) {
			student_name = name;
		}
		void add_exam(string exam_name, string exam_date, string exam_result){
			exams.push_back(exam_name + '\t' + exam_date + '\t' + exam_result + '\n');
		}
		void print_zachetka() {
			cout << student_name + '\n';
			for (size_t i = 0; i < exams.size(); i++) {
				cout << exams[i];
			}
		}
		void remove_exam(string name) {
			for (size_t i = 0; i < exams.size(); i++) {
				for (size_t j = 0; j < name.length() + 1; j++) {
					if (j == name.length()) {
						exams.erase(exams.begin() + i);
						break;
					}
					if (exams[i][j] != name[j]) {
						j = 0;
						break;
					}
				}
			}
		}
	private:
		vector<string> exams;
	};
	void set_group_name(string name) {
		group_name = name;
	}
	void print_group_name() {
		cout << group_name;
	}
	void add_student(string name) {
		Student tmp;
		tmp.set_name(name);
		students.push_back(tmp);
	}
	void find_student(string name) {
		for (size_t i = 0; i < students.size(); i++) {
			if (students[i].student_name == name) {
				cout << "Студент " << name << " имеет номер " << i + 1 << endl;
			}
		}
	}
	void add_student_exam(size_t num, string exam_name, string exam_date, string exam_result) {
		students[num - 1].add_exam(exam_name, exam_date, exam_result);
	}
	void remove_student_exam(size_t num, string name) {
		students[num - 1].remove_exam(name);
	}
	void remove_student(size_t num) {
		students.erase(students.begin() + (num - 1));
	}
	void print_student_zachetka(size_t num) {
		cout << num << "." << " ";
		students[num - 1].print_zachetka();
	}
	void print_group_zachetka() {
		for (size_t i = 0; i < students.size(); i++) {
			cout << i + 1 << "." << " ";
			students[i].print_zachetka();
		}
	}
private:
	string group_name;
	vector<Student> students;
};

int main() {
	setlocale(0, "");
	Group mh;
	mh.set_group_name("МХ-101");
	mh.add_student("Кутас Сергей Витальевич");
	cout << "Поиск студента" << endl;
	mh.find_student("Кутас Сергей Витальевич");
	mh.add_student_exam(1, "Математический анализ", "14.01.2020", "неуд.");
	mh.add_student_exam(1, "Алгебра и геометрия", "21.01.2020", "хор.");
	mh.add_student("Кондратьева Анастасия Григорьевна");
	mh.find_student("Кондратьева Анастасия Григорьевна");
	mh.add_student_exam(2, "Математический анализ", "14.01.2020", "неуд.");
	mh.remove_student_exam(1, "Алгебра и геометрия");
	cout << endl << endl << "Зачетка Анастасии" << endl;
	mh.print_student_zachetka(2);
	cout << endl << endl << "Зачетка группы" << endl;
	mh.print_group_zachetka();
	mh.remove_student(1);
	cout << endl << endl << "Зачетка группы после удаления Cергея" << endl;
	mh.print_group_zachetka();
}
