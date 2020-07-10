/*
    배열을 이용한 이진트리순회

    부모노드 rootIdx/2 -> 나머지는 버림
    좌측자식 rootIdx*2, 우측자식 (rootIdx*2)+1

    쉽게 idx를 일치시키기 위해 배열의 0번자리를 사용안함 1번부터 사용    
*/
#include <iostream>
#include <vector>

using namespace std;

using Tree = vector<char>;

/*
            1
        2      3
      4  5    6  7
    8 9 A B  C  
*/
Tree getTree()
{
    return { -1, '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', -1, -1, -1 };
}

// 전위
void preorder(const Tree& tree, const int nodePos)
{
    if ((nodePos < tree.size()) && (tree[nodePos] != -1))
    {
        auto pivot{ nodePos * 2 };

        cout << tree[nodePos] << " ";       
        preorder(tree, nodePos * 2);
        preorder(tree, (nodePos * 2) + 1);
    }
}

// 중위
void inorder(const Tree& tree, const int nodePos)
{
    if ((nodePos < tree.size()) && (tree[nodePos] != -1))
    {
        auto pivot{ nodePos * 2 };

        inorder(tree, nodePos * 2);
        cout << tree[nodePos] << " ";
        inorder(tree, (nodePos * 2) + 1);
    }
}

// 후위
void postorder(const Tree& tree, const int nodePos)
{
    if ((nodePos < tree.size()) && (tree[nodePos] != -1))
    {
        auto pivot{ nodePos * 2 };

        postorder(tree, nodePos * 2);
        postorder(tree, (nodePos * 2) + 1);
        cout << tree[nodePos] << " ";
    }
}

int main(void)
{
    Tree simpleTree{ getTree() };

    preorder(simpleTree, 1);
    cout << endl;

    inorder(simpleTree, 1);
    cout << endl;

    postorder(simpleTree, 1);
    cout << endl;

    return 0;
}