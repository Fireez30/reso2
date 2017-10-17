#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

using namespace std;

typedef struct s_msgbuff {
	long etiquette;//etiquette du message
	char m[7];//message sous la forme : operateur operande1 operande2
} msgbuff;

int main(){

	key_t cle;
	int f_id;
	long etiquette;
	msgbuff r;

	cle = ftok("docufile",2);
	f_id = msgget(cle,IPC_CREAT|0666);

	for (int i=0;i<7;i++){
		r.m[i]= '0';
	}
	int nblus =7; 
	//msgrcv(f_id,&r,11,5,0);
	if (nblus == -1) {cout << "Erreur lors de la lecture ! " << endl;return -1;}
	cout << "id de la file : " << f_id << " de clé : " << cle << endl;

	cout << " message : " << endl;
	for (int i=0;i<nblus;i++){cout << &r.m[i];}
	cout << endl;
	return 0;
}