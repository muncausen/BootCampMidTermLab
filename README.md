# Engine Emulator Project

## 1- User Input

## 2-DriveLine

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

Any given throttle level will produce a certain RPM, RPM also is affected by the gear shifting. for a given car with a 265/60 R18 tire which has a Diameter of 775 and Circumference of 2435, bellow graph shows the relation between rpm-speed and gear shifting.

<<<<<<< Updated upstream
![Rpm vs Speed / Gear shifting @rpm2000](https://github.com/muncausen/BootCampMidTermLab/blob/engine_sim/Emulator/doc/rpm_vs_speed_gear.png)

whith changing throttle request by user RPM vs Gear vs Speed for the given car will be represented by bellow table:
![Rpm vs Speed / Gear shifting @rpm2000](https://github.com/muncausen/BootCampMidTermLab/blob/engine_sim/Emulator/doc/rpm_vs_speed_gear_t.png)
[ref.](https://www.blocklayer.com/rpm-gear.aspx)
=======
![Rpm vs Speed / Gear shifting @rpm2000](https://github.com/muncausen/BootCampMidTermLab/blob/main/Emulator/doc/rpm_vs_speed_gear-png)

whith changing throttle request by user RPM vs Gear vs Speed for the given car will be represented by bellow table:
![Rpm vs Speed / Gear shifting @rpm2000](https://github.com/muncausen/BootCampMidTermLab/blob/main/Emulator/doc/rpm_vs_speed_gear_t.png)
[ref.](https://www.blocklayer.com/rpm-gear.aspx)
>>>>>>> Stashed changes
