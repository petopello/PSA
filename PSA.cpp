#include <vector>
#include <stdexcept>
#include <iostream>
using namespace std;

vector<double> SHN_PSA(const vector<double>& space, const vector<int>& q, int r){
    //restrictions
    int len_q = q.size();
    int len_s = space.size();
    int prod_q = 1;
    for (int val : q){prod_q *= val;}
    if (len_s != prod_q){throw invalid_argument("len(space) == prod(q)");}
    if (len_q < r){throw invalid_argument("0 <= r <= len(q)");}
    for (int val : q){if (val<=1) throw invalid_argument("q[i]>1"); }
    //getbase(q)
    vector<vector<int>> base(len_q);
    int cumprod=1;
    for(int i = len_q - 1; i >= 0; --i){
        base[i].resize(q[i]);
        for(int n = q[i], j = 0; n > 0; --n, ++j){base[i][j]=n*cumprod;}
        cumprod*=q[i];
    }
    //PSA
    vector<double> sum = space;
    vector<double> aux(len_s);
    vector<vector<double>> acum(len_q, space);
    for (int n=0; n<r; ++n) {
        fill(aux.begin(), aux.end(), 0.0);
        for (int i=n; i<len_q; ++i) {
            //basic transformation, same result as numpy functions reshape+roll+flatten
            //TODO: take non-dependent variables out of deep loops
            int t = 0;
            vector<int> indices(base[i].begin()+1, base[i].end());
            while (t<len_s) {
                for (int k=0; k<indices.size(); indices[k]-=base[i][0], k++) {
                    for (int j=0; j<base[i].back(); ++j, t++) {
                        for (int idx=0; idx<indices.size(); indices[idx]++, ++idx){aux[t]+=acum[i-n][indices[idx]];}
                    }
                }
                for (int j=0; j<base[i].back(); ++j, t++) {
                    for (int idx=0; idx<indices.size(); indices[idx]++, ++idx){aux[t]+=acum[i-n][indices[idx]];}
                }
                for(int &index:indices){index += base[i][0];}
            }
            acum[i-n]=aux;
        }
        for (size_t j=0; j<sum.size(); ++j){sum[j]+=acum[len_q-n-1][j];}
    }
    return sum;
}

int main(){
    int r=4;
    vector<int> q = {3,3,3,3,3,3,3,3,3,3,3,3,3,3};
    //vector<int> q = {2,3};
    int prod_q = 1;
    for (int val : q){prod_q *= val;}
    //create space
    vector<double> space(prod_q, 0.0);
    for (int i=0; i<prod_q; ++i) {space[i]=i;}

    vector<double> shn = SHN_PSA(space, q, r);
    for (int i = 0; i < 10; ++i) {
        cout << static_cast<long long>(shn[i]) << endl;
    }

    //TODO: implement function for symMetric space

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
