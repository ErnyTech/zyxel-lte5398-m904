echo 'AT+QCFG="pcmclk",1' > /dev/ttyUSB2
rmmod /lib/modules/3.10.14/ralink_pcm.ko
insmod /lib/modules/3.10.14/ralink_pcm.ko VOLTE_EN=1
echo "Voice mode switch to VoLTE"
