# THIS FILE IS AUTOMATICALLY GENERATED
# Project: F:\Utilisateurs\demasson\Documents\EPM\PSoC Creator\EPM2.0\EPM_parfait\EYESAT_EPM\EYESAT_EPM.cydsn\EYESAT_EPM.cyprj
# Date: Wed, 15 Jul 2015 11:51:32 GMT
#set_units -time ns
create_clock -name {I2CS_SCBCLK(FFB)} -period 166.66666666666666 -waveform {0 83.3333333333333} [list [get_pins {ClockBlock/ff_div_2}]]
create_clock -name {CyHFCLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/hfclk}]]
create_generated_clock -name {I2CS_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 5 9} [list]
create_generated_clock -name {Clock} -source [get_pins {ClockBlock/hfclk}] -edges {1 241 481} [list [get_pins {ClockBlock/udb_div_0}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CySYSCLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/sysclk}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFCLK} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for F:\Utilisateurs\demasson\Documents\EPM\PSoC Creator\EPM2.0\EPM_parfait\EYESAT_EPM\EYESAT_EPM.cydsn\TopDesign\TopDesign.cysch
# Project: F:\Utilisateurs\demasson\Documents\EPM\PSoC Creator\EPM2.0\EPM_parfait\EYESAT_EPM\EYESAT_EPM.cydsn\EYESAT_EPM.cyprj
# Date: Wed, 15 Jul 2015 11:51:24 GMT
