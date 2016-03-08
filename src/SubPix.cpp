// find_peaks.cpp
// Stand-alone functions for calculating the sub-pixel location of a gaussian
// curve passing through three equally spaced points. 
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created:

#include "SubPix.hpp"

namespace PivEng {

// gauss
// Calculate sub-pixel displacement components for each of the peaks in peaks
// for the correlation function ccf.
void gauss(const Mat2<double> &ccf, const Peak::PeaksVec &peaks,
           Disp::DispVec &displacements) {
  // std::cout << "In Gauss, eww!" << std::endl;
  uint_fast16_t i, j;
  double dx, dy;

  // Offset value make central row and column the zero displacement
  uint_fast16_t cols = ccf.cols(), offsetX = ccf.offsetX(),
                offsetY = ccf.offsetY();

  auto e0 = ccf.begin(), e = e0;

  // Calculate displacements for each peak
  auto p = peaks.begin();
  auto d = displacements.begin();

  while (p != peaks.end() && p->valid) {
    i = p->i;
    j = p->j;

    // Pointer to correlation peak value
    e = e0 + j * cols + i;
    // std::cout << e << "\t" << *e << std::endl;

    // Calculate x and y subpixel displacements
    dx = i + gauss3((e - 1), e, (e + 1)) - offsetX;
    dy = j + gauss3((e - cols), e, (e + cols)) - offsetY;

    // A number is only not equal to itself iff it is a NaN. If the peak is
    // invalid,
    // assume subsequent peaks are also invalid. Invalidity is caused by taking
    // the
    // logarithm of a negative correlation function element. Is it logical to
    // think
    // if a peak is invalid then all subsequent peaks will be invalid?
    if (std::isnan(dx) || std::isnan(dy))
      break;

    d->set_displacement(dx, dy, true);
    p++, d++;
  }
}

// gauss3
// Calculate the sub-pixel peak location of the gausian curve passing through
// points a, b and c. If the denominator is undefined or equal to zero, return
// a NAN.
double gauss3(const double *a, const double *b, const double *c) {

	auto const numer = log(*a) - log(*c);
	auto const denom = 2 * log(*a) - 4 * log(*b) + 2 * log(*c);

	if (!denom) return NAN;

  return numer / denom;
}
}
