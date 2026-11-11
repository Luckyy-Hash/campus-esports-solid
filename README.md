# Campus Esports Tournament Registration System

[![C++17 CI Build](https://github.com/Luckyy-Hash/campus-esports-solid/actions/workflows/ci.yml/badge.svg)](https://github.com/Luckyy-Hash/campus-esports-solid/actions)
[![Language: C++17](https://img.shields.io/badge/Language-C%2B%2B17-blue.svg)](https://isocpp.org/)
[![License: Academic](https://img.shields.io/badge/License-Academic%20Evaluation-green.svg)](#)
[![Institution: VIT Vellore](https://img.shields.io/badge/Institution-VIT%20Vellore-orange.svg)](https://vit.ac.in)

**Course:** BCSE102L – Structured and Object-Oriented Programming  
**Student Name:** P. Latheesh Reddy  
**Registration Number:** 23BCE0329  
**Institution:** Vellore Institute of Technology (VIT), Vellore  
**Role:** Sole Contributor  
**Public Repository:** [https://github.com/Luckyy-Hash/campus-esports-solid](https://github.com/Luckyy-Hash/campus-esports-solid)  

---

## 1. Project Overview & Architectural Modes

The **Campus Esports Tournament Registration System** is an object-oriented C++17 application designed for collegiate esports tournaments (such as BGMI, Valorant, and Counter-Strike). The system demonstrates how modern software engineering principles solve real-world problems in event ticketing, multi-tier pricing, and multi-channel notification routing.

### Dual Execution Modes

To strictly preserve the academic scope of the original submission while providing an interactive mini-project, the codebase provides two complementary modes:

| Mode | Entry Point | Target Audience & Purpose |
|---|---|---|
| **Mode 1: Interactive Menu-Driven Application** | `campus_esports.exe` (run directly) | Fully interactive tournament manager featuring participant registration, session tables, statistics, notification testing, and robust input validation. |
| **Mode 2: Case Study Benchmark Demonstration** | `campus_esports.exe --demo` or `campus_esports_unified.exe` | The exact batch demonstration described in the submitted case study report. Outputs Solo (Rs. 150) with Email and Squad (Rs. 500) with SMS. |
| **Optional Companion Dashboard** | [`dashboard.html`](dashboard.html) | Standalone visual web simulator in dark theme. *Note for evaluation: Strictly an optional visual companion; distinct from the core C++ application.* |

---

## 2. Interactive Application Features (Phase 1)

When launched without arguments, `campus_esports` presents a robust console interface:

```text
========================================
       CAMPUS ESPORTS TOURNAMENT        
========================================

1. Register Solo Player
2. Register Squad Team
3. View Registered Participants
4. View Registration Fee Details
5. Demonstrate Email Notification
6. Demonstrate SMS Notification
7. View Tournament Statistics
8. Exit

========================================
Enter your choice (1-8): 
```

### Feature Highlights:
1. **Solo Player Registration:** Prompts for participant name, evaluates fee via `SoloRegistration` (Rs. 150.00), injects `EmailNotification`, and records session data.
2. **Squad Team Registration:** Prompts for squad name, evaluates fee via `SquadRegistration` (Rs. 500.00), injects `SMSNotification`, and records session data.
3. **Participant Directory:** Displays a formatted, aligned table of all players/teams registered during the current active session.
4. **Fee Structure Details:** Explains how `IFeeCalculator` decouples tournament pricing from the manager, allowing zero-touch additions of new modes (e.g., Duo).
5. **Direct Notification Demonstrations:** Triggers standalone alerts via `EmailNotification` and `SMSNotification` to verify protocol isolation.
6. **Live Tournament Statistics:** Calculates total registrations, count per category, and cumulative revenue in real-time.
7. **Crash-Proof Input Validation:** Gracefully handles invalid numeric choices, string inputs where integers are expected, and empty names without throwing exceptions or entering infinite loops.

---

## 3. SOLID Principles Architecture (Phase 2)

```
               +----------------------+
               | INotificationService |  <--- [ISP: Interface Segregation]
               +----------------------+
               | +send(message) = 0   |
               +----------------------+
                          ^
         +----------------+----------------+
         |                                 |
+-------------------+             +-----------------+
| EmailNotification |             | SMSNotification |  <--- [SRP & Extension (OCP)]
+-------------------+             +-----------------+
| +send(message)    |             | +send(message)  |
+-------------------+             +-----------------+

               +----------------------+
               |    IFeeCalculator    |  <--- [ISP: Interface Segregation]
               +----------------------+
               | +calculateFee() = 0  |
               +----------------------+
                          ^
         +----------------+----------------+
         |                                 |
+-------------------+             +-------------------+
| SoloRegistration  |             | SquadRegistration |  <--- [OCP & LSP]
+-------------------+             +-------------------+
| +calculateFee()   |             | +calculateFee()   |
| (returns 150.0)   |             | (returns 500.0)   |
+-------------------+             +-------------------+

                        +----------------------+
                        | RegistrationManager  |  <--- [DIP: Depends on Abstractions]
                        +----------------------+
                        | -notifier: shared_ptr|
                        +----------------------+
                        | +registerTeam()      |
                        +----------------------+
```

1. **Single Responsibility Principle (SRP):**  
   `EmailNotification` handles exclusively email delivery. `RegistrationManager` coordinates tournament business flow without knowing communication protocol details.
2. **Open/Closed Principle (OCP):**  
   New match formats (`SquadRegistration`) and notification channels (`SMSNotification`) were introduced by deriving from abstract base classes without altering a single line of existing core code.
3. **Liskov Substitution Principle (LSP):**  
   Any subclass of `IFeeCalculator` (`SoloRegistration`, `SquadRegistration`) seamlessly substitutes the base interface when passed into `RegistrationManager::registerTeam(name, feeType)`.
4. **Interface Segregation Principle (ISP):**  
   Instead of one bloated interface containing both pricing and messaging, interfaces are segregated into `IFeeCalculator` and `INotificationService`.
5. **Dependency Inversion Principle (DIP):**  
   `RegistrationManager` depends exclusively on abstractions:
   - Receives `INotificationService` through **constructor injection** (`std::shared_ptr<INotificationService>`).
   - Receives `IFeeCalculator` as a **`const` reference** in `registerTeam(name, const IFeeCalculator&)`.

---

## 4. Project Directory Structure

```
campus-esports-solid/
├── .github/
│   └── workflows/
│       └── ci.yml               # Automated C++17 GitHub Actions workflow
├── include/
│   ├── INotificationService.h   # Notification abstraction (ISP)
│   ├── IFeeCalculator.h          # Fee calculation abstraction (ISP, OCP)
│   ├── EmailNotification.h       # Email protocol delivery (SRP)
│   ├── SMSNotification.h         # SMS protocol delivery (OCP extension)
│   ├── SoloRegistration.h        # Solo pricing model (Rs. 150)
│   ├── SquadRegistration.h       # Squad pricing model (Rs. 500)
│   └── RegistrationManager.h     # High-level coordinator (DIP)
├── src/
│   ├── EmailNotification.cpp     # Email implementation
│   ├── SMSNotification.cpp       # SMS implementation
│   ├── SoloRegistration.cpp      # Solo calculation logic
│   ├── SquadRegistration.cpp     # Squad calculation logic
│   └── RegistrationManager.cpp   # Registration management & session tracking
├── Case_Study_Screenshots/       # Original Case Study verification captures (1-9)
│   ├── Screenshot_1_Project_Structure.png
│   ├── Screenshot_2_Interface_Implementation.png
│   ├── Screenshot_3_Email_and_SMS_Notification.png
│   ├── Screenshot_4_Fee_Calculation.png
│   ├── Screenshot_5_Registration_Manager.png
│   ├── Screenshot_6_Main_Function.png
│   ├── Screenshot_7_Compilation.png
│   ├── Screenshot_8_Program_Execution.png
│   └── Screenshot_9_SOLID_Principles_Demonstration.png
├── Demo_Screenshots/             # Interactive Mini-Project demo captures (1-7)
│   ├── Demo_1_Main_Menu.png
│   ├── Demo_2_Solo_Registration.png
│   ├── Demo_3_Squad_Registration.png
│   ├── Demo_4_Participant_Listing.png
│   ├── Demo_5_Fee_Calculation.png
│   ├── Demo_6_Notification_Output.png
│   └── Demo_7_Tournament_Statistics.png
├── campus_esports_unified.cpp    # Standalone single-file submission benchmark
├── main.cpp                      # Interactive CLI driver with menu & session management
├── dashboard.html                # Optional interactive web companion simulator
├── Makefile                      # Cross-platform GNU Make script (Linux & Windows)
├── compile.bat                   # Automated Windows batch compiler script
├── .gitignore                    # Excludes binaries, object files, and local PDFs
└── README.md                     # Comprehensive project documentation
```

---

## 5. Instructions for Faculty & Evaluators

### Step 1: Clone the Repository
```bash
git clone https://github.com/Luckyy-Hash/campus-esports-solid.git
cd campus-esports-solid
```

### Step 2: Compile the Project

#### On Windows (PowerShell or Command Prompt):
**Option A — Automated Script:**
```powershell
.\compile.bat
```

**Option B — Direct g++ Command:**
```powershell
g++ -std=c++17 -Wall -Wextra -Iinclude main.cpp src\EmailNotification.cpp src\SMSNotification.cpp src\SoloRegistration.cpp src\SquadRegistration.cpp src\RegistrationManager.cpp -o campus_esports.exe
```

#### On Linux / macOS (Terminal):
**Option A — Using Make:**
```bash
make
./campus_esports
```

**Option B — Direct g++ Command:**
```bash
g++ -std=c++17 -Wall -Wextra -Iinclude main.cpp src/*.cpp -o campus_esports
./campus_esports
```

---

## 6. Execution Options

### Option A: Launch Interactive Menu Application
```bash
./campus_esports          # Linux / macOS
.\campus_esports.exe      # Windows
```

### Option B: Run Original Case Study Batch Demonstration
```bash
./campus_esports --demo   # Linux / macOS
.\campus_esports.exe --demo # Windows
```

*Expected Batch Output:*
```text
--- Campus Esports Registration ---
Registered Latheesh_Solo. Amount due: Rs.150
Sending Email: Registration successful for Latheesh_Solo
Registered VIT_Strikers. Amount due: Rs.500
Sending SMS text: Registration successful for VIT_Strikers
```

### Option C: Compile & Run Unified Case Study Benchmark
```bash
g++ -std=c++17 -Wall campus_esports_unified.cpp -o campus_esports_unified
./campus_esports_unified
```

---

## 7. Interactive Mini-Project Screenshots (`Demo_Screenshots/`)

All seven interactive capabilities have been captured from the running application:

| Demo # | Screenshot Link | Demonstrated Capability |
|---|---|---|
| **Demo 1** | [`Demo_1_Main_Menu.png`](Demo_Screenshots/Demo_1_Main_Menu.png) | Interactive CLI Menu (Options 1–8) |
| **Demo 2** | [`Demo_2_Solo_Registration.png`](Demo_Screenshots/Demo_2_Solo_Registration.png) | Solo Player registration with Rs. 150 fee & Email dispatch |
| **Demo 3** | [`Demo_3_Squad_Registration.png`](Demo_Screenshots/Demo_3_Squad_Registration.png) | Squad Team registration with Rs. 500 fee & SMS dispatch |
| **Demo 4** | [`Demo_4_Participant_Listing.png`](Demo_Screenshots/Demo_4_Participant_Listing.png) | Formatted table of registered participants in active session |
| **Demo 5** | [`Demo_5_Fee_Calculation.png`](Demo_Screenshots/Demo_5_Fee_Calculation.png) | Fee structure details demonstrating `IFeeCalculator` polymorphism |
| **Demo 6** | [`Demo_6_Notification_Output.png`](Demo_Screenshots/Demo_6_Notification_Output.png) | Standalone invocation of `EmailNotification` and `SMSNotification` |
| **Demo 7** | [`Demo_7_Tournament_Statistics.png`](Demo_Screenshots/Demo_7_Tournament_Statistics.png) | Real-time session metrics (total count, breakdown, total revenue) |

---

## 8. Original Case Study Verification Screenshots (`Case_Study_Screenshots/`)

The original nine implementation screenshots submitted in the case study report remain preserved:

| Screenshot # | File Link | Original Case Study Section |
|---|---|---|
| **Screenshot 1** | [`Screenshot_1_Project_Structure.png`](Case_Study_Screenshots/Screenshot_1_Project_Structure.png) | Project Folder Structure in VS Code |
| **Screenshot 2** | [`Screenshot_2_Interface_Implementation.png`](Case_Study_Screenshots/Screenshot_2_Interface_Implementation.png) | Pure Abstract Interfaces (`INotificationService` & `IFeeCalculator`) |
| **Screenshot 3** | [`Screenshot_3_Email_and_SMS_Notification.png`](Case_Study_Screenshots/Screenshot_3_Email_and_SMS_Notification.png) | `EmailNotification` & `SMSNotification` implementations |
| **Screenshot 4** | [`Screenshot_4_Fee_Calculation.png`](Case_Study_Screenshots/Screenshot_4_Fee_Calculation.png) | `SoloRegistration` & `SquadRegistration` fee calculators |
| **Screenshot 5** | [`Screenshot_5_Registration_Manager.png`](Case_Study_Screenshots/Screenshot_5_Registration_Manager.png) | `RegistrationManager` Constructor DI & `const` ref passing |
| **Screenshot 6** | [`Screenshot_6_Main_Function.png`](Case_Study_Screenshots/Screenshot_6_Main_Function.png) | Original `main.cpp` driver workflow |
| **Screenshot 7** | [`Screenshot_7_Compilation.png`](Case_Study_Screenshots/Screenshot_7_Compilation.png) | MinGW `g++` compilation terminal output |
| **Screenshot 8** | [`Screenshot_8_Program_Execution.png`](Case_Study_Screenshots/Screenshot_8_Program_Execution.png) | Original execution output (Solo Rs. 150 Email, Squad Rs. 500 SMS) |
| **Screenshot 9** | [`Screenshot_9_SOLID_Principles_Demonstration.png`](Case_Study_Screenshots/Screenshot_9_SOLID_Principles_Demonstration.png) | SOLID Principles verification matrix |

---

## 9. Automated CI/CD (GitHub Actions)

Every push to this repository automatically triggers a GitHub Actions workflow defined in [`.github/workflows/ci.yml`](.github/workflows/ci.yml) that:
1. Compiles the modular C++17 project with `-Wall -Wextra`.
2. Compiles the unified benchmark single-file project.
3. Executes batch verification (`--demo`).
4. Executes automated piped interactive session testing.
5. Runs tests on both **Ubuntu Linux** and **Windows (MinGW-w64)** environments.
