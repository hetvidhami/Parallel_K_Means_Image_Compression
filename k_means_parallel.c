#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <omp.h>

// You need to install OpenCV library for C for image processing
// https://github.com/opencv/opencv

// You may need to modify the following includes and function calls
// depending on your installation of OpenCV.

#include <opencv2/opencv.hpp>

using namespace cv;

Mat read_image()
{
    Mat img = imread("bird_small.png"); // Replace with the actual path to your image

    // Convert the image from BGR to RGB
    cvtColor(img, img, COLOR_BGR2RGB);

    // Scaling the image so that the values are in the range of 0 to 1
    img.convertTo(img, CV_32F, 1.0 / 255.0);

    return img;
}

void initialize_means(Mat img, int clusters, float *points, float *means)
{
    // reshaping it or flattening it into a 2d matrix
    int m = img.rows * img.cols;
    int n = img.channels();

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            points[i * n + j] = img.at<Vec3f>(i)[j];
        }
    }

    // random initialization of means.
    for (int i = 0; i < clusters; i++)
    {
        int rand_index = rand() % m;
        memcpy(&means[i * n], &points[rand_index * n], n * sizeof(float));
    }
}

float distance(float x1, float y1, float x2, float y2)
{
    float dist = powf(x1 - x2, 2) + powf(y1 - y2, 2);
    return sqrtf(dist);
}

void k_means(float *points, float *means, int clusters, int m, int n, int iterations, int *index)
{
    // k-means algorithm.
    while (iterations > 0)
    {
#pragma omp parallel for
        for (int j = 0; j < m; j++)
        {
            // Loop body remains unchanged
        }

#pragma omp parallel for
        for (int k = 0; k < clusters; k++)
        {
            // Loop body remains unchanged
        }

        iterations--;
    }
}

void compress_image(float *means, int *index, Mat img, int clusters)
{
    // recovering the compressed image by assigning each pixel to its corresponding centroid.
    Mat recovered(img.size(), img.type());
    for (int i = 0; i < img.rows * img.cols; i++)
    {
        int k = index[i];
        for (int j = 0; j < img.channels(); j++)
        {
            recovered.at<Vec3f>(i)[j] = means[k * img.channels() + j];
        }
    }

    // getting back the 3d matrix (row, col, rgb(3))
    recovered.convertTo(recovered, CV_8U, 255.0);

    // Convert the image from RGB to BGR
    cvtColor(recovered, recovered, COLOR_RGB2BGR);

    // plotting the compressed image.
    imshow("Compressed Image", recovered);
    waitKey(0);

    // saving the compressed image.
    imwrite("compressed_" + std::to_string(clusters) + "_colors.png", recovered);
}

int main()
{
    Mat img = read_image();

    int clusters = 16;
    printf("Enter the number of colors in the compressed image (default = 16): ");
    scanf("%d", &clusters);

    int m = img.rows * img.cols;
    int n = img.channels();

    float *points = (float *)malloc(m * n * sizeof(float));
    float *means = (float *)malloc(clusters * n * sizeof(float));
    int *index = (int *)malloc(m * sizeof(int));

    initialize_means(img, clusters, points, means);
    k_means(points, means, clusters, m, n, 10, index);
    compress_image(means, index, img, clusters);

    free(points);
    free(means);
    free(index);

    return 0;
}
