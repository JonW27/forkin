#include "pipe_networking.h"
#include <signal.h>

void process(char *s);
void subserver(int from_client);

static void sighandler(int signo) {
  if (signo == SIGINT) {
    remove("luigi");
    exit(0);
  }
}

int main() {
  signal(SIGINT, sighandler);
  int parent = fork();
  if(parent){
    
    server_setup();
    
  } else{
    
    subserver(server_connect());
    
  }
    
}

void subserver(int from_client) {
  process();
}

void process(char * s) {
}
