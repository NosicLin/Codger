(1)计算矩形的面积

[Program]

rect=Rectangle(2,5)
width=rect.width
height=rect.height
area=width*height
print area
print rect.area()

[translate]

symbol "Rectangle"
frame_func
object 2
pushg
object 5
pushg 
call
destory_func
assign rect 

symbol rect 
symbol_r width
assign width
symbol height
symbol_r height
assign height 

symbol width 
pushd
symbol height
pushd
expr "@*"
assign area

symbol area
print

symbol rect 
symbol_r area
frame_func
call 
destory_func 
print 




