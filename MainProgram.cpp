// ============================================================
// MainProgram.cpp  —  STUDENT VERSION
// Lab: Inheritance and Polymorphism
// Standard: C++17  |  Single file only, no headers
// ------------------------------------------------------------
// Complete every TODO. Do NOT rename classes, methods, or
// functions: the autograder depends on these exact names.
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// ================================
// CLASS DEFINITIONS
// ================================

// --- Base class -------------------------------------------------
class Shape {
protected:
    std::string name;

public:
    Shape(const std::string& n) : name(n) {}

    // TODO 1: Make this destructor VIRTUAL.
    //         (Add the 'virtual' keyword in front.)
    //         A virtual destructor is required for safe deletion
    //         through a Shape* pointer.
    virtual ~Shape() {}

    // Pure virtual: Shape is abstract and cannot be instantiated.
    // Each derived class MUST override area(). (Leave this line.)
    virtual double area() const = 0;

    // describe() is virtual with a default body — leave as is.
    virtual std::string describe() const {
        return name + " with area " + std::to_string(area());
    }

    std::string getName() const { return name; }
};

// --- Derived class: Circle --------------------------------------
class Circle : public Shape {
private:
    double radius;

public:
Circle(double r) : Shape("Circle"), radius(r) { }

double area() const override { return 3.14 * radius * radius; }

};

// --- Derived class: Rectangle -----------------------------------
class Rectangle : public Shape {
protected:
    double width;
    double height;

public:
    Rectangle(double w, double h) : Shape("Rectangle"), width(w), height(h) { }

    double area() const override { return width * height; }

};

// --- Derived class: Square (inherits from Rectangle) ------------
class Square : public Rectangle {
public:
    Square(double s) : Rectangle(s, s) {
        name = "Square";
    }
};

// ================================
// FUNCTION IMPLEMENTATIONS
// ================================

// TODO 7: Sum the area() of every shape in the vector.
//         Must work polymorphically (through Shape*).
//         An empty vector returns 0.0.
double totalArea(const std::vector<Shape*>& shapes) {
    double res = 0;
    
    for (size_t i = 0; shapes[i]; i++)
        res += shapes[i]->area();
    return res;
}

// TODO 8: Return getName() of the shape with the LARGEST area.
//         If the vector is empty, return "".
std::string largestShapeName(const std::vector<Shape*>& shapes) {
    double largest = 0;
    std::string shape;
    
    for (size_t i = 0; shapes[i]; i++)
        if (shapes[i]->area() > largest) {
            largest = shapes[i]->area();
            shape = shapes[i]->getName();
        }
    return shape;
}

// ================================
// MAIN
// ================================
int main() {
    std::vector<Shape*> shapes;
    shapes.push_back(new Circle(2.0));
    shapes.push_back(new Rectangle(3.0, 4.0));
    shapes.push_back(new Square(5.0));

    for (const Shape* s : shapes) {
        std::cout << s->describe() << std::endl;
    }

    std::cout << "Total area: " << totalArea(shapes) << std::endl;
    std::cout << "Largest:    " << largestShapeName(shapes) << std::endl;

    for (Shape* s : shapes) delete s;
    return 0;
}
