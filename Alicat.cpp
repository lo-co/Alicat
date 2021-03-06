/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Alicat.cpp
 * Author: mrichardson
 * 
 * Created on March 7, 2017, 4:11 PM
 */

#include "Alicat.h"

namespace device {

    Alicat::Alicat(const std::string &id, const std::string &addr, 
            boost::shared_ptr<BufferedAsyncSerial> *port) :
    Device(id), address(addr), serial_port(port) {
        
        // TODO: Here we will add code to open the serial connection; use the 
        // paradigm as the session data object - when we go to grab the serial 
        // connection, we will check out the connection.  If it is not open,
        // attempt to open it...
    }

    Alicat::Alicat(const Alicat& orig) {
    }
    Alicat::retrieve_data(){
        ;
    }
    void Alicat::set_flowrate(double Q){
            
            std::string cmd =  
                    address + std::to_string((int)(Q/range)*64000) + '\r';
        }

    Alicat::~Alicat() {
        
        // TODO: Add the release of the serial port resource here
    }
}
