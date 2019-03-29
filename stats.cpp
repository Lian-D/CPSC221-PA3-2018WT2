
#include "stats.h"

stats::stats(PNG & im){

/* your code here */
initializeHueX(im);
initializeHueY(im);
initializeSat(im);
initializeLum(im);

}


void stats::initializeHueX(PNG& im){
      // fill in the vector with the values
    for(int x = 0; x < im.width(); x++){
        vector<double> vertical;
        for(int y = 0; y < im.height(); y++){
            HSLAPixel* pixel = im.getPixel(x,y);
            vertical.push_back(cos(pixel->h * PI/180));
        }
        sumHueX.push_back(vertical);
    }
    // Then rewrite the vector to be the cumulative sum
     for(int x1 = 0; x1 < im.width(); x1++){
        for(int y1 = 0; y1 < im.height(); y1++){
            // Initializing the sum of the first row of x and first row of y
            if(x1 == 0 && y1 >= 1){
                // For this case, where this is the first column, the cumulative sum is produced by simply adding the sum 
                // of the entry above to the current hue value;
                sumHueX[x1][y1] = sumHueX[x1][y1] + sumHueX[x1][y1-1]; 
            }
            if(y1 == 0 && x1 >= 1){
                sumHueX[x1][y1] = sumHueX[x1][y1] + sumHueX[x1-1][y1];
            }
            // We add the cumulative sum of the entry above, the entry to the left, and the current entry, and then 
            // subtract the overlapped sums, which is represented by x-1, y-1
            if(x1 > 0 && y1 > 0){
                sumHueX[x1][y1] = sumHueX[x1][y1] + sumHueX[x1][y1-1] + sumHueX[x1-1][y1] - sumHueX[x1-1][y1-1];
            }
        }
    }
}

void stats::initializeHueY(PNG& im){
      // fill in the vector with the values
    for(int x = 0; x < im.width(); x++){
        vector<double> vertical;
        for(int y = 0; y < im.height(); y++){
            HSLAPixel* pixel = im.getPixel(x,y);
            vertical.push_back(sin(pixel->h * PI/180));
        }
        sumHueY.push_back(vertical);
    }
    // Then rewrite the vector to be the cumulative sum
     for(int x1 = 0; x1 < im.width(); x1++){
        for(int y1 = 0; y1 < im.height(); y1++){
            // Initializing the sum of the first row of x and first row of y
            if(x1 == 0 && y1 >= 1){
                // For this case, where this is the first column, the cumulative sum is produced by simply adding the sum 
                // of the entry above to the current hue value;
                sumHueY[x1][y1] = sumHueY[x1][y1] + sumHueY[x1][y1-1]; 
            }
            if(y1 == 0 && x1 >= 1){
                sumHueY[x1][y1] = sumHueY[x1][y1] + sumHueY[x1-1][y1];
            }
            // We add the cumulative sum of the entry above, the entry to the left, and the current entry, and then 
            // subtract the overlapped sums, which is represented by x-1, y-1
            if(x1 > 0 && y1 > 0){
                sumHueY[x1][y1] = sumHueY[x1][y1] + sumHueY[x1][y1-1] + sumHueY[x1-1][y1] - sumHueY[x1-1][y1-1];
            }
        }
    }
}

void stats::initializeSat(PNG& im){
      // fill in the vector with the values
    for(int x = 0; x < im.width(); x++){
        vector<double> vertical;
        for(int y = 0; y < im.height(); y++){
            HSLAPixel* pixel = im.getPixel(x,y);
            vertical.push_back(pixel->s);
        }
        sumSat.push_back(vertical);
    }
    // Then rewrite the vector to be the cumulative sum
     for(int x1 = 0; x1 < im.width(); x1++){
        for(int y1 = 0; y1 < im.height(); y1++){
            // Initializing the sum of the first row of x and first row of y
            if(x1 == 0 && y1 >= 1){
                // For this case, where this is the first column, the cumulative sum is produced by simply adding the sum 
                // of the entry above to the current value;
                sumSat[x1][y1] = sumSat[x1][y1] + sumSat[x1][y1-1]; 
            }
            if(y1 == 0 && x1 >= 1){
                sumSat[x1][y1] = sumSat[x1][y1] + sumSat[x1-1][y1];
            }
            // We add the cumulative sum of the entry above, the entry to the left, and the current entry, and then 
            // subtract the overlapped sums, which is represented by x-1, y-1
            if(x1 > 0 && y1 > 0){
                sumSat[x1][y1] = sumSat[x1][y1] + sumSat[x1][y1-1] + sumSat[x1-1][y1] - sumSat[x1-1][y1-1];
            }
        }
    }
}

