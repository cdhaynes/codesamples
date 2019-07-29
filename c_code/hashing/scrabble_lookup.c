/**
 * @file scrabble_lookup.c
 * @brief Implements a hash table with the scrabble dictionary and chaining
 * @details
 * @author Casey Haynes
 * @date April 2018
 * @bug none
 * @todo
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define LEN 128

struct node_t {
        char *word; /* dictionary word */
        struct node_t *next;
};

struct list_t {
        int nnodes; /* number of nodes list contains */
        struct node_t *head; /*head of the list */
};


/**
 * @brief Converts a string to lowercase using tolower
 * @param the string to pass in
 */
void tolowercase(char *s)
{
        int i = 0;
        while (s[i] != '\0') {
                s[i] = tolower(s[i]);
                i++;
        }
}

/**
 * @brief Strips whitespace from a string using isspace
 * @param a the string to pass in
 */
void rstrip(char *s)
{
        int i = 0;
        while(s[i] != '\0') {
                if (isspace(s[i]) != 0) {
                        s[i] = '\0';
                }
                i++;
        }
}

/**
 * @brief Implements Bernstein's Hash
 * @param s the string to turn into a key
 * @return the key
 */
int bernstein_hash(char *s)
{
        int h = 0;

        while(*s) {
                h = 33 * h + *s;
                s++;
        }

        return h;
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
 * @brief creates a node
 * @param n the string to create the node with
 * @return the created node
 */
struct node_t *create_node(char * n)
{
        struct node_t *a = NULL;
        a = malloc(sizeof(struct node_t));
        assert (a != NULL);
        a->word = n;
        a->next = NULL;
        return a;


}

/**
 * @brief prints a single node
 * @param node pointer a specified node
 */
void print_node(struct node_t *node)
{

        printf("%s", node->word);

}

/**
 * @brief calls upon print_node to print all of the nodes
 * @param head the current head pointer
 */
void print_list(struct node_t *head)
{

        print_node(head);
        if (head->next != NULL) {
                printf(", ");
        } else {
                printf("\n");
        }
        while (head->next != NULL) {
                head = head->next;
                print_node(head);
                if (head->next != NULL) {
                        printf(", ");
                } else {
                        printf("\n");
                }
        }
}

/**
 * @brief deletes the entire list
 * @param head the head pointer
 */
void delete_list(struct node_t *head)
{
        struct node_t *trail = NULL;
        while (head->next != NULL) {
                free(head->word);
                trail = head;
                head = head->next;
                free(trail); /*liberate node behind current working node, go down the list*/
        }
        if (head->next == NULL) {
                free(head->word);
                free(head); /*liberate tail node*/
        }
}

/**
 * @brief finds a specified node
 * @param head the head pointer
 * @param a the string to search for in the list
 */
void find_node(struct node_t *head, char * a)
{

        while (head->next != NULL) {
                if(strcmp(head->word, a) == 0) {
                        printf("That word is in the dictionary.\n");
                        return;
                } else {
                        head = head->next;
                }
        }
        while (head->next == NULL) {
                if(strcmp(head->word, a) == 0) {
                        printf("That word is in the dictionary.\n");
                        return;
                } else {
                        printf("That word isn't in the dictionary.\n");
                        return;
                }
        }

}



int main(int argc, char *argv[])
{
	char buf[LEN];
        FILE *in = fopen("scrabble.txt", "r");
        assert(in != NULL);
        //this fails if argv[1] is not provided
        if (argc != 2) {
                printf("usage: n (tablesize)\n");
                return 1;
        }




        size_t tbl_size = strtol(argv[1], NULL, 10);
        struct list_t **dict = malloc(sizeof(struct list_t *) * tbl_size);

        assert(dict != NULL);
        for (int i = 0; i < tbl_size; i++) {
                dict[i] = malloc(sizeof(struct list_t));
                dict[i]->nnodes = 0;
                dict[i]->head = NULL;
        }


        char * tmp = NULL;
        int count;
        char * dump = NULL;

        struct node_t *a = NULL;
        int ldfcr_den = 0;
        while (fgets(buf, LEN, in)) {
                tmp = strtok(buf, "\n");
                assert (tmp != NULL);
                count = strnlen(tmp, LEN);
                dump = malloc((count + 1) * sizeof(char));
                strncpy(dump, tmp, (count + 1));

                int key = bernstein_hash(dump);
                int hash = key % tbl_size; /*table size is variable this time */

                a = create_node(dump);
                assert(a != NULL);
                dict[hash]->head = insert_head(dict[hash]->head, a);
                assert(dict[hash]->head != NULL);
                dict[hash]->nnodes++;
                ldfcr_den++;

        }

        printf("Find a word? y/n (n for debug print): "); /* y/n for finding feature */
        fgets(buf, LEN, stdin);
        rstrip (buf);
        if (strcmp(buf, "y") == 0) {
                printf("Enter word: ");
                fgets(buf, LEN, stdin);
                rstrip(buf);
                int key = bernstein_hash(buf);
                int hash = key % tbl_size;

                find_node(dict[hash]->head, buf);

        } else {

        for (int i = 0; i < tbl_size; i++) {
                printf("%5d: ", i);
                if (dict[i]->head != NULL) {
                        print_list(dict[i]->head);
                } else if (dict[i]->head == NULL){
                        printf("\n");
                        i++;
                }


        }

        double ldfcr = (ldfcr_den * 1.0) / tbl_size;

        printf("table size %ld load factor: %3.2lf\n", tbl_size, ldfcr);
}


        for (int i = 0; i < tbl_size; i++) {
                if (dict[i]->head == NULL) {
                        continue;
                } else {
                        delete_list(dict[i]->head);
                }
        }

        for (int i = 0; i < tbl_size; i++) {
                free(dict[i]);
        }

        free(dict);

        fclose(in);


	return 0;
}
