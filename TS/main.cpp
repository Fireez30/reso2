#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string>
#include <unistd.h>
#include <sys/sem.h>

using namespace std;

/*typedef struct s_sembuf {
    unsigned short sem_num;
    short sem_op;
    short sem_flg;
} sembuf;
*/



int main(){

    union semun{
        int val;
        struct semid_ds *buf;
        unsigned short *array;
        struct seminfo *__buf;
    } arg_ctrl;

    key_t cle;
    int f_id;
    int nbt;
    int nbz;
    cout << "Nombre de traitements : ";
    cin >> nbt;
    cout << "Nombre de zones : ";
    cin >> nbz;

    cle = ftok("docufile",8);
    f_id = semget(cle, nbz + 2, IPC_CREAT|IPC_EXCL|0666);

    if (f_id == -1) {
        f_id = semget(cle, 1, 0666);
        semctl(f_id, 0, IPC_RMID);
       // perror("erreur creation");
    }

    cout << "f_id = " << f_id << endl;

    arg_ctrl.val = nbz;
    if (semctl(f_id, 0, SETVAL, arg_ctrl) == -1)
        cout << "erreur init" << endl;

    arg_ctrl.val = nbt;
    for (int i = 1; i < nbz + 2; ++i)
        if (semctl(f_id, i, SETVAL, arg_ctrl) == -1)
            cout << "erreur init" << endl;


    unsigned short array2[nbz];
    semctl(f_id, 0, GETALL, &array2);
    for (int i (0); i < nbz + 2; ++i)
        cout << "jftrezjlmlm " << i << " lrtezmlmgezop " << array2[i] << endl;

    while (semctl(f_id, nbz + 1, GETVAL, NULL) != 0) {}

    cout << "Tous les traitements se sont terminés !" << endl;

    for (int i (0); i < nbz + 2; i++)
        semctl(f_id, i, IPC_RMID);

    return 0;
}
