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

Each gear will drive a limited range of speed based on throtle.

Requested Throtle | Gear     | speed upr  | speed lwr thr |
| :---            | :---:    |    :----:  |         :---: |
|0                | Gear 0   | 0          | 0             |
|0 ~ 20           | Gear 1   | 0          | 20            |
|20 ~ 40           | Gear 2   | 20         | 50            |
|40 ~ 60           | Gear 3   | 50         | 80            |
|60 ~ 80           | Gear 4   | 80         | 150           |
|80 ~ 100           | Gear 5   | 150        | 180           |
