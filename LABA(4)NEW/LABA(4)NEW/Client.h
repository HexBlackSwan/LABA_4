#pragma once
using namespace System;

ref class Client {
public:
    property String^ Name;
    property String^ Phone;

    Client(String^ name, String^ phone) {
        Name = name;
        Phone = phone;
    }
};