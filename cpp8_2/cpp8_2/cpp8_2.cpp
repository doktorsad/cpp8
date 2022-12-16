#include <iostream>
#include <vector>
#include <string>
#include <exception>

// функция what() не была наследована, ибо vs(windows) noexcept, а на  mac _NOEXCEPT

class ErrorObject : public std::exception {
protected:
    std::string name;
public:
    ErrorObject(std::string name) {
        this->name = name;
    }
    std::string error_message() {
        std::string str = name;
        str += " was not created. Reason: the sides are greater than 0\n";
        return str;
    };
};

class ErrrorTriangle : public std::exception {
protected:
    std::string name, correction;
    int side1, side2, side3, corner1, corner2, corner3;
public:
    ErrrorTriangle(const int& side1, const int& side2, const int& side3,
        const int& corner1, const int& corner2, const int& corner3,
        const std::string& name, const std::string& correcrion) {
        this->side1 = side1;
        this->side2 = side2;
        this->side3 = side3;
        this->corner1 = corner1;
        this->corner2 = corner2;
        this->corner3 = corner3;
        this->name = name;
        this->correction = correcrion;
    }
    std::string error_message() {
        std::string str = name;
        str += " (sides: ";
        str += std::to_string(side1);
        str += ", ";
        str += std::to_string(side2);
        str += ", ";
        str += std::to_string(side3);
        str += "; corners: ";
        str += std::to_string(corner1);
        str += ", ";
        str += std::to_string(corner2);
        str += ", ";
        str += std::to_string(corner3);
        str += ") ";
        str += correction;
        return str;
    }
};

class ErrorQuadrilateral : public std::exception {
protected:
    std::string name, correction;
    int side1, side2, side3, side4, corner1, corner2, corner3, corner4;
public:
    ErrorQuadrilateral(const int& side1, const int& side2, const int& side3,
        const int& side4, const int& corner1, const int& corner2, const int& corner3,
        const int& corner4, const std::string& name, const std::string& correcrion) {
        this->side1 = side1;
        this->side2 = side2;
        this->side3 = side3;
        this->side4 = side4;
        this->corner1 = corner1;
        this->corner2 = corner2;
        this->corner3 = corner3;
        this->corner4 = corner4;
        this->name = name;
        this->correction = correcrion;
    }
    std::string error_message() {
        std::string str = name;
        str += " (sides: ";
        str += std::to_string(side1);
        str += ", ";
        str += std::to_string(side2);
        str += ", ";
        str += std::to_string(side3);
        str += ", ";
        str += std::to_string(side4);
        str += "; corners: ";
        str += std::to_string(corner1);
        str += ", ";
        str += std::to_string(corner2);
        str += ", ";
        str += std::to_string(corner3);
        str += ", ";
        str += std::to_string(corner4);
        str += ") ";
        str += correction;
        return str;
    }

};

class Object {
private:
    std::vector <int> sides;
    std::vector <int> corners;
    std::string name;
public:
    Object() = default;
    Object(const std::string& name) {
        this->name = name;
        if (get_count_sides() != 0)
            throw ErrorObject(name);
    }
    int get_corner_one() const { return corners[0]; }
    int get_corner_two() const { return corners[1]; }
    int get_corner_three() const { return corners[2]; }
    int get_corner_four() const { return corners[3]; }
    int get_side_one() const { return sides[0]; }
    int get_side_two() const { return sides[1]; }
    int get_side_three() const { return sides[2]; }
    int get_side_four() const { return sides[3]; }
    std::string get_name() const { return name; }
    int get_count_sides() const { return sides.size(); }
    virtual void print() {
        std::cout << get_name() << " (sides :" << get_count_sides() <<
            ") created" << '\n';
    }
protected:
    void set_sides(int side) { sides.push_back(side); }
    void set_corners(int corner) { corners.push_back(corner); }
    void set_name(std::string name) { this->name = name; }
};

