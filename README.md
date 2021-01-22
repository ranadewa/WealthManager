# WealthManager
Personal wealth management system in C++

## PreRequisites  
### [CPPRestSDK](https://github.com/microsoft/cpprestsdk#getting-started)

* For Ubuntu 16.04 the installation command doesn't generate the necessary .cmake file So we have to [build it from the source](https://death-of-rats.github.io/posts/building-cpprest-sample/).
  * Checkout to branch ubuntu_16.04
   

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