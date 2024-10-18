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
   bool  is_prefecet(TreeNode *root,bool flag= true)
   {
       if (!root)
           return false;

       if (!root->right||!root->left)
           flag= false;
       if (root->right)
           is_prefecet(root->right);
       if (root->left)
           is_prefecet(root->right);


       return flag;
   }

   void _isPerfect_cnt(TreeNode * root){
       is_prefecet(root);
   }
};

int main() {	// rename like main1 for leetcode
    BinaryTree tree(1);

    assert(Solution()._isPerfect_cnt(tree.root).first == 1);

    tree.add( { 2 }, { 'L' });
    assert(Solution()._isPerfect_cnt(tree.root).first == 0);

    tree.add( { 3 }, { 'R' });
    assert(Solution()._isPerfect_cnt(tree.root).first == 1);

    tree.add( { 3, 6}, { 'R', 'R' });
    tree.add( { 3, 14 }, { 'R', 'L'});
    assert(Solution()._isPerfect_cnt(tree.root).first == 0);

    tree.add( { 2, 4, 7 }, { 'L', 'L', 'L' });
    tree.add( { 2, 4, 8 }, { 'L', 'L', 'R' });
    tree.add( { 2, 5, 9 }, { 'L', 'R', 'R' });
    tree.add( { 3, 6, 15 }, { 'R', 'R', 'L' });
    assert(Solution()._isPerfect_cnt(tree.root).first == 0);

    tree.add( { 2, 5, 13 }, { 'L', 'R', 'L' });
    tree.add( { 3, 6, 12 }, { 'R', 'R', 'R' });
    assert(Solution()._isPerfect_cnt(tree.root).first == 0);

    tree.add( { 3, 14, 15 }, { 'R', 'L', 'L' });
    tree.add( { 3, 14, 16 }, { 'R', 'L', 'R' });

    assert(Solution()._isPerfect_cnt(tree.root).first == 1);	// now 8 leaf nodes

    cout<<"bye";

    return 0;
}

