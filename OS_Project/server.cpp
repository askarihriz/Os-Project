#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<unistd.h>
#include<string>

using namespace std;

#define MAXSIZE 27

class Library {

private:
	int numOfBooks;
	string bookName;
public:
	Library(int num, string name) {
		numOfBooks = num;
		bookName = name;
	}

	int getNumOfBooks() {
		return numOfBooks;	
	}

	string getBookName() {
		return bookName;
	}

	void setNumOfBooks(int number) {
		numOfBooks = number;	
	}

	void setNameOfBooks(string name) {
		bookName = name;	
	}

};

void die(const char *str) {
	perror(str);
	exit(1);
}

int main(void) {
	Library L(25,"The Good Book");
	int shmid;
	key_t key;
	char *shm, *s;

	key = 2211;
	
	if((shmid = shmget(key, MAXSIZE, IPC_CREAT | 0666)) < 0)
		die("shmget");
	if((shm = (char*) shmat(shmid, NULL, 0)) == (char*) -1)
		die("shmat");
	s = shm;

	*s++ = L.getNumOfBooks();
	string temp = L.getBookName();
	*s++ = temp.length();
	for(int i=0 ; i<temp.length() ; i++){
		*s++ = temp[i];
	}
	
	while(*s != '!')
		sleep(1);

	exit(0);
}
