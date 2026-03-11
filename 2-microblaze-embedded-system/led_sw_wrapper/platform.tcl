# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct /home/grads/n/nithingowtham25/Spring_2026/ECEN749/lab_2/led_sw_wrapper/platform.tcl
# 
# OR launch xsct and run below command.
# source /home/grads/n/nithingowtham25/Spring_2026/ECEN749/lab_2/led_sw_wrapper/platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {led_sw_wrapper}\
-hw {/home/grads/n/nithingowtham25/Spring_2026/ECEN749/lab_2/led_sw_wrapper.xsa}\
-out {/home/grads/n/nithingowtham25/Spring_2026/ECEN749/lab_2}

platform write
domain create -name {standalone_microblaze_0} -display-name {standalone_microblaze_0} -os {standalone} -proc {microblaze_0} -runtime {cpp} -arch {32-bit} -support-app {empty_application}
platform generate -domains 
platform active {led_sw_wrapper}
platform generate -quick
platform generate
