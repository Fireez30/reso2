#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string>

using namespace std;

typedef struct s_msgbuff {
	long etiquette;//etiquette du message
	char mess[10];//message sous la forme : operateur operande1 operande2
} msgbuff;

int main(){


	key_t cle;
	int f_id;
	char init[10];
	msgbuff request;

	cout << "Message a envoyer : " << endl;
	for (unsigned i = 0; i < 10 ; i++) init[i]='\0';

	scanf("%s",init);
	//cout << "PAF " << endl;
	for (unsigned i = 0; i < 10 ; i++) request.mess[i] = init[i];
	request.etiquette=1;
	//for (unsigned i = 0; i < 10 ; i++) cout << request.mess[i] ;
	
	//cout << " PAF2 " << endl;

	cle = ftok("docufile",2);

	f_id = msgget(cle,0666);

	cout << "cle : " << cle << " id de la file : " << f_id << endl;

	int result = msgsnd(f_id,&request,sizeof(request.mess),0);
	if (result == -1) {cout << "erreur lors de l'envoi ! " << endl;return -1;}

	return 0;
}