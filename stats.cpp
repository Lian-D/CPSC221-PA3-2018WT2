
#include "stats.h"

stats::stats(PNG & im){

/* your code here */
initializeHueX(im);
initializeHueY(im);
initializeSat(im);
initializeLum(im);
initializeHist(im);
}

// cout << "stats.cpp: " << __LINE__ << endl;

void stats::initializeHueX(PNG& im){
      // fill in the vector with the values
    //   cout << "stats.cpp: " << __LINE__ << endl;
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
    //   cout << "stats.cpp: " << __LINE__ << endl;
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
    //   cout << "stats.cpp: " << __LINE__ << endl;
    for(int x = 0; x < im.width(); x++){
        vector<double> vertical;
        for(int y = 0; y < im.height(); y++){
            HSLAPixel* pixel = im.getPixel(x,y);
            vertical.push_back(pixel->s);
        }
        sumSat.push_back(vertical);
    }
    // Then rewrite the vector to be the cumulative sum
    // cout << "stats.cpp: " << __LINE__ << endl;
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
    // cout << "stats.cpp: " << __LINE__ << endl;
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
    // cout << "stats.cpp: " << __LINE__ << endl;
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
    cout << "print hist size" << endl;
    for(int i = 0; i < im.width(); i++){
        for(int j = 0; j < im.height(); j++){
            cout << hist[i][j].size() << endl;
        }
    }

    // Now we construct the histogram woweeee
    for(int x2 = 0; x2 < im.width(); x2++){
        for(int y2 = 0; y2 < im.height(); y2++){
            
            HSLAPixel* pixel = im.getPixel(x2,y2);
            // Here, we add one to the appropriate bin
            cout << pixel->h/10 << endl;
            hist[x2][y2][(int)((pixel->h)/10)] = hist[x2][y2][(int)((pixel->h)/10)] + 1;
            // Going to construct the histograms for each pixel by adding the bins together 
            // cout << "print hist y" << endl;
            // cout << hist[0].size() << endl;
            // cout << "print hist x " << endl;
            // cout << hist.size() << endl;

            // This is the case where x is 0, so to get the histograms, we simply add the current histogram to the one above it
            if( x2 == 0 && y2 >= 1){
                for(int ba = 0; ba < 36; ba++){
                    hist[x2][y2][ba] = hist[x2][y2-1][ba] + hist[x2][y2][ba]; 
                }
            }
            // This is the case where y is 0 , so to get hte histograms, we simply add the current histogram to the one to the left of it
            else if( y2 == 0 && x2 >= 1){
                for(int bingsoo = 0; bingsoo < 36; bingsoo++){
                    hist[x2][y2][bingsoo] = hist[x2-1][y2][bingsoo] + hist[x2][y2][bingsoo];
                }
            }
            // Otherwise, we get the histogram by adding the histogram above and to the left of it, and then subtracting the overlapping
            // histogram at x2-1, y2 - 1;
            else if(x2 > 0 && y2 > 0){
                for(int bingo = 0; bingo < 36; bingo++){
                    hist[x2][y2][bingo] = hist[x2-1][y2][bingo] + hist[x2][y2-1][bingo] + hist[x2][y2][bingo] - hist[x2-1][y2-1][bingo];
                }
            }
        }
    }
        int test = 0;
        for(int b = 0 ; b < 36; b++){
            test = test + hist[im.width()-1][im.height()-1][b];
            }
            cout << "printing last histogram" << endl;
            cout << test << endl;
            cout << im.height() * im.width() << endl;
        }
    // }
// }


// given a rectangle, return the number of pixels in the rectangle
	/* @param ul is (x,y) of the upper left corner of the rectangle 
	* @param lr is (x,y) of the lower right corner of the rectangle */
long stats::rectArea(pair<int,int> ul, pair<int,int> lr){
    // cout << "stats.cpp: " << __LINE__ << endl;
    // First case is where the rectangle area is normal and does not wrap
    if(lr.first >= ul.first && lr.second >= ul.second){
        long areacase1;
        areacase1 = (lr.first - ul.first + 1) * (lr.second - ul.second + 1);
        return areacase1;
    }
    //This is the case where the lower x is less than the upper x, but the y coordinate is not wrapping 
    if(ul.first >= lr.first && lr.second >= ul.second){
        long areacase2;
        areacase2 = ((hist.size() - ul.first) + lr.first + 1) * (lr.second - ul.second + 1);
        return areacase2; 
    }
    // This is the case where the y is wrapped, that is lower y is smaller than upper y but x is not wrapped
    if(lr.first >= ul.first && ul.second >= lr.second){
        long areacase3;
        areacase3 = (lr.first - ul.first + 1) * (lr.second + (hist[0].size() - ul.second + 1));
        return areacase3;
    }
    // This is the case where both x and y are wrapped
    if(ul.first >= lr.first && ul.second >= lr.second){
        long areacase4;
        areacase4 = ((hist.size() - ul.first) + lr.first + 1) * (lr.second + (hist[0].size() - ul.second + 1));
        return areacase4;
    }
    if(ul.first == lr.first && ul.second == lr.second){
        int ha = 1;
        return ha;
    }

/* your code here */

}

HSLAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){
   // Case 1: getAvg is called with 0,0 NO WRAPPING
   // Case 2: getAvg is called with with x and y both greater than 0,0 NO WRAPPING
   // Case 3: getAvg is called with x = 0 and y!=0 NO WRAPPING
   // Case 4: getAvg is called with y = 0 and x !=0 NO WRAPPING
   // Case 5: getAvg is called with y = 0  X WRAPPING
   // Case 6: getAvg is called with y != 0 X WRAPPING
   // Case 7: getAvg is called with x = 0 and y != 0 Y WRAPPING
   // Case 8: getAvg is called with x !=0  Y WRAPPING
   // Case 9: double wrapping
   // We know that lr can never be 0,0 when considering both wrapping case
   // We also know that ul.first can't be the edge
   // We also know that lr.first can't be the edge either 
   // So it seems like the edge cases are at minimum lr = 1,1
   // Then it seems like we only need one case for double wrapping and that is general wrapping
  // Assuming that getAvg is always called with UL being 0,0 
  // CASE 1:
    // When ul x,y are 0,0
    // cout << "stats.cpp: " << __LINE__ << endl;
        if(ul.first == 0 && ul.second == 0){
            // cout << "is it here?" << endl;
            double avgHueX = sumHueX[lr.first][lr.second]/rectArea(ul,lr);
            double avgHueY = sumHueY[lr.first][lr.second]/rectArea(ul,lr);
            double trueavg = atan2(avgHueY,avgHueX) * 180/PI;
            // cout << "trueavg calculated" << endl;
            if(trueavg < 0){
           trueavg = trueavg + 360;
            }
            double satavg = sumSat[lr.first][lr.second]/rectArea(ul,lr);
            double lumavg = sumLum[lr.first][lr.second]/rectArea(ul,lr);
            // cout << "satavg and lumavg passed" << endl;
            HSLAPixel pixel(trueavg,satavg,lumavg,1.0);
            return pixel;
        }
        // CASE 2: getAvg is called with with x and y both greater than 0,0 NO WRAPPING
        // cout << "stats.cpp: " << __LINE__ << endl;
        if(ul.first <= lr.first && ul.second <= lr.second){
            // cout << "is it here2?" << endl;
            if(ul.first != 0 && ul.second != 0){
                double xhueA = sumHueX[lr.first][lr.second];
                double yhueA = sumHueY[lr.first][lr.second];
                double xhueB = sumHueX[ul.first-1][lr.second];
                double yhueB = sumHueY[ul.first-1][lr.second];
                double xhueC = sumHueX[lr.first][ul.second-1];
                double yhueC = sumHueY[lr.first][ul.second-1];
                double xhueD = sumHueX[ul.first-1][ul.second-1];
                double yhueD = sumHueY[ul.first-1][ul.second-1];
                

                double avgHueX = (xhueA - xhueB - xhueC + xhueD)/rectArea(ul,lr);
                double avgHueY = (yhueA - yhueB - yhueC + yhueD)/rectArea(ul,lr);

                double trueavg = atan2(avgHueY,avgHueX) * 180/PI ; 

                    if(trueavg < 0){
                        trueavg = trueavg + 360;
                    }

                double satavg = (sumSat[lr.first][lr.second] - sumSat[ul.first-1][lr.second] - sumSat[lr.first][ul.second-1] 
                + sumSat[ul.first-1][ul.second-1])/rectArea(ul,lr);

                double lumavg = (sumLum[lr.first][lr.second] - sumLum[ul.first-1][lr.second] - sumLum[lr.first][ul.second-1] 
                + sumLum[ul.first-1][ul.second-1])/rectArea(ul,lr);

                HSLAPixel returnpixel(trueavg,satavg,lumavg,1.0);
                return returnpixel;
            }
            // cout << "stats.cpp: " << __LINE__ << endl;
            // Case 3: getAvg is called with x = 0 and y!=0 NO WRAPPING
            if(ul.first == 0 && ul.second != 0){
                // cout << "is it here3?" << endl;
                double xhueA = sumHueX[lr.first][lr.second];
                double yhueA = sumHueY[lr.first][lr.second];
                double xhueC = sumHueX[lr.first][ul.second-1];
                double yhueC = sumHueY[lr.first][ul.second-1];


                 double avgHueX = (xhueA - xhueC)/rectArea(ul,lr);
                double avgHueY = (yhueA - yhueC)/rectArea(ul,lr);

                double trueavg = atan2(avgHueY,avgHueX) * 180/PI ; 

                    if(trueavg < 0){
                        trueavg = trueavg + 360;
                    }

                double satavg = (sumSat[lr.first][lr.second] - sumSat[lr.first][ul.second-1])/rectArea(ul,lr);

                double lumavg = (sumLum[lr.first][lr.second] - sumLum[lr.first][ul.second-1])/rectArea(ul,lr);

                HSLAPixel returnpixel(trueavg,satavg,lumavg,1.0);
                return returnpixel;
            }
            // Case 4: getAvg is called with y = 0 and x !=0 NO WRAPPING
            // cout << "stats.cpp: " << __LINE__ << endl;
            if(ul.first != 0 && ul.second == 0){
                // cout << "is it here4?" << endl;
                double xhueA = sumHueX[lr.first][lr.second];
                double yhueA = sumHueY[lr.first][lr.second];
                double xhueB = sumHueX[ul.first-1][lr.second];
                double yhueB = sumHueY[ul.first-1][lr.second];
        

                double avgHueX = (xhueA - xhueB)/rectArea(ul,lr);
                double avgHueY = (yhueA - yhueB)/rectArea(ul,lr);

                double trueavg = atan2(avgHueY,avgHueX) * 180/PI ; 

                    if(trueavg < 0){
                        trueavg = trueavg + 360;
                    }

                double satavg = (sumSat[lr.first][lr.second] - sumSat[ul.first-1][lr.second])/rectArea(ul,lr);

                double lumavg = (sumLum[lr.first][lr.second] - sumLum[ul.first-1][lr.second])/rectArea(ul,lr);

                HSLAPixel returnpixel(trueavg,satavg,lumavg,1.0);
                return returnpixel;
            }
        }
        // cout << "stats.cpp: " << __LINE__ << endl;
        // Case 5: getAvg is called with y = 0  X WRAPPING
        if(ul.first >= lr.first && ul.second <= lr.second){
            // cout << "is it here5?" << endl;
            if(ul.second == 0 ){
             double xhueA = sumHueX[lr.first][lr.second];
             double yhueA = sumHueY[lr.first][lr.second];
             double xhueB = sumHueX[hist.size()-1][lr.second];
             double yhueB = sumHueY[hist.size()-1][lr.second];
             double xhueC = sumHueX[ul.first-1][lr.second];
             double yhueC = sumHueY[ul.first-1][lr.second];
             

                double avgHueX = (xhueB - xhueC + xhueA)/rectArea(ul,lr);
                double avgHueY = (yhueB - yhueC + yhueA)/rectArea(ul,lr);

                double trueavg = atan2(avgHueY,avgHueX) * 180/PI ; 

                    if(trueavg < 0){
                        trueavg = trueavg + 360;
                    }

                double satavg = (sumSat[hist.size()-1][lr.second] - sumSat[ul.first-1][lr.second] + sumSat[lr.first][lr.second])/rectArea(ul,lr);

                double lumavg = (sumLum[hist.size()-1][lr.second] - sumLum[ul.first-1][lr.second] + sumLum[lr.first][lr.second])/rectArea(ul,lr);

                HSLAPixel returnpixel(trueavg,satavg,lumavg,1.0);
                return returnpixel;
        }
        }
        //// Case 6: getAvg is called with y != 0 X WRAPPING
        // cout << "stats.cpp: " << __LINE__ << endl;
        if(ul.first >= lr.first && ul.second <= lr.second){
            // cout << "is it here6?" << endl;
            double xhueA = sumHueX[lr.first][lr.second];
             double yhueA = sumHueY[lr.first][lr.second];
             double xhueB = sumHueX[hist.size()-1][lr.second];
             double yhueB = sumHueY[hist.size()-1][lr.second];
             double xhueC = sumHueX[ul.first-1][lr.second];
             double yhueC = sumHueY[ul.first-1][lr.second];
             double xhueD = sumHueX[hist.size()-1][ul.second-1];
             double yhueD = sumHueY[hist.size()-1][ul.second-1];
             double xhueE = sumHueX[ul.first-1][ul.second-1];
             double yhueE = sumHueY[ul.first-1][ul.second-1];
             double xhueF = sumHueX[lr.first][ul.second-1];
             double yhueF = sumHueY[lr.first][ul.second-1];

                double avgHueX = (xhueB - xhueC + xhueA + xhueE - xhueD - xhueF)/rectArea(ul,lr);
                double avgHueY = (yhueB - yhueC + yhueA + yhueE - yhueD - yhueF)/rectArea(ul,lr);

                double trueavg = atan2(avgHueY,avgHueX) * 180/PI ; 

                    if(trueavg < 0){
                        trueavg = trueavg + 360;
                    }

                double satavg = (sumSat[hist.size()-1][lr.second] - sumSat[ul.first-1][lr.second]
                 + sumSat[lr.first][lr.second] + sumSat[ul.first-1][ul.second-1]- sumSat[hist.size()-1][ul.second-1]
                 - sumSat[lr.first][ul.second-1])/rectArea(ul,lr);

                double lumavg = (sumLum[hist.size()-1][lr.second] - sumLum[ul.first-1][lr.second]
                 + sumLum[lr.first][lr.second] + sumLum[ul.first-1][ul.second-1]- sumLum[hist.size()-1][ul.second-1]
                 -sumLum[lr.first][ul.second-1])/rectArea(ul,lr);

                HSLAPixel returnpixel(trueavg,satavg,lumavg,1.0);
                return returnpixel;
        }
        // Case 7: getAvg is called with x = 0 and y != 0 Y WRAPPING
        // cout << "stats.cpp: " << __LINE__ << endl;
        // cout << ul.first << endl;
        // cout << lr.first << endl;
        // cout << "y values" << endl;
        // cout << ul.second << endl;
        // cout << lr.second << endl;
        if(ul.first <= lr.first && ul.second >= lr.second){
            // cout << "being called correctly?" << endl;
            if(ul.first == 0){
             double xhueA = sumHueX[lr.first][lr.second];
             double yhueA = sumHueY[lr.first][lr.second];
             double xhueB = sumHueX[lr.first][hist[0].size()-1];
             double yhueB = sumHueY[lr.first][hist[0].size()-1];
             double xhueC = sumHueX[lr.first][ul.second-1];
             double yhueC = sumHueY[lr.first][ul.second-1];
            
            double avgHueX = (xhueB - xhueC + xhueA)/rectArea(ul,lr);
            double avgHueY = (yhueB - yhueC + yhueA)/rectArea(ul,lr);

            double trueavg = atan2(avgHueY,avgHueX) * 180/PI ; 

                    if(trueavg < 0){
                        trueavg = trueavg + 360;
                    }

            double satavg = (sumSat[lr.first][hist[0].size()-1] - sumSat[lr.first][ul.second-1] + sumSat[lr.first][lr.second])/rectArea(ul,lr);

            double lumavg = (sumLum[lr.first][hist[0].size()-1] - sumLum[lr.first][ul.second-1] + sumLum[lr.first][lr.second])/rectArea(ul,lr);

            HSLAPixel returnpixel(trueavg,satavg,lumavg,1.0);
            return returnpixel;
            }
            else if(ul.first != 0){
                // cout << "called y wrapping no x zero" << endl;
             double xhueA = sumHueX[lr.first][lr.second];
             double yhueA = sumHueY[lr.first][lr.second];
             double xhueB = sumHueX[lr.first][hist[0].size()-1];
             double yhueB = sumHueY[lr.first][hist[0].size()-1];
             double xhueC = sumHueX[lr.first][ul.second-1];
             double yhueC = sumHueY[lr.first][ul.second-1];
             double xhueD = sumHueX[ul.first-1][hist[0].size()-1];
             double yhueD = sumHueY[ul.first-1][hist[0].size()-1];
             double xhueE = sumHueX[ul.first-1][ul.second-1];
             double yhueE = sumHueY[ul.first-1][ul.second-1];
             double xhueF = sumHueX[ul.first-1][lr.second];
             double yhueF = sumHueY[ul.first-1][lr.second];

             double avgHueX = (xhueB - xhueC - xhueD + xhueE + xhueA - xhueF)/rectArea(ul,lr);
             double avgHueY = (yhueB - yhueC - yhueD + yhueE + yhueA - yhueF)/rectArea(ul,lr);

             double trueavg = atan2(avgHueY,avgHueX) * 180/PI ; 

                    if(trueavg < 0){
                        trueavg = trueavg + 360;
                    }
            double satavg = (sumSat[lr.first][hist[0].size()-1] - sumSat[lr.first][ul.second-1] - sumSat[ul.first-1][hist[0].size()-1]
            + sumSat[ul.first-1][ul.second-1] + sumSat[lr.first][lr.second] - sumSat[ul.first-1][lr.second])/rectArea(ul,lr);

            double lumavg = (sumLum[lr.first][hist[0].size()-1] - sumLum[lr.first][ul.second-1] - sumLum[ul.first-1][hist[0].size()-1]
            + sumLum[ul.first-1][ul.second-1] + sumLum[lr.first][lr.second] - sumSat[ul.first-1][lr.second])/rectArea(ul,lr);

            HSLAPixel returnpixel(trueavg,satavg,lumavg,1.0);
            return returnpixel;
 
            }
        }
        // cout << "stats.cpp: " << __LINE__ << endl;
        // CASE 9 Double wrapping come back to this later 
        if(ul.first >= lr.first && ul.second >= lr.second){
            // cout << " YAYEET" << endl;
            double xhueA = sumHueX[hist.size()-1][hist[0].size()-1];
            double yhueA = sumHueY[hist.size()-1][hist[0].size()-1];
            double xhueB = sumHueX[hist.size()-1][lr.second];
            double yhueB = sumHueY[hist.size()-1][lr.second];
            double xhueC = sumHueX[lr.first][lr.second];
            double yhueC = sumHueY[lr.first][lr.second];
            double xhueD = sumHueX[lr.first][hist[0].size()-1];
            double yhueD = sumHueY[lr.first][hist[0].size()-1];
            double xhueA1 = sumHueX[hist.size()-1][ul.second-1];
            double yhueA1 = sumHueY[hist.size()-1][ul.second-1];
            double xhueA2 = sumHueX[ul.first-1][ul.second-1];
            double yhueA2 = sumHueY[ul.first-1][ul.second-1];
            double xhueA3 = sumHueX[ul.first-1][hist[0].size()-1];
            double yhueA3 = sumHueY[ul.first-1][hist[0].size()-1];
            double xhueB1 = sumHueX[ul.first-1][lr.second];
            double yhueB1 = sumHueY[ul.first-1][lr.second];
            double xhueD1 = sumHueX[lr.first][ul.second-1];
            double yhueD1 = sumHueY[lr.first][ul.second-1];

            double ASUMX = xhueA - xhueA1 - xhueA3 + xhueA2;
            double ASUMY = yhueA - yhueA1 - yhueA3 + yhueA2;
            double BSUMX = xhueB -xhueB1;
            double BSUMY = yhueB - yhueB1;
            double DSUMX = xhueD - xhueD1;
            double DSUMY = yhueD - yhueD1;

            double avgHueX = (ASUMX + BSUMX + xhueC + DSUMX)/rectArea(ul,lr);
            double avgHueY = (ASUMY + BSUMY + yhueC + DSUMY)/rectArea(ul,lr);

            double trueavg = atan2(avgHueY,avgHueX) * 180/PI ; 

                    if(trueavg < 0){
                        trueavg = trueavg + 360;
                    }

             double satA = sumSat[hist.size()-1][hist[0].size()-1];
            double satB = sumSat[hist.size()-1][lr.second];
            double satC = sumSat[lr.first][lr.second];
            double satD = sumSat[lr.first][hist[0].size()-1];
            double satA1 = sumSat[hist.size()-1][ul.second-1];
            double satA2 = sumSat[ul.first-1][ul.second-1];
            double satA3 = sumSat[ul.first-1][hist[0].size()-1];
            double satB1 = sumSat[ul.first-1][lr.second];
            double satD1 = sumSat[lr.first][ul.second-1];


            
             double lumA = sumLum[hist.size()-1][hist[0].size()-1];
            double lumB = sumLum[hist.size()-1][lr.second];
            double lumC = sumLum[lr.first][lr.second];
            double lumD = sumLum[lr.first][hist[0].size()-1];
            double lumA1 = sumLum[hist.size()-1][ul.second-1];
            double lumA2 = sumLum[ul.first-1][ul.second-1];
            double lumA3 = sumLum[ul.first-1][hist[0].size()-1];
            double lumB1 = sumLum[ul.first-1][lr.second];
            double lumD1 = sumLum[lr.first][ul.second-1];

            double satavg = (satA - satA1 - satA3 + satA2 + satB - satB1 + satC + satD - satD1)/rectArea(ul,lr);

            double lumavg = (lumA - lumA1 - lumA3 + lumA2 + lumB - lumB1 + lumC + lumD - lumD1)/rectArea(ul,lr);
        
            // double xhueA = sumHueX[hist.size()-1][hist[0].size()-1];
            // double yhueA = sumHueY[hist.size()-1][hist[0].size()-1];
            // // double xhueB = sumHueX[hist.size()-1][hist[0].size()-1];
            // // double yhueB = sumHueY[hist.size()-1][hist[0].size()-1];
            // double xhueC = sumHueX[hist.size()-1][ul.second-1];
            // double yhueC = sumHueY[hist.size()-1][ul.second-1];
            // double xhueD = sumHueX[ul.first-1][hist[0].size()-1];
            // double yhueD = sumHueY[ul.first-1][hist[0].size()-1];
            // double xhueE = sumHueX[lr.first][hist[0].size()-1];
            // double yhueE = sumHueY[lr.first][hist[0].size()-1];
            // double xhueG = sumHueX[lr.first][lr.second];
            // double yhueG = sumHueY[lr.first][lr.second];             
            // double xhueF = sumHueX[lr.first][ul.second-1];
            // double yhueF = sumHueY[lr.first][ul.second-1];
            // double xhueH = sumHueX[ul.first-1][lr.second];
            // double yhueH = sumHueY[ul.first-1][lr.second];
            // double xhueI = sumHueX[ul.first-1][ul.second-1];
            // double yhueI = sumHueY[ul.first-1][ul.second-1];

            // double avgHueX = (xhueA - xhueD + xhueE - xhueF + xhueG - xhueC + xhueF + xhueH + xhueI + xhueG)/rectArea(ul,lr);

            // double avgHueY = (yhueA - yhueD + yhueE - yhueF + yhueG - yhueC + yhueF + yhueH + yhueI + yhueG)/rectArea(ul,lr);

             

            // double satavg = (sumSat[hist.size()-1][hist[0].size()-1] - sumSat[ul.first-1][hist[0].size()-1] + sumSat[lr.first][hist[0].size()-1]
            // - sumSat[lr.first][ul.second-1] + sumSat[lr.first][lr.second] - sumSat[hist.size()-1][ul.second-1] + sumSat[lr.first][ul.second-1]
            // + sumSat[ul.first-1][lr.second] + sumSat[ul.first-1][ul.second-1] + sumSat[lr.first][lr.second])/rectArea(ul,lr);

            // cout << "print rectarea" << endl;
            // cout << rectArea(ul,lr) << endl;
            // cout << "print satavg" << endl;
            // cout << satavg * rectArea(ul,lr) << endl;

            // double lumavg = (sumLum[hist.size()-1][hist[0].size()-1] - sumLum[ul.first-1][hist[0].size()-1] + sumLum[lr.first][hist[0].size()-1]
            // - sumLum[lr.first][ul.second-1] + sumLum[lr.first][lr.second] - sumLum[hist.size()-1][ul.second-1] + sumLum[lr.first][ul.second-1]
            // + sumLum[ul.first-1][lr.second] + sumLum[ul.first-1][ul.second-1] + sumLum[lr.first][lr.second])/rectArea(ul,lr);

            HSLAPixel returnpixel(trueavg,satavg,lumavg,1.0);
            return returnpixel;

        }
        // If ul and lr are the same;
        if(ul.first == lr.first && ul.second == lr.second){
            // cout << "stats.cpp: " << __LINE__ << endl;
            if (ul.first == 0 && ul.second == 0){
                double avgHueX = sumHueX[0][0];
                double avgHueY = sumHueY[0][0];
                double trueavg = atan2(avgHueY,avgHueX) * 180/PI ; 

                    if(trueavg < 0){
                        trueavg = trueavg + 360;
                    }

                double satavg = sumSat[0][0];
                double lumavg = sumSat[0][0];
                HSLAPixel returnpixel(trueavg,satavg,lumavg,1.0);
                return returnpixel;
            }
            else if(ul.first == 0 && ul.second != 0){
                // cout << "stats.cpp: " << __LINE__ << endl;
                double xhueA = sumHueX[lr.first][lr.second];
                double yhueA = sumHueY[lr.first][lr.second];
                double xhueB = sumHueX[lr.first][lr.second-1];
                double yhueB = sumHueY[lr.first][lr.second-1];

                double avgHueX = xhueA - xhueB;
                double avgHueY = yhueA - yhueB;
                
                double trueavg = atan2(avgHueY,avgHueX) * 180/PI ; 

                    if(trueavg < 0){
                        trueavg = trueavg + 360;
                    }
                double satavg = sumSat[lr.first][lr.second] - sumSat[lr.first][lr.second-1];
                double lumavg = sumSat[lr.first][lr.second] - sumSat[lr.first][lr.second-1];

                HSLAPixel returnpixel(trueavg,satavg,lumavg,1.0);
                return returnpixel;    
            }
            else if(ul.first != 0 && ul.second == 0){
                // cout << "stats.cpp: " << __LINE__ << endl;
                double xhueA = sumHueX[lr.first][lr.second];
                double yhueA = sumHueY[lr.first][lr.second];
                double xhueB = sumHueX[lr.first-1][lr.second];
                double yhueB = sumHueY[lr.first-1][lr.second];

                double avgHueX = xhueA - xhueB;
                double avgHueY = yhueA - yhueB;
                
                double trueavg = atan2(avgHueY,avgHueX) * 180/PI ; 

                    if(trueavg < 0){
                        trueavg = trueavg + 360;
                    }
                double satavg = sumSat[lr.first][lr.second] - sumSat[lr.first-1][lr.second];
                double lumavg = sumSat[lr.first][lr.second] - sumSat[lr.first-1][lr.second];

                HSLAPixel returnpixel(trueavg,satavg,lumavg,1.0);
                return returnpixel;    
            }
            else{
                // cout << "is it here?theendxd" << endl;
                double xhueA = sumHueX[lr.first][lr.second];
                double yhueA = sumHueY[lr.first][lr.second];
                double xhueB = sumHueX[lr.first-1][lr.second];
                double yhueB = sumHueY[lr.first-1][lr.second];
                double xhueC = sumHueX[lr.first][lr.second-1];
                double yhueC = sumHueY[lr.first][lr.second-1];
                double xhueD = sumHueX[lr.first-1][lr.second-1];
                double yhueD = sumHueY[lr.first-1][lr.second-1];

                double avgHueX = xhueA - xhueB - xhueC + xhueD;
                double avgHueY = yhueA - yhueB - yhueC + yhueD;
                
                double trueavg = atan2(avgHueY,avgHueX) * 180/PI ; 

                    if(trueavg < 0){
                        trueavg = trueavg + 360;
                    }
                 double satavg = sumSat[lr.first][lr.second] - sumSat[lr.first-1][lr.second] - sumSat[lr.first][lr.second-1] 
                + sumSat[lr.first-1][lr.second-1];

                 double lumavg = sumLum[lr.first][lr.second] - sumLum[lr.first-1][lr.second] - sumLum[lr.first][lr.second-1] 
                + sumLum[lr.first-1][lr.second-1];

                HSLAPixel returnpixel(trueavg,satavg,lumavg,1.0);
                return returnpixel;
            }

        }
        
    }

