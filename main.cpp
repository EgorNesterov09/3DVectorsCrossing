#include <iostream>
#include <optional>
#include <cmath>

class Vector3D {
public:
    double X, Y, Z;

    Vector3D(double x = 0, double y = 0, double z = 0) : X(x), Y(y), Z(z) {}

    Vector3D operator-(const Vector3D& other) const {
        return Vector3D(X - other.X, Y - other.Y, Z - other.Z);
    }

    Vector3D operator+(const Vector3D& other) const {
        return Vector3D(X + other.X, Y + other.Y, Z + other.Z);
    }

    Vector3D operator*(double scalar) const {
        return Vector3D(X * scalar, Y * scalar, Z * scalar);
    }

    double dot(const Vector3D& other) const {
        return X * other.X + Y * other.Y + Z * other.Z;
    }

    Vector3D cross(const Vector3D& other) const {
        return Vector3D(
            Y * other.Z - Z * other.Y,
            Z * other.X - X * other.Z,
            X * other.Y - Y * other.X
        );
    }

    double length() const {
        return std::sqrt(X * X + Y * Y + Z * Z);
    }

    Vector3D normalize() const {
        double len = length();
        return Vector3D(X / len, Y / len, Z / len);
    }
};

class Segment3D {
public:
    Vector3D start;
    Vector3D end;

    Segment3D(const Vector3D& s, const Vector3D& e) : start(s), end(e) {}

    std::optional<Vector3D> Intersect(const Segment3D& other) const {
        Vector3D dir1 = end - start;
        Vector3D dir2 = other.end - other.start;

        Vector3D cross = dir1.cross(dir2);
        double crossLength = cross.length();
        
        // Если векторы параллельны
        if (crossLength < 1e-6) {
            return std::nullopt;
        }

        Vector3D diff = other.start - start;
        double t = (diff.cross(dir2)).dot(cross) / (crossLength * crossLength);
        double u = (diff.cross(dir1)).dot(cross) / (crossLength * crossLength);

        // Проверка, находится ли t и u в пределах отрезков
        if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
            Vector3D intersectionPoint = start + dir1 * t;
            return intersectionPoint;
        }

        return std::nullopt;
    }
};

int main() {
    Segment3D seg1(Vector3D(0, 0, 0), Vector3D(1, 1, 1));
    Segment3D seg2(Vector3D(0, 1, 0), Vector3D(1, 0, 1));

    auto intersection = seg1.Intersect(seg2);
    if (intersection) {
        std::cout << "Intersection point: (" << intersection->X << ", "
                  << intersection->Y << ", " << intersection->Z << ")\n";
    } else {
        std::cout << "No intersection.\n";
    }

    return 0;
}
