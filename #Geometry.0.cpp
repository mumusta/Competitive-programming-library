
/*

             N 90
            (0, 1)

   NW 135             NE 45
  (-1, 1)             (1, 1)

 W 180                    E 0
(-1,0)                   (1,0)

   SW 225             SE 315
  (-1, -1)           (1, -1)

             S 270
            (0,-1)
*/


#include <iostream>
#include <cmath>
#include <vector>
#include <complex>
#include <algorithm>
#define pp push_back

using namespace std;





typedef long double LD;
typedef complex < LD > point;


#define EPS 1e-9
#define PI ((LD)(acos(-1.0)))

#define X real()
#define Y imag()

#define vec(a,b) ((b) - (a)) // vector from a to b

#define length(v) ((LD)hypot((v).Y, (v).X))
// This is the length of the vector v. Note that: length(v) equal to sqrt(dot(v, v))
// = r is the modulus and it is the distance from (in polar representation),
// the origin to the point, length(v) return the r of v,
// this is equal to abs(v).

#define angle(v) (atan2((v).Y, (v).X))
// The Theta is called the argument and it is the angle in radian,
// formed between Line [(0, 0) <-> (v.x, v.y)] and the x-axis,
// this is equal to arg(v).

#define normalize(p) ((p) / length(p)) // normalize vector p

#define dot(a,b) ((conj(a) * (b)).real())
// Dot product is (a.x * b.x) + (a.y * b.y) for 2D vectors
// and equal a scaler value, Two vectors --> dot() --> scaler value.
// also dot(a,b) = length(a) * length(b) * cos the angle between a and b.
#define cross(a,b) ((conj(a) * (b)).imag()) // Cross product
// Cross product is only defined for 3D space, but here it is kind of a hack,
// Usually cross priduct produce a vector, but when we add extra dimention to each point
// by add z to each equal to zero, the cross product produce point contain only one information that are not equal 0,
// this function return the non zero value = x1*y2 - x2*y1.

#define lengthSqr(v) (dot(v, v))
// The Square of r, the square norm of the vector or,
// the square magnitude of the vector, it is like norm(v),
// but avoid using norm() and use this instead.

#define same(a,b) (lengthSqr(vec(a, b)) < EPS) // is same

// Roration tools, v is the point to rotate, t is theta and a is the point about.
#define polar(r,t) ((LD)(r) * exp(point(0, (t)))) // From (r, Theta) to (x, y)
#define rotate(v,t) (polar(v, t)) // we use polar() to perform rotation
#define rotateabout(v,t,a) (rotate(vec(a, v), t) + (a))
// create vector a->v, rotate arount origin then shift it back.

#define Dist(a,b) ((LD)hypot(b.X-a.X,b.Y-a.Y)) // Euclidean distance
#define sqDist(p1,p2) ((ll)((ll)((p2.X-p1.X)*(p2.X-p1.X))+(ll)((p2.Y-p1.Y)*(p2.Y-p1.Y))))
// Square Euclidean distance


point read_point(){ LD x, y; cin >> x >> y; return point(x, y); }



// Double comparison [-1 --> (a < b)] [0 --> (a = b)] [1 --> (a > b)]//{
int dcmp(LD a, LD b){ return fabs(a - b) < EPS ? 0 : a < b ? -1 : 1; }
//}


// Useful for sorting points while using complex class
bool pcmp (const point p1, const point p2){
    if (fabs(p1.X - p2.X) > EPS) return p1.X < p2.X;
    return p1.Y < p2.Y;
}


//[Transformations]//{

LD toDegreeFromMinutes(LD minutes){ return (minutes / 60.0); }

LD toRadians(LD degree){ return (degree * PI / 180.0); }

LD toDegree(LD radian){ if (radian < 0) radian += 2 * PI;
    return (radian * 180.0 / PI); }

//-----------------//}



// Angle aob in rad
LD Angle(point a, point o, point b) {
    point oa = vec(o, a); point ob = vec(o, b);
    return acos(dot(oa, ob) / sqrt(lengthSqr(oa) * lengthSqr(ob)));
}




// Lines ------------------------------------------------------------------------------------------------------//

struct line { LD a, b, c;
    line(point p1, point p2) {
        if (fabs(p1.X - p2.X) < EPS) a = 1.0, b = 0.0, c = -p1.X;
        else {
            a = -(LD)(p1.Y - p2.Y) / (p1.X - p2.X);
            b = 1.0; c = -(LD)(a * p1.X) - p1.Y;
        }
    }
    line(point p, LD m){
        a = -m; b = 1;
        c = -((a * p.X) + (b * p.Y));
    }
};

bool areParallel(line l1, line l2) {
    return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS);
}

bool areSame(line l1, line l2) {
    return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS) && (fabs(l1.c - l2.c) < EPS);
}

//-------------------------------------------------------------------------------------------------------------//





// Is point P on line A B?  ------------------------------------------------------------//{

// If 3 points on the same infinite line, they are called Collinear points.
// Fact: Cross product between 2 vectors is ZERO if angle between them is ZERO or 180.
// So if we create vector A->P and vector A->B, and we found that Cross between them
// equal zero, then they are collinear. Then the drawing is A B P, A P B or P A B.
bool isCollinear(const point& a, const point& b, const point& p){
    return fabs(cross(vec(a,b),vec(a,p))) < EPS;
}
// We have to check first if A B is a line, if not return -1.
int pointOnLine(const point& a, const point& b, const point& p) {
    if (same(a, b)) return -1; // line is a point
    return isCollinear(a, b, p);
}

