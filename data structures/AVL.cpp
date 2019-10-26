#include <iostream>
#include <vector>

class AVL{
private:
    struct node{
        int key;
        int index; // for print
        int height;
        node *l, *r;
        node () : height(1), index(0), l(nullptr), r(nullptr) {}
        node (int key) : key(key), index(0), height(1), l(nullptr), r(nullptr) {}
    };

    node *root;
    int size_of_tree;

    void build_tree(node *&v, int norm_v, const std::vector<int> &values, const std::vector<std::pair<int, int>> &g) {
        v = new node(values[norm_v]);

        if (g[norm_v].first != -1) {
            build_tree(v->l, g[norm_v].first, values, g);
        }

        if (g[norm_v].second != -1) {
            build_tree(v->r, g[norm_v].second, values, g);
        }
    }

    void make_height(node *&v) {
        if (v->l != nullptr) {
            make_height(v->l);
        }

        if (v->r != nullptr) {
            make_height(v->r);
        }

        v = balancing(v);   ///All v != nullptr because we begin this fun, when values.size() > 0
    }

    void fix_balance(node *v) {
        v->height = std::max(get_height(v->l), get_height(v->r)) + 1;
    }

    void make_index(node *v, int &cnt) {
        v->index = cnt++;

        if (v->l != nullptr) {
            make_index(v->l, cnt);
        }

        if (v->r != nullptr) {
            make_index(v->r, cnt);
        }
    }

    void print_all_tree(const node *v) {
        std::cout << v->key << " ";
        std::cout << (v->l ? v->l->index + 1 : 0) << " ";
        std::cout << (v->r ? v->r->index + 1 : 0) << " " << v->height << std::endl;

        if (v->l != nullptr) {
            print_all_tree(v->l);
        }

        if (v->r != nullptr) {
            print_all_tree(v->r);
        }
    }

    node* rotate_left(node *v) {
        node *temp = v->r;
        v->r = temp->l;
        temp->l = v;
        fix_balance(v);
        fix_balance(temp);
        return temp;
    }

    node* rotate_right(node *v) {
        node *temp = v->l;
        v->l = temp->r;
        temp->r = v;
        fix_balance(v);
        fix_balance(temp);
        return temp;
    }

    node* balancing(node *v) {
        fix_balance(v);

        if (get_balance(v) == 2) {
            if (get_balance(v->r) < 0) {
                v->r = rotate_right(v->r);
            }
            return rotate_left(v);
        }

        if (get_balance(v) == -2) {
            if (get_balance(v->l) > 0) {
                v->l = rotate_left(v->l);
            }
            return rotate_right(v);
        }

        return v;
    }

    node* find_key(node *v, int key) {
        while (v != nullptr && v->key != key) {
            if (v->key < key) {
                v = v->r;
            } else {
                v = v->l;
            }
        }
        return v;
    }

    node* get_prev(node *v) {
        v = v->l;
        while (v->r != nullptr) {
            v = v->r;
        }
        return v;
    }

    node* insert(node *v, int key) {
        if (v == nullptr) {
            return new node(key);
        }
        if (v->key < key) {
            v->r = insert(v->r, key);
        } else {
            v->l = insert(v->l, key);
        }

        return balancing(v);
    }

    node* erase(node *v, int key) {
        if (v->key < key) {
            v->r = erase(v->r, key);
        } else if (v->key > key) {
            v->l = erase(v->l, key);
        } else {
            if (v->l == nullptr && v->r == nullptr) {  // If vertex is leaf
                delete v;
                return nullptr;
            }

            if (v->l == nullptr && v->r != nullptr) { // If vertex hasn't left child
                node *result = v->r;
                delete v;
                return result;
            }

            if (v->l != nullptr && v->r == nullptr) { // If vertex hasn't right child
                node *result = v->l;
                delete v;
                return result;
            }

            if (v->l != nullptr && v->r != nullptr) { // Normal vertex
                node* prev_key = get_prev(v);

                int temp_key = prev_key->key;
                v->l = erase(v->l, temp_key);
                v->key = temp_key;

                return balancing(v);
            }
        }

        return balancing(v);
    }

public:
    AVL(): size_of_tree(0) {
        root = nullptr;
    }

    AVL(const std::vector<int> &values, const std::vector<std::pair<int, int>> &g): AVL() {
        if (!values.empty()) {
            size_of_tree = (int)values.size();
            build_tree(root, 0, values, g);
            make_height(root);
        }
    }

    bool empty() {
        return root == nullptr;
    }

    int size() {
        return size_of_tree;
    }

    int get_height(const node *v) {
        return (v ? v->height : 0);
    }

    int get_balance(const node *v) {
        return get_height(v->r) - get_height(v->l);
    }

    int get_root_balance() {
        if (empty()) {
            return 0;
        } else {
            return get_balance(root);
        }
    }

    bool exists(int key) {
        if (!empty()) {
            node *temp = find_key(root, key);
            return temp != nullptr && temp->key == key;
        } else {
            return false;
        }
    }

    void insert(int key) {
        if (!exists(key)) {
            root = insert(root, key);
            size_of_tree++;
        }
    }

    void erase(int key) {
        if (exists(key)) {
            root = erase(root, key);
            size_of_tree--;
        }
    }

    void print() {
        std::cout << size_of_tree << std::endl;
        if (size_of_tree != 0) {
            int temp = 0;
            make_index(root, temp);
            print_all_tree(root);
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);

    AVL tree;

    int count_req;
    std::cin >> count_req;
    while (count_req--) {
        char request;
        int key;
        std::cin >> request >> key;

        if (request == 'A') {
            tree.insert(key);
            std::cout << tree.get_root_balance() << std::endl;
        }

        if (request == 'D') {
            tree.erase(key);
            std::cout << tree.get_root_balance() << std::endl;
        }

        if (request == 'C') {
            std::cout << (tree.exists(key) ? 'Y' : 'N') << std::endl;
        }
    }
    return 0;
}