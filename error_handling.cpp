#include"headfile.h"
#include"error_handling.h"
#include<iostream>

using namespace std;

void error_handling(string msg){
//	fputs(msg,stderr);
//	fputc('\n',stderr);
	std::cout<<msg<<std::endl;
	exit(1);
}
