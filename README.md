# makeScaffold
Build a haplotype scaffold for a VCF/BCF from a PED file

Usage:

makeScaffold --vcf myGenotypes.vcf.gz --fam myPedigreees.txt --reg chr1 --myScaffoldedGenotypes.vcf.gz

makeScaffold --vcf myGenotypes.vcf.gz --fam myPedigreees.txt --reg chr22:10000000-20000000 --myScaffoldedGenotypes.bcf


cat myPedigreees.txt

child1 father1 mother1
child2 father2 mother2
child3 father3 mother3
child4 father4 mother4
