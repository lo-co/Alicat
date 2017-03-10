/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main_test_simple.cpp
 * Author: mrichardson
 *
 * Created on March 9, 2017, 11:34 AM
 */

#include "Session.h"
#include <iostream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    data temp_data;
    data temp_data2;
    temp_data2.ID = "another_test";
    temp_data.ID = "testing";
    cout << "Opening 1st session" << endl;
    session_manager::create_open_session(temp_data);
    cout << "Opening 2nd session" << endl;
    session_manager::create_open_session(temp_data);
    cout << "Opening 3rd session" << endl;
   session_manager::create_open_session(temp_data);
   cout << "Opening new session instance" << endl;
   session_manager::create_open_session(temp_data2);
    
    return 0;
}

