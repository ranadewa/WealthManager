- [WealthManager](#wealthmanager)
  - [Introduction](#introduction)
    - [Use Cases Covered](#use-cases-covered)
      - [Investment related](#investment-related)
      - [User Management related](#user-management-related)
  - [Setting up the project](#setting-up-the-project)
  - [Running the project](#running-the-project)
  - [User Manual](#user-manual)
    - [Loging in](#loging-in)
    - [Adding investments](#adding-investments)
    - [User Management & Currency conversion](#user-management--currency-conversion)
    - [CPPRestSDK](#cpprestsdk)


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
* Once client binary is run. It will generate a login window as shown below
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
### [CPPRestSDK](https://github.com/microsoft/cpprestsdk#getting-started)




* For Ubuntu 16.04 the installation command doesn't generate the necessary .cmake file So we have to [build it from the source](https://death-of-rats.github.io/posts/building-cpprest-sample/).
  * Checkout to branch ubuntu_16.04
  * Install needed build tools and libs:
    ```
    sudo apt-get install g++ git libboost-atomic-dev libboost-thread-dev libboost-system-dev libboost-date-time-dev libboost-regex-dev libboost-filesystem-dev libboost-random-dev libboost-chrono-dev libboost-serialization-dev libwebsocketpp-dev openssl libssl-dev ninja-build
    ```.
    
   

[boost_system]

For windows:   
inside build folder:  
cmake .. "-DCMAKE_TOOLCHAIN_FILE=D:/Work/Source/Repos/vcpkg/scripts/buildsystems/vcpkg.cmake"

For Ubuntu:
cmake . -DCMAKE_PREFIX_PATH=/usr/lib/x86_64-linux-gnu/cmake


References:   
[CPPREST](https://mariusbancila.ro/blog/2017/11/19/revisited-full-fledged-client-server-example-with-c-rest-sdk-2-10/)
[QT Signals & Slots](https://doc.qt.io/qt-5/signalsandslots.html)


https://github.com/microsoft/cpprestsdk/issues/686

[set cmake module path] (https://stackoverflow.com/questions/8711109/could-not-find-module-findopencv-cmake-error-in-configuration-process)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

[cannot install cpprest](https://github.com/microsoft/cpprestsdk/issues/686#issuecomment-458009956)
