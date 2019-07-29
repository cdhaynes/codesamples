/**
 * @file avl.c
 * @brief Contains functions for use in avl_test.c
 * @details Logic implements an avl tree, does operations.
 * @author Casey Haynes
 * @date May 2018
 * @bug Delete function doesn't fully free memory
 * @todo Free memory, delete entire tree
 */
#include "avl.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

/**
 * @brief Finds height
 * @param root the root node
 * @return the height
 */
int height(struct avl_node_t *root)
{
	if (!root)
		return -1;

	else
		return root->height;
}
/**
 * @brief FInds the max of two ints
 * @param a first int to compare
 * @param b the second int to compare
 * @return one or the other
 */
int max(int a, int b)
{
	if (a < b)
		return b;
	else
		return a;
}
/**
 * @brief compares two strings with strcmp
 * @param a first string
 * @param b the second string
 * @return the result of strcmp
 */
int ucmp(void *a, void *b)
{
	char *c = (char *)a;
	char *d = (char *)b;

	assert(c != NULL);
	assert(d != NULL);

	int ans = strcmp(c, d);
	return ans;
}


/* LL new node inserted into the left subtree of the left subtree of the critical node */
/**
 * @brief rotates tree once left
 * @param x the critical node
 * @return the address of the root
 */
struct avl_node_t *single_rotate_left(struct avl_node_t *x)
{
	struct avl_node_t *w = x->left;
	x->left = w->right;
	w->right = x;

	x->height = max(height(x->left), height(x->right)) + 1;
	w->height = max(height(w->left), x->height) + 1;
	return w; 		/* new root */

}


/* RR new node inserted into the right subtree of the right subtree of the critical node */
/**
 * @brief rotates tree once right
 * @param x the critical node
 * @return the address of the root
 */
struct avl_node_t *single_rotate_right(struct avl_node_t *w)
{
	struct avl_node_t *x = w->right;
	w->right = x->left;
	x->left = w;

	w->height = max(height(w->left), height(w->right)) + 1;
	x->height = max(height(x->right), w->height) + 1;
	return x; 		/* new root */

}

/* LR rotation new node inserted into the right subtree of the left subtree of the critical node  */
/**
 * @brief rotates tree twice left
 * @param x the critical node
 * @return the address of the root
 */
struct avl_node_t *double_rotate_left(struct avl_node_t *z)
{
	z->left = single_rotate_right(z->left);
	return single_rotate_left(z);
}

/* RL rotation new node inserted into the left subtree of the right subtree of the critical node  */
/**
 * @brief rotates tree twice right
 * @param x the critical node
 * @return the address of the root
 */
struct avl_node_t *double_rotate_right(struct avl_node_t *z)
{
	z->right = single_rotate_left(z->right);
	return single_rotate_right(z);
}
/**
 * @brief insert a node into a tree
 * @param root the root node
 * @param key the key
 * @param value the value associated with a key
 * @param ucmp a function pointer to a user provided compare function
 * @return the address of the root
 */
struct avl_node_t *insert(struct avl_node_t *root, void *key, void *value, int (*ucmp)(void *, void *))
{

	if (!root) {
		root = malloc(sizeof(struct avl_node_t));
		if (!root) {
			printf("insert: malloc error\n");
			return NULL;
		}
		else {
			root->key = key;
			root->value = value;
			root->height = 0;
			root->left = NULL;
			root->right = NULL;
		}

	}
	else if((*ucmp)(key , root->key) < 0) { /* left subtree */
		root->left = insert(root->left, key, value, ucmp);
		if ((height(root->left) - height(root->right)) == 2) {
			if ((*ucmp)(key , root->left->key) < 0) /* left subtree */
				root = single_rotate_left(root); /* LL */
			else 	/* LR */
				root = double_rotate_left(root);

		}
	}
	else if ((*ucmp)(key, root->key) > 0) { /* right subtree */
		root->right = insert(root->right, key, value, ucmp);
		if ((height(root->right) - height(root->left)) == 2) {
			if ((*ucmp)(key , root->right->key) < 0) /* left subtree */
				root = double_rotate_right(root); /* RL */
			else 	/* RR */
				root = single_rotate_right(root);
		}
	}

	root->height = max(height(root->left), height(root->right)) + 1;

	return root;
}
/**
 * @brief finds max node of an avl tree
 * @param root the root node
 * @return the address of the root
 */
struct avl_node_t *find_max(struct avl_node_t *root)
{
	while (root->right != NULL) {
		root = root->right;
	}
	return root;
}
/**
 * @brief frees SOME memory
 * @param str the structure to pass in
 */
void myfree(void *str)
{
	struct avl_node_t *c = (struct avl_node_t *)str;


	free(c->value);
	free(c->key);
	free(c);


}




/* this is a delete for a bst not an avl tree */
/* make it an avl deletion by accounting for rotations after you delete a node */
/**
 * @brief delete a node from a tree
 * @param root the root node
 * @param key the key
 * @param value the value associated with a key
 * @param ucmp a function pointer to a user provided compare function
 * @return the address of the root
 */
