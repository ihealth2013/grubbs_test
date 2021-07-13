#include<stdio.h>
#include<math.h>
#include "grubbstest.h"


double calAverage(int arr[], int length);
double calStandard(int arr[], int length, double average);
double queryG(n);


// 静态数组，用于格拉布斯准则  
static double GrubbsCon90[] = { 0, 0, 0,
                                1.135, 1.463, 1.672, 1.822, 1.938,2.032, 2.11,
                                2.176, 2.234, 2.285, 2.331, 2.371,2.409, 2.443,
                                2.475, 2.504, 2.532, 2.557, 2.58, 2.603, 2.624,
                                2.644, 2.663, 2.745, 2.811, 2.866, 2.914, 2.956
};  //the con90 map value isn't right .

static double GrubbsCon95[] = { 0, 0, 0,
                                1.135, 1.463, 1.672, 1.822, 1.938,2.032, 2.11,
                                2.176, 2.234, 2.285, 2.331, 2.371,2.409, 2.443,
                                2.475, 2.504, 2.532, 2.557, 2.58, 2.603, 2.624,
                                2.644, 2.663, 2.745, 2.811, 2.866, 2.914, 2.956 
                              };

static double GrubbsCon99[] = { 0, 0, 0, 
                                1.155, 1.492, 1.749, 1.944, 2.097, 2.231, 2.323,
                                2.41, 2.485, 2.55, 2.607, 2.659, 2.705, 2.747,
                                2.785, 2.821, 2.854, 2.884, 2.912, 2.939, 2.963,
                                2.987, 3.009, 3.103, 3.178, 3.24, 3.292, 3.336
                              };



//=====================================================
// 
// 给定数组，计算平均值
// 
//=====================================================
//
double calAverage(int arr[], int length) {
    double sum = 0.0;
    for (int i = 0; i < length; i++) {
        sum += arr[i];
    }
    return sum / length;
}



//=====================================================
// 
// 给定数组，计算标准差  
// 
//=====================================================
//
double calStandard(int arr[], int length, double average) {
    double sum = 0.0;
    for (int i = 0; i < length; i++) {
        sum += (arr[i] * 1.0 - average) * (arr[i] * 1.0 - average);
    }
    return sqrt(sum / (length - 1));
}

//=====================================================
// 
// 取alpha=0.05，返回g(n,a) 
// 
//=====================================================
double queryG(n) {
 
    double g_value = 0.0;

    if (CONCONFIDENCE_LEVEL == 0) {
        g_value = GrubbsCon90[n];
    }
    else if (CONCONFIDENCE_LEVEL == 1) {
        g_value = GrubbsCon95[n];
    }
    else if (CONCONFIDENCE_LEVEL == 2) {
        g_value = GrubbsCon99[n];
    }
    return g_value;
}
 

//=====================================================
// 
//  使用格拉布斯算法剔除一个异常值
// 
//  输入数组 
// 
//  成功返回1--剔除了1个异常值，失败返回 0--没有异常值
// 
//=====================================================

int Discard_One_Outlier_ByGrubbs(int* arrayList, int length) {
 
    int discardFlag =0;

    if (length >= 3 && length <= 31) {

        printf("length= %d\r\n", length);
        for (int i = 0; i < length; i++) {
            printf("%d ", arrayList[i]);
        }
        printf("\r\n");

        
        //1. calc average and standard value         
        double average = calAverage(arrayList, length);
        double standard = calStandard(arrayList, length, average);

        //2. query g value
        double g = queryG(length);

        printf("average = %lf \n", average);
        printf("standard = %lf \n", standard);
        printf("g = %lf \n", g);
          
        //3. get the outlier 
        
        int outlierPos =-1;  //the outlier in array postion

        for (int i = 0; i < length; i++) {
         
            if (fabs(arrayList[i] * 1.0 - average) > standard * g) {
                // outlier data
                printf("outlier data: %d \r\n", arrayList[i]);
                outlierPos = i;
                break;
            } 
        }

        if (outlierPos >= 0) {
            for (int i = outlierPos; i < length - 1; i++) {
                arrayList[i] = arrayList[i + 1];
            }
            arrayList[length - 1] = 0;
            discardFlag = 1;
        } 
 
    } 

    return discardFlag;

}

 



//=====================================================
// 
//  格拉布斯算法，剔除数组当中所有的异常值
// 
//  输入数组 
// 
//  返回 剔除数据的个数
// 
//=====================================================

int Discard_All_Outlier_Grubbs(int* arrayList, int length) {

    int arrLen = 0;
    int ret = 0;

    if (length >= 3 && length <= 31) {
         
        arrLen = length;

        do { 
            ret= Discard_One_Outlier_ByGrubbs(arrayList, arrLen);
            if (ret > 0) arrLen--;

        } while (ret>0 && arrLen>0);

    }

    return (length-arrLen);

}


