// Some weird stuff. Maybe I understand it later (not sure I'll return, actually)

#include <iostream>
#include <vector>
#include <string>


class DigitSequenceManager {
private:
    struct SegmentNode {
        char symbol;
        int rand_priority;
        int total_weight;
        int left_idx;
        int right_idx;
        char leftmost_sym;
        char rightmost_sym;
        bool contains_drop;
        int drop_position;
    };

    std::vector<SegmentNode> _nodes_pool;
    int _tree_root;

    void refresh(int v) {
        if (!v) { return; }
        int L = _nodes_pool[v].left_idx;
        int R = _nodes_pool[v].right_idx;

        _nodes_pool[v].total_weight = 1 + _nodes_pool[L].total_weight + _nodes_pool[R].total_weight;
        _nodes_pool[v].leftmost_sym = L ? _nodes_pool[L].leftmost_sym : _nodes_pool[v].symbol;
        _nodes_pool[v].rightmost_sym = R ? _nodes_pool[R].rightmost_sym : _nodes_pool[v].symbol;

        if (L && _nodes_pool[L].contains_drop) {
            _nodes_pool[v].contains_drop = true;
            _nodes_pool[v].drop_position = _nodes_pool[L].drop_position;
        } else if (L && _nodes_pool[L].rightmost_sym < _nodes_pool[v].symbol) {
            _nodes_pool[v].contains_drop = true;
            _nodes_pool[v].drop_position = _nodes_pool[L].total_weight;
        } else if (R && _nodes_pool[v].symbol < _nodes_pool[R].leftmost_sym) {
            _nodes_pool[v].contains_drop = true;
            _nodes_pool[v].drop_position = _nodes_pool[L].total_weight + 1;
        } else if (R && _nodes_pool[R].contains_drop) {
            _nodes_pool[v].contains_drop = true;
            _nodes_pool[v].drop_position = _nodes_pool[L].total_weight + 1 + _nodes_pool[R].drop_position;
        } else {
            _nodes_pool[v].contains_drop = false;
            _nodes_pool[v].drop_position = 0;
        }
    }

    void partition(int v, int k, int& l, int& r) {
        if (!v) {
            l = r = 0;
            return;
        }
        int left_sz = _nodes_pool[_nodes_pool[v].left_idx].total_weight;
        if (left_sz >= k) {
            partition(_nodes_pool[v].left_idx, k, l, _nodes_pool[v].left_idx);
            r = v;
        } else {
            partition(_nodes_pool[v].right_idx, k - left_sz - 1, _nodes_pool[v].right_idx, r);
            l = v;
        }
        refresh(v);
    }

    void unify(int& v, int l, int r) {
        if (!l || !r) {
            v = (l ? l : r);
            return;
        }
        if (_nodes_pool[l].rand_priority > _nodes_pool[r].rand_priority) {
            unify(_nodes_pool[l].right_idx, _nodes_pool[l].right_idx, r);
            v = l;
        } else {
            unify(_nodes_pool[r].left_idx, l, _nodes_pool[r].left_idx);
            v = r;
        }
        refresh(v);
    }

public:
    DigitSequenceManager() {
        SegmentNode dummy = {0, 0, 0, 0, 0, 0, 0, false, 0};
        _nodes_pool.push_back(dummy);
        _tree_root = 0;
    }

    void buildFromSequence(const std::string_view str) {
        for (char c : str) {
            SegmentNode node;
            node.symbol = c;
            node.rand_priority = rand() ^ (rand() << 15);
            node.total_weight = 1;
            node.left_idx = 0;
            node.right_idx = 0;
            node.leftmost_sym = c;
            node.rightmost_sym = c;
            node.contains_drop = false;
            node.drop_position = 0;

            _nodes_pool.push_back(node);
            int nv = _nodes_pool.size()-1;
            unify(_tree_root, _tree_root, nv);
        }
    }

    char extractCharacter(int pos) {
        int L, mid, R;
        partition(_tree_root, pos-1, L, R);
        partition(R, 1, mid, R);
        char res = _nodes_pool[mid].symbol;
        unify(R, mid, R);
        unify(_tree_root, L, R);
        return res;
    }
    
    void eliminateTarget() {
        int pos = _nodes_pool[_tree_root].contains_drop ? _nodes_pool[_tree_root].drop_position : _nodes_pool[_tree_root].total_weight;
        int L, mid, R;
        partition(_tree_root, pos-1, L, R);
        partition(R, 1, mid, R);
        unify(_tree_root, L, R);
    }
};


int main() {
    std::string x;
    std::cin >> x;
    int m;
    std::cin >> m;

    struct QueryInfo {
        int l;
        int id;
    };

    int n = x.length();
    std::vector<std::vector<QueryInfo>> queries_by_k(n+1);
    for (int i = 0; i < m; ++i) {
        int k, l;
        std::cin >> k >> l;
        queries_by_k[k].push_back({l, i});
    }

    std::string final_answers(m, ' ');
    DigitSequenceManager mn;
    mn.buildFromSequence(x);
    
    for (int current_k = n; current_k >= 1; --current_k) {
        for (const auto& q : queries_by_k[current_k]) {
            final_answers[q.id] = mn.extractCharacter(q.l);
        }
        if (current_k > 1) {
            mn.eliminateTarget();
        }
    }
    
    std::cout << final_answers << std::endl;
    return 0;
}
