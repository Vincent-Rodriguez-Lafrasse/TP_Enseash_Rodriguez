#include "Enseash.h"
#define CMD_SIZE 100
#define true 1
#define false 0

//int main(int argc, char *argv[]){
int main(void){//pour éviter les warnings vu qu'on utilise pas encore argc, argv
	
	const char welcome_msg[]="Welcome on board ! Le shell Ensea.\nPour quitter, tapez 'exit'.\n"; 
	const char prompt[]="enseash % ";
	const char exit_msg[]="\nA bientot !\n";


	write(STDOUT_FILENO,welcome_msg,sizeof(welcome_msg));//STDOUT permet d'afficher un message sur la console sans utiliser printf
	write(STDOUT_FILENO,prompt,sizeof(prompt));

	char msgTemps[30];
	char cmd[CMD_SIZE]; //stock la commande écrite
	char stringSTATUS[1]={0}; //stock la valeur de sortie du fils ou le numéro du signal
	int pid,status;
	int cmd_lenght;
	int size;


	struct timespec start, stop; //sert à la mesure du temps avec gettime()
    long temps; //stock la durée d'execution d'une commande

	while (1){

		size=read(STDIN_FILENO,cmd,CMD_SIZE); //size permet de connaitre la longueure de la commande lue
		cmd_lenght=strlen(cmd);
		cmd[cmd_lenght-1]='\0';//On remplace le \n par défaut qui pose problème lors de l'éxécution, on indique alors la fin de la chaine de caractère

		clock_gettime( CLOCK_REALTIME, &start);//on récupère le temps au début de l'execution

		pid=fork();//on crée un processus fils pour ne pas exit du programme après éxécution d'une commande

		if (pid !=0) //Je suis dans le père
			{
			wait(&status);// on attend que tous les processus soient terminés
			clock_gettime( CLOCK_REALTIME, &stop);//on récupère le temps à la fin de l'execution
			temps = ((stop.tv_nsec - start.tv_nsec )/1000000); //permet d'obtenir la durée d'execution en ms
	 		
	 		if(WIFEXITED(status) == true){ //on va determine si le fils s'est termiuné normalement ou à cause d'un signal
	 		stringSTATUS[0] =(WTERMSIG(status)&0xf) +'0';

	 		write(STDOUT_FILENO,"enseash [exit:",sizeof("enseash [exit:"));//on ne peut pas faire %d comme dans printf donc j'ai divisé en trois lignes
	 		write(STDOUT_FILENO,stringSTATUS,1);
	 		sprintf(msgTemps,"|%ldms] %%",temps); //je pensais qu'on avait pas le droit d'utiliser sprintf,d'ou mon usage tardif
		 	write(STDOUT_FILENO,msgTemps,strlen(msgTemps));
		 	}

			if (WIFSIGNALED(status) == true){
			stringSTATUS[0]=(WTERMSIG(status)&0xf) +'0';//Je bloquais, et après demande d'aide, on m'a donné cette formule

			write(STDOUT_FILENO,"enseash [sign:",sizeof("enseash [sign:"));
		 	write(STDOUT_FILENO,stringSTATUS,1);
		 	sprintf(msgTemps,"|%ldms] %%",temps); //je pensais qu'on avait pas le droit d'utiliser sprintf,d'ou mon usage tardif
		 	write(STDOUT_FILENO,msgTemps,strlen(msgTemps));
		 	//write(STDOUT_FILENO,"|",sizeof("|"));
		 	//write(STDOUT_FILENO,temps,1);
	 		//write(STDOUT_FILENO,"ms] % ",sizeof("ms] % "));
			}

			if(WIFEXITED(status) == false && WIFSIGNALED(status) == true ){ //dans les cas ou on a pas lancé de processus
				write(STDOUT_FILENO,prompt,sizeof(prompt)); //on affiche enseash %
			}
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

				
	}


}


//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