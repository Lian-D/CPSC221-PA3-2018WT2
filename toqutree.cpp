
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

	//First we need to solve for the lowest entropy chose that as SE top right
	//Then split the table like that with SE((x) being lowest Entropy + 2^k-1 being the width and SE(Y)- 2^k-1 being the length
	//Then we determine the difference between 0 and SE minus 2^k-1 to decide the amount of pixels on the bottom for NE
	//Rinse and repeat for the rest

	//Optimal entropy and points
	pair<int,int> optimal;
	double minEntropy;

	//The area of the square we are checking
	int areaHeight = *im.height()/2;
	int areaLength = *im.length()/2;

	//Upper Left Pair
	pair<int,int> zoneUpperLeft = make_pair((*im.length()/4), (*im.height()/4));

	//Lower Left Pair
	pair<int,int> zoneLowerRight = make_pair((*im.length()*3/4), (*im.height()*3/4));

	//Possible Error here for new, not sure yet.
	Stats* stats = new Stats(im);


	for (int i = zoneUpperLeft.first; i < zoneLowerRight.first; i++){
		for (int j = zoneUpperLeft.second; i < zoneLowerRight.second; i++){
			
			double totalAvgEntropy;
			//Need to instantiate Stats
			//This should check the zones possible for this int.

			double zone1 =  stats.entropy(pair<int,int>, pair<int,int>); //NW
			double zone2 =  stats.entropy(pair<int,int>, pair<int,int>); //NE

			double zone3 =  stats.entropy(pair<int,int>, pair<int,int>); //SW
			double zone4 =  stats.entropy(pair<int,int>, pair<int,int>); //SE
			
			//Total Entropy
			totalAvgEntropy = (zone1 + zone2 + zone3 + zone4)/4;

			//If we don't have a min Entropy yet (only for first case)
			if (minEntropy == NULL){
				minEntropy = totalAvgEntropy;
				optimal = make_pair(i, j);
			} //If smaller, then we change it
			else if(minEntropy > totalAvgEntropy){
				minEntropy = totalAvgEntropy;
				optimal = make_pair(i, j);
			}

		}
	}
	//Now we do stuff that creates the new node with the coodinates and stuff
	//IDK RN
	delete stats;
	return NULL;
}

PNG toqutree::render(){

// My algorithm for this problem included a helper function
// that was analogous to Find in a BST, but it navigated the 
// quadtree, instead.

/* your code here */
	return NULL;
}

/* oops, i left the implementation of this one in the file! */
void toqutree::prune(double tol){

	// prune(root,tol);

}

/* called by destructor and assignment operator*/
void toqutree::clear(Node * & curr){

	//Run through conds to slowly delete the node
	if (*NW != NULL){
		clear(*NW);
	}
	if (*NE != NULL){
		clear(*NE);
	}
	if (*SW != NULL){
		clear(*SW);
	}
	if (*SE != NULL){
		clear(*SE);
	}

	if (*NW == NULL && *SW = NULL && *SE == NULL && *NE == NULL){
		delete curr;
		curr = NULL;
	}
	else {
		delete curr;
		curr = NULL;
	}
	//Everything should be deleted now
}

/* done */
/* called by assignment operator and copy constructor */
toqutree::Node * toqutree::copy(const Node * other) {
	return NULL;

/* your code here */
}


