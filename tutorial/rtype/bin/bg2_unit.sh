export PATH=$PATH:.
echo begin unit test

echo now is bg_expr2
bg_expr2 < bg.dat >t1
echo bg_expr2 complete 
echo 
echo now is bg.py
python bg.py >t2
echo bg.py complete 
diff t1 t2



