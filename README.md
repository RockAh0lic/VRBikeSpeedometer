# Tachometer with Bluetooth communication
This code is an Arduino sketch that allows you to create a tachometer that can communicate over Bluetooth. It utilizes a hall-effect sensor or any other type of sensor to read the RPM of a spinning object and then sends that data to a Bluetooth module to be transmitted to another device.

# Configuration
The code contains a configuration zone that should be modified according to your setup. The following configuration options are available:

- digitalBluetoothRXpin and digitalBluetoothTXpin: the digital pins used for Bluetooth communication.
- analogTachometerPin: the analog pin used for reading the RPM signal.
- magnets: the number of magnets attached to the spinning object.
- samples: the number of samples to be taken for RPM calculation.
- automaticSampler: enable or disable automatic RPM precision control.
- readTimeOut: the time in milliseconds to wait for another reading before zeroing out the RPM value.

## Variables
- analogValue: the analog value read from the tachometer sensor.
- digitalValue: the digital value read from the tachometer sensor.
- serialData: the serial data received over Bluetooth.
- rpmSampleInterval: the sample ratio used for automatic RPM precision control.
- maxSamples: the maximum number of samples allowed.
- sampleCounter: the number of samples taken so far.
- oldSampleCounter: the number of samples taken in the previous iteration.
- ignoreFirstSample: a boolean flag used to ignore the first sample taken.
- sampleTimeCounter: the time counter used for timeout control.
- rpmCurrentTime: the current time in microseconds.
- rpmRefferenceTime: the reference time in microseconds.
- rpmDeltaTime: the time difference between the current and reference times.
- currentRPM: the current RPM value.
- summedRPM: the sum of all RPM values taken so far.
- instantRPM: the RPM value calculated from the last sample.
- refferenceTime: the reference time in milliseconds.
- currentTime: the current time in milliseconds.
- deltaTime: the time difference between the current and reference times.

## Functions
- setup(): initializes the Bluetooth serial connection and the tachometer sensor pin.
- loop(): calculates the RPM value and the time difference, updates the timeout counter, and sends data over Bluetooth.
- calculateDeltaTime(): calculates the time difference between the current and reference times.
- calculateRPM(): calculates the RPM value from the tachometer sensor readings.
- printRPM(): prints the current RPM value and the number of samples taken to the serial monitor and sends the RPM value over Bluetooth.

# Usage
To use this code, you will need an Arduino board, a Bluetooth module, and a tachometer sensor. Connect the sensor to the analog input pin specified in the configuration zone and connect the Bluetooth module to the digital input pins specified in the configuration zone. Upload the code to the Arduino board and power it up. Use a Bluetooth terminal application to receive the RPM values transmitted by the Arduino board.

Note that this code is designed to work with a sensor that outputs a digital signal (i.e. a hall-effect sensor). If your sensor outputs an analog signal, you will need to modify the code accordingly.

# Pictures
Can be found in the 'VR Bike Thingy' folder
