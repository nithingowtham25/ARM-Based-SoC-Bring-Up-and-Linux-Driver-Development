# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: /home/grads/n/nithingowtham25/Spring_2026/ECEN749/lab_3/multiply_test_system/_ide/scripts/debugger_multiply_test-default.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source /home/grads/n/nithingowtham25/Spring_2026/ECEN749/lab_3/multiply_test_system/_ide/scripts/debugger_multiply_test-default.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent Zybo Z7 210351AB7220A" && level==0 && jtag_device_ctx=="jsn-Zybo Z7-210351AB7220A-13722093-0"}
fpga -file /home/grads/n/nithingowtham25/Spring_2026/ECEN749/lab_3/multiply_test/_ide/bitstream/multiply_wrapper.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw /home/grads/n/nithingowtham25/Spring_2026/ECEN749/lab_3/multiply_wrapper/export/multiply_wrapper/hw/multiply_wrapper.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source /home/grads/n/nithingowtham25/Spring_2026/ECEN749/lab_3/multiply_test/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow /home/grads/n/nithingowtham25/Spring_2026/ECEN749/lab_3/multiply_test/Debug/multiply_test.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A9*#0"}
con
