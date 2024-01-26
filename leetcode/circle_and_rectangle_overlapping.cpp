//https://leetcode.com/problems/circle-and-rectangle-overlapping/

#include <iostream>

using namespace std;

class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
        int nearestX = max(x1,min(x2,xCenter));
        int nearestY = max(y1,min(y2,yCenter));

        int xdist = nearestX - xCenter;
        int ydist = nearestY - yCenter;

        int distance = (xdist*xdist) + (ydist*ydist);

        if(distance <= radius*radius)
            return true;
        else
            return false;
    }
};

int main() {
    Solution s;
    std::cout << s.checkOverlap(1415,807,-784,-733,623,-533,1005) << '\n';
}
