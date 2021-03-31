//[Tools]

#define PI ((LD)(acos(-1.0)))
#define vec(a,b) ((b) - (a))
#define polar(r,t) ((r) * exp(point(0, (t))))
#define angle(v) (atan2((v).Y, (v).X))
#define length(v) ((LD)hypot((v).Y, (v).X))
#define lengthSqr(v) (dot(v, v))
#define dot(a,b) ((conj(a) * (b)).real())
#define cross(a,b) ((conj(a) * (b)).imag())
#define rotate(v,t) (polar(v, t))
#define rotateabout(v,t,a) (rotate(vec(a, v), t) + (a))
#define reflect(p,m) ((conj((p) / (m))) * (m))
#define normalize(p) ((p) / length(p))
#define same(a,b) (lengthSqr(vec(a, b)) < EPS)
#define mid(a,b) (((a) + (b)) / point(2, 0))
#define perp(a) (point(-(a).Y, (a).X))



// Reflect point p1 around p0p1
point reflect2(point p, point p0, point p1){
    point z = p - p0, w = p1 - p0;
    return conj(z / w) * w + p0;
}

ll  sqdist (ll  p1x , ll  p1y , ll  p2x , ll  p2y)
{ return(p2x-p1x)*(p2x-p1x)+(p2y-p1y)*(p2y-p1y); }



//[Transformations]

const long double PI = acos(-1.0);

LD toDegreeFromMinutes(LD minutes){
    return (minutes / 60.0);
}

LD toRadians(LD degree){
    return (degree * PI / 180.0);
}

LD toDegree(LD radian){
    if (radian < 0) radian += 2 * PI;
    return (radian * 180.0 / PI);
}

//[solving triangles]

LD fixAngle(LD A){
    return A > 1 ? 1 : (A < -1 ? -1 : A);
}

LD getSide_a_bAB(LD b, LD A, LD B){
    return (sin(A) * b) / sin(B);
}

LD getAngle_A_abB(LD a, LD b, LD B){
    return asin(fixAngle( (a * sin(B)) / b ));
}

LD getAngle_A_abc(LD a, LD b, LD c){
    return acos(fixAngle( (b*b + c*c - a*a) / (2*b*c) ));
}

//[Triangle area]

LD triangleAreaBH(LD b, LD h) {
    return b * h / 2.0;
}

LD triangleArea2sidesAngle(LD a, LD b, LD included){
    return fabs(a * b * sin(included) / 2.0);
}

LD triangleArea3sides(LD a, LD b, LD c){
    LD s((a + b + c) / 2);
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

LD triangleArea3medians(LD m1, LD m2, LD m3){ // -1 equals impossible
    if (m1 <= 0 || m2 <= 0 || m3 <= 0) return -1;
    LD s = 0.5 * (m1 + m2 + m3);
    LD medians_area = (s * (s - m1) * (s - m2) * (s - m3));
    LD area = 4.0 / 3.0 * sqrt(medians_area);
    if (medians_area <= 0.0 || area <= 0.0) return -1;
    return area;
}

//TO TEST
LD triangleArea2anglesSide(LD t1, LD t2, LD s){
    return fabs(s * s * sin(t1) * sin(t2) / (2 * sin(t1 + t2)));
}

LD triangleArea3points(const point &a, const point &b,
                                       const point &c){
    return fabs(cross(a,b) + cross(b,c) + cross(c,a)) / 2.0;
}


//[line, ray, segment and point]

bool isCollinear(const point& a, const point& b, const point& p){
    return fabs(cross(vec(a,b),vec(a,p))) < EPS;
}

int pointOnLine(const point& a, const point& b, const point& p) {
    if (same(a, b)) return -1; // line is a point
    return isCollinear(a, b, p);
}

bool pointOnRay(const point& a, const point& b, const point& p){
    return dot(vec(a,p), vec(a,b)) > -EPS && isCollinear(a, b, p);
}

bool pointOnSegment(const point& a, const point& b, const point& p){
    return isCollinear(a,b,p) && pointOnRay(a,b,p) && pointOnRay(b,a,p);
}

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
    if (fabs(d1) < EPS) return false;//parallel or identical or not line
    intersect = a + (b - a) * t1; return true;
}

int circlePoint(const point &cen, const LD &r, const point &p) {
    LD lensqr = lengthSqr(vec(cen,p));
    if (fabs(lensqr - r * r) < EPS) return 0; //BOUNDRY
    if (lensqr < r * r) return 1; return -1; //IN, OUT
}

void circle2points(const point &p1, const point &p2,
                                          point &cen, LD &r){
    cen = mid(p1, p2); r = length(vec(p1, p2)) / 2;
}

bool circle3points(const point &p1, const point &p2, const point &p3,
                                                point& cen, LD& r){
    point m1 = mid(p1, p2), m2 = mid(p2, p3);
    point perp1 = perp(vec(p1, p2)), perp2 = perp(vec(p2, p3));
    bool res = intersectLines(m1, m1 + perp1, m2, m2 + perp2, cen);
    r = length(vec(cen,p1)); return res;
}

int circleLineIntersection(const point &p0, const point &p1,
                    const point &cen, LD rad, point &r1, point &r2){
    if (same(p0,p1)){
        if (fabs(lengthSqr(vec(p0,cen))-(rad * rad)) < EPS){
                r1 = r2 = p0; return 1;
        } return 0;
    }
    LD a, b, c, t1, t2; a = dot(p1 - p0, p1 - p0);
    b = 2 * dot( p1 - p0, p0 - cen);
    c = dot(p0 - cen, p0 - cen) - rad * rad;
    LD det = b * b - 4 * a * c; int res;
    if (fabs(det) < EPS) det = 0, res = 1;
    else if (det < 0) res = 0; else res = 2;
    det = sqrt(det); t1 = (-b + det) / (2 * a);
    t2 = (-b - det) / (2 * a); r1 = p0 + t1 * (p1 - p0);
    r2 = p0 + t2 * (p1 - p0); return res;
}

LD cosRule(LD a, LD b, LD c){
    LD res = (b * b + c * c - a * a) / (2 * b * c);
    if (res > 1) res = 1; if (res < -1) res = -1; return acos(res);
}

int circleCircleIntersection(const point &c1, const LD &r1,
    const point &c2, const LD &r2, point &res1, point &res2){
    if (same(c1,c2) && fabs(r1 - r2) < EPS){
        res1 = res2 = c1;
        return fabs(r1) < EPS ? 1 : 1e9;
    }
    LD len = length(vec(c1,c2));
    if (fabs(len - (r1 + r2)) < EPS ||
        fabs(fabs(r1 - r2) - len) < EPS){
        point d, c; LD r;
        if (r1 > r2) d = vec(c1,c2), c = c1, r = r1;
        else d = vec(c2,c1), c = c2, r = r2;
        res1 = res2 = normalize(d) * r + c; return 1;
    }
    if (len > r1 + r2 || len < fabs(r1 - r2)) return 0;
    LD a = cosRule(r2, r1, len); point c1c2 = normalize(vec(c1,c2)) * r1;
    res1 = rotate(c1c2,  a) + c1; res2 = rotate(c1c2, -a) + c1; return 2;
}