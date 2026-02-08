#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

void processOBST(int N, const vector<int> &keys, const vector<int> &freq)
{
    vector<int> sum(N + 1);
    for (int i = 0; i < N; ++i)
        sum[i + 1] = sum[i] + freq[i];

    vector<vector<int>> cost(N, vector<int>(N, 0));
    vector<vector<int>> root(N, vector<int>(N, 0));

    for (int i = 0; i < N; ++i)
    {
        cost[i][i] = freq[i];
        root[i][i] = i;
    }

    // Knuth's optimization
    for (int L = 2; L <= N; ++L)
    {
        for (int i = 0; i <= N - L; ++i)
        {
            int j = i + L - 1;
            cost[i][j] = numeric_limits<int>::max();

            int kStart = (i + 1 <= j) ? root[i][j - 1] : i;
            int kEnd = (i <= j - 1) ? root[i + 1][j] : j;

            for (int r = kStart; r <= kEnd; ++r)
            {
                int c = (r > i ? cost[i][r - 1] : 0) +
                        (r < j ? cost[r + 1][j] : 0) +
                        sum[j + 1] - sum[i];
                if (c < cost[i][j])
                {
                    cost[i][j] = c;
                    root[i][j] = r;
                }
            }
        }
    }

    // Level order traversal without building full tree
    vector<int> result;
    queue<pair<int, int>> q;
    q.emplace(0, N - 1);

    while (!q.empty())
    {
        auto [l, r] = q.front();
        q.pop();
        if (l > r)
        {
            result.push_back(-1);
            continue;
        }
        int k = root[l][r];
        result.push_back(keys[k]);
        q.emplace(l, k - 1);
        q.emplace(k + 1, r);
    }

    while (!result.empty() && result.back() == -1)
        result.pop_back();

    for (size_t i = 0; i < result.size(); ++i)
    {
        cout << result[i];
        if (i + 1 < result.size())
            cout << ' ';
    }
    cout << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        vector<int> keys(N), freq(N);
        for (int &k : keys)
            cin >> k;
        for (int &f : freq)
            cin >> f;
        processOBST(N, keys, freq);
    }
    return 0;
}
