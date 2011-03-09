/* Solution to the "Liar, Liar" Facebook puzzle
 * By: Lincoln Simmons
 * Date: March 6, 2011
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Report index of the given name.
 *
 * If name is not reported yet, assign an index
 */
int index(char *name)
{
	int index;

	

	return index;
}
	
int main (int argc, char *argv[])
{
	int num_vets, ii;
	char name[15];
	FILE *fp = fopen(argv[1], "r");

	if (fp == NULL) {
		printf("File not found\n");
		return 0;
	}

	fscanf(fp, "%d", &num_vets);

	int votes[num_vets][num_vets];

	printf("%d\n", num_vets);
	while (!feof(fp))
	{
		fscanf(fp, "%s", name);
		printf("%s\n", name);
		fscanf(fp, "%d", &ii);
		printf("%d\n", ii);
		while (ii > 0) {
			fscanf(fp, "%s", name);
			printf("%s\n", name);
			ii--;
		}
	}

	fclose(fp);

	return 0;
}

