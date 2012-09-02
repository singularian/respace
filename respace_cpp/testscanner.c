#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int bscanner(char *string);
int bbscanner(char *string);
int fxscanner(char *string);
int fscanner(char *string);
void stringxy(char *string, int beginning, int end);

int main (int argc, char *argv[])
{
	if ((argc = 2))
	{
		fscanner(argv[1]);
		fxscanner(argv[1]);
		bscanner(argv[1]);
		bbscanner(argv[1]);
	}


}

// new scanner
int fxscanner(char *string) {
        int i = 0, j = 0, cntr = 0;
        int length = 0;
	length = strlen(string) - 1;

	printf("\nfx scan two %s", string);


	while(1)
	{
		for (j = i; j <= length; j++) {
		stringxy(string, i, j);
		cntr++;
		}
		j = 0;
		i++;
		if (i > length) break;
	}

	printf("\n");
	printf("count = %d\n", cntr);
	return (0);

}

// forward scanner
int fscanner(char *string) {
        int i = 0, j, k, ctr = 0;
        int length = 0;

	length = strlen(string) - 1;
	printf("\nforward scan %s", string);

    //      size.length = (strlen(string) - 1);
    //
             for(i = 0; i <= length; i++)
		for(j = i; j <= length; j++)
		{
     	//		printf("%d %d\n", i, j);
			if (j >= i) stringxy(string, i, j);
			ctr++;
		}
	printf("\n");
	printf("count = %d\n", ctr);
	return (0);
}

// backward scanner
int bscanner(char *string) {
       int i = 0, j, k, ctr = 0;
       int length = 0;

       length = strlen(string) - 1;
	printf("\nbackward scan %s", string);

	for(i = length; i >= 0; i--)
           for(j = length; j >= 0; j--)
  	{
		if (j >= i) stringxy(string, i, j);
	}
	printf("\n");
	return (0);


}

// backward scanner two
int bbscanner(char *string) {
	int i = 0, j, k, ctr = 0;
	int length = 0;

	length = strlen(string) - 1;
	printf("\nbackward scan two %s", string);

             for(i = length; i >= 0; i--)
                for(j = 0; j <= length; j++)
                {
		if (j >= i) stringxy(string, i, j);
	}
	printf("\n");
	return (0);

}


// show string from x to y
void stringxy(char *string, int beginning, int end)
{
    printf("\nString from (%i, %i) ", beginning, end);
    int i = 0;
    for (i = beginning; i <= end; i++)
    {
              printf("%c", (char *) string[i]);
    }

}

