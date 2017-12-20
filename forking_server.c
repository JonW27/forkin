#include "pipe_networking.h"
#include <signal.h>
#include <ctype.h>

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
  while(1){
    int wkp = server_setup();
    int parent = fork();
    if(!parent){
      subserver(wkp);
    }
  }
    
}

void subserver(int from_client) {
  int client = server_connect(from_client);
  char msg[BUFFER_SIZE];
  while(read(from_client, msg, sizeof(msg))){
    process(msg);
    write(client, msg, sizeof(msg));
  }
  exit(0);
}

void process(char * s) {
  int i = 0;
  for (; s[i]; i++) {
    s[i] = toupper(s[i]);
  }
}
