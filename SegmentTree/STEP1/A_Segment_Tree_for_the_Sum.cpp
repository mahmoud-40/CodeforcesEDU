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

struct Node
{
    ll sum;
    // each
    Node()
    { // for padding to nearest power 2
        sum = 0;
    }
    Node(int x)
    {
        sum = x;
    }
    // each
    void change(int x)
    {
        sum = x;
    }
};

struct SegTree
{
    int treeSize;
    vector<Node> SegData;

    SegTree(int n)
    {
        treeSize = 1;
        while (treeSize < n)
            treeSize *= 2;
        SegData.assign(2 * treeSize, Node());
    }
    // each
    void init(vector<ll> &ar, ll ni, ll lx, ll rx)
    {
        if (rx - lx == 1)
        {
            if (lx < ar.size())
                SegData[ni] = Node(ar[lx]);
            return;
        }
        ll mid = (rx + lx) / 2;
        init(ar, 2 * ni + 1, lx, mid);
        init(ar, 2 * ni + 2, mid, rx);

        SegData[ni] = merge(SegData[2 * ni + 1], SegData[2 * ni + 2]);
    }
    Node merge(Node &lf, Node &ri)
    { // get the parent of 2 nodes
        Node ans = Node();

        ans.sum = lf.sum + ri.sum;

        return ans;
    }
    void set(ll idx, ll val, ll ni, ll lx, ll rx)
    {
        if (rx - lx == 1)
        {
            SegData[ni].change(val); // or any operation
            return;
        }

        ll mid = (lx + rx) / 2;
        if (idx < mid)
        {
            set(idx, val, 2 * ni + 1, lx, mid); // go left
        }
        else
        {
            set(idx, val, 2 * ni + 2, mid, rx); // go right
        }

        SegData[ni] = merge(SegData[2 * ni + 1], SegData[2 * ni + 2]);
    }
    Node getRange(ll l, ll r, ll ni, ll lx, ll rx)
    {
        if (lx >= l && rx <= r)
            return SegData[ni];
        if (lx >= r || rx <= l)
            return Node();

        ll mid = (lx + rx) / 2;
        Node lf = getRange(l, r, 2 * ni + 1, lx, mid);
        Node ri = getRange(l, r, 2 * ni + 2, mid, rx);

        return merge(lf, ri);
    }
    ll traverse(ll k, ll ni, ll lx, ll rx)
    {
        if (rx - lx == 1)
        {
            return k;
        }
        ll ret = traverse(k + 1, 2 * ni + 1, lx, (rx + lx) / 2);
        return ret;
    }

    void set(ll idx, ll val)
    {
        if (0 <= idx && idx < treeSize)
            set(idx, val, 0, 0, treeSize);
    }
    ll getRange(ll l, ll r)
    {
        Node n = getRange(l, r, 0, 0, treeSize);
        return n.sum;
    }
    void init(vector<ll> &ar)
    {
        init(ar, 0, 0, treeSize);
    }
};

int main()
{
    b3dsh;

    ll n, q;
    cin >> n;
    cin >> q;

    // n = 1 << n;
    SegTree tree(n);
    vector<ll> a(n);

    loop(n)
    {
        cin >> a[i];
    }

    tree.init(a);

    while (q--)
    {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1)
        {
            tree.set(l, r);
        }
        else
        {
            ll sum = tree.getRange(l, r);
            cout << sum << endl;
        }
    }
    return 0;
}