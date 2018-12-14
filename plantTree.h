#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <basicFunction.h>
#include <plantTree.h>
void destroyTree( Node *node );
void growTree( Node *node );
void removeChildren(Node * parent);
void setFlag(Node *node);
int addTree(Node *node);
int cutTree(Node *node);
void adapt(Node * head);
double nodeValue( Node *node, double time );
double value( double x, double y, double time );
