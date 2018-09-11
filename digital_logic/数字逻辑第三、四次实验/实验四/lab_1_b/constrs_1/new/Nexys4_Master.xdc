# Clock signal
#Bank = 35, Pin name = IO_L12P_T1_MRCC_35,					Sch name = CLK100MHZ
set_property PACKAGE_PIN E3 [get_ports clk]							
	set_property IOSTANDARD LVCMOS33 [get_ports clk]
	create_clock -add -name sys_clk_pin -period 10.00 -waveform {0 5} [get_ports clk]

# Switches
#Bank = 34, Pin name = IO_L21P_T3_DQS_34,					Sch name = SW0
set_property PACKAGE_PIN U9 [get_ports {M}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {M}]
#Bank = 34, Pin name = IO_25_34,							Sch name = SW1
set_property PACKAGE_PIN U8 [get_ports {CLR}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {CLR}]
#Bank = 34, Pin name = IO_L17P_T2_34,						Sch name = LED11
set_property PACKAGE_PIN R1 [get_ports {QA}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {QA}]
#Bank = 34, Pin name = IO_L13N_T2_MRCC_34,					Sch name = LED12
set_property PACKAGE_PIN P5 [get_ports {QB}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {QB}]
#Bank = 34, Pin name = IO_L7P_T1_34,						Sch name = LED13
set_property PACKAGE_PIN U1 [get_ports {QC}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {QC}]
#Bank = 34, Pin name = IO_L15N_T2_DQS_34,					Sch name = LED14
set_property PACKAGE_PIN R2 [get_ports {QD}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {QD}]
#Bank = 34, Pin name = IO_L15P_T2_DQS_34,					Sch name = LED15
set_property PACKAGE_PIN P2 [get_ports {Qcc}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Qcc}]