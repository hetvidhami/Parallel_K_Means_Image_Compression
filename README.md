# Parallel K-Means Image Compression

## Overview
This project implements the K-Means clustering algorithm in C++ for image compression. The algorithm clusters points in a 2D space and assigns them to the nearest cluster based on Euclidean distance, then updates the clusters iteratively until convergence or a maximum number of iterations.

## Features
- Efficient parallelized implementation using OpenMP.
- Handles large datasets with customizable parameters.
- Outputs clustering results and visualizations using Gnuplot.

## Algorithm Workflow
1. **Initialization**:
   - Randomly generate points and initial cluster centroids.
   - Points and clusters are stored as objects with coordinates and cluster assignments.

2. **Assignment Step**:
   - Compute the distance of each point to all clusters.
   - Assign each point to the nearest cluster.

3. **Update Step**:
   - Update cluster centroids based on the mean position of points assigned to them.
   - Check for convergence by verifying if cluster centroids change.

4. **Termination**:
   - Stop when the clusters stabilize or the maximum number of iterations is reached.

5. **Visualization**:
   - Generate a visualization of clustered points using Gnuplot.

## Customizable Parameters
- `num_point`: Number of points to generate.
- `num_cluster`: Number of clusters.
- `max_iterations`: Maximum number of iterations for the algorithm.
- `max_range`: Range of coordinates for points and clusters.

## Technologies Used
- C++
- OpenMP for parallel processing.
- Gnuplot for visualization.
