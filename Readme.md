
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


Build TRDP
----------

This was tested on v 2.1.0.0

    git checkout experiments_2100

    cd trdp
    make LINUX_config
    make
    make test
    make pdtest


Run TRDP Examples
-----------------

This was tested on v 2.1.0.0

    git checkout experiments_2100

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


Build SDTv2
-----------

This was tested on main aka SDTv2 SDK 2.4.0.1

    git checkout main

    cd SDTv2
    rm -rf output
    make


Run SDTv2 Tests
------------------

Build Tests

    cd test
    make

Run Test

    cd test
    ./test

Run Test "IPT Latency Run ok"

    ./test/test -a
    ./test/test -a | grep EXCEL > test_a_output.csv
    libreoffice test_a_output.csv

The big question is now how do we interpret the output.
Aka what is the expection?


