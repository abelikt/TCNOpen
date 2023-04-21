#!/bin/bash

echo ""

#--------------------------------------------------------

QDISC_PORT="enp3s0"         # Queueing Disciplines, siehe: https://tsn.readthedocs.io/qdiscs.html
HOST_PORT="enp3s0"          # empfangen wird von enp3s0
EP_PORT="enp3s0np1"
TSN_PORTS=("enp3s0np2" "enp3s0np3" "enp3s0np4" "enp3s0np5")

CPU_MASK="F"                   # Bitmask: alle 4 Cores: 1 + 2 + 4 + 8

HOST_IP="10.100.0.200/24"

VLAN_ID="10"
VLAN_ID_BULK="20"
VLAN_IP="10.110.0.200/24"

#--------------------------------------------------------

SCRIPT_DIR="$(dirname "$0")"
CONFIG_BASE="${SCRIPT_DIR}/kontron_qbv"
CONFIG_ALL="_all_ports"        # suche nach CONFIG_BASE + CONFIG_ALL  =>  lade diese cfg in alle Ports
CONFIG_SEPARATE="_port_"       # wenn kein "all" existiert            =>  lade je Port [0..3] die separate cfg
CONFIG_FILETYPE=".cfg"
# -> one configfile:       "kontron_qbv_all_ports.cfg"
# -> separate configfiles: "kontron_qbv_port2.cfg" "kontron_qbv_port_3.cfg" "kontron_qbv_port_4.cfg" "kontron_qbv_port_5.cfg")

CYCLETIME="1/1000"             # 1/1000 = 1/1000 seconds    = 1ms 
CYCLETIME_EXTENSION="0"        # 0      = 0 nanoseconds

#--------------------------------------------------------
# Configure Switch (Traffic Control Queueing Disciplines: use Multiqueue Priority)

# Alstom-Hardware: "RTNETLINK answers: Operation not supported"
# tc qdisc add dev ${QDISC_PORT} root mqprio

#--------------------------------------------------------
# Configure IRQ affinity

# echo "Configure IRQ affinity"
# for irq in `ls -1 /sys/bus/pci/drivers/edgx-pci/*/msi_irqs`; do
#   if [ -e /proc/irq/${irq}/smp_affinity ]; then
#     echo ${CPU_MASK} > /proc/irq/${irq}/smp_affinity
#     echo "  set affinity-mask for irq ${irq} to CPU-Mask: ${CPU_MASK}"
#   fi
# done
# echo ""

#--------------------------------------------------------
# Configure Host-IP

echo "Configure Host-IP to IP $HOST_IP on port $HOST_PORT"

# remove old IP setup
for oldip in `ip addr show dev ${HOST_PORT} | sed -r "s/^( +inet[0-9]? (.*) scope.*)|.*$/\2/" | sort -r | uniq`; do
  echo "  -> delete old IP ${oldip} on port ${HOST_PORT}"
  ip addr delete ${oldip} dev ${HOST_PORT}
done
# ip addr show dev ${HOST_PORT}

# set new IP
ip addr add ${HOST_IP} dev ${HOST_PORT}
ip link set ${HOST_PORT} up
echo "  -> set new IP ${HOST_IP} on port ${HOST_PORT}"

echo "  -> final IP-configuration on port ${HOST_PORT}:"
ip addr show dev ${HOST_PORT}
echo ""

#--------------------------------------------------------
# Configure VLAN-ID and VLAN-IP

echo "Setup VLAN $VLAN_ID on port $HOST_PORT to IP $VLAN_IP"
ip link add link ${HOST_PORT} name ${HOST_PORT}.${VLAN_ID} type vlan id ${VLAN_ID} egress-qos-map 0:0 1:1 2:2 3:3 4:4 5:5 6:6 7:7

