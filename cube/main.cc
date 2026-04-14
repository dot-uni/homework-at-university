#include <iostream>
#include "cube.h"


int main() {
    float time;
    float x, y, z;
    std::cout << "Координаты точки: "; 
    std::cin >> x >> y >> z;
    Point3D point{x, y, z};
    std::cout << "Координаты вектора скорости: "; 
    std::cin >> x >> y >> z;
    Vector3D speed{x, y, z};
    std::cout << "Время t: "; 
    std::cin >> time;

    Cube cube{point, speed, time, 1};
    Vector3D result = cube.run_simulation();
    std::cout << "(" << result->x << ", " << result->y << ", " << result->z << ")\n";
    return 0;
} 