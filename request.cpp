#include"headfile.h"
#include"serv_send.h"
#include"request.h"
#include"deal_path.h"

void *request(void *arg){
	int clnt_sock=(*((int*)arg));
//	printf("resquest:\n");
//	printf("clnt_sock: %d\n",clnt_sock);
	// GET /index.html HTTP/1.1
	int len;
	char buf[BUF_SIZE];
	char str[BUF_SIZE];
	str[0]='\0';
	/*
	while((len=read(clnt_sock,buf,BUF_SIZE))!=0){
		if(len==-1){
			printf("len==-1\n");
			// send get index fail to client
			serv_send(400,clnt_sock);
			close(clnt_sock);
			//error_handling("read() error!");
			return NULL;
		}
		buf[len]=0;
		printf("len=%d buf=%s\n",len,buf);
		strcat(str,buf);
	}
	*/
	len=read(clnt_sock,buf,BUF_SIZE);
	if(len==-1){
		serv_send(400,clnt_sock);
		close(clnt_sock);
		error_handling("read() error!");
		return NULL;
	}
	buf[len]=0;
	strcpy(str,buf);
//	printf("msg from clnt:\n");
//	printf("%s\n",str);
	shutdown(clnt_sock,SHUT_RD);
	char path[LEN];
	if(Get(str,path)) serv_send(path,clnt_sock);
	else serv_send(400,clnt_sock);
}

bool Get(char *str,char *path){
	char get[LEN],http[LEN];
	sscanf(str,"%s",get);
//	printf("get=%s_\n",get);//--
	if(strcmp(get,"GET")) return false;
	sscanf(str+3,"%s",path);
	deal_path(path);
//	printf("path=%s_\n",path);//--
	FILE *fp=fopen(path,"rb");
	if(fp==NULL) return 0;
//	printf("fp!=NULL\n");//--
	fclose(fp);
	int httpn=0;
	int j=0;
	int cnt=0;
	int str_len=strlen(str);
	while(1){
		if(cnt==2||j==str_len) break;
		while(j<str_len&&str[j]==' ') j++;
		while(j<str_len&&str[j]!=' ') j++;
		cnt++;
	}
//	printf("cnt=%d\n",cnt);
	if(j==str_len||cnt<2) return 0;
	sscanf(str+j,"%s",http);
//	printf("http=%s_\n",http);
	//if(strcmp(http,"HTTP/1.1")) return 0;
	printf("yes\n");
	return 1;
}

