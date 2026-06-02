#ifndef KIJO_WAS_HERE
# define KIJO_WAS_HERE

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

class Shape {
protected:
    std::string name;

public:
    Shape(const std::string& n) : name(n) {}

    virtual ~Shape() {}

    virtual double area() const = 0;

    virtual std::string describe() const {
        return name + " with area " + std::to_string(area());
    }

    std::string getName() const { return name; }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : Shape("Circle"), radius(r) { }

    double area() const override { return 3.14159265358979323846 * radius * radius; }

};

class Rectangle : public Shape {
protected:
    double width;
    double height;

public:
    Rectangle(double w, double h) : Shape("Rectangle"), width(w), height(h) { }

    double area() const override { return width * height; }

};

class Square : public Rectangle {
public:
    Square(double s) : Rectangle(s, s) {
        name = "Square";
    }
};

double totalArea(const std::vector<Shape*>& shapes) {
    if (shapes.empty())
        return 0.0;
    double res = 0.0;
    
    for (size_t i = 0; shapes[i]; i++)
        res += shapes[i]->area();
    return res;
}

std::string largestShapeName(const std::vector<Shape*>& shapes) {
    if (shapes.empty())
        return "";
        
    const Shape* biggest = shapes[0];
    
    for (const Shape* s : shapes){
        if (s->area() > biggest->area())
            biggest = s;
    }
    return biggest->getName();
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

#endif
