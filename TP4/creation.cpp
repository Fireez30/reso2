#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string>

using namespace std;

typedef struct s_sembuf {
	unsigned short sem_num;
	short sem_op;
	short sem_flg;
} sembuf;

int main(){

	key_t cle;
	sembuf opv;
	int f_id;

	cle = ftok("docufile",3);

	
	f_id = msgget(cle,IPC_CREAT|0666);

	if (semget(cle,1,IPC_CREAT|0666) == -1) {
		cout << "Error lors de la creation des semaphores ! " << endl;
		return -1;
	}

	opv.sem_num=0;
	opv.sem_op=+1;
	opv.sem_flg=SEM_UNDO;

	semop(idSem,&opv,120);

	return 0;
}