class TriangleDefault : public Object {
public:
    TriangleDefault() = default;
    TriangleDefault(const int& side1, const int& side2, const int& side3,
        const int& corner1, const int& corner2, const int& corner3, const std::string& name = "Triangle Default") {
        if (side1 == 0 || side2 == 0 || side3 == 0)
            throw ErrrorTriangle(side1, side2, side3, corner1, corner2, corner3, name, "The number of sides is not equal to 3");
        if (corner1 + corner2 + corner3 != 180)
            throw ErrrorTriangle(side1, side2, side3, corner1, corner2, corner3, name, "The sum of the angles is not equal to 180");
        set_sides(side1);
        set_sides(side2);
        set_sides(side3);
        set_corners(corner1);
        set_corners(corner2);
        set_corners(corner3);
        set_name(name);
    }
    void print() override {
        std::cout << get_name() << " (sides: " << get_side_one() << ", " <<
            get_side_two() << ", " << get_side_three() << "; corners: " <<
            get_corner_one() << ", " << get_corner_two() << ", " <<
            get_corner_three() << ") created\n";
    }
};

class TriangleRight : public TriangleDefault {
public:
    TriangleRight(const int& side1, const int& side2, const int& side3,
        const int& corner1, const int& corner2, const int& corner3, const std::string& name = "Triangle Right") {
        if (corner3 != 90)
            throw ErrrorTriangle(side1, side2, side3, corner1, corner2, corner3, name, "The angle 3 is not equal to 90");
        set_sides(side1);
        set_sides(side2);
        set_sides(side3);
        set_corners(corner1);
        set_corners(corner2);
        set_corners(corner3);
        set_name(name);
    }
};

class TriangleIsosceles : public TriangleDefault {
public:
    TriangleIsosceles(const int& side1, const int& side2, const int& side3,
        const int& corner1, const int& corner2, const int& corner3, const std::string& name = "Triangle Isosceles") {
        if (side1 != side3)
            throw ErrrorTriangle(side1, side2, side3, corner1, corner2, corner3, name, "Side A is not equal to side");
        if (corner1 != corner3)
            throw ErrrorTriangle(side1, side2, side3, corner1, corner2, corner3, name, "Angle A is not equal to angle");
        set_sides(side1);
        set_sides(side2);
        set_sides(side3);
        set_corners(corner1);
        set_corners(corner2);
        set_corners(corner3);
        set_name(name);
    }
};

class TriangleEquilateral : public TriangleDefault {
public:
    TriangleEquilateral(const int& side1, const int& side2, const int& side3,
        const int& corner1, const int& corner2, const int& corner3, const std::string& name = "Triangle Equilateral") {
        if (side1 != side2 || side2 != side3 ||
            side1 != side3)
            throw ErrrorTriangle(side1, side2, side3, corner1, corner2, corner3, name, "The sides are not equal");
        if (corner1 != corner2 || corner1 != corner3 ||
            corner2 != corner3)
            throw ErrrorTriangle(side1, side2, side3, corner1, corner2, corner3, name, "The angles are not equal");
        set_sides(side1);
        set_sides(side2);
        set_sides(side3);
        set_corners(corner1);
        set_corners(corner2);
        set_corners(corner3);
        set_name(name);
    }
};

class QuadrilateralDefault : public Object {
public:
    QuadrilateralDefault() = default;
    QuadrilateralDefault(const int& side1, const int& side2, const int& side3, const int &side4,
        const int& corner1, const int& corner2, const int& corner3, const int &corner4, const std::string& name = "Quadrilateral Default") {
        if (side1 == 0 || side2 == 0 || side3 == 0 || side4 == 0)
            throw ErrorQuadrilateral(side1, side2, side3, side4, corner1, corner2, corner3, corner4, name, "The number of sides is not equal to 4");
        if (corner1 + corner2 + corner3 + corner4 != 360)
            throw ErrorQuadrilateral(side1, side2, side3, side4, corner1, corner2, corner3, corner4, name, "The sum of the angles is not equal to 360");
        set_sides(side1);
        set_sides(side2);
        set_sides(side3);
        set_sides(side4);
        set_corners(corner1);
        set_corners(corner2);
        set_corners(corner3);
        set_corners(corner4);
        set_name(name);
    }
    void print() override {
        std::cout << get_name() << " (sides: " << get_side_one() << ", " <<
            get_side_two() << ", " << get_side_three() << ", " << get_side_four() <<
            "; corners: " << get_corner_one() << ", " << get_corner_two() << ", " <<
            get_corner_three() << ", " << get_corner_four();
    }
};

