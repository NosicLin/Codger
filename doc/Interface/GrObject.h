struct GrObject
{
	ssize_t g_ref;
	GrTypeInfo* g_type;
};


GrObject* Gr_Init(GrObject*,GrTypeInfo*);
GrObject* Gr_New(ClassName,GrTypeInfo*);
int Gr_Free(GrObject*);
int Gr_Destruct(GrObject*);
int Gr_Dealloc(GrObject*);

ssize_t Gr_RefCnt(GrObject*);
void Gr_Ref(GrObject*);
void Gr_UnRef(GrObject*);
void Gr_InitRef(GrObject*);


int Gr_GetSymbol(GrObject*,GrObject*,GrObject*,long flags);
GrObject* Gr_SetSymbol(GrObject*,GrObject*,long flags);

Robject* GrObject_Call(GrObject*,GrArray*,long flags);

int Gr_SetItem(GrObject*,GrObject*,GrObject*);
GrObject* Gr_GetItem(GrObject*,GrObject*);

GrObject* Gr_Positvie(GrObject*);
GrObject* Gr_Negative(GrObject*);
GrObject* Gr_Negated(GrObject*);

GrObject* Gr_Mul(GrObject*,GrObject*);
GrObject* Gr_Mod(GrObject*,GrObject*);
GrObject* Gr_Div(GrObject*,GrObject*);

GrObject* Gr_Plus(GrObject*,GrObject*);
GrObject* Gr_Minus(GrObject*,GrObject*);

GrObject* Gr_LShift(GrObject*,GrObject*);
GrObject* Gr_RShift(GrObject*,GrObject*);

GrObject* Gr_And(GrObject*,GrObject*);
GrObject* Gr_Xor(GrObject*,GrObject*);
GrObject* Gr_Or(GrObject*,GrObject*);


int Gr_Cmp(GrObject*,GrObject*,int op);

int Gr_Bool(GrObject*);


GrObject* Gr_Iter(GrObject*);
GrObject* Gr_IterNext(GrObject*);
GrObject* Gr_Print(GrObject*,FILE* f,long flags);


ssize_t Gr_Hash(GrObject*);


GrObject* Gr_RichCmp(GrObject*,GrObject,int op);

enum GrCmpType
{
	GR_CMP_UNKOWN=0,
	GR_CMP_LT,
	GR_CMP_LE,
	GR_CMP_GE,
	GR_CMP_GT,
	GR_CMP_EQ,
	GR_CMP_NE,
};
