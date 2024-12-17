// https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/description/
#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val { };
    TreeNode *left { };
    TreeNode *right { };
    TreeNode(int val) :
            val(val) {
    }
};

struct BinaryTree {
    TreeNode *root { };
    BinaryTree(int root_value) :
            root(new TreeNode(root_value)) {
    }

    void add(vector<int> values, vector<char> direction) {
        assert(values.size() == direction.size());
        TreeNode *current = this->root;
        // iterate on the path, create all necessary TreeNodes
        for (int i = 0; i < (int) values.size(); ++i) {
            if (direction[i] == 'L') {
                if (!current->left)
                    current->left = new TreeNode(values[i]);
                else
                    assert(current->left->val == values[i]);
                current = current->left;
            } else {
                if (!current->right)
                    current->right = new TreeNode(values[i]);
                else
                    assert(current->right->val == values[i]);
                current = current->right;
            }
        }
    }
};

bool isLeaf(TreeNode *node) {
    return node && !node->left && !node->right;
}

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode *root) {


        deque<TreeNode*> nodes_queue;
        vector<vector<int>> results;

        if (!root)
            return results;

        nodes_queue.push_back(root);

        bool forward_level = true;

        while (!nodes_queue.empty()) {
            int sz = nodes_queue.size();

            vector<int> level;
            while (sz--) {
                TreeNode *cur;

                if (forward_level) {	// generate from front
                    // Usual queue style: pop queue front, push queue rear: left, then right
                    cur = nodes_queue.front();
                    nodes_queue.pop_front();

                    if (cur->left)
                        nodes_queue.push_back(cur->left);

                    if (cur->right)
                        nodes_queue.push_back(cur->right);
                } else {				// generate  from back
                    // like Stack: pop stack end, push stack front: right, then left
                    cur = nodes_queue.back();
                    nodes_queue.pop_back();

                    // observe from the end, the right comes before left
                    if (cur->right)
                        nodes_queue.push_front(cur->right);

                    if (cur->left)
                        nodes_queue.push_front(cur->left);
                }
                level.push_back(cur->val);
            }
            forward_level = !forward_level;
            results.push_back(level);
        }
        return results;
    }
};

int main() {
    BinaryTree tree(3);
    tree.add( { 9 }, { 'L' });
    tree.add( { 20, 7 }, { 'R', 'R' });
    tree.add( { 20, 15 }, { 'R', 'L' });

    auto results = Solution().zigzagLevelOrder(tree.root);

    for (auto row : results) {
        for (auto col : row)
            cout << col << " ";
        cout << "\n";
    }

    return 0;
}
