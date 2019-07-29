/**
* @file collatz.c
*
* @author Casey D. Haynes
*
* @date 11/16/2017
*
* Assignment: Lab 8
*
* @brief Applies linked lists idea to the hailstone sequence problem.
*
* @details
*
* @bugs none
*
* @todo get rid of compiler WARNING that tail pointer is initialized but not used.
*/
#include <stdio.h>
#include <stdlib.h>
#include "math.h"

#define MALLOC_FAILED 1000

struct node_t {
        int x;
        struct node_t *next;
};

struct node_t *create_node(int n);
void print_node(struct node_t *node);
void print_list(struct node_t *head);
struct node_t *insert_head(struct node_t *head, struct node_t *node);
struct node_t *insert_tail(struct node_t *head, struct node_t *node);
struct node_t *insert_middle(struct node_t *head, struct node_t *node, int pos);
int count_nodes(struct node_t *head);
struct node_t *find_node(struct node_t *head, double n);
struct node_t *delete_node(struct node_t *head, double n);
void delete_list(struct node_t *head);

int main(void) {
        struct node_t *a = NULL;
        struct node_t *head = NULL;
        struct node_t *tail = NULL;
        int n;
        int tmp;
        int count;
        char buf[1024];
        printf("Please enter a number: ");
        fgets(buf, 1024, stdin);
        n = atoi(buf);
        tmp = n;


        a = create_node(n);
        head = insert_head(head, a);

        while (((a->x) != 1)) {
                if(((a->x) % 2 == 0)) {
                        n = ((a->x / 2));
                        a = create_node(n);
                        tail = insert_tail(head, a); /*Inserting at tail ensures that sequence will print in order*/
                } else if (((a->x) % 2 != 0)) {
                        n = ((a->x * 3) + 1);
                        a = create_node(n);
                        tail = insert_tail(head, a);
                }
        }


        printf("n = %d\n", tmp);
        count = count_nodes(head);
        printf("cycle length = %d\n", count);
        print_list(head);
        printf("\n");
        delete_list(head); /* Frees the list */

}

/**
 * @brief creates a node
 * @param n the number to create the node with
 * @return the created node
 */
struct node_t *create_node(int n)
{
        struct node_t *a = NULL;
        a = malloc(sizeof(struct node_t));
        if (a == NULL) {
                printf("Malloc Failed! Bye.\n");
                exit(MALLOC_FAILED);
        }
        a->x = n;
        a->next = NULL;
        return a;


}
/**
 * @brief prints a single node
 * @param node pointer a specified node
 */
void print_node(struct node_t *node)
{

        printf("%d, ", node->x);
}
/**
 * @brief calls upon print_node to print all of the nodes
 * @param head the current head pointer
 */
void print_list(struct node_t *head)
{
        if(head == NULL) {
                printf("The list is empty!\n"); /*Tests condition to avoid a seg fault*/
        } else {
        print_node(head);
        while (head->next != NULL) {
                head = head->next;
                print_node(head);
                }

        }
}
/**
 * @brief inserts a given node at the head
 * @param head the current head pointer
 * @param node the node to insert
 * @return the new head pointer
 */
struct node_t *insert_head(struct node_t *head, struct node_t *node)
{
        node->next = head;
        head = node;
        return head;
}
/**
 * @brief inserts a given node at the tail
 * @param head the current head pointer
 * @param node the node to insert
 * @return the original head pointer
 */
struct node_t *insert_tail(struct node_t *head, struct node_t *node)
{

        struct node_t *tmp = NULL;
        tmp = head;
        if (head == NULL) {
                head = node;
                head->next = NULL;
                return head;
        }
        while (head->next != NULL) {
                head = head->next;
        }
        if (head->next == NULL) {
                head->next = node;
                node->next = NULL;
        }

        return tmp; /*tmp keeps track of the orignal head pointer so the list isn't lost*/

}
/**
 * @brief inserts a given node at the middle
 * @param head the current head pointer
 * @param node the node to insert
 * @param pos the numeric postion where to insert the node (head = 1)
 * @return the original head pointer
 */
struct node_t *insert_middle(struct node_t *head, struct node_t *node, int pos)
{
        struct node_t *tmp = NULL;
        if(head == NULL || pos == 1){ /*fringe case test */
                return insert_head(head, node);
        }
        tmp = head;
        int i = 1;
        struct node_t *trail = NULL; /*trail keeps track of previous node to head */
        if(head->next == NULL) {
                return insert_tail(head, node);
        }
        while (head->next != NULL) {
                i++; /*index is used to keep track of position */
                trail = head;
                head = head->next;
                if (pos > i) {
                        printf("This position does not exist!\n");
                }
                if (i == pos) {
                        node->next = head;
                        trail->next = node;
                }

        }

        return tmp; /*tmp keeps track of original head so list isn't lost*/
}

/**
 * @brief counts the nodes in the list
 * @param head the head pointer
 * @return an integer count of the nodes
 */
int count_nodes(struct node_t *head)
{
        if (head == NULL) {
                printf("The list is empty\n");
                int a = 0; /*Returns int 0 to main, which expects an int*/
                return a;
        } else {
        int i = 1; /*index starts at one to account for the tail */
        while(head->next != NULL) {
                i++;
                head = head->next;
        }
        return i;
}
}
/**
 * @brief finds a specified node
 * @param head the head pointer
 * @param n the number to search for in the list
 * @return the memory address of where the node is
 */
struct node_t *find_node(struct node_t *head, double n)
{
        if (head == NULL) { /*Tests case to avoid seg fault*/
                printf("The list is empty!\n");
        } else {
        while (head->next != NULL) {
                if((isgreaterequal(head->x, n)) && (islessequal(head->x, n))) {
                        return head;
                } else {
                        head = head->next;
                }
        }
        while (head->next == NULL) {
                if((isgreaterequal(head->x, n)) && (islessequal(head->x, n))) {
                        return head;
                } else {
                        return NULL;
                }
        }
}
        return 0;
}
/**
 * @brief deletes a specified node
 * @param head the head pointer
 * @param n the number to delete from the list
 * @return the original head pointer
 */
struct node_t *delete_node(struct node_t *head, double n)
{

        struct node_t *tmp = NULL;
        struct node_t *trail = NULL;
        tmp = head;
        if(head->x == n) {
                tmp = head;
                head = head->next;
                free(tmp);
                tmp = head;
                return head;
        }
        while(head->next != NULL) {
                trail = head;
                head = head->next;
                if(head->x == n) {
                        trail->next = head->next;
                        free(head); /*liberate the specified node*/
                        return tmp;
                }
        }
        if(head->next == NULL) {
                free(head); /*liberate the specified node*/
        }



        return tmp;

}
/**
 * @brief deletes the entire list
 * @param head the head pointer
 */
void delete_list(struct node_t *head) //
{
        struct node_t *trail = NULL;
        while (head->next != NULL) {
                trail = head;
                head = head->next;
                free(trail); /*liberate node behind current working node, go down the list*/
        }
        if (head->next == NULL) {
               free(head); /*liberate tail node*/
        }
}
