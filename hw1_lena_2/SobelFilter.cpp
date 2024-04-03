#include <cmath>

#include "SobelFilter.h"
#include "filter_def.h"

SobelFilter::SobelFilter(sc_module_name n) : sc_module(n) {
  SC_THREAD(do_filter);
  sensitive << i_clk.pos();
  dont_initialize();
  reset_signal_is(i_rst, false);
}

// sobel mask
const int mask[MASK_X][MASK_Y] = 
  { 
    {1, 4, 7, 4, 1},
    {4, 16, 26, 16, 4},
    {7, 26, 41, 26, 7},
    {4, 16, 26, 16, 4},
    {1, 4, 7, 4, 1}
  };

void SobelFilter::do_filter() {

  unsigned int buffer[5][5] = {0};

  while (true) {

    unsigned int accumulator = 0;

    for (int i = 0; i < MASK_X; ++i) {
    for (int j = 0; j < MASK_Y; ++j) {
      accumulator += buffer[i][j] * mask[i][j];
    }
    }

    o_result.write(accumulator / 273);

    for (int i = 0; i < MASK_X - 1; ++i) {
    for (int j = 0; j < MASK_Y    ; ++j) {
      buffer[i][j] = buffer[i + 1][j];
    }
    }

    for (int i = 0; i < MASK_Y; ++i) {
      buffer[4][i] = (i_r[i].read() + i_g[i].read() + i_b[i].read()) / 3;
    }

    wait(10);
  }
}
