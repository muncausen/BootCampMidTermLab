


    
    DriveLine:

    ![emulator.png]

    1- CANTranceiver
    2- Server
    2- DriveLine Simulator

    1- CANTranceiver: receiving CAN frames from the UserInput module and saves CAN frames. It also receives info from Server and publish them on CAN bus.
        
    2-Server: The purpose of Server is to provide interface for the DriveLine Simulator and encapsulates it. It takes CAN frames, once they published and takes back the reulsts from Simulator then sends them to CANTranceiver.

    3- DriveLine Simulator: Once it Receives deta from the Server calculates speed and RPM etc. It has no public interface, only talks to the Server.

    2.4- test: performs GoogleTest on the DriveLine unit.

    Repository [Engine Emulator](https://github.com/muncausen/BootCampMidTermLab/tree/main/Emulator).
