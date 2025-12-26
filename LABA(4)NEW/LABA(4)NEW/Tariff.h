#pragma once
using namespace System;

public enum class CargoType {
    General,
    Fragile,
    Hazardous,
    Refrigerated
};

ref class Tariff {
public:
    property CargoType Type;
    property double PricePerUnit;

    Tariff(CargoType type, double price) {
        Type = type;
        PricePerUnit = price;
    }

    // Äë˙ DataGridView
    property String^ TypeString {
        String^ get() {
            switch (Type) {
            case CargoType::General: return "General";
            case CargoType::Fragile: return "Fragile";
            case CargoType::Hazardous: return "Hazardous";
            case CargoType::Refrigerated: return "Refrigerated";
            default: return "Unknown";
            }
        }
    }
};