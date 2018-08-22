#ifndef COLOR_MATRIX_H
#define COLOR_MATRIX_H

#include <algorithm>

struct ColorMatrix {
  float values[5][5];
  ColorMatrix() { }
  ColorMatrix(const float(&values)[25])
  {
    std::copy(std::begin(values), std::end(values), (float*)this->values);
  }
  float (&operator[](unsigned i))[5] { return values[i]; }
  const float(&operator[](unsigned i) const)[5] { return values[i]; }
  ColorMatrix& operator*=(const ColorMatrix&);
};

struct ColorVector {
  float values[5];
  ColorVector(const float(&values)[5])
  {
    std::copy(std::begin(values), std::end(values), (float*)this->values);
  }
  float& operator[](size_t i) { return values[i]; }
  const float& operator[](size_t i) const { return values[i]; }
};

extern const ColorMatrix Identity;

#endif // COLOR_MATRIX_H
