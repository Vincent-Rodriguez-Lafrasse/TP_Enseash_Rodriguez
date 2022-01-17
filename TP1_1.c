#include "Enseash.h"

int main(int argc, char *argv[]){

const char welcome[]="Welcome on board ! Le shell Ensea.\nPour quitter, tapez 'exit'.\n"; 
const char shell[]="enseash % ";
write(STDOUT_FILENO,welcome,sizeof(welcome));//STDOUT permet d'afficher un message sur la console sans utiliser printf
write(STDOUT_FILENO,shell,sizeof(shell));

}
