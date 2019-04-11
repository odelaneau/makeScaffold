#define _DECLARE_TOOLBOX_HERE
#include "data.h"

void data::readPedigrees(string fped) {
	string buffer;
	vector < string > str;
	vrb.title("Reading pedigrees in [" + fped + "]");
	input_file fd (fped);
	if (fd.fail()) vrb.error("Cannot open file!");
	int n_unr = 0, n_duo = 0, n_tri = 0;
	while (getline(fd, buffer)) {
		stb.split(buffer, str);
		map < string, int > :: iterator itC = map_names.find(str[0]);
		map < string, int > :: iterator itF = map_names.find(str[1]);
		map < string, int > :: iterator itM = map_names.find(str[2]);
		if (itC != map_names.end()) {
			if (itF != map_names.end()) fathers[itC->second] = itF->second;
			else fathers[itC->second] = -1;
			if (itM != map_names.end()) mothers[itC->second] = itM->second;
			else mothers[itC->second] = -1;
			int type = (fathers[itC->second] >= 0) + (mothers[itC->second] >= 0);
			switch (type) {
				case 2: n_tri ++; break;
				case 1: n_duo ++; break;
				default: n_tri ++; break;
			}
		}
	}
	vrb.bullet("#trios = " + stb.str(n_tri));
	vrb.bullet("#duos = " + stb.str(n_duo));
	vrb.bullet("#unrelateds = " + stb.str(n_unr));
}

void data::readGenotypes(string fgen, string region) {
	vrb.title("Reading genotypes in ["  + fgen + "]");
	bcf_srs_t * sr =  bcf_sr_init();
	if (region != "") {
		if (bcf_sr_set_regions(sr, region.c_str(), 0) == -1) vrb.error("Impossible to jump to region [" + region + "]");
		else vrb.bullet("Jump to region [" + region + "] done");
	}

	//Read headers
	if(!(bcf_sr_add_reader (sr, fgen.c_str()))) vrb.error("Impossible to read header of [" + fgen + "]");

	//Genotype ids processing
	int n_samples_gen = bcf_hdr_nsamples(sr->readers[0].header);
	for (int i = 0 ; i < n_samples_gen ; i ++) {
		string sample_id = string(sr->readers[0].header->samples[i]);
		map_names.insert(pair < string, int > (sample_id, vec_names.size()));
		vec_names.push_back(sample_id);
		fathers.push_back(-1);
		mothers.push_back(-1);
	}
	vrb.bullet("#genotyped samples = " + stb.str(vec_names.size()));

	//Memory allocation
	gen1 = vector < vector < bool > > (vec_names.size());
	gen2 = vector < vector < bool > > (vec_names.size());
	phas = vector < vector < bool > > (vec_names.size());
	miss = vector < vector < bool > > (vec_names.size());

	//Read genotype and haplotype data
	int nset = 0, *gt_arr_gen = NULL, ngt_arr_gen = 0;
	int n_variant_tot = 0, n_variant_set = 0;
	bcf1_t * line_gen;
	while ((nset = bcf_sr_next_line (sr))) {
		line_gen =  bcf_sr_get_line(sr, 0);
		if (line_gen->n_allele == 2) {
			//
			bcf_unpack(line_gen, BCF_UN_STR);
			chr.push_back(bcf_hdr_id2name(sr->readers[0].header, line_gen->rid));
			pos.push_back(line_gen->pos + 1);
			id.push_back(string(line_gen->d.id));
			ref.push_back(line_gen->d.allele[0]);
			alt.push_back(line_gen->d.allele[1]);
			//Extract genotypes
			bcf_get_genotypes(sr->readers[0].header, line_gen, &gt_arr_gen, &ngt_arr_gen);
			for(int h = 0 ; h < 2 * n_samples_gen ; h += 2) {
				gen1[h/2].push_back(bcf_gt_allele(gt_arr_gen[h+0])!=0);
				gen2[h/2].push_back(bcf_gt_allele(gt_arr_gen[h+1])!=0);
				phas[h/2].push_back(bcf_gt_is_phased(gt_arr_gen[h+0]) && bcf_gt_is_phased(gt_arr_gen[h+1]));
				miss[h/2].push_back(gt_arr_gen[h+0] == bcf_gt_missing || gt_arr_gen[h+1] == bcf_gt_missing);
			}
			n_variant_set ++;
		}
		n_variant_tot ++;
	}
	vrb.bullet("#variants: total = " + stb.str(n_variant_tot) + " / set = " + stb.str(n_variant_set));
	free(gt_arr_gen);
	bcf_sr_destroy(sr);
}