struct avl_node_t *delete_node(struct avl_node_t *root, void *key, void (*myfree)(void *), int (*ucmp)(void *, void *))
{
	struct avl_node_t *tmp;

	/* find node */
	if (root == NULL)
		printf("element not found\n");
	else if((*ucmp)(key, root->key) < 0) { /* left subtree */
		root->left = delete_node(root->left, key, myfree, ucmp);
	}
	else if ((*ucmp)(key, root->key) > 0) { /* right subtree */
		root->right = delete_node(root->right, key, myfree, ucmp);
	}
	else { 			/* found element */
		if (root->left && root->right) {
			/* two children */
			/* replace with largest in left subtree */
			/* you need to implement the find_max function */
			/* uncomment the next two lines once find_max is implemented */
			tmp = find_max(root->left);
			char* tmp1 = root->key;
			root->key = tmp->key;
			tmp->key = tmp1;

			char *tmp2 = root->value;

			root->value = tmp->value;
			tmp->value = tmp2;

			root->left = delete_node(root->left, tmp->key, myfree, ucmp);
		}
		else {

			tmp = root;
			/* no children */
			if (root->left == NULL && root->right == NULL){
				(*myfree)(root);
				root = NULL;
			} else if (root->left != NULL) { 			/* one child */
				root = root->left;
				(*myfree)(tmp);
			} else {
				root = root->right;
				(*myfree)(tmp);
			}
		}


	}
/* Copied from Scott's Rebalance section */
	if (root != NULL) {
		if((*ucmp)(key , root->key) < 0) { /* left subtree */
			//root->left = insert(root->left, key, value, ucmp);
			if ((height(root->left) - height(root->right)) == 2) {
				if ((*ucmp)(key , root->left->key) < 0) /* left subtree */
					root = single_rotate_left(root); /* LL */
				else 	/* LR */
					root = double_rotate_left(root);

			}
		}
		else if ((*ucmp)(key, root->key) > 0) { /* right subtree */
			//root->right = insert(root->right, key, value, ucmp);
			if ((height(root->right) - height(root->left)) == 2) {
				if ((*ucmp)(key , root->right->key) < 0) /* left subtree */
					root = double_rotate_right(root); /* RL */
				else 	/* RR */
					root = single_rotate_right(root);
			}
		}
		root->height = max(height(root->left), height(root->right)) + 1;
	} else {

	}






	return root;
}

/**
 * @brief traverses tree inorder
 * @param root the root node
 */
void inorder(struct avl_node_t *node)
{
	if (node != NULL) {
		inorder(node->left);
		char *k = (char *)node->key;
		char *v = (char *)node->value;
		printf("%s\n", k);
		printf("\t%s\n", v);
		inorder(node->right);
	}
}
/**
 * @brief traverses tree inorder (print key only)
 * @param root the root node
 */
void inorderkey(struct avl_node_t *node)
{
	if (node != NULL) {
		inorderkey(node->left);
		char *k = (char *)node->key;
		printf("%s\n", k);
		inorderkey(node->right);
	}
}
/**
 * @brief traverses tree preorder
 * @param root the root node
 */
void preorder(struct avl_node_t *node)
{
	if (node != NULL) {
		char *k = (char *)node->key;
		char *v = (char *)node->value;
		printf("%s\n", k);
		printf("\t%s\n", v);
		preorder(node->left);
		preorder(node->right);
	}
}
/**
 * @brief traverses tree preorder (print key only)
 * @param root the root node
 */
void preorderkey(struct avl_node_t *node)
{
	if (node != NULL) {
		char *k = (char *)node->key;
		printf("%s\n", k);
		preorderkey(node->left);
		preorderkey(node->right);
	}
}
/**
 * @brief traverses tree postorder
 * @param root the root node
 */
void postorder(struct avl_node_t *node)
{
	if (node != NULL) {
		postorder(node->left);
		postorder(node->right);
		char *k = (char *)node->key;
		char *v = (char *)node->value;
		printf("%s\n", k);
		printf("\t%s\n", v);
	}
}
/**
 * @brief traverses tree postorder (print key only)
 * @param root the root node
 */
void postorderkey(struct avl_node_t *node)
{
	if (node != NULL) {
		postorderkey(node->left);
		postorderkey(node->right);
		char *k = (char *)node->key;
		printf("%s\n", k);
	}
}
/**
 * @brief find a node
 * @param node the root node
 * @param ucmp the user provided compare function
 * @param query the node to find
 * @return a flag (if thing isn't found, it effects the behavior of avl_test)
 */
int find(struct avl_node_t *node, int (*ucmp)(void *, void *), char *query)
{	int ans = 5555;
	if (node != NULL) {
		find(node->left, ucmp, query);
		char *k = (char *)node->key;
		char *v = (char *)node->value;
		if ((*ucmp)(query, k) == 0) {
			printf("%s\n", k);
			printf("\t%s\n", v);
			ans = 0;
		}
		find(node->right, ucmp, query);
	}

	return ans;

}
