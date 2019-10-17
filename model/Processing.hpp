#include "Image.hpp"
#include "Histogram.hpp"
#include "HistogramColor.hpp"

class Processing
{
public:
  static void perataanHistogram(Image &image);
  static void spesifikasiHistogram(Image &image, Histogram &spec);
  static void spesifikasiHistogram(Image &image, HistogramColor &spec);
  static void penapisMedian(Image &image);

  static int hitungMedian(int *arr, int size);
};
