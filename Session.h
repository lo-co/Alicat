/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SimpleSession.h
 * Author: mrichardson
 *
 * Created on March 9, 2017, 10:33 AM
 */

#ifndef SIMPLESESSION_H
#define SIMPLESESSION_H

#include <boost/shared_ptr.hpp>
#include <string>
#include <map>

struct data {
    std::string ID;
};

class Session {
public:
    Session(data session_data);
    
    // Class is noncopyable
    Session(const Session &) = delete;
    Session& operator=(const Session&) = delete;


    virtual ~Session();
protected:
    data session_data;
};

namespace session_manager {
    boost::shared_ptr<Session> create_open_session(data session_data);
}
#endif /* SIMPLESESSION_H */

