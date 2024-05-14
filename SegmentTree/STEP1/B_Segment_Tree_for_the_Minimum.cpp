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
    long long val;

    Node()
    {
        // update this variable to a value that has no effect on the answer of the operation
        val = INT_MAX;
    }

    Node(long long x)
    {
        val = x;
    }
};

struct SegTree
{
    int tree_size;
    vector<Node> seg_data;
    SegTree(int n)
    {
        tree_size = 1;
        while (tree_size < n)
            tree_size *= 2;
        seg_data.resize(2 * tree_size, Node());
    }

    // update this function for the desired operation
    Node merge(Node &lf, Node &ri)
    {
        Node ans = Node();
        ans.val = min(lf.val, ri.val);
        return ans;
    }

    void init(vector<long long> &nums, int ni, int lx, int rx)
    {

        if (rx - lx == 1)
        {
            if (lx < (int)nums.size())
            {
                seg_data[ni] = Node(nums[lx]);
            }
            return;
        }

        int mid = lx + (rx - lx) / 2;
        init(nums, 2 * ni + 1, lx, mid);
        init(nums, 2 * ni + 2, mid, rx);

        seg_data[ni] = merge(seg_data[2 * ni + 1], seg_data[2 * ni + 2]);
    }

    void init(vector<ll> &nums)
    {
        init(nums, 0, 0, tree_size);
    }

    void set(int idx, long long value, int node, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            seg_data[node] = Node(value);
            return;
        }

        int mid = (lx + rx) / 2;
        if (idx < mid)
            set(idx, value, 2 * node + 1, lx, mid);
        else
            set(idx, value, 2 * node + 2, mid, rx);

        seg_data[node] = merge(seg_data[2 * node + 1], seg_data[2 * node + 2]);
    }
    void set(int idx, long long value) // zero indexed
    {
        set(idx, value, 0, 0, tree_size);
    }

    Node get_range(int l, int r, int node, int lx, int rx)
    {
        if (rx <= l || lx >= r)
            return Node();
        if (lx >= l && rx <= r)
            return seg_data[node];

        int mid = (lx + rx) / 2;

        Node lf = get_range(l, r, 2 * node + 1, lx, mid);
        Node ri = get_range(l, r, 2 * node + 2, mid, rx);
        return merge(lf, ri);
    }

    long long get_range(int l, int r) // zero indexed range and get from l to r-1, i.e [l,r)
    {
        return get_range(l, r, 0, 0, tree_size).val;
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

    for (int i = 0; i < n; i++)
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
            int mn = tree.get_range(l, r);
            cout << mn << endl;
        }
    }
    return 0;
}
