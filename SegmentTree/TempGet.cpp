#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("avx,avx2,fma")
#include <bits/stdc++.h>
#define b3dsh                \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0);
#define dpp(arr, val) memset(arr, val, sizeof(arr))
#define ll long long
#define ull unsigned long long
#define dd double
#define ld long double
#define PQ priority_queue
#define pii pair<int, int>
#define pll pair<ll, ll>
#define S second
#define F first
#define MP make_pair
#define endl "\n"
#define PI 3.14159265
#define mod 1000000007
#define tests   \
    ll t;       \
    cin >> t;   \
    ll i_t = 0; \
    while (i_t++ < t)
#define loop(n) for (ll i = 0; i < (n); i++)
#define SetPre(n, x) cout << fixed << setprecision(n) << x
#define forp(i, a, b) for (ll i = a; i < b; i++)
#define forn(i, a, b) for (ll i = a; i > b; i--)
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
#define trav(i, a) for (auto &i : a)
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define si(a) ((int)(a).size())
#define ins insert
#define pb push_back
#define sz(v) ((int)((v).size()))
#define clr(v, d) memset(v, d, sizeof(v))
#define rep(i, v) for (int i = 0; i < sz(v); ++i)
#define lp(i, n) for (int i = 0; i < (int)(n); ++i)
#define lpi(i, j, n) for (int i = (j); i < (int)(n); ++i)
#define lpd(i, j, n) for (int i = (j); i >= (int)(n); --i)

using namespace std;

const int N = 1e5 + 10;

int n, q;
int l, r;
ll cnt, x;

vector<int> seg_data(4 * N), a(N);
map<int, vector<int>> mp;

void init(int node, int lx, int rx)
{
    if (rx - lx == 1)
    {
        seg_data[node] = a[lx];
        return;
    }
    int mid = (lx + rx) / 2;
    init(2 * node, lx, mid);
    init(2 * node + 1, mid, rx);
    seg_data[node] = __gcd(seg_data[2 * node], seg_data[2 * node + 1]);
    return;
}

int get_range(int node, int lx, int rx, int l, int r)
{
    if (r <= lx || l >= rx)
        return 0;
    if (lx >= l && rx <= r)
        return seg_data[node];
    int mid = (lx + rx) / 2;
    ll lf = get_range(2 * node, lx, mid, l, r);
    ll rf = get_range(2 * node + 1, mid, rx, l, r);

    return __gcd(lf, rf);
}

int main()
{
    b3dsh;

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        mp[a[i]].push_back(i);
    }

    init(1, 0, n);
    cin >> q;

    while (q--)
    {
        cin >> l >> r;
        l--;
        x = get_range(1, 0, n, l, r);
        cout << r - l - x << endl;
    }
    return 0;
}
