#include "data.h"


void data::writeGenotypes(string filename) {
	// Init
	vrb.title("Writing genotypes in ["  + filename + "]");
	string file_format = "wz";
	htsFile * fp = hts_open(filename.c_str(),file_format.c_str());
	bcf_hdr_t * hdr = bcf_hdr_init("w");
	bcf1_t *rec    = bcf_init1();

	// Create VCF header
	bcf_hdr_append(hdr, "##source=makeScaffold");

	string pchr = chr[0];
	bcf_hdr_append(hdr, string("##contig=<ID="+ pchr + ">").c_str());
	for (int v = 1 ; v < chr.size() ; v++) if (chr[v] != pchr) {
		pchr = chr[v];
		bcf_hdr_append(hdr, string("##contig=<ID="+ pchr + ">").c_str());
	}
	bcf_hdr_append(hdr, "##FORMAT=<ID=GT,Number=1,Type=String,Description=\"Genotypes\">");

	//Add samples
	for (int i = 0 ; i < vec_names.size() ; i ++) bcf_hdr_add_sample(hdr, vec_names[i].c_str());
	bcf_hdr_add_sample(hdr, NULL);      // to update internal structures
	bcf_hdr_write(fp, hdr);

	//Add records
	int * genotypes = (int*)malloc(bcf_hdr_nsamples(hdr)*2*sizeof(int));
	for (int l = 0 ; l < chr.size() ; l ++) {
		bcf_clear1(rec);
		rec->rid = bcf_hdr_name2id(hdr,chr[l].c_str());
		rec->pos = pos[l] - 1;
		bcf_update_id(hdr, rec, id[l].c_str());
		string alleles = ref[l] + "," + alt[l];
		bcf_update_alleles_str(hdr, rec, alleles.c_str());
		for (int i = 0 ; i < vec_names.size() ; i++) {
			if (miss[i][l]) {
				genotypes[2*i+0] = bcf_gt_missing;
				genotypes[2*i+1] = bcf_gt_missing;
			} else if (phas[i][l]) {
				genotypes[2*i+0] = bcf_gt_phased(gen1[i][l]);
				genotypes[2*i+1] = bcf_gt_phased(gen2[i][l]);
			} else {
				genotypes[2*i+0] = bcf_gt_unphased(gen1[i][l]);
				genotypes[2*i+1] = bcf_gt_unphased(gen2[i][l]);
			}
		}
		bcf_update_genotypes(hdr, rec, genotypes, bcf_hdr_nsamples(hdr)*2);
		bcf_write1(fp, hdr, rec);
	}
	free(genotypes);
	bcf_destroy1(rec);
	bcf_hdr_destroy(hdr);
	if (hts_close(fp)) vrb.error("Non zero status when closing VCF/BCF file descriptor");
	vrb.bullet("VCF writing [Compressed / N=" + stb.str(vec_names.size()) + " / L=" + stb.str(chr.size()) + "]");
}
