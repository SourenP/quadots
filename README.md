## Quadots
*C++ library for manipulating points on 2D space using quad trees*

### Description
Quadots is a C++ library of for making 2D simulations of a set of points. More specifically, the movement of these points based on some logic the user defines.

Points on the 2D space are called *dots* and have an x/y coordinate, a velocity, a direction and a type. The significance of the a type of dot is up to the user to define.

The library provides functions to get information about dots and manipulate their behavior based on that.

### Implementation
**Dot:**
```
int                 x_coordinate
int                 y_coordinate
float               velocity
pair<float,float>   direction
int                 type
```

**Space:**
```
bool                add_dot(Dot d)
bool                remove_dot(Dot d)

Dot                 set_coord(Dot d, int x, int y)
Dot                 set_vel(Dot d, float vel)
Dot                 set_dir(Dot d, pair<float, float> dir)
Dot                 set_type(int t)

vector<Dot>         get_dots()
vector<Dot>         get_dots(int type)
vector<Dot>         get_neighbors(Dot d, int N)
float               get_distance(Dot d, Dot d)
```
