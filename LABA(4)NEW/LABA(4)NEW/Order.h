#pragma once
#include "Client.h"
#include "Tariff.h"

using namespace System;
using namespace System::ComponentModel;

ref class Order {
public:

    [Browsable(false)]
        property Client^ ClientData;

    [Browsable(false)]
        property Tariff^ TariffData;

    property double Volume;

    Order(Client^ c, Tariff^ t, double v) {
        ClientData = c;
        TariffData = t;
        Volume = v;
    }

    property String^ ClientName {
        String^ get() {
            if (ClientData == nullptr) return "";
            if (ClientData->Name == nullptr) return "";
            return ClientData->Name;
        }
    }

    property String^ ClientPhone {
        String^ get() {
            if (ClientData == nullptr) return "";
            if (ClientData->Phone == nullptr) return "";
            return ClientData->Phone;
        }
    }


    property String^ TariffType {
        String^ get() {
            if (TariffData == nullptr) return "";
            if (TariffData->TypeString == nullptr) return "";
            return TariffData->TypeString;
        }
    }

    property double TotalCost {
        double get() {
            if (TariffData == nullptr) return 0;
            return Volume * TariffData->PricePerUnit;
        }
    }

};