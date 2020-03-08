#!/bin/bash 

test -b /dev/disk0 && echo ok || echo wrong
test -b /dev/console && echo ok || echo wrong
test -b DOESTNOTEXIST && echo ok || echo wrong
test -c /dev/disk0 && echo ok || echo wrong
test -c /dev/console && echo ok || echo wrong
test -d /dev/disk0 && echo ok || echo wrong
test -d ${HOME} && echo ok || echo wrong
test -d /dev/disk0 && echo ok || echo wrong
test -d ${HOME} && echo ok || echo wrong
test -e /dev/null && echo ok || echo wrong
test -e /usr/share/man/man2/execve.2 && echo ok || echo wrong
test -e DOESTNOTEXIST && echo ok || echo wrong
test -f /dev/null && echo ok || echo wrong
test -f /usr/share/man/man2/execve.2 && echo ok || echo wrong
test -L /dev/null && echo ok || echo wrong
test -L /var && echo ok || echo wrong
cd /tmp
touch notfifo && mkfifo fifo
test -p fifo && echo ok || echo wrong
test -p notfifo && echo ok || echo wrong
touch read noread; chmod u-r noread
test -r read && echo ok || echo wrong
test -r noread && echo ok || echo wrong
