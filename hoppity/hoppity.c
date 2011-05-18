/* Solution to the "Hoppity Hop!" Facebook puzzle
 * By: Lincoln Simmons
 * Date: March 3, 2011
 */

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	int ii, input;

	if (argc <= 1) return 0;

	input = atoi(argv[1]);

	for(ii = 1; ii <= input; ii++)
	{
		if (ii % 3 == 0 && ii % 5 == 0)
			printf("Hop\n");
		else if (ii % 3 == 0)
			printf("Hoppity\n");
		else if (ii % 5 == 0)
			printf("Hophop\n");
	}

	return 0;
}
