# 🏦 Sarnath Advanced Banking System

A comprehensive C-based banking management system with advanced features including user authentication, money transfers, transaction history, and administrative controls.

## 📋 Table of Contents

- [Features](#features)
- [System Requirements](#system-requirements)
- [Installation & Setup](#installation--setup)
- [Usage Guide](#usage-guide)
- [Admin Panel](#admin-panel)
- [User Features](#user-features)
- [File Structure](#file-structure)
- [Security Features](#security-features)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)

## ✨ Features

### 🔐 Security & Authentication
- **Secure password hashing** for user accounts
- **Hidden password input** during login
- **Account lockout** after 3 failed login attempts
- **Admin authentication** system
- **Account blocking/unblocking** functionality

### 💳 Banking Operations
- **Multiple account types**: Savings, Current, Premium
- **Money deposit** with real-time balance updates
- **Money withdrawal** with minimum balance validation
- **Money transfer** between accounts
- **Transaction history** with detailed records
- **Balance inquiry** and account details

### 👤 Account Management
- **New account creation** with validation
- **Password change** functionality
- **Account status management** (Active/Blocked)
- **User profile management**
- **Email and mobile validation**

### 🛠️ Administrative Features
- **View all accounts** overview
- **Block/unblock accounts**
- **System statistics**
- **Transaction monitoring**
- **User management**

## 🖥️ System Requirements

- **Operating System**: Windows (uses `conio.h` and `system("cls")`)
- **Compiler**: GCC or any C compiler supporting C99 standard
- **Memory**: Minimum 4MB RAM
- **Storage**: 10MB free disk space

## 🚀 Installation & Setup

### Step 1: Download the Source Code
```bash
# Clone or download the banking_system.c file
```

### Step 2: Compile the Program
```bash
gcc banking_system.c -o banking_system.exe
```

### Step 3: Run the Application
```bash
./banking_system.exe
```

## 📖 Usage Guide

### Initial Setup

When you first run the program, it will create necessary data files:
- `accounts.dat` - Stores all account information
- Binary format for secure data storage

### Main Menu Options

```
╔══════════════════════════════════════════════════════════════╗
║                    SARNATH ADVANCED BANK                    ║
║                   Professional Banking System               ║
╠══════════════════════════════════════════════════════════════╣
║  [1] Admin Login                                            ║
║  [2] User Login                                             ║
║  [3] Create New Account                                     ║
║  [4] Exit                                                   ║
╚══════════════════════════════════════════════════════════════╝
```

## 🔑 Admin Panel

### Admin Credentials
- **Username**: `admin`
- **Password**: `admin`

### Admin Features
1. **View All Accounts** - Complete overview of all bank accounts
2. **Block Account** - Disable user account access
3. **Unblock Account** - Restore account access
4. **System Statistics** - View total accounts and bank balance

### Admin Dashboard
```
╔══════════════════════════════════════════════════════════════╗
║                      ADMIN DASHBOARD                        ║
╚══════════════════════════════════════════════════════════════╝

[1] View All Accounts
[2] Block Account
[3] Unblock Account
[4] View System Statistics
[5] Back to Main Menu
```

## 👨‍💼 User Features

### Account Creation
1. **Personal Information**
   - Full name (letters and spaces only)
   - Username (8-15 characters, must be unique)
   - Email address (valid format required)
   - Mobile number (10 digits)
   - Date of birth (DD/MM/YYYY)

2. **Account Types & Minimum Balances**
   - **Savings**: ₹500 minimum balance
   - **Current**: ₹1,000 minimum balance  
   - **Premium**: ₹5,000 minimum balance

3. **Security Setup**
   - Password creation with confirmation
   - Automatic account number generation

### User Dashboard
```
╔══════════════════════════════════════════════════════════════╗
║                    WELCOME [User Name]                      ║
║                      USER DASHBOARD                         ║
╚══════════════════════════════════════════════════════════════╝

[1] View Account Details
[2] Deposit Money
[3] Withdraw Money
[4] Transfer Money
[5] Transaction History
[6] Change Password
[7] Logout

Current Balance: ₹[Amount]
```

### Banking Operations

#### 💰 Deposit Money
- Enter amount to deposit
- Real-time balance update
- Transaction record creation
- Instant confirmation

#### 💸 Withdraw Money
- Amount validation
- Minimum balance checking
- Secure withdrawal process
- Updated balance display

#### 🔄 Transfer Money
- Enter target account number
- Recipient verification
- Amount validation
- Dual transaction recording
- Transfer confirmation

#### 📊 Transaction History
```
Date                 Type            Amount      Balance     Description
================================================================================
29/07/2025 14:30    DEPOSIT         ₹1000.00    ₹1500.00    Cash Deposit
29/07/2025 15:45    TRANSFER_OUT    ₹500.00     ₹1000.00    Transfer to John Doe
```

## 📁 File Structure

```
banking_system/
├── banking_system.c          # Main source code
├── banking_system.exe        # Compiled executable
├── accounts.dat              # Binary data file (auto-generated)
└── README.md                # This documentation
```

## 🔒 Security Features

### Password Security
- **User passwords**: Encrypted using hash function
- **Admin password**: Plain text for simplicity
- **Hidden input**: Passwords masked during entry

### Account Protection
- **Failed attempt tracking**: Max 3 attempts
- **Automatic lockout**: Account blocked after failed attempts
- **Admin override**: Admins can unblock accounts

### Data Security
- **Binary storage**: Efficient and secure data format
- **Input validation**: All user inputs validated
- **Memory management**: Proper allocation and cleanup

## 🐛 Troubleshooting

### Common Issues

#### "Invalid admin credentials"
- **Solution**: Use username `admin` and password `admin`
- **Check**: Ensure no extra spaces in input

#### "Account not found"
- **Solution**: Verify correct account number or username
- **Check**: Account may be blocked - contact admin

#### "Insufficient balance"
- **Solution**: Check minimum balance requirements:
  - Savings: ₹500
  - Current: ₹1,000
  - Premium: ₹5,000

#### "File cannot be opened"
- **Solution**: Ensure write permissions in program directory
- **Check**: Run as administrator if necessary

### Data File Issues

If `accounts.dat` becomes corrupted:
1. Delete the file
2. Restart the program
3. Create new accounts

## 📝 Account Types Comparison

| Feature | Savings | Current | Premium |
|---------|---------|---------|---------|
| Minimum Balance | ₹500 | ₹1,000 | ₹5,000 |
| Account Purpose | Personal savings | Business transactions | High-value accounts |
| Withdrawal Limit | Standard | Unlimited | Unlimited |
| Transfer Limit | ₹1,000,000 | ₹1,000,000 | ₹1,000,000 |

## 🔄 Workflow Example

### Creating a New Account
1. Select option [3] from main menu
2. Enter personal details
3. Choose account type
4. Set password
5. Make initial deposit
6. Receive account number
7. Login with new credentials

### Making a Transfer
1. Login to user account
2. Select [4] Transfer Money
3. Enter recipient account number
4. Verify recipient details
5. Enter transfer amount
6. Confirm transaction
7. View updated balance

## 📈 System Limitations

- **Maximum accounts**: 1,000
- **Maximum transactions per account**: 100
- **Maximum transfer amount**: ₹1,000,000
- **Username length**: 8-15 characters
- **Password length**: Up to 19 characters

## 🛡️ Best Practices

### For Users
- **Keep credentials secure**: Don't share username/password
- **Regular password changes**: Use change password feature
- **Monitor transactions**: Check transaction history regularly
- **Report issues**: Contact admin for account problems

### For Administrators
- **Regular backups**: Backup `accounts.dat` file
- **Monitor system**: Check system statistics regularly
- **User management**: Block suspicious accounts promptly
- **Data security**: Ensure secure file permissions

## 🤝 Contributing

### How to Contribute
1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

### Code Standards
- Follow existing code style
- Add comments for complex functions
- Test all new features
- Update documentation

## 📞 Support

For technical support or questions:
- Review this README
- Check troubleshooting section
- Submit issues via repository

## 📄 License

This project is open source and available under the MIT License.

---

**🏦 Sarnath Advanced Banking System** - Professional banking solution for educational and demonstration purposes.

*Last updated: July 29, 2025*