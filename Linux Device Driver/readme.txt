Jonathan Norheim
4088123 norhe003
UNITE

Compiling and installing the scullbuffer devices:

1. Execute Make: 
   make
2. If scull devices already exist then unload them first.
   sudo ./scull_unload
   This may ask you for your root password.
3. Load scull devices
   sudo ./scull_load
   This will create four scull devices (scull0, scull1, scull2, scull3), and four
   scullpipe devices (scullpipe0, scullpipe1, scullpipe2, scullpipe3). 
4. Check that devices are properly created.
   ls -ltr /dev/scull*
5. Change device permissions to 777
   sudo chmod 777 /dev/scull*

Potential issues with compiling and installing the scullbuffer devices:

If the compilation fails, it is likely the issue lies with inability to build clean.
Errors indicating this problem:
implicit declaration of function "init_MUTEX"
implicit declaration of function "signal_pending"

To get a clean compile, it is necessary to patch vmnet and vmci. This is explained at:
http://blog.gnu-designs.com/solved-building-vmware-workstation-modules-on-linux-2-6-32/

Testing the functioning of scull buffer devices:
- Open two terminals corresponding to two consumer processes.
- On these terminal windows execute the following command: more /dev/scullpipe0
  Both these processes will block as there is no data available in the pipe yet.
- Open another terminal corresponding to the producer process. 
  From this terminal window execute the following commands repeatedly:
  echo "String 1" > /dev/scullpipe0
  echo "String 2" > /dev/scullpipe0
- You will see that each string is consumed by only one consumer.
  Once a string is consumed, it is not available for other consumer.