#include <bits/stdc++.h>
using namespace std;
struct WaterTank{
    bool check(vector<int> &t, vector<int> &x, int C, double v) {
        double current = 0;
        int n = t.size();
        for (int i = 0; i < n; i++) {
            double rate = x[i] - v;
            current += rate * t[i];
            if (current < 0) current = 0;
            if (current > C) return false;
        }
        return true;
    }
    double minOutputRate(vector<int> t, vector<int> x, int C) {
        double maxVal = 1e10, minVal = 0;
        while (maxVal - minVal > 1e-8) {
            double mid = (maxVal + minVal) / 2;
            if (check(t, x, C, mid)) maxVal = mid;
            else minVal = mid;
        }
        return maxVal;
    }
};
