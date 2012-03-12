export PATH=$PATH:.
echo begin unit test

echo now is bg.sh
chmod a+x bash.dat
bash.dat >t1.dat
echo bg.sh complete 
echo 
echo now is bg.py
python py.dat >t2.dat
echo bg.py complete 
diff t1.dat t2.dat



