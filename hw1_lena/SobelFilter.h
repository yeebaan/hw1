#ifndef SOBEL_FILTER_H_
#define SOBEL_FILTER_H_
#include <systemc>
using namespace sc_core;

#include "filter_def.h"

class SobelFilter : public sc_module {
public:
  sc_in_clk i_clk;
  sc_in<bool> i_rst;
  std::array<std::array<sc_fifo_in<unsigned char>, MASK_Y>, MASK_X> i_r;
  std::array<std::array<sc_fifo_in<unsigned char>, MASK_Y>, MASK_X> i_g;
  std::array<std::array<sc_fifo_in<unsigned char>, MASK_Y>, MASK_X> i_b;
  sc_fifo_out<int> o_result;

  SC_HAS_PROCESS(SobelFilter);
  SobelFilter(sc_module_name n);
  ~SobelFilter() = default;

private:
  void do_filter();
  int val[MASK_N];
};
#endif
