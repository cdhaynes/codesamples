/**
* @file linkedlists.c
*
* @author Casey D. Haynes
*
* @date 11/16/2017
*
* Assignment: Lab 8
*
* @brief Implements linked list data structure to manipulate numbers
*
* @details
*
* @bugs none
*
* @todo none
*/
#include <stdio.h>
#include <stdlib.h>
#include "math.h"

#define MALLOC_FAILED 1000

struct node_t {
        double x;
        struct node_t *next;
};

struct node_t *create_node(double n);
void print_node(struct node_t *node);
void print_list(struct node_t *head);
struct node_t *insert_head(struct node_t *head, struct node_t *node);
struct node_t *insert_tail(struct node_t *head, struct node_t *node);
struct node_t *insert_middle(struct node_t *head, struct node_t *node, int pos);
int count_nodes(struct node_t *head);
struct node_t *find_node(struct node_t *head, double n);
struct node_t *delete_node(struct node_t *head, double n);
void delete_list(struct node_t *head);

int main() {
        struct node_t *head = NULL;

        int menu2;
        double n;
        struct node_t *a = NULL;
        int pos;
        double x;
        int count;
        struct node_t *search = NULL;
        int m = 0;
        int menu;
        printf("Hello.\n");
while(1) {

        printf("1.  Enter a number\n");
        printf("2.  Delete a number\n");
        printf("3.  Print all numbers\n");
        printf("4.  Tell how many items are in the list\n");
        printf("5.  Find if a number is in the list\n");
        printf("6.  Quit\n");
        printf("Enter an option: ");

        char buf[1024];
        fgets(buf, 1024, stdin);
        menu = atoi(buf);

        switch(menu) {

        case 1:

                printf("1.  Enter at head?\n");
                printf("2.  Or tail?\n");
                printf("3.  Or middle?\n");
                printf("Enter a sub-option: ");
                fgets(buf, 1024, stdin);
                menu2 = atoi(buf); /*menu2 is sub-menu controller*/


                switch(menu2) {

                case 1:
                        printf("Provide a double to enter: ");
                        fgets(buf, 1024, stdin);
                        n = atof(buf);
                        a = create_node(n);
                        head = insert_head(head, a);
                        break;
                case 2:
                        printf("Provide a double to enter: ");
                        fgets(buf, 1024, stdin);
                        n = atof(buf);
                        a = create_node(n);
                        head = insert_tail(head, a);
                        break;
                case 3:
                        printf("Provide a double to enter: ");
                        fgets(buf, 1024, stdin);
                        n = atof(buf);
                        printf("Provide a position: ");
                        fgets(buf, 1024, stdin);
                        pos = atoi(buf);
                        a = create_node(n);
                        head = insert_middle(head, a, pos);
                        break;

                }
                break;
        case 2:
                printf("Which number would you like to delete: ");
                fgets(buf,1024,stdin);
                x = atof(buf);

                head = delete_node(head, x);
                break;
        case 3:
                print_list(head);
                printf("\n");
                break;
        case 4:
                count = count_nodes(head);
                printf("The count of nodes is %d\n\n", count);
                break;
        case 5:
                printf("Enter a value (double) to search for: ");
                fgets(buf, 1024, stdin);
                m = atof(buf);
                search = find_node(head, m);
                if (search == NULL) {
                        printf("That number is not in the list.\n\n");
                } else {
                printf("The specified value is located at memory address %p\n\n", search);
        }
                break;
        case 6:
                if (head == NULL) {
                        printf("See ya!\n"); /* Tests condition to avoid seg fault */
                        return 0;
                } else {
                printf("See ya!\n");
                delete_list(head);
                return 0;
                }

        }
}






        return 0;
}
/**
 * @brief creates a node
 * @param n the number to create the node with
 * @return the created node
 */
struct node_t *create_node(double n)
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
        printf("Node's location is %p\n", node);
        printf("Value of Node's double is %lf\n", node->x);
        printf("Address of the next pointer is %p\n", node->next);
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
