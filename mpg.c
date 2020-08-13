#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
   
char *gen(unsigned int len) {
	unsigned int random;
	unsigned int ilatin, iulatin, iansi;
	unsigned int i;
	char *pass;

  char latin[] = {
		'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q',
    'r','s','t','u','v','w','x','y','z'
	};

	char ulatin[] = {
		'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R',
    'S','T','U','V','W','X','Y','Z'
	};

	char ansi[] = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!','@','#','$','%','^',
    '&','*','(',')','-','=','+','.',',',':',';','"','?'
	};

	pass = (char *) malloc (len * sizeof(char)); /*allocating pass on memory.*/

  /*generating random sequences.*/
	ilatin = len - rand() % (len + 1);
	iulatin = len - ilatin - rand() % (len - ilatin + 1);

	if (iulatin > 0) {
		iansi = len - ilatin - iulatin;
  }

	else {
		iansi = len - ilatin;
  }

	for (i = 0; i < len; i++) {
		random = rand() % 100;

		if (random > 50) {
			pass[i] = latin[rand() % sizeof(latin)];
    }

		else if (random > 20 && random <= 50) {
		  pass[i] = ulatin[rand() % sizeof(ulatin)];
    }
		
    else {
		  pass[i] = ansi[rand() % sizeof(ansi)];
    }
	}

  /*delay 1 second to generate password to avoid 
   * people having the same password.*/
  system("sleep 01");
  	
	return pass;
}

void printLogo() {
  printf(" _____ ___ ___\n");
  printf("|     | . | . |\n");
  printf("|_|_|_|  _|_  |\n");
  printf("      |_| |___|\n\n");
  printf("          ~0xbiel\n\n");
}

int main(int argc, char **argv[]) {
	srand(time(0));
	unsigned int len;
	char *pass;

  /* determine if stdout is connected to a terminal */

  int tty = isatty(fileno(stdout));
  
  /*if there's no first argument, show help.*/

  if(!argv[1]) {

    if(tty) {
      printLogo();
      printf("usage: mpg [password length]\n\n");
    }

    exit(1);
  }

	else if (atoi(argv[1]) > 4096 || atoi(argv[1]) < 5) {

    if(tty) {
      printLogo();
      printf("the length must be higher than 5 and lower than 4096.\n");
    }

	  exit(1);
	} 
  
  else {
	  len = atoi(argv[1]);
  }

  if(tty) {
    printLogo();
    printf("here's your password: ");
  }

  pass = gen(len);
  int usleep(dsec);
  printf("%s\n",pass);

	return 0;
}
