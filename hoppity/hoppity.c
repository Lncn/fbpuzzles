/* Solution to the "Hoppity Hop!" Facebook puzzle
 * By: Lincoln Simmons
 * Date: March 3, 2011
 */

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	int iter, input = atoi(argv[1]);

	for(iter = 1; iter <= input; iter++)
	{
		if (iter % 3 == 0 && iter % 5 == 0)
			printf("Hop\n");
		else if (iter % 3 == 0)
			printf("Hoppity\n");
		else if (iter % 5 == 0)
			printf("Hophop\n");
	}

	return 0;
}
