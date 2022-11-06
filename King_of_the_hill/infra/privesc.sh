#!/bin/bash

#suid perms
chmod u+s /bin/chown
chmod u+s /usr/bin/awk
chmod u+s /usr/bin/vi

#adding vulnerable crontab
echo "*/2 * * * * root /root/run.sh" > /etc/crontab
echo -e "#!/bin/bash\n\nprintf 'hello'" > /root/run.sh
chmod 777 /root/run.sh

#vulnerable path in script
#echo -e "#!/bin/bash\n\necho'testing internet'\ncurl -I http://google.com" > /home/luke_skywalker/internet.sh
#chown root /home/luke_skywalker/internet.sh
#chmod 555 /home/luke_skywalker/internet.sh
#chmod u+s /home/luke_skywalker/internet.sh
# SUID BIT ONLY WORKS FOR COMPILED BINARY NOT SHELL SCRIPT
