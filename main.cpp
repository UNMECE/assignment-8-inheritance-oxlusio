#include <iostream>
#include <cmath>

class Field {
protected:
	double x, y, z; // components of field

public:
	// default constructor
	Field() : x(0), y(0), z(0) {}

	// parameterized constructor
	Field(double xVal, double yVal, double zVal) : x(xVal), y(yVal), z(zVal) {}

	// function to print magnitude of components
	virtual void printMagnitude() const {
		std::cout << "Field components: (" << x << ", " << y << ", " << z << ")" << std::endl;
	}

	// virtual destructor
	virtual ~Field() {}
};

const double epsilon0 = 8.85e-12; // permittivity of free space

class ElectricField : public Field {
private:
	double calculatedField;

public:
	// default constructor
	ElectricField() : Field(), calculatedField(0) {}

	// parameterized constructor
	ElectricField(double xVal, double yVal, double zVal) : Field(xVal, yVal, zVal), calculatedField(0) {} 
	// function using Gauss' Law
	void calculateElectricField(double Q, double r) {
		calculatedField = Q / (4 * M_PI * pow(r, 2) * epsilon0);
	}

	// overload + operator
	ElectricField operator+(const ElectricField& other) const {
		return ElectricField(x + other.x, y + other.y, z + other.z);
	}

	// overload <<  operator
	friend std::ostream& operator<<(std::ostream& os, const ElectricField& e) {
		os << "Electric Field components: (" << e.x << ", " << e.y << ", " << e.z << ")";
		return os;
	}

	// print calculated electric field
	void printCalculatedField() const {
		std::cout << "Calculated Electric Field: " << calculatedField << "N/C" << std::endl;
	}
};

const double mu0 = 4 * M_PI * 1e-7; // permeability of free space

class MagneticField : public Field {
private:
	double calculatedField; 

public:
	// default constructor
	MagneticField() : Field(), calculatedField(0) {}

	// parameterized constructor
	MagneticField(double xVal, double yVal, double zVal) : Field(xVal, yVal, zVal), calculatedField(0) {}

	// calculate magnetic field using Ampere's Law
	void calculateMagneticField(double I, double r) {
		calculatedField = (mu0 * I) / (2 * M_PI * r);
	}

	// overload + operator
	MagneticField operator+(const MagneticField& other) const {
		return MagneticField(x + other.x, y + other.y, z + other.z);
	}

	// overlaod << operator
	friend std::ostream& operator<<(std::ostream& os, const MagneticField& m) {
		os << "Magnetic Field components: (" << m.x << ", " << m.y << ", " << m.z << ")";
		return os;
	}

	// print calculated magnetic field
	void printCalculatedField() const {
		std::cout << "Calculated Magnetic Field: " << calculatedField << " T" << std::endl;
	}
};

int main() {
	// create electricl and magnetic field objects
	ElectricField e1(0.0, 1e5, 1e3);
	MagneticField m1(0.0, 2.0, 1.0);

	//print magnitudes
	e1.printMagnitude();
	m1.printMagnitude();

	// calculte fields based on laws
	e1.calculateElectricField(1e-6, 1.0);
	m1.calculateMagneticField(10, 1.0);

	// print fields
	e1.printCalculatedField();
	m1.printCalculatedField();

	// demonstrate overloaded operators
	ElectricField e2(1.0, 2.0, 3.0);
	ElectricField e3 = e1 + e2;
	std::cout << e3 << std::endl;

	MagneticField m2(1.0, 2.0, 3.0);
	MagneticField m3 = m1 + m2;
	std::cout << m3 << std::endl;

	return 0;
}
