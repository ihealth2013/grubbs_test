#ifndef GRUBBSTEST_H
#define GRUBBSTEST_H
  
#define CONCONFIDENCE_LEVEL 1 // 0 = q90, 1 = q95, 2 = q99 

int Discard_One_Outlier_ByGrubbs(int* arrayList, int length);

int Discard_All_Outlier_Grubbs(int* arrayList, int length);
 
#endif
