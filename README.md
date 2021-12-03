# Anti-Theft-Alarm-IoT
IoT Project - Building an interactive Anti Theft Alarm for lockers (Home security)
## What is this project about ?
The Anti-theft system along with fire alarm is an IOT project to protect our important belongings from being stolen. It adds additional security to homes, banks, lockers. Our main focus here is to build a home security alarm.
## Objective
* It is to provide home safety and detect burglary. 
* They provide protection against fire and such threats. 
* We will be mainly focusing on designing a fire alarm and burglary detection by giving an alarm and turning on the lights whenever it encounters a rise in temperature and motion in its vicinity. 
* There will be a motion sensor and DHT11 for detecting motion and temperature. We take the password of the locker through the serial monitor at the entry. 
  * If the password is correct then we do not activate any buzzer or alarm. 
  * If the password is incorrect or there has been no input and we detect a motion, then we activate buzzers and lights to indicate an attempt of theft. 
* If the temperature of the locker exceeds a certain amount, then we give a buzzer to indicate fire. 
## How to setup ?
* Before uploading the **project.ino** to your ESP32 make sure that you have put up your ssid and password correctly and also run **ifconfig** command in the terminal and paste your inet ip in the place of cse_ip in the code.
* Now to setup the om2m server firstly run **python3 sensors.py**to create entities and then open **127.0.0.1:8080 or 127.0.0.1:8080/webpage** in your favorite browser.
* Login to the om2m server. Your default **USERNAME: admin** and **PASSWORD: admin**
* Once logged into the server you will notice extra 3 entities(Motion, Temperature, and Humidity) created.
![m2m](https://user-images.githubusercontent.com/82858718/144572286-59c58597-dae2-4b00-a9fc-1a2ee673e318.png)

* Now upload the IDE code to your ESP32 and give your credentials within 20sec.
* **NOTE:** In case you get an error regarding SerialPort connection then try running this command: sudo chmod 777 /dev/ttyUSB0

## Data Analysis
To analyze the environment of your locker visually we retrieve the data collected in om2m server.
* Run the **retrieve.py** code: python3 retrieve.py
* This will output 3 different .png files
* 1st .png file is the data analysis of the Motion
* 2nd .png file is the data analysis of the temeperature
* 3rd .png file is the data analysis of the humidity.

## User Interface
* To view the locker status you need to first signin as the OWNER with correct credentials.
* Here the credentials are --> Username: Bhargavi and Password: 1234
* After correct signin you will be able see the locker status.
![monitor1](https://user-images.githubusercontent.com/82858718/144571799-f8a79280-0123-464d-b838-75a5d661c936.png)

# Try this and have Fun :) Thank You (:
