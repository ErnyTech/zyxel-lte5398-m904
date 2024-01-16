sleep 2
while read line; do
	if [ "$line" == "RING" ]; then
		echo "RING"
		pcmtest w 30 4
		pcmtest h
		read hook < /tmp/onhook
		while [ "$hook" == "onhook" ]
		do
			read hook < /tmp/onhook
			if [ "$hook" == "onhook" ]; then
				sleep 1
				pcmtest h
			else
				pcmtest a
				pcmtest h
				read hook < /tmp/onhook
				while [ "$hook" == "offhook" ]
				do
					read hook < /tmp/onhook
					if [ "$hook" == "offhook" ]; then
						sleep 1
						pcmtest h
					else
						pcmtest d
						echo "phone is on-hook"
						break
					fi
				done
				break
			fi
			done
			break
	else
		sleep 1
	fi
done < /tmp/checkincomingcall
rm /tmp/checkincomingcall
killall cat