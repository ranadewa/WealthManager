- [WealthManager](#wealthmanager)
  - [Introduction](#introduction)
    - [Use Cases Covered](#use-cases-covered)
      - [Investment related](#investment-related)
      - [User Management related](#user-management-related)
    - [High Level Architecture](#high-level-architecture)
  - [Setting up the project](#setting-up-the-project)
  - [Running the project](#running-the-project)
  - [User Manual](#user-manual)
    - [Loging in](#loging-in)
    - [Adding investments](#adding-investments)
    - [User Management & Currency conversion](#user-management--currency-conversion)
  - [Libraries Used](#libraries-used)
    - [CPPRestSDK](#cpprestsdk)
    - [Nlomaan Json](#nlomaan-json)
    - [QT Framework](#qt-framework)


# WealthManager
Personal wealth management system in C++

## Introduction 
* This project is implmented to manage personal finance mainly in investment domain. It provides a multi user system with multiple predefined currencies to work with.
### Use Cases Covered
#### Investment related
* As a user, I want to store the amount of money with thier respective currencies that I hold in different banks.
* As a user, I want to store the amount of share market investments I have done in different instruments (ie. Equity, Bonds, Reits)
* As a user, I want to store the value of my properties (ie. Residential, Commercial, Land)
* As a user, I want to store other type of investments I have done.
* As a user, I want to have a consolidated overview of all of my current investments in USD.
* As a user, I want to maintain my financial activities in multiple currencies. (eg: United States Dollar, Singapore Dollar, Sri Lankan Rupee)
* As a user, I want to update the currency conversion rates.
  
#### User Management related
* As a user, I want to have authenticated access to my information. (Requiring user name & password before fetching user data)
* As a user, I want to create new users who can use this system. 
* As a user, I want to have an admin user which will be created by default with predefined username & password to initially login to the system. 
* As a user, I want to change my existing password.

### High Level Architecture
* A C++ client communicates with a C++ server using REST protocol. Data is transfered as JSON objects and persisted in the disk as files.   
  <img src="images/high_level_Arc.png" width="600"/>
## Setting up the project  
* Clone the repository while recursing submodules. Use command below.
  ```
  git clone https://github.com/ranadewa/WealthManager --recurse-submodules
  ```
* Build libraries in 3rd Party folder. Go into 3rd Party folder. Create a build directory and build the libraries.
  ```
  cd 3rdParty
  mkdir build
  cd build
  cmake ..
  make
  ```
* Build source files. Start inside the WealthManager directory. ie ```/home/workspace/WealthManager```
  ```
  mkdir build
  cd build
  cmake ..
  make
  ```
## Running the project
* Two binaries will be created inside build directory when above is done.
  * Server Binary in : /home/workspace/WealthManager/build/Server/src/
  * Client binary in: /home/workspace/WealthManager/build/QTClient/Client/
* Go to Server binary path above. Run server:
  ```
    ./server 
  ```
* Go to Client binary path above. Run client:
  ```
  `./Client
  ```

## User Manual
### Loging in
* As instructed above, run server and client binaries.
* Once client binary is run. It will generate a login window as shown below.     
  <img src="images/login.png" width="300"/>
* For inital login use user name as **admin** & password as **123**. Password can be changed once logged in.   
* Once logged in ***Overview*** tab will be displayed.   
  <img src="images/overview_first_login.png" width="600"/>
### Adding investments
* Click on ***Investments*** tab. Click on add new button.   
  <img src="images/investments_first_login.png" width="600"/>
* A new dialog to add new investments will be displayed. Fill the neccessary information and click add button.   
  <img src="images/add_new_investment.png" width="300"/> 
* Confirmation dialog will be displayed. Click OK and focus will go back to Investments page. Then click refresh button in bottom right corner.   
  <img src="images/confirmation_dialog.png" width="600"/>
* The inserted information will be shown in the correct insvestment table.   
  <img src="images/investments_updated1.png" width="600"/>
* As above add few different investments. Click refresh.   
  <img src="images/investments_multiple.png" width="600"/>
* Go to ***Overview*** tab. Now overview will be sources from updated information.   
  <img src="images/overview_updated.png" width="600"/>
### User Management & Currency conversion
* Go to ***System*** tab. Click on add user button to add a user.   
  <img src="images/add_new_user.png" width="600"/>
* A new user dialog is generated. Add necessary information and click ok.   
  <img src="images/new_user_dialog.png" width="300"/>
* Click Get Users button & all existing users will be listed in the table.   
  <img src="images/get_users_listing_existing.png" width="600"/>
* To change logged in user's password, click Change Password button.    
  <img src="images/change_password.png" width="300"/>
* To update currency conversion rates. Select respective currency from 2nd drop down in Currency conversion group and update it to correct value. Currently, only conversion from USD is supported. These rates will be used to calculate overview's total assets in USD.   
  <img src="images/currency_conversion.png" width="600"/>

## Libraries Used
### [CPPRestSDK](https://github.com/microsoft/cpprestsdk#getting-started)
This is used to create a REST server with API defined. This library resides in 3rdParty folder.
### [Nlomaan Json](https://github.com/nlohmann/json)
This header only library is copied to common folder to create a static library along side solution defined Data Transfer Objects.
### [QT Framework](https://www.qt.io/product/development-tools)
QT is used to create the GUI of the client.
