#include "benchmark.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void BENCH_ADD(const char func[], double effective_time, double actual_time) {
	FILE *in = fopen("bench", "r");
	FILE *out = fopen("tmp", "a");

	bool new = true;

	#define FMT_STR "%lf = %lf / %i \t%lf \t%s\n"

	double frac = 0.0;
	double eff = 0.0;
	int i = 0;
	double act = 0.0;
	char *f = malloc(100 * sizeof(char));

	while (true) {
		int z = fscanf(in, FMT_STR, &frac, &eff, &i, &act, f);

		if (z == EOF) break;
		if (z == 0) continue;


		if (strcmp(f, func) == 0) {
			frac = (eff + effective_time) / (i + 1);
			fprintf(out, FMT_STR, frac, eff + effective_time, i + 1, act + actual_time, func);
			new = false;
		}
		else {
			// Copy old one
			fprintf(out, FMT_STR, frac, eff, i, act, f);
		}
	}

	free(f);


	if (new) {
		fprintf(out, FMT_STR, effective_time, effective_time, 1, actual_time, func);
	}


	fclose(in);
	fclose(out);

	rename("tmp", "bench");
}
