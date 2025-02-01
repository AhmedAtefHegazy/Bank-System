# Bank System

## Description

The **Bank System** is a simple console-based C++ application that simulates basic banking operations. It allows users to create an account, check their balance, deposit and withdraw money, and perform other essential banking functions.

## Features

- User authentication with account number and PIN code
- Deposit and withdrawal functionality
- Balance inquiry
- Quick withdraw options
- Data storage using a text file (`Clients.txt`)
- Console-based user interface
- Client Management (Add, Remove, Update Clients)
- User Authentication System
- Currency Handling
- Transaction Logging (Transfers, Deposits, Withdrawals)
- Input Validation for Secure Data Handling

## Requirements

- C++ Compiler (GCC, MSVC, Clang, etc.)
- Any text editor or IDE (e.g., Visual Studio Code, Code::Blocks, Dev-C++)

## Installation & Setup

1. **Clone the Repository**

   ```sh
   git clone https://github.com/AhmedAtefHegazy/Bank-System.git
   ```

2. **Navigate to the Project Directory**

   ```sh
   cd Bank-System
   ```

3. **Compile the Source Code**

   ```sh
   g++ main.cpp -o BankSystem.exe
   ```

   *(Replace **`main.cpp`** with the actual main source file name if different.)*

4. **Run the Application**

   ```sh
   ./BankSystem.exe
   ```
5. **Login**

   ```sh
   ./User:User1
   ./PassWord:AhmedAtef1234
   ```

## Usage

1. Launch the application.
2. Enter your **Account Number** and **PIN Code**.
3. Choose an option from the menu:
   - Check Balance
   - Deposit Money
   - Withdraw Money
   - Quick Withdraw
   - Exit
4. Follow the on-screen instructions to perform banking operations.

## Project Structure
```
Project1/
├── Header Files/
│   ├── Core/
│   │   ├── CBankClient.h
│   │   ├── CCurrency.h
│   │   ├── CPerson.h
│   │   ├── CUser.h
│   ├── Lib/
│   │   ├── CDate.h
│   │   ├── CInputValidate.h
│   │   ├── CPeriod.h
│   │   ├── CString.h
│   │   ├── CUtil.h
│   ├── Screens/
│   │   ├── Client/
│   │   ├── Currencies/
│   │   ├── User/
│   │   ├── CMainMenueScreen.h
│   │   ├── CScreen.h
│   ├── Global.h
├── Source Files/
│   ├── Main.cpp
├── Text Files/
│   ├── Clients.txt
│   ├── Currencies.txt
│   ├── LoginRegister.txt
│   ├── TransferRegister.txt
│   ├── Users.txt
```

## Future Enhancements

- Implement Object-Oriented Programming (OOP) concepts
- Add an Admin Panel for better account management
- Encrypt stored user data for security
- Introduce a GUI version using C++ frameworks

## Contributing

Contributions are welcome! Feel free to fork this repository, make improvements, and submit a pull request.

## License

This project is licensed under the MIT License.

## Contact

- **Author:** Ahmed Atef Hegazy
- **GitHub:** [AhmedAtefHegazy](https://github.com/AhmedAtefHegazy)
- **Linkedin:** [[LinkedIn Profile](https://www.linkedin.com/in/ahmed-atef-hegazy/)]

---



