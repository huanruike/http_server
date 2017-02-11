#include"deal_path.h"
#include"headfile.h"

void deal_path(char *path){
	int len=strlen(path);
	if(len==1&&path[0]=='/'){
		strcpy(path,"index.html");
		return;
	}
	if(path[len-1]=='/') strcat(path,"index.html");
	if(path[0]=='/'){
		for(int i=0;i<len;i++) path[i]=path[i+1];
	}
	printf("path: %s\n",path);
}
