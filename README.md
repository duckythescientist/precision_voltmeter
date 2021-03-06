# Precision Voltmeter

Partly based off of the Scullcom millivolt meter: http://www.scullcom.uk/design-build-6%c2%bd-digit-millivolt-meter-part-1/



## Serial comms

```
Commands:
    h    - Print this help
    ?    - Print version and date
    r    - Toggle live readout over serial
    p    - Print calibration
    z    - Calibrate at 0V (inputs shorted)
    c... - Calibrate for a specific range and value

Calibration:
    c[n]:[f]  - Calibrates for range [n] with external applied voltage [f]
    Range:
        0: x1 LV
        1: x10
        2: x100
        3: x1000
    Example: to calibrate the x10 range (HV input) with a 4.123V reference,
        the command would be `c1:4.123`
```


# Improvement notes

I added an opto-isolated serial output and spent a weekend tearing down and building back up the circuit. I don't think it's going to get much better than it is (or already was). Without ESD/EMI and environmental noise, the noise in the readings is on the same order of magnitude that I'd expect from thermal noise of a 1Meg resistor. Assuming that my napkin math is correct. Also, the constant offset that I'm seeing is also on the order of what's to be expected with the input bias current of the LTC2057 and a 1Meg resistor. I guess it's just up to software corrections. Still getting around 19-20 usable bits from the ADC. I'm calling that a win.

Environmental noise is still a big issue. Stddev of the readings lowers by an order of magnitude if I sit perfectly still.


# Notes for Future Versions and Improvements

## Issues

The LTC2057 has a common-mode input range from 0.1V below V- to 1.5V _below_ V+. Meaning that with a -2.5V,+5V supply, I can only buffer signals up to 3.5V technically. I'm seeing some sort of latchup-type behavior at around 4.2V. I've bodged in a 6.8V supply rail to the op-amp.

## Bodges

The sampling of the ADC is rather noisy. Adding filter capacitors right at the input and the vref seem to help. Reduced the resistor between the buffer and the ADC to 2.2k. May want to go lower? I'm currently at 100R series from the buffer to the ADC and a 2.2nF cap to gnd.

Adding extra voltage regulator to drive the op-amp positive rail at around 6.8V to give enough common-mode headroom to buffer a full input swing to the ADC.


## Future

The x10 mode presents around a 1Meg input impedance to the op-amp this combined with the couple hundred pA of input bias and offset results in a couple hundred microvolts of DC offset. This has a minimal temperature coefficient up to about 75C but does have a common-mode voltage dependence. I'm not sure what to do to fix it.

A 1Meg input impedance may be the way to go.

For lower noise, it may be nice to try LT3094 and LT3042 for post switching converter regulation. The switching regulator. However, the voltage lines look pretty clean right now. Also, these regulators are pretty expensive and are DFN packages. UPDATE: replacing the switching regulator with batteries didn't measurably reduce the noise. The current design is good enough.

A metal enclosure and/or more shielding could maybe help with environmental noise.

I need a buffer amp for the output of my Kelvin-Varley divider. Or I need a voltage reference below about 4V to calibrate the x1 range. This is a lab problem and not a problem of the voltmeter.

I need to investigate Barbouri's v2 design and see if there is anything worth adding to my design.


# References

## App Notes

Shielding and guarding: https://www.analog.com/media/en/technical-documentation/application-notes/41727248an_347.pdf

Staying well grounded: https://www.analog.com/en/analog-dialogue/articles/staying-well-grounded.html

Millivolt meter PCB: https://www.barbouri.com/2016/05/26/millivolt-meter/ and https://www.barbouri.com/2019/08/07/millivolt-meter-version-2/

EMI filtering for DC-DC converters: https://www.ti.com/lit/an/snva489c/snva489c.pdf

Ferrite beads demystified: https://www.analog.com/en/analog-dialogue/articles/ferrite-beads-demystified.html

Shielding and guarding: https://www.analog.com/media/en/technical-documentation/application-notes/41727248an_347.pdf

PCB guidelines for reduced EMI: https://www.ti.com/lit/an/szza009/szza009.pdf

Overvoltage protection for sensitive amplifier applications: https://www.maximintegrated.com/en/design/technical-documents/app-notes/4/4035.html

Switching low-level signals to a DMM: https://www.ni.com/en-us/innovations/white-papers/06/switching-low-level-signals-to-a-dmm.html




## Datasheets

Voltage reference, ADR4540, used in Scullcom's meter: https://www.analog.com/media/en/technical-documentation/data-sheets/ADR4520_4525_4530_4533_4540_4550.pdf

Voltage reference, MAX6126, used in my meter, kelvin connections: https://datasheets.maximintegrated.com/en/ds/MAX6126.pdf

Negative adjustable voltage regulator, LM337L: https://www.ti.com/lit/ds/symlink/lm337l.pdf

HV low noise zero-drift op-amp, LTC2057, used in my meter: https://www.analog.com/media/en/technical-documentation/data-sheets/2057f.pdf

Zero-drift single-supply rail-to-rail op-amp, AD8628, used in Scullcom's meter: https://www.analog.com/media/en/technical-documentation/data-sheets/AD8628_8629_8630.pdf

ADC 24-bit, LTC2400: https://www.analog.com/media/en/technical-documentation/data-sheets/2400fa.pdf

SPI digital isolator, ADuM3152: https://www.analog.com/media/en/technical-documentation/data-sheets/ADuM3151_3152_3153.pdf

ATmega32U4: https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7766-8-bit-AVR-ATmega16U4-32U4_Datasheet.pdf



## Software

64-bit floating point library for AVR-8: https://fp64lib.org/documentation/fp64lib-library-reference/ and https://github.com/fp64lib/fp64lib

MAX7219 7-seg LED driver library: https://github.com/JemRF/max7219

PinChangeInterrupt: https://github.com/NicoHood/PinChangeInterrupt

Statistics library for Arduino: https://github.com/RobTillaart/Statistic

