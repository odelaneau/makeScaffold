#include "data.h"

bool data::solveTrio(int locus, int cidx, int fidx, int midx) {
	int cg = gen1[cidx][locus] + gen2[cidx][locus];
	int fg = gen1[fidx][locus] + gen2[fidx][locus];
	int mg = gen1[midx][locus] + gen2[midx][locus];
	int phased = 0, mendel = 0;
	bool c0 = false, c1 = false, f0 = false, f1 = false, m0 = false, m1 = false;
	if (fg == 0 && mg == 0 && cg == 0) { f0 = 0; f1 = 0; m0 = 0; m1 = 0; c0 = 0; c1 = 0; mendel = 0; phased = 1;}
	if (fg == 0 && mg == 0 && cg == 1) { f0 = 0; f1 = 0; m0 = 0; m1 = 0; c0 = 0; c1 = 1; mendel = 1; phased = 0;}
	if (fg == 0 && mg == 0 && cg == 2) { f0 = 0; f1 = 0; m0 = 0; m1 = 0; c0 = 1; c1 = 1; mendel = 1; phased = 0;}
	if (fg == 0 && mg == 1 && cg == 0) { f0 = 0; f1 = 0; m0 = 1; m1 = 0; c0 = 0; c1 = 0; mendel = 0; phased = 1;}
	if (fg == 0 && mg == 1 && cg == 1) { f0 = 0; f1 = 0; m0 = 0; m1 = 1; c0 = 0; c1 = 1; mendel = 0; phased = 1;}
	if (fg == 0 && mg == 1 && cg == 2) { f0 = 0; f1 = 0; m0 = 0; m1 = 1; c0 = 1; c1 = 1; mendel = 1; phased = 0;}
	if (fg == 0 && mg == 2 && cg == 0) { f0 = 0; f1 = 0; m0 = 1; m1 = 1; c0 = 0; c1 = 0; mendel = 1; phased = 0;}
	if (fg == 0 && mg == 2 && cg == 1) { f0 = 0; f1 = 0; m0 = 1; m1 = 1; c0 = 0; c1 = 1; mendel = 0; phased = 1;}
	if (fg == 0 && mg == 2 && cg == 2) { f0 = 0; f1 = 0; m0 = 1; m1 = 1; c0 = 1; c1 = 1; mendel = 1; phased = 0;}
	if (fg == 1 && mg == 0 && cg == 0) { f0 = 0; f1 = 1; m0 = 0; m1 = 0; c0 = 0; c1 = 0; mendel = 0; phased = 1;}
	if (fg == 1 && mg == 0 && cg == 1) { f0 = 1; f1 = 0; m0 = 0; m1 = 0; c0 = 1; c1 = 0; mendel = 0; phased = 1;}
	if (fg == 1 && mg == 0 && cg == 2) { f0 = 1; f1 = 0; m0 = 0; m1 = 0; c0 = 1; c1 = 1; mendel = 1; phased = 0;}
	if (fg == 1 && mg == 1 && cg == 0) { f0 = 0; f1 = 1; m0 = 1; m1 = 0; c0 = 0; c1 = 0; mendel = 0; phased = 1;}
	if (fg == 1 && mg == 1 && cg == 1) { f0 = 0; f1 = 1; m0 = 0; m1 = 1; c0 = 0; c1 = 1; mendel = 0; phased = 0;}
	if (fg == 1 && mg == 1 && cg == 2) { f0 = 1; f1 = 0; m0 = 0; m1 = 1; c0 = 1; c1 = 1; mendel = 0; phased = 1;}
	if (fg == 1 && mg == 2 && cg == 0) { f0 = 0; f1 = 1; m0 = 1; m1 = 1; c0 = 0; c1 = 0; mendel = 1; phased = 0;}
	if (fg == 1 && mg == 2 && cg == 1) { f0 = 0; f1 = 1; m0 = 1; m1 = 1; c0 = 0; c1 = 1; mendel = 0; phased = 1;}
	if (fg == 1 && mg == 2 && cg == 2) { f0 = 1; f1 = 0; m0 = 1; m1 = 1; c0 = 1; c1 = 1; mendel = 0; phased = 1;}
	if (fg == 2 && mg == 0 && cg == 0) { f0 = 1; f1 = 1; m0 = 0; m1 = 0; c0 = 0; c1 = 0; mendel = 1; phased = 0;}
	if (fg == 2 && mg == 0 && cg == 1) { f0 = 1; f1 = 1; m0 = 0; m1 = 0; c0 = 1; c1 = 0; mendel = 0; phased = 1;}
	if (fg == 2 && mg == 0 && cg == 2) { f0 = 1; f1 = 1; m0 = 0; m1 = 0; c0 = 1; c1 = 1; mendel = 1; phased = 0;}
	if (fg == 2 && mg == 1 && cg == 0) { f0 = 1; f1 = 1; m0 = 0; m1 = 1; c0 = 0; c1 = 0; mendel = 1; phased = 0;}
	if (fg == 2 && mg == 1 && cg == 1) { f0 = 1; f1 = 1; m0 = 1; m1 = 0; c0 = 1; c1 = 0; mendel = 0; phased = 1;}
	if (fg == 2 && mg == 1 && cg == 2) { f0 = 1; f1 = 1; m0 = 0; m1 = 1; c0 = 1; c1 = 1; mendel = 0; phased = 1;}
	if (fg == 2 && mg == 2 && cg == 0) { f0 = 1; f1 = 1; m0 = 1; m1 = 1; c0 = 0; c1 = 0; mendel = 1; phased = 0;}
	if (fg == 2 && mg == 2 && cg == 1) { f0 = 1; f1 = 1; m0 = 1; m1 = 1; c0 = 0; c1 = 1; mendel = 1; phased = 0;}
	if (fg == 2 && mg == 2 && cg == 2) { f0 = 1; f1 = 1; m0 = 1; m1 = 1; c0 = 1; c1 = 1; mendel = 0; phased = 1;}
	gen1[cidx][locus] = c0; gen2[cidx][locus] = c1; gen1[fidx][locus] = f0; gen2[fidx][locus] = f1; gen1[midx][locus] = m0; gen2[midx][locus] = m1;
	phas[cidx][locus] = phased;
	phas[fidx][locus] = phased;
	phas[midx][locus] = phased;
	if (mendel) return true;
	else return false;
}

