#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string>
#include <ctime>
#include <unistd.h>
#include <sys/sem.h>

using namespace std;

int main(){

    int numTraitement = 0;

    key_t cle;
    int f_id;
    int nbt;
    int nbz;


    struct sembuf opv;

    srand(time(NULL));

    cle = ftok("docufile", 8);
    f_id = semget(cle, 1, 0666);

    nbz = semctl(f_id, 0, GETVAL, NULL);
    nbt = semctl(f_id, 1, GETVAL, NULL);

    if (f_id == -1){
        //perror("erreur create");
    }

    cout << "id du tableau de semaphores : " << f_id << endl;

    opv.sem_op = -1;
    opv.sem_flg = 0;

    for (int i (2); i < nbz + 2; ++i) {

        if (semctl(f_id, i, GETVAL, NULL) != nbt - numTraitement){
            cout << "en attente du traitement précédent" << endl;
            sleep(1);
            i--;
            continue;
        }

        opv.sem_num = i;
        sleep (5);
        semop(f_id, &opv, 1);
        cout << "traitement sur zone " << i - 2 << " terminé" << endl;
    }

    return 0;
}
