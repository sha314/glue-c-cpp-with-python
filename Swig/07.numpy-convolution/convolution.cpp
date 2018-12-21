/*
  convolution.cpp
 
   Created on: 2018-12-21
       Author: shahnoor
 */
#include "convolution.h"
#include <stdlib.h>
#include <errno.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <omp.h>

using namespace std;

/****
 @param data       : is the input 1d array as a pointer
 @param columns     : columns in the input array
 @param thread_count  : number of thread to use
 @param data_out      : output array
 @prama dim_out      : row of the output array
***/
void convolve1d(
    double *data, int columns,
    int thread_count,
    double **data_out, int *dim_out)
{
    vector<double>   _forward_factor(columns),  _backward_factor(columns);

    for (size_t i=0; i < columns; ++i)
    {
        _forward_factor[i]  = (double) (columns - i + 1) / i;
        _backward_factor[i] = (double) (i + 1) / (columns - i);
    }

    cout << "cols " << columns << endl;

    // double *arr = new double[columns];
    std::vector<double> arr(columns);
    
    size_t step = columns / 1000 + 1;

    int th = omp_get_max_threads();
    if (thread_count > th || thread_count < 1){
        thread_count = th;
    }

// use paralalization here
#pragma omp parallel for schedule(dynamic) num_threads(thread_count)
    for (long j=0; j <columns; ++j)
    {
        double prob     = (double) j / columns;
        double factor   = 0;
        double binom    = 0;
        double prev     = 0;
        double binomNormalization_const = 1;
        double sum      = data[j];

        // forward iteraion part
        factor = prob / (1-prob);
        prev   = 1;

        for (long i=j+1; i<columns; ++i)
        {
            binom     = prev * _forward_factor[i] * factor;
            binomNormalization_const += binom;
            sum      += data[i] * binom;
            prev      = binom;
        }

        // backward iteration part
        factor = (1-prob)/prob;
        prev   = 1;

        for (long i=j-1; i>=0; --i)
        {
            binom     = prev * _backward_factor[i] * factor;
            binomNormalization_const += binom;
            sum      += data[i] * binom;
            prev      = binom;
        }

        // normalizing data
        arr[j] = sum / binomNormalization_const;
        if(j % step == 0) {
            cout << "\33[2K"; // erase the current line
            cout << '\r'; // return the cursor to the start of the line
//            cout << "row " << j << " ";
            cout << "progress " << j * 100 / double(columns) << " %";
            std::fflush(stdout);
        }

    }

    cout << "\33[2K"  << '\r';
    cout << "progress 100 %" << endl;

    // setting return value
    *dim_out = columns;
    // *data_out = arr; // if arr is naked array 
    *data_out = &arr[0]; // if arr is a vector

}


/****
 @param data_in       : is the input 1d array as a pointer
 @param n_rows        : rows in the input array
 @param n_columns     : columns in the input array
 @param thread_count  : number of thread to use
 @param data_out      : output array
 @prama dim1_out      : row of the output array
 @param dim2_out      : column of the output array
 
***/
void convolve2d(
    double *data_in, int n_rows, int n_columns,
    int thread_count,
    double **data_out, int *dim1_out, int *dim2_out
    ){
    
    vector<double>   _forward_factor(n_rows),  _backward_factor(n_rows);

    for (size_t i=0; i < n_rows; ++i)
    {
        _forward_factor[i]  = (double) (n_rows - i + 1) / i;
        _backward_factor[i] = (double) (i + 1) / (n_rows - i);
        // cout << _forward_factor[i] << ", " << _backward_factor[i] << endl;
    }

    // cout << "rows " << n_rows << endl;
    // cout << "cols " << n_columns << endl;

    // double *arr = new double[n_rows*n_columns];
    std::vector<double> arr(n_rows*n_columns);
    
    size_t step = n_rows / 1000 + 1;

    int th = omp_get_max_threads();
    if (thread_count > th || thread_count < 1){
        thread_count = th;
    }
// use paralalization here
#pragma omp parallel for schedule(dynamic) num_threads(thread_count)
    for (long row=0; row < n_rows; ++row){
        // cout << "row " << row << endl;
        // cout << "line : " << __LINE__ << endl;
        double prob     = (double) row / n_rows;
        double factor   = 0;
        double binom    = 0;
        double prev     = 0;
        double binomNormalization_const = 1;

        vector<double> sum(n_columns);
        for(size_t k{}; k < n_columns; ++k){
            sum[k] = data_in[row*n_columns + k];
        }

       // cout << "line : " << __LINE__ << endl;

        // forward iteration part
        factor = prob / (1-prob);
        prev   = 1;


        for (long i=row+1; i < n_rows; ++i)
        {
            binom     = prev * _forward_factor[i] * factor;
            binomNormalization_const += binom;
            for(size_t j{}; j < n_columns; ++j){
                sum[j] += data_in[i*n_columns + j] * binom;
            }
            prev      = binom;
        }
//        cout << "line : " << __LINE__ << endl;
        // backward iteration part
        factor = (1-prob)/prob;
        prev   = 1;

        for (long i=row-1; i>=0; --i)
        {
            // cout << i << ", " << prev << ", " << _backward_factor[i] << ", " << factor << endl;
            binom     = prev * _backward_factor[i] * factor;
            binomNormalization_const += binom;
            for(size_t j{}; j < n_columns; ++j){
                sum[j] += data_in[i*n_columns + j] * binom;
            }
            prev      = binom;
        }

       // cout << "line : " << __LINE__ << endl;
        // normalizing data
        for(size_t j{}; j < n_columns; ++j){
            arr[row*n_columns + j] = sum[j] / binomNormalization_const;
            // if(isnan(arr[row*n_columns + j])){
            //     cout << "nan " << endl;
            //     cout << "row " << row << endl;
            //     cout << "binomNormalization_const " << binomNormalization_const << endl;
            // }
//            cout << "j " << j << endl;
        }
        // cout << "line : " << __LINE__ << endl;
        if(row % step == 0) {
//             cout << "line : " << __LINE__ << endl;
            cout << "\33[2K"; // erase the current line
            cout << '\r'; // return the cursor to the start of the line
// //            cout << "row " << row << " ";
//             cout << "line : " << __LINE__ << endl;
            cout << "progress " << row * 100 / double(n_rows) << " %";
            std::fflush(stdout);
        }
    }
    cout << "\33[2K"  << '\r';
    cout << "progress 100 %" << endl;
    
    // setting return value
    *dim1_out = n_rows;
    *dim2_out = n_columns;
    // *data_out = arr; // if arr is naked array 
    *data_out = &arr[0]; // if arr is a vector
}

