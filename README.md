This project implements a complete Edge-to-Cloud architecture where environmental parameters are monitored locally and uploaded to the cloud for remote access and analysis.
The system continuously reads temperature and relative humidity using a DHT11 sensor, displays the values on an LCD, and uploads the data to the ThingSpeak cloud every 3 minutes using an ESP01 Wi-Fi module.
A user-defined temperature set-point is stored in AT24C256 EEPROM to ensure persistence even after power failure. If the temperature exceeds the configured threshold, the system activates a buzzer alert and updates an alert field on the cloud.
Features:

1. Real-time temperature & humidity monitoring

2.LCD display for local visualization

3. Cloud data upload to ThingSpeak (every 3 minutes)

4. Threshold-based alert system (buzzer + cloud alert field)

5. User-configurable temperature set-point

6.EEPROM-based non-volatile storage

7. External interrupt for instant set-point update mode

8. Works locally even if internet is unavailable
   
 System Architecture:

Edge Layer (Device Side)

LPC2148 ARM7 Microcontroller

DHT11 Sensor

LCD (16x2)

AT24C256 EEPROM (I2C)

4×4 Matrix Keypad

Buzzer

External Interrupt Switch.
Working Principle:

1.On startup, the system loads the temperature set-point from EEPROM.

2.Continuously reads temperature and humidity from DHT11.

3.Displays live readings on LCD.

4.Every 3 minutes:

5.Uploads temperature & humidity to ThingSpeak.

6.If temperature exceeds the set-point:

7.Activates buzzer alert.

8.Sends alert data to a dedicated cloud field.

9.User can press interrupt switch to:

10.Enter new set-point via keypad.

11.Store updated value in EEPROM.
