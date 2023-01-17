nRF Home
========

*nRF Home* is a template code for Nordic nRF chips with BLE capability. The template code can be used to quickly bootstrap a project for home automation devices based on BLE. Originally the project was supposed to be a static library, but this could be troublesome due to possible discrepancies between SDK configuration for a static library and user's code. Given that, instead of looking for voodoo based workarounds which would make the code complicated more than necessary, I decided to keep it simple -- you clone (or fork) the repo, and simply start developing your project on top of it.

.. note::
    I don't like "smart" word being put everywhere. Adding a radio transceiver to a power outlet does not make it smart. Neither a home with radio controlled devices is smart. This is just "automation". The home can become smart if you implement algorithms controlling the home automation in a smart way. Until then, if you have to click a button to turn off the light, it's an automation (barely, because you still have to click the button manually).

Why BLE?
--------

I'm constantly repeating: "Bluetooth Low Energy is way too underrated in home automation universe". Everyone focused on Wi-Fi, and I'm not surprised why - it's simple, ESP chips are cheap, and there's Wi-Fi everywhere. It's not a cruciate, I'm not trying to convert people to use BLE, but if you'd like to power your <whatever> sensor from a CR2032 for months or even years, then Wi-Fi won't make it.

Why nRF?
--------

Cheap, versatile, fast. BLE devices for hobbyists are usually UART's on top of BLE (UART service with TX and RX characteristics), which means it uses only a few percent of BLE capabilities. nRF chips, like nRF52840, give access to every aspect of BLE, allowing developers to control nearly everything what's being sent over radio, so the developer is responsible for setting up proper services, characteristics, authentication etc. Sounds complicated, it is complicated (I'm not gonna lie), but it can be learnt.

With great power comes great responsibility and steep learning curve. SDK for nRF is overwhelming for newcomers, but after a couple of weeks it starts to be quite intuitive. This template code can help with understanding the SDK's internals.

Why?
----

There are a couple of reasons I started learning nRF and eventually created this repo. The first and foremost: home automation market is a cancer. If you start building your automation around products from Vendor X, you are tied to Vendor X's products and whims forever. Want to switch to Vendor Y? Good luck with replacing all power outlets, sensors and other devices. Vendors put very much effort to make their devices incompatible with everything else as much as possible.

The second reason is my will to learn more about BLE. In spite of being used nearly everywhere, I have a feeling it's a niche topic.

It's ultimately power efficient solution. I don't like putting cables everywhere as much as I hate thinking about changing batteries. BLE allows to run wireless devices for extremely long time, while still maintaining a very good range, even through walls. At some point I'd like to investigate BLE Mesh, which allows for almost infinite range.

Repository structure
--------------------

Aside from the template code, I'd like to keep other stuff here, possibly some schematics, examples, and other source codes. For the time being, there's only one directory: **nrf-template** and it is what you think it is.

.. toctree::
    :maxdepth: 1

    nRF Template Code <nrf-template/README>