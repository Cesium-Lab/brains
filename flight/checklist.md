## For perfboard
- [x] Read Device ID and registers from all sensors
- [ ] Make all sensors have values in an Eigen Vector3d or similar structure, with quaternions
- [ ] Get calibrated data from sensors with configs
  - [ ] For "native" platform, have setup require reverse drivers for connection to a sim potentially?
- [ ] Send message over Ethernet, CAN, and Wifi (for ESP)
  - [ ] in correct packet framing

###
- GNC navigation (Sensors --> filtering --> state estimation --> uart)
  - [ ] Implement a simple Kalman filter for sensor fusion
  - [ ] Test the Kalman filter
  - [ ] Algorithms for calibrating sensors
  


