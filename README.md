# Campus Esports Tournament Registration System

**Course:** BCSE102L – Structured and Object-Oriented Programming  
**Student Name:** P. Latheesh Reddy  
**Registration Number:** 23BCE0329  
**Institution:** Vellore Institute of Technology (VIT), Vellore  
**Role:** Sole Contributor  
**Repository Location:** Local Git Repository at `C:\Users\lathe\Desktop\New folder (2)`  
**Target Remote:** `https://github.com/latheeshreddy/campus-esports-solid` (Staged & configured, ready to push upon remote creation)  

---

## 1. Project Overview

The **Campus Esports Tournament Registration System** is an object-oriented C++ application developed for collegiate gaming tournaments (such as BGMI, Valorant, and CS:GO competitions). Managing campus esports tournaments requires an architecture capable of accommodating rapidly changing event formats, varying team sizes (Solo, Squad, etc.), and multiple participant communication channels (Email, SMS, Push Notifications) without recurring modifications to core registration logic.

This project demonstrates the rigorous application of the **SOLID Principles** of Object-Oriented Design to build a robust, modular, and maintainable tournament registration system in modern C++ (C++17).

---

## 2. Problem Statement & Motivation

Traditional registration implementations often couple team registration logic with fee calculations (using error-prone `switch` or `if-else` blocks) and hardcode notification channels directly into manager classes. Such tightly-coupled designs:
- Violate the **Single Responsibility Principle** by forcing a single class to handle business registration, fee algorithms, and notification dispatching.
- Violate the **Open/Closed Principle** by requiring modifications to existing, tested classes whenever a new tournament category (e.g., Squad mode) or communication channel (e.g., SMS) is introduced.
- Violate the **Dependency Inversion Principle** by having high-level business managers directly depend on low-level concrete implementations.

By restructuring the system around segregated abstract interfaces and constructor-based dependency injection, our design decouples high-level policy from low-level details.

---

## 3. SOLID Principles Implementation

The architecture strictly adheres to all five SOLID principles as detailed below:

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

### 1. Single Responsibility Principle (SRP)
- **Concept:** A class should have one, and only one, reason to change.
- **Application:** `EmailNotification` is solely responsible for formatting and sending emails. It has zero knowledge of tournament fees, team sizes, or registration rules. Similarly, `RegistrationManager` coordinates registration workflows without embedding protocol-specific message delivery logic.

### 2. Open/Closed Principle (OCP)
- **Concept:** Software entities should be open for extension, but closed for modification.
- **Application:**
  - When introducing a new match format, **Squad Registration**, we created `SquadRegistration` implementing `IFeeCalculator` returning `Rs. 500.0`, without touching `SoloRegistration` or `RegistrationManager`.
  - When extending notifications with **SMS Alerting**, we introduced `SMSNotification` implementing `INotificationService` without modifying `RegistrationManager` or `EmailNotification`.

### 3. Liskov Substitution Principle (LSP)
- **Concept:** Subclasses must be substitutable for their base types without altering program correctness.
- **Application:** Any concrete implementation of `IFeeCalculator` (`SoloRegistration` or `SquadRegistration`) can be passed into `RegistrationManager::registerTeam(teamName, feeType)`. The manager interacts exclusively via `calculateFee() const`, guaranteeing uniform and predictable behavior without type introspection or dynamic casting.

### 4. Interface Segregation Principle (ISP)
- **Concept:** Clients should not be forced to depend upon interfaces that they do not use.
- **Application:** Instead of creating a monolithic `ITournament` interface containing both `calculateFee()` and `sendNotification()`, the responsibilities are split into two targeted interfaces: `IFeeCalculator` and `INotificationService`. This prevents fee calculation classes from being forced to implement dummy notification methods.

### 5. Dependency Inversion Principle (DIP)
- **Concept:** High-level modules should not depend on low-level modules; both must depend on abstractions.
- **Application:** `RegistrationManager` depends exclusively on abstractions rather than concrete implementations:
  - It receives `INotificationService` through **constructor injection** (using `std::shared_ptr<INotificationService>`).
  - It receives `IFeeCalculator` passed to `registerTeam()` as a **const reference** (`const IFeeCalculator& feeType`).
  This completely decouples the manager from low-level communication mechanisms and specific tournament pricing models:
  ```cpp
  class RegistrationManager {
  private:
      std::shared_ptr<INotificationService> notifier; // Injected via constructor
  public:
      RegistrationManager(std::shared_ptr<INotificationService> n) : notifier(n) {}

      // IFeeCalculator passed as a const reference
      void registerTeam(const std::string& teamName, const IFeeCalculator& feeType) {
          double fee = feeType.calculateFee();
          std::cout << "Registered " << teamName << ". Amount due: Rs." << fee << "\n";
          notifier->send("Registration successful for " + teamName);
      }
  };
  ```

---

## 4. Project Directory Structure