class Rectangle : public QuadrilateralDefault {
public:
    Rectangle(const int& side1, const int& side2, const int& side3, const int& side4,
        const int& corner1, const int& corner2, const int& corner3, const int& corner4, const std::string& name = "Rectangle") {
        if (side1 != side3 || side2 != side4)
            throw ErrorQuadrilateral(side1, side2, side3, side4, corner1, corner2, corner3, corner4, name, "The pairwise sides are not equal");
        if (corner1 != 90 || corner2 != 90 ||
            corner3 != 90 || corner4 != 90)
            throw ErrorQuadrilateral(side1, side2, side3, side4, corner1, corner2, corner3, corner4, name, "The angles are not equal to 90");
        set_sides(side1);
        set_sides(side2);
        set_sides(side3);
        set_sides(side4);
        set_corners(corner1);
        set_corners(corner2);
        set_corners(corner3);
        set_corners(corner4);
        set_name(name);
    }

};

class Square : public QuadrilateralDefault {
public:
    Square(const int& side1, const int& side2, const int& side3, const int& side4,
        const int& corner1, const int& corner2, const int& corner3, const int& corner4, const std::string& name = "Square") {
        if (side1 != side2 || side1 != side3 || side1 != side4 || side2 !=  side3 || side2 !=  side4 || side3 != side4)
            throw ErrorQuadrilateral(side1, side2, side3, side4, corner1, corner2, corner3, corner4, name, "The sides are not equal");
        if (corner1 != 90 || corner2 != 90 ||
            corner3 != 90 || corner4 != 90)
            throw ErrorQuadrilateral(side1, side2, side3, side4, corner1, corner2, corner3, corner4, name, "The angles are not equal to 90");
        set_sides(side1);
        set_sides(side2);
        set_sides(side3);
        set_sides(side4);
        set_corners(corner1);
        set_corners(corner2);
        set_corners(corner3);
        set_corners(corner4);
        set_name(name);
    }
};

class Parallelogram : public QuadrilateralDefault {
public:
    Parallelogram() = default;
    Parallelogram(const int& side1, const int& side2, const int& side3, const int& side4,
        const int& corner1, const int& corner2, const int& corner3, const int& corner4, const std::string& name = "Parallelogram") {
        if (side1 != side3 || side2 != side4)
            throw ErrorQuadrilateral(side1, side2, side3, side4, corner1, corner2, corner3, corner4, name, "The pairwise sides are not equal");
        if (corner1 != corner3 || corner2 != corner4)
            throw ErrorQuadrilateral(side1, side2, side3, side4, corner1, corner2, corner3, corner4, name, "The angles are not equal");
        set_sides(side1);
        set_sides(side2);
        set_sides(side3);
        set_sides(side4);
        set_corners(corner1);
        set_corners(corner2);
        set_corners(corner3);
        set_corners(corner4);
        set_name(name);
    }
};

class Rhomb :public Parallelogram {
public:
    Rhomb(const int& side1, const int& side2, const int& side3, const int& side4,
        const int& corner1, const int& corner2, const int& corner3, const int& corner4, const std::string& name = "Rhomb") {
        if (side1 != side2 || side1 != side3 || side1 != side4 || side2 != side3 || side2 != side4 || side3 != side4)
            throw ErrorQuadrilateral(side1, side2, side3, side4, corner1, corner2, corner3, corner4, name, "The sides are not equal");
        if (corner1 != corner3 || corner2 != corner4)
            throw ErrorQuadrilateral(side1, side2, side3, side4, corner1, corner2, corner3, corner4, name, "The angles are not equal");
        set_name(name);
        set_sides(side1);
        set_sides(side2);
        set_sides(side3);
        set_sides(side4);
        set_corners(corner1);
        set_corners(corner2);
        set_corners(corner3);
        set_corners(corner4);
    }
};




template <typename T>
void print(Object* o, T& x) {
    o = &x;
    o->print();
}

int main() {
    try {
        TriangleDefault td{ 1,2,3,60,60,60 };
        Object* o = &td;
        Object ob{ "Object" };
        print(o, ob);
        print(o, td);
        TriangleRight tr{ 1,2,3,60, 70, 50 };
    }
    catch (ErrorObject& ex) {
        std::cout << ex.error_message();
    }
    catch (ErrrorTriangle& ex) {
        std::cout << ex.error_message();
    }
    catch (ErrorQuadrilateral& ex) {
        std::cout << ex.error_message();
    }
    catch (...) {
        std::cout << "unknow error";
    }

    return 0;
}