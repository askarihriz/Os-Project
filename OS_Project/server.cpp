#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<unistd.h>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

#define MAXSIZE 27
char *s;
ofstream File("Database.txt");

class Library {

private:
	int numOfBooks;
	char bookName[5][100];
public:
	Library(string name) {
		for(int i=0 ; i<5 ; i++) {
			for(int j=0 ; j<100 ; j++) {
				bookName[i][j]	= ' ';		
			}		
		}
		for(int i=0 ; i<name.length() ; i++) {
			bookName[0][i] = name[i];		
		}
		s[0] = 0;
		int k=(100*s[0])+100;
		for(int i=0 ; i<5 ; i++) {
			for(int j=0 ; j<100 ; j++) {
				s[k++] = bookName[i][j];		
			}
		}
		s[0] = s[0] + 1;
		for(int i=600 ; i<1200 ; i++) {
			s[i] = ' ';
		}
	}

	void UpdateMemory() {
		int n = s[0];
		setNumOfBooks(n);
		int k=1;
		for(int i=0 ; i<5 ; i++) {
			for(int j=0 ; j<100 ; j++) {
				bookName[i][j] = s[k++];			
			}
		}
	}

	void setNumOfBooks(int number) {
		numOfBooks = number;	
	}

};

void UpdateDatabase() {
	File << (int)s[0];
	File << "\n";
	for(int i=100 ; i<600 ; i++) {
		if(i%100 == 0) {
			File << "\n";
		}
		File << s[i];
	}
}

void die(const char *str) {
	perror(str);
	exit(1);
}

int main(void) {
	int shmid;
	key_t key;
	char *shm;

	key = 2211;
	
	if((shmid = shmget(key, MAXSIZE, IPC_CREAT | 0666)) < 0)
		die("shmget");
	if((shm = (char*) shmat(shmid, NULL, 0)) == (char*) -1)
		die("shmat");
	s = shm;

	Library L("The not very Good Book");
	
	
	while(s[1500]!='*'){
		L.UpdateMemory();
	}

	UpdateDatabase();
	File.close();

}
