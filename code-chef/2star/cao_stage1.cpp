//https://www.codechef.com/practice/course/2-star-difficulty-problems/DIFF1500/problems/CAOS1

#include <iostream>

using namespace std;

bool cpc(int num,int *prime) {
    int i;
    for(i=0;i<9;i++)
        if(prime[i]<=num)
            return true;
    return false;
}

int main() {
    int t,r,c,count=0,L=0,T=0,B=0,R=0,i,j;
    std::cin >> t;
    int prime[] = {2,3,5,7,11,13,17,19,23};

    while(t--) {
        std::cin >> r >> c;
        char arr[r][c];
        count = 0;
        L=1,T=1,B=1,R=1;
        for(i=0;i<r;i++)
            for(j=0;j<c;j++)
                std::cin >> arr[i][j];

        for(i=0;i<r;i++) {
            for(j=0;j<c;j++)
                std::cout << arr[i][j];
            std::cout << '\n';
        }
    
        for(i=0;i<r;i++) {
            for(j=0;j<c;j++) {
                if(i!=0) {
                    int a=i;
                    while(a!=0 && arr[a][j]!='#') {
                        T++;
                        a--;
                    }
                }
                if(j!=0) {
                    int a=j;
                    while(a!=0 && arr[i][a]!='#') {
                        L++;
                        a--;
                    }
                }
                if(i!=r-1) {
                    int a=i;
                    while(a<r-1 && arr[a][j]!='#') {
                        B++;
                        a++;
                    }
                }
                if(j!=c-1) {
                    int a=j;
                    while(a<c-1 && arr[i][a]!='#') {
                        R++;
                        a++;
                    }
                }
        
                std::cout << "T="<<T<<" L="<<L<<" B="<<B<<" R="<<R<<'\n';
                if(cpc(min(min(min(L,T),B),R),prime))
                    count++;
                L=1,T=1,B=1,R=1;
            }
        }
        std::cout << count << '\n';
    }

    return 0;
}
