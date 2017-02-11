#include"headfile.h"
#include"work.h"

int main(int argc,char *argv[]){
	if(argc!=2){
		printf("Usage : %s <port>\n",argv[0]);
		exit(1);
	}
	// create sock ,bind and listen
	int serv_sock=socket(AF_INET,SOCK_STREAM,0);
	if(serv_sock==-1) error_handling("socket() error!");
	struct sockaddr_in serv_addr;
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));
	if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("bind() error!");
	if(listen(serv_sock,30)==-1) error_handling("listen() error!");
	work(serv_sock);
	close(serv_sock);
	return 0;
}

