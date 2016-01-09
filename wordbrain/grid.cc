#include "grid.h"

#include <cassert>
#include <cmath>

Point kInvalidPoint = {-1,-1};

Grid::Grid(std::string chars) : chars_(std::move(chars)) {
    width_ = sqrt(chars_.size());
    assert(width_*width_ == chars_.size());
    ResetMask();
};

Point Grid::FromIndex(int idx) const {
    Point res = {
        .x = idx % width_,
        .y = idx / width_
    };
    assert(res.y >= 0 && res.y < width_);
    assert(res.x >= 0 && res.x < width_);
    return res;
}

int Grid::ToIndex(const Point& p) const {
    assert(p.y >= 0 && p.y < width_);
    assert(p.x >= 0 && p.x < width_);
    return p.y * width_ + p.x;
}

void Grid::Mark(Point p) {
	mask_[ToIndex(p)] = true;
}

void Grid::ResetMask() {
    mask_.clear();
    mask_.resize(chars_.size(), false);
}

void Grid::DropMarked() {
    for(int i = 0; i < width_ * width_; ++i) {
        if(mask_[i]) {
           Drop(i); 
        }
    }
    ResetMask();
}

void Grid::Drop(int idx) {
    Point dst = FromIndex(idx);
    Point src = { .x = dst.x, .y = dst.y-1 };
    while(src.y >= 0) {
        chars_[ToIndex(dst)] = chars_[ToIndex(src)];
        --src.y;
        --dst.y;
    }
    chars_[ToIndex(dst)] = '_';
}

std::string Grid::ToString() const {
    std::string res;
    for(int y = 0; y < width_; ++y) {
        for(int x = 0; x < width_; ++x) {
           int idx = ToIndex({x,y});
           res += mask_[idx] ? "[" : " "; 
           res += chars_[idx];
           res += mask_[idx] ? "]" : " "; 
        }
        res += "\n";
    }
    return res;
}

std::map<Point, char> Grid::Neighbors(Point p) const {
	std::map<Point, char> res;
	for(int dx = -1; dx <= +1 ; ++dx) {
		for(int dy = -1; dy <= +1 ; ++dy) {
			if(dx == 0 && dy == 0) continue;
			Point n = {p.x + dx, p.y + dy};
			if(n.x < 0 || n.x >= width_) continue;
			if(n.y < 0 || n.y >= width_) continue;
			int idx = ToIndex(n);
			if(!mask_[idx] && chars_[idx] != '_') res[n] = chars_[idx];
		}
	}
	return res;
}

std::map<Point, char> Grid::All() const {
	std::map<Point, char> res;
	for(int x = 0; x < width_; ++x) {
		for(int y = 0; y < width_; ++y) {
			Point p = {x,y};
			int idx = ToIndex(p);
			if(!mask_[idx] && chars_[idx] != '_') res[p] = chars_[idx];
		}
	}
	return res;
}
