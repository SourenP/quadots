## Quadots
*C++ library for manipulating points on 2D space using quad trees*

### Description
Quadots is a C++ library of for making 2D simulations of a set of points. More specifically, the movement of these points based on some logic the user defines.

Points on the 2D space are called *dots* and have an x/y coordinate, a velocity, a direction and a type. The significance of the a type of dot is up to the user to define.

The library provides functions to get information about dots and manipulate their behavior based on that.

### Uses
**Boids:**

Dots that follow simple these simple rules to simulate a flcoking behavior of birds:
* separation: steer to avoid crowding local flockmates
* alignment: steer towards the average heading of local flockmates
* cohesion: steer to move toward the average position (center of mass) of local flockmates

**Safari**

A group of animal types that interact with one another. For example:
* Jaguar: eats antelopes and lingers.
* Antelope: avoids jaguars and eats grass.
* Grass: gets eaten.

**Data Processing**

* Not sure yet

### Implementation
**Dot:**
```
int                 x_coordinate
int                 y_coordinate
float               velocity
pair<float,float>   direction
int                 type
int8_t              r
int8_t              g
int8_t              b
```

**Space:**
```
bool                add_dot(Dot d)
bool                remove_dot(Dot d)

Dot                 set_coord(Dot d, int x, int y)
Dot                 set_vel(Dot d, float vel)
Dot                 set_dir(Dot d, pair<float, float> dir)
Dot                 set_type(int t)
Dot                 set_color(int8_t r, int8_t g, int8_t b)

vector<Dot>         get_dots()
vector<Dot>         get_dots(int type)
vector<Dot>         get_neighbors(Dot d, int N)
float               get_distance(Dot d, Dot d)
vector<Dot>         on_collision(Type t1, Type t2, float threshold, func(t1,t2))
```

**Quadtrees**

A significant data structure for our library that we are going to implement ourselves.

Used for:
* get_neighbors
* on_collision
* 

### Measurements
* How efficent it is to manipulate dots.
* Compare boids complexity with other boids implementation.
* Compare our quadtree implementation runtime with other quadtree libraries.
