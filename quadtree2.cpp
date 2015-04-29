#include "quadtree2.h"
#include "Point.h"

float get_distance(pair<float, float> a, pair<float, float> b) {
    return sqrt(pow(a.first - b.first,2) + pow(a.second - b.second,2));
}


quadtree2::quadtree2(int pLevel, double x, double y, double width, double height) {
    this->level = pLevel;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->nodes = vector<quadtree2*>();
    this->objects = vector<Point>();
}

/*
 * Splits the node into 4 subnodes
 */
 void quadtree2::split() {
   double subWidth = (this->width / 2);
   double subHeight = (this->height / 2);
 
   nodes.push_back(new quadtree2(level+1, x + subWidth, y, subWidth, subHeight));
   nodes.push_back(new quadtree2(level+1, x, y, subWidth, subHeight));
   nodes.push_back(new quadtree2(level+1, x, y + subHeight, subWidth, subHeight));
   nodes.push_back(new quadtree2(level+1, x + subWidth, y + subHeight, subWidth, subHeight));
 }

/*
 * Determine which node the object belongs to. -1 means
 * object cannot completely fit within a child node and is part
 * of the parent node
 */
 int quadtree2::getIndex(Point p) {
    int index = -1;

    double verMidpoint = this->x + 0.5*this->width;
    double horMidpoint = this->y + 0.5*this->height;

    if (p.y < horMidpoint) {
        if (p.x < verMidpoint)
            index = 0;
        else
            index = 1;
    } else {
        if (p.x > verMidpoint)
            index = 2;
        else
            index = 3;
    }

    return index;
}

/*
 * Insert the object into the quadtree. If the node
 * exceeds the capacity, it will split and add all
 * objects to their corresponding nodes.
 */
void quadtree2::insert(Point p) {
    // If tree is already split
    if (nodes.size()) {
        // get which node to put into
        int index = getIndex(p);
        // insert into that node
        nodes[index]->insert(p);
        return;
    }

    objects.push_back(p);
    if (objects.size() > MAX_OBJECTS && level < MAX_LEVELS) {
        split();
        for(Point p : objects) {
            int index = getIndex(p);
            nodes[index]->insert(p);
        }
        objects.clear();
    }
}

void quadtree2::retrieve(vector<Point>& robjects, Point p) {
    int index = getIndex(p);
    if (nodes.size()) {
        nodes[index]->retrieve(robjects, p);
    }

    for(Point p : objects) {
        robjects.push_back(p);
    }
}

/* Use this function for testing */
void quadtree2::traverseTree() {
    for(Point p : objects)
        cout << p.x << " " << p.y << " at level " << level << endl;

    for(quadtree2* n : nodes)
        n->traverseTree();
}

bool quadtree2::intersects(double rad, pair<float, float> c) {
    pair<float, float> topLeft(this->x, this->y); 
    pair<float, float> botLeft(this->x, this->y + this->height);
    pair<float, float> topRight(this->x + this->width, this->y);
    pair<float, float> botRight(this->x + this->width, this->y + this->height);

    if(get_distance(topLeft, c) < rad ||
        get_distance(botLeft, c) < rad ||
        get_distance(topRight, c) < rad ||
        get_distance(botRight, c) < rad )
        return true;
    return false;
}

vector<Point> quadtree2::getNearestNeighbours(float rad, pair<float, float> c) {
    stack<quadtree2*> s;
    vector<Point> neighbors;
    s.push(this);

    while(!s.empty()) {
        quadtree2 *T = s.top();
        s.pop();

        if (T->isLeaf()) {
            for (Point p : T->objects) {
                if(get_distance(make_pair(p.x, p.y), c) < rad) {
                    neighbors.push_back(p);
                }
            }
        } else {
            for(quadtree2* C : T->nodes) {
                if (C->isLeaf()) {
                    for (Point p : C->objects)
                        if(get_distance(make_pair(p.x, p.y), c) < rad)
                            neighbors.push_back(p);
                }
                else if (C->intersects(rad, c)) {
                    cout << C->level << endl;
                    s.push(C);
                }
            }
        }
    }
    return neighbors;
}

bool quadtree2::isLeaf() {
    return !nodes.size(); 
}

quadtree2::~quadtree2() {
    for(quadtree2* n : nodes) {
        delete n;
    }
}