# remove old IP setup
for oldip in `ip addr show dev ${HOST_PORT}.${VLAN_ID} | sed -r "s/^( +inet[0-9]? (.*) scope.*)|.*$/\2/" | sort -r | uniq`; do
  echo "  -> delete old IP ${oldip} on port ${HOST_PORT}.${VLAN_ID}"
  ip addr delete ${oldip} dev ${HOST_PORT}.${VLAN_ID}
done
# ip addr show dev ${HOST_PORT}.${VLAN_ID}

# set new IP
ip addr add ${VLAN_IP} dev ${HOST_PORT}.${VLAN_ID}
ip link set ${HOST_PORT}.${VLAN_ID} up
echo "  -> set new IP ${VLAN_IP} on port ${HOST_PORT}.${VLAN_ID}"

echo "  -> final IP-configuration on port ${HOST_PORT}.${VLAN_ID}:"
ip addr show dev ${HOST_PORT}.${VLAN_ID}
echo ""

#--------------------------------------------------------
# Configure SWITCH VLAN-bridge to all (available) ports

for port in ${EP_PORT} ${TSN_PORTS[*]}
do
  # if [ "$(cat /sys/class/net/${port}/operstate)" != "up" ]
  # then
  #   echo "  port $port is not active"
  # continue
  # fi
 
  echo "  bridge VLAN $VLAN_ID to switch-port $port"
  bridge vlan add vid ${VLAN_ID} dev ${port}
  echo "  bridge VLAN $VLAN_ID_BULK to switch-port $port"
  bridge vlan add vid ${VLAN_ID_BULK} dev ${port}
done
echo ""

#--------------------------------------------------------
# Sofern "all" Datei vorhanden: allgemeines Scheduler-Setup fuer alle Ports benutzen
# Sonst: separaten Scheduler je Port einstellen fuer den eine Einzel-Datei vorhanden ist

one_file_for_all="$CONFIG_BASE$CONFIG_ALL$CONFIG_FILETYPE"
if [ -f $one_file_for_all ]
then
  echo "Configure all ports with cfg from: $one_file_for_all"
else
  echo "Configure each port with separate cfg from: $CONFIG_BASE$CONFIG_SEPARATE[2..5]$CONFIG_FILETYPE"
fi
echo ""

#--------------------------------------------------------
# Scheduler einstellen:

for port in ${TSN_PORTS[*]}
do
  INDEX=${port: -1}
  # echo ""
  
  if [ "$(cat /sys/class/net/${port}/operstate)" != "up" ]
  then
    echo "port[$INDEX] $port is not active"
	continue
  fi  
  
  if [ -f $one_file_for_all ]
  then
    file=$one_file_for_all
  else
    file=$CONFIG_BASE$CONFIG_SEPARATE$INDEX$CONFIG_FILETYPE
  fi
  
  # timenow=$(cat /sys/class/net/$port/ieee8021ST/CurrentTime)
  # mit der richtigen Zeit erscheint es sinnvoller, eine 0 geht aber wohl auch...
  timenow=0.0                   
  date=$(date --date="@$timenow")

  # echo "Configuration for port[$INDEX] $port, timenow = $timenow = $date, file = $file"

  # falls vorhanden: Konfiguration einlesen und aktivieren
  if [ -f $file ]
  then
	tsntool st disable $port
    tsntool st wrcl $port $file
    tsntool st configure $timenow $CYCLETIME $CYCLETIME_EXTENSION $port
    echo "configure tsn port[$INDEX]: $timenow $CYCLETIME $CYCLETIME_EXTENSION $port"
  else
    echo "no configuration file for port $port"
  fi

done
echo "";

#--------------------------------------------------------
# TSN-Scheduler auslesen:

echo "-------------------------------------";

for port in ${TSN_PORTS[*]}
do
  INDEX=${port: -1}
  echo "";
  
  if [ "$(cat /sys/class/net/${port}/operstate)" != "up" ]
  then
    echo "Port[$INDEX] $port is not active"
  else 
    echo "TSN scheduling configuration read-out for port[$INDEX] $port:"
    tsntool st rdacl $port
  fi

done
echo "";

echo "-------------------------------------";

#--------------------------------------------------------
