## Clock signal
##Bank = 35, Pin name = IO_L12P_T1_MRCC_35,					Sch name = CLK100MHZ
set_property PACKAGE_PIN E3 [get_ports clk]						
	set_property IOSTANDARD LVCMOS33 [get_ports clk]
	create_clock -add -name sys_clk_pin -period 10.00 -waveform {0 5} [get_ports clk]
# Switches
#Bank = 34, Pin name = IO_L21P_T3_DQS_34,					Sch name = SW0
set_property PACKAGE_PIN U9 [get_ports {sig_nsyn}]					
    set_property IOSTANDARD LVCMOS33 [get_ports {sig_nsyn}]

# LEDs
#Bank = 34, Pin name = IO_L21N_T3_DQS_34,					Sch name = LED1
set_property PACKAGE_PIN V9 [get_ports {clk_n}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {clk_n}]
#Bank = 34, Pin name = IO_L24P_T3_34,						Sch name = LED2
set_property PACKAGE_PIN R8 [get_ports {q1}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {q1}]
#Bank = 34, Pin name = IO_L23N_T3_34,						Sch name = LED3
set_property PACKAGE_PIN T6 [get_ports {q2}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {q2}]
##Bank = 34, Pin name = IO_L12P_T1_MRCC_34,					Sch name = LED4
set_property PACKAGE_PIN T5 [get_ports {sig_syn}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {sig_syn}]
get_property C_USER_SCAN_CHAIN [get_debug_cores dbg_hub]