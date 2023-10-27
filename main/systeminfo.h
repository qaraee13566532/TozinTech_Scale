
#include "esp_chip_info.h"
 
class esp_systeminfo
{
   private:
   esp_chip_info_t chip_info;
   public:
   void print();
};
