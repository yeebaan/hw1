#ifndef TESTBENCH_H_
#define TESTBENCH_H_

#include <string>
using namespace std;

#include <systemc>
using namespace sc_core;

#include "filter_def.h"

const int WHITE = 255;
const int BLACK = 0;
const int THRESHOLD = 90;

class Testbench : public sc_module {
public:
  sc_in_clk i_clk;
  sc_out<bool> o_rst;
  std::array<sc_fifo_out<unsigned char>, MASK_Y> o_r;
  std::array<sc_fifo_out<unsigned char>, MASK_Y> o_g;
  std::array<sc_fifo_out<unsigned char>, MASK_Y> o_b;
  sc_fifo_in<int> i_result;

  SC_HAS_PROCESS(Testbench);

  Testbench(sc_module_name n);
  ~Testbench() = default;

  int read_bmp(string infile_name);
  int write_bmp(string outfile_name);

private:
  unsigned int input_rgb_raw_data_offset;
  const unsigned int output_rgb_raw_data_offset;
  int width;
  int height;
  unsigned char bits_per_pixel;
  unsigned short bytes_per_pixel;
  unsigned char *source_bitmap;
  unsigned char *target_bitmap;

  void do_sobel();
};
#endif
