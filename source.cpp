#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

bool SortNames(string name1, string name2) {
	vector<string> v = { name1, name2 };
	for (size_t i = 0; i < 2; i++) {
		for (size_t j = i + 1; j < 2; j++) {
			if (strcmp(v[i].c_str(), v[j].c_str()) > 0)
			{
				string swap = v[i];
				v[i] = v[j];
				v[j] = swap;
			}
		}
	}
	return (name1 == v[0]);
}

class Group {
public:
	class Record {
	public:
		void SetName(string name) {
			studentName = name;
		}
		string GetName() {
			return studentName;
		}
		void AddExam(string examName, string examDate, string examResult) {
			exams.push_back(examName + '\t' + examDate + '\t' + examResult + '\n');
		}
		void PrintRecord() {
			cout << studentName << endl;
			for (size_t i = 0; i < exams.size(); i++) {
				cout << exams[i];
			}
		}
		void RemoveExam(string examName) {
			for (size_t i = 0; i < exams.size(); i++) {
				for (size_t j = 0; j < examName.length() + 1; j++) {
					if (j == examName.length()) {
						exams.erase(exams.begin() + i);
						break;
					}
					if (exams[i][j] != examName[j]) {
						j = 0;
						break;
					}
				}
			}
		}
	private:
		string studentName;
		vector<string> exams;
	};
	struct Student {
		Record studentRecord;
		Student* prev;
		Student* next;
	};
	Group(string name) {
		groupName = name;
		studentsCount = 0;
	}
	void SetGroupName(string name) {
		groupName = name;
	}
	void AddStudent(string name) {
		if (studentsCount == 0) {
			head = new Student;
			head->studentRecord.SetName(name);
			head->prev = nullptr;
			head->next = nullptr;
			studentsCount++;
		}
		else {
			auto tmp = head;
			string name1 = tmp->studentRecord.GetName();
			auto newStudent = new Student;
			newStudent->studentRecord.SetName(name);
			while (SortNames(name1, name) && tmp->next != nullptr) {
				tmp = tmp->next;
				name1 = tmp->studentRecord.GetName();
			}
			if (tmp->next == nullptr && SortNames(name1, name)) {
				tmp->next = newStudent;
				newStudent->prev = tmp;
				newStudent->next = nullptr;
			}
			else if (!SortNames(name1, name) && tmp->next == nullptr) {
				auto tmpNext = tmp;
				head = newStudent;
				head->prev = nullptr;
				head->next = tmpNext;
				tmpNext->prev = head;
			}
			else {
				auto prevTmp = tmp->prev;
				newStudent->next = tmp;
				newStudent->prev = prevTmp;
				prevTmp->next = newStudent;
				tmp->prev = newStudent;
			}
			studentsCount++;
		}
	}
	void FindStudent(string name) {
		if (studentsCount == 0) {
			cout << "Что бы найти студента, сначала нужно добавить студента" << endl;
		}
		else {
			auto tmp = head;
			size_t count = 0;
			while (tmp->studentRecord.GetName() != name && count <= studentsCount) {
				tmp = tmp->next;
				count++;
			}
			if (count > studentsCount) {
				cout << "Такого студента нет" << endl;
			}
			else {
				cout << "Студент " << name << " в списке под номером " << (count + 1) << endl;
			}
		}
	}
	void AddStudentExam(string name, string examName, string examDate, string examResult) {
		auto tmp = head;
		while (tmp->studentRecord.GetName() != name) {
			tmp = tmp->next;
		}
		tmp->studentRecord.AddExam(examName, examDate, examResult);
	}
	void RemoveStudentExam(string name, string examName) {
		auto tmp = head;
		while (tmp->studentRecord.GetName() != name) {
			tmp = tmp->next;
		}
		tmp->studentRecord.RemoveExam(examName);
	}
	void RemoveStudent(string name) {
		auto tmp = head;
		if (studentsCount == 1) {
			delete head;
			studentsCount = 0;
			return;
		}
		if (head->studentRecord.GetName() == name) {
			tmp = head->next;
			delete head;
			head = tmp;
			studentsCount--;
			return;
		}
		while (tmp->studentRecord.GetName() != name) {
			tmp = tmp->next;
		}
		auto tmpPrev = tmp->prev;
		if (tmp->next == nullptr) {
			tmpPrev->next = nullptr;
			delete tmp;
			studentsCount--;
		}
		else {
			auto tmpNext = tmp->next;
			tmpPrev->next = tmpNext;
			tmpNext->prev = tmpPrev;
			delete tmp;
			studentsCount--;
		}
	}
	void PrintStudentRecord(string name) {
		auto tmp = head;
		while (tmp->studentRecord.GetName() != name) {
			tmp = tmp->next;
		}
		tmp->studentRecord.PrintRecord();
	}
	void PrintGroupRecord() {
		auto tmp = head;
		while (tmp->next != nullptr) {
			tmp->studentRecord.PrintRecord();
			tmp = tmp->next;
		}
		tmp->studentRecord.PrintRecord();
	}
	~Group() {
		groupName.clear();
		auto tmp = head;
		while (tmp->next != nullptr) {
			auto tmp1 = tmp;
			tmp = tmp->next;
			RemoveStudent(tmp1->studentRecord.GetName());
		}
		RemoveStudent(tmp->studentRecord.GetName());
	}
private:
	Student* head;
	string groupName;
	size_t studentsCount;
};

int main() {
	setlocale(0, "");
	Group mh("МХ-101");
	//mh.SetGroupName("МХ-101");
	mh.AddStudent("Кутас Сергей Витальевич");
	cout << "Поиск студента" << endl;
	mh.FindStudent("Кутас Сергей Витальевич");
	mh.AddStudentExam("Кутас Сергей Витальевич", "Математический анализ", "14.01.2020", "неуд.");
	mh.AddStudentExam("Кутас Сергей Витальевич", "Алгебра и геометрия", "21.01.2020", "хор.");
	cout << endl << endl << "Зачетка Сергея" << endl;
	mh.PrintStudentRecord("Кутас Сергей Витальевич");
	mh.AddStudent("Кондратьева Анастасия Григорьевна");
	mh.FindStudent("Кондратьева Анастасия Григорьевна");
	mh.AddStudentExam("Кондратьева Анастасия Григорьевна", "Математический анализ", "14.01.2020", "неуд.");
	mh.RemoveStudentExam("Кутас Сергей Витальевич", "Алгебра и геометрия");
	cout << endl << endl << "Зачетка Анастасии" << endl;
	mh.PrintStudentRecord("Кондратьева Анастасия Григорьевна");
	cout << endl << endl << "Зачетка группы после удаления экзамена у Сергея" << endl;
	mh.PrintGroupRecord();
	mh.RemoveStudent("Кутас Сергей Витальевич");
	cout << endl << endl << "Зачетка группы после удаления Cергея" << endl;
	mh.PrintGroupRecord();
}
