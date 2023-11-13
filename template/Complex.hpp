#include <iostream>

template<class T>
class Complex {
    private:
        T real;
        T imag;
    public:
        Complex(): real(0), imag(0) {}
        Complex(T r, T i): real(r), imag(i) {}
        Complex modify(T r, T i) const {
            return Complex(r, i);
        }
        T getReal() const {
            return real;
        }
        T getImag() const {
            return imag;
        }
        friend std::ostream& operator<<(std::ostream& os, const Complex<T>& a) {
            os << a.real << " " << a.imag;
            return os;
        }
        template<class U>
        Complex operator+(const Complex<U>& b) const {
            return Complex(real + b.getReal(), imag + b.getImag());
        }
        template<class U>
        Complex operator-(const Complex<U>& b) const {
            return Complex(real - b.getReal(), imag - b.getImag());
        }
        template<class U>
        Complex operator*(const Complex<U>& b) const {
            return Complex(real * b.getReal() - imag * b.getImag(), real * b.getImag() + imag * b.getReal());
        }
};