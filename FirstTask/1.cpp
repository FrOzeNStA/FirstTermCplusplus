#include <iostream>
#include <cmath>

class Shape {
public:
  virtual ~Shape() = default;

  [[nodiscard]] virtual double area() const = 0;
  [[nodiscard]] virtual double perimeter() const = 0;
  virtual void print() const = 0;
};

class Rectangle : public Shape {
public:
  Rectangle(const double a, const double b) : a(a), b(b) {}

  [[nodiscard]] double area() const override {
    return a * b;
  }
  [[nodiscard]] double perimeter() const override {
    return 2 * (a + b);
  }
  void print() const override {
    std::cout << "Rectangle with sides: (" << a << ", " << b << "), perimeter: " <<
                 perimeter() << " and area: " << area() << '\n';
  }
private:
  double a;
  double b;
};

class Square final : public Rectangle {
public:
  explicit Square(const double a) : Rectangle(a, a), a(a) {}

  [[nodiscard]] double area() const override {
    return a * a;
  }
  [[nodiscard]] double perimeter() const override {
    return 4 * a;
  }
  void print() const override {
    std::cout << "Square with side: " << a << ", perimeter: " <<
                 perimeter() << " and area: " << area() << '\n';
  }
private:
  double a;
};

class Circle final : public Shape {
public:
  explicit Circle(const double radius) : radius(radius) {}

  [[nodiscard]] double area() const override {
    return M_PI * radius * radius;
  }
  [[nodiscard]] double perimeter() const override {
    return 2 * M_PI * radius;
  }
  void print() const override {
    std::cout << "Circle with radius: " << radius << ", perimeter: " <<
                 perimeter() << " and area: " << area() << '\n';
  }
private:
  double radius;
};

class Triangle final : public Shape {
public:
  explicit Triangle(const double a, const double b, const double c) : a(a), b(b), c(c) {}
  explicit Triangle(const double a, const double b) : Triangle(a, a, b) {}
  explicit Triangle(const double a) : Triangle(a, a, a) {}

  [[nodiscard]] double area() const override {
    const double p = perimeter() / 2;
    return sqrt(p * (p - a) * (p - b) * (p - b));
  }
  [[nodiscard]] double perimeter() const override {
    return a + b + c;
  }
  void print() const override {
    std::cout << "Triangle with sides: (" << a << ", " << b << ", " << c << "), perimeter: "
              << perimeter() << " and area: " << area() << '\n';
  }
private:
  double a;
  double b;
  double c;
};
