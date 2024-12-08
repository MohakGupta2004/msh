#include <stdio.h>
#include <string.h>
#include<stdbool.h>
int main(int argc, char *argv[]) {
  if(argc == 2){
	char *arg = argv[1];
	if(strncmp(arg, "PATH=", 5)==0){
		char *value = arg+5;
		
	}
  }
  while(true){
	printf("$ ");
  	fflush(stdout);
  	char input[100];
 	fgets(input, 100, stdin);
	input[strlen(input)-1] = '\0';
	int i = strlen(input)-1;
	if(input[i] == '0'){
		break;
	}
	char *token = strtok(input, " ");
	
	char echo[] = "echo";
	char exit[] = "exit";
	char type[] = "type";
	while(token!=NULL){
		if(strcmp(token, exit)==0){
			break;
		}
		else if(strcmp(token, echo)==0){
			token = strtok(NULL, "");
			printf("%s\n", token);
		}
		else if(strcmp(token, type) == 0){
			token = strtok(NULL, " ");
			if(strcmp(token,type)==0){
				printf("%s is a shell builtin\n", token);
			}
			else if(strcmp(token, echo)==0 || strcmp(token, exit)==0){
				printf("%s is a shell builtin\n", token);
			}
			else {
				printf("%s: not found\n",token);
			}
		}
		else {
			printf("%s: not found\n", input);
		}
		token = strtok(NULL, " ");
	}
	
  }

  return 0;
}