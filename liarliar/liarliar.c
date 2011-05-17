/* C solution to the "Liar, Liar" Facebook puzzle
 * By: Lincoln Simmons
 * Date: May 12, 2011
 *
 * This solution is written in C and the execution time can be rather slow,
 * as the algorithm is O(n^2), but it uses no special structs except the GNU
 * C (glibc) hash table functions.
 *
 * Algorithm: Grab first name, assume they're honest and enter into hash.
 *            Then run through all names using these rules for each pair
 * 			  of accuser/victim
 *  RULE 1) If neither accuser or victim has been hashed yet
 *	    	 - You can't make an assumption, so drop them for now
 *  RULE 2) If only one has been hashed (accuser or victim)
 *			 - Keep already hashed in current group, assign opposite
 *        	   group to un-hashed member and insert them into hash
 *  RULE 3) If both accuser and victim have already been hashed
 *      	 - Assert both are in opposite groups, else, this is invalid input!
 *
 * 			Cycle through the list repeatedly until all names have been accounted for
 */

#include <search.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 16

static int num_liars = 0;
static int num_hashed = 0;

/* I'm going to improperly use the ENTRY field, data.  I don't care to
   create pointers to data structures.  I merely want to save the value
   0 or 1, so I am misusing the pointer type to act as an boolean value. */
#define LIAR 	(void *)1
#define HONEST	(void *)0

int set_groups(char *accuser, char *victim);

int main (int argc, char *argv[])
{
	char *accuser, *victim, *names[1000000];
	int ii, total_vets, acc_hashed, num_votes, vet_iter, names_iter = 0;
	ENTRY vet, *vetptr;
	fpos_t fp_pos;
	FILE *fp = fopen(argv[1], "r");

	if (fp == NULL) {
		printf("File not found\n");
		return 0;
	}

	/* Create hash based on total number of veterans */
	fscanf(fp, "%d", &total_vets);
	if (!hcreate(total_vets)) {
		printf("Hash creation failed. Not enough memory (probably).\n");
		return 0;
	}

	/* Save file pointer so we can reload it after grabbing first name */
	if (fgetpos(fp, &fp_pos)) {
		printf("fgetpos() failed\n");
		fclose(fp);
		return -1;
	}

	/* Grab first name, assume they're honest (so we start with an
       assumption to base everything else off of) and load in the hash */
	names[names_iter] = malloc(MAX_NAME_LEN);
	fscanf(fp, "%s", names[names_iter]);
	vet.key = names[names_iter];
	vet.data = HONEST;
	num_hashed++;
	vetptr = hsearch(vet, ENTER);
	if (vetptr == NULL) {
		printf("hsearch(ENTER) failed\n");
		return -1;
	}

	names_iter++;

	do {
		/* Reset the file pointer increment names_iter and start reading accusations! */
		if (fsetpos(fp, &fp_pos)) {
			printf("fsetpos() failed\n");
			fclose(fp);
			return -1;
		}

		for (vet_iter = 0; vet_iter < total_vets; vet_iter++)
		{
			names[names_iter] = malloc(MAX_NAME_LEN);
			fscanf(fp, "%s", names[names_iter]);
			accuser = names[names_iter];
			acc_hashed = 0;
			names_iter++;

			fscanf(fp, "%d", &num_votes);
			while (num_votes > 0) {
				names[names_iter] = malloc(MAX_NAME_LEN);
				fscanf(fp, "%s", names[names_iter]);
				victim = names[names_iter];
				if (set_groups(accuser, victim)) {
					acc_hashed = 1;
					names_iter++;
					num_hashed++;
				} else {
					/* Free victim's name.  It wasn't hashed yet */
					free(names[names_iter]);
				}
				num_votes--;
			}
			
			if (!acc_hashed) {
				/* Free accuser's name, too.  It wasn't hashed */
				names_iter--;
				free(names[names_iter]);
			}
		}
	} while (num_hashed < total_vets);

	if (num_liars > (total_vets - num_liars)) {
		printf("%d %d\n", num_liars, total_vets-num_liars);
	} else {
		printf("%d %d\n", total_vets-num_liars, num_liars);
	}

	names_iter--;
	while (names_iter >= 0)
	{
		free(names[names_iter]);
		names_iter--;
	}


	fclose(fp);

	return 0;
}

/**
 * Takes an accuser and victim, looks up their data in the hash
 * (or adds the veteran if needed), and sets their group based
 * on the rules in file header.
 *
 * The data pointer in the hash will be 1 if the entry is a liar
 *
 * Returns 1 if a key was hashed, 0 otherwise.
 */
int set_groups(char *accuser, char *victim) {
	ENTRY ae, *aep; /* Accuser entry (pointer) */
	ENTRY ve, *vep; /* Victim entry (pointer)  */

	ae.key = accuser;
	ve.key = victim;

	aep = hsearch(ae, FIND);
	vep = hsearch(ve, FIND);

	if (aep == NULL && vep == NULL) {
		/* Can't make assumption, just return */
		return 0;
	} else if (aep != NULL && vep == NULL) {
		if (aep->data == HONEST) {
			ve.data = LIAR;
			num_liars++;
		} else {
			ve.data = HONEST;
		}
		vep = hsearch(ve, ENTER);
		return 1;
	} else if (vep != NULL && aep == NULL) {
		if (vep->data == HONEST) {
			ae.data = LIAR;
			num_liars++;
		} else {
			ae.data = HONEST;
		}
		aep = hsearch(ae, ENTER);
		return 1;
	}

	return 0;
}
