
# Assignment #2 Exercise 1
In this exercise we are exploring transformations and poly-line drawings. We were provided with a dog.txt file, with space seperated floating point numbers. The ith number and the i + 1th number encode a (x,y) position of vertex. When all vertices were drawn in sequence using linestrip a dog was formed.

The program had to follow these specifications:
- Specifies the viewing volume to be (0, 60, 0, 60) (left, right, bottom, top).
- Set the background to white.
- Around a circle of radius 25, centered at (30,30), draw, with immediate mode, the dog poly-line image at 8 different points along the circle.
- for each frame that is drawn rotate the dogs counterclockwise 1 degree about their point on the circle. Each dog should "spin" in place.

# Assignment #2 Exercise 2
In this exercise we draw a dot plot using a algorithm given in pseudo-code.

* Choose a random corner of a square.
* Choose a random point between the points of the square.
  * Choose a random corner of the square which is not diagonally opposite to the previous corner.
  * let p be a point halfway between the previous point and corner.
  * draw a point.
The program had to follow these specifications.

- take command line arguments for N, screen width, screen height.
- Use glOrtho to set the viewing volume to be (-1.1, 1.1, -1.1, 1.1).
- Set the background to white.
- Draw points in black of size 2.0.
- Use immediate mode to draw outside of the loop
- Program must support N as large as 5,000,000.

Attached Files
- exer1.cpp (The source code)
- exer2.cpp (The source code)


## Screenshots
## Exercise 2
![Exercise 2](https://i.imgur.com/3FNulmy.png)


## Authors

- Josh Bakelaar - 251139121

