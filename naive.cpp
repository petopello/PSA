#include <iostream>
#include <vector>
#include <array>
#include <cmath>
using namespace std;

constexpr int DIM = 14;
constexpr int SIZE = 4782969;  // 3^DIM
constexpr int RADIUS = 4;

double SHN_naive(int index, array<int, DIM> coords, const vector<double>& space, int r, const vector<vector<int>>& base, int min = 0) {
    double acum = space[index];
    if (r > 1) {
        for (size_t i = min; i < base.size(); ++i) {
            for (int b = coords[i]; b < coords[i] + 2; ++b) {
                acum += SHN_naive(index + base[i][b], coords, space, r - 1, base, i + 1);
            }
        }
    } else {
        for (size_t i = min; i < base.size(); ++i) {
            for (int b = coords[i]; b < coords[i] + 2; ++b) {
                acum += space[index + base[i][b]];
            }
        }
    }
    return acum;
}

int main() {
    //create space
    vector<double> space(SIZE, 0.0);
    for (int i = 0; i < SIZE; ++i) {
        space[i] = i;
    }
    //create base
    vector<vector<int>> base(DIM, vector<int>(4));
    for (int i = 0; i < DIM; ++i) {
        int p = pow(3, DIM-i-1);
        base[i] = {p * 2, p * 1, p * -1, p * -2};
    }
    //loop for call SHN_naive with each point in space
    double value_naive = 0;
    array<int, DIM> coords = {};
    for (int index = 0; index < 10; ++index) {
        value_naive = SHN_naive(index, coords, space, RADIUS, base);
        cout << static_cast<long long>(value_naive) << endl;
        // update coords
        for (int i = DIM-1; i >= 0; --i) {
            if (++coords[i] < 3) break;
            coords[i] = 0;
        }
    }

    /*PRINT
    18847285404
    18847296844
    18847308284
    18847319724
    18847331164
    18847342604
    18847354044
    18847365484
    18847376924
    18847388364
    */

    return 0;
}
