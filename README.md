## Quadots
*C++ library for manipulating points on 2D space using quad trees*

### Description
Quadots is a C++ library of for making 2D simulations of a set of points. More specifically, the movement of these points based on some logic the user defines.

Points have x/y coordinates, a velocity, a direction and a behavior. The significance of the behavior of dot is up to the user to define.

The library provides various functions that help construct behaviors, such as the nearest neighbors of a point or the average direction of all points.

### Use

Let's simulate two points rotating in circles.

The first step is to define a the rule which will change the direction of a point by a little each step.
By applying this rule every step to a point, the point will rotate in a circle.

A rule is a function that takes as parameters a pointer to a Point and a Control.

Don't worry about what the Control does for now.

For example:

```c++
void rotate(Point::Point_p p, Control& c) {
    p->ang += 2;
}

Simulation::rule rot = &rotate;
```

Our rule is the ```rot``` object.

You don't assign a rule to a point, instead you assign a behavior, which is a set of rules it will follow.

So we can construct a behavior with our single rule rot like so:

```c++
Simulation::behavior circle = {rot};
```

Once we have our behavior, we can now create our simulation and add the behavior ```cirlce``` to it:

```c++
// Initialize Simulation
Simulation *s = new Simulation();

// Create behavior circle
int b = s->CreateBehavior(circle);
```

When a behavior is added to the Simulation, an index is returned. You pass this index to any point you want to have that behavior. So we save this "behavior index" in ```b```.

Now we're ready to make our points!

They will both have positions x = 200, y = 200.

The first point will be facing at an angle = 0 and the other 180. So back to back.

The first has a velocity = 1 and the other 2. So that the second draws a bigger circle.

And finally, we'll give them both the same behavior index ```b```.

```c++
// Create two Points in the middle of the screen facing opposite directions
s->CreatePoint(200, 200, 0, 1, b);
s->CreatePoint(200, 200, 180, 2, b);
``` 

Now all that's left is to run the simulation. But since we want to see our points visually lets define a renderer to run the simulation with.

The renderer will be a window of size 400/400 and will run at 32 steps per second.

```c++
// Initialize Renderer
Renderer twodee = Renderer(400,400, 32);

// Run Simulation for 0 (infinite) steps
s->Run(0, twodee);
```

**Here is our full code:**
```c++
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

**Quadtrees**

A significant data structure for our library that we are going to implement ourselves.

Used for:
* Get nearest neighbors
* Get points in area (either square or circle)
* Detect collision of two points based on some distance scalar.
* 

### Measurements
* How efficent it is to manipulate dots.
* Compare boids complexity with other boids implementation.
* Compare our quadtree implementation runtime with other quadtree libraries.
