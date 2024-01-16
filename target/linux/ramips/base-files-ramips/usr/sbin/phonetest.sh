#!/bin/sh

/etc/init.d/mstc_voice_modeswitch voip

A=`lsmod | grep ve_vtsp_rt | wc -l`
if [ $A -eq 0 ]; then
/etc/init.d/dsp_vtsp restart
fi

C=`ps T | grep voiceApp | grep -v grep | wc -l`
if [ $C -eq 0 ]; then
	/bin/icf.exe /bin/icf.cfg &
	/usr/bin/mm.exe &
	/usr/bin/voiceApp &
fi

while [ 1 ]
do
	C=`ps T | grep voiceApp | grep -v grep | wc -l`
	if [ $C -gt 2 ]; then
		phonetest dut 1234
		echo ""
		echo "OK"
		exit 0
	fi
	sleep 2
done

