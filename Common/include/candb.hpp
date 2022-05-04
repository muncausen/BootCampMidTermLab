
struct UserInputCanFrame {
  unsigned frame_counter : 4;
  unsigned ignition : 2;
  unsigned gear_select : 4;
  unsigned throttle : 8;
  unsigned brake : 8;
  unsigned blinkers : 2;
};

struct DisplayCanFrame {
  unsigned frame_counter : 4;
  unsigned ignition : 2;
  unsigned gear_select : 4;
  unsigned speed : 8;
  unsigned rpm : 8;
  unsigned blinkers : 2;
};
