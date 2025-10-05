#include <iostream>
#include <stdint.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

struct Point {
    int32_t x, y;
};

// Sweep-Line
struct Event {
    double coordinate;
    int16_t type;  // +1 or -1

    Event(double coord, int16_t tp) : coordinate(coord), type(tp) {
    }

    bool operator<(const Event& other) const {
        if (coordinate != other.coordinate) {
            return coordinate < other.coordinate;
        }
        return type > other.type;
    }
};

bool CheckRadius(std::vector<Point>& points, double radius, uint16_t covered_points_num) {
    size_t size_points = points.size();

    std::vector<Event> events;
    events.reserve(2 * size_points);

    for (const auto& point : points) {
        if (std::abs(point.y) <= radius) {
            double dx = std::sqrt(radius * radius - point.y * point.y);
            events.emplace_back(point.x - dx, 1);
            events.emplace_back(point.x + dx, -1);
        }
    }

    std::sort(events.begin(), events.end());

    int32_t current_overlap = 0;
    int32_t max_overlap = 0;

    for (const auto& event : events) {
        current_overlap += event.type;
        max_overlap = std::max(max_overlap, current_overlap);
    }

    return max_overlap >= covered_points_num;
}

int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);

    uint16_t points_count = 0;
    uint16_t covered_points_num = 0;

    std::cin >> points_count >> covered_points_num;

    std::vector<Point> points(points_count);

    for (size_t ind = 0; ind < points_count; ++ind) {
        std::cin >> points[ind].x >> points[ind].y;
    }

    double radius_low = 0.0;
    double radius_high = 1500.0;

    for (size_t iter = 0; iter < 50; ++iter) {
        double radius_mid = radius_low + (radius_high - radius_low) * 0.5;
        if (CheckRadius(points, radius_mid, covered_points_num)) {
            radius_high = radius_mid;
        } else {
            radius_low = radius_mid;
        }
    }

    std::cout << std::fixed << std::setprecision(6) << radius_high << '\n';

    return 0;
}
