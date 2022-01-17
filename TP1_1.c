#include "Enseash.h"

//int main(int argc, char *argv[]){
int main(void){//pour éviter les warnings vu qu'on utilise pas encore argc, argv

	const char welcome[]="Welcome on board ! Le shell Ensea.\nPour quitter, tapez 'exit'.\n"; 
	const char shell[]="enseash % \n";
	write(STDOUT_FILENO,welcome,sizeof(welcome));//STDOUT permet d'afficher un message sur la console sans utiliser printf
	write(STDOUT_FILENO,shell,sizeof(shell));

}
