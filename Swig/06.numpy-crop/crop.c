/*
  Word.cpp
 
   Created on: 2015-10-25
       Author: gberseth
 */
#include "crop.h"
#include <stdlib.h>
#include <errno.h>


// void crop(int *arr_in, int dim1, int dim2, int d1_0, int d1_1, int d2_0, int d2_1, int **arr_out, int *dim1_out, int *dim2_out)
// {
//     int *arr=NULL;
//     int dim1_o=0;
//     int dim2_o=0;
//     int i,j;

//     //value checks
//     if ((d1_1 < d1_0) || (d2_1 < d2_0) ||
//         (d1_0 >= dim1) || (d1_1 >= dim1) || (d1_0 < 0) || (d1_1 < 0) ||
//         (d2_0 >= dim2) || (d2_1 >= dim2) || (d2_0 < 0) || (d2_1 < 0))
//     {
//         errno = EPERM;
//         goto end;
//     }

//     //output sizes
//     dim1_o = d1_1-d1_0;
//     dim2_o = d2_1-d2_0;

//     //memory allocation
//     arr = (int *)malloc(dim1_o*dim2_o*sizeof(int));
//     if (arr == NULL)
//     {
//         errno = ENOMEM;
//         goto end;
//     }

//     //copying the cropped arr_in region to arr (naive implementation)
//     printf("\n--- d1_0=%d d1_1=%d (rows)  -- d2_0=%d d2_1=%d (columns)\n",d1_0,d1_1,d2_0,d2_1);
//     for (j=0; j<dim1_o; j++)
//     {
//         for (i=0; i<dim2_o; i++)
//         {
//             arr[j*dim2_o+i] = arr_in[(j+d1_0)*dim2+(i+d2_0)];
//             printf("%d ",arr[j*dim2_o+i]);
//         }
//         printf("\n");
//     }
//     printf("---\n\n");

// end:
//     *dim1_out = dim1_o;
//     *dim2_out = dim2_o;
//     *arr_out = arr;
// }


void crop(long *arr_in, int dim1, int dim2, int d1_0, int d1_1, int d2_0, int d2_1, long **arr_out, int *dim1_out, int *dim2_out)
{
    long *arr=NULL;
    int dim1_o=0;
    int dim2_o=0;
    int i,j;

    //value checks
    if ((d1_1 < d1_0) || (d2_1 < d2_0) ||
        (d1_0 >= dim1) || (d1_1 >= dim1) || (d1_0 < 0) || (d1_1 < 0) ||
        (d2_0 >= dim2) || (d2_1 >= dim2) || (d2_0 < 0) || (d2_1 < 0))
    {
        errno = EPERM;
        goto end;
    }

    //output sizes
    dim1_o = d1_1-d1_0;
    dim2_o = d2_1-d2_0;

    //memory allocation
    arr = (long *)malloc(dim1_o*dim2_o*sizeof(long));
    if (arr == NULL)
    {
        errno = ENOMEM;
        goto end;
    }

    //copying the cropped arr_in region to arr (naive implementation)
    printf("\n--- d1_0=%d d1_1=%d (rows)  -- d2_0=%d d2_1=%d (columns)\n",d1_0,d1_1,d2_0,d2_1);
    for (j=0; j<dim1_o; j++)
    {
        for (i=0; i<dim2_o; i++)
        {
            arr[j*dim2_o+i] = arr_in[(j+d1_0)*dim2+(i+d2_0)];
            printf("%d ",arr[j*dim2_o+i]);
        }
        printf("\n");
    }
    printf("---\n\n");

end:
    *dim1_out = dim1_o;
    *dim2_out = dim2_o;
    *arr_out = arr;
}

