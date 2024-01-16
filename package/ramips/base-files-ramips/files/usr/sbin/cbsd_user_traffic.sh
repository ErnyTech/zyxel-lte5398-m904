#!/bin/sh

LOCK_SCRIPT="/tmp/.cbsd_traffic.lock"
LOCK_IPTABLES="/tmp/.cbsd_iptables.lock"

FUNC_IPTABLES_BLOCK_SETTING ()
{
	echo "FUNC_IPTABLES_BLOCK_SETTING"
	iptables -F INPUT_TEST
	ip6tables -F INPUT_TEST
	iptables -A INPUT_TEST -i br+ -p udp --dport 53 -j REJECT
	iptables -A INPUT_TEST -i eth2+ -p udp --dport 53 -j REJECT
	ip6tables -A INPUT_TEST -i br+ -p udp --dport 53 -j REJECT
	ip6tables -A INPUT_TEST -i eth2+ -p udp --dport 53 -j REJECT
}

FUNC_IPTABLES_UNBLOCK_SETTING ()
{
	echo "FUNC_IPTABLES_UNBLOCK_SETTING"
	iptables -F INPUT_TEST
	ip6tables -F INPUT_TEST
}

FUNC_IPTABLES_BLOCK ()
{
	echo "FUNC_IPTABLES_BLOCK"

	# Lock file already exists, exit the script
	if [ -f $LOCK_IPTABLES ]; then
		echo "$LOCK_IPTABLES is already locked."
		rm -f $LOCK_SCRIPT
		exit 1
	fi

	# Create the lock file
	touch $LOCK_IPTABLES

	FUNC_IPTABLES_BLOCK_SETTING
}

FUNC_IPTABLES_UNBLOCK ()
{
	echo "FUNC_IPTABLES_UNBLOCK"

	if [ -f $LOCK_IPTABLES ]; then
		FUNC_IPTABLES_UNBLOCK_SETTING
		rm -f $LOCK_IPTABLES
	fi
}

FUNC_FORWARD_SETTING ()
{
	echo "FUNC_FORWARD_SETTING $1"
	if [ $1 -eq 0 ] || [ $1 -eq 1 ]; then
		echo $1 > /proc/sys/net/ipv4/ip_forward
		echo $1 > /proc/sys/net/ipv6/conf/all/forwarding
	else
		echo "$1 is not 0 or 1."
		rm -f $LOCK_SCRIPT
		exit 1
	fi

}

FUNC_TRAFFIC_BLOCK ()
{
	echo "FUNC_TRAFFIC_BLOCK"
	FUNC_FORWARD_SETTING 0
	FUNC_IPTABLES_BLOCK
}

FUNC_TRAFFIC_UNBLOCK ()
{
	echo "FUNC_TRAFFIC_UNBLOCK"
	FUNC_FORWARD_SETTING 1
	FUNC_IPTABLES_UNBLOCK
}

FUNC_TRAFFIC ()
{
	# Lock file already exists, exit the script
	if [ -f $LOCK_SCRIPT ]; then
		echo "$LOCK_SCRIPT is already locked."
		exit 1
	fi

	# Create the lock file
	touch $LOCK_SCRIPT

	# Do the normal stuff
	case $1 in
		-b) FUNC_TRAFFIC_BLOCK ;;
		-u) FUNC_TRAFFIC_UNBLOCK ;;
		*) echo "UNKNOWN CASE." ;;
	esac

	# clean-up before exit
	rm -f $LOCK_SCRIPT
}


FUNC_HELP ()
{
echo "
	Usage: $0 <State>
	-b	block user traffic.
	-u	unblock user traffic.
"
}


case $1 in
	-b|-u) FUNC_TRAFFIC $1 ;;
	*) FUNC_HELP ;;
esac
