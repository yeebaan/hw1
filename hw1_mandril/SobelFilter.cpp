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
  while (true) {
    unsigned int accumulator = 0;

    for (int i = 0; i < MASK_X; ++i) {
    for (int j = 0; j < MASK_Y; ++j) {
      accumulator += mask[i][j] * (i_r[i][j].read() + i_g[i][j].read() + i_b[i][j].read()) / 3;
    }
    }

    o_result.write(accumulator / 273);

    wait(10);
  }
}
