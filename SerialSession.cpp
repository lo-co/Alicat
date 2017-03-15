/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SerialSession.cpp
 * Author: mrichardson
 * 
 * Created on March 9, 2017, 3:03 PM
 */

#include "SerialSession.h"
#include <boost/bind.hpp>
#include <boost/asio/error.hpp>

using namespace boost;
using namespace std;

SerialSession::SerialSession(const serial_struct& sdata) : psettings(sdata.psettings), msg(sdata.msg_set), Session(sdata) {

    asio::io_service serial_service;
    serial_port_ = std::shared_ptr<asio::serial_port>(new asio::serial_port(serial_service, sdata.dev));
}

void SerialSession::close_port() {
    if (serial_port_->is_open()) {
        serial_port_->close();
    }
}

SerialSession::~SerialSession() {

    if (serial_port_->is_open()) serial_port_->close();

}
