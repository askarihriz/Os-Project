#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<iostream>
#include<string>

using namespace std;

#define MAXSIZE 27
int choice;
char* s;

class Student {
private:
public:

	void Menu() {
		system("clear");
		cout << "LIBRARY SYSTEM" << endl;
		cout << "==============\n" << endl;
		cout << "0. MainMenu" << endl;
		cout << "1. Check Library" << endl;
		cout << "2. Deposit a Book" << endl;
		cout << "3. Withdraw a Book" << endl;
		cout << "4. Exit\n" << endl;

		cout << "Your Choice? (press the number you want)" << endl;
		cin >> choice;
		cin.ignore();
		while(choice<0 || choice>4) {
			cout << "Invalid Choice.... try again!" << endl;
			cin >> choice;
			cin.ignore();
		}
	}

	void Info() {
		system("clear");
		cout << "INFORMATION" << endl;
		cout << "===========" << endl;
		cout << endl;
		int n = s[0];
		cout << "Num of Books = " << n << "\n" << endl;
		cout << "Available Books" << endl;
		cout << "---------------" << endl;
		for(int i=100 ; i<600 ; i++) {			
			if(i%100 == 0)
				cout << endl;
	
			cout << s[i];
		}
		cout << endl << endl;
		cout << "1. Back to Menu" << endl;
		cout << "2. Exit" << endl;
		cout << "Your Choice? (press the number you want)" << endl;
		int ch;
		cin >> ch;
		cin.ignore();
		while(ch<1 || ch>2) {
			cout << "Invalid Choice.... try again!" << endl;
			cin >> ch;
			cin.ignore();
		}
		if(ch == 1)
			choice = 0;
		else if(ch == 2)
			choice = 4;
	}

	void DepositBook() {
		if(s[0] == 5) {
			cout << "Library is full ..." << endl;
			sleep(1);
			choice = 0;
			return;
		}
		system("clear");
		cout << "\nEnter a Book: ";
		string name;
		getline(cin,name);
		int k = (s[0]*100)+100;
		for(int i=0 ; i<name.length() ; i++) {
			s[k++] = name[i];
		}
		s[0] = s[0]+1;
		cout << endl;
		cout << "1. Deposit More" << endl;
		cout << "2. Back To Menu" << endl;
		cout << "Your Choice? (press the number you want)" << endl;
		int ch;
		cin >> ch;
		cin.ignore();
		while(ch<1 || ch>2) {
			cout << "Invalid Choice.... try again!" << endl;
			cin >> ch;
			cin.ignore();
		}
		if(ch == 1)
			choice = 2;
		else if(ch == 2)
			choice = 0;
	}
	
	void Display() {
		system("clear");
		cout << "INFORMATION" << endl;
		cout << "===========" << endl;
		int n = s[0];
		cout << "Num of Books = " << n << "\n" << endl;
		cout << "Available Books" << endl;
		cout << "---------------" << endl;
		for(int i=100 ; i<600 ; i++) {			
			if(i%100 == 0)
				cout << endl;
	
			cout << s[i];
		}
		cout << endl << endl;
	}

	void WithdrawBook() {
		if(s[0] == 0) {
			cout << "No Books to be Withdrawn ..." << endl;
			sleep(1);
			choice = 0;
			return;
		}
		Display();
		cout << "\nEnter the name of the Book to be Withdrew: ";
		string name;
		getline(cin,name);
		int flag = 0;
		for(int i=100 ; i<600-name.length() ; i++) {
			flag = 0;
			for(int j=0 ; j<name.length() ; j++) {
				if(s[i+j] == name[j]) {
					continue;				
				}
				flag = 1;
			}
			if(flag == 0) {
				if(i<200) {
					for(int i=100 ; i<200 ; i++) {
						s[i] = ' ';
					}
					for(int i=200 ; i<700 ; i++) {
						char m = s[i];
						s[i-100] = m;
					}		
				}
				else if(i<300) {
					for(int i=200 ; i<300 ; i++) {
						s[i] = ' ';
					}
					for(int i=300 ; i<700 ; i++) {
						char m = s[i];
						s[i-100] = m;
					}		
				}
				else if(i<400) {
					for(int i=300 ; i<400 ; i++) {
						s[i] = ' ';
					}
					for(int i=400 ; i<700 ; i++) {
						char m = s[i];
						s[i-100] = m;
					}		
				}
				else if(i<500) {
					for(int i=400 ; i<500 ; i++) {
						s[i] = ' ';
					}
					for(int i=500 ; i<700 ; i++) {
						char m = s[i];
						s[i-100] = m;
					}		
				}
				else if(i<600) {
					for(int i=500 ; i<600 ; i++) {
						s[i] = ' ';
					}		
				}
				s[0] = s[0] - 1;
				Display();
				break;
			}
		}
		if(flag == 0) {
			cout << "Book withdrawn successfully!" << endl;
			cout << endl;
			cout << "1. Withdraw More" << endl;
			cout << "2. Back To Menu" << endl;
			cout << "Your Choice? (press the number you want)" << endl;
			int ch;
			cin >> ch;
			cin.ignore();
			while(ch<1 || ch>2) {
				cout << "Invalid Choice.... try again!" << endl;
				cin >> ch;
				cin.ignore();
			}
			if(ch == 1)
				choice = 3;
			else if(ch == 2)
				choice = 0;
		}
		else {
			cout << "Could not find that Book ... try again!" << endl;
			cout << endl;
			cout << "1. Withdraw More" << endl;
			cout << "2. Back To Menu" << endl;
			cout << "Your Choice? (press the number you want)" << endl;
			int ch;
			cin >> ch;
			cin.ignore();
			while(ch<1 || ch>2) {
				cout << "Invalid Choice.... try again!" << endl;
				cin >> ch;
				cin.ignore();
			}
			if(ch == 1)
				choice = 3;
			else if(ch == 2)
				choice = 0;
		}
	}
};

void die(const char *str) {
	perror(str);
	exit(1);
}



int main(void) {
	Student S;
	int shmid;
	key_t key;
	char *shm;

	key = 2211;
	fflush(stdin);
	if((shmid = shmget(key, MAXSIZE, IPC_CREAT | 0666)) < 0)
		die("shmget");
	if((shm = (char*) shmat(shmid, NULL, 0)) == (char*)-1)
		die("shmat");
	s=shm;
	s[0] = 1;
	choice = 0;

	while(1)
	{
		switch(choice)
		{
			case 0:
				S.Menu();
				break;
			case 1:
				S.Info();
				break;
			case 2:
				S.DepositBook();
				break;
			case 3:
				S.WithdrawBook();
				break;
			case 4:
				system("clear");
				s[1500] = '*';
				sleep(1);
				cout << "Exited" << endl;
				s[1500] = '^';
				exit(1);
				break;
			default:
				break;
		}
	}

}

