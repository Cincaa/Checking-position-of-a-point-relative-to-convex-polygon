# Checking position of a point relative to convex polygon in ℝ^2

The algorithm follows a simple idea to check whether a point is inside or outside:
  - Draw a horizontal line to the right of each point and extend it to infinity
  - Count the number of times the line intersects with polygon edges.
  - A point is inside the polygon if either count of intersections is odd or point lies on an edge of polygon.  If none of the conditions is true, then point lies outside.

![Graphical representation](https://media.geeksforgeeks.org/wp-content/uploads/polygon1.png)

The decidability of hypothesis can be found in [Point relative to polygon.cpp](https://github.com/Cincaa/Checking-position-of-a-point-relative-to-convex-polygon/blob/master/Point%20relative%20to%20polygon.cpp) and the visual online representation in [index.html](https://github.com/Cincaa/Checking-position-of-a-point-relative-to-convex-polygon/blob/master/index.html), [main.css](https://github.com/Cincaa/Checking-position-of-a-point-relative-to-convex-polygon/blob/master/main.css) and `.js` files.

# Demo

https://check-position.herokuapp.com/index.html
