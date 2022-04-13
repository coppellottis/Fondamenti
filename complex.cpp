#include <iostream>
#include <cmath>
using namespace std;

class complex {
  private:
    float Re, Im;

  public:
    complex(const float Re, const float Im = 0) {
      this->Re = Re;
      this->Im = Im;
    }

    complex(const complex& c) {
      this->Re = c.Re;
      this->Im = c.Im;
    }

    complex operator+(const complex& z) const {
      return complex(this->Re+z.Re, this->Im+z.Im);
    }

    complex operator-(const complex& z) const {
      return complex(this->Re-z.Re, this->Im-z.Im);
    }

    complex operator*(const complex& z) const {
      float Re = (this->Re)*(z.Re)-(this->Im)*(z.Im);
      float Im = (this->Re)*(z.Im)+(this->Im)*(z.Re);
      return complex(Re, Im);
    }

    complex operator/(const complex& z) const {
      return ((*this)*z.conjugate())*(1/(z.norm()*z.norm()));
    }

    complex conjugate() const {
      return complex(this->Re, -1*this->Im);
    }

    complex reverse() const {
      return complex(this->Re/(this->norm()*this->norm()), -1*this->Im/(this->norm()*this->norm()));
    }

    complex opposite() const {
      return complex(-1*this->Re, -1*this->Im);
    }

    double norm() const {
      return sqrt((this->Re*this->Re+this->Im*this->Im));
    }

    double angle(const complex& z) const {
      return acos(((this->Re)*(z.Re)+(this->Im)*(z.Im))/(this->norm()*z.norm()));
    }

    double angle() const {
      return this->angle(complex(1, 0));
    }

    double angle_deg(const complex& z) const {
      double angle = this->angle(z);
      return (angle*180)/3.14;
    }

    double angle_deg() const {
      double angle = this->angle();
      return (angle*180)/3.14;
    }

    float getRe() const { return this->Re; }
    float getIm() const { return this->Im; }

    ostream& print(ostream& output) const {
      output << this->Re;
      if(this->Im < 0) output << "-" << -1*this->Im << "i";
      else output << "+" << this->Im << "i";
      return output;
    }
};

complex operator*(const complex& z, const float& n) {
  complex z1 = complex(n, 0);
  return z*z1;
}

complex operator*(const float& n, const complex& z) {
  complex z1 = complex(n, 0);
  return z*z1;
}

ostream& operator<<(ostream& output, const complex& z) {
  return z.print(output);
}

int main() {
  cout << ((complex(2,1)*complex(1,-1))/(complex(1,1)*complex(3,-4))).norm() << endl;
  cout << complex(2, -1).norm() << endl;
  cout << (10*complex(2, -1)).reverse() << endl;
  cout << (10*complex(2, -1)).reverse().norm() << endl;
  cout << (10*complex(2, -1)).reverse().angle_deg() << endl;
  return 0;
}
