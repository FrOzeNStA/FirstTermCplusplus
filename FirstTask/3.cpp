#include <iostream>
#include <numeric>

class Rational {
public:
  Rational(const int numerator, const int denominator) : numerator(numerator), denominator(denominator){}

  explicit operator double() const { return static_cast<double>(numerator) / denominator; }

  Rational& operator+=(const Rational& other) {
    denominator = denominator * other.denominator;
    numerator = numerator * other.denominator + other.numerator * denominator;
    normalize();
    return *this;
  }

  Rational& operator-=(const Rational& other) {
    denominator = denominator * other.denominator;
    numerator = numerator * other.denominator - other.numerator * denominator;
    normalize();
    return *this;
  }

  Rational& operator*=(const Rational& other) {
    denominator = denominator * other.denominator;
    numerator = numerator * other.denominator;
    normalize();
    return *this;
  }

  Rational& operator/=(const Rational& other) {
    if (other.denominator == 0) {
      std::cerr << "Division by zero" << '\n';
      return *this;
    }
    denominator = denominator * other.numerator;
    numerator = numerator * other.denominator;
    normalize();
    return *this;
  }

  Rational operator++(int) {
    const Rational temp = *this;
    numerator += denominator;
    normalize();
    return temp;
  }

  Rational operator--(int) {
    const Rational temp = *this;
    numerator -= denominator;
    normalize();
    return temp;
  }

  Rational& operator++(){
    numerator += denominator;
    normalize();
    return *this;
  }

  Rational& operator--() {
    numerator -= denominator;
    normalize();
    return *this;
  }

  Rational operator+(const Rational& other) const {
    Rational copy = Rational(numerator, denominator);
    copy += other;
    return copy;
  }

  Rational operator-(const Rational& other) const {
    Rational copy = Rational(numerator, denominator);
    copy -= other;
    return copy;
  }

  Rational operator*(const Rational& other) const {
    Rational copy = Rational(numerator, denominator);
    copy *= other;
    return copy;
  }

  Rational operator/(const Rational& other) const {
    Rational copy = Rational(numerator, denominator);
    copy /= other;
    return copy;
  }

  bool operator==(const Rational& other) const {
    return numerator == other.numerator && denominator == other.denominator;
  }

  bool operator!=(const Rational& other) const {
    return numerator != other.numerator || denominator != other.denominator;
  }

  bool operator<(const Rational& other) const {
    return numerator * other.denominator < denominator * other.numerator;
  }

  bool operator>(const Rational& other) const {
    return numerator * other.denominator > denominator * other.numerator;
  }

  bool operator<=(const Rational& other) const {
    return *this < other || *this == other;
  }

  bool operator>=(const Rational& other) const {
    return *this > other || *this == other;
  }
private:
  int numerator;
  int denominator;
  friend std::ostream& operator<<(std::ostream& stream, const Rational& number);
  friend std::istream& operator>>(std::istream& stream, Rational& number);

  void normalize() {
    const int gcd = std::gcd(std::abs(denominator), std::abs(numerator));
    numerator /= gcd;
    denominator /= gcd;
  }
};

std::ostream& operator<<(std::ostream& stream, const Rational& number) {
  stream << number.numerator << " / " << number.denominator;
  return stream;
}

std::istream& operator>>(std::istream& stream, Rational& number) {
  stream >> number.numerator >> number.denominator;
  return stream;
}
