#include "internalErrors.h"
#include <stdio.h>
#include <stdlib.h>

void ie_allocationError(){
   fprintf(stderr, "INTERNAL ERROR: allocation failed.\n");
   exit(EXIT_FAILURE);
};