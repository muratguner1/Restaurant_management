# Restaurant Management System

This project is a simple restaurant management system written in C.  
It supports two types of users: **Admin** and **Customer**, and includes basic functions such as table management, order tracking, and logging.

---

## Features

- **Admin Privileges:**
  - Display menu
  - Create and delete tables
  - View order lists
  - Confirm orders
  - Maintain and view system logs

- **Customer Privileges:**
  - Display menu
  - Place orders
  - Cancel orders
  - View order list
  - Pay bills

- **Common Functions:**
  - Display menu
  - Read and write order lists
  - Write logs to files

---


## Build and Run

Step 1: Clone the repo

```bash
git clone https://github.com/muratguner1/Restaurant_management.git
```

Step 2: Compile the project with the following commands in terminal:

Compaile Admin panel:

```bash
gcc -o adminPanel Admin/mainAdmin.c Admin/admin.c Common/common.c -IAdmin -ICommon
```

Compaile Customer panel:

```bash
gcc -o customerPanel Customer/mainCustomer.c Customer/customer.c Common/common.c -ICustomer -ICommon
```

- **Run Admin and Customer panels:**
    - Admin: ./adminPanel
    - Customer: ./customerPanel

# Requirements
    - GCC compailer
    - Cygwin or Linux environment
    - Standard C libraries (stdio.h, stdlib.h, dirent.h, unistd.h, etc.)

## Author

- **Murat Güner**