// We can use the same strategy to know if point P above line A B or not.

//---------------------------------------------------------------------------------------//}






// Is point P on ray A B?  ------------------------------------------------------------//{

// If we create vector A->P and vector A->B, P is on ray A B if
// The angle between them equal ZERO, so we have to check if they are collinear first,
// because if this is true then the angle between them equal ZERO or 180, then if so
// we have to make sure that dot product between them is +ve, because the dot product
// between two vectors is > 0 IF angle is acute (FACT).

/* Facts: dot > 0 -> angle is acute.
          dot = 0 -> angle is right.
          dot < 0 -> angle is obtuse.
*/

bool pointOnRay(const point& a, const point& b, const point& p){
    return dot(vec(a,p), vec(a,b)) > -EPS && isCollinear(a, b, p);
}

//---------------------------------------------------------------------------------------//}





// Is point P on segment A B?  -------------------------------------------//{

// Point on segment if it is on 2 rays: A -> B and B -> A.

bool pointOnSegment(const point& a, const point& b, const point& p){
    return pointOnRay(a,b,p) && pointOnRay(b,a,p);
}

//------------------------------------------------------------------------//}




// ------------------------------------------------------------------//{

LD pointLineDist(const point& a, const point& b, const point& p){
  if (same(a, b)) return hypot(a.X - p.X, a.Y - p.Y);
  return fabs(cross(vec(a,b),vec(a,p)) / length(vec(a,b)));
}

LD pointSegmentDist(const point &a, const point &b, const point &p){
    if (dot(vec(a,b),vec(a,p)) < EPS) return length(vec(a,p));
    if (dot(vec(b,a),vec(b,p)) < EPS) return length(vec(b,p));
    return pointLineDist(a, b, p);
}

bool intersectLines(const point &a, const point &b,
               const point &c, const point &d, point &intersect){
    LD d1 = cross(a-b,d-c), d2 = cross(a-c,d-c); LD t1 = d2 / d1;
    if (fabs(d1) < EPS) return false; //parallel or identical or not line
    intersect = a + (b - a) * t1; return true;
}

// -------------------------------------------------------------------//}


bool intersectSegments(const point &a, const point &b,
               const point &c, const point &d, point &intersect){
    line l1(a, b); line l2(c, d);
    if (!intersectLines(a, b, c, d, intersect)){
            // The two segments on each other
        if (pointOnSegment(a, b, c) || pointOnSegment(a, b, d) ||
            pointOnSegment(c, d, a) || pointOnSegment(c, d, b)) return true;
        else return false; // parallel
    }
    else return pointOnSegment(a, b, intersect) && pointOnSegment(c, d, intersect);
}

bool pointInOrOnRectangle(point p, point p1, point p2, point p3, point p4){
    /*
        1   2

        4   3
    */
    return (p1.X <= p.X) & (p.X <= p2.X) & (p4.Y <= p.Y) & (p.Y <= p1.Y);
}


int main (){


    point p;
    cout << p << endl; // (0,0)

    point p1 = 15;
    cout << p1 << endl; // (15,0)



    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

    point a(1, 2); point b(3, 4);

    cout << a + b << endl;        // (4,6)
    cout << a - b << endl;        // (-2,-2)

    cout << b * (LD)2.0 << endl;  // (6,8)
    cout << b / (LD)2.0 << endl;  // (1.5,2)

    cout << a * b << endl;        // (-5,10)

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//



    //----------------------------------------------------------------------------------//

    point p2(1, 1);

    // -> r
    cout << "Modulus = " << abs(p2) << endl;                        // r = 1.41421
    // = r is the modulus and it is the distance from
    // the origin to the point, abs(p2) return the r of p2.

    // -> Theta
    cout << "Argument in radian = " << arg(p2) << endl;             // Theta = 0.785398
    cout << "Argument in degree = " << toDegree(arg(p2)) << endl;   // Theta = 45
    // = Theta is called the argument and it is the angle in radian
    // formed between Line [(0, 0) <-> (p2.x, p2.y)] and the x-axis.

    // -> The Square of r, the square norm of the vector or
    //the square magnitude of the vector
    cout << "Norm = " << norm(p2) << endl; // (1*1 + 1*1) = 2


    // -> (r, Theta) to (x, y)
    point p3 = polar(1.41421, 0.785398);
    cout << p3 << endl; // (0.999998,0.999997) ~> (1,1)

    //----------------------------------------------------------------------------------//




    //Sorting points using complex class and pcmp function------------------//

    vector < point > v;

    v.pp(point(-1,-1)); v.pp(point(13,17)); v.pp(point(8,-5));
    v.pp(point(-1,-2)); v.pp(point(0,0)); v.pp(point(-77,3));
    v.pp(point(14,0)); v.pp(point(0,44)); v.pp(point(8,7));

    sort (v.begin(), v.end(), pcmp);

    for (int i = 0 ; i < v.size(); i ++)
        cout << v[i] << endl;

    /*
        (-77,3)
        (-1,-2)
        (-1,-1)
        (0,0)
        (0,44)
        (8,-5)
        (8,7)
        (13,17)
        (14,0)
    */

    //-----------------------------------------------------------------------//


    cout << toDegree(Angle(point(1, 0), point(0, 0), point(0, 1))) << endl;


    return 0;
}
