export PATH=$PATH:.
echo begin unit test

echo now is bg_expr2
bg_expr2 < bash.dat >t1.dat
echo bg_expr2 complete 
echo 
echo now is bg.py
python py.dat >t2.dat
echo bg.py complete 
diff t1.dat t2.dat



