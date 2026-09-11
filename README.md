#  AuraLogic IP: Hardware-Optimized Edge AI & Kinematics Engine
**Author:** Ivy Nguyen | **Company:** AuraLogic IP  
**Update V2.0:** Integrated Custom Neural Network Inference Engine (C++)

##  Project Overview (V2.0 Update)
Welcome to the algorithmic foundation of the **AuraLogic Kinematic Core**. 
In this Version 2.0 update, the solver has been completely refactored using **Object-Oriented Programming (OOP)** and integrated with a custom **Edge AI Inference Engine**. 

Instead of relying on heavy mathematical matrices (Jacobian) for multi-DOF robots, this architecture uses a Neural Network to predict base coordinates, combined with Planar Projection (Law of Cosines) for pinpoint accuracy.

##  Architectural Highlights
1. **Zero-Dependency AI Inference:** The Neural Network is written in pure, raw C++ (Multiply-Accumulate operations + ReLU activations). No external libraries (like TensorFlow or OpenCV) are used, making it 100% ready for **High-Level Synthesis (HLS)**.
2. **OOP Multi-Instance Control:** Packaged into a `bonaoRobot` (Robot Brain) class. You can instantiate multiple limbs (`left_arm`, `right_arm`) running parallel inference simultaneously without memory collision.
3. **Proprietary Weights:** *Note: The trained weight matrix file (`ma_tran_AI.h`) is AuraLogic IP's trade secret and is NOT included in this public repo. This code serves as an architectural demonstration of the inference pipeline.*

## Hardware Acceleration Roadmap
This C++ model is strictly statically-typed. The next phase involves using Xilinx Vitis HLS to synthesize these MAC operations into FPGA DSP slices, driving latency down from milliseconds to the microsecond level.

---
*Evaluating B2B Licensing? Please check the `LICENSE.txt` or contact me directly.*
