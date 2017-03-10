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

#include <stdexcept>
#include <boost/utility.hpp>
#include <boost/asio.hpp>
#include <string>
#include "Session.h"

/**
 * Thrown if timeout occurs
 */
class timeout_exception : public std::runtime_error {
public:

    timeout_exception(const std::string& arg) : runtime_error(arg) {
    }
};

struct serial_struct : data {
    unsigned int baud_rate;
    std::string port;
    boost::asio::serial_port_base::parity parity;
    boost::asio::serial_port_base::character_size csize;
    boost::asio::serial_port_base::flow_control flow;
    boost::asio::serial_port_base::stop_bits stop;
    long t;
    std::string termination_char;
    bool use_term_char;
    boost::posix_time::time_duration timeout; ///< Read/write timeout
};

class SerialSession : Session {
public:

    /**
     * Parameters of performReadSetup.
     * Just wrapper class, no encapsulation provided
     */
    class ReadSetupParameters {
    public:

        ReadSetupParameters() : fixedSize(false), delim(""), data(0), size(0) {
        }

        explicit ReadSetupParameters(const std::string& delim) :
        fixedSize(false), delim(delim), data(0), size(0) {
        }

        ReadSetupParameters(char *data, size_t size) : fixedSize(true),
        delim(""), data(data), size(size) {
        }

        //Using default copy constructor, operator=

        bool fixedSize; ///< True if need to read a fixed number of parameters
        std::string delim; ///< String end delimiter (valid if fixedSize=false)
        char *data; ///< Pointer to data array (valid if fixedSize=true)
        size_t size; ///< Array size (valid if fixedSize=true)
    };
    SerialSession(serial_struct serial_data);

    bool connected() const;
    void connect();

    /**
     * This member function sets up a read operation, both reading a specified
     * number of characters and reading until a delimiter string.
     */
    void performReadSetup(const ReadSetupParameters& param);

    /**
     * Set the timeout on read/write operations.
     * To disable the timeout, call setTimeout(boost::posix_time::seconds(0));
     */
    void setTimeout(const boost::posix_time::time_duration& t);


    /**
     * Write a string. Can be used to send ASCII data to the serial device.
     * To send binary data, use write()
     * \param s string to send
     * \throws boost::system::system_error if any error
     */
    void writeString(std::string s);

    /**
     * Read some data, blocking
     * \param data array of char to be read through the serial device
     * \param size array size
     * \return numbr of character actually read 0<=return<=size
     * \throws boost::system::system_error if any error
     * \throws timeout_exception in case of timeout
     */
    void read(char *data, size_t size);

    /**
     * Read a string, blocking
     * Can only be used if the user is sure that the serial device will not
     * send binary data. For binary data read, use read()
     * The returned string is empty if no data has arrived
     * \param size hw much data to read
     * \return a string with the received data.
     * \throws boost::system::system_error if any error
     * \throws timeout_exception in case of timeout
     */
    std::string readString(size_t size);

    /**
     * Read a line, blocking
     * Can only be used if the user is sure that the serial device will not
     * send binary data. For binary data read, use read()
     * The returned string is empty if the line delimiter has not yet arrived.
     * \param delimiter line delimiter, default="\n"
     * \return a string with the received data. The delimiter is removed from
     * the string.
     * \throws boost::system::system_error if any error
     * \throws timeout_exception in case of timeout
     */
    std::string readStringUntil();

    /**
     * Callack called either when the read timeout is expired or canceled.
     * If called because timeout expired, sets result to resultTimeoutExpired
     */
    void timeoutExpired(const boost::system::error_code& error);

    virtual ~SerialSession();
private:

    enum ReadResult {
        resultInProgress,
        resultSuccess,
        resultError,
        resultTimeoutExpired
    };

    boost::asio::io_service io; ///< Io service object
    boost::asio::serial_port port; ///< Serial port object
    boost::asio::deadline_timer timer; ///< Timer for timeout
    boost::asio::streambuf readData; ///< Holds eventual read but not consumed
    size_t bytesTransferred; ///< Used by async read callback
    enum ReadResult result; ///< Used by read with timeout
    serial_struct serial_data;

};

#endif /* SERIALSESSION_H */

