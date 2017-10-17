#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string>

using namespace std;

int main(){

	key_t cle;

	cle = ftok("docufile",3);

	while (true){

	}

	return 0;
}