
Inofficial git fork of TCNOpen
==============================

Components for IEC61375 standardised communication.

This is an inofficial fork of the TCNOpen project into a git repository.

The intention is to analyse different aspects of the TRDP and SDTv2 protocols.

See also: https://sourceforge.net/projects/tcnopen/

Licenses
--------

Copied from the SF website:

* TRDP: MPLv2.0 http://www.mozilla.org/MPL/2.0/
* TRDPSpy: GPL http://www.gnu.org/licenses/gpl.html


Build
-----

    cd trdp
    make LINUX_config
    make
    make test
    make pdtest


Run
---

Add second IP address. E.g.:

    sudo ip address add 192.168.53.103/24 dev enp8s0

View help:

    bld/output/linux-rel/sendHello -h
    bld/output/linux-rel/receiveHello -h

Run hello clients:

    bld/output/linux-rel/receiveHello -o 192.168.53.104
    bld/output/linux-rel/sendHello -o 192.168.53.103 -t 192.168.53.104

Run local tests:

    bld/output/linux-rel/localtest -o 192.168.53.103 -i 192.168.53.104
    bld/output/linux-rel/localtest2 -o 192.168.53.103 -i 192.168.53.104
