#include <iostream>
#include <set>
#include <string>
#include <stdlib.h>
using namespace std;

typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<ll, ll> ipair;
#define mod 1000000007
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define sz size()
#define ln length()
#define rep(i,n) for(i=0;i<n;i++)
#define fu(i,a,n) for(i=a;i<=n;i++)
#define fd(i,n,a) for(i=n;i>=a;i--)
#define all(a)  a.begin(),a.end()
#define gi(n) scanf("%d",&n)
#define gl(n) scanf("%lld",&n)
#define pi(n) printf("%d",n)
#define pl(n) printf("%lld",n);
#define pp printf(" ")
#define pn printf("\n")
#define MAXN 50000
#define LN 26

char s[100];
int ctr = 1;
int id;
struct node {
	bool isLeaf;
	int pr;		//priority
	int cnt;	// cnt
	int ch[26];	// child index
	node() {
		isLeaf = false;
		pr = 10000000;
		cnt = 0;
		int i;
		rep(i, LN) {
			ch[i] = 0;
		}
	}
} tree[MAXN];

void insert() {
	int l = strlen(s);
	int cur = 1;
	int i;
	rep(i, l) {
		tree[cur].cnt++;
		tree[cur].pr = min(tree[cur].pr, id);
		int nxt = s[i] - 'a';
		if(!tree[cur].ch[nxt]) {
			tree[cur].ch[nxt] = ++ctr;
		}
		cur = tree[cur].ch[nxt];
	}
	tree[cur].pr = min(tree[cur].pr, id);
	tree[cur].isLeaf = true;
}

void getLowest(int cur, string str, set<pair<int, string> > &st) {
	if(tree[cur].isLeaf) {
		st.insert(mp(tree[cur].pr, str));
		if(st.size() > 4) {
			st.erase(--(st.end()));
		}
	}
	int i;
	rep(i, LN) {
		if(tree[cur].ch[i]) {
			getLowest(tree[cur].ch[i], str + (char)(i + 'a'), st);
		}
	}
}
void getSearch() {
	int l = strlen(s);
	string str = "";
	int cur = 1;
	int i;
	rep(i, l) {
		str+=s[i];
		int nxt = s[i] - 'a';
		if(!tree[cur].ch[nxt]) {
			cout << "No search found" << endl;
			return;
		}
		cur = tree[cur].ch[nxt];
	}
	set<pair<int, string> > st;
	getLowest(cur, str, st);
	set<pair<int, string> > :: iterator it;
	for(it = st.begin(); it != st.end(); it++) {
		cout << it->ss << endl;
	}
	
}

int main(int argc, char *argv[]) {
	FILE *fp;
	fp = fopen("english.txt", "r");
	while(fscanf(fp, "%s %d", s, &id) != EOF) {
		insert();
	}
	fclose(fp);
	cout << "Suggestion for 1st word" << endl;
	strcpy(s, argv[1]);
	getSearch();
	cout << "Suggestion for 2nd word" << endl;
	strcpy(s, argv[2]);
	getSearch();
	cout << "Suggestion for 3rd word" << endl;
	strcpy(s, argv[3]);
	getSearch();
	return 0;
}