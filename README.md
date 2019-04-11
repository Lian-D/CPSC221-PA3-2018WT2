# CPSC221-PA3-2018WT2
C++ Programming Assignment Authorized Release

The inspiration for this assignment came from an article about an artist whose work recreates classic portraits with a blocky effect. The exact algorithm he used is not given in the article, but we will create similar images using a strategy for image representation that underlies common lossy image compression algorithms.
![](https://www.ugrad.cs.ubc.ca/~cs221/2018W2/mps/p3/PA3pic1.png)
![](https://www.ugrad.cs.ubc.ca/~cs221/2018W2/mps/p3/prelim-stanley.05.png)

In specifying the algorithm we make several conventional assumptions, illustrated below:
- The origin, position (0,0), is in the upper left corner of the image.
- Rectangles are typically specified either by a pair of points at its upper left and lower right corners, or by an upper left point, together with dimensions (this assingment uses both).
- The upper left corner of a rectangle is the one nearest to the origin.
- Image locations are typically specified as (x,y), where x is a horizontal offset, and y is a vertical offset.
![](https://www.ugrad.cs.ubc.ca/~cs221/2018W2/mps/p3/PA3pic3.png)

The original image will be represented in memory as a 4-ary tree whose nodes contain information about square subsets of the image.

- Every node is the root of a subtree that represents a subset of the original image. Note that the region might not be contiguous in the original image.
- Every node also contains a pixel that represents the average color over the square in the original image.
- Every node contains a dimension that determines the size of the square it represents. If dimension == d, then the node represents a
- 2d×2d square.
- When a square is split into four smaller squares, the parent node represents the whole square, and the 4 children each contain a quadrant of the original.
- Each square is split into 4 equal sized quadrants by an optimal choice of “splitting” point, described below.
- Before pruning, every leaf in the tree corresponds to a pixel in the original image, and every pixel is represented by some leaf. The image below represents a part of the unpruned quadtree. We did not draw the leaves in the diagram.
![](https://www.ugrad.cs.ubc.ca/~cs221/2018W2/mps/p3/quadtrees.png)


Main files of focus are the Toqutree (Lian's code) and Stats (Nathan's code).
