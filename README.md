AuraLogic IP: Hardware-Optimized 3D Inverse Kinematics (IK) Solver
Author: Ivy Nguyen | Company: AuraLogic IP
Status: Prototyping (C++ Algorithmic Model)
📌 Project Overview
Welcome to the algorithmic foundation of the AuraLogic Kinematic Core.
This repository contains a highly optimized C++ mathematical model for solving 3-DOF (Degrees of Freedom) Inverse Kinematics. It is designed from the ground up to be later synthesized into Hardware IP Cores (FPGA/ASIC) via HLS (High-Level Synthesis) for real-time Edge Robotics.
🧠 Algorithmic Architecture: 3D to 2D Decoupling
To ensure zero-latency hardware implementation, this solver avoids computationally expensive 3D spherical coordinate matrices. Instead, it utilizes the Planar Projection (Decoupling) Technique:
Base Rotation (1D Yaw): Uses the hardware-friendly atan2(Z, X) to instantly rotate the base joint, forcing the 3D target into the robot's local 2D working plane.
Arm Articulation (2D Pitch): Once aligned, the 3D space collapses into a flat 2D triangle. The algorithm then applies the Law of Cosines to resolve the Shoulder and Elbow angles.
Safety Constraints: Includes hardware safety checks to prevent NaN arithmetic errors and mechanical failures when the target exceeds the arm's physical reach.
⚡ Why C++ for Hardware?
Python is for prototyping, but C++ is the language of Silicon. This model is written with strict data typing (double, int) and sequential logic to prepare for a seamless transition into RTL (Register-Transfer Level) design.
By translating mathematical equations (like trigonometric functions) into hardware logic (such as CORDIC algorithms in the future), this IP core will execute IK calculations without any CPU/Software overhead.
🚀 Next Steps (Roadmap)

Complete 3D IK Mathematical Model (C++).

Implement CORDIC algorithms to replace <cmath> standard libraries.

HLS Synthesis for Xilinx/Altera FPGA platforms.

Performance benchmarking (Latency vs. Power consumption).
