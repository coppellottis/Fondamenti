#include <iostream>
#include <string>
using namespace std;

template <typename t>
class set {
  private:
    t* S;     // puntatore al primo campo del set
    int d;    // dimensione del set

  public:
    set() {
      this->S = NULL;
      this->d = 0;
    }

    set(const t arr[], const int d) {
      this->S = NULL;           // imposto S = NULL per evitare eccezioni di accesso in memoria
      this->d = 0;              // imposto d = 0, si auto-incrementa ad ogni chiamata di this->add()
      for(int i = 0; i < d; i++) {
        this->add(arr[i]);
      }
    }

    set(const int d) {
      this->S = new t[d];
      this->d = d;
    }

    set(const set<t>& T) {      // costruttore di copia (deep-copy)
      this->S = NULL;
      this->d = 0;
      for(int i = 0; i < T.d; i++) {
        this->add(T.S[i]);
      }
    }

    ~set() {                    // distruttore
      this->fire();
    }

    set<t>& operator=(const set<t>& T) {      // operatore di assegnamento
      if(this != &T) {
        this->fire();
        this->d = 0;
        for(int i = 0; i < T.d; i++) {
          this->add(T.S[i]);
        }
      }
      return *this;
    }

    set<t>& operator+(const set<t> T) const {       // somma due insiemi
      set<t>* E = new set<t>(this->d+T.d);
      for(int i = 0; i < this->d; i++) {
        E->S[i] = this->S[i];
      }
      for(int i = this->d; i < this->d+T.d; i++) {
        E->S[i] = T.S[i-this->d];
      }
      return *E;
    }

    bool operator<(const set<t>& T) const {
      if(this->d >= T.d) return false;
      for(int i = 0; i < this->d; i++) {
        if(!T.find(this->S[i])) return false;
      }
      return true;
    }

    bool find(const t a) const {
      for(int i = 0; i < this->d; i++) {
        if(this->S[i] == a) return true;
      }
      return false;
    }

    void add(const t a) {                     // aggiunge un elemento a this->S incrementando this->d
      t* T = new t[this->d+1];
      for(int i = 0; i < this->d; i++) {
        T[i] = this->S[i];
      }
      T[this->d] = a;
      this->fire();
      this->S = T;
      this->d++;
      return;
    }

    ostream& print(ostream& output) const {
      output << "[";
      for(int i = 0; i < this->d; i++) {
        output << this->S[i];
        if(i != this->d-1) output << ", ";
      }
      output << "] ";
      return output;
    }

    istream& read(istream& input) {
      for(int i = 0; i < this->d; i++) {
        input >> this->S[i];
      }
      return input;
    }

    private:
      void fire() {
        if(this->S != NULL) {
          delete [] this->S;
          this->S = NULL;
        }
        return;
      }
};

template <typename t>
istream& operator>>(istream& input, set<t>& T) {
  return T.read(input);
}

template <typename t>
ostream& operator<<(ostream& output, const set<t>& T) {
  return T.print(output);
}

int main() {
  int n = 0;
  cout << "Quanti elementi si desidera inserire nel set? ";
  cin >> n;
  set<string> Set(n);
  cout << "Inserisci ora il valore degli elementi: ";
  cin >> Set;
  string arr[3] = {"#","!","="};
  set<string> Set2 = Set+Set+set<string>(arr, 3);
  cout << "Il set e': " << Set2 << endl;
  string arr2[2] = {"&", "!"};
  cout << (set<string>(arr2, 2) < Set2) << endl;
  return 0;
}
