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
class Solution {

public:
    TreeNode* searchBST(TreeNode* root, int val) {
        while (root){
            if (root->val==val)
                return root;
            if (root->val>val)
                root=root->left;
            if (root->val<val)
                root=root->right;
        }
        return nullptr;
        }
};