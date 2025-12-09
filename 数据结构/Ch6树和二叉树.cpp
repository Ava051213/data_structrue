#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>

using namespace std;

// 二叉树结点类定义
template<typename T>
struct TreeNode {
    T data;                    // 数据域
    TreeNode<T>* left;         // 左孩子指针
    TreeNode<T>* right;        // 右孩子指针
    
    // 构造函数
    TreeNode() : left(nullptr), right(nullptr) {}
    TreeNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
    TreeNode(const T& value, TreeNode<T>* l, TreeNode<T>* r) 
        : data(value), left(l), right(r) {}
};

// 二叉树类定义
template<typename T>
class BinaryTree {
protected:
    TreeNode<T>* root;         // 指向根结点的指针
    
public:
    BinaryTree() : root(nullptr) {}
    BinaryTree(const T& value) { root = new TreeNode<T>(value); }
    
    // 构造函数：以根值和左右子树构造
    BinaryTree(const T& value, BinaryTree<T>& leftTree, BinaryTree<T>& rightTree) {
        root = new TreeNode<T>(value);
        root->left = leftTree.root;
        root->right = rightTree.root;
        leftTree.root = nullptr;
        rightTree.root = nullptr;
    }
    
    // 析构函数
    ~BinaryTree() { destroy(root); }
    
    // 判断是否为空树
    bool isEmpty() const { return root == nullptr; }
    
    // 获取根结点值
    T getRoot() const { 
        if (root == nullptr) {
            throw runtime_error("树为空");
        }
        return root->data; 
    }
    
    // 获取左子树
    BinaryTree<T> getLeftChild() const {
        BinaryTree<T> leftTree;
        if (root != nullptr && root->left != nullptr) {
            leftTree.root = root->left;
            root->left = nullptr;
        }
        return leftTree;
    }
    
    // 获取右子树
    BinaryTree<T> getRightChild() const {
        BinaryTree<T> rightTree;
        if (root != nullptr && root->right != nullptr) {
            rightTree.root = root->right;
            root->right = nullptr;
        }
        return rightTree;
    }
    
    // 遍历操作
    void preOrder() const { 
        cout << "先序遍历: ";
        preOrder(root); 
        cout << endl;
    }
    
    void inOrder() const { 
        cout << "中序遍历: ";
        inOrder(root); 
        cout << endl;
    }
    
    void postOrder() const { 
        cout << "后序遍历: ";
        postOrder(root); 
        cout << endl;
    }
    
    void levelOrder() const { 
        cout << "层序遍历: ";
        levelOrder(root); 
        cout << endl;
    }
    
    // 非递归遍历
    void preOrderIterative() const {
        cout << "非递归先序遍历: ";
        preOrderIterative(root);
        cout << endl;
    }
    
    void inOrderIterative() const {
        cout << "非递归中序遍历: ";
        inOrderIterative(root);
        cout << endl;
    }
    
    void postOrderIterative() const {
        cout << "非递归后序遍历: ";
        postOrderIterative(root);
        cout << endl;
    }
    
    // 树的基本操作
    int getHeight() const { return getHeight(root); }
    int getNodeCount() const { return getNodeCount(root); }
    int getLeafCount() const { return getLeafCount(root); }
    
    // 创建二叉树（前序输入，#表示空结点）
    void createTree() {
        root = createTreeHelper();
    }
    
private:
    void destroy(TreeNode<T>*& node);              // 销毁二叉树
    void preOrder(TreeNode<T>* node) const;        // 前序遍历
    void inOrder(TreeNode<T>* node) const;         // 中序遍历
    void postOrder(TreeNode<T>* node) const;       // 后序遍历
    void levelOrder(TreeNode<T>* node) const;      // 层序遍历
    
    void preOrderIterative(TreeNode<T>* node) const;  // 非递归前序遍历
    void inOrderIterative(TreeNode<T>* node) const;   // 非递归中序遍历
    void postOrderIterative(TreeNode<T>* node) const; // 非递归后序遍历
    
    int getHeight(TreeNode<T>* node) const;        // 获取树的高度
    int getNodeCount(TreeNode<T>* node) const;     // 获取结点数
    int getLeafCount(TreeNode<T>* node) const;     // 获取叶子结点数
    
    TreeNode<T>* createTreeHelper();               // 创建二叉树辅助函数
};

// 销毁二叉树
template<typename T>
void BinaryTree<T>::destroy(TreeNode<T>*& node) {
    if (node != nullptr) {
        destroy(node->left);
        destroy(node->right);
        delete node;
        node = nullptr;
    }
}

// 递归遍历实现
template<typename T>
void BinaryTree<T>::preOrder(TreeNode<T>* node) const {
    if (node != nullptr) {
        cout << node->data << " ";      // 访问根结点
        preOrder(node->left);           // 遍历左子树
        preOrder(node->right);          // 遍历右子树
    }
}

template<typename T>
void BinaryTree<T>::inOrder(TreeNode<T>* node) const {
    if (node != nullptr) {
        inOrder(node->left);            // 遍历左子树
        cout << node->data << " ";      // 访问根结点
        inOrder(node->right);           // 遍历右子树
    }
}