bool data::solveDuoFather(int locus, int cidx, int pidx) {
	int cg = gen1[cidx][locus] + gen2[cidx][locus];
	int pg = gen1[pidx][locus] + gen2[pidx][locus];
	bool c0 = false, c1 = false, p0 = false, p1 = false;
	int phased = 0, mendel = 0;
	if (pg == 0 && cg == 0) { p0 = 0; p1 = 0; c0 = 0; c1 = 0; mendel = 0; phased = 1;}
	if (pg == 0 && cg == 1) { p0 = 0; p1 = 0; c0 = 0; c1 = 1; mendel = 0; phased = 1;}
	if (pg == 0 && cg == 2) { p0 = 0; p1 = 0; c0 = 1; c1 = 1; mendel = 1; phased = 0;}
	if (pg == 1 && cg == 0) { p0 = 0; p1 = 1; c0 = 0; c1 = 0; mendel = 0; phased = 1;}
	if (pg == 1 && cg == 1) { p0 = 0; p1 = 1; c0 = 0; c1 = 1; mendel = 0; phased = 0;}
	if (pg == 1 && cg == 2) { p0 = 1; p1 = 0; c0 = 1; c1 = 1; mendel = 0; phased = 1;}
	if (pg == 2 && cg == 0) { p0 = 1; p1 = 1; c0 = 0; c1 = 0; mendel = 1; phased = 0;}
	if (pg == 2 && cg == 1) { p0 = 1; p1 = 1; c0 = 1; c1 = 0; mendel = 0; phased = 1;}
	if (pg == 2 && cg == 2) { p0 = 1; p1 = 1; c0 = 1; c1 = 1; mendel = 0; phased = 1;}
	gen1[cidx][locus] = c0; gen2[cidx][locus] = c1; gen1[pidx][locus] = p0; gen2[pidx][locus] = p1;
	phas[cidx][locus] = phased;
	phas[pidx][locus] = phased;
	if (mendel) return true;
	else return false;
}

