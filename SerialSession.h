/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SerialSession.h
 * Author: mrichardson
 *
 * Created on March 9, 2017, 3:03 PM
 */

#ifndef SERIALSESSION_H
#define SERIALSESSION_H

#include <boost/asio.hpp>
#include <string>
#include "Session.h"

struct msg_settings{
    char termination_char;
    bool enable_term_char;
    int timeout;
    int loop_rate;
};

struct port_settings{
    int baud;
    boost::asio::serial_port_base::character_size csize;
    /* Values are: none, software, hardware */
    boost::asio::serial_port_base::flow_control fctl;
    /* Values are: none, odd, even */
    boost::asio::serial_port_base::parity parity;
    /* Values are: none, onepointfive, two */
    boost::asio::serial_port_base::stop_bits sbits;
};

struct serial_struct : data {
    std::string dev;
    boost::asio::serial_port port;
    port_settings psettings;
    msg_settings msg_set;
    
    
};


class SerialSession : Session {
public:


    SerialSession(const serial_struct& serial_data);
    
    void close_port();
    
    void write(std::string data_in);
    std::string read_bytes(int nbytes);
    
    // Read until termination character or timeout reached...
    std::string read_to_termination();
    
    // blocking rw to prevent stepping on communication...
    std::string sync_rw(std::string data_in);
    
    
    std::string read_bytes(int nbytes);
    

    inline bool is_connected() {
        serial_port_->is_open();
    };

    virtual ~SerialSession();
private:
    std::shared_ptr<boost::asio::serial_port> serial_port_;
    msg_settings msg;
    port_settings psettings;

};

#endif /* SERIALSESSION_H */

