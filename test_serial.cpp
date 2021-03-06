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
#include <iostream>
#include <thread>
using namespace boost::asio;
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    string data_out;
    io_service udp_service;
    
    char *temp = new char[1024];
    boost::system::error_code ec;

    ip::address_v4 targetIP;
    targetIP.from_string("140.172.240.223", ec);

    boost::asio::ip::udp::endpoint endpoint_(targetIP, 15211);

    ip::udp::socket socket_(udp_service, endpoint_.protocol());


    socket_.set_option(ip::udp::socket::reuse_address(true));
    socket_.set_option(socket_base::broadcast(true));
    // Use defaults for all input parameters except the 
    cout << "Opening port at /dev/ttyO2..." << endl;
    string comm = "/dev/ttyO2";
    io_service io;
    
    boost::asio::streambuf response_data;
    
    char delimiter = '\r';


    serial_port_base::baud_rate baud(19200);

    // Create and open the serial port...
    serial_port port(io, comm);

    cout << "Setting baud rate to 19200..." << endl;
    port.set_option(baud);
    cout << "Starting broadcast on port 15211..." << endl;
    
    
    while (true) {
        port.write_some(buffer("B32000\r"));

        // Synchronous read_until
        read_until(port, response_data, delimiter);


        std::istream is(&response_data);
        getline(is, data_out);

        cout << "\r" << data_out << flush;

        copy(data_out.begin(), data_out.end(), temp);
        socket_.send_to(buffer(data_out, data_out.size()), endpoint_);

        sleep(1);
    }


    return 0;
}

