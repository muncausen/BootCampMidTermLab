

there are two executables:
    1- CANTranceiver
    2- DriveLine Emulator

    DriveLine Emulator includs:
    2.1- CANReceiver: receiving CAN frames from the User Input module and saves them.
        since CAN communication a event based, then once CANReceiver receives a new frame will
        call a methode from Server and pass the reference of saved frame/s to the Server class.

    2.2-Server: Receives CAN frames, once they published, unpack data and checks if CAN communication is ok and CAN bus is alive.
        also Server packs the result one are ready and sends it to CANSender.

    2.3- DriveLine: Server passes unpacked data to related module in DriveLine.
        each software component does its job and save the result in its variables. Calculated speed and RPM will be collected by server from where other DriveLine components stored.
    2.4- CANSender: this class has a data collector function which is called by the Server. 
        Server will pass then the reference of where the calculated values are stored. CANSender will put data together in a CAN fram.

    pros: secure sw design. calculation and data are hidden inside DriveLine. DriveLine Emulator's Interface has no information about sensetive data or functions from DriveLine.
    cons: might be not easy to do unit test per software component.