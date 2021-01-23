# WealthManager
Personal wealth management system in C++

## PreRequisites  
### [CPPRestSDK](https://github.com/microsoft/cpprestsdk#getting-started)

* For Ubuntu 16.04 the installation command doesn't generate the necessary .cmake file So we have to [build it from the source](https://death-of-rats.github.io/posts/building-cpprest-sample/).
  * Checkout to branch ubuntu_16.04
  * Install needed build tools and libs:
    ```
    sudo apt-get install g++ git libboost-atomic-dev libboost-thread-dev libboost-system-dev libboost-date-time-dev libboost-regex-dev libboost-filesystem-dev libboost-random-dev libboost-chrono-dev libboost-serialization-dev libwebsocketpp-dev openssl libssl-dev ninja-build
    ```
    
   

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