```
c:\Users\lathe\Desktop\New folder (2)\
├── include/
│   ├── INotificationService.h   # Notification interface (ISP)
│   ├── IFeeCalculator.h          # Fee calculation interface (ISP, OCP)
│   ├── EmailNotification.h       # Email delivery class (SRP)
│   ├── SMSNotification.h         # SMS delivery class (OCP extension)
│   ├── SoloRegistration.h        # Solo tournament category (Rs. 150)
│   ├── SquadRegistration.h       # Squad tournament category (Rs. 500)
│   └── RegistrationManager.h     # High-level coordinator (DIP)
├── src/
│   ├── EmailNotification.cpp     # Email implementation
│   ├── SMSNotification.cpp       # SMS implementation
│   ├── SoloRegistration.cpp      # Solo fee implementation
│   ├── SquadRegistration.cpp     # Squad fee implementation
│   └── RegistrationManager.cpp   # Registration manager logic
├── Case_Study_Screenshots/       # High-resolution documentation captures
│   ├── Screenshot_1_Project_Structure.png
│   ├── Screenshot_2_Interface_Implementation.png
│   ├── Screenshot_3_Email_and_SMS_Notification.png
│   ├── Screenshot_4_Fee_Calculation.png
│   ├── Screenshot_5_Registration_Manager.png
│   ├── Screenshot_6_Main_Function.png
│   ├── Screenshot_7_Compilation.png
│   ├── Screenshot_8_Program_Execution.png
│   └── Screenshot_9_SOLID_Principles_Demonstration.png
├── campus_esports_unified.cpp    # Consolidated single-file C++ program
├── main.cpp                      # Modular entry point
├── Makefile                      # Make build script
├── compile.bat                   # Windows batch compilation script
├── SOLID Case Study Submission.pdf # Original case study document
└── README.md                     # Project documentation
```

---

## 5. Compilation and Execution

### Prerequisites
- Modern C++ compiler with C++17 support (e.g., `g++` / MinGW-w64, Clang, or MSVC).

### Option A: Using the Automated Windows Script
Simply run the provided batch script:
```powershell
.\compile.bat
```

### Option B: Using g++ Command Line Directly
```powershell
g++ -std=c++17 -Wall -Wextra -Iinclude main.cpp src\EmailNotification.cpp src\SMSNotification.cpp src\SoloRegistration.cpp src\SquadRegistration.cpp src\RegistrationManager.cpp -o campus_esports.exe
.\campus_esports.exe
```

### Option C: Compiling Single-File Unified Code
```powershell
g++ -std=c++17 -Wall campus_esports_unified.cpp -o campus_esports_unified.exe
.\campus_esports_unified.exe
```

---

## 6. Execution Output Verification

When executed, the program produces the exact output required:

```
--- Campus Esports Registration ---
Registered Latheesh_Solo. Amount due: Rs.150
Sending Email: Registration successful for Latheesh_Solo
Registered VIT_Strikers. Amount due: Rs.500
Sending SMS text: Registration successful for VIT_Strikers
```

---

## 7. Case Study Screenshot Mapping Table

| Screenshot # | File Name | Case Study Section | Visual Content & Key SOLID Elements |
|---|---|---|---|
| **Screenshot 1** | `Screenshot_1_Project_Structure.png` | **Part B - Project Setup** | Full VS Code Explorer showing all 7 headers (`include/`), 5 sources (`src/`), build scripts, and unified files. |
| **Screenshot 2** | `Screenshot_2_Interface_Implementation.png` | **Part 1: Interfaces (ISP)** | Dual editor panes showing pure abstract classes `INotificationService` and `IFeeCalculator` with virtual methods and default virtual destructors. |
| **Screenshot 3** | `Screenshot_3_Email_and_SMS_Notification.png` | **Part 1 & Extension (SRP, OCP)** | Dual editor panes showing `EmailNotification` (SRP) and `SMSNotification` (OCP extension) implementing `send() override`. |
| **Screenshot 4** | `Screenshot_4_Fee_Calculation.png` | **Part 2: OCP & LSP** | Side-by-side view of `SoloRegistration` (Rs. 150) and `SquadRegistration` (Rs. 500) substituting `IFeeCalculator`. |
| **Screenshot 5** | `Screenshot_5_Registration_Manager.png` | **Part 2: DIP Implementation** | `RegistrationManager.h` and `.cpp` showing constructor dependency injection with `std::shared_ptr<INotificationService>`. |
| **Screenshot 6** | `Screenshot_6_Main_Function.png` | **Part 3: Main Execution** | `main()` function instantiating services, performing dependency injection, and executing Solo and Squad registrations. |
| **Screenshot 7** | `Screenshot_7_Compilation.png` | **Part 3: Build Verification** | VS Code integrated terminal showing successful `g++` compilation with zero errors and zero warnings. |
| **Screenshot 8** | `Screenshot_8_Program_Execution.png` | **Part 3: Execution Output** | Terminal capture displaying registration for `Latheesh_Solo` (Rs. 150, Email) and `VIT_Strikers` (Rs. 500, SMS). |
| **Screenshot 9** | `Screenshot_9_SOLID_Principles_Demonstration.png` | **Part C - Application of SOLID** | Comprehensive visual dashboard correlating each SOLID principle (SRP, OCP, LSP, ISP, DIP) directly to project classes and code. |

---

## 8. Reflection & Future Extensions

- **Current Architecture:** Interfaces are decoupled and stateless, enabling zero-touch extensibility for notification channels and registration categories.
- **Future Enhancements:**
  - Introduce dynamic fee calculators that accept player parameters (e.g., Early Bird discount, VIT Esports Club membership, or game title pricing BGMI vs. Valorant).
  - Add thread-safe asynchronous notification dispatching via a queueing mechanism.

