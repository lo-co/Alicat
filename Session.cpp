/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Session.cpp
 * Author: mrichardson
 * 
 * Created on March 9, 2017, 10:33 AM
 */

#include "Session.h"
#include <iostream>

Session::Session(data session_data):session_data(session_data){
    std::cout << "Creating new session..." << std::endl;
    
}

Session::~Session() {
    std::cout << "Destroying session with ID " + session_data.ID << std::endl;
}

namespace session_manager {

    // Use anonymous namespace to hide the map
    namespace {
    }

    boost::shared_ptr<Session> create_open_session(data session_data) {
        static std::map<std::string, boost::shared_ptr<Session> > sessions;


        std::map<std::string, boost::shared_ptr<Session> >::iterator it = sessions.find(session_data.ID);
        if (it != sessions.end()) {
            boost::shared_ptr<Session> temp(it->second);
            return temp;
        } else {
            boost::shared_ptr<Session> temp(new Session(session_data));
            sessions.insert(std::pair<std::string, boost::shared_ptr<Session> >(session_data.ID, temp));
            return temp;
        }



    }

}

