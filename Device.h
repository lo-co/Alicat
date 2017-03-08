/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Device.h
 * Author: mrichardson
 *
 * Created on March 7, 2017, 4:19 PM
 */

#ifndef DEVICE_H
#define DEVICE_H
#include <string>
#include "../Data/Data.h"

namespace device {

    class Device {
    public:
        /** Constructor for the Device class.
         * 
         */
        Device(const std::string &id = "");
        //Device(const Device& orig);

        reusable::Data get_data() {
            return data;
        };
       
        /** Method for retrieving data from a device.
         * 
         * This is a method that is specific to the implementation of the device in
         * question.  This is intended to serve as the template for the actual 
         * retrieval of the data.
         * 
         * @returns data from the device
         */
        virtual void retrieve_data() = 0;

        virtual ~Device();

    protected:
        
        reusable::Data data;

    private:

        std::string ID;

    };
}

#endif /* DEVICE_H */

