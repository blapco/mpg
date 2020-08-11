#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *gen(unsigned int len) {
  unsigned int random;
  unsigned int l, ul, a, n;
  char *pass;

  char *latin[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

  char *upperlatin[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

  char *ansi[] = {'!','@','#','$','%','^','&','*','(',')','-','=','+','.',',',':',';','"','?'};

  int num[] = {
    1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 
    11, 12, 13, 14, 15, 16, 17, 18, 19,
    20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
    30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
    40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
    50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
    60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
    70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
    90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
  };

  pass = (char*) malloc (len * sizeof(char)); /*allocating password on memory.*/
  
  /*generating random sequences*/
  ul = len - rand() % (len + 1);
  l = len - ul - rand() % (len - ul + 1);

  if(l > 0) {
    a = len - ul - l - n;
  }

  else {
    a = len - ul;
  }

  for(int i = 0; i < len; i++) {
    random = rand() % 100;
    
    if(random > 50) {
      pass[i] = upperlatin[rand() % sizeof(upperlatin)];
    }

    else if(random > 20 && random <= 50) {
      pass[i] = latin[rand() % sizeof(latin)];
    }

    else {
      pass[i] = ansi[rand() % sizeof(ansi)];
      pass[i] = num[rand() % sizeof(num)];
    }
  }

  return pass;
}

int main(int argc, char **argv[]) {
  srand(time(0));
  unsigned int len;
  char *pass;

  /*if there's no first argument, show help.*/

  if(!argv[1]) {
    printf(" _____ ___ ___\n");
    printf("|     | . | . |\n");
    printf("|_|_|_|  _|_  |\n");
    printf("      |_| |___|\n\n");
    printf("          ~0xbiel\n\n");
    
    printf("usage: mpg [password length]\n\n");
  }

  else if(atoi(argv[1]) > 4096 || atoi(argv[1]) < 5) {
    printf("password length must be bigger than 5 and smaller than 4096.");
    exit(1);
  }

  else {
    len = atoi(argv[1]);
  }

  pass = gen(len);
  printf("%s\n", pass);

  return 0; 
}