template<typename T>
void BinaryTree<T>::postOrder(TreeNode<T>* node) const {
    if (node != nullptr) {
        postOrder(node->left);          // 遍历左子树
        postOrder(node->right);         // 遍历右子树
        cout << node->data << " ";      // 访问根结点
    }
}

// 层序遍历
template<typename T>
void BinaryTree<T>::levelOrder(TreeNode<T>* node) const {
    if (node == nullptr) return;
    
    queue<TreeNode<T>*> q;
    q.push(node);
    
    while (!q.empty()) {
        TreeNode<T>* current = q.front();
        q.pop();
        
        cout << current->data << " ";
        
        if (current->left != nullptr) q.push(current->left);
        if (current->right != nullptr) q.push(current->right);
    }
}

// 非递归遍历实现
template<typename T>
void BinaryTree<T>::preOrderIterative(TreeNode<T>* node) const {
    if (node == nullptr) return;
    
    stack<TreeNode<T>*> s;
    s.push(node);
    
    while (!s.empty()) {
        TreeNode<T>* current = s.top();
        s.pop();
        
        cout << current->data << " ";   // 访问当前结点
        
        // 先压入右子树，再压入左子树（因为栈是后进先出）
        if (current->right != nullptr) s.push(current->right);
        if (current->left != nullptr) s.push(current->left);
    }
}

template<typename T>
void BinaryTree<T>::inOrderIterative(TreeNode<T>* node) const {
    if (node == nullptr) return;
    
    stack<TreeNode<T>*> s;
    TreeNode<T>* current = node;
    
    while (current != nullptr || !s.empty()) {
        // 一直向左走到最左边的结点
        while (current != nullptr) {
            s.push(current);
            current = current->left;
        }
        
        // 处理栈顶结点
        current = s.top();
        s.pop();
        cout << current->data << " ";   // 访问当前结点
        
        // 转向右子树
        current = current->right;
    }
}

template<typename T>
void BinaryTree<T>::postOrderIterative(TreeNode<T>* node) const {
    if (node == nullptr) return;
    
    stack<TreeNode<T>*> s;
    TreeNode<T>* current = node;
    TreeNode<T>* lastVisited = nullptr;
    
    while (current != nullptr || !s.empty()) {
        if (current != nullptr) {
            s.push(current);
            current = current->left;
        } else {
            TreeNode<T>* peekNode = s.top();
            // 如果右子树存在且未被访问过
            if (peekNode->right != nullptr && lastVisited != peekNode->right) {
                current = peekNode->right;
            } else {
                cout << peekNode->data << " ";  // 访问当前结点
                lastVisited = s.top();
                s.pop();
            }
        }
    }
}

// 树的基本操作实现
template<typename T>
int BinaryTree<T>::getHeight(TreeNode<T>* node) const {
    if (node == nullptr) return 0;
    
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    
    return max(leftHeight, rightHeight) + 1;
}

template<typename T>
int BinaryTree<T>::getNodeCount(TreeNode<T>* node) const {
    if (node == nullptr) return 0;
    
    return getNodeCount(node->left) + getNodeCount(node->right) + 1;
}

template<typename T>
int BinaryTree<T>::getLeafCount(TreeNode<T>* node) const {
    if (node == nullptr) return 0;
    
    if (node->left == nullptr && node->right == nullptr) {
        return 1;
    }
    
    return getLeafCount(node->left) + getLeafCount(node->right);
}

// 创建二叉树辅助函数（前序输入，#表示空结点）
template<typename T>
TreeNode<T>* BinaryTree<T>::createTreeHelper() {
    T data;
    cin >> data;
    
    if (data == T('#')) {  // 假设#表示空结点
        return nullptr;
    }
    
    TreeNode<T>* node = new TreeNode<T>(data);
    node->left = createTreeHelper();
    node->right = createTreeHelper();
    
    return node;
}

// 对于字符类型，特殊处理
template<>
TreeNode<char>* BinaryTree<char>::createTreeHelper() {
    char ch;
    cin >> ch;
    
    if (ch == '#') {
        return nullptr;
    }
    
    TreeNode<char>* node = new TreeNode<char>(ch);
    node->left = createTreeHelper();
    node->right = createTreeHelper();
    
    return node;
}

// 哈夫曼树结点定义
struct HuffmanNode {
    int weight;                // 权值
    char data;                 // 数据
    HuffmanNode* left;         // 左孩子
    HuffmanNode* right;        // 右孩子
    
    HuffmanNode(int w) : weight(w), data(0), left(nullptr), right(nullptr) {}
    HuffmanNode(int w, char d) : weight(w), data(d), left(nullptr), right(nullptr) {}
    
    // 用于优先队列的比较运算符
    bool operator>(const HuffmanNode& other) const {
        return weight > other.weight;
    }
};

// 哈夫曼树类
class HuffmanTree {
public:
    HuffmanNode* root;
    
    HuffmanTree() : root(nullptr) {}
    
