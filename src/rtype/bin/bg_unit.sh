export PATH=$PATH:.
echo begin unit test

echo now is bg.sh
bg.sh >t1
echo bg.sh complete 
echo 
echo now is bg.py
python bg.py >t2
echo bg.py complete 
diff t1 t2



