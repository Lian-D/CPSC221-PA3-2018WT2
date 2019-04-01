
/**
 *
 * toqutree (pa3)
 * significant modification of a quadtree .
 * toqutree.cpp
 * This file will be used for grading.
 *
 */

#include "toqutree.h"

toqutree::Node::Node(pair<int,int> ctr, int dim, HSLAPixel a)
	:center(ctr),dimension(dim),avg(a),NW(NULL),NE(NULL),SE(NULL),SW(NULL)
	{}

toqutree::~toqutree(){
	clear(root);
}

toqutree::toqutree(const toqutree & other) {
	root = copy(other.root);
}


toqutree & toqutree::operator=(const toqutree & rhs){
	if (this != &rhs) {
		clear(root);
		root = copy(rhs.root);
	}
	return *this;
}

toqutree::toqutree(PNG & imIn, int k){ 

/* This constructor grabs the 2^k x 2^k sub-image centered */
/* in imIn and uses it to build a quadtree. It may assume  */
/* that imIn is large enough to contain an image of that size. */

/* your code here */
// Node node = new Node(ctr);

// Creating the subimage
PNG subimage(pow(2,k),pow(2,k));
int center = imIn.width()/2;
// Getting the right coordinates for the subimage square
int upleft = center - pow(2,k)/2;
int upright = center + pow(2,k)/2;

// Change the pixel by using getPixel, and then change the pixel 

for(int x = 0; x < pow(2,k); x++){
	for(int y = 0; y < pow(2,k); y++){
		HSLAPixel* pixel = subimage.getPixel(x,y);
		HSLAPixel* originalpixel = imIn.getPixel(upleft + x, upleft + y);
		*pixel = *originalpixel; 
	}
}

root = buildTree(subimage,k);

/* your code here */

}

int toqutree::size() {
int size = 1; //This node
if (*NW == NULL && *SW = NULL && *SE == NULL && *NE == NULL){
	return size = size + 0;
}
if (*NW != NULL){
	size = size + NW.size();
}
if (*NE != NULL){
	size = size + NE.size();
}
if (*SW != NULL){
	size = size + SW.size();
}
if (*SE != NULL){
	size = size + SE.size();
}
return size;
}


toqutree::Node * toqutree::buildTree(PNG * im, int k) {

/* your code here */

// Note that you will want to practice careful memory use
// In this function. We pass the dynamically allocated image
// via pointer so that it may be released after it is used .
// similarly, at each level of the tree you will want to 
// declare a dynamically allocated stats object, and free it
// once you've used it to choose a split point, and calculate
// an average.

}

PNG toqutree::render(){

// My algorithm for this problem included a helper function
// that was analogous to Find in a BST, but it navigated the 
// quadtree, instead.

/* your code here */

}

/* oops, i left the implementation of this one in the file! */
void toqutree::prune(double tol){

	prune(root,tol);

}

/* called by destructor and assignment operator*/
void toqutree::clear(Node * & curr){
/* your code here */
}

/* done */
/* called by assignment operator and copy constructor */
toqutree::Node * toqutree::copy(const Node * other) {

/* your code here */
}


