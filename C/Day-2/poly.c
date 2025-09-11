#include <stdio.h>
#include <stdlib.h>
#define MAX 100
void inputPolynomial(int poly[],int degree){
for(int i=degree;i>=0;i--){
printf("Enter coefficient for x^%d:",i);
scanf("%d",&poly[i]);}
}

void addPolynomials(int poly1[],int poly2[],int result[],int max_deg){
for  (int i=0;i<=max_deg;i++)
result[i]=poly1[i]+poly2[i];}

void printpolynomial(int poly[],int deg)
{
int isFirst=1;
for(int i=deg;i>=0;i--){
if(poly[i]!=0){
if(!isFirst && poly[i]>0)
printf("+");
else if (poly[i]<0)
printf("-");
if(abs(poly[i])!=1||i==0)
printf("%d",isFirst?poly[i]:abs(poly[i]));
if(i>0){printf("x");
if(i>1)
printf("^%d",i);}
isFirst=0;
}}}

int main(){
int poly1[MAX]={0};
int poly2[MAX]={0};
int result[MAX]={0};
int deg1,deg2,max_deg;
printf("\nEnter degree of the first polynominal :");
scanf("%d",&deg1);
inputPolynomial(poly1,deg1);
printf("\nEnter degree of the Second polynominal :");
scanf("%d",&deg2);
inputPolynomial(poly2,deg2);
max_deg=(deg1>deg2)?deg1:deg2;
addPolynomials(poly1,poly2,result,max_deg);
printf("\nFirst Polynomial : ");
printpolynomial(poly1,deg1);
printf("\nSecond Polynomial : ");
printpolynomial(poly2,deg2);
printf("\nSum of the two polynomials : ");
printpolynomial(result,max_deg);
return 0;
}
