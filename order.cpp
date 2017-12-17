#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
int find(char c, char *st, int s, int e){
	for (int i=s; i<=e; ++i)
		if (c == st[i])
			return i;
	return s;
}
void trans(char *pre, int ps, int pe, char *mid, int ms, int me){
	if (ms > me)
		return;
	if (ms == me){
		cout << mid[ms];
		return;
	}
	int k = find(pre[ps], mid, ms, me);
	trans(pre, ps + 1, ps + k - ms, mid, ms, k-1);
	trans(pre, ps + k - ms + 1, pe, mid, k+1, me);
	cout << pre[ps];
}
int main(){
	char pre[] = "abdc";
	char mid[] = "bdac";
	trans(pre, 0, strlen(pre)-1, mid, 0, strlen(mid)-1);
	cout << endl;
	return 0;
}

