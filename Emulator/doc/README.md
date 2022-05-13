# Engine Emulator Project

## -DriveLine

![Emulator](https://github.com/muncausen/BootCampMidTermLab/blob/main/Emulator/doc/emulator.png)

1- CANTranceiver

2- Server

3- DriveLine Simulator

4- test

1- CANTranceiver: receives CAN frames from the UserInput module and saves CAN frames. It also receives results from Server and publish them on CAN bus.
    
2-Server: The purpose of Server is to provide interface for the DriveLine Simulator and encapsulates it. It takes CAN frames, once they published and takes back the reulsts from Simulator then sends them to CANTranceiver.

3- DriveLine Simulator: Once it Receives deta from the Server calculates speed and RPM etc. It has no public interface, only talks to the Server.

4- test: performs GoogleTest on the DriveLine unit.

Repository [Engine Emulator](https://github.com/muncausen/BootCampMidTermLab/tree/main/Emulator).

if RPM is considered as a representative of the throttle for each RPM one speed is targeted. the vehicle will gradually approach the top speed for given throttle using transmission system.
 ![Speed vs RPM](https://github.com/muncausen/BootCampMidTermLab/blob/engine_sim/Emulator/doc/rpm_vs_speed_gear.png)
 
 by increasing acceleration request a.k.a increasing throttle more RPM then higher speed will be reached.
 ![RPM-Gear]
