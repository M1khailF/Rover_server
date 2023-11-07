
class Esp_rover
{
  public:
  void begin();
  bool arm(int arm);
  bool motor(float motor);
  bool servo(float servo);
  private:
  void main_f();


};
