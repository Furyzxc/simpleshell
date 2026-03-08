#include <stdio.h>
#include "utilities/init.h"
#include "utilities/handle_input.h"

int main(int argc, char * argv[]){
  init();

  if (argc == 2) {
    handle_input(argv[1]);
  }
  else {
    handle_input(NULL);
  }
  return 0;
}
