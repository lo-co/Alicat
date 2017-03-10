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

using namespace boost;
using namespace std;

SerialSession::SerialSession(serial_struct sdata) : io(), port(io), timer(io), Session(serial_data) {
    serial_data = sdata;
    connect();
}

bool SerialSession::connected() const{
    
    return port.is_open();
    
}

void SerialSession::writeString(string s)
{
    // Add the termination character...
    if (serial_data.use_term_char) s += serial_data.termination_char;
    
    asio::write(port,asio::buffer(s.c_str(),s.size()));
}

void SerialSession::read(char *data, size_t size)
{
    if(readData.size()>0)//If there is some data from a previous read
    {
        istream is(&readData);
        size_t toRead=min(readData.size(),size);//How many bytes to read?
        is.read(data,toRead);
        data+=toRead;
        size-=toRead;
        if(size==0) return;//If read data was enough, just return
    }
    
    //setupParameters=ReadSetupParameters(data,size);
    //performReadSetup(setupParameters);

    //For this code to work, there should always be a timeout, so the
    //request for no timeout is translated into a very long timeout
    if(serial_data.timeout!=posix_time::seconds(0)) timer.expires_from_now(serial_data.timeout);
    else timer.expires_from_now(posix_time::hours(100000));
    
    timer.async_wait(boost::bind(&SerialSession::timeoutExpired,this,
                asio::placeholders::error));
    
    result=resultInProgress;
    bytesTransferred=0;
    for(;;)
    {
        io.run_one();
        switch(result)
        {
            case resultSuccess:
                timer.cancel();
                return;
            case resultTimeoutExpired:
                port.cancel();
                throw(timeout_exception("Timeout expired"));
            case resultError:
                timer.cancel();
                port.cancel();
                throw(boost::system::system_error(boost::system::error_code(),
                        "Error while reading"));
            //if resultInProgress remain in the loop
        }
    }
}

string SerialSession::readString(size_t size)
{
    string result(size,'\0');//Allocate a string with the desired size
    read(&result[0],size);//Fill it with values
    return result;
}

string SerialSession::readStringUntil()
{

    //For this code to work, there should always be a timeout, so the
    //request for no timeout is translated into a very long timeout
    if(serial_data.timeout!=posix_time::seconds(0)) timer.expires_from_now(serial_data.timeout);
    else timer.expires_from_now(posix_time::hours(100000));

    timer.async_wait(boost::bind(&SerialSession::timeoutExpired,this,
                asio::placeholders::error));

    result=resultInProgress;
    bytesTransferred=0;
    
    for(;;)
    {
        io.run_one();
        switch(result)
        {
            case resultSuccess:
                {
                    timer.cancel();
                    bytesTransferred-=serial_data.termination_char.size();//Don't count delim
                    istream is(&readData);
                    string result(bytesTransferred,'\0');//Alloc string
                    is.read(&result[0],bytesTransferred);//Fill values
                    is.ignore(serial_data.termination_char.size());//Remove delimiter from stream
                    return result;
                }
            case resultTimeoutExpired:
                port.cancel();
                throw(timeout_exception("Timeout expired"));
            case resultError:
                timer.cancel();
                port.cancel();
                throw(boost::system::system_error(boost::system::error_code(),
                        "Error while reading"));
            //if resultInProgress remain in the loop
        }
    }
}
void SerialSession::timeoutExpired(const boost::system::error_code& error)
{
     if(!error && result==resultInProgress) result=resultTimeoutExpired;
}

void SerialSession::connect() {
    if (connected()) close_connection();
    port.open(serial_data.port);
    port.set_option(asio::serial_port_base::baud_rate(serial_data.baud_rate));
    port.set_option(serial_data.parity);
    port.set_option(serial_data.csize);
    port.set_option(serial_data.flow);
    port.set_option(serial_data.stop);
}

void SerialSession::performReadSetup(const ReadSetupParameters& param)
{
    if(param.fixedSize)
    {
        asio::async_read(port,asio::buffer(param.data,param.size),boost::bind(
                &TimeoutSerial::readCompleted,this,asio::placeholders::error,
                asio::placeholders::bytes_transferred));
    } else {
        asio::async_read_until(port,readData,param.delim,boost::bind(
                &TimeoutSerial::readCompleted,this,asio::placeholders::error,
                asio::placeholders::bytes_transferred));
    }
}

SerialSession::~SerialSession() {
    
    if (connected()) close_connection();
}
