# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\zakis\Documents\EOS_Assignment_Two\JSON_Parser\EOS_Assignment_Two\Archive\JSON_Parser.cyprj.Archive02\JSON_Parser.cydsn\Archive\JSON_Parser.cyprj.Archive01\JSON_Parser.cydsn\JSON_Parser.cyprj
# Date: Sun, 11 Feb 2024 21:55:36 GMT
#set_units -time ns
create_clock -name {CyILO} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_generated_clock -name {TFT_SPI_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {UART_LOG_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 27 53} -nominal_period 1083.3333333333333 [list [get_pins {ClockBlock/dclk_glb_1}]]
create_generated_clock -name {CLK_LED} -source [get_pins {ClockBlock/clk_sync}] -edges {1 4801 9601} [list [get_pins {ClockBlock/dclk_glb_2}]]
create_generated_clock -name {PWM_Clock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 4801 9601} [list [get_pins {ClockBlock/dclk_glb_3}]]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for C:\Users\zakis\Documents\EOS_Assignment_Two\JSON_Parser\EOS_Assignment_Two\Archive\JSON_Parser.cyprj.Archive02\JSON_Parser.cydsn\Archive\JSON_Parser.cyprj.Archive01\JSON_Parser.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\zakis\Documents\EOS_Assignment_Two\JSON_Parser\EOS_Assignment_Two\Archive\JSON_Parser.cyprj.Archive02\JSON_Parser.cydsn\Archive\JSON_Parser.cyprj.Archive01\JSON_Parser.cydsn\JSON_Parser.cyprj
# Date: Sun, 11 Feb 2024 21:55:30 GMT