#include "expTree.h"

Node*   makeNode(ElementType newData) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newData; 
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void    destroyNode(Node* node) {
    free(node);
}

void    destroyTree(Node* root) {
    if (root == NULL) return;
    destroyTree(root->left);
    destroyTree(root->right);
    destroyNode(root);
}

// 전위순회 및 출력
void    printTreePreorder(Node* root) {
    if (root == NULL) return;
    printf(" %c", root->data);
    printTreePreorder(root->left);
    printTreePreorder(root->right);
}
// 중위순회 및 출력
void    printTreeInorder(Node* root) {
    if (root == NULL) return;
    printTreeInorder(root->left);
    printf(" %c", root->data);
    printTreeInorder(root->right);
}
// 후위순회 및 출력
void    printTreePostorder(Node* root) {
    if (root == NULL) return;
    printTreePostorder(root->left);
    printTreePostorder(root->right);
    printf(" %c", root->data);
}

void    buildExpressionTree(Node** root, char* postfixExp) {
    int len = strlen(postfixExp);
    /* [한계점 1] 연산자도 한글자, 피연산자도 한글자로만 가정하고 있음
    따라서, 피연산자가 두자릿수 이상인 경우, 한글자씩 따로따로 인식해 계산결과가 달라짐.
    해결하기 위해서는
        1. 숫자여부 판단
        2. 연산자 또는 whitespace를 발견할 때까지 char 타입 스택 token에 push하고
        3. 계산할 때(`calculate()`)는 스택이 빌 때까지 10씩 곱하며 pop한다.
    참고로 double형은 약 308자릿수까지 계산 가능하다.
    */
    char token = postfixExp[len - 1];
    postfixExp[len - 1] = '\0';

    switch(token){
    // 읽은 토큰이 연산자인 경우, 토큰을 2번 읽어 왼쪽자식과 오른쪽자식 트리로
    case '+': case '-': case '*': case '/':
        (*root) = makeNode(token);
        buildExpressionTree(&((*root)->right), postfixExp);
        buildExpressionTree(&((*root)->left), postfixExp);
        break;
    // 피연산자인경우 리프노드로
    default:
        (*root) = makeNode(token);
        break;
    }
}

double  calculate(Node* root) {
    if (root == NULL) return 0.0;

    char temp[2];
    double op1 = 0.0, op2 = 0.0, result = 0.0;

    switch(root->data) {
    case '+': case '-': case '*': case '/':
        op1 = calculate(root->left);
        op2 = calculate(root->right);
        if (root->data == '+') result = op1 + op2;
        else if (root->data == '-') result = op1 - op2;
        else if (root->data == '*') result = op1 * op2;
        // [한계점 2] No Division zero exception check
        else if (root->data == '/') result = op1 / op2;
        break;
    default:
        temp[0] = root->data;
        temp[1] = '\0';
        result = atof(temp);
        break;
    }
    return result;
}
