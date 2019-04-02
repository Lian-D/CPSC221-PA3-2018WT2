
#include "stats.h"

stats::stats(PNG & im){

/* your code here */
initializeHueX(im);
initializeHueY(im);
initializeSat(im);
initializeLum(im);
initializeHist(im);
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
            for(int b = 0; b < 36; b++){
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
                for(int ba = 0; ba < 36; ba++){
                    hist[x2][y2][ba] = hist[x2][y2-1][ba] + hist[x2][y2][ba]; 
                }
            }
            // This is the case where y is 0 , so to get hte histograms, we simply add the current histogram to the one to the left of it
            if( y2 == 0 && x2 >= 1){
                for(int bingsoo = 0; bingsoo < 36; bingsoo++){
                    hist[x2][y2][bingsoo] = hist[x2-1][y2][bingsoo] + hist[x2][y2][bingsoo];
                }
            }
            // Otherwise, we get the histogram by adding the histogram above and to the left of it, and then subtracting the overlapping
            // histogram at x2-1, y2 - 1;
            if(x2 > 0 && y2 > 0){
                for(int bingo = 0; bingo < 36; bingo++){
                    hist[x2][y2][bingo] = hist[x2-1][y2][bingo] + hist[x2][y2-1][bingo] + hist[x2][y2][bingo] - hist[x2-1][y2-1][bingo];
                }
            }
        }
    }
}


long stats::rectArea(pair<int,int> ul, pair<int,int> lr){

 // First case is where the rectangle area is normal and does not wrap
    if(lr.first > ul.first && lr.second > ul.second){
        long areacase1;
        areacase1 = (lr.first - ul.first + 1) * (lr.second - ul.second + 1);
        return areacase1;
    }
    //This is the case where the lower x is less than the upper x, but the y coordinate is not wrapping 
    if(ul.first > lr.first && lr.second > ul.second){
        long areacase2;
        areacase2 = ((hist.size() - ul.first) + lr.first + 1) * (lr.second - ul.second + 1);
        return areacase2; 
    }
    // This is the case where the y is wrapped, that is lower y is smaller than upper y but x is not wrapped
    if(lr.first > ul.first && ul.second > lr.second){
        long areacase3;
        areacase3 = (lr.first - ul.first + 1) * (lr.second + (hist[0].size() - ul.second + 1));
        return areacase3;
    }
    // This is the case where both x and y are wrapped
    if(ul.first > lr.first && ul.second > lr.second){
        long areacase4;
        areacase4 = ((hist.size() - ul.first) + lr.first + 1) * (lr.second + (hist[0].size() - ul.second + 1));
        return areacase4;
    }

/* your code here */


}

HSLAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){
// Assuming that getAvg is always called with UL being 0,0
    if(lr.first > ul.first && lr.second > ul.second){
        if(ul.first == 0 && ul.second == 0){
            double avgHueX = sumHueX[lr.first][lr.second]/rectArea(ul,lr);
            double avgHueY = sumHueY[lr.first][lr.second]/rectArea(ul,lr);
            double trueavg = atan2(avgHueY,avgHueX) * 180/PI;
            cout << "yeet yeet" << endl;
            if(trueavg < 0){
           trueavg = trueavg + 360;
            }
            double satavg = sumSat[lr.first][lr.second]/rectArea(ul,lr);
            double lumavg = sumLum[lr.first][lr.second]/rectArea(ul,lr);
            HSLAPixel pixel(trueavg,satavg,lumavg,1.0);
            return pixel;
        }
        else{
       double xhueA = sumHueX[lr.first][lr.second];
       double yhueA = sumHueY[lr.first][lr.second];
       double xhueB = sumHueX[ul.first-1][lr.second];
       double yhueB = sumHueY[ul.first-1][lr.second];
       double xhueC = sumHueX[lr.first][ul.second-1];
       double yhueC = sumHueY[lr.first][ul.second-1];
       double xhueD = sumHueX[ul.first-1][ul.second-1];
       double yhueD = sumHueY[ul.first-1][ul.second-1];

       double avgHueX = xhueA - xhueB - xhueC + xhueD;
       double avgHueY = yhueA - yhueB - yhueC + yhueD;

       double trueavg = atan2(avgHueY,avgHueX) * 180/PI ; 

       if(trueavg < 0){
           trueavg = trueavg + 360;
       }

        double satavg = sumSat[lr.first][lr.second] - sumSat[ul.first-1][lr.second] - sumSat[lr.first][ul.second-1] 
        + sumSat[ul.first-1][ul.second-1];

        double lumavg = sumLum[lr.first][lr.second] - sumLum[ul.first-1][lr.second] - sumLum[lr.first][ul.second-1] 
        + sumLum[ul.first-1][ul.second-1];

       HSLAPixel returnpixel(trueavg,satavg,lumavg,1.0);
       return returnpixel;
        }
    }
}

vector<int> stats::buildHist(pair<int,int> ul, pair<int,int> lr){
// non zero normal case 
    if(ul.first != 0 && ul.second != 0){
        vector<int> oghistogram = hist[lr.first][lr.second];
        vector<int> blhistogram = hist[ul.first-1][lr.second];
        vector<int> uphistogram = hist[ul.first-1][ul.second-1];
        vector<int> urhistogram = hist[lr.first][ul.second-1];
        for(int i = 0; i < 36; i++){
            oghistogram[i] = oghistogram[i] - blhistogram[i] - urhistogram[i] + uphistogram[i];
        }
        return oghistogram;
    }
    if(ul.first == 0 && ul.second == 0){
        vector<int> histogram = hist[lr.first][lr.second];
        return histogram;
    }
    // first case where x is zero
    if(ul.first == 0 && ul.second != 0){
        vector<int> histogram = hist[lr.first][lr.second];
        vector<int> tophisto = hist[lr.first][ul.second-1];
        for(int i = 0; i < 36; i++){
            histogram[i] = histogram[i] - tophisto[i];
        }
        return histogram;
    }
    // where y is zero
    if(ul.first != 0 && ul.second == 0){
        vector<int> histogram = hist[lr.first][lr.second];
        vector<int> lefthisto = hist[lr.first][lr.second-1];
        for(int i = 0; i < 36; i++){
            histogram[i] = histogram[i] - lefthisto[i];
        }
        return histogram;
    }

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
    int area = rectArea(ul,lr);
    
    vector<int> histogram = buildHist(ul,lr);
    
    return entropy(histogram,area);

}
