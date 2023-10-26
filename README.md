# WDS
## Main info
The goal of the project was to create a graphical application that visualizes data from sensors simulating a car's front parking sensors. The project consists of both hardware and software components. The first part consists of an Arduino Uno microcontroller and 4 ultrasonic sensors (HC-SR04). The second part, on the other hand, is an application designed to visualize whether there is an obstacle in front of the sensors and, if so, at what distance.

## User Interface

The device's configuration is done through a dialog window that appears when you press the "Settings" button and then select from the dropdown menu "Connection." It allows you to choose the port to which the desktop application should connect. When the window is opened, it scans for active ports. Additionally, when the main window is closed, any open dialog window will automatically close. This behavior is visible.
<p align="center">
  <img src="https://github.com/JakubBacik/WDS/blob/main/Picture/Dialog.png" alt="Dialog">
</p>

The main window consists of two tabs. In the first tab, there is a 2D simulation that illustrates the distance from an obstacle by illuminating the corresponding section in red. The effect of this operation is visible in Figure 3. The activation of specific sections is related to the distance from the obstacle.

<p align="center">
  <img src="https://github.com/JakubBacik/WDS/blob/main/Picture/MainWindow.png" alt="MainWindow" width="600">
</p>

The charts illustrate the history of the sensor's distance from an obstacle over a period of 20 seconds. On the horizontal axis, you can find time, which increments from the device's connection, while on the vertical axis, you have the distance value expressed in centimeters. In this tab, there are four charts, one for each distance sensor.

<p align="center">
  <img src="https://github.com/JakubBacik/WDS/blob/main/Picture/PlotWindow.png" alt="PlotWindow" width="600">
</p>


## Testing

The figure presents tests of the application under sample working conditions by simulating various obstacle placement situations. On the right side, you can see the application window, while on the left side, there is the device and obstacles.
<table>
  <tr>
    <td><img src="https://github.com/JakubBacik/WDS/blob/main/Picture/FrontView1.png" alt="FrontView1"></td>
    <td><img src="https://github.com/JakubBacik/WDS/blob/main/Picture/FrontView2.png" alt="FrontView2"></td>
  </tr>
</table>

## Communication
The communication is done using UART (Universal Asynchronous Receiver-Transmitter). The QSerialPort library was used for communication. The communication frame looks as follows:
* The header is the character "X".
* The frame body consists of four distance sensor values separated by spaces. The distance values are in centimeters.
* The checksum is CRC16.

<p align="center">
  <img src="https://github.com/JakubBacik/WDS/blob/main/Picture/DataFrame.jpg" alt="DataFrame">
</p>

## Hardware Part

The device consists of four ultrasonic sensors HC-SR04 and an Arduino Uno, enclosed in a cardboard box.
There is a program that cyclically retrieves information from the four sensors, creates a frame with this information, adding a header, which is the character "X," and a checksum.
<table>
  <tr>
    <td><img src="https://github.com/JakubBacik/WDS/blob/main/Picture/HardwarePart1.jpg" alt="HardwarePart1" height="250"></td>
    <td><img src="https://github.com/JakubBacik/WDS/blob/main/Picture/HardwarePart2.jpg" alt="HardwarePart2" height="250"></td>
  </tr>
</table>