bool data::solveDuoMother(int locus, int cidx, int pidx) {
	int cg = gen1[cidx][locus] + gen2[cidx][locus];
	int pg = gen1[pidx][locus] + gen2[pidx][locus];
	bool c0 = false, c1 = false, p0 = false, p1 = false;
	int phased = 0, mendel = 0;
	if (pg == 0 && cg == 0) { p0 = 0; p1 = 0; c0 = 0; c1 = 0; mendel = 0; phased = 1;}
	if (pg == 0 && cg == 1) { p0 = 0; p1 = 0; c0 = 1; c1 = 0; mendel = 0; phased = 1;}
	if (pg == 0 && cg == 2) { p0 = 0; p1 = 0; c0 = 1; c1 = 1; mendel = 1; phased = 0;}
	if (pg == 1 && cg == 0) { p0 = 1; p1 = 0; c0 = 0; c1 = 0; mendel = 0; phased = 1;}
	if (pg == 1 && cg == 1) { p0 = 0; p1 = 1; c0 = 0; c1 = 1; mendel = 0; phased = 0;}
	if (pg == 1 && cg == 2) { p0 = 0; p1 = 1; c0 = 1; c1 = 1; mendel = 0; phased = 1;}
	if (pg == 2 && cg == 0) { p0 = 1; p1 = 1; c0 = 0; c1 = 0; mendel = 1; phased = 0;}
	if (pg == 2 && cg == 1) { p0 = 1; p1 = 1; c0 = 0; c1 = 1; mendel = 0; phased = 1;}
	if (pg == 2 && cg == 2) { p0 = 1; p1 = 1; c0 = 1; c1 = 1; mendel = 0; phased = 1;}
	gen1[cidx][locus] = c0; gen2[cidx][locus] = c1; gen1[pidx][locus] = p0; gen2[pidx][locus] = p1;
	phas[cidx][locus] = phased;
	phas[pidx][locus] = phased;
	if (mendel) return true;
	else return false;
}

void data::solvePedigrees() {
	vrb.title("Solving pedigrees");
	int n_trio = 0, n_fduo = 0, n_mduo = 0, n_mendel = 0;
	mendel_error = vector < int > (vec_names.size(), 0);
	mendel_total = vector < int > (vec_names.size(), 0);
	for (int i = 0 ; i < vec_names.size() ; i++) {
		//Trio case
		if (fathers[i] >= 0 && mothers[i] >= 0) {
			int mendel = 0;
			for (int l = 0 ; l < gen1[i].size() ; l ++) {
				if (!miss[i][l]) {
					if (!miss[fathers[i]][l] && !miss[mothers[i]][l]) mendel += solveTrio(l, i, fathers[i], mothers[i]);
					else if (!miss[fathers[i]][l]) mendel += solveDuoFather(l, i, fathers[i]);
					else if (!miss[mothers[i]][l]) mendel += solveDuoMother(l, i, mothers[i]);
				}
			}
			n_mendel += mendel;
			mendel_error[fathers[i]] = mendel;
			mendel_error[mothers[i]] = mendel;
			mendel_error[i] = mendel;
			n_trio ++;
		}
		//Duo father case
		if (fathers[i] >= 0 && mothers[i] < 0) {
			int mendel = 0;
			for (int l = 0 ; l < gen1[i].size() ; l ++) {
				if (!miss[i][l] && !miss[fathers[i]][l]) mendel += solveDuoFather(l, i, fathers[i]);
			}
			n_mendel += mendel;
			mendel_error[fathers[i]] = mendel;
			mendel_error[i] = mendel;
			n_fduo ++;
		}
		//Duo mother case
		if (fathers[i] < 0 && mothers[i] >= 0) {
			int mendel = 0;
			for (int l = 0 ; l < gen1[i].size() ; l ++) {
				if (!miss[i][l] && !miss[mothers[i]][l]) mendel += solveDuoMother(l, i, mothers[i]);
			}
			n_mendel += mendel;
			mendel_error[mothers[i]] = mendel;
			mendel_error[i] = mendel;
			n_mduo ++;
		}
	}
	vrb.bullet("#mendel_errors = " + stb.str(n_mendel));
}
