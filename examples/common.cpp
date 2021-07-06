/*
    Copyright (c) 2013, Philipp Krähenbühl
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
        * Neither the name of the Stanford University nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY Philipp Krähenbühl ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL Philipp Krähenbühl BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "common.h"
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

// Store the colors we read, so that we can write them again.
int nColors = 0;
int colors[255];

int getColor( const unsigned char * c ){
	return c[0] + 256*c[1] + 256*256*c[2];
}

void putColor( unsigned char * c, int cc ){
	c[0] = cc&0xff; c[1] = (cc>>8)&0xff; c[2] = (cc>>16)&0xff;
}

// Produce a color image from a bunch of labels
unsigned char * colorize( const VectorXs & labeling, int W, int H ){
	unsigned char * r = new unsigned char[ W*H*3 ];
	for( int k=0; k<W*H; k++ ){
		int c = colors[ labeling[k] ];
		putColor( r+3*k, c );
	}
	//printf("%d %d %d \n",r[0],r[1],r[2]);
	return r;
}


// Read the labeling from an OpenCV image
//VectorXs getLabeling( cv::Mat img, int M ){
//
//	std::cout << img << std::endl;
//
//	VectorXs res(img.rows * img.cols);
//	for( int i = 0; i < img.rows; i++ ) {
//		for( int j = 0; j < img.cols; j++ ) {
//			// Map the color to a label
//			auto c = img.at<uchar>(i, j);
//			printf("%d \n", c);
//		for( int k=0; k < nColors && c!=colors[i]; i++ );
//		if (c && i==nColors){
//			if (i<M)
//				colors[nColors++] = c;
//			else
//				c=0;
//		}
//			res[i*img.cols + j] = c?i:-1;
//		}
//	}
//	return res;
//}

// Read the labeling from a file
// Read the labeling from a file
VectorXs getLabeling( const unsigned char * im, int N, int M ){
    VectorXs res(N);
    //printf("%d %d %d \n",im[0],im[1],im[2]);
    for( int k=0; k<N; k++ ){
        // Map the color to a label
        int c = getColor( im + 3*k );
        int i;
        for( i=0;i<nColors && c!=colors[i]; i++ );
        if (c && i==nColors){
            if (i<M)
                colors[nColors++] = c;
            else
                c=0;
        }
        res[k] = c?i:-1;
    }
    return res;
}
//
//VectorXs getLabeling( const unsigned char * im, int N, int M ){
//	VectorXs res(N);
////	printf("%d %d %d \n",im[0],im[1],im[2]);
//	for( int k=0; k<N; k++ ){
//		// Map the color to a label
//        auto rgb = im + 3*k;
//		int c = getColor( im + 3*k );
//		int i;
//		for( i=0;i<nColors && c!=colors[i]; i++ );
////        if (c && i==nColors){
//		if (i==nColors){
//			if (i<M) {
//				colors[nColors++] = c;
//                printf("RGB: %d %d %d \n",rgb[0],rgb[1],rgb[2]);
//				std::cout << "\tColour " << nColors << ':' << c << std::endl;
//			}
//			else
//				c=-1;
//		}
//		// Include black as label
////        res[k] = c>?i:-1;
//		res[k] = c>-1?i:-1;
//
//	}
//	return res;
//}

// Prints image data to console
void print( const unsigned char * data, const int nrows, const int ncols) {
    const uint32_t& truc = 200u;
    std::cout << std::fixed;
    std::cout << std::setprecision(6);

    for( auto i = 1000u; i <= truc && i < nrows; ++i )
    { // iterate rows
        if ( i == truc ) { // add ellipsis for truncated rows
            std::cout << " ... " << std::endl;
            i = nrows - 1u;
        }
        for( auto j = 1000u; j <= truc && j < ncols; ++j )
        { // iterate columns
            if ( j == truc )
            { // add ellipsis for truncated cols
                std::cout << "... ";
                j = ncols - 1u;
            }
            std::cout << ' ' << data[ncols * i + j] << ' ';

        }
        std::cout << std::endl;
    }
}

// Prints image data to console
void print( VectorXs data, const int nrows, const int ncols) {
	const uint32_t& truc = 30u;
	std::cout << std::fixed;
	std::cout << std::setprecision(6);

	for( auto i = 0u; i <= truc && i < nrows; ++i )
	{ // iterate rows
		if ( i == truc ) { // add ellipsis for truncated rows
			std::cout << " ... " << std::endl;
			i = nrows - 1u;
		}
		for( auto j = 0u; j <= truc && j < ncols; ++j )
		{ // iterate columns
			if ( j == truc )
			{ // add ellipsis for truncated cols
				std::cout << "... ";
				j = ncols - 1u;
			}
			std::cout << ' ' << data[ncols * i + j] << ' ';

		}
		std::cout << std::endl;
	}
}


