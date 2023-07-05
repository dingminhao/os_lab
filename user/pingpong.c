#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  int parent_fd[2], child_fd[2];
  pipe(parent_fd);
  pipe(child_fd);
  char buf[64];

  if (fork()) {
    // Parent
    close(child_fd[1]);
    write(parent_fd[1], "ping", strlen("ping"));
    read(child_fd[0], buf, 4);
    printf("%d: received %s\n", getpid(), buf);
    close(parent_fd[1]);
    close(parent_fd[0]);
    close(child_fd[0]);
  } else {
    // Child
    close(parent_fd[1]);
    read(parent_fd[0], buf, 4);
    printf("%d: received %s\n", getpid(), buf);
    write(child_fd[1], "pong", strlen("pong"));
    close(child_fd[1]);
    close(child_fd[0]);
  }
  exit(0);
}