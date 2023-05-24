# loadcell
     measuring the force exerted by a rocket /. beyond rocket design

/* Program for load cell with HX711
  Arduino UNO - HX711 Module - 1-ton Load Cells
  Beyond Rocket Design Project   May 24, 2023
  Library: https://github.com/bogde/HX711
*/

/*
 BLACK CABLE CELL WIRES:
 Red: E+
 Black: E-
 White: A-
 Green: A+
 The remaining wire is just a mesh.

 GRAY CABLE CELL WIRES:
 Red: E+
 Yellow: E-
 White: A-
 Green: A+
 The black wire is just a mesh.
*/

/*
 Calibration (black cable load cell): -4700
 Calibration (gray cable load cell):
 It is necessary to calculate a new calibration factor for each load cell. Follow the steps below to do this:
 1. Run the code.
 2. calibration_factor = average of values in the serial monitor / known weight on the load cell.
*/

Sample:
![ezgif com-gif-maker](https://github.com/alighieribot/loadcell/assets/131944578/eb261fa0-bd4e-4e00-839f-43e814144ebf)
