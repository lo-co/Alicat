/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   test_serial.cpp
 * Author: mrichardson
 *
 * Created on March 10, 2017, 2:39 PM
 */

#include <string>
#include <boost/asio.hpp>
using namespace boost::asio;

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    // Use defaults for all input parameters except the 
    
    string comm = "/dev/ttyO2";
    io_service io;
    boost::asio::streambuf response_data;
    char delimiter = '\r';
    serial_port_base::baud_rate baud(19200);
    
    // Create and open the serial port...
    serial_port port(io, comm);
    
    port.set_option(baud);
    
    port.write_some(buffer("B32000\r"));
    
    // Synchronous read_until
    read_until(port, response_data, delimiter);
    
    
    
    return 0;
}

