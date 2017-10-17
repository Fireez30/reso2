#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

using namespace std;

typedef struct s_msgbuff {
	long etiquette;//etiquette du message
	char mess[10];//message sous la forme : operateur operande1 operande2
} msgbuff;


int calcul(char op,int op1,int op2){
	switch(op) {
		case '*': 
		return op1*op2;
		break;

		case '+':
		return op1+op2;
		break;

		case '-':
		return op1-op2;
		break;

		case '/':
		if (op2 != 0) {return op1/op2;} else {cout << "Division by zero ! " << endl;}
		break;
	}
}
int main(){
	
	key_t cle;
	int f_id;
	long etiquette;
	msgbuff request;
	char operateur;
	char * op1;
	char * op2;

	cle = ftok("docufile",2);
	f_id = msgget(cle,IPC_CREAT|0666);

	while(1){
	/*int nblus =7;
	for (unsigned i = 0; i < nblus; i++) request.mess[i]='0';
	*/

	cout << "cle : " << cle << " id de la file : " << f_id << endl;

	int nblus = msgrcv(f_id,&request,sizeof(request.mess),0,0);
	if (nblus == -1) {
		cout << "Erreur lors de la lecture ! " << endl;
		msgctl(f_id,IPC_RMID,NULL);
		return -1;}
	

	cout <<  " message : ";
	for (int i=0;i<nblus;i++){cout << request.mess[i];}
	cout << endl;

	operateur = request.mess[0];
	/*op1[0] = request.mess[1];
	op1[1] = request.mess[2];
	op2[0] = request.mess[3];
	op2[1] = request.mess[4];
	*/

	int j=0;
	while (isdigit(request.mess[j])) {
		cout << "isdigit 1 : " << request.mess[j] << endl;
		op1[j]=request.mess[j];
		j++;
	}
	j++;
	while (isdigit(request.mess[j])) {
		op2[j]=request.mess[j];
		j++;
	}

	int res = calcul(operateur,atoi(op1),atoi(op2));
	cout << " Resultat = " << res << endl;

	
}

	msgctl(f_id,IPC_RMID,NULL);
	return 0;
}