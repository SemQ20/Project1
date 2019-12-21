#pragma once

String^ I2C_Read(int testn, int ProdNum, double(*CABLE_KOEF)[2][3], double(*POWER_KOEF)[3], double(*POWER_CORRECT)[2][3], I2CParams^i2cp);

bool I2C_send_byte(int Testn, int ProdNum, I2CParams^ ParmsI2c, bool checked, bool synchrCheck);