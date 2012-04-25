[file]
	garbage collection interface

[interface]
{
    [note]
     如果些时堆中垃圾过多，GrGc_Collection可以会被触发,
     调用该接口的程序必须小心，因为以前的针指都可能会失效；
     如果内存分配失败，则返回NULL，否则返回指向该内存单元的指针
     
	@在年轻分代堆上，分配一个内存单元
	TypeName* GrGc_New(TypeName,GrTypeInfo*);
	
	@分配一个内存单元，并且指定其处于那一个分代
        GrGc_HEAP_YONG:年轻分代
        GrGc_HEAP_OLD:年老分代
        GrGc_HEAP_STATIC:静态数据区
    TypeName* GcGr_Alloc(TypeName,GrTypeInfo*,long flags);
    
    @从静态数据存分配一个内存单元
    TypeName* GrGc_AllocStatic(TypeName,GrTypeInfo*);
    
    @从年老分代中分配一个内存单元
    TypeName* GrGc_AllocOld(TypeName,GrTypeInfo*);
    
    @从年轻分代中分配一个内存单元
    TypeName* GrGc_AllocYoung(TypeName,GrTypeInfo*);
}

[interface]
{
   [note]
    调用下面的接口并不会触发垃圾回收例程，也就是调用该接口是安全的，以前的指针都会有效
    如果内存分配失败，则返回NULL，否则返回指抽内存单元的指针
    
   
    @在年轻分代堆上，分配一个内存单元
    TypeName* GrGc_SafeNew(TypeName,GrTypeInfo*);
    
    @分配一个内存单元，并且指定其处于那一个分代
        GrGc_HEAP_YONG:年轻分代
        GrGc_HEAP_OLD:年老分代
        GrGc_HEAP_STATIC:静态数据区
    TypeName* GcGr_SafeAlloc(TypeName,GrTypeInfo*,long flags);
    
    @从静态数据存分配一个内存单元
    TypeName* GrGc_SafeAllocStatic(TypeName,GrTypeInfo*);
    
    @从年老分代中分配一个内存单元
    TypeName* GrGc_SafeAllocOld(TypeName,GrTypeInfo*);
    
    @从年轻分代中分配一个内存单元
    TypeName* GrGc_SafeAllocYoung(TypeName,GrTypeInfo*);
   
}
       
[interface]
{
    @垃圾回收例程，当堆中垃圾过多的时候，会被主动触发，或者可以显示的调用来清理堆中的垃圾
    int GrGc_Collection();
}



