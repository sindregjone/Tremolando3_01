# Tremolando3_01

Tremolo effect pedal firmware for Teensy 3.1/3.2 running on the [OnkartGromt OpenEffects Project](https://www.onkartgromt.no/) (OEP2.2) platform with AK4558 codec.

## Features

- Stereo tremolo effect with adjustable depth and frequency
- 5 LFO waveforms: Sine, Sawtooth, Reverse Sawtooth, Square, Triangle
- Tap tempo with ratio control (1:1 up to 4:1 and 1:4)
- Mono/Stereo mode with 180° phase offset option
- CV input for expression pedal (depth and frequency)
- 128×64 OLED display showing waveform, depth, BPM and ratio
- NeoPixel LEDs for signal level and on/off status
- True bypass relay switching

## Controls

| Control | Function |
|---------|----------|
| Pot 1 | Output level |
| Pot 2 | LFO frequency |
| Pot 3 | Modulation depth |
| Pot 4 | Waveform shape |
| Tap 1 | On/Off toggle |
| Tap 2 | Tap tempo |
| SW1 | Tap ratio (up/down) |
| SW2 | Mono / Stereo (0° / 180° phase) |
| CV1 | Expression: depth |
| CV2 | Expression: frequency |

## Hardware

- **MCU:** Teensy 3.1 / 3.2
- **Platform:** OnkartGromt OpenEffects Project v2.2
- **Codec:** AK4558
- **Display:** 128×64 I2C OLED (SSD1306, address 0x3C)
- **LEDs:** Adafruit NeoPixel

## Dependencies

- [Teensy Audio Library](https://www.pjrc.com/teensy/td_libs_Audio.html)
- Adafruit GFX + SSD1306
- Adafruit NeoPixel
- Bounce
- Metro
- spieeprom (included)

## License

Based on the Teensy Audio Library by Paul Stoffregen / [PJRC](https://www.pjrc.com).
