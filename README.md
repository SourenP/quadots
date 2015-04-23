## Quadots
*C++ library for manipulating points on 2D space using quad trees*

### Description
Quadots is a C++ library of for making 2D simulations of a set of points. More specifically, the movement of these points based on some logic the user defines.

Points have x/y coordinates, a velocity, a direction and a behavior. The significance of the behavior of dot is up to the user to define.

The library provides various functions that help construct behaviors, such as the neigherst neighbors of a point or the average direction of all points.

### Use
The user first creates a Simulation object to which he/she can add Points with behaviors.

The first step is to define a rule (since a behavior is a set of rules a point follows).

A rule is a function that takes a pointer to a point and a control object.
For example:

```
void rotate(Point::Point_p p, Control& c) {
    p->ang += 2;
}

// Simulation defines the type rule
Simulation::rule rot = &rotate;
```

This rule simply adds 2 degrees to the angle of a point.

We can also use the control function to depend the behavior of our point on other point. For example:


```
void rotate(Point::Point_p p, Control& c) {
    p->ang = c.avg_ang();
}

auto rot = &rotate;
```

But this is a more boring behavior, so we'll stick to our first one.

A behavior is a vector of rules. So we can construct a behavior with our single rule rotate like so:

```
Simulation::rule rot = &rotate;
Simulation::behavior circle = {rot};
```

Once we have our behavior, we need to create a Simulation to then add that behavior to it.

```
// Initialize Simulation
Simulation *s = new Simulation();

// Create behavior circle
int b = s->CreateBehavior(circle);
```

When a behavior is added to the Simulation, an index is returned. This index is then passed to a point to which you want to assign that behavior.


So let's make our points!

They will both have positions x = 200, y = 200

The first point will be facing at an angle = 0 and the other 180. So back to back.

The first has a velocity = 1 and the other 2.

And finally, we'll give them both the same behavior index b.

```
// Create two Points in the middle of the screen facing opposite directions
s->CreatePoint(200, 200, 0, 1, b);
s->CreatePoint(200, 200, 180, 2, b);
``` 

Now all that's left is to run the simulation. But since we want to see our points visually lets define a renderer which we'll pass in.

```
// Initialize Renderer
Renderer twodee = Renderer(400,400, 32);

// Run Simulation for 0 (infinite) steps
s->Run(0, twodee);
```

**Here is our full code:**
```
void rotate(Point::Point_p p, Control& c) {
    p->ang += 2;
}


int main()
{
    // Brains
    Simulation::rule rot = &rotate;
    Simulation::behavior circle = {rot};

    // Initialize Simulation
    Simulation *s = new Simulation();

    // Create behavior circle
    int b = s->CreateBehavior(circle);

    // Create two Points in the middle of the screen facing opposite directions
    s->CreatePoint(200, 200, 0, 1, b);
    s->CreatePoint(200, 200, 180, 2, b);

    // Initialize Renderer
    Renderer twodee = Renderer(400,400, 32);

    // Run Simulation for 200 steps
    s->Run(200, twodee);

    delete s;
    return 0;
}
```

### Examples
**Boids:**

Dots that follow simple these simple rules to simulate a flocking behavior of birds:
* separation: steer to avoid crowding local flockmates
* alignment: steer towards the average heading of local flockmates
* cohesion: steer to move toward the average position (center of mass) of local flockmates

**Safari**
/
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
typedef vector<Dot_p>   target;
typedef void (*action)(Dot_p);

Space(int screen_w, int screen_h, int sps);

Dot_p           CreateDot(float x, float y, array<int8_t,4> color, float ang, float vel, int type);
void            Run(vector<pair<target, action>> tas);
float           get_distance(const Dot_p a,const Dot_p b);

vector<Dot_p>   get_dots()
vector<Dot_p>   get_dots(int type)
vector<Dot_p>   get_neighbors(Dot_p d, int N)
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
