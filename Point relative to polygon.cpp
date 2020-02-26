#include <iostream> 
#include<algorithm>
using namespace std;

// Pentru extrem
#define INF 10000 

struct Point
{
	double x;
	double y;
	bool operator == (const Point& curr) {
		if (x != curr.x)
			return false;
		return y == curr.y;
	}

	bool operator < (const Point& curr) {
		if (x != curr.x)
			return x < curr.x;
		return y < curr.y;
	}
};
 
bool onSegment(Point p, Point q, Point r)
{
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
		q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
		return true;
	return false;
}

bool collinear(Point A, Point B, Point C) {
	if (A.x * B.y + B.x * C.y + C.x * A.y - B.y * C.x - C.y * A.x - A.y * B.x == 0)
		return true;
	return false;
}

Point first(Point a, Point b) {
	if (a.x != b.x) {
		if (a.x <= b.x)
			return a;
		return b;
	}
	if (a.y <= b.y)
		return a;
	return b;
}

Point second(Point a, Point b) {
	if (a.x != b.x) {
		if (a.x >= b.x)
			return a;
		return b;
	}
	if (a.y >= b.y)
		return a;
	return b;
}
bool intersect(Point A1, Point A2, Point A3, Point A4) {
	// Ecuati dreptei determinata de cele 2 segmente
	double a1 = A1.y - A2.y;
	double a2 = A3.y - A4.y;
	double b1 = A2.x - A1.x;
	double b2 = A4.x - A3.x;
	double c1 = A2.x * A1.y - A1.x * A2.y;
	double c2 = A4.x * A3.y - A3.x * A4.y;

	double det = a1 * b2 - b1 * a2; //determinantul

	double x = 0, y = 0;

	//Cazul 1(det != 0)
	if (det != 0) {
		x = (c1 * b2 - c2 * b1) / det;
		y = (a1 * c2 - a2 * c1) / det;
		//Verificam daca (x,y) apartine lui [A1,A2]
		if ((x < A1.x && x < A2.x) || (x < A3.x && x < A4.x)) {
			//cout << "Multimea vida\n";
			return false;
		}
		//Verificam daca (x,y) apartine lui [A3,A4]
		if ((x > A1.x&& x > A2.x) || (x > A3.x&& x > A4.x)) {
			//cout << "Multimea vida\n";
			return false;
		}
		// Daca da, afisam solutia ( intervalul xy)
		//cout << "Se intersecteaza in: (" << x << "," << y << ")\n";
		return true;
	}

	//caz 2 (det == 0)

	//Rang == 2
	if (b1 * c2 - b2 * c1 != 0) {
		//cout << "Multimea vida\n";
		return false;
	}
	if (a1 * c2 - a2 * c1 != 0)
	{
		//cout << "Multimea vida\n";
		return false;
	}
	//Rang == 1 - collinear

	Point min1 = first(A1, A2);
	Point min2 = first(A3, A4);
	Point max1 = second(A1, A2);
	Point max2 = second(A3, A4);

	if (min1 == min2 && max1 == max2) {
		//cout << "Segmentele se suprapun\n";
		return true;
	}

	if (min2 == first(max1, max2)) {
		//cout << "Se intersecteaza in: (" << min2.x << "," << min2.y << ")\n";
		return true;
	}

	if (max2 == min1) {
		//cout << "Se intersecteaza in: (" << min1.x << "," << min1.y << ")\n";
		return true;
	}

	if (max2 < min1) {
		//cout << "Multimea vida\n";
		return false;
	}

	if (min1 == min2 && min2 == first(max1, max2)) {
		//cout << "Se intersecteaza in: (" << min1.x << "," << min1.y << ")\n";
		return true;
	}

	if (min2 < min1) {
		//cout << "Se intersecteaza intre: (" << min1.x << "," << min1.y << ") , (" << first(max1, max2).x << "," << first(max1, max2).y << ")\n";
		return true;
	}

	if (min2 < first(max1, max2)) {
		//cout << "Se intersecteaza intre: (" << min2.x << "," << min2.y << ") , (" << first(max1, max2).x << "," << first(max1, max2).y << ")\n";
		return true;
	}

	//cout << "Multimea vida\n";
	return false;
}

// Returns true if the point p lies inside the polygon[] with n vertices 
int isInside(Point polygon[], int n, Point p)
{
	// There must be at least 3 vertices in polygon[] 
	if (n < 3) return false;

	// Create a point for line segment from p to infinite 
	Point extreme = { INF, p.y };

	// Numar in cate puncte se intersecteaza, verificand cu fiecare latura
	int count = 0, i = 0;
	do
	{
		int next = (i + 1) % n;

		// Check if the line segment from 'p' to 'extreme' intersects 
		// with the line segment from 'polygon[i]' to 'polygon[next]' 
		if (intersect(polygon[i], polygon[next], p, extreme))
		{
			if (polygon[i].x != p.x && polygon[i].y != p.y) {
				count++;
				if (collinear(polygon[i], p, polygon[next]) == true)
					if (onSegment(polygon[i], p, polygon[next]) == true)
						//Cazul in care punctul se afla pe latura
						return 2;
					else
						return 0;

			}
			else
				//cazul in care punctul e colt
				return 3;
		}
		i = next;
	} while (i != 0);

	//Daca count e 1, punctul se afla in interior sau e colt
	//Daca count !=1, se afla in exterior
	if(count==1)
		return 1; 
	return 0;
}

int main()
{
	Point polygon1[] = { {0, 0}, {0, 10}, {10 , 10}, {10,0} };
	int n = sizeof(polygon1) / sizeof(polygon1[0]);
	Point p = { 0, 5};
	if (isInside(polygon1, n, p) == 1)
		cout << "Yes \n";
	else
		if (isInside(polygon1, n, p) == 0)
			cout << "No \n";
		else
			if (isInside(polygon1, n, p) == 2)
				cout << "It lies on segment\n";
			else
				cout << "Intersect corner\n";

	
	return 0;
}
//277, 266   467,267   469, 332    279,335