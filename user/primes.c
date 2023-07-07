#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void primes(int p[]){
  int num;
  if(read(p[0], &num, sizeof(num)) == 0) exit(0);

  fprintf(1, "prime %d\n", num);

  int c[2];
  pipe(c);
  if(fork()){
    int get_num;
    while(read(p[0], &get_num, sizeof(get_num))){
        if(get_num % num != 0) write(c[1], &get_num, sizeof(get_num));
             }
        close(p[0]);
        close(c[1]);
        wait(0);
  } else {
        close(p[0]);
        close(c[1]);
        primes(c);
  }
}

int main(int arc, char *argv[]){
  
// fork() pipe()
  int p[2];
  pipe(p);
  for(int i = 2; i < 35; i++){
    write(p[1], &i, sizeof(i));
  }
  close(p[1]);
  primes(p);
  exit(0);
}
