//Ʈ�� ��� ����
//root(��Ʈ) : Ʈ���� �������� �Ǵ� ���
//node(���) : Ʈ���� �����ϴ� �����Ϳ� ��ũ�� ��
//link(��ũ) : �ٸ� ��带 ����Ű�� ������
//level(����) : root���κ��� ������ �Ÿ�
//���� ��� : ������ ���� ���
//�ڽ� ��� : ��ũ�� ���� �Ʒ� ������ ���
//�θ� ��� : ���� ��ũ�� ���� �� ������ ���
//���� ���(leaf) : �ڽ� ��尡 ���� ���
//���� : �ڽ� ����� ����
//====================================================================
//����Ʈ��
//-��� ����� �ڽ��� 0~2���� Ʈ��
//-���������� ���� ���� ���Ǵ� Ʈ��
//====================================================================
//root�� �������� ���� ���� ��������
//root�� �������� ū ���� ����������
//====================================================================
//Ʈ�� �����(��ȸ)
//-->��� ��带 �� ���� ��� �湮�ϴ� ��
//====================================================================
// ��������(preoreder)
//-->root�� �������� root->left node->right node �湮
// ��������(inorder)
//-->root�� �߰��� �湮�ϴ� ���� left node->root->right node
// ��������(postorder)
//-->root�� �������� �湮�ϴ� ���� left node->right node->root
//====================================================================
//����Ʈ���� ����
//====================================================================
// - ��ȭ ����Ʈ�� : ����Ʈ��(2^n-1)
// - ���� ����Ʈ�� : �� ������ ���� �� ������ ���� Ʈ�� 2^(n-1)-1+������ ���� ��� ��
// - ���� ����Ʈ�� : ���ʹ���
//====================================================================
// Ʈ�� ����
//====================================================================

#include <stdio.h>
#include <malloc.h>

typedef struct TreeNode {
	int data;
	TreeNode *left;
	TreeNode *right;
};
//====================================================================
TreeNode *root = NULL;//Ʈ���� ��Ʈ ������
//====================================================================
//Ʈ���� ���ο� ��带 �����ϴ� �Լ�


void Insert(int value) {
	TreeNode * NewNode = (TreeNode*)calloc(1, sizeof(TreeNode));
	NewNode->data = value;
	NewNode->left = NULL;
	NewNode->right = NULL;

	if (root == NULL) {//�� Ʈ���� ���
		root = NewNode;
	}
	else {//Ʈ���� ��尡 1�� �̻� �����ϴ� ���
		TreeNode *p = root;

		while (1) {
			if (p->data > NewNode->data) {//��������
				if (p->left == NULL) {
					p->left = NewNode;
					return;
				}
				else {
					p = p->left;
				}
			}
			else {//����������
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

//���� Ʈ�� ��ȸ(����,����,����)
//����Լ� : �Լ� �ȿ��� ���� �Լ��� �ٽ� ȣ��

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