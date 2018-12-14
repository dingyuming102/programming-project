#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <plantTree.h>
#ifndef basicFunction_H
#define basicFunction_H
const int maxLevel = 6;
int add_max;
int cut_max;
struct qnode {
	int level;
	int flag;
	double xy[2];
	struct qnode *child[4];
};
typedef struct qnode Node;

Node *makeNode( double x, double y, int level );
void makeChildren( Node *parent );
void writeTree( Node *head );
void writeNode( FILE *fp, Node *node );
void printOut( FILE *fp, Node *node );
#endif
