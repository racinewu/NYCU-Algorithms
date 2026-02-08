#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <cfloat>

using namespace std;

struct Point
{
    double x, y;
};

double calcDistance(const Point &p1, const Point &p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

double Brute(vector<Point> &points, int left, int right)
{
    double minDist = DBL_MAX;
    for (int i = left; i < right; ++i)
    {
        for (int j = i + 1; j <= right; ++j)
        {
            minDist = min(minDist, calcDistance(points[i], points[j]));
        }
    }
    return minDist;
}

// Minimum in strip
double stripClosest(vector<Point> &strip, double d)
{
    double minDist = d;

    // Sort y
    sort(strip.begin(), strip.end(),
         [](const Point &a, const Point &b)
         { return a.y < b.y; });

    // In strip
    for (int i = 0; i < strip.size(); ++i)
    {
        for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; ++j)
        {
            minDist = min(minDist, calcDistance(strip[i], strip[j]));
        }
    }

    return minDist;
}

// Recursion divide and conquer
double closestUtil(vector<Point> &points, int left, int right)
{
    if (right - left <= 3)
    {
        return Brute(points, left, right);
    }

    int mid = left + (right - left) / 2;
    Point midPoint = points[mid];

    double dl = closestUtil(points, left, mid);
    double dr = closestUtil(points, mid + 1, right);
    double d = min(dl, dr);

    // Points in strip
    vector<Point> strip;
    for (int i = left; i <= right; ++i)
    {
        if (abs(points[i].x - midPoint.x) < d)
        {
            strip.push_back(points[i]);
        }
    }

    // Find closest points in strip
    return min(d, stripClosest(strip, d));
}

// Main function to find closest pair
double findClosestPair(vector<Point> &points)
{
    // Sort by x
    sort(points.begin(), points.end(),
         [](const Point &a, const Point &b)
         { return a.x < b.x; });

    // Call recursive utility function
    return closestUtil(points, 0, points.size() - 1);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    short T;
    cin >> T;

    for (int t = 0; t < T; ++t)
    {
        int n;
        cin >> n;

        vector<Point> points(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> points[i].x >> points[i].y;
        }

        double minDistance = findClosestPair(points);
        cout << fixed << setprecision(6) << minDistance << '\n';
    }

    return 0;
}