
#include "stats.h"

stats::stats(PNG & im){

/* your code here */

}


void stats::initializeSHX(PNG & im){
    for(int x = 0; x < im.width(); x++){
        for(int y = 0; y < im.height(); y++){
            HSLAPixel* pixel = im.getPixel(x,y);
            sumHueX[x][y] = cos(pixel->h * PI/180);
            // Initializing the sum of the first row of x and first row of y
            if(x == 0 && y >= 1){
                // For this case, where this is the first column, the cumulative sum is produced by simply adding the sum 
                // of the entry above to the current hue value;
                sumHueX[x][y] = sumHueX[x][y] + sumHueX[x][y-1]; 
            }
            if(y == 0 && x >= 1){
                sumHueX[x][y] = sumHueX[x][y] + sumHueX[x-1][y];
            }
            // We add the cumulative sum of the entry above, the entry to the left, and the current entry, and then 
            // subtract the overlapped sums, which is represented by x-1, y-1
            if(x > 0 && y > 0){
                sumHueX[x][y] = sumeHueX[x][y] + sumHueX[x][y-1] + sumeHueX[x-1][y] - sumHueX[x-1][y-1];
            }
        }
    }
}


long stats::rectArea(pair<int,int> ul, pair<int,int> lr){

/* your code here */

}

HSLAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){

/* your code here */
}

vector<int> stats::buildHist(pair<int,int> ul, pair<int,int> lr){

/* your code here */
}

// takes a distribution and returns entropy
// partially implemented so as to avoid rounding issues.
double stats::entropy(vector<int> & distn,int area){

    double entropy = 0.;

/* your code here */

    for (int i = 0; i < 36; i++) {
        if (distn[i] > 0 ) 
            entropy += ((double) distn[i]/(double) area) 
                                    * log2((double) distn[i]/(double) area);
    }

    return  -1 * entropy;

}

double stats::entropy(pair<int,int> ul, pair<int,int> lr){

/* your code here */

}
