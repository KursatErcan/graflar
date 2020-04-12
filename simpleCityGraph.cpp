#include<iostream>
#include<stdlib.h>
#include<string.h>

#define notVisited 1

using namespace std;

struct node {
	char label[15];
	int counter;
	int state;
	struct node* neighbors[100]; //matris yapılabilir
	struct node* next;
};
struct node* start = NULL;
struct node* last = NULL;
struct node* temp;
struct node* important;
bool  myStrCmp(char* a, char* b){	//ayı ise true farklı ise false döndürür
	bool result = true;
	for (int i = 0; a[i] != '\0' && b[i] != '\0'; i++) {
		if (a[i] != b[i]) {
			result = false;
			break;
		}
	}
	return result ;
}
void myStrCopy(char* a, char* b) {
	for (int i = 0; b[i] != '\0'; i++) a[i] = b[i];
}
void addCity(char city[15]) {
	struct node* current = (struct node*)malloc(sizeof(struct node));
	myStrCopy(current->label , city);
	current->counter = 0;
	current->state = notVisited;
	current->next = NULL;
	if (start == NULL) {
		start = current;
		last = current;
	}
	else {
		last->next = current;
		last = current;
	}
}
void printCitys() {
	temp = start;
	while (temp->next != NULL) {
		cout << temp->label;
		temp = temp->next;
	}
	cout << temp->label;
}
void getCity(char l[15]) {
	temp = start;
	while (!myStrCmp(temp->label, l)) {
		temp = temp->next;
	}
	important = temp; 
}
void addNeighbors(char src[15], char dest[15]) {
	struct node* source;
	getCity(src);
	source = important;
	struct node* destination;
	getCity(dest);
	destination = important;
	source->neighbors[source->counter] = destination;
	source->counter++;
	destination->neighbors[destination->counter] = source;//yönsüz graf olur
	destination->counter++;
}
void printNeighbors(char city[15]) {
	getCity(city);
	for (int i = 0; i < important->counter; i++) {
		cout << important->neighbors[i]->label<<" ";
	}
}
int main() {
	bool b = true;
	int choose;
	char cityTag[15];
	char cityTag1[15];
	while (b) {
		cout << "1.Sehir Ekle..." << endl;
		cout << "2.Sehir Yazdir..." << endl;
		cout << "3.Komsu Ekle..." << endl;
		cout << "4.Komsu Yazdir..." << endl;
		cout << "0.EXIT..." << endl;

		cout << "Seciminiz : " ;
		cin >> choose;
		switch (choose) {
			case 1:
				cout << endl << "Eklenilece Sehrin Etiketini Giriniz : " ;
				cin >> cityTag;
				addCity(cityTag);
				break;
			case 2:
				printCitys();
				break;
			case 3:
				cout << endl << "Komsu Eklenilecek Sehrin Etiketini Giriniz : " ;
				cin >> cityTag;
				cout << endl << "Kac Komsu Eklenilecek? : ";
				cin >> choose;
				printCitys();
				for (int i = 0; i < choose; i++) {
					cout <<endl << i + 1 << ". Komsuyu giriniz : ";
					cin>> cityTag1;
					addNeighbors(cityTag, cityTag1);
				}
				break;
			case 4:
				cout <<endl << "Sehri Etiketini Giriniz : " ;
				cin >> cityTag;
				printNeighbors(cityTag);
				break;
			case 0:
				b = false;
		}

	}
	return 0;
}

