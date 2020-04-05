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
		friend ostream& operator<< (ostream& out, Group::Record& record) {
			out << record.GetName() << "\n";
			for (size_t i = 0; i < record.exams.size(); i++) {
				out << record.exams[i] << "\n";
			}
			return out;
		}
		friend istream& operator>>(istream& in, Group::Record& record) {

			getline(in, record.studentName);
			return in;
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
    cout << endl;
	}
	friend Group operator+ (Group& grp, Group::Record& rec) {
		if (grp.studentsCount == 0) {
			grp.head = new Student;
			grp.head->studentRecord = rec;
			grp.head->prev = nullptr;
			grp.head->next = nullptr;
			grp.studentsCount++;
		}
		else {
			auto tmp = grp.head;
			string name1 = tmp->studentRecord.GetName();
			auto newStudent = new Student;
			newStudent->studentRecord = rec;
			string name = rec.GetName();
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
				grp.head = newStudent;
				grp.head->prev = nullptr;
				grp.head->next = tmpNext;
				tmpNext->prev = grp.head;
			}
			else {
				auto prevTmp = tmp->prev;
				newStudent->next = tmp;
				newStudent->prev = prevTmp;
				prevTmp->next = newStudent;
				tmp->prev = newStudent;
			}
			grp.studentsCount++;
		}
		return grp;
	}
	friend Group operator- (Group& grp, Group::Record& rec) {
		string name = rec.GetName();
		grp.RemoveStudent(name);
		return grp;
	}
private:
	Student* head;
	string groupName;
	size_t studentsCount;
};

int main() {
	setlocale(0, "");
	Group mh("МХ-101");
	Group::Record record;
//cin >> record;
  record.SetName("Речкалов Андрей Юрьевич");
	record.AddExam("Математический анализ", "15.01.2020", "удовл.");
	cout << record;
	Group::Record record1;
	record1.SetName("Чиликин Клим Евгеньевич");
	record1.AddExam("Математический анализ", "15.01.2020", "неуд.");
	mh = mh + record;
	mh = mh + record1;
	mh.PrintGroupRecord();
	mh = mh - record1;
	mh.PrintGroupRecord();

}
