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
char choice;
char* s;

void die(const char *str) {
	perror(str);
	exit(1);
}

void Intro(){
	cout << "Do you want information? \n y or n" << endl;
	cin >> choice;
	if(choice == 'y'){
		cout << "Num of Books = " << (int)*s++ << endl;
		int n = *s++;
		cout << "Name of Book = ";
		for(int i=0 ; i<n ; i++){
			cout << *s++;
		}
	}
	choice = '0';
}

int main(void) {
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
	choice = '!';
	
	while(1)
	{
		switch(choice)
		{
			case '!':
				Intro();
				break;
			case '*':
				exit(1);
				break;
			default:
				sleep(1);
		}
	}


	exit(0);
}
