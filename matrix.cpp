// Calculates determinant of provided matrixes
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class matrix {
  private:
    int** M;
    int n, k;

  public:
    matrix() {
      this->M = NULL,
      this->n = 0;
    }

    matrix(const int n) {
      this->M = new int*[n];
      for(int i = 0; i < n; i++) {
        this->M[i] = new int[n];
      }
      this->n = n;
    }

    matrix(ifstream& input, const int n) {
      if(!input.is_open()) throw string("Errore: input stream non disponibile");
      else {
        this->M = new int*[n];
        for(int i = 0; i < n; i++) {
          this->M[i] = new int[n];
        }
        for(int i = 0; i < n; i++) {
          if(input.eof() && i < n-1) throw string("Errore: matrice incompleta");
          for(int j = 0; j < n; j++) {
            if(input.eof() && j < n-1) throw string("Errore: matrice incompleta");
            input >> this->M[i][j];
          }
        }
        this->n = n;
      }
    }

    ~matrix() {
      for(int i = 0; i < this->n; i++) {
        delete [] this->M[i];
      }
      delete [] this->M;
    }

    const matrix& operator=(const matrix& m) {
      if(this->M != NULL) {
        for(int i = 0; i < this->n; i++) {
          delete [] this->M[i];
        }
        delete [] this->M;
      }
      this->n = m.n;
      this->M = new int*[this->n];
      for(int i = 0; i < this->n; i++) {
        this->M[i] = new int[this->n];
      }
      for(int i = 0; i < this->n; i++) {
        for(int j = 0; i < this->n; j++) {
          this->M[i][j] = m.M[i][j];
        }
      }
      return *this;
    }

    matrix* submatrix(const int r, const int c) const {
      matrix* sm = new matrix(this->n-1);
      int a = 0;
      for(int i = 0; i < this->n; i++) {
        if(i == r) continue;
        for(int j = 0, b = 0; j < this->n; j++) {
            if(j == c) continue;
            sm->M[a][b++] = this->M[i][j];
        }
        a++;
      }
      return sm;
    }

    int det() const {
      return this->detr(this);
    }

    void print() const {
      for(int i = 0; i < this->n; i++) {
        for(int j = 0; j < this->n; j++) {
          cout << this->M[i][j] << " ";
        }
        cout << endl;
      }
      return;
    }

  private:
    int detr(const matrix* m) const {
      if(m->n == 2) {
        return (m->M[0][0])*(m->M[1][1])-(m->M[0][1])*(m->M[1][0]);
      } else {
        int d = 0;
        for(int i = 0; i < m->n; i++) {
          if(m->M[i][0] != 0) {
            int g = i%2 == 0 ? 1 : -1;
            matrix* temp = m->submatrix(i, 0);
            d += g*(m->M[i][0])*(m->detr(temp));
            delete temp;
          }
        }
        return d;
      }
    }
};
/*
ostream& operator<<(ostream& output, matrix& m) {
  for(int i = 0; i < m.n; i++) {
    for(int j = 0; j < m.n; j++) {
      output << m.M[i][j] << " ";
    }
  cout << endl;
  }
  return output;
}*/

int main() {
	ifstream finput("matrix.txt");
  try {
    matrix m(finput, 4);
    m.print();
    cout << "Il determinante della matrice e': " << m.det() << endl;
  } catch(...) {
    cout << "Errore!";
  }
  return 0;
}
