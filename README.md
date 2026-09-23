# 🦾 AuraLogic IP: Hardware-Optimized Edge AI & Kinematics Engine
**Author:** Ivy Nguyen | **Company:** AuraLogic IP  
**Update V3.0:** Upgraded to 5-DOF Humanoid Arm Architecture!

## Project Overview (V3.0 Update)
Welcome to the algorithmic foundation of the **AuraLogic Kinematic Core**. 
In this update, the OOP architecture has been expanded to support a **5-DOF Humanoid Arm**. 

To keep it hardware-friendly for future FPGA synthesis (HLS), I avoided computationally heavy Inverse Jacobian matrices. Instead, this model uses the **Wrist Decoupling** technique:
1. Abstracting the End-Effector to find the wrist center.
2. Reducing the remaining arm into a 2D planar triangle.
3. Solving the Shoulder and Elbow angles cleanly using the Law of Cosines.

## Architectural Highlights
1. **Zero-Dependency C++:** Written in raw C++ without external heavy libraries. It is structured to be 100% ready for **High-Level Synthesis (HLS)**.
2. **OOP Multi-Instance Control:** Packaged into a robot arm class. You can easily instantiate multiple limbs running simultaneously.
3. **Proprietary IP Notice:** *The Field-Oriented Control (FOC) motor drivers and AI trained weights are currently kept private for a future commercial/competition prototype. This repository serves as a mathematical and architectural baseline.*

##  Next Steps
Tackling CORDIC algorithms to replace `<cmath>` for true RTL hardware optimization.

---
*Evaluating B2B Licensing? Please check the `LICENSE.txt` or contact me directly.*