vector<int> stats::buildHist(pair<int,int> ul, pair<int,int> lr){
    vector<int> rvect;
    for(int i = 0; i < 36; i++){
        rvect.push_back(BHHelper(ul,lr,i));
    }
    return rvect;
}

int stats::BHHelper(pair<int,int> ul, pair<int,int> lr,int i){
    if(ul.first <= lr.first && ul.second <= lr.second){
        if(ul.first == 0 && ul.second == 0 ){
            return hist[lr.first][lr.second][i];
        }
        else if(ul.first != 0 && ul.second ==0){
            int hi1 = hist[lr.first][lr.second][i];
            int hi2 = hist[ul.first-1][lr.second][i];
            return hi1-hi2;
        }
        else if(ul.first == 0 && ul.second != 0){
            int hi1 = hist[lr.first][lr.second][i];
            int hi2 = hist[ul.first][lr.second-1][i];
            return hi1 - hi2;
        }
        else{
            int hi1 = hist[lr.first][lr.second][i];
            int hi2 = hist[ul.first-1][lr.second][i];
            int hi3 = hist[lr.first][ul.second-1][i];
            int hi4 = hist[ul.first-1][ul.second-1][i];
            return hi1 - hi2 - hi3 + hi4;
        }
    }
    if(ul.first > lr.first && ul.second <= lr.second){
        pair<int,int> uright(ul.first,ul.second);
        pair<int,int> lright(hist.size()-1,lr.second);
        pair<int,int> uleft(0,ul.second);
        pair<int,int> lleft(lr.first,lr.second);
        return BHHelper(uright,lright,i) + BHHelper(uleft,lleft,i);
    }

    if(ul.first <= lr.first && ul.second > lr.second){
        pair<int,int> udown(ul.first,ul.second);
        pair<int,int> ldown(lr.first,hist[0].size()-1);
        pair<int,int> uup(ul.first,0);
        pair<int,int> lup(lr.first,lr.second);
        return BHHelper(udown,ldown,i) + BHHelper(uup,lup,i);
    }

    else{
        pair<int,int> ulul(0,0);
        pair<int,int> ullr = lr;

        pair<int,int> urul(ul.first,0);
        pair<int,int> urlr(hist.size()-1,lr.second);

        pair<int,int> lrul = ul;
        pair<int,int> lrlr(hist.size()-1,hist[0].size()-1);

        pair<int,int> llul(0,ul.second);
        pair<int,int> lllr(lr.first,hist[0].size()-1);
        return BHHelper(ulul,ullr,i) + BHHelper(urul,urlr,i) + BHHelper(lrul,lrlr,i) + BHHelper(llul,lllr,i);
    }
}
/**
vector<int> stats::buildHist(pair<int,int> ul, pair<int,int> lr){
   // when ul and lr are the same
    if(ul.first == lr.first && ul.second == lr.second){
        if(ul.first == 0 && ul.second == 0){
            return hist[0][0];
        }
        if(ul.first == 0 && ul.second != 0){
            vector<int> hA = hist[ul.first][ul.second];
            vector<int> hB = hist[ul.first][ul.second-1];
            for(int i = 0; i < 36; i++){
            hA[i] = hA[i] - hB[i];
        }
        return hA;
        }
        if(ul.first != 0 && ul.second == 0){
            vector<int> hA = hist[ul.first][ul.second];
            vector<int> hB = hist[ul.first-1][ul.second];
            for(int i = 0; i < 36; i++){
            hA[i] = hA[i] - hB[i];
        }
        return hA;
        }
        if(ul.first != 0 && ul.second != 0){
            vector<int> hA = hist[ul.first][ul.second];
            vector<int> hB = hist[ul.first][ul.second-1];
            vector<int> hC = hist[ul.first-1][ul.second-1];
            vector<int> hD = hist[ul.first-1][ul.second];
            for(int i = 0; i< 36; i++){
                hA[i] = hA[i] - hB[i] - hD[i] + hC[i];
            }
            return hA;
        }   
    }
    // ul is 0,0 case
    if(ul.first == 0 && ul.second == 0 && lr.first != 0 && lr.second != 0){
        vector<int> histogram = hist[lr.first][lr.second];
        return histogram;
    }
    if( ul.first <= lr.first && ul.second <= lr.second){
        cout << "called correclty? " <<  endl;
        cout << "verifying that this is the rolledback stats" << endl;
    //     vector<int> oghistogram = hist[lr.first][lr.second];
    //     vector<int> blhistogram = hist[ul.first-1][lr.second];
    //     vector<int> uphistogram = hist[ul.first-1][ul.second-1];
    //     vector<int> urhistogram = hist[lr.first][ul.second-1];
    //     for(int i = 0; i < 36; i++){
    //         oghistogram[i] = oghistogram[i] - blhistogram[i] - urhistogram[i] + uphistogram[i];
    //     }
    //     return oghistogram;
    // }
    
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
    // When ul is 0,0
    if(ul.first == 0 && ul.second == 0){
        vector<int> histogram = hist[lr.first][lr.second];
        return histogram;
    }
    else{
        cout << "temporary" << endl;
        return hist[lr.first][lr.second];
    }
    }
    // Case 5: getAvg is called with y = 0  X WRAPPING
   // Case 6: getAvg is called with y != 0 X WRAPPING
   // Case 7: getAvg is called with x = 0 and y != 0 Y WRAPPING
   // Case 8: getAvg is called with x !=0  Y WRAPPING
   // Case 5: 
    if((ul.first >= lr.first && ul.second <= lr.second)){
        if(ul.second == 0){
            vector<int> hA = hist[hist.size()-1][lr.second];
            vector<int> hB = hist[lr.first][lr.second];
            vector<int> hC = hist[ul.first - 1][lr.second];

            for(int i = 0; i < 36; i++){
                hA[i] = hA[i] + hB[i] - hC[i];
            }
            return hA;
        }
        // Case 6
        else{
            vector<int> hA = hist[hist.size()-1][lr.second];
            vector<int> hB = hist[lr.first][lr.second];
            vector<int> hC = hist[ul.first - 1][lr.second];
            vector<int> hD = hist[hist.size()-1][ul.second-1];
            vector<int> hF = hist[lr.first][ul.second-1];
            vector<int> hE = hist[ul.first-1][ul.second-1];

            for(int i = 0; i < 36; i++){
                hA[i] = hA[i] - hC[i] + hB[i] - hD[i] + hE[i] - hF[i];
            }
            return hA;
        }
        }
        // Case 7: y wrapping ul first is zero 
        if(ul.first <= lr.first && ul.second >= lr.second){
            if(ul.first == 0){
                vector<int> hA = hist[lr.first][hist[0].size()-1];
                vector<int> hC = hist[lr.first][ul.second-1];
                vector<int> hB = hist[lr.first][lr.second];

                 for(int i = 0; i < 36; i++){
                    hA[i] = hA[i] + hB[i] - hC[i];
                    }
                return hA;
            }
            else{
                // Case 8
                vector<int> hA = hist[lr.first][hist[0].size()-1];
                vector<int> hB = hist[lr.first][lr.second];
                vector<int> hC = hist[lr.first][ul.second-1];
                vector<int> hD = hist[ul.first-1][hist[0].size()-1];
                vector<int> hE = hist[ul.first-1][ul.second-1];
                vector<int> hF = hist[ul.first-1][lr.second];

                for(int i = 0; i < 36; i++){
                    hA[i] = hA[i] + hB[i] - hC[i] - hD[i] + hE[i] - hF[i];
                    }
                return hA;

            }
        }
        // Case 9 : double wrapping
    }
    
    
    





/**/// takes a distribution and returns entropy
// partially implemented so as to avoid rounding issues.
// is already done huheuheuheuh

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
