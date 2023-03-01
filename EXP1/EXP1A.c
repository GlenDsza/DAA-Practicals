#include <stdio.h>
 #include <stdlib.h>
 #include <math.h>
 
 int f1_n(int n){
   return n;
 }
 int f2_n_cube(int n){
   return n*n*n;
 }
 double f3_3_by_2_pow_n(int n){
   return pow(1.5, n);
 }
 double f4_ln_n(int n){
   return log(n);
 }
 double f5_ln_ln_n(int n){
   return log(log(n));
 }
 double f6_log2_n(int n){
   return log2(n);
 }
 double f7_log2_log2_n(int n){
   return log2(log2(n));
 }
 double f8_n_log2_n(int n){
   return n * log2(n);
 }
 long f9_2_pow_n(int n){
   return pow(2, n);
 }
 double f10_2_pow_log_n(int n){
   return pow(2, log2(n));
 }
 long f11_n_fact(long n){
   return ((n == 1 || n == 0) ? 1 : n * f11_n_fact(n - 1));
 }
 
 int main(){
   printf("n\tFunc1\tFunc2\t%-20s\tFunc4\tFunc5\tFunc6\tFunc7\tFunc8\t%-21s\tFunc10\tFunc11\n\n","Func3","Func9");
   for(int i=0; i <= 100; i++) {
       printf("%d\t", i);
       printf("%d\t", f1_n(i)); 
       printf("%d\t", f2_n_cube(i));
       printf("%-18.2f\t", f3_3_by_2_pow_n(i));
       printf("%.2f\t", f4_ln_n(i));
       printf("%.2f\t", f5_ln_ln_n(i));
       printf("%.2f\t", f6_log2_n(i));
       printf("%.2f\t", f7_log2_log2_n(i));
       printf("%.2f\t", f8_n_log2_n(i));
       printf("%-21ld\t", f9_2_pow_n(i));
       printf("%.2f\t", f10_2_pow_log_n(i));
       if(i<=20)
        printf("%ld", f11_n_fact(i));
       printf("\n");
   }
   return 0;
 }