    // 构造哈夫曼树
    void createHuffmanTree(vector<int>& weights, vector<char>& chars) {
        if (weights.empty()) return;
        
        // 使用优先队列（最小堆）
        priority_queue<HuffmanNode*, vector<HuffmanNode*>, greater<HuffmanNode*>> pq;
        
        // 将所有叶子结点加入优先队列
        for (int i = 0; i < weights.size(); i++) {
            char c = (i < chars.size()) ? chars[i] : 0;
            pq.push(new HuffmanNode(weights[i], c));
        }
        
        // 构造哈夫曼树
        while (pq.size() > 1) {
            // 取出权值最小的两个结点
            HuffmanNode* left = pq.top(); pq.pop();
            HuffmanNode* right = pq.top(); pq.pop();
            
            // 创建新结点，权值为两个子结点权值之和
            HuffmanNode* parent = new HuffmanNode(left->weight + right->weight);
            parent->left = left;
            parent->right = right;
            
            // 将新结点加入优先队列
            pq.push(parent);
        }
        
        // 最后剩余的结点就是哈夫曼树的根
        root = pq.top();
    }
    
    // 计算WPL（带权路径长度）
    int calculateWPL() {
        return calculateWPL(root, 0);
    }
    
    int calculateWPL(HuffmanNode* node, int depth) {
        if (node == nullptr) return 0;
        
        // 如果是叶子结点，返回权值乘以深度
        if (node->left == nullptr && node->right == nullptr) {
            return node->weight * depth;
        }
        
        return calculateWPL(node->left, depth + 1) + 
               calculateWPL(node->right, depth + 1);
    }
    
    // 生成哈夫曼编码
    void generateHuffmanCodes(HuffmanNode* node, string code, 
                             vector<pair<char, string>>& codes) {
        if (node == nullptr) return;
        
        // 如果是叶子结点，保存编码
        if (node->left == nullptr && node->right == nullptr) {
            if (node->data != 0) {  // 只保存有数据的叶子结点
                codes.push_back({node->data, code});
            }
            return;
        }
        
        // 递归生成编码：左0右1
        generateHuffmanCodes(node->left, code + "0", codes);
        generateHuffmanCodes(node->right, code + "1", codes);
    }
    
    // 打印哈夫曼编码
    void printHuffmanCodes() {
        vector<pair<char, string>> codes;
        generateHuffmanCodes(root, "", codes);
        
        cout << "哈夫曼编码:" << endl;
        for (auto& pair : codes) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }
    
    // 析构函数
    ~HuffmanTree() {
        destroy(root);
    }
    
private:
    void destroy(HuffmanNode* node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }
};

// 完整示例程序
int main() {
    cout << "=== 二叉树完整实现演示 ===" << endl << endl;
    
    // 示例1：创建并演示二叉树
    cout << "【示例1：二叉树基本操作】" << endl;
    
    // 创建二叉树 A(B(D, E), C(#, F))
    // 手动创建树: A为根，B为左子树根，C为右子树根
    BinaryTree<char> d('D');
    BinaryTree<char> e('E');
    BinaryTree<char> b('B', d, e);  // B的左右子树是D和E
    
    BinaryTree<char> f('F');
    BinaryTree<char> c('C');
    c.root = new TreeNode<char>('C');
    c.root->right = f.root;
    f.root = nullptr;
    
    BinaryTree<char> tree('A', b, c);  // A的左右子树是B和C
    
    // 遍历演示
    tree.preOrder();
    tree.inOrder();
    tree.postOrder();
    tree.levelOrder();
    
    cout << "树的高度: " << tree.getHeight() << endl;
    cout << "结点总数: " << tree.getNodeCount() << endl;
    cout << "叶子结点数: " << tree.getLeafCount() << endl << endl;
    
    // 非递归遍历演示
    cout << "【示例2：非递归遍历算法】" << endl;
    tree.preOrderIterative();
    tree.inOrderIterative();
    tree.postOrderIterative();
    
    cout << endl << "【示例3：哈夫曼树构造与编码】" << endl;
    
    // 构造哈夫曼树
    vector<int> weights = {5, 29, 7, 8, 14, 23, 3, 11};
    vector<char> chars = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    
    HuffmanTree huffmanTree;
    huffmanTree.createHuffmanTree(weights, chars);
    
    cout << "WPL (带权路径长度): " << huffmanTree.calculateWPL() << endl;
    huffmanTree.printHuffmanCodes();
    
    cout << endl << "【示例4：二叉树性质验证】" << endl;
    cout << "对于n个结点的二叉树，叶子结点数n₀与度为2的结点数n₂的关系: n₀ = n₂ + 1" << endl;
    
    // 通过遍历计数验证性质
    int totalNodes = tree.getNodeCount();
    int leafNodes = tree.getLeafCount();
    int twoDegreeNodes = totalNodes - leafNodes - 
        (tree.getNodeCount() - tree.getHeight()); // 简化的度为1的结点计算
    
    cout << "总节点数: " << totalNodes << endl;
    cout << "叶子节点数: " << leafNodes << endl;
    cout << "度为2的节点数估算: " << twoDegreeNodes << endl;
    cout << "验证 n₀ = n₂ + 1: " << leafNodes << " = " << twoDegreeNodes << " + 1" << endl;
    
    return 0;
}