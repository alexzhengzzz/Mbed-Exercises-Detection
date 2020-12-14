#ifndef FILTER_H
#define FILTER_H
/**** Filter Parameters  ****/
const float PI = 3.1415926;
const uint8_t N = 10;
 
class FILTER {
  public:
    FILTER();
    float filterAngle(int16_t zAccel);
  private:
    float g_z = 0;
    float ringbuf[N];
    uint8_t ringbuf_index = 0;
};
#endif