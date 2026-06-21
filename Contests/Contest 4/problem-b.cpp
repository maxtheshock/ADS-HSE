// This billboard task designed to work with modified SegmentTree data structure.

#include <iostream>
#include <vector>
#include <algorithm>


class BillboardManager {
    std::vector<int> _tree;
    int _width;
    int _rows;

    void build(int node, int tl, int tr) {
        if (tl == tr) {
            _tree[node] = _width;
            return;
        }
        int tm = (tl + tr) / 2;
        build(2*node, tl, tm);
        build(2*node + 1, tm+1, tr);
        _tree[node] = std::max(_tree[2*node], _tree[2*node + 1]);
    }

    int reqAndRefresh(int node, int tl, int tr, int req_width) {
        if (_tree[node] < req_width) {
            return -1;
        }
        if (tl == tr) {
            _tree[node] -= req_width;
            return tl;
        }
        int tm = (tl + tr) / 2;
        int result;

        if (_tree[2*node] >= req_width) {
            result = reqAndRefresh(2*node, tl, tm, req_width);
        } else {
            result = reqAndRefresh(2*node + 1, tm+1, tr, req_width);
        }

        _tree[node] = std::max(_tree[2*node], _tree[2*node + 1]);
        return result;
    }

public:
    BillboardManager(int rows, int width) : _width(width), _rows(rows) {
        _tree.assign(4*rows + 1, 0);
        build(1, 1, rows);
    }

    int placeAnnouncement(int req_width) {
        return reqAndRefresh(1, 1, _rows, req_width);
    }
};

int main() {
    int h, w, n;
    std::cin >> h >> w >> n;

    int affected_rows = std::min(h, n);
    BillboardManager billboard(affected_rows, w);
    for (int i = 0; i < n; ++i) {
        int req_w;
        std::cin >> req_w;
        std::cout << billboard.placeAnnouncement(req_w) << "\n";
    }

    return 0;
}
