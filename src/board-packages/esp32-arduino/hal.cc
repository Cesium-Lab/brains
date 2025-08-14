#include <Arduino.h>


// Silencing the gods of Arduino linkage
int main();
void loop() {}
void setup() {main();}

namespace Cesium {
    
void hal_init() {
    ::init();
}

} // namespace Cesium