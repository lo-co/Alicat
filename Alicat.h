/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Alicat.h
 * Author: mrichardson
 *
 * Created on March 7, 2017, 4:11 PM
 */

#ifndef ALICAT_H
#define ALICAT_H
#include "Device.h"
#include <string>

namespace device {

    class Alicat : Device {
    public:
        Alicat(const std::string &id, const std::string &addr);
        Alicat(const Alicat& orig);

        void retrieve_data();
        virtual ~Alicat();
    private:
        std::string address;
        int range;

    };
}

#endif /* ALICAT_H */

