#include <cstdio>
//#include <cmath>
//#include <cstdlib>
//#include <cstring>

//#include <string>
//#include <sstream>
//#include <map>
//#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <functional>
#include <iterator>

//#define min(a, b) ((a) < (b) ? (a) : (b))
//#define max(a, b) ((a) > (b) ? (a) : (b))

//using namespace std;

class data_t {
public:
    int w, s, id;
    data_t(int w, int s, int id) : w(w), s(s), id(id) {};
    bool operator<(const data_t &that) const {
        if (this->w != that.w)
            return this->w < that.w ? true : false;
        else
            return this->s < that.s ? true : false;
    }
};

std::vector<data_t> v;
std::pair<int, int> dp[1024];
int prev[1024], l;

bool cmp(const std::pair<int, int> &lhs,
         const std::pair<int, int> &rhs) {
    return (lhs.first > rhs.first ? true : false);
}

int main(int argc, char *argv[]) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int w, s, id = 1;
    while (scanf("%d %d", &w, &s) != EOF)
        v.push_back(data_t(w, s, id++));
    std::sort(v.begin(), v.end());

    int size = v.size();
    dp[0].second = -1, dp[1].first = v[0].s, dp[1].second = 0, prev[1] = -1, l = 2;
    for (int i = 1; i < size; i++) {
        s = v[i].s;

        if (s < dp[l - 1].first) {
            prev[i] = dp[l - 1].second;
            dp[l].first = s;
            dp[l++].second = i;
        } else {
            std::pair<int, int> *k = std::lower_bound(dp + 1, dp + l, std::pair<int, int>(s, 0), cmp);
            prev[i] = (*(k - 1)).second;
            (*k).first = s;
            (*k).second = i;
        }
    }

    printf("%d\n", l - 1);

    std::vector<int> ans;
    for (int i = dp[l - 1].second; i != -1; i = prev[i])
        ans.push_back(v[i].id);
    std::reverse(ans.begin(), ans.end());

    for (std::vector<int>::iterator iter = ans.begin(); iter != ans.end(); iter++)
        printf("%d\n", *iter);

    printf("kdfd!");


    return 0;
}
