//트리 용어 정리
//root(루트) : 트리의 시작점이 되는 노드
//node(노드) : 트리를 구성하는 데이터와 링크의 블럭
//link(링크) : 다른 노드를 가리키는 포인터
//level(레벨) : root노드로부터 떨어진 거리
//형제 노드 : 레벨이 같은 노드
//자식 노드 : 링크를 갖는 아랫 레벨의 노드
//부모 노드 : 나의 링크를 갖는 윗 레벨의 노드
//말단 노드(leaf) : 자식 노드가 없는 노드
//차수 : 자식 노드의 개수
//====================================================================
//이진트리
//-모든 노드의 자식이 0~2개인 트리
//-현실적으로 가장 많이 사용되는 트리
//====================================================================
//root를 기준으로 작은 값은 왼쪽으로
//root를 기준으로 큰 값은 오른쪽으로
//====================================================================
//트리 운행법(순회)
//-->모든 노드를 한 번씩 모두 방문하는 것
//====================================================================
// 전위운행(preoreder)
//-->root를 기준으로 root->left node->right node 방문
// 중위운행(inorder)
//-->root를 중간에 방문하는 개념 left node->root->right node
// 후위운행(postorder)
//-->root를 마지막에 방문하는 개념 left node->right node->root
//====================================================================
//이진트리의 종류
//====================================================================
// - 포화 이진트리 : 꽉찬트리(2^n-1)
// - 완전 이진트리 : 맨 마지막 레벨 위 까지만 꽉찬 트리 2^(n-1)-1+마지막 레벨 노드 수
// - 사항 이진트리 : 한쪽방향
//====================================================================
// 트리 구현
//====================================================================

#include <stdio.h>
#include <malloc.h>

typedef struct TreeNode {
	int data;
	TreeNode *left;
	TreeNode *right;
};
//====================================================================
TreeNode *root = NULL;//트리의 루트 포인터
//====================================================================
//트리에 새로운 노드를 삽입하는 함수


void Insert(int value) {
	TreeNode * NewNode = (TreeNode*)calloc(1, sizeof(TreeNode));
	NewNode->data = value;
	NewNode->left = NULL;
	NewNode->right = NULL;

	if (root == NULL) {//빈 트리일 경우
		root = NewNode;
	}
	else {//트리에 노드가 1개 이상 존재하는 경우
		TreeNode *p = root;

		while (1) {
			if (p->data > NewNode->data) {//왼쪽으로
				if (p->left == NULL) {
					p->left = NewNode;
					return;
				}
				else {
					p = p->left;
				}
			}
			else {//오른쪽으로
				if (p->right == NULL) {
					p->right = NewNode;
					return;
				}
				else {
					p = p->right;
				}
			}
		}
	}
}

//이진 트리 순회(전위,중위,후위)
//재귀함수 : 함수 안에서 같은 함수를 다시 호출

void preorder(TreeNode *root) {
	printf("%d->", root->data);
	if (root->left != NULL) {
		preorder(root->left);
	}
	if (root->right != NULL) {
		preorder(root->right);
	}
}

void inorder(TreeNode *root) {
	if (root->left != NULL) {
		inorder(root->left);
	}
	printf("%d->", root->data);
	if (root->right != NULL) {
		inorder(root->right);
	}
}

void postorder(TreeNode *root) {
	if (root->left != NULL) {
		postorder(root->left);
	}
	if (root->right != NULL) {
		postorder(root->right);
	}
	printf("%d->", root->data);
}

int main(void) {
	Insert(10);
	Insert(15);
	Insert(5);
	Insert(20);
	Insert(7);
	Insert(12);
	postorder(root);
	return 0;
}