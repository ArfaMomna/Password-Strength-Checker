# Password Strength Checker README

## Overview

This is a simple password manager written in C. It allows users to store and retrieve passwords for different accounts. The program check the strength of the password and provide suggestions for improvements.

## Features

   1) Password strength checker: The program evalutes the strength of a password based on it's length,useof uppercase and lowercase letters,digits,and special characters.
   2) Password Suggestion: If a password is weak, the program provides suggestions for improvement,such as adding more characters , using uppercase and lowercase letters, digits, and special  caharcters.
   3) Breached password checker: the program checks if a password is in a list of commonly breached passwords and warns the user if it is.
   4) Password storage: The program stores account names amd passwords in a file named
   "passwords.txt".
   5) Search Functionality: The program allows users to search for passwords by account name.

   ## Usage  

   1.Compile the program using a C program.
   2.Run the program.
   3.Follow the menu prompts to add new passwords,search for existing passwords,or exit the program.

   ## Menu Options

   1) Add new password: Allows users to add a new account name and password. The program checks the strength of the password and provides suggections for improvements.
   2) Search by account name: Allows users to search for a password by account name.
   3) Exit: Exits the program.
   4) Get suggestions for a password: Allows users to check the strength of a password and get suggestions for improvements without adding it to the password storage.

   ## Requirements

   1) A C compiler
   2) A Windows operating system (due to the use of window.h for Beep functionality)

   ## Security Note

   This program stores passwords in plain text, which is not secure.In a real-world application, passwords should be hashed and stored securely. This program is intended for educational purposes only.
