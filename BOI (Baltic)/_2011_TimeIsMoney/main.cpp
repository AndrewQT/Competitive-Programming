
// Problem : BOI 2011 P5 - Time Is Money
// Contest : DMOJ
// URL : https://dmoj.ca/problem/boi2011p5
// Memory Limit : 64.000000 MB
// Time Limit : 1000.000000 milisec
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

int N, M;
pair<long long, int> srt[10005];
int u[10005], v[10005], par[205];
long long a[10005], b[10005];
pair<long long, long long> ans = {INT_MAX, INT_MAX};
pair<long long, long long> val = {0, 0};
vector<pair<int, int>> vec;

int getrt(int n){
	return par[n] = (par[n] == n ? n : getrt(par[n]));
}

pair<long long, long long> mst(const long long x, const long long y, bool bb = 0){
	for(int i = 1; i<=M; i++){
		srt[i] = make_pair(a[i]*x + b[i]*y, i);
	}
	sort(srt+1, srt+M+1);
	for(int i = 1; i<=N; i++){
		par[i] = i;
	}
	pair<long long, long long> ret = make_pair(0LL, 0LL);
	for(int i = 1; i<=M; i++){
		int pu = u[srt[i].second], pv = v[srt[i].second];
		pu = getrt(pu), pv = getrt(pv);
		if(pu != pv){
			ret.first += a[srt[i].second];
			ret.second += b[srt[i].second];
			if(bb){
				vec.push_back(make_pair(u[srt[i].second], v[srt[i].second]));
			}
			par[pu] = pv;
		}
	}
	return ret;
}

void solve(pair<long long, long long> l, pair<long long, long long> r, int c = 0){
	//cout << l.first << " " << l.second << " " << r.first << " " << r.second << endl;
	if(l == r || c > 10){
		return;
	}
	auto m = mst(l.second-r.second, r.first-l.first);
	if(m.first*m.second < ans.first*ans.second){
		ans = m;
		val = {l.second-r.second, r.first-l.first};
	}
	solve(l, m, c+1);
	solve(m, r, c+1);
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;
	for(int i = 1; i<=M; i++){
		cin >> u[i] >> v[i] >> a[i] >> b[i];
		u[i]++, v[i]++;
	}
	pair<long long, long long> sl = mst(1, 0);
	pair<long long, long long> sr = mst(0, 1);
	if(sl.first*sl.second <= sr.first*sr.second){
		ans = sl;
		val = {1, 0};
	}
	else{
		ans = sr;
		val = {0, 1};
	}
	solve(sl, sr);
	auto m = mst(val.first, val.second, 1);
	cout << m.first << " " << m.second << "\n";
	for(auto e : vec){
		cout << e.first-1 << " " << e.second-1 << "\n";
	}
}
