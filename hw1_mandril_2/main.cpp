#include <iostream>
#include <string>
using namespace std;

// Wall Clock Time Measurement
#include <sys/time.h>

#include "SobelFilter.h"
#include "Testbench.h"
#include "filter_def.h"

// TIMEVAL STRUCT IS Defined ctime
// use start_time and end_time variables to capture
// start of simulation and end of simulation
struct timeval start_time, end_time;

// int main(int argc, char *argv[])
int sc_main(int argc, char **argv) {
  if ((argc < 3) || (argc > 4)) {
    cout << "No arguments for the executable : " << argv[0] << endl;
    cout << "Usage : >" << argv[0] << " in_image_file_name out_image_file_name"
         << endl;
    return 0;
  }

  //Create modules and signals
  Testbench tb("tb");
  SobelFilter sobel_filter("sobel_filter");
  sc_clock clk("clk", CLOCK_PERIOD, SC_NS);
  sc_signal<bool> rst("rst");

  //Create FIFO channels
  std::array<sc_fifo<unsigned char>, MASK_Y> r;
  std::array<sc_fifo<unsigned char>, MASK_Y> g;
  std::array<sc_fifo<unsigned char>, MASK_Y> b;
  sc_fifo<int> result;

  //Connect FIFO channels with modules
  tb.i_clk(clk);
  sobel_filter.i_clk(clk);

  tb.o_rst(rst);
  sobel_filter.i_rst(rst);

  for (int i = 0; i < MASK_Y; ++i) {
    tb.o_r[i](r[i]);
    tb.o_g[i](g[i]);
    tb.o_b[i](b[i]);
    sobel_filter.i_r[i](r[i]);
    sobel_filter.i_g[i](g[i]);
    sobel_filter.i_b[i](b[i]);
  }

  tb.i_result(result);
  sobel_filter.o_result(result);

  tb.read_bmp(argv[1]);
  sc_start();
  std::cout << "Simulated time == " << sc_core::sc_time_stamp() << std::endl;
  tb.write_bmp(argv[2]);

  return 0;
}