void stats::initializeLum(PNG& im){
      // fill in the vector with the values
    for(int x = 0; x < im.width(); x++){
        vector<double> vertical;
        for(int y = 0; y < im.height(); y++){
            HSLAPixel* pixel = im.getPixel(x,y);
            vertical.push_back(pixel->l);
        }
        sumLum.push_back(vertical);
    }
    // Then rewrite the vector to be the cumulative sum
     for(int x1 = 0; x1 < im.width(); x1++){
        for(int y1 = 0; y1 < im.height(); y1++){
            // Initializing the sum of the first row of x and first row of y
            if(x1 == 0 && y1 >= 1){
                // For this case, where this is the first column, the cumulative sum is produced by simply adding the sum 
                // of the entry above to the current value;
                sumLum[x1][y1] = sumLum[x1][y1] + sumLum[x1][y1-1]; 
            }
            if(y1 == 0 && x1 >= 1){
                sumLum[x1][y1] = sumLum[x1][y1] + sumLum[x1-1][y1];
            }
            // We add the cumulative sum of the entry above, the entry to the left, and the current entry, and then 
            // subtract the overlapped sums, which is represented by x-1, y-1
            if(x1 > 0 && y1 > 0){
                sumLum[x1][y1] = sumLum[x1][y1] + sumLum[x1][y1-1] + sumLum[x1-1][y1] - sumLum[x1-1][y1-1];
            }
        }
    }
}

void stats::initializeHist(PNG& im){

    // Initializing the histogram, and starting it off by filling everything with zero
    
    for(int x1 = 0; x1 < im.width(); x1++){
        vector<vector<int>> vertical2;
        for(int y1 = 0; y1 < im.height(); y1++){
            vector<int> bin;
            for(int b = 0; b < 37; b++){
                bin.push_back(0);
            }
            vertical2.push_back(bin);
        }
        hist.push_back(vertical2);
    }

    // Now we construct the histogram woweeee
    for(int x2 = 0; x2 < im.width(); x2++){
        for(int y2 = 0; y2 < im.height(); y2++){
            HSLAPixel* pixel = im.getPixel(x2,y2);
            // Here, we add one to the appropriate bin
            hist[x2][y2][(pixel->h)/10] = hist[x2][y2][(pixel->h)/10] + 1;
            // Going to construct the histograms for each pixel by adding the bins together 

            // This is the case where x is 0, so to get the histograms, we simply add the current histogram to the one above it
            if( x2 == 0 && y2 >= 1){
                for(int ba = 0; ba < 37; ba++){
                    hist[x2][y2][ba] = hist[x2][y2-1][ba] + hist[x2][y2][ba]; 
                }
            }
            // This is the case where y is 0 , so to get hte histograms, we simply add the current histogram to the one to the left of it
            if( y2 == 0 && x1 >= 1){
                for(int bingsoo = 0; bingsoo < 37; bingsoo++){
                    hist[x2][y2][bingsoo] = hist[x2-1][y2][bingsoo] + hist[x2][y2][bingsoo];
                }
            }
            // Otherwise, we get the histogram by adding the histogram above and to the left of it, and then subtracting the overlapping
            // histogram at x2-1, y2 - 1;
            if(x2 > 0 && y2 > 0){
                for(int bingo = 0; bingo < 37; bingo++){
                    hist[x2][y2][bingo] = hist[x2-1][y2][bingo] + hist[x2][y2-1][bingo] + hist[x2][y2][bingo] - hist[x2-1][y2-1][bingo];
                }
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
