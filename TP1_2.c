#include "Enseash.h"
#define CMD_SIZE 100

//int main(int argc, char *argv[]){
int main(void){//pour éviter les warnings vu qu'on utilise pas encore argc, argv
	
	const char welcome_msg[]="Welcome on board ! Le shell Ensea.\nPour quitter, tapez 'exit'.\n"; 
	const char prompt[]="enseash % ";
	
	write(STDOUT_FILENO,welcome_msg,sizeof(welcome_msg));//STDOUT permet d'afficher un message sur la console sans utiliser printf
	write(STDOUT_FILENO,prompt,sizeof(prompt));

	char cmd[CMD_SIZE];
	int pid,status;

	while (1){

		read(STDIN_FILENO,cmd,CMD_SIZE);
		int cmd_lenght=strlen(cmd);
		cmd[cmd_lenght-1]='\0';//On remplace le \n par défaut qui pose problème lors de l'éxécution, on indique alors la fin de la chaine de caractère

		pid=fork();//on crée un processus fils pour ne pas exit du programme après éxécution d'une commande

		if (pid !=0) //Je suis dans le père
			{
			wait(&status);
			}
		else //Je suis dans le fils
			{
			execlp(cmd,cmd,(char*)NULL) ; //contient un exit quand la commande est exécutée
			exit(EXIT_FAILURE); //On ferme le processus fils si on a mis une commande inconnue
			}

		write(STDOUT_FILENO,prompt,sizeof(prompt));
}



}