#include <bits/stdc++.h>

using namespace std;

struct point{
    long long x, y, z, t;
    vector<int> v;
    bool operator < (point p) const{
        return abs(x) + abs(y) + abs(z) < abs(p.x) + abs(p.y) + abs(p.z);
    }

};

int N, K, M = 300000;
long long fact[300005], inv[300005];
point arr[5005];
long long dp[5005];
long long tbl[5005][5005];
long long tot[5005];
long long MOD = 1e9+7;
set<pair<pair<int, int>, int>> st;

int which(int n){
    if(n > 0){
        return 1;
    }
    if(n < 0){
        return -1;
    }
    return 0;
}

bool sameoctant(int i, int j){
    bool ret = 1;
    for(int k = 0; k<3; k++){
        ret &= !((arr[i].v[k] == -1 && arr[j].v[k] == 1) || (arr[i].v[k] == 1 && arr[j].v[k] == -1));
    }
    ret &= (abs(arr[i].x) >= abs(arr[j].x));
    ret &= (abs(arr[i].y) >= abs(arr[j].y));
    ret &= (abs(arr[i].z) >= abs(arr[j].z));
    return ret;
}

long long mult(long long a, long long b){
    return (a*b)%MOD;
}

long long add(long long a, long long b){
    return (a+b)%MOD;
}

long long sub(long long a, long long b){
    a = add(a, -b);
    if(a < 0){
        a += MOD;
    }
    return a;
}

long long qikpow(long long b, long long e){
    if(!e){
        return 1;
    }
    long long ret = qikpow(b, e>>1);
    ret = mult(ret, ret);
    if(e&1){
        ret = mult(ret, b);
    }
    return ret;
}

long long divd(long long a, long long b){
    return mult(a, qikpow(b, MOD-2));
}

long long combo(long long a, long long b, long long c){
    return mult(fact[a+b+c], mult(inv[a], mult(inv[b], inv[c])));
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    fact[0] = inv[0] = 1;
    for(int i = 1; i<=M; i++){
        fact[i] = mult(i, fact[i-1]);
        inv[i] = divd(1, fact[i]);
    }
    cin >> N >> K;
    for(int i =1 ; i<=N; i++){
        cin >> arr[i].x >> arr[i].y >> arr[i].z >> arr[i].t;
        arr[i].v.resize(3);
        arr[i].v[0] = which(arr[i].x);
        arr[i].v[1] = which(arr[i].y);
        arr[i].v[2] = which(arr[i].z);
    }
    sort(arr+1, arr+1+N);
    for(int i = 1; i<=N; i++){
        dp[i] = combo(abs(arr[i].x), abs(arr[i].y), abs(arr[i].z));
        tot[i] = dp[i];
        for(int j = 1; j<i; j++){
            //cout << sameoctant(i, j) << endl;
            //cout << arr[j].t << " " << arr[i].t << endl;
            int dx = abs(arr[i].x-arr[j].x);
            int dy = abs(arr[i].y-arr[j].y);
            int dz = abs(arr[i].z-arr[j].z);
            if(arr[j].t != arr[i].t && sameoctant(i, j)){
                cout << " " << i << " " << j << " " << tot[j] << " " << tbl[j][arr[i].t] << endl;
                dp[i] = sub(dp[i], mult(add(tot[j], tbl[j][arr[i].t]), combo(dx, dy, dz)));
            }
            if(sameoctant(i, j)){
                long long temp = mult(tot[j], combo(dx, dy, dz));
                tot[i] = sub(tot[i], temp);
                tbl[i][arr[j].t] = add(tbl[i][arr[j].t], temp);
            }
        }
    }
    long long ans = 1;
    for(int k = 1; k<=K; k++){
        long long t = 0;
        for(int n = 1; n<=N; n++){
            if(arr[n].t == k){
                t = add(t, dp[n]);
            }
        }
        ans = mult(ans, t);
    }
    cout << ans << endl;
}
