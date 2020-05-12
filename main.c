#include <stdio.h>
#include "xor-list.h"


int main(int argc, char **argv)
{
	struct Xorlist l;
	init_xor_list(&l);
	int command;
	long long pos, data;
	
	printf("0                     : print list\n");
	printf("1 <position> <number> : insert <number> into <position>\n");
	printf("2 <position> 		  : erase <position> in the list\n");
	printf("Ctrl + D              : exit\n");
	
	while(scanf("%d", &command) == 1){
		switch (command) {
		  case 0:
			printf("Your list: ");
			print_xor_list(&l);
			break;
		  case 1:
			scanf("%Ld %Ld", &pos, &data);
			if(insert(&l, pos, data)){
				fprintf (stderr, "error \n");
				return 1;
			}
			break;
		  case 2:
			scanf("%Ld", &pos);
			if(erase(&l, pos)){
				fprintf (stderr, "error \n");
				return 1;
			};
			break;
		default:
			printf("Unknown command %d\n", command);
			break;
		}
	}
	delete_xor_list(&l);
	
	return 0;
}

