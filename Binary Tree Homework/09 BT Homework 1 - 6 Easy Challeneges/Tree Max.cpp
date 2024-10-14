#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

struct TreeNode {
	int val { };
	TreeNode* left { };
	TreeNode* right { };
	TreeNode(int val) : val(val) { }
};


struct BinaryTree {
	TreeNode* root { };
	BinaryTree(int root_value) :
			root(new TreeNode(root_value)) {
	}

	void add(vector<int> values, vector<char> direction) {
		assert(values.size() == direction.size());
		TreeNode* current = this->root;
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

	void _print_inorder(TreeNode* current) {
		if (!current)
			return;
		_print_inorder(current->left);
		cout << current->val << " ";
		_print_inorder(current->right);
	}


	void print_inorder() {
		_print_inorder(root);
		cout << "\n";
	}

};
bool isLeaf(TreeNode *node) {
    return node && !node->left && !node->right;
}

class Solution {
public:
    int maxValue(TreeNode *root){
        if (!root)
            return 0;
        int max=root->val;

        if (root->left)
            max=std::max(max, maxValue(root->left));

        if (root->right)
            max=std::max(max, maxValue(root->right));

        return max;
    }


};

int main() {
    BinaryTree tree(1);
//cout << maxValue(tree.root) << "\n";

    tree.add( { 2, 4, 7 }, { 'L', 'L', 'L' });
    cout << Solution().maxValue(tree.root) << "\n";

    tree.add( { 2, 4, 8 }, { 'L', 'L', 'R' });
    cout << Solution().maxValue(tree.root) << "\n";

    tree.add( { 2, 5, 9 }, { 'L', 'R', 'R' });
    cout << Solution().maxValue(tree.root) << "\n";

    tree.add( { 3, 6, 10 }, { 'R', 'R', 'L' });
    cout << Solution().maxValue(tree.root) << "\n";

    return 0;
}

