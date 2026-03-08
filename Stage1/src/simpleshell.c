#include <stdio.h>
#include "utilities/init.h"
#include "utilities/handle_input.h"

int main(int argc, char * argv[]){
  // init the shell
  init();
  // if filename present
  if (argc == 2) {
    handle_input(argv[1]);
  }
  else { // if no filename
    handle_input(NULL);
  }
  return 0;
}
