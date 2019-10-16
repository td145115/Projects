// Trenton Davis
// CS4420
// Homework 1 Part 1

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

//Funtion for reading in a file and tokenizing it while youre at it.
char readfile(char *file)
{
    FILE *fptr;
    char filename[50];
    strcpy(filename, file);
    char ch;
    char str[1000] = "";
 
    // Opens the File itself
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        exit(0);
    }

    // Gets each individual character from the stat file

    ch = fgetc(fptr);
    while (ch != EOF)
    {
    	str[strlen(str)] = ch;
        ch = fgetc(fptr);
    }

    //Tokenizing the string of characters that the stat file had

    char* tok = strtok(str, " ");
    int iter = 0;

    //Getting the correct tokens to display on the screen in the correct order

    while(tok != NULL && iter < 23){

    	// Tokens 0: PID 1: Name 2: State 3: PPID 22: Memory Size

    	if(iter == 0)
    		printf("\t%-12s",tok);
    	else if(iter == 1)
    		printf("%-12s\t\t", tok);
    	else if(iter == 2)
    		printf("%-s\t\t", tok);
    	else if(iter == 3)
    		printf("%-12s\t\t", tok);
    	else if(iter == 22)
    		printf("%-17s\n", tok);
    	iter++;

    	if(iter == 0)
    		tok = strtok(NULL, " ()");
    	else
    		tok = strtok(NULL, " ()");
    }

    fclose(fptr);
}

// Main function is what originally sets everything up and traverses to the correct directory.

int main(){
	system("tabs 6");
	int pid;
	struct dirent *ep;
	struct dirent *de;
	DIR* dr;
	DIR* dp;

	// Printing the header for the chart displayed after tokenization

	printf("\n\tPID\t\tName\t\t\t\tState\t\tPPID\t\t\t\tMemory Size\n");

	// Opening proc directory from original place

	dp = opendir ("/proc");

	if (dp != NULL){
		while (ep = readdir (dp)){
			pid = strtol(ep->d_name, NULL, 10);
			if( ( ep->d_type == DT_DIR ) && ( pid > 0) ){

				// Concatinating the file names to open the desired file.
				
				char tmp[50];
				strcpy(tmp, "/");
				strcat(tmp, ep->d_name);

				char tmp1[50];
				strcpy(tmp1, "/proc");
				strcat(tmp1, tmp);
				strcat(tmp1, "/stat");

				dr = opendir(tmp);
				readfile(tmp1);
				closedir(dr);
			}
		}
		closedir(dp);
	}
	else{
		perror ("Couldn't open the directory");
	}
	printf("\n");
}