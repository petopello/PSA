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
    std::vector<double> space(SIZE, 0.0);
    for (int i = 0; i < SIZE; ++i) {
        space[i] = i;
    }

    //create base
    std::vector<std::vector<int>> base(DIM, std::vector<int>(4));
    for (int i = 0; i < DIM; ++i) {
        int p = pow(3, DIM-i-1);
        base[i] = {p * 2, p * 1, p * -1, p * -2};
    }

    //loop for call SHN_naive with each point in space
    double value_naive = 0;
    std::array<int, DIM> coords = {};
    for (int index = 0; index < 10; ++index) {
        value_naive = SHN_naive(index, coords, space, RADIUS, base);
        std::cout << static_cast<long long>(value_naive) << std::endl;
        // update coords
        for (int i = DIM-1; i >= 0; --i) {
            if (++coords[i] < 3) break;
            coords[i] = 0;
        }
    }
    return 0;
}
