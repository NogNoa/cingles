#include <stdio.h>
//#include <string.h>
#include "stoi.lb.c"
void rcrs_itoa(int n, char s[]);

int main(int argc, char *argv[])
{
    int n;
    char s[1024];

    scanf("%d",&n);

    rcrs_itoa(n,s);
    rcrs_reverse(0,s);
    printf("%s\n",s);
    
    return 0;

}
