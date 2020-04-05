#include <iostream>
#include <string>
using namespace std;

struct Node {
	string predmet;
	string prepodovatel;
	string ocenka;
	Node* next;
};

void print(Node *zachetka) {
	cout << zachetka->predmet << " " << zachetka->prepodovatel << " " << zachetka->ocenka << endl;
	if (zachetka->next != NULL) {
		print(zachetka->next);
	}
	return;
}

int main() {
	setlocale(0, "");
	Node* zachetka1str, * zachetka2str,* zachetka3str;
	zachetka1str = new Node;
	zachetka2str = new Node;
	zachetka3str = new Node;
	zachetka1str->predmet = "Основы программирования";
	zachetka1str->prepodovatel = "Осипов Сергей Иванович        ";
	zachetka1str->ocenka = "4(хор.)";
	zachetka1str->next = zachetka2str;
	zachetka2str->predmet = "Математический анализ  ";
	zachetka2str->prepodovatel = "Антонов Николай Юрьевич       ";
	zachetka2str->ocenka = "4(хор.)";
	zachetka2str->next = zachetka3str;
	zachetka3str->predmet = "Алгебра и геометрия    ";
	zachetka3str->prepodovatel = "Овсянников Александр Яковлевич";
	zachetka3str->ocenka = "4(хор.)";
	zachetka3str->next = NULL;
	cout << "Зачетная книжка студента УрФУ Кутас Сергея" << endl;
	cout << "1 семестр" << endl << "Предмет                 " << "Преподаватель                  " << "Оценка      " << endl;
	print(zachetka1str);

}
