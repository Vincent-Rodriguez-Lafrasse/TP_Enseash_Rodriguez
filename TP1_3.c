#include "Enseash.h"
#define CMD_SIZE 100

int main(int argc, char *argv[])
	{
	const char welcome_msg[]="Welcome on board ! Le shell Ensea.\nPour quitter, tapez 'exit'.\n"; 
	const char prompt[]="enseash % ";
	const char exit_msg[]="A bientot !\n";


	write(STDOUT_FILENO,welcome_msg,sizeof(welcome_msg));//STDOUT permet d'afficher un message sur la console sans utiliser printf
	write(STDOUT_FILENO,prompt,sizeof(prompt));

	char cmd[CMD_SIZE];
	int pid,status;
	int cmd_lenght;
	int size;

	while (1){

		size=read(STDIN_FILENO,cmd,CMD_SIZE); //size permet de connaitre la longueure de la commande lue
		cmd_lenght=strlen(cmd);
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
		if (strncmp("exit",cmd, strlen("exit"))==0)//on ferme si on tape exit
			{
			write(STDOUT_FILENO,exit_msg,sizeof(exit_msg)); 
			exit(EXIT_SUCCESS);
			}	
		if (size==0) //fermeture si ctrl+D, car ça renvoie un End of transmission, donc on ne lira rien, d'ou size=0
			{
			write(STDOUT_FILENO,exit_msg,sizeof(exit_msg)); //on aurait pu le combiner avec le if du dessus mais moins claire pour les commentaires
			exit(EXIT_SUCCESS);
			}			
		write(STDOUT_FILENO,prompt,sizeof(prompt));
	}


}


