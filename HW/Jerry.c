#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <signal.h>
#include <wait.h>
#include <stdlib.h>
#include<iostream>
using namespace std;

pid_t parent, child;

void myhandler(int sig){
	if(p_pid == getpid()){
		sleep(2);
		return;
	}
	cout<<"자식 프로세스 종료"<<endl;
	exit(0);
}
void child_wait(int sig){
	wait(NULL);
	cout<<"부모 프로세스 종료"<<endl;
	exit(0);
} int main() {
    char user[80], other[80];
    int i, n;
    int fdw, fdr;
    char *chatTtoJ = "./chatTtoJ";
    char *chatJtoT = "./chatJtoT";


    mkfifo(chatTtoJ, 0666);
    mkfifo(chatJtoT, 0666);

    pid_t pid = fork();
    ostream out(chatJtoT);
    istream in(chatTtoJ);
    signal(SIGINT, myhandler);
    signal(SIGCHLD, child_wait);
  if(pid > 0){
    child = pid;
    parent = getpid();
    printf("부모 프로세스 PID = %d : 자식 PID = %d\n", parent, child);
    while(1){
      in>>other;
      cout<<other<<endl;
      sleep(1);
    }
  }
  else if(pid == 0){
    child = getpid();
    parent = getppid();

    printf("자식 프로세스 PID = %d : 부모 프로세스 PID = %d\n", child, parent);
    while(1){
      cin>>user;
      out<<user<<endl;
    }
  }
  else{
    printf("fork 오류");
    return 0;
  }
  in.close();
  out.close();
  return 0;
}
