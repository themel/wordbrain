#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include <iostream>
#include <map>
#include <string>
#include <vector>

// 0 based coordinates, top left to bottom right.
//    x=012
//  y=0 FOO 
//  y=1 BAR
//  y=2 BAZ
struct Point {
    int x;
    int y;
};

// This point is not valid in any grid.
extern Point kInvalidPoint;

inline bool operator<(const Point& a, const Point& b) {
    return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

inline bool operator==(const Point& a, const Point& b) {
    return std::tie(a.x, a.y) == std::tie(b.x, b.y);
}

inline bool operator!=(const Point& a, const Point& b) {
    return !(a == b);
}

inline std::ostream& operator<<(std::ostream& str, const Point& p) {
    str << "(" << p.x << "," << p.y << ")";
    return str;
}

class Grid {
    public:
        Grid(std::string chars);
        Grid(const Grid& other) = default;
        const char Get(Point p) const;
        std::map<Point, char> Neighbors(Point p) const;
        std::map<Point, char> All() const;
        void DropMarked();
        std::string ToString() const;
        void Mark(Point p);
    private:
    void ResetMask();
    bool Marked(Point p) const;
    Point FromIndex(int idx) const;
    int ToIndex(const Point& p) const;
    void Drop(int idx);
        
    int width_;

    std::string chars_;
    std::vector<bool> mask_;
};

#endif  // defined GRID_H_INCLUDED
