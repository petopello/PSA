#include <vector>
#include <stdexcept>
#include <iostream>
using namespace std;

//basic transformation (oscillating shift), same result as using numpy functions reshape+roll+flatten
void apply_diff(int shift, int group, const vector<double>& read, vector<double>& write) {
    int unshift = group - shift;
    double* pwrite   = write.data();
    const double* pread   = read.data() + shift;
    const double* end = pwrite + write.size();
    const double* block;
    while (pwrite < end) {
        block = pwrite + unshift;
        while (pwrite < block) {*pwrite++ += *pread++;}
        pread -= group;
        block = pwrite + shift;
        while (pwrite < block) {*pwrite++ += *pread++;}
        pread += group;
    }
}

vector<double> SHN_PSA(const vector<double>& space, const vector<int>& q, int r){
    //restrictions
    int prod_q = 1; for (int val : q){prod_q*=val;}
    if (space.size() != prod_q){throw invalid_argument("len(space) == prod(q)");}
    if (q.size() < r){throw invalid_argument("0 <= r <= len(q)");}
    for (int val : q){if (val<=1) throw invalid_argument("q[i]>1"); }
    //getbase(q)
    vector<vector<int>> base(q.size());
    int cumprod=1;
    for(int i = q.size() - 1; i >= 0; --i){
        base[q.size()-1-i].resize(q[i]);
        for(int n = q[i], j = 0; n > 0; --n, ++j){base[q.size()-1-i][j]=n*cumprod;}
        cumprod*=q[i];
    }
    //PSA
    vector<double> sum = space;
    vector<double> aux(space.size());
    vector<vector<double>> acum(q.size(), space);
    for(int n=0; n<r; ++n){
        fill(aux.begin(), aux.end(), 0.0);
        for(int i=n; i<q.size(); ++i){
            for(int k=1; k<base[i].size(); ++k){
                apply_diff(base[i][k], base[i][0], acum[i-n], aux);
            }
            acum[i-n]=aux;
        }
        for(size_t j=0; j<space.size(); ++j){sum[j]+=aux[j];}
    }
    return sum;
}

int main(){
    //inputs
    int r=4;
    vector<int> q = {3,3,3,3,3,3,3,3,3,3,3,3,3,3};
    //vector<int> q = {2,2,2,2,2,10000};
    //vector<int> q = {10000,2,2,2,2,2};
    int prod_q = 1;
    for (int val : q){prod_q*=val;}
    vector<double> space(prod_q, 0.0);
    for (int i=0; i<prod_q; ++i){space[i]=i;}
    
    //output
    vector<double> shn = SHN_PSA(space, q, r);
    for (int i = 0; i < 10; ++i){cout << static_cast<long long>(shn[i]) << endl;}

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
