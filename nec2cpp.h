/*
 * nec2cpp.h - header file for nec2 c++
 */
#ifndef NEC2CPP_H
#define NEC2CPP_H

#include "math_util.h"
#include "nec_context.h"

using namespace std;

int mainforNEC(int argc, char **argv, nec_context* s_context,FILE *input_fp,
	FILE *output_fp);
void fblock(int nrow, int ncol, int imax, int ipsym);

#include "misc.h"
#endif
