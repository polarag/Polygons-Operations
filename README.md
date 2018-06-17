






**Project Description**

It is required to develop a program to do operations on polygons data. The program use a defined string format to represent polygons. All polygons will be in one line input. For example:

**Polygons=[(1,1),(4,1),(4,5),(1,5);(3,4),(6,4),(6,12),(3,12)]**

**Polygons Data**

The Polygons line contains a list of polygons data separated by &#39;;&#39;. Fields of a Polygon is represented by a set of points separated by &#39;,&#39;. The number of polygons are up to 1000 polygon. Each polygon has up to 100 points.

**Definition of Redundant Point**

A redundant point is a point of the polygon points that can be deleted without change in the polygon shape. Like
(1,1),(2,1),(4,1),(4,3),(1,3)
(1,2),(4,2),(4,2),(4,8),(1,8)
(1,2),(4,2),(4,2),(4,2),(4,8),(1,8)

In the second case two neighbor identical points any one of them can be redundant (you should select only the second one). If more than two points are identical and follow each other, all of them are redundant except the first point of them.

**Intersecting Polygons**

Intersecting Polygons are polygons sharing common area, side, or point(s).

**Connected Polygons**

Two Connected Polygons are polygons that are intersecting or polygons which have path from one to the other through intersecting polygons.

**Operations**

When the program start, the user enters one Polygons Line in the defined above format then followed by **one or more** operations from the below table (each operation in a line). The program ends when it reads **Quit** operation.

|  Operation | Action Required from the Program |
| --- | --- |
|  **Number\_Polygons** | Print the number of polygons. |
| **Total\_Number\_Points** | Print the total number of points in all polygons. |
| **Minimum\_X** | Print the minimum X value of all points. |
| **Maximum\_X** | Print the maximum X value of all points |
| **Minimum\_Y** | Print the minimum Y value of all points. |
| **Maximum\_Y** | Print the maximum Y value of all points |
| **Enclosing\_Rectangle** | Print the minimum Enclosing Rectangle that includes all polygons inside it. |
| **Total\_Redundant\_Points** | The number of Redundant points in all polygons |
| **Quit** | End program |
|  **Polygon\_Points** n | List all points of the nth polygon (neglecting redundant points) n start from 1 (1 means the first polygon) output should be in the same format of input polygons string i.e.
(1,1),(4,1),(4,2),(1,2) |
| **Point\_Polygons** (2,1) | List all polygons IDs (ID is 1 for the first polygon, 2 for the second polygon,...)  of polygons that have the point (2,1) in their points list The output is a comma separated IDs of polygons having the point like2,4,6,10 |
| **List\_Polygons\_Points More** n | List Polygons having more than n points excluding redundant points where n is an integer.The output is a comma separated IDs of polygons like2,4,6,10 |
| **List\_Polygons\_Points Less** n | List Polygons having less than n points excluding redundant points where n is an integer. The output is a comma separated IDs of polygons like2,4,6,10 |
| **List\_Polygons\_Points Equal** n | List Polygons having exactly n points excluding redundant points where n is an integer. The output is a comma separated IDs of polygons like2,4,6,10 |
| **List\_Points\_Polygons More** n | List all Points that are in the list of more than n polygons where n is an integer.The output is a comma separated points like(3,2),(4,1) |
| **List\_Points\_Polygons Less** n | List all Points that are in the list of less than n polygons where n is an integer. The output is a comma separated points like(3,2),(4,1) |
| **List\_Points\_Polygons Equal** n | List all Points that are in the list of less than n polygons where n is an integer. The output is a comma separated points like(3,2),(4,1) |
| **Polygon\_Perimeter** n | Print the perimeter of the nth polygon. |
| **List\_Triangles** | List all Polygon IDs of polygons that are triangles.The output is a comma separated IDs of polygons like2,4,6,10 |
| **List\_Rectangles** | List all Polygon IDs of polygons that are rectangles. The output is a comma separated IDs of polygons like2,4,6,10 |
| **List\_Trapezoid** | List all Polygon IDs of polygons that are trapezoid.The output is a comma separated IDs of polygons like2,4,6,10 |
|  **Inside\_Rectangle** (1,2),(1,5),(6,5),(6,1) | List all Polygon IDs of polygons that are inside the given rectangle. The output is a comma separated IDs of polygons like2,4,6,10 |
| **Inside\_Circle** (1,2),5 | List all Polygon IDs of polygons that are inside the given Circle (Center, radius in the format (1,2),5 ). The output is a comma separated IDs of polygons like2,4,6,10 |
| **Polygon\_Area** n | Print the polygon area of the nth polygon |
| **Polygons\_Area\_Range** minArea,maxArea | List all Polygon IDs of polygons that have area &lt;= minArea and &gt;=maxArea. The output is a comma separated IDs of polygons like2,4,6,10 |
| **Polygons\_Enclosing\_Point** (1,2) | List all Polygon IDs of polygons that have the point (1,2) inside it (or on its boundaries). The output is a comma separated IDs of polygons like2,4,6,10 |
| **Is\_Intersecting** i,j | Print TRUE if ith polygon intersects the jth polygon |
| **Intersecting\_Group** 3,5,6 | Print TRUE if the list of polygon are all intersecting with each other (each one is intersecting with all other polygons) |
| **Largest\_Intersecting\_Pair** | Print the two IDs of polygons that are intersecting and having the largest sum of area. The output is a comma separated IDs of polygons like2,4 |
| **Largest\_Rectangle\_Inside** n | Print the largest rectangle that can inside the nth polygon. output should be in the same format of input polygons string i.e.
(1,1),(4,1),(4,2),(1,2) |
| **Largest\_Circle\_Inside** n | Print the largest circle that can inside the nth polygon. output should be in the format center, radius i.e.
(1,1),5 |
| **Is\_Connected** i,j | Print TRUE if ith polygon is connected to the jth polygon |
| **Is\_Connected\_Group** 1,2,5 | Print TRUE if all polygon in the list are connected. |
| **Maximum\_Intersecting\_Group** | List polygon IDs forming the largest set of polygons that are intersecting (any ID should intersect with All other IDs in the list) |
| **Maximum\_Connected\_Group** | List polygon IDs forming the largest set of polygons that are connected directly or indirectly (through another polygon) |

