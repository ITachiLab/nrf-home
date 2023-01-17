Overview
========

Modes of operation
------------------

A device can be configured to run in one of two different modes: simple advertiser, or bonded node. The choice of proper mode depends on a use-case.

Simple advertiser
+++++++++++++++++

When configured as a simple advertiser, the device does not require pairing to transmit data. The data is simply contained within advertising packets, so the other device simply listens for these packets and extracts the data as it appears. This mode allows the device to be very power efficient as no pairing or encrypting is performed. Bear in mind that anyone with a phone or a cheap BLE dongle can receive the data, thus it's not suitable for exchanging sensitive information. This mode also imposes a one-way communication, because there's no way to send something to a device which only advertises.

Simple advertiser is a good solution for:

- temperature/humidity sensors and other sensors transmitting not sensitive measurements,
- event indicators,
- various power efficient applications for non-critical data.

When configured properly, a simple advertiser can run on CR2032 battery for years.

Bonded node
+++++++++++

When a devices is bonded, connection details are remembered within the other device, so the device doesn't have to be paired again when it comes online. Additionally, the transmission is encrypted between bonded devices, so it's safe to transmit data from and to critical nodes. As opposed to simple advertiser, communication happens in two ways.

The price one has to pay for the above features are: slightly greater power consumption, and requirement to bond devices before using them together. Bonded nodes usually communicate with only one device (it's possible to bond with multiple centrals), as opposed to simple advertiser which simply broadcasts data to everyone.
