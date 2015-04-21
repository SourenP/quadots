## Quadots
*C++ library for manipulating points on 2D space using quad trees*

### Description
Quadots is a C++ library of for making 2D simulations of a set of points. More specifically, the movement of these points based on some logic the user defines.

Points on the 2D space are called *dots* and have an x/y coordinate, a velocity, a direction and a type. The significance of the a type of dot is up to the user to define.

The library provides functions to get information about dots and manipulate their behavior based on that.

### Use
The simulation has a Step function which is executed at a speed defined by the user.
The Step function takes a set of (target, action) pairs and executes the action on the each of the dots in target.
A target is a list of dots. This can be a discrete set of dots, a type or all dots.
An action is a function that takes a dot as an argument and manipulates it.

For example this simple program will simulate two black dots rotating in circles.
```
Space *s = new Space(400, 400, 12);
array<int8_t,4> black = {0,0,0,255};

auto dot1 = s->CreateDot(200, 200, black, 0, 1, 1);
auto dot2 = s->CreateDot(200, 200, black, 180, 1, 1);

vector<Dot_p> dots = {dot1, dot2};
void rotate(Dot_p d) {
  d->ang += 2;
}

s->Run( ({dot1, dot2}, rotate) );
```

### Examples
**Boids:**

Dots that follow simple these simple rules to simulate a flocking behavior of birds:
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
float               x
float               y
array<int8_t,4>		color
float               ang
float               vel
int                 type
```

**Space:**
```
typedef shared_ptr<Dot> Dot_p;

void                Run(pair<vector<Dot_p>, func(Dot_p)>(target, action), ... );

Dot_p               CreateDot(float x, float y, array<int8_t,4> color, float ang, float vel, int type)
void                RemoveDot(Dot_p d)

vector<Dot_p>       get_dots()
vector<Dot_p>       get_dots(int type)
vector<Dot_p>       get_neighbors(Dot_p d, int N)
float               get_distance(Dot_p d, Dot_p d)
vector<Dot_p>       on_collision(Type t1, Type t2, float threshold, func(t1,t2))
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
