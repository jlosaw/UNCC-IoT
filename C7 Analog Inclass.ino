#include "Particle.h"

//SYSTEM_MODE(MANUAL);


const BleUuid serviceUuid("4677062c-ad02-4034-9abf-98581772427c");
const BleUuid valueUuid("dc13b36a-3499-46b0-ac11-5ac0173c4cc5");

BleCharacteristic valueCharacteristic("value", BleCharacteristicProperty::NOTIFY, valueUuid, serviceUuid);

const int ADC_PIN = A3;
const unsigned long UPDATE_PERIOD_MS = 100;
unsigned long lastUpdate = 0;

void setup() {
    Serial.begin();

    BLE.addCharacteristic(valueCharacteristic);

    BleAdvertisingData data;
    data.appendServiceUUID(serviceUuid);
    BLE.advertise(&data);
}

void loop() {
    if (BLE.connected()) {
    	if (millis() - lastUpdate >= UPDATE_PERIOD_MS) {
    		lastUpdate = millis();

        	uint8_t data[1];

        	// ADC value is 0-4095 (12 bits) but only put 8 unsigned bits in the data
        	// as we don't need the resolution and it avoid dealing with byte order issues.
        	data[0] = analogRead(ADC_PIN) >> 4;

        	valueCharacteristic.setValue(data, sizeof(data));
    	}
    }
}
