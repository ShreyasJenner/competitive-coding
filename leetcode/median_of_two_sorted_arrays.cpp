#include <vector>
#include <iostream>

class Solution {
public:
    double findMedian(std::vector<int>& nums1, std::vector<int>& nums2) {
       int size = nums1.size()+nums2.size();
       int c=0;
       double temp;
       auto i = nums1.begin();
       auto j = nums2.begin();
       while(c!=size/2) {
           if(*i < *j) {
               temp = *i;
               i++;
           } else {
               temp = *j;
               j++;
           }
           c++;
       }

       if(size%2==1) {
           if(*i<*j)
               return *i;
           else
               return *j;
        }
       else {
           if(*i<*j)
               return double(temp + *i)/2;
           else
               return double(temp + *j)/2;
       }
    }
};

int main() {
    std::vector<int> a1,a2;
    int m,n,tmp;

    std::cin >> m;
    for(int i=0;i<m;i++) {
        std::cin >> tmp;
        a1.push_back(tmp);
    }
    std::cin >> n;
    for(int i=0;i<n;i++) {
        std::cin >> tmp;
        a2.push_back(tmp);
    }


    Solution s;
    double ans = s.findMedian(a1,a2);
    std::cout << ans << '\n';
}
