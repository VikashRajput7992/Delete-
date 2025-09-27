#include<bits/stdc++.h>
using namespace std;

using cd = complex<double>;
const double PI = acos(-1);

vector<cd> dft(vector<cd>& p, int n){
    if(n==1) return p;

    vector<cd> pe(n/2), po(n/2);
    for(int i=0;i<n/2;i++){
        pe[i] = p[i*2];
        po[i] = p[i*2+1];
    }
    pe = dft(pe,n/2);
    po = dft(po,n/2);

    double ang = 2*PI/n; 
    cd w(1,0), w_delta(cos(ang), sin(ang));

    for(int i=0;i<n/2;i++){
        p[i] = pe[i] + w*po[i];
        p[i+n/2] = pe[i] - w*po[i];
        w = w*w_delta;
    }
    return p;  
}

vector<cd> idft(vector<cd>& p, int n){
    if(n==1) return p;

    vector<cd> pe(n/2), po(n/2);
    for(int i=0;i<n/2;i++){
        pe[i] = p[i*2];
        po[i] = p[i*2+1];
    }
    pe = idft(pe,n/2);
    po = idft(po,n/2);

    double ang = -2*PI/n; 
    cd w(1,0), w_delta(cos(ang), sin(ang));

    for(int i=0;i<n/2;i++){
        p[i] = pe[i] + w*po[i];
        p[i+n/2] = pe[i] - w*po[i];
        w = w*w_delta;
    }
    return p;  
}

vector<long long> fft(const vector<int>& a, const vector<int>& b){
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while(n < a.size() + b.size()) n<<=1;
    fa.resize(n);
    fb.resize(n);

    fa = dft(fa,n);
    fb = dft(fb,n);

    for(int i=0;i<n;i++) fa[i] *= fb[i];

    fa = idft(fa,n);

    vector<long long> res(n);
    for(int i=0;i<n;i++) res[i] = round(fa[i].real()/n);
    return res;
}

void solve()
{
    int n;cin>>n;
    vector<int> a(n+1),b(n+1);
    for(int i=0;i<=n;i++) cin>>a[i];
    for(int i=0;i<=n;i++) cin>>b[i];

    vector<long long> res = fft(a, b);
    for(int i=0;i<=2*n;i++) cout<<res[i]<<" ";
    cout<<endl;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;cin>>t;
    while(t--) solve();
    return 0